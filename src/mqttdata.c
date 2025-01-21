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

/********************** FOR PUBLISH **********************/
#define MQTT_PUB_QOS		        1
#define MQTT_PUB_TOPIC_STATUS       "/device/%s/state"
#define MQTT_PUB_TOPIC_COUNTER      "/device/%s/data"
#define MQTT_PUB_TOPIC_SMS          "/device/%s/sms"

static char * status2Json(StatusReport *report)
{
    cJSON *jsonObj = cJSON_CreateObject();

    char timeStampStr[20] = {0};
    snprintf(timeStampStr, sizeof(timeStampStr), "0x%" PRIx64, SYSTICK());
    cJSON_AddStringToObject(jsonObj, "timeStamp", timeStampStr);
    cJSON_AddNumberToObject(jsonObj, "hardwareVersion", report->hardwareVersion);
    cJSON_AddNumberToObject(jsonObj, "firmwareVersion", report->firmwareVersion);
    cJSON_AddStringToObject(jsonObj, "imei", report->imei);
    cJSON_AddNumberToObject(jsonObj, "directTicketOut", report->directTicketOut);
    cJSON_AddNumberToObject(jsonObj, "signal", report->signal);
    cJSON_AddNumberToObject(jsonObj, "pinCoinerInit", report->pinCoinerInit);
    cJSON_AddNumberToObject(jsonObj, "pinMbOnoffInit", report->pinMbOnoffInit);
    cJSON_AddNumberToObject(jsonObj, "pinExtCountInit", report->pinExtCountInit);
    cJSON_AddNumberToObject(jsonObj, "errorCode", report->errorCode);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

static char * counters2Json(CounterReport *report)
{
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

static char * sms2Json(char* time, char* phone, char* pdu)
{
    cJSON *jsonObj = cJSON_CreateObject();

    cJSON_AddStringToObject(jsonObj, "time", time);
    cJSON_AddStringToObject(jsonObj, "phone", phone);
    cJSON_AddStringToObject(jsonObj, "pdu", pdu);

    char *jsonOut = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);
    return jsonOut;
}

void mqtt_pub_status(void)
{
    StatusReport sts;

    sts.hardwareVersion = HARDWARE_VERSION;
    sts.firmwareVersion = SOFTWARE_VERSION;
    strcpy(sts.imei, svIMEI);
    strcpy(sts.imsi, svIMSI);
    strcpy(sts.iccid, svICCID);
    sts.directTicketOut = svTicketDirectOut;
    sts.signal = svSignal;
    sts.pinCoinerInit = 0; //k
    sts.pinMbOnoffInit = 0;//k
    sts.pinExtCountInit = 0;//k
    sts.errorCode = 0;//k

    char *json = status2Json(&sts);
    if(json) {
        char topic[64] = {0};
        sprintf(topic, MQTT_PUB_TOPIC_STATUS, svSystemID);
        mqtt_publish_data(topic, json, MQTT_PUB_QOS);
    }
}

void mqtt_pub_counter(void)
{
    CounterReport cnt;

    strcpy(cnt.lastCommandTS, svLastCommandExecuted);
    cnt.coin = svCounterC;
    cnt.prize = svCounterD;
    cnt.ticketWantOut = svCounterW;
    cnt.ticketRealOut = svCounterR;
    cnt.ticketEmulated = svCounterE;

    char *json = counters2Json(&cnt);
    if(json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_COUNTER, svSystemID);
        mqtt_publish_data(topic, json, MQTT_PUB_QOS);
    }
}

void mqtt_pub_sms(char* time, char* phone, char* pdu)
{
    char *json = sms2Json(time, phone, pdu);
    if(json) {
        char topic[64];
        sprintf(topic, MQTT_PUB_TOPIC_SMS, svSystemID);
        mqtt_publish_data(topic, json, MQTT_PUB_QOS);
    }
}

/* Mqtt的json数据和配置结构体来回转换 */
static int json2Config(char *jsonIn, MqttConfig *config)
{
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

    cJSON_Delete(json);
    return 0;
}

static int json2Command(char *jsonIn, Command *cmd)
{
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
    errno = 0;
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
    strcpy(cmd->commandParam, item->valuestring);

    cJSON_Delete(json);
    return 0;
}

void mqtt_data_cb_config(char* data, uint32_t len)
{
    MqttConfig config;
    if(json2Config(data, &config) != 0)
    {
        LUAT_DEBUG_PRINT("mqtt_data_cb_config() ERROR!!!! ");
        return;
    }
    LUAT_DEBUG_PRINT("firmwareVersion %d", config.firmwareVersion);
}

void mqtt_data_cb_command(char* data, uint32_t len)
{
    Command cmd;

    if(json2Command(data, &cmd) != 0)
    {
        LUAT_DEBUG_PRINT("Mqtt_DataCallbackCommand() ERROR!!!! ");
        return;
    }
    LUAT_DEBUG_PRINT("CommandId %d", cmd.commandId);
}

/* clear json ptr */
void mqtt_data_free(void *obj)
{
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

    MqttConfig firmwareConfig = {0}; // 初始化结构体
    if (json2Config(&json1, &firmwareConfig) == 0) {
        LUAT_DEBUG_PRINT("Parsed firmware config successfully.");
        LUAT_DEBUG_PRINT("Firmware Version: %d", firmwareConfig.firmwareVersion);
        LUAT_DEBUG_PRINT("Firmware URL: %s", firmwareConfig.firmwareUrl);
        LUAT_DEBUG_PRINT("Resource URL: %s", firmwareConfig.resourceUrl);
        LUAT_DEBUG_PRINT("System Mode: %d", firmwareConfig.systemMode);
        LUAT_DEBUG_PRINT("Pay URL: %s", firmwareConfig.payUrl);
        LUAT_DEBUG_PRINT("Save Ticket URL: %s", firmwareConfig.saveTicketUrl);
        LUAT_DEBUG_PRINT("Coin Pulse Width: %d", firmwareConfig.coinPulseWidth);
        LUAT_DEBUG_PRINT("Ticket Pulse Width: %d", firmwareConfig.ticketPulseWidth);
        LUAT_DEBUG_PRINT("Coin Pulse Low: %d", firmwareConfig.coinPulseLow);
        LUAT_DEBUG_PRINT("Coin Pulse High: %d", firmwareConfig.coinPulseHigh);
        LUAT_DEBUG_PRINT("Ticket Pulse Low: %d", firmwareConfig.ticketPulseLow);
        LUAT_DEBUG_PRINT("Ticket Pulse High: %d", firmwareConfig.ticketPulseHigh);
        LUAT_DEBUG_PRINT("Coin Per Play: %d", firmwareConfig.coinPerPlay);
        LUAT_DEBUG_PRINT("Direction: %d", firmwareConfig.direction);
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
        .directTicketOut = -50,
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