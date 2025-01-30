#include <string.h>
#include <stdio.h>
#include "common_api.h"
#include "luat_mem.h"
#include "luat_pwm.h"
#include "luat_rtc.h"
#include "luat_gpio.h"

#include "wrapper.h"
#include "vt_ctrl.h"
#include "str2x.h"
#include "sysvars.h"
#include "usart.h"
#include "wgpio.h"
#include "fskv.h"
#include "mqttdata.h"
#include "tecontrol.h"
#include "http.h"

#include "cli.h"

//---------------------------------------------------------------------------------------------
static void cmd_cls(int argc, char **argv) {
    CON_VT_Erase_Screen(1);
    CON_VT_Set_Cursor_to_XY(0, 0);
}

//---------------------------------------------------------------------------------------------
static void cmd_help(int argc, char **argv) {
    uart_print("Command         Function \n");
    uart_print("---------------------------------------------------------------------\n");
    CliPrintCmdList();
}

//---------------------------------------------------------------------------------------------
static void cmd_tick(int argc, char **argv) {
    static uint64_t _tick = 0;
    uint64_t        tick  = SYSTICK(); // 26000 per ms
    static uint64_t _ms   = 0;
    uint64_t        ms    = soc_get_poweron_time_ms();

    uart_print("soc_get_poweron_time_ms %llu, delta %llu\n", ms, ms - _ms);
    uart_print("SYSTICK %llu, delta %llu\n", tick, tick - _tick);
    _tick = tick;
    _ms   = ms;
    // uart_print("soc_get_utc %u\n",soc_get_utc());
    // uart_print("soc_get_utc_ms %llu\n",soc_get_utc_ms());
}

//---------------------------------------------------------------------------------------------
static void cmd_halt(int argc, char **argv) {
    extern void system_halt_for_update(void);

    uart_print("system_halt_for_update()");
    system_halt_for_update();
}

//---------------------------------------------------------------------------------------------
static void cmd_reboot(int argc, char **argv) {
    uart_print("system_reboot()");
    luat_os_reboot(0);
}

//---------------------------------------------------------------------------------------------
static void cmd_pwm(int argc, char **argv) {
    uint32_t channel, freq, ratio, count;

    if ((Str2Dec32(argv[1], &channel) == 0)) {
        uart_print("channel error :%d\n", channel);
        return;
    }
    if ((Str2Dec32(argv[2], &freq) == 0)) {
        uart_print("freq error\n");
        return;
    }
    if ((Str2Dec32(argv[3], &ratio) == 0)) {
        uart_print("ratio error :%d\n", ratio);
        return;
    }
    if ((Str2Dec32(argv[4], &count) == 0)) {
        uart_print("count error\n");
        return;
    }
    if (channel != 0 && channel != 1 && channel != 2 && channel != 4) {
        uart_print("ratio error :%d\n", ratio);
        return;
    }
    if (ratio > 1000) {
        uart_print("ratio error :%d\n", ratio);
        return;
    }

    int param = 123;
    // uart_print("PWM Set CB %d\n", luat_pwm_set_callback(channel, pwm_callback, &param));
    uart_print("PWM Start %d\n", luat_pwm_open(channel, freq, ratio, count));
}

//---------------------------------------------------------------------------------------------
static void cmd_pin(int argc, char **argv) {
    uint32_t id, value;
    if ((Str2Dec32(argv[1], &id) == 0)) {
        uart_print("id error :%d\n", id);
        return;
    }
    if ((Str2Dec32(argv[2], &value) == 0)) {
        uart_print("value error\n");
        return;
    }
    luat_gpio_set(id, value == 0 ? 0 : 1);
    uart_print("Set Pin %d to %d\n", id, value);
}

//---------------------------------------------------------------------------------------------
static void cmd_sysinfo(int argc, char **argv) {
    size_t total;
    size_t used;
    size_t max_used;

    uart_print("********************************************\n");
    luat_meminfo_sys(&total, &used, max_used);
    uart_print("luat_meminfo_sys: total %dB used %dB max_used %dB\n", total, used, max_used);

    uart_print("********************************************\n");
    uart_print("Minimal Free Stack:\n");
}

