#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#include "cJSON.h"

#include "luat_debug.h"
#include "luat_crypto.h"

#include "wrapper.h"
#include "sysvars.h"

#include "mqttdata.h"
#include "mqtt.h"
#include "fskv.h"
#include "wgpio.h"
#include "tecontrol.h"
#include "gui.h"

/* for variables */
static WCustomer customer_info = {0};

/********************** FOR PUBLISH **********************/
#define MQTT_PUB_QOS               1
#define MQTT_PUB_TOPIC_STATUS      "/device/%s/state"
#define MQTT_PUB_TOPIC_COUNTER     "/device/%s/data"
#define MQTT_PUB_TOPIC_TICKET_SAVE "/device/%s/ticketsave"
#define MQTT_PUB_TOPIC_SMS         "/device/%s/sms"

static char *status2Json(WStatusReport *report) {
    cJSON *jsonObj = cJSON_CreateObject();

    char timeStampStr[20] = {0};
    snprintf(timeStampStr, sizeof(timeStampStr), "0x%" PRIx64, SYSTICK());
    cJSON_AddStringToObject(jsonObj, "timeStamp", timeStampStr);
    cJSON_AddNumberToObject(jsonObj, "hardwareVersion", report->hardwareVersion);
    cJSON_AddNumberToObject(jsonObj, "firmwareVersion", report->firmwareVersion);
    cJSON_AddStringToObject(jsonObj, "imei", report->imei);
    cJSON_AddStringToObject(jsonObj, "imsi", report->imsi);
    cJSON_AddStringToObject(jsonObj, "iccid", report->iccid);
    cJSON_AddStringToObject(jsonObj, "phone", report->phone);
    cJSON_AddNumberToObject(jsonObj, "signal", report->signal);
    cJSON_AddNumberToObject(jsonObj, "pinCoinerInit", report->pinCoinerInit);
    cJSON_AddNumberToObject(jsonObj, "pinMbOnoffInit", report->pinMbOnoffInit);
    cJSON_AddNumberToObject(jsonObj, "pinExtCountInit", report->pinExtCountInit);
    cJSON_AddNumberToObject(jsonObj, "errorCode", report->errorCode);
    cJSON_AddStringToObject(jsonObj, "errorMessage", report->errorMessage);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

static char *counters2Json(WCounterReport *report) {
    cJSON *jsonObj = cJSON_CreateObject();

    cJSON_AddStringToObject(jsonObj, "dataFlag", report->dataFlag);
    cJSON_AddStringToObject(jsonObj, "lastCommandTS", report->lastCommandTS);
    cJSON_AddNumberToObject(jsonObj, "coin", report->coin);
    cJSON_AddNumberToObject(jsonObj, "prize", report->prize);
    cJSON_AddNumberToObject(jsonObj, "ticketWantOut", report->ticketWantOut);
    cJSON_AddNumberToObject(jsonObj, "ticketRealOut", report->ticketRealOut);
    cJSON_AddNumberToObject(jsonObj, "ticketEmulated", report->ticketEmulated);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

static char *ticketsave2Json(WTicketSave *report) {
    cJSON *jsonObj = cJSON_CreateObject();

    char timeStampStr[20] = {0};
    snprintf(timeStampStr, sizeof(timeStampStr), "0x%" PRIx64, SYSTICK());
    cJSON_AddStringToObject(jsonObj, "timeStamp", timeStampStr);
    cJSON_AddStringToObject(jsonObj, "userID", report->userID);
    cJSON_AddStringToObject(jsonObj, "ticket", report->ticketAdd);
    cJSON_AddNumberToObject(jsonObj, "ticketDirectOut", report->ticketDirectOut);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

static char *sms2Json(char *time, char *phone, char *pdu) {
    cJSON *jsonObj = cJSON_CreateObject();

    cJSON_AddStringToObject(jsonObj, "time", time);
    cJSON_AddStringToObject(jsonObj, "phone", phone);
    cJSON_AddStringToObject(jsonObj, "pdu", pdu);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

void mqtt_pub_status(int signal, char *imei, char *imsi, char *iccid, char *phone) {
    LOG("mqtt_pub_status Signal %d", signal);
    WStatusReport sts;

    sts.hardwareVersion = HARDWARE_VERSION;
    sts.firmwareVersion = SOFTWARE_VERSION;
    strcpy(sts.imei, imei);
    strcpy(sts.imsi, imsi);
    strcpy(sts.iccid, iccid);
    strcpy(sts.phone, phone);
    sts.signal          = signal;
    sts.pinCoinerInit   = 0;      // k
    sts.pinMbOnoffInit  = 0;      // k
    sts.pinExtCountInit = 0;      // k
    sts.errorCode       = 0;      // k
    strcpy(sts.errorMessage, ""); // k

    char *json = status2Json(&sts);
    if (json) {
        char topic[64] = {0};
        sprintf(topic, MQTT_PUB_TOPIC_STATUS, svSystemID);
        mqtt_publish_data(topic, json, 1, MQTT_PUB_QOS);
    }
}

void mqtt_pub_counter(void) {
    LOG("mqtt_pub_counter C %d, D %d, W %d, R %d, E %d", svCounterC, svCounterD, svCounterW, svCounterR, svCounterE);

    WCounterReport cnt;

    strncpy(cnt.dataFlag, svDataFlag, sizeof(cnt.dataFlag));
    strncpy(cnt.lastCommandTS, svLastCommandExecuted, sizeof(cnt.lastCommandTS));
    cnt.coin           = svCounterC;
    cnt.prize          = svCounterD;
    cnt.ticketWantOut  = svCounterW;
    cnt.ticketRealOut  = svCounterR;
    cnt.ticketEmulated = svCounterE;

    char *json = counters2Json(&cnt);
    if (json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_COUNTER, svSystemID);
        mqtt_publish_data(topic, json, 0, MQTT_PUB_QOS);
    }
}

void mqtt_pub_ticket_save(void) {
    LOG("mqtt_pub_ticket_save C %d, D %d, W %d, R %d, E %d", svCounterC, svCounterD, svCounterW, svCounterR, svCounterE);
    WTicketSave cnt;

    cnt.userID = customer_info.userID;
    // cnt.ticketAdd       = ticketAdd;
    // cnt.ticketDirectOut = ticketDirectOut;

    char *json = counters2Json(&cnt);
    if (json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_TICKET_SAVE, svSystemID);
        mqtt_publish_data(topic, json, 0, MQTT_PUB_QOS);
    }
}

void mqtt_pub_sms(char *time, char *phone, char *pdu) {
    LOG("mqtt_pub_sms time %s phone %s text %s", time, phone, pdu);
    char *json = sms2Json(time, phone, pdu);
    if (json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_SMS, svSystemID);
        mqtt_publish_data(topic, json, 0, MQTT_PUB_QOS);
    }
}

/********************** FOR SUBSCRIBE **********************/
enum _MQTT_COMMAND_IDS {
    MQTT_CMD_INSERTCOIN      = 1,
    MQTT_CMD_RESETCOUNTER    = 2,
    MQTT_CMD_SETDIRECTTICKET = 3,
    MQTT_CMD_REBOOT          = 99,
} MQTT_COMMAND_IDS;

/* Mqtt的json数据和配置结构体来回转换 */
static int json2Config(char *jsonIn, WConfig *config) {
    // LUAT_DEBUG_PRINT("json2Config: %s", jsonIn);

    cJSON *json = cJSON_Parse(jsonIn);
    if (!json) {
        LUAT_DEBUG_PRINT("JSON parse error: %s", cJSON_GetErrorPtr());
        return -1;
    }

    cJSON *item = NULL;

    item = cJSON_GetObjectItem(json, "firmwareVersion");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'firmwareVersion' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->firmwareVersion = item->valueint;

    item = cJSON_GetObjectItem(json, "firmwareUrl");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'firmwareUrl' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(config->firmwareUrl, item->valuestring, sizeof(config->firmwareUrl));

    item = cJSON_GetObjectItem(json, "systemMode");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'systemMode' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->systemMode = item->valueint;

    item = cJSON_GetObjectItem(json, "machineName");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'machineName' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(config->machineName, item->valuestring, sizeof(config->machineName));

    item = cJSON_GetObjectItem(json, "payUrl");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'payUrl' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(config->payUrl, item->valuestring, sizeof(config->payUrl));

    item = cJSON_GetObjectItem(json, "ticketUrl");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'ticketUrl' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(config->ticketUrl, item->valuestring, sizeof(config->ticketUrl));

    item = cJSON_GetObjectItem(json, "coinPulseWidth");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'coinPulseWidth' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->coinPulseWidth = item->valueint;

    item = cJSON_GetObjectItem(json, "ticketPulseWidth");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'ticketPulseWidth' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->ticketPulseWidth = item->valueint;

    item = cJSON_GetObjectItem(json, "coinPulseLow");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'coinPulseLow' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->coinPulseLow = item->valueint;

    item = cJSON_GetObjectItem(json, "coinPulseHigh");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'coinPulseHigh' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->coinPulseHigh = item->valueint;

    item = cJSON_GetObjectItem(json, "ticketPulseLow");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'ticketPulseLow' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->ticketPulseLow = item->valueint;

    item = cJSON_GetObjectItem(json, "ticketPulseHigh");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'ticketPulseHigh' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->ticketPulseHigh = item->valueint;

    item = cJSON_GetObjectItem(json, "coinPerPlay");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'coinPerPlay' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->coinPerPlay = item->valueint;

    item = cJSON_GetObjectItem(json, "direction");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'direction' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->direction = item->valueint;

    cJSON_Delete(json);
    return 0;
}

static int json2Command(char *jsonIn, WCommand *cmd) {
    cJSON *json = cJSON_Parse(jsonIn);
    if (!json) {
        LUAT_DEBUG_PRINT("JSON parse error: %s", cJSON_GetErrorPtr());
        return -1;
    }

    cJSON *item = cJSON_GetObjectItem(json, "timeStamp");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'timeStamp' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(cmd->timeStamp, item->valuestring, sizeof(cmd->timeStamp));

    item = cJSON_GetObjectItem(json, "commandId");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'commandId' field.");
        cJSON_Delete(json);
        return -1;
    }
    cmd->commandId = item->valueint;

    item = cJSON_GetObjectItem(json, "commandParam");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'commandParam' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(cmd->commandParam, item->valuestring, sizeof(cmd->commandParam));

    cJSON_Delete(json);
    return 0;
}

