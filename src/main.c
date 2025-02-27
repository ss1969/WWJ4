#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"
#include "luat_pm.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_gpio.h"
#include "luat_mobile.h"
#include "luat_crypto.h"
#include "wdt.h"
#include "mbedtls/base64.h"
#include "libemqtt.h"

#include "sysvars.h"
#include "wgpio.h"
#include "usart.h"
#include "mqtt.h"
#include "fskv.h"
#include "http.h"
#include "mobile.h"
#include "mqttdata.h"
#include "wrapper.h"
#include "gui.h"
#include "defines.h"

#define HTTP_CRYPTO_KEY        "IcG6OnMCLgii7McbzuTtLNSbS7XU4F9G"
#define CRYPTO_AES_CBC_IV_SIZE 16
#define CRYPTO_CIPHER          "AES-256-CBC"
#define CRYPTO_PAD             "PKCS7"

static luat_rtos_task_handle task_main_handle;
static bool                  first = true; // first time connect

extern void cli_task_init(void);
extern void lvgl_task_init(void);

/* 解密固定格式 mqtt,xxx.xxx.xxx.xxx,12345,username,password 的base64 */
int decrypt_mqtt_info(const char *base64str, char *mqtt_server, int *mqtt_port, char *mqtt_user, char *mqtt_password) {
    char enc[128];
    char obuf[128] = {0};
    int  enclen;

    // uart_print("Input Str: %d\n", strlen(base64str));
    // uart_print("Input Str: %s\n", base64str);

    /* base64 */
    if (mbedtls_base64_decode(enc, sizeof(enc), &enclen, base64str, strlen(base64str)) != 0) {
        LOG("Base64 decode error!\n");
        return -1;
    }
    // uart_print("base64: %d\n Data: ", enclen);
    // for (int i = 0; i < enclen; i++) {
    //     uart_print("%02x", enc[i]);
    // }
    // uart_print("\n");
    // uart_print("Enc: %d\n Data: ", enclen - 16);
    // for (int i = 0; i < enclen - 16; i++) {
    //     uart_print("%02x", enc[i + 16]);
    // }
    // uart_print("\n");

    /* decrypt */
    luat_crypto_cipher_ctx_t cctx = {
        .cipher      = CRYPTO_CIPHER,
        .pad         = CRYPTO_PAD,
        .str         = enc + CRYPTO_AES_CBC_IV_SIZE,
        .key         = HTTP_CRYPTO_KEY,
        .iv          = enc,
        .cipher_size = strlen(CRYPTO_CIPHER),
        .pad_size    = strlen(CRYPTO_PAD),
        .str_size    = enclen - CRYPTO_AES_CBC_IV_SIZE,
        .key_size    = strlen(HTTP_CRYPTO_KEY),
        .iv_size     = CRYPTO_AES_CBC_IV_SIZE,
        .outbuff     = obuf,
        .flags       = 0, // 0: dec, 1: enc
    };

    int r = luat_crypto_cipher_xxx(&cctx);
    // uart_print("dec result: %d, outlen %d\n", r, cctx.outlen);
    // uart_print("dec string: %s\n", obuf);

    /* parse */
    char mqtt[5];
    int  matched = sscanf(obuf, "%4[mqtt],%31[^,],%d,%31[^,],%31s", mqtt, mqtt_server, mqtt_port, mqtt_user, mqtt_password);

    if (matched != 5 || strcmp(mqtt, "mqtt") != 0) {
        LOG("Mqtt config string format error!\n");
        return -2;
    }

    return 0;
}

void http_data_rx_cb(const char *data, const int size, HTTP_STATUS status) {
    static char *http_data = NULL;
    static int   http_rx   = 0;
    switch (status) {
        case HTTP_STATUS_GET_DATA: {
            // LOG("HTTP_STATUS_GET_DATA %d\n", size);
            // LOG("HTTP_STATUS_GET_DATA : %s\n", data);
            char *t = (char *)REALLOC(http_data, http_rx + size + 1); // end \0
            if (t != NULL)
                http_data = t;
            else {
                LOG("=== HTTP DATA REALLOC FAIL (%d), SYSTEM HALT ===", http_rx + size);
                while (1) {
                }
            }
            memcpy(http_data + http_rx, data, size);
            http_rx += size;
            http_data[http_rx] = 0;
            break;
        }
        case HTTP_STATUS_GET_DATA_DONE: {
            char mqtt_server[32];
            int  mqtt_port;
            char mqtt_user[32];
            char mqtt_password[32];
            if (decrypt_mqtt_info(http_data, mqtt_server, &mqtt_port, mqtt_user, mqtt_password) == 0)
                mqtt_task_init(mqtt_server, mqtt_port, mqtt_user, mqtt_password);
            FREE(http_data);
            http_data = NULL;
            http_rx   = 0;
        }
        default:
            break;
    }
}

