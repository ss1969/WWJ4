#include "luat_network_adapter.h"
#include "common_api.h"
#include "luat_debug.h"
#include "luat_mem.h"
#include "luat_rtos.h"

#include "luat_mobile.h"
#include "libemqtt.h"
#include "luat_mqtt.h"
#include "luat_mcu.h"
#include "luat_uart.h"

#include "mqtt.h"
#include "mqttdata.h"
#include "wrapper.h"
#include "sysvars.h"

// 配置
static char MQTT_HOST[256] = "111.231.206.29";
static int MQTT_PORT = 9883;
static char USERNAME[32] = "admin";
static char PASSWORD[32] = "fkww_168";

// 结构
typedef struct _MQTT_SUB_ACTIONS_DEF{
    char topicString[128];
    char qosLevel;
    void (*DataHandler)(void* data, uint32_t len);
}MQTT_SUB_ACTIONS_DEF;

typedef struct _MQTT_MSG
{
    int qos;
    char topic[64];
	char *json;
	int len;
}MQTT_MSG;

// SUB 项目
const char *MQTT_SUB_TOPIC_PATTERNS[] = {
    "/device/%s/config",
    "/device/%s/command",
};

static MQTT_SUB_ACTIONS_DEF MQTT_SUB_ACTIONS[] = {
    {
		.qosLevel = 1,
 		.DataHandler = mqtt_data_cb_config,
	},
    {
		.qosLevel = 1,
   		.DataHandler = mqtt_data_cb_command,
	},
};
#define MQTT_SUB_ACTIONS_DEF_COUNT (sizeof(MQTT_SUB_ACTIONS) / sizeof(MQTT_SUB_ACTIONS_DEF))

static void (*MQTT_PUB_AFTERCONNECT[])() = {
    mqtt_pub_status,
    mqtt_pub_counter
};

// 变量
static luat_rtos_task_handle task_mqtt_handle;
static luat_mqtt_ctrl_t *mqttHandle;
static luat_rtos_mutex_t mqtt_sema_puback;

// 辅助函数
static const char* mqtt_get_msg_name(uint16_t msg)
{
    switch (msg & 0xF0) { // Mask the lower 4 bits to match the defined values
        case MQTT_MSG_CONNECT: return "CONNECT";
        case MQTT_MSG_CONNACK: return "CONNACK";
        case MQTT_MSG_PUBLISH: return "PUBLISH";
        case MQTT_MSG_PUBACK: return "PUBACK";
        case MQTT_MSG_PUBREC: return "PUBREC";
        case MQTT_MSG_PUBREL: return "PUBREL";
        case MQTT_MSG_PUBCOMP: return "PUBCOMP";
        case MQTT_MSG_SUBSCRIBE: return "SUBSCRIBE";
        case MQTT_MSG_SUBACK: return "SUBACK";
        case MQTT_MSG_UNSUBSCRIBE: return "UNSUBSCRIBE";
        case MQTT_MSG_UNSUBACK: return "UNSUBACK";
        case MQTT_MSG_PINGREQ: return "PINGREQ";
        case MQTT_MSG_PINGRESP: return "PINGRESP";
        case MQTT_MSG_DISCONNECT: return "DISCONNECT";
        default: return "UNKNOWN";
    }
}

