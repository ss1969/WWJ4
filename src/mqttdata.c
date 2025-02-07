#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#include "cJSON.h"

#include "luat_debug.h"
#include "wrapper.h"
#include "sysvars.h"

#include "mqttdata.h"
#include "mqtt.h"
#include "fskv.h"
#include "wgpio.h"
#include "tecontrol.h"

/********************** FOR PUBLISH **********************/
#define MQTT_PUB_QOS           1
#define MQTT_PUB_TOPIC_STATUS  "/device/%s/state"
#define MQTT_PUB_TOPIC_COUNTER "/device/%s/data"
#define MQTT_PUB_TOPIC_SMS     "/device/%s/sms"

static char *status2Json(StatusReport *report) {
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
    cJSON_AddNumberToObject(jsonObj, "ticketDirectOut", report->ticketDirectOut);
    cJSON_AddNumberToObject(jsonObj, "signal", report->signal);
    cJSON_AddNumberToObject(jsonObj, "pinCoinerInit", report->pinCoinerInit);
    cJSON_AddNumberToObject(jsonObj, "pinMbOnoffInit", report->pinMbOnoffInit);
    cJSON_AddNumberToObject(jsonObj, "pinExtCountInit", report->pinExtCountInit);
    cJSON_AddNumberToObject(jsonObj, "errorCode", report->errorCode);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

static char *counters2Json(CounterReport *report) {
    cJSON *jsonObj = cJSON_CreateObject();

    char timeStampStr[20] = {0};
    snprintf(timeStampStr, sizeof(timeStampStr), "0x%" PRIx64, SYSTICK());
    cJSON_AddStringToObject(jsonObj, "timeStamp", timeStampStr);
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

static char *sms2Json(char *time, char *phone, char *pdu) {
    cJSON *jsonObj = cJSON_CreateObject();

    cJSON_AddStringToObject(jsonObj, "time", time);
    cJSON_AddStringToObject(jsonObj, "phone", phone);
    cJSON_AddStringToObject(jsonObj, "pdu", pdu);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

void mqtt_pub_status(void) {
    StatusReport sts;

    sts.hardwareVersion = HARDWARE_VERSION;
    sts.firmwareVersion = SOFTWARE_VERSION;
    strcpy(sts.imei, svIMEI);
    strcpy(sts.imsi, svIMSI);
    strcpy(sts.iccid, svICCID);
    strcpy(sts.phone, svPhoneNumber);
    sts.ticketDirectOut = svTicketDirectOut;
    sts.signal          = svSignal;
    sts.pinCoinerInit   = 0; // k
    sts.pinMbOnoffInit  = 0; // k
    sts.pinExtCountInit = 0; // k
    sts.errorCode       = 0; // k

    char *json = status2Json(&sts);
    if (json) {
        char topic[64] = {0};
        sprintf(topic, MQTT_PUB_TOPIC_STATUS, svSystemID);
        mqtt_publish_data(topic, json, MQTT_PUB_QOS);
    }
}

void mqtt_pub_counter(void) {
    CounterReport cnt;

    strcpy(cnt.lastCommandTS, svLastCommandExecuted);
    cnt.coin           = svCounterC;
    cnt.prize          = svCounterD;
    cnt.ticketWantOut  = svCounterW;
    cnt.ticketRealOut  = svCounterR;
    cnt.ticketEmulated = svCounterE;

    char *json = counters2Json(&cnt);
    if (json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_COUNTER, svSystemID);
        mqtt_publish_data(topic, json, MQTT_PUB_QOS);
    }
}

void mqtt_pub_sms(char *time, char *phone, char *pdu) {
    char *json = sms2Json(time, phone, pdu);
    if (json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_SMS, svSystemID);
        mqtt_publish_data(topic, json, MQTT_PUB_QOS);
    }
}

/********************** FOR SUBSCRIBE **********************/
enum _MQTT_COMMAND_IDS {
    MQTT_CMD_INSERTCOIN   = 1,
    MQTT_CMD_RESETCOUNTER = 2,
    MQTT_CMD_REBOOT       = 99,
} MQTT_COMMAND_IDS;

/* Mqtt的json数据和配置结构体来回转换 */
static int json2Config(char *jsonIn, MqttConfig *config) {
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
    strcpy(config->firmwareUrl, item->valuestring);

    item = cJSON_GetObjectItem(json, "resourceUrl");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'resourceUrl' field.");
        cJSON_Delete(json);
        return -1;
    }
    strcpy(config->resourceUrl, item->valuestring);

    item = cJSON_GetObjectItem(json, "systemMode");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'systemMode' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->systemMode = item->valueint;

    item = cJSON_GetObjectItem(json, "payUrl");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'payUrl' field.");
        cJSON_Delete(json);
        return -1;
    }
    strcpy(config->payUrl, item->valuestring);

    item = cJSON_GetObjectItem(json, "saveTicketUrl");
    if (!item || !cJSON_IsString(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'saveTicketUrl' field.");
        cJSON_Delete(json);
        return -1;
    }
    strcpy(config->saveTicketUrl, item->valuestring);

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

    item = cJSON_GetObjectItem(json, "ticketDirectOut");
    if (!item || !cJSON_IsNumber(item)) {
        LUAT_DEBUG_PRINT("Invalid or missing 'ticketDirectOut' field.");
        cJSON_Delete(json);
        return -1;
    }
    config->ticketDirectOut = item->valueint;

    cJSON_Delete(json);
    return 0;
}

