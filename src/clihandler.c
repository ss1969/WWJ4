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

#include "cli.h"

//---------------------------------------------------------------------------------------------
static void cmd_cls(int argc, char** argv)
{
	CON_VT_Erase_Screen(1);
	CON_VT_Set_Cursor_to_XY(0, 0);
}

//---------------------------------------------------------------------------------------------
static void cmd_help(int argc, char** argv)
{
	usart_print("Command         Function \n");
	usart_print("---------------------------------------------------------------------\n");
	CliPrintCmdList();
}

//---------------------------------------------------------------------------------------------
static void cmd_tick(int argc, char** argv)
{
	static uint64_t _tick = 0;
	uint64_t tick = soc_get_poweron_time_tick();	// 26000 per ms
	static uint64_t _ms = 0;
	uint64_t ms = soc_get_poweron_time_ms();

	usart_print("soc_get_poweron_time_ms %llu, delta %llu\n", ms, ms-_ms);
	usart_print("soc_get_poweron_time_tick %llu, delta %llu\n", tick, tick - _tick);
	_tick = tick;
	_ms = ms;
	// usart_print("soc_get_utc %u\n",soc_get_utc());
	// usart_print("soc_get_utc_ms %llu\n",soc_get_utc_ms());
}

//---------------------------------------------------------------------------------------------
static void cmd_halt(int argc, char** argv)
{
	extern void system_halt_for_update(void);

	usart_print("system_halt_for_update()");
	system_halt_for_update();
}

//---------------------------------------------------------------------------------------------
static void cmd_reboot(int argc, char** argv)
{
	usart_print("system_reboot()");
	luat_os_reboot(0);
}

//---------------------------------------------------------------------------------------------
static void cmd_pwm(int argc, char** argv)
{
	uint32_t channel, freq, ratio, count;

	if((Str2Dec32(argv[1], &channel) == 0)){
		usart_print("channel error :%d\n", channel);
		return;
	}
	if((Str2Dec32(argv[2], &freq) == 0)){
		usart_print("freq error\n");
		return;
	}
	if((Str2Dec32(argv[3], &ratio) == 0)){
		usart_print("ratio error :%d\n", ratio);
		return;
	}
	if((Str2Dec32(argv[4], &count) == 0)){
		usart_print("count error\n");
		return;
	}
	if(channel != 0 && channel != 1 && channel != 2 && channel != 4){
		usart_print("ratio error :%d\n", ratio);
		return;
	}
	if(ratio > 1000){
		usart_print("ratio error :%d\n", ratio);
		return;
	}

	int param = 123;
	// usart_print("PWM Set CB %d\n", luat_pwm_set_callback(channel, pwm_callback, &param));
	usart_print("PWM Start %d\n", luat_pwm_open(channel, freq, ratio, count));
}

//---------------------------------------------------------------------------------------------
static void cmd_pin(int argc, char** argv)
{
	uint32_t id, value;
	if((Str2Dec32(argv[1], &id) == 0)){
		usart_print("id error :%d\n", id);
		return;
	}
	if((Str2Dec32(argv[2], &value) == 0)){
		usart_print("value error\n");
		return;
	}
	luat_gpio_set(id, value == 0 ? 0 : 1);
	usart_print("Set Pin %d to %d\n", id, value);
}

//---------------------------------------------------------------------------------------------
static void cmd_sysinfo(int argc, char** argv)
{
	size_t total;
	size_t used;
	size_t max_used;

	usart_print("********************************************\n");
	luat_meminfo_sys(&total, &used, max_used);
	usart_print("luat_meminfo_sys: total %dB used %dB max_used %dB\n", total, used, max_used);

	usart_print("********************************************\n");
	usart_print("Minimal Free Stack:\n");
}

//---------------------------------------------------------------------------------------------
static void cmd_rtc(int argc, char** argv)
{
	struct tm tblock = {0};
    luat_rtc_get(&tblock);
    usart_print("%04d/%02d/%02d/ %02d:%02d:%02d %02d\n",
			tblock.tm_year+1900,
			tblock.tm_mon+1,
			tblock.tm_mday,
			tblock.tm_hour,
			tblock.tm_min,
			tblock.tm_sec,
			tblock.tm_wday);
}