// MQTT 回调函数
static void mqtt_main_callback(luat_mqtt_ctrl_t *ctrl, uint16_t event)
{
    int ret = 0;
    const uint8_t *ptr = NULL;
    uint16_t msgId = 0;

    switch (event) {
		case MQTT_MSG_CONNACK: {
			LUAT_DEBUG_PRINT("MQTT connected successfully.");
			for(int i = 0; i < MQTT_SUB_ACTIONS_DEF_COUNT; i++){
				mqtt_subscribe(&ctrl->broker, MQTT_SUB_ACTIONS[i].topicString, &msgId, MQTT_SUB_ACTIONS[i].qosLevel);
				LUAT_DEBUG_PRINT("Subscribing to topic: %s, msgID %d", MQTT_SUB_ACTIONS[i].topicString, msgId);
			}
			for (int i = 0; i < sizeof(MQTT_PUB_AFTERCONNECT) / sizeof(MQTT_PUB_AFTERCONNECT[0]); i++) {
				MQTT_PUB_AFTERCONNECT[i]();
			}
			break;
		}

		case MQTT_MSG_PUBLISH: {
			const char* ptrTopic, *ptrData = NULL;
			uint16_t topicLen = mqtt_parse_pub_topic_ptr(ctrl->mqtt_packet_buffer, &ptrTopic);
			uint32_t payloadLen = mqtt_parse_pub_msg_ptr(ctrl->mqtt_packet_buffer, &ptrData);
			LUAT_DEBUG_PRINT("MQTT_MSG_PUBLISH ----------> %d payload", payloadLen);

			for(int i = 0; i < MQTT_SUB_ACTIONS_DEF_COUNT; i++){
				if(memcmp(ptrTopic, MQTT_SUB_ACTIONS[i].topicString, topicLen) == 0){	// topic相符则调用 DataHandler
					MQTT_SUB_ACTIONS[i].DataHandler(ptrData, payloadLen);
				}
			}
			break;
		}

		case MQTT_MSG_PUBACK:
			luat_rtos_semaphore_release(mqtt_sema_puback);
			LUAT_DEBUG_PRINT("MQTT_MSG_PUBACK received.");
		case MQTT_MSG_PUBCOMP:
			// {
			// 	uint16_t ackMsgId = mqtt_parse_msg_id(ctrl->mqtt_packet_buffer);
			// 	LUAT_DEBUG_PRINT("Message acknowledgment received: msgId=%d", ackMsgId);
			// }
			break;
		case MQTT_MSG_DISCONNECT: {
			LUAT_DEBUG_PRINT("MQTT disconnected. Attempting to reconnect...");
			if (MQTT_AUTOCON) {
				luat_mqtt_reconnect(ctrl);
			}
			break;
		}
		//=================================
		case MQTT_MSG_RELEASE:
			LUAT_DEBUG_PRINT("MQTT Release message received.");
			break;
		case MQTT_MSG_TCP_TX_DONE:	// for tx data done, used when qos==0 as a sign of send.
			break;
		case MQTT_MSG_TIMER_PING:
			LUAT_DEBUG_PRINT("MQTT PING timer triggered. Sending PING.");
			luat_mqtt_ping(ctrl);
			break;
		case MQTT_MSG_RECONNECT: {
			if (MQTT_AUTOCON) {
				LUAT_DEBUG_PRINT("MQTT auto-reconnect triggered.");
				luat_mqtt_reconnect(ctrl);
			}
			break;
		}
		case MQTT_MSG_CLOSE: {
			LUAT_DEBUG_PRINT("MQTT connection closed. Attempting manual reconnect...");
			if (!MQTT_AUTOCON) {
				ret = luat_mqtt_reconnect(ctrl);
				if (ret) {
					LUAT_DEBUG_PRINT("Manual reconnect failed: %d", ret);
					luat_mqtt_close_socket(ctrl);
					return;
				}
			}
			break;
		}
		default:
			LUAT_DEBUG_PRINT("Unhandled MQTT event: %s 0x%x", mqtt_get_msg_name(event), event);
			break;
    }
}

// 初始化 MQTT 参数
static void mqtt_init_params(const char *host, int port, const char *username, const char *password)
{
	if(host != NULL)
		strcpy(MQTT_HOST, host);
	if(port != 0)
		MQTT_PORT = port;
	if(username != NULL)
		strcpy(USERNAME, username);
	if(password != NULL)
		strcpy(PASSWORD, password);

    LUAT_DEBUG_PRINT("MQTT parameters initialized: host=%s, port=%d", MQTT_HOST, MQTT_PORT);
}