static int json2Command(char *jsonIn, Command *cmd) {
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
    errno          = 0;
    cmd->timeStamp = strtoull(item->valuestring, NULL, 16);
    if (errno != 0) {
        LUAT_DEBUG_PRINT("Error: Invalid 'timeStamp' format or out of range.");
        cJSON_Delete(json);
        return -1;
    }

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

void mqtt_data_cb_config(char *data, uint32_t len) {
    /* 检查是否收到长度0的 config，这是解绑 */
    if (len == 0) {
        LUAT_DEBUG_PRINT("收到空config，这是一个解绑操作");
        fskv_reset_data();
        LUAT_DEBUG_PRINT("fskv_reset_data() done");
        luat_rtos_task_sleep(1000);
        LUAT_DEBUG_PRINT("Reboot inited ");
        luat_os_reboot(0);
        return;
    }

    /* 正常命令 */
    bool       needReboot = false;
    MqttConfig config;
    if (json2Config(data, &config) != 0) {
        LUAT_DEBUG_PRINT("mqtt_data_cb_config() ERROR!!!! ");
        return;
    }

    // Info
    LUAT_DEBUG_PRINT("/device/+/config RECEIVED!");
    LUAT_DEBUG_PRINT("Firmware Version: %d", config.firmwareVersion);
    LUAT_DEBUG_PRINT("Firmware URL: %s", config.firmwareUrl);
    LUAT_DEBUG_PRINT("Resource URL: %s", config.resourceUrl);
    LUAT_DEBUG_PRINT("System Mode: %d", config.systemMode);
    LUAT_DEBUG_PRINT("Pay URL: %s", config.payUrl);
    LUAT_DEBUG_PRINT("Save Ticket URL: %s", config.saveTicketUrl);
    LUAT_DEBUG_PRINT("Coin Pulse Width: %d", config.coinPulseWidth);
    LUAT_DEBUG_PRINT("Ticket Pulse Width: %d", config.ticketPulseWidth);
    LUAT_DEBUG_PRINT("Coin Pulse Low: %d", config.coinPulseLow);
    LUAT_DEBUG_PRINT("Coin Pulse High: %d", config.coinPulseHigh);
    LUAT_DEBUG_PRINT("Ticket Pulse Low: %d", config.ticketPulseLow);
    LUAT_DEBUG_PRINT("Ticket Pulse High: %d", config.ticketPulseHigh);
    LUAT_DEBUG_PRINT("Coin Per Play: %d", config.coinPerPlay);
    LUAT_DEBUG_PRINT("Direction: %d", config.direction);
    LUAT_DEBUG_PRINT("TicketDirectOut: %d", config.ticketDirectOut);

    // 需要重启的
    if (config.systemMode != svDeviceType) {
        fskv_save_async(FSKV_EVT_DEV_TYPE, config.systemMode);
        needReboot = true;
    }
    if (svCoinSw2 != config.coinPulseWidth) {
        fskv_save_async(FSKV_EVT_COINER_SW2, config.coinPulseWidth);
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
    gpio_setDirectOut(config.ticketDirectOut);

    // 如果版本更高则升级
    // 需要排除https开头，因为现在https开头的直接要挂
    if (config.firmwareVersion > SOFTWARE_VERSION && memcmp(config.firmwareUrl, "http://", 7) == 0) {
        // initialize OTA
        LUAT_DEBUG_PRINT("Start OTA: new version %d", config.firmwareVersion);
        gpio_deinit();
        mqtt_deinit();
        extern void ota_taskinit(const char *firmware_url);
        ota_taskinit(config.firmwareUrl);
        return;
    }
    else {
        LUAT_DEBUG_PRINT("new firmware version: %d, address: %s", config.firmwareVersion, config.firmwareUrl);
        LUAT_DEBUG_PRINT("WILL NOT SOTA, quit!");
    }

    // 重启
    if (needReboot) {
        LUAT_DEBUG_PRINT("REBOOT required!");
        luat_rtos_task_sleep(1000);
        luat_os_reboot(0);
    }
}

void mqtt_data_cb_command(char *data, uint32_t len) {
    if (len == 0)
        return;

    Command cmd;

    if (json2Command(data, &cmd) != 0) {
        LUAT_DEBUG_PRINT("Mqtt_DataCallbackCommand() ERROR!!!! ");
        return;
    }

    switch (cmd.commandId) {
        case MQTT_CMD_INSERTCOIN: {
            int coin = strtoul(cmd.commandParam, NULL, 16);
            strcpy(svLastCommandExecuted, cmd.timeStamp);
            gpio_outCoin(coin);
        } break;
        case MQTT_CMD_RESETCOUNTER: {
            strcpy(svLastCommandExecuted, cmd.timeStamp);
            // k
        } break;
        case MQTT_CMD_REBOOT: {
            strcpy(svLastCommandExecuted, cmd.timeStamp);
            LUAT_DEBUG_PRINT("Reboot required!");
            luat_os_reboot(0);
        } break;
    }
}

/* clear json ptr */
void mqtt_data_free(void *obj) {
    cJSON_free(obj);
}

#if 0 // 函数调用签名不正确
void Testbench()
{
    // 测试解析第一个 JSON（ParseFirmwareConfig）
    const char *json1 =
        "{"
        "\"firmwareVersion\":30,"
        "\"firmwareUrl\":\"http://www.123.com/fw.bin\","
        "\"resourceUrl\":\"http://..\","
        "\"systemMode\":1,"
        "\"payUrl\":\"http://\","
        "\"saveTicketUrl\":\"http://xxxxx\","
        "\"coinPulseWidth\":40,"
        "\"ticketPulseWidth\":80,"
        "\"coinPulseLow\":15,"
        "\"coinPulseHigh\":105,"
        "\"ticketPulseLow\":15,"
        "\"ticketPulseHigh\":105,"
        "\"coinPerPlay\":1,"
        "\"direction\":2"
        "}";

    MqttConfig config = {0}; // 初始化结构体
    if (json2Config(&json1, &config) == 0) {
        LUAT_DEBUG_PRINT("Parsed firmware config successfully.");
        LUAT_DEBUG_PRINT("Firmware Version: %d", config.firmwareVersion);
        LUAT_DEBUG_PRINT("Firmware URL: %s", config.firmwareUrl);
        LUAT_DEBUG_PRINT("Resource URL: %s", config.resourceUrl);
        LUAT_DEBUG_PRINT("System Mode: %d", config.systemMode);
        LUAT_DEBUG_PRINT("Pay URL: %s", config.payUrl);
        LUAT_DEBUG_PRINT("Save Ticket URL: %s", config.saveTicketUrl);
        LUAT_DEBUG_PRINT("Coin Pulse Width: %d", config.coinPulseWidth);
        LUAT_DEBUG_PRINT("Ticket Pulse Width: %d", config.ticketPulseWidth);
        LUAT_DEBUG_PRINT("Coin Pulse Low: %d", config.coinPulseLow);
        LUAT_DEBUG_PRINT("Coin Pulse High: %d", config.coinPulseHigh);
        LUAT_DEBUG_PRINT("Ticket Pulse Low: %d", config.ticketPulseLow);
        LUAT_DEBUG_PRINT("Ticket Pulse High: %d", config.ticketPulseHigh);
        LUAT_DEBUG_PRINT("Coin Per Play: %d", config.coinPerPlay);
        LUAT_DEBUG_PRINT("Direction: %d", config.direction);
    } else {
        LUAT_DEBUG_PRINT("Failed to parse firmware config.");
    }

    // 测试解析第二个 JSON（json2Command）
    const char *json2 =
        "{"
        "\"timeStamp\":\"0xABCDEF00ABCDEF00\","
        "\"commandId\":1,"
        "\"commandParam\":\"test\""
        "}";

    Command command = {0}; // 初始化结构体
    if (json2Command(&json2, &command) == 0) {
        LUAT_DEBUG_PRINT("Parsed command successfully.");
        LUAT_DEBUG_PRINT("Time Stamp: 0x%016llX", command.timeStamp);
        LUAT_DEBUG_PRINT("Command ID: %d", command.commandId);
        LUAT_DEBUG_PRINT("Command Param: %s", command.commandParam);
    } else {
        LUAT_DEBUG_PRINT("Failed to parse command.");
    }

    // 测试组装第三个 JSON（status2Json）
    StatusReport statusReportData = {
        .hardwareVersion = 1,
        .firmwareVersion = 1,
        .imei = "123456789012345",
        .ticketDirectOut = -50,
        .signal = 0,
        .pinCoinerInit = 0,
        .pinMbOnoffInit = 0,
        .pinExtCountInit = 0,
        .errorCode = 0
    };

    char *statusReportJson = NULL;
    if (status2Json(&statusReportJson, &statusReportData) == 0 && statusReportJson) {
        LUAT_DEBUG_PRINT("Status report JSON: %s", statusReportJson);
        cJSON_free(statusReportJson); // 释放 JSON 字符串内存
    } else {
        LUAT_DEBUG_PRINT("Failed to create status report JSON.");
    }

    // 测试组装第四个 JSON（counters2Json）
    CounterReport coinPrizeReportData = {
        .lastCommandTS = "123",
        .coin = 12345,
        .prize = 12345,
        .ticketWantOut = 12345,
        .ticketRealOut = 12345,
        .ticketEmulated = 12345
    };

    char *coinPrizeReportJson = NULL;
    if (counters2Json(&coinPrizeReportJson, &coinPrizeReportData) == 0 && coinPrizeReportJson) {
        LUAT_DEBUG_PRINT("Coin prize report JSON: %s", coinPrizeReportJson);
        cJSON_free(coinPrizeReportJson); // 释放 JSON 字符串内存
    } else {
        LUAT_DEBUG_PRINT("Failed to create coin prize report JSON.");
    }
}
#endif