static int json2Customer(char *jsonIn, WCustomer *info) {
    cJSON *json = cJSON_Parse(jsonIn);
    if (!json) {
        LUAT_DEBUG_PRINT("JSON parse error: %s", cJSON_GetErrorPtr());
        return -1;
    }

    cJSON *item = cJSON_GetObjectItem(json, "userPortrait");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'userPortrait' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(info->userPortrait, item->valuestring, sizeof(info->userPortrait));

    item = cJSON_GetObjectItem(json, "nickName");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'nickName' field.");
        cJSON_Delete(json);
        return -1;
    }
    strncpy(info->nickName, item->valuestring, sizeof(info->nickName));

    item = cJSON_GetObjectItem(json, "userID");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'userID' field.");
        cJSON_Delete(json);
        return -1;
    }
    info->userID = item->valueint;

    cJSON_Delete(json);
    return 0;
}

void mqtt_data_cb_config(char *data, uint32_t len) {
    /* 检查是否收到长度0的 config，这是解绑 */
    if (len == 0) {
        LOG("收到空config，这是一个解绑操作");
        fskv_reset_data();
        LOG("fskv_reset_data() done");
        luat_rtos_task_sleep(1000);
        LOG("Reboot inited ");
        luat_os_reboot(0);
        return;
    }

    /* 正常命令 */
    bool    needReboot = false;
    WConfig config;
    if (json2Config(data, &config) != 0) {
        LOG("mqtt_data_cb_config() ERROR!!!! ");
        return;
    }

    // Info
    LOG("/device/+/config RECEIVED!");
    LUAT_DEBUG_PRINT("Firmware Version: %d", config.firmwareVersion);
    LUAT_DEBUG_PRINT("Firmware URL: %s", config.firmwareUrl);
    LUAT_DEBUG_PRINT("System Mode: %d", config.systemMode);
    LUAT_DEBUG_PRINT("Pay URL: %s", config.payUrl);
    LUAT_DEBUG_PRINT("Ticket URL: %s", config.ticketUrl);
    LUAT_DEBUG_PRINT("Machine Name: %s", config.machineName);
    LUAT_DEBUG_PRINT("Coin Pulse Width: %d", config.coinPulseWidth);
    LUAT_DEBUG_PRINT("Ticket Pulse Width: %d", config.ticketPulseWidth);
    LUAT_DEBUG_PRINT("Coin Pulse Low: %d", config.coinPulseLow);
    LUAT_DEBUG_PRINT("Coin Pulse High: %d", config.coinPulseHigh);
    LUAT_DEBUG_PRINT("Ticket Pulse Low: %d", config.ticketPulseLow);
    LUAT_DEBUG_PRINT("Ticket Pulse High: %d", config.ticketPulseHigh);
    LUAT_DEBUG_PRINT("Coin Per Play: %d", config.coinPerPlay);
    LUAT_DEBUG_PRINT("Direction: %d", config.direction);

    // 需要重启的
    if (config.systemMode != svDeviceType) {
        fskv_save_async(FSKV_EVT_DEV_TYPE, config.systemMode);
        needReboot = true;
    }
    if (config.coinPulseWidth != svCoinSw2) {
        fskv_save_async(FSKV_EVT_COINER_SW2, config.coinPulseWidth);
        needReboot = true;
    }
    if (strcmp(svPayUrl, config.payUrl) != 0) {
        fskv_save_async(FSKV_EVT_URL_WXPAY, config.payUrl);
        needReboot = true;
    }
    if (strcmp(svTicketUrl, config.ticketUrl) != 0) {
        fskv_save_async(FSKV_EVT_URL_TICKET, config.ticketUrl);
        needReboot = true;
    }
    if (strcmp(svMachineName, config.machineName) != 0) {
        fskv_save_async(FSKV_EVT_MACHINE_NAME, config.machineName);
        needReboot = true;
    }

    // 不需要重启的
    fskv_save_async(FSKV_EVT_TE_PULSE, config.ticketPulseWidth);
    svTEpulse = config.ticketPulseWidth;
    fskv_save_async(FSKV_EVT_COIN_IN_LOW, config.coinPulseLow);
    svCoinPulseWidthInLow = config.coinPulseLow;
    fskv_save_async(FSKV_EVT_COIN_IN_HIGH, config.coinPulseHigh);
    svCoinPulseWidthInHigh = config.coinPulseHigh;
    fskv_save_async(FSKV_EVT_TICKET_IN_LOW, config.ticketPulseLow);
    svPrizePulseWidthInLow = config.ticketPulseLow;
    fskv_save_async(FSKV_EVT_TICKET_IN_HIGH, config.ticketPulseHigh);
    svPrizePulseWidthInHigh = config.ticketPulseHigh;
    fskv_save_async(FSKV_EVT_COIN_PERPLAY_BTN1, config.coinPerPlay);
    svCoinPerPlay = config.coinPerPlay;
    // fskv_save_async(FSKV_EVT_COIN_PERPLAY_BTN2, config.coinPerPlay2);
    fskv_save_async(FSKV_EVT_DEV_SCREEN_DIR, config.direction);
    svDeviceDirection = config.direction;

    // 如果版本更高则升级
    // 需要排除https开头，因为现在https开头的直接要挂
    if (config.firmwareVersion > SOFTWARE_VERSION && memcmp(config.firmwareUrl, "http://", 7) == 0) {
        // initialize OTA
        LOG("Start OTA: new version %d", config.firmwareVersion);
        gpio_deinit();
        mqtt_task_deinit();
        extern void ota_task_init(const char *firmware_url);
        ota_task_init(config.firmwareUrl);
        return;
    }
    else {
        LOG("new firmware version: %d, address: %s", config.firmwareVersion, config.firmwareUrl);
        LOG("WILL NOT SOTA, quit!");
    }

    // 重启
    if (needReboot) {
        LOG("REBOOT required!");
        luat_rtos_task_sleep(1000);
        luat_os_reboot(0);
    }
}