void mobile_ready_status_cb(bool ready) {
    bool    r      = false;
    uint8_t signal = 0;
    char   *imei = NULL, *imsi = NULL, *iccid = NULL, *phone = NULL;
    mobile_get_status(&r, &signal, &imei, &imsi, &iccid, &phone);
    gui_all_set_signal(ready, mobile_detect_card(), signal);

    if (ready & first) {
        http_get(svHttpServer, http_data_rx_cb);
        first = false;
    }
}

void mobile_info_cb(void) {
    bool    ready  = false;
    uint8_t signal = 0;
    char   *imei = NULL, *imsi = NULL, *iccid = NULL, *phone = NULL;
    mobile_get_status(&ready, &signal, &imei, &imsi, &iccid, &phone);
    mqtt_pub_status(signal, imei, imsi, iccid, phone);
    gui_all_set_signal(ready, mobile_detect_card(), signal);
}

void mqtt_status_cb(uint16_t status) {
    switch (status) {
        case MQTT_MSG_CONNACK: {
            bool    ready  = false;
            uint8_t signal = 0;
            char   *imei = NULL, *imsi = NULL, *iccid = NULL, *phone = NULL;
            mobile_get_status(&ready, &signal, &imei, &imsi, &iccid, &phone);
            mqtt_pub_status(signal, imei, imsi, iccid, phone);
            gui_all_set_signal(ready, mobile_detect_card(), signal);
            break;
        }
        default:
            break;
    }
}

/* 主初始化线程 */
static void main_main_routine(void *param) {
    get_system_id();
    uart_task_init();
    fskv_task_init();
    gpio_task_init();
#if 1 // dynamic get mqtt parameters
    mobile_set_netready_callback(mobile_ready_status_cb);
    mobile_set_sms_callback(mqtt_pub_sms);
    mobile_set_info_callback(mobile_info_cb);
    mobile_task_init();
#else
    mobile_set_sms_callback(mqtt_pub_sms);
    mobile_task_init();
    mqtt_task_init("mq.catchtoy.cn", 9883, "admin", "fkww_168");
#endif
    mqtt_set_status_callback(mqtt_status_cb);
    lvgl_task_init();
    generate_data_flag();

    /* info */
    LOG("\nBUILD: %s %s\n", __DATE__, __TIME__);
    LOG("Sys mode: %d\n", svDeviceType);
    LOG("System ID: %s\n", svSystemID);
    LOG("DataFlag: %s\n", svDataFlag);

    /* cli */
    cli_task_init();

    int          ret;
    luat_event_t event;
    while (true) {
        // ret = luat_rtos_event_recv(task_main_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);

        // switch (event.id) {
        //     case MAIN_EVENT_OTA:

        //         extern void ota_task_init(void);
        //         // ota_task_init();
        //         break;

        //     default:
        //         break;
        // }

        gpio_toggle(PIN_LED_D0);
        luat_rtos_task_sleep(1 * 1000);
    }
}

void main_task_init(void) {
    /* 出现异常后默认为死机重启
       demo这里设置为 LUAT_DEBUG_FAULT_HANG_RESET 出现异常后尝试上传死机信息给PC工具，上传成功或者超时后重启
       如果为了方便调试，可以设置为 LUAT_DEBUG_FAULT_HANG ，出现异常后死机不重启
       但量产出货一定要设置为出现异常重启！！！！！！！！！
    */
    luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_RESET);
    luat_heap_init();
    luat_rtos_task_create(&task_main_handle, 2 * 1024, 1, "task_boot", main_main_routine, NULL, 0);
}

void main_deinit(void) {
    luat_rtos_task_suspend(task_main_handle);
    luat_rtos_task_delete(task_main_handle);
}

void system_halt_for_update(void) {
    extern void cli_deinit(void);
    extern void uart_deinit(void);
    extern void gpio_deinit(void);
    extern void fskv_deinit(void);

    int step = 1;
    LOG("HALT STEP %d", step++);
    main_deinit();
    LOG("HALT STEP %d", step++);
    gpio_deinit();
    LOG("HALT STEP %d", step++);
    fskv_deinit();
    LOG("HALT STEP %d", step++);
    uart_deinit();
    LOG("HALT STEP %d", step++);
    cli_deinit();
    LOG("HALT STEP %d", step++);
}

INIT_TASK_EXPORT(main_task_init, "0");
