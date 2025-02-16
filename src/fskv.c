#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "sysvars.h"
#include "fskv.h"
#include "str2x.h"

#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_mem.h"

static luat_rtos_task_handle task_fskv_handle;
static luat_rtos_timer_t     timer0;

static uint32_t _c, _d, _e, _r, _w; // 4 counter store

const char *FSKV_NAME[] = {
    "COUNTER_C",
    "COUNTER_D",
    "C OUNTER_E",
    "COUNTER_R",
    "COUNTER_W",
    "COINER_SW2",
    "COIN_IN_LOW",
    "COIN_IN_HIGH",
    "TICKET_IN_LOW",
    "TICKET_IN_HIGH",
    "DEV_STATUS",
    "DEV_TYPE",
    "DEV_SCREEN_DIR",
    "COIN_PERPLAY_BTN1",
    "COIN_PERPLAY_BTN2",
    "TE_PULSE",
    "URL_WXPAY",
};

// return 1 success
static int ef_get_num(const char *key, uint32_t *data) {
    char value[16] = {0};
    int  ret       = luat_fskv_get(key, value, sizeof(value));
    if (ret < 0)
        return ret;
    return Str2Hex32(value, data);
}

static int ef_get_num8(const char *key, uint8_t *data) {
    char value[8] = {0};
    int  ret      = luat_fskv_get(key, value, sizeof(value));
    if (ret < 0)
        return ret;
    uint32_t v;
    ret   = Str2Hex32(value, &v);
    *data = (uint8_t)(v & 0xFF);
    // LUAT_DEBUG_PRINT("RRRRRRRRRRRRRRRRRRR key %s value %s, data %d ret %d", key, value, *data, ret);
    return ret;
}

// return >0 success
static int ef_set_num(const char *key, uint32_t data) {
    char value[16] = {0};
    int  len       = sprintf(value, "%x", data);
    return luat_fskv_set(key, value, len);
}

static int ef_set_num8(const char *key, uint8_t data) {
    char value[8] = {0};
    int  len      = sprintf(value, "%x", data);
    // LUAT_DEBUG_PRINT("luat_fskv_set %s %s %d", key, value, len);
    return luat_fskv_set(key, value, len);
}

static int ef_get_str(const char *key, char *data) {
    return luat_fskv_get(key, data, FSKV_STRING_MAX_LEN);
}

static int ef_set_str(const char *key, char *data) {
    if (strlen(data) >= FSKV_STRING_MAX_LEN)
        LUAT_DEBUG_PRINT("ERROR ef_set_str strlen %s is %dB >= FSKV_STRING_MAX_LEN", data, strlen(data));
    return luat_fskv_set(key, data, strlen(data));
}

/* read settings  */
static void fskv_read_data(void) {
    LUAT_DEBUG_PRINT("fskv_read_data");
    /* read counters */
    ef_get_num("c", &svCounterC);
    ef_get_num("d", &svCounterD);
    ef_get_num("e", &svCounterE);
    ef_get_num("r", &svCounterR);
    ef_get_num("w", &svCounterW);

    /* read settings */
    ef_get_str("urlWxPay", svUrlWXPay);
    ef_get_num8("dstatus", &svDeviceStatus);
    ef_get_num8("dtype", &svDeviceType);
    ef_get_num8("coinsw2", &svCoinSw2);
    ef_get_num8("pulsec1", &svCoinPulseWidthInLow);
    ef_get_num8("pulsec2", &svCoinPulseWidthInHigh);
    ef_get_num8("pulsec3", &svPrizePulseWidthInLow);
    ef_get_num8("pulsec4", &svPrizePulseWidthInHigh);
    ef_get_num8("dir", &svDeviceDirection);
    ef_get_num8("coinbtn1", &svCoinPerPlay);
    ef_get_num8("coinbtn2", &svCoinPerPlay2);
    ef_get_num8("tepulse", &svTEpulse);
}

/* reset counters */
void fskv_reset_data(void) {
    LUAT_DEBUG_PRINT("fskv_reset_data");
    luat_fskv_clear();

    /* set counters */
    svCounterC = svCounterD = svCounterE = svCounterR = svCounterW = 0;
    ef_set_num("c", svCounterC);
    ef_set_num("d", svCounterD);
    ef_set_num("e", svCounterE);
    ef_set_num("r", svCounterR);
    ef_set_num("w", svCounterW);

    /* set settings */
    strcpy(svUrlWXPay, "");
    svDeviceStatus          = 1;
    svDeviceType            = 2;
    svCoinSw2               = 40;
    svCoinPulseWidthInLow   = 15;
    svCoinPulseWidthInHigh  = 105;
    svPrizePulseWidthInLow  = 15;
    svPrizePulseWidthInHigh = 105;
    svDeviceDirection       = 0;
    svCoinPerPlay           = 1;
    svCoinPerPlay2          = 2;
    svTEpulse               = 80;
    ef_set_str("urlWxPay", svUrlWXPay);
    ef_set_num8("dstatus", svDeviceStatus);
    ef_set_num8("dtype", svDeviceType);
    ef_set_num8("coinsw2", svCoinSw2);
    ef_set_num8("pulsec1", svCoinPulseWidthInLow);
    ef_set_num8("pulsec2", svCoinPulseWidthInHigh);
    ef_set_num8("pulsec3", svPrizePulseWidthInLow);
    ef_set_num8("pulsec4", svPrizePulseWidthInHigh);
    ef_set_num8("dir", svDeviceDirection);
    ef_set_num8("coinbtn1", svCoinPerPlay);
    ef_set_num8("coinbtn2", svCoinPerPlay2);
    ef_set_num8("tepulse", svTEpulse);
}