void mqtt_data_cb_command(char *data, uint32_t len) {
    if (len == 0)
        return;

    WCommand cmd;

    if (json2Command(data, &cmd) != 0) {
        LOG("Mqtt_DataCallbackCommand() ERROR!!!! ");
        return;
    }

    switch (cmd.commandId) {
        case MQTT_CMD_INSERTCOIN: {
            int coin = strtoul(cmd.commandParam, NULL, 16);
            strncpy(svLastCommandExecuted, cmd.timeStamp, sizeof(svLastCommandExecuted));
            gpio_outCoin(coin);
        } break;
        case MQTT_CMD_RESETCOUNTER: {
            strncpy(svLastCommandExecuted, cmd.timeStamp, sizeof(svLastCommandExecuted));
            generate_data_flag();
        } break;
        case MQTT_CMD_SETDIRECTTICKET: {
            int dttimeout = strtoul(cmd.commandParam, NULL, 16);
            // k 这里要启动倒计时定时器，完成后标志设0
            svTicketDirectOut = 1;
            gui_ticket_update_save_timer(dttimeout);
        }
        case MQTT_CMD_REBOOT: {
            strncpy(svLastCommandExecuted, cmd.timeStamp, sizeof(svLastCommandExecuted));
            LOG("MQTT_CMD_REBOOT Reboot required!");
            luat_os_reboot(0);
        } break;
    }
}

void mqtt_data_cb_customer(char *data, uint32_t len) {
    if (len == 0)
        return;

    if (json2Customer(data, &customer_info) != 0) {
        LOG("Mqtt_DataCallbackCommand() ERROR!!!! ");
        return;
    }

    gui_ticket_switch();
    gui_ticket_set_customer_info(&customer_info);
}

/* clear json ptr */
void mqtt_data_free(void *obj) {
    cJSON_free(obj);
}