//---------------------------------------------------------------------------------------------
static void cmd_env(int argc, char** argv)
{
	usart_print("PIN COIN_IN : %d\n", luat_gpio_get(PIN_COIN_IN));
	usart_print("PIN PRIZE_MB_ONOFF : %d\n", luat_gpio_get(PIN_PRZ_MB_ONOFF));
	usart_print("PIN PRIZE_EXT_COUNT : %d\n", luat_gpio_get(PIN_PRZ_EXT_COUNT));
    usart_print("Emulated Ticket %d\n", gpio_emuTicket());

    usart_print("0  svCounterC %d\n", svCounterC);
    usart_print("1  svCounterD %d\n", svCounterD);
    usart_print("2  svUrlWXPay %s\n", svUrlWXPay);
    usart_print("3  svUrlOta %s\n", svUrlOta);
    usart_print("4  svDeviceStatus %d\n", svDeviceStatus);
    usart_print("5  svDeviceType %d\n", svDeviceType);
    usart_print("7  svCoinSw2 %d\n", svCoinSw2);
    usart_print("8  svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow);
    usart_print("9  svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh);
    usart_print("10 svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow);
    usart_print("11 svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh);
    usart_print("12 svCardDirection %d\n", svCardDirection);
    usart_print("13 svCoinPerPlay %d\n", svCoinPerPlay);
    usart_print("14 svCoinPerPlay2 %d\n", svCoinPerPlay2);
    usart_print("17 svTEpulse %d\n", svTEpulse);
}

//---------------------------------------------------------------------------------------------
static void cmd_set(int argc, char** argv)
{
	uint32_t id, value;
	if((Str2Dec32(argv[1], &id) == 0)){
		usart_print("id error :%d\n", id);
		return;
	}

	if(id != 2 && id != 3){
		if((Str2Dec32(argv[2], &value) == 0)){
			usart_print("value error\n");
			return;
		}
	}

	switch(id){
    	case  0: fskv_save_async(FSKV_EVT_COUNTER_C, value); usart_print("set svCounterC %d\n", svCounterC); break;
    	case  1: fskv_save_async(FSKV_EVT_COUNTER_D, value); usart_print("set svCounterD %d\n", svCounterD); break;
    	case  2: fskv_save_async(FSKV_EVT_URL_WXPAY, (uint32_t)argv[2]); usart_print("set svUrlWXPay %s\n", argv[2]); break;
    	case  3: fskv_save_async(FSKV_EVT_URL_OTA, (uint32_t)argv[2]); usart_print("set sxUrlUpdate %s\n", argv[2]); break;
    	case  4: fskv_save_async(FSKV_EVT_DEV_STATUS, value); usart_print("set svDeviceStatus %d\n", svDeviceStatus); break;
    	case  5: fskv_save_async(FSKV_EVT_DEV_TYPE, value); ; usart_print("set svDeviceType %d\n", svDeviceType); break;
    	case  7: fskv_save_async(FSKV_EVT_COINER_SW2, value); usart_print("set svCoinSw2 width %d\n", svCoinSw2); break;
    	case  8: fskv_save_async(FSKV_EVT_COIN_IN_LOW, value); usart_print("set svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow); break;
    	case  9: fskv_save_async(FSKV_EVT_COIN_IN_HIGH, value); usart_print("set svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh); break;
    	case 10: fskv_save_async(FSKV_EVT_PRZ_IN_LOW, value); usart_print("set svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow); break;
    	case 11: fskv_save_async(FSKV_EVT_COIN_IN_HIGH, value); usart_print("set svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh); break;
    	case 12: fskv_save_async(FSKV_EVT_DEV_DIR, value); usart_print("set svCardDirection %d\n", svCardDirection); break;
    	case 13: fskv_save_async(FSKV_EVT_COIN_BTN1, value); usart_print("set svCoinPerPlay %d\n", svCoinPerPlay); break;
    	case 14: fskv_save_async(FSKV_EVT_COIN_BTN2, value); usart_print("set svCoinPerPlay2 %d\n", svCoinPerPlay2); break;
    	case 17: fskv_save_async(FSKV_EVT_TE_PULSE, value); usart_print("set svTEpulse %d\n", svTEpulse); break;
	}
}

//---------------------------------------------------------------------------------------------
static void cmd_ota(int argc, char** argv)
{
	usart_print("Start OTA : %s\n", svUrlOta);
}

//---------------------------------------------------------------------------------------------
static void cmd_sys_debugcoin(int argc, char** argv)
{
	if(svDbgCoin == 0) svDbgCoin = 1;
	else svDbgCoin = 0;
	usart_print("Debug Coin Mode : %s\n", svDbgCoin ? "ON" : "OFF");
}

//---------------------------------------------------------------------------------------------
static void cmd_coin(int argc, char** argv)
{
	uint32_t count;

	if((Str2Dec32(argv[1], &count) == 0)){
		usart_print("coin count error :%d\n", count);
		return;
	}
	usart_print("coin emulate %d\n", count);
	gpio_outCoin(count);
}

//---------------------------------------------------------------------------------------------
static void cmd_ticket(int argc, char** argv)
{
	uint32_t count;

	if((Str2Dec32(argv[1], &count) == 0)){
		usart_print("ticket count error :%d\n", count);
		return;
	}
	usart_print("ticket emulate %d\n", count);
	gpio_outTicket(count);
}

//---------------------------------------------------------------------------------------------
static void cmd_test1(int argc, char** argv)
{
	usart_print("123\n");
}

//---------------------------------------------------------------------------------------------
static void cmd_test2(int argc, char** argv)
{
	usart_print("123\n");
}

//---------------------------------------------------------------------------------------------
/* COMMANDS LIST */
struct cli_command cli[] = {
	/* system */
	{"cls", 			"clear screen",						cmd_cls},
	{"help", 			"help",								cmd_help},
	{"sysinfo",			"os information",					cmd_sysinfo},
	{"tick",			"tick",								cmd_tick},
	{"halt",			"halt",								cmd_halt},
	{"reboot",			"reboot",							cmd_reboot},
	{"pwm",				"pwm [ch] [Hz] [Ratio] [Count]",	cmd_pwm},
	{"pin",             "pin [pin id] [value]",             cmd_pin},
	{"time",            "time",             				cmd_rtc},
	{"env",             "env",             					cmd_env},
	{"set",             "set [env id] [value]",             cmd_set},
	{"ota",             "ota",                              cmd_ota},

	{"dbg",             "dbg",              				cmd_sys_debugcoin},
	{"coin",            "coin [count]",    				    cmd_coin},
	{"ticket",          "ticket [count]",    				cmd_ticket},
	// {"prize",           "prize [count]",         			cmd_prize},
	{"t1",            "test1",        	    				cmd_test1},
	{"t2",            "test2",         						cmd_test2},
};
int32_t cli_num = sizeof(cli) / sizeof(cli[0]);