static void fskv_dev_init(void) {
    LUAT_DEBUG_PRINT("fskv_init start");
    luat_fskv_init();

    size_t using_sz, max_sz, kv_count;
    luat_fskv_stat(&using_sz, &max_sz, &kv_count);
    LUAT_DEBUG_PRINT("luat_fskv_stat using %d, max %d, count %d", using_sz, max_sz, kv_count);
    if (kv_count == 0) {
        fskv_reset_data();
    }
    fskv_read_data();

    LUAT_DEBUG_PRINT("fskv_init end");
}

static void fskv_main_rountine(void *param) {
#define SETNUM(k, v)                                                                                                   \
    v = event.param1;                                                                                                  \
    ef_set_num(k, v);                                                                                                  \
    break;
#define SETNU8(k, v)                                                                                                   \
    v = event.param1;                                                                                                  \
    ef_set_num8(k, v);                                                                                                 \
    break;
#define SETSTR(k, v)                                                                                                   \
    strncpy(v, (char *)event.param1, sizeof(v));                                                                       \
    ef_set_str(k, v);                                                                                                  \
    break;

    int          ret;
    luat_event_t event;
    while (true) {
        ret = luat_rtos_event_recv(task_fskv_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);

        if (ret) {
            LUAT_DEBUG_PRINT("luat_rtos_event_recv ERROR %d", event.id);
            continue;
        }
        LUAT_DEBUG_PRINT("FSKV_SAVE %s -> %d", FSKV_NAME[event.id], event.param1);
        switch (event.id) {
            // int types
            case FSKV_EVT_COUNTER_C:
                SETNUM("c", svCounterC);
            case FSKV_EVT_COUNTER_D:
                SETNUM("d", svCounterD);
            case FSKV_EVT_COUNTER_E:
                SETNUM("e", svCounterE);
            case FSKV_EVT_COUNTER_R:
                SETNUM("r", svCounterR);
            case FSKV_EVT_COUNTER_W:
                SETNUM("r", svCounterW);
            case FSKV_EVT_COINER_SW2:
                SETNU8("coinsw2", svCoinSw2);
            case FSKV_EVT_COIN_IN_LOW:
                SETNU8("pulsec1", svCoinPulseWidthInLow);
            case FSKV_EVT_COIN_IN_HIGH:
                SETNU8("pulsec2", svCoinPulseWidthInHigh);
            case FSKV_EVT_TICKET_IN_LOW:
                SETNU8("pulsec3", svPrizePulseWidthInLow);
            case FSKV_EVT_TICKET_IN_HIGH:
                SETNU8("pulsec4", svPrizePulseWidthInHigh);
            case FSKV_EVT_DEV_STATUS:
                SETNU8("dstatus", svDeviceStatus);
            case FSKV_EVT_DEV_TYPE:
                SETNU8("dtype", svDeviceType);
            case FSKV_EVT_DEV_SCREEN_DIR:
                SETNU8("dir", svDeviceDirection);
            case FSKV_EVT_COIN_PERPLAY_BTN1:
                SETNU8("coinbtn1", svCoinPerPlay);
            case FSKV_EVT_COIN_PERPLAY_BTN2:
                SETNU8("coinbtn2", svCoinPerPlay2);
            case FSKV_EVT_TE_PULSE:
                SETNU8("tepulse", svTEpulse);
            // string types
            case FSKV_EVT_URL_WXPAY:
                SETSTR("urlWxPay", svUrlWXPay);
            default:
                break;
        }
    }
}

static void timer_save_important_kv(void *param) {
    if (_c != svCounterC) {
        _c = svCounterC;
        fskv_save_async(FSKV_EVT_COUNTER_C, svCounterC);
    }
    if (_d != svCounterD) {
        _d = svCounterD;
        fskv_save_async(FSKV_EVT_COUNTER_D, svCounterD);
    }
    if (_e != svCounterE) {
        _e = svCounterE;
        fskv_save_async(FSKV_EVT_COUNTER_E, svCounterE);
    }
    if (_r != svCounterR) {
        _r = svCounterR;
        fskv_save_async(FSKV_EVT_COUNTER_R, svCounterR);
    }
    if (_w != svCounterW) {
        _w = svCounterW;
        fskv_save_async(FSKV_EVT_COUNTER_W, svCounterW);
    }
}

void fskv_save_async(FSKV_ITEM item, uint32_t p1) {
    luat_rtos_event_send(task_fskv_handle, item, p1, 0, 0, 1000);
}

void fskv_task_init(void) {
    fskv_dev_init();

    _c = svCounterC;
    _d = svCounterD;
    _e = svCounterE;
    _r = svCounterR;
    _w = svCounterW;

    luat_rtos_task_create(&task_fskv_handle, 4 * 1024, 60, "fskv_init", fskv_main_rountine, NULL, 0);
    luat_rtos_timer_create(&timer0);
    luat_rtos_timer_start(timer0, FSKV_SAVE_IMPORTANT_INTERVAL, 1, timer_save_important_kv, NULL);
}

void fskv_deinit(void) {
    luat_rtos_timer_stop(timer0);
    luat_rtos_timer_delete(timer0);

    luat_rtos_task_suspend(task_fskv_handle);
    luat_rtos_task_delete(task_fskv_handle);
}
