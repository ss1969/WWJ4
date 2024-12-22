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
	usart_print("soc_get_poweron_time_ms %llu\n",soc_get_poweron_time_ms());
	// usart_print("soc_get_poweron_time_tick %llu\n",soc_get_poweron_time_tick());
	// usart_print("soc_get_utc %u\n",soc_get_utc());
	// usart_print("soc_get_utc_ms %llu\n",soc_get_utc_ms());
}

//---------------------------------------------------------------------------------------------
static void cmd_halt(int argc, char** argv)
{
	usart_print("system_halt_for_update()");
	system_halt_for_update();
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
	char* pcWriteBuffer = (char*)MALLOC(1024);
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
	usart_print("PIN PRIZE_IN : %d\n", luat_gpio_get(PIN_PRZ_IN));

    usart_print("0  svCounterC %d\n", svCounterC);
    usart_print("1  svCounterD %d\n", svCounterD);
    usart_print("2  svUrlWXPay %s\n", svUrlWXPay);
    usart_print("3  svDeviceStatus %d\n", svDeviceStatus);
    usart_print("4  svDeviceType %d\n", svDeviceType);
    usart_print("5  svCoinNormal %d\n", svCoinNormal);
    usart_print("6  svPrizeNormal %d\n", svPrizeNormal);
    usart_print("7  svCoinPulseWidth %d\n", svCoinPulseWidth);
    usart_print("8  svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow);
    usart_print("9  svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh);
    usart_print("10 svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow);
    usart_print("11 svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh);
    usart_print("12 svCardDirection %d\n", svCardDirection);
    usart_print("13 svCoinPerPlay %d\n", svCoinPerPlay);
    usart_print("14 svCoinPerPlay2 %d\n", svCoinPerPlay2);
    usart_print("15 svTEsw1 %d\n", svTEsw1);
    usart_print("16 svTEsw2 %d\n", svTEsw2);
    usart_print("17 svTEticketCount %d\n", svTEticketCount);
    usart_print("18 svTEpulse %d\n", svTEpulse);
}

//---------------------------------------------------------------------------------------------
static void cmd_set(int argc, char** argv)
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

	switch(id){
    	case  0: svCounterC = value; usart_print("set svCounterC %d\n", svCounterC); break;
    	case  1: svCounterD = value; usart_print("set svCounterD %d\n", svCounterD); break;
    	// case  2: xxxx = value; usart_print("set svUrlWXPay %s\n", svUrlWXPay); break;
    	case  3: svDeviceStatus = value; usart_print("set svDeviceStatus %d\n", svDeviceStatus); break;
    	case  4: svDeviceType = value; usart_print("set svDeviceType %d\n", svDeviceType); break;
    	case  5: svCoinNormal = value; usart_print("set svCoinNormal %d\n", svCoinNormal); break;
    	case  6: svPrizeNormal = value; usart_print("set svPrizeNormal %d\n", svPrizeNormal); break;
    	case  7: svCoinPulseWidth = value; usart_print("set svCoinPulseWidth %d\n", svCoinPulseWidth); break;
    	case  8: svCoinPulseWidthInLow = value; usart_print("set svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow); break;
    	case  9: svCoinPulseWidthInHigh = value; usart_print("set svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh); break;
    	case 10: svPrizePulseWidthInLow = value; usart_print("set svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow); break;
    	case 11: svPrizePulseWidthInHigh = value; usart_print("set svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh); break;
    	case 12: svCardDirection = value; usart_print("set svCardDirection %d\n", svCardDirection); break;
    	case 13: svCoinPerPlay = value; usart_print("set svCoinPerPlay %d\n", svCoinPerPlay); break;
    	case 14: svCoinPerPlay2 = value; usart_print("set svCoinPerPlay2 %d\n", svCoinPerPlay2); break;
    	case 15: svTEsw1 = value; usart_print("set svTEsw1 %d\n", svTEsw1); break;
    	case 16: svTEsw2 = value; usart_print("set svTEsw2 %d\n", svTEsw2); break;
    	case 17: svTEticketCount = value; usart_print("set svTEticketCount %d\n", svTEticketCount); break;
    	case 18: svTEpulse = value; usart_print("set svTEpulse %d\n", svTEpulse); break;
	}
}

//---------------------------------------------------------------------------------------------
static void cmd_sys_debugcoin(int argc, char** argv)
{
	if(svDbgCoin == 0) svDbgCoin = 1;
	else svDbgCoin = 0;
	usart_print("Debug Coin Mode : %s\r\n", svDbgCoin ? "ON" : "OFF");
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
	svCoinInsert += count * 2;
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
	{"cls", 			"clear screen",		cmd_cls},
	{"help", 			"help",				cmd_help},
	{"sysinfo",			"os information",	cmd_sysinfo},
	{"tick",			"tick",				cmd_tick},
	{"halt",			"halt",				cmd_halt},
	{"pwm",				"pwm [ch] [Hz] [Ratio] [Count]",				cmd_pwm},
	{"pin",             "pin [pin id] [value]",             cmd_pin},
	{"time",            "time",             cmd_rtc},
	{"env",              "env",             cmd_env},
	{"set",              "set [env id] [value]",             cmd_set},

	{"dbg",             "dbg",              cmd_sys_debugcoin},
	{"coin",            "coint [count]",    cmd_coin},
	// {"prize",           "prize [count]",         cmd_prize},
	{"t1",            "test1",        	    cmd_test1},
	{"t2",            "test2",         		cmd_test2},


};
int32_t cli_num = sizeof(cli) / sizeof(cli[0]);