// MQTT 主任务
static void mqtt_main_routine(void *param)
{
    int ret;
	uint32_t message_id = 0;

	// topics
	for(int i = 0; i < MQTT_SUB_ACTIONS_DEF_COUNT; i++){
		snprintf(MQTT_SUB_ACTIONS[i].topicString, sizeof(MQTT_SUB_ACTIONS[i].topicString), MQTT_SUB_TOPIC_PATTERNS[i], MQTT_DEVICE_ID);
	}

	// handle
    mqttHandle = (luat_mqtt_ctrl_t *)MALLOC(sizeof(luat_mqtt_ctrl_t));
    ret = luat_mqtt_init(mqttHandle, NW_ADAPTER_INDEX_LWIP_GPRS);
    if (ret) {
        LUAT_DEBUG_PRINT("Failed to initialize MQTT: %d", ret);
        return;
    }

	// connect parameters
    mqtt_init_params(NULL, NULL, NULL, NULL);	//k 以后改成从https服务器获取

	// start connect
    luat_mqtt_connopts_t opts = {0};
    opts.is_tls = MQTT_SSL;
    opts.host = MQTT_HOST;
    opts.port = MQTT_PORT;
    ret = luat_mqtt_set_connopts(mqttHandle, &opts);

    mqtt_init(&mqttHandle->broker, MQTT_DEVICE_ID);
    mqtt_init_auth(&mqttHandle->broker, USERNAME, PASSWORD);

    mqttHandle->keepalive = 240;
	mqttHandle->broker.clean_session = 1;
    mqttHandle->reconnect = MQTT_AUTOCON;
    mqttHandle->reconnect_time = 3000; // 延迟3秒重连

    luat_mqtt_set_cb(mqttHandle, mqtt_main_callback);
    LUAT_DEBUG_PRINT("Connecting to MQTT...");
	ret = luat_mqtt_connect(mqttHandle);
    if (ret) {
        LUAT_DEBUG_PRINT("Failed to connect to MQTT: %d", ret);
		luat_mqtt_close_socket(mqttHandle);
        FREE(mqttHandle);
        return;
    }

	/* task loop for data publish */
	MQTT_MSG *msg = NULL;
    while (1) {
		// receive
		ret = luat_rtos_message_recv(task_mqtt_handle, &message_id, (void**)&msg, LUAT_WAIT_FOREVER);
		if(ret){
			LUAT_DEBUG_PRINT("luat_rtos_message_recv ERROR %d", message_id);
			continue;
		}
		// LUAT_DEBUG_PRINT("topic %s", msg->topic);
		// LUAT_DEBUG_PRINT("json %s", msg->json);

		// send
		uint16_t msgId = 0;
		mqtt_publish_with_qos(&mqttHandle->broker, msg->topic, msg->json, msg->len, 1, msg->qos, &msgId);
		if(luat_rtos_semaphore_take(mqtt_sema_puback, MQTT_PUBACK_TIMEOUT) == 0){
			LUAT_DEBUG_PRINT("Published topic: %s, len %dB, msgID %d", msg->topic, msg->len, msgId);
		}
		else{
			svErrorCount ++;
		}

		// clean
		mqtt_data_free(msg->json);
		LUAT_MEM_FREE(msg);
		msg = NULL;
    }

	// end delete
	luat_rtos_task_delete(task_mqtt_handle);
}

// 动态修改 MQTT 连接参数并重连
void mqtt_update_reconnect(const char *host, int port, const char *username, const char *password)
{
    LUAT_DEBUG_PRINT("Updating MQTT parameters...");
    mqtt_init_params(host, port, username, password);

    if (mqttHandle) {
        luat_mqtt_close_socket(mqttHandle);
        luat_mqtt_reconnect(mqttHandle);
    }
}

// 发布数据
int mqtt_publish_data(char* topic, char *json, int qos)
{
	MQTT_MSG *msg = (MQTT_MSG *)LUAT_MEM_MALLOC(sizeof(MQTT_MSG));
	msg->qos = qos;
	strcpy(msg->topic, topic);
	msg->json = json;
	msg->len = strlen(msg->json);
	return luat_rtos_message_send(task_mqtt_handle, 0, msg);
}

void mqtt_taskinit(void)
{
	luat_rtos_semaphore_create(&mqtt_sema_puback, 1);
	luat_rtos_task_create(&task_mqtt_handle, 8 * 1024, 10, "task_mqtt", mqtt_main_routine, NULL, 16);
}

void mqtt_deinit(void)
{
	uint16_t msgId;
	for(int i = 0; i < MQTT_SUB_ACTIONS_DEF_COUNT; i++){
		mqtt_unsubscribe(&mqttHandle->broker, MQTT_SUB_ACTIONS[i].topicString, &msgId);
		LUAT_DEBUG_PRINT("Unsubscribing to topic: %s, msgID %d", MQTT_SUB_ACTIONS[i].topicString, msgId);
	}
	luat_rtos_semaphore_delete(mqtt_sema_puback);
	luat_rtos_task_suspend(task_mqtt_handle);
	luat_rtos_task_delete(task_mqtt_handle);

	LUAT_DEBUG_PRINT("mqtt_deinit end");
}