//---------------------------------------------------------------------------------------------
static void cmd_rtc(int argc, char **argv) {
    struct tm tblock = {0};
    luat_rtc_get(&tblock);
    uart_print("%04d/%02d/%02d/ %02d:%02d:%02d %02d\n", tblock.tm_year + 1900, tblock.tm_mon + 1, tblock.tm_mday,
               tblock.tm_hour, tblock.tm_min, tblock.tm_sec, tblock.tm_wday);
}

//---------------------------------------------------------------------------------------------
static void cmd_env(int argc, char **argv) {
    uart_print("PIN COIN_IN : %d\n", luat_gpio_get(PIN_COIN_IN));
    uart_print("PIN PRIZE_MB_ONOFF : %d\n", luat_gpio_get(PIN_PRZ_MB_ONOFF));
    uart_print("PIN PRIZE_EXT_COUNT : %d\n", luat_gpio_get(PIN_PRZ_EXT_COUNT));

    uart_print("   svCounterC %d\n", svCounterC);
    uart_print("   svCounterD %d\n", svCounterD);
    uart_print("   ticket emu %d\n", svCounterE);
    uart_print("   ticket real %d\n", svCounterR);
    uart_print("   ticket want %d\n", svCounterW);

    uart_print("2  svUrlWXPay %s\n", svUrlWXPay);
    uart_print("4  svDeviceStatus %d\n", svDeviceStatus);
    uart_print("5  svDeviceType %d\n", svDeviceType);
    uart_print("7  svCoinSw2 %d\n", svCoinSw2);
    uart_print("8  svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow);
    uart_print("9  svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh);
    uart_print("10 svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow);
    uart_print("11 svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh);
    uart_print("12 svDeviceDirection %d\n", svDeviceDirection);
    uart_print("13 svCoinPerPlay %d\n", svCoinPerPlay);
    uart_print("14 svCoinPerPlay2 %d\n", svCoinPerPlay2);
    uart_print("17 svTEpulse %d\n", svTEpulse);
}

//---------------------------------------------------------------------------------------------
static void cmd_set(int argc, char **argv) {
    uint32_t id, value;
    if ((Str2Dec32(argv[1], &id) == 0)) {
        uart_print("id error :%d\n", id);
        return;
    }

    if (id != 2 && id != 3) {
        if ((Str2Dec32(argv[2], &value) == 0)) {
            uart_print("value error\n");
            return;
        }
    }

    switch (id) {
        case 0:
            fskv_save_async(FSKV_EVT_COUNTER_C, value);
            uart_print("set svCounterC %d\n", svCounterC);
            break;
        case 1:
            fskv_save_async(FSKV_EVT_COUNTER_D, value);
            uart_print("set svCounterD %d\n", svCounterD);
            break;
        case 2:
            fskv_save_async(FSKV_EVT_URL_WXPAY, (uint32_t)argv[2]);
            uart_print("set svUrlWXPay %s\n", argv[2]);
            break;
        case 4:
            fskv_save_async(FSKV_EVT_DEV_STATUS, value);
            uart_print("set svDeviceStatus %d\n", svDeviceStatus);
            break;
        case 5:
            fskv_save_async(FSKV_EVT_DEV_TYPE, value);
            ;
            uart_print("set svDeviceType %d\n", svDeviceType);
            break;
        case 7:
            fskv_save_async(FSKV_EVT_COINER_SW2, value);
            uart_print("set svCoinSw2 width %d\n", svCoinSw2);
            break;
        case 8:
            fskv_save_async(FSKV_EVT_COIN_IN_LOW, value);
            uart_print("set svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow);
            break;
        case 9:
            fskv_save_async(FSKV_EVT_COIN_IN_HIGH, value);
            uart_print("set svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh);
            break;
        case 10:
            fskv_save_async(FSKV_EVT_TICKET_IN_LOW, value);
            uart_print("set svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow);
            break;
        case 11:
            fskv_save_async(FSKV_EVT_COIN_IN_HIGH, value);
            uart_print("set svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh);
            break;
        case 12:
            fskv_save_async(FSKV_EVT_DEV_SCREEN_DIR, value);
            uart_print("set svDeviceDirection %d\n", svDeviceDirection);
            break;
        case 13:
            fskv_save_async(FSKV_EVT_COIN_PERPLAY_BTN1, value);
            uart_print("set svCoinPerPlay %d\n", svCoinPerPlay);
            break;
        case 14:
            fskv_save_async(FSKV_EVT_COIN_PERPLAY_BTN2, value);
            uart_print("set svCoinPerPlay2 %d\n", svCoinPerPlay2);
            break;
        case 17:
            fskv_save_async(FSKV_EVT_TE_PULSE, value);
            uart_print("set svTEpulse %d\n", svTEpulse);
            break;
    }
}

//---------------------------------------------------------------------------------------------
static void cmd_sys_debugcoin(int argc, char **argv) {
    if (svDbgCoin == 0)
        svDbgCoin = 1;
    else
        svDbgCoin = 0;
    uart_print("Debug Coin Mode : %s\n", svDbgCoin ? "ON" : "OFF");
}

//---------------------------------------------------------------------------------------------
static void cmd_coin(int argc, char **argv) {
    uint32_t count;

    if ((Str2Dec32(argv[1], &count) == 0)) {
        uart_print("coin count error :%d\n", count);
        return;
    }
    uart_print("coin emulate %d\n", count);
    gpio_outCoin(count);
}

//---------------------------------------------------------------------------------------------
static void cmd_ticket(int argc, char **argv) {
    uint32_t count;

    if ((Str2Dec32(argv[1], &count) == 0)) {
        uart_print("ticket count error :%d\n", count);
        return;
    }
    uart_print("ticket emulate %d\n", count);
    gpio_outTicket(count);
}

//---------------------------------------------------------------------------------------------
static void cmd_direct(int argc, char **argv) {
    uint32_t d;

    if ((Str2Dec32(argv[1], &d) == 0)) {
        uart_print("direct count error :%d\n", d);
        return;
    }
    uart_print("direct ticket out: %d -> %d\n", svTicketDirectOut, d);
    te_set_direct_out(d);
}

//---------------------------------------------------------------------------------------------
static void cmd_test1(int argc, char **argv) {
    mqtt_pub_status();
    mqtt_pub_counter();
}

void http_cb(const char *data, const int size, HTTP_STATUS status) {
    switch (status) {
        case TEST_HTTP_GET_DATA:
            uart_print_async("HTTP DATA : %s\n", data);
            break;
        default:
            break;
    }
}

//---------------------------------------------------------------------------------------------
static void cmd_test2(int argc, char **argv) {

    http_get(svHttpServer, http_cb);
}

//---------------------------------------------------------------------------------------------
/* COMMANDS LIST */
struct cli_command cli[] = {
    /* system */
    {"cls", "clear screen", cmd_cls},
    {"help", "help", cmd_help},
    {"sysinfo", "os information", cmd_sysinfo},
    {"tick", "tick", cmd_tick},
    {"halt", "halt", cmd_halt},
    {"reboot", "reboot", cmd_reboot},
    {"pwm", "pwm [ch] [Hz] [Ratio] [Count]", cmd_pwm},
    {"pin", "pin [pin id] [value]", cmd_pin},
    {"time", "time", cmd_rtc},
    {"env", "env", cmd_env},
    {"set", "set [env id] [value]", cmd_set},

    {"dbg", "dbg", cmd_sys_debugcoin},
    {"coin", "coin [count]", cmd_coin},
    {"ticket", "ticket [count]", cmd_ticket},
    {"direct", "direct out mode", cmd_direct},
    // {"prize",           "prize [count]",         			cmd_prize},
    {"t1", "test1", cmd_test1},
    {"t2", "test2", cmd_test2},
};
int32_t cli_num = sizeof(cli) / sizeof(cli[0]);
