#include <string.h>
#include <stdio.h>
#include "common_api.h"
#include "luat_mem.h"
#include "luat_pwm.h"
#include "luat_rtc.h"

#include "wrapper.h"
#include "vt_ctrl.h"
#include "str2x.h"
#include "sysvars.h"
#include "usart.h"

#include "cli.h"

//---------------------------------------------------------------------------------------------
void cmd_cls(int argc, char** argv)
{
	CON_VT_Erase_Screen(1);
	CON_VT_Set_Cursor_to_XY(0, 0);
}

//---------------------------------------------------------------------------------------------
void cmd_help(int argc, char** argv)
{
	uart_print("Command         Function \n");
	uart_print("---------------------------------------------------------------------\n");
	CliPrintCmdList();
}

//---------------------------------------------------------------------------------------------
void cmd_tick(int argc, char** argv)
{
	uart_print("soc_get_poweron_time_ms %llu\n",soc_get_poweron_time_ms());
	// uart_print("soc_get_poweron_time_tick %llu\n",soc_get_poweron_time_tick());
	// uart_print("soc_get_utc %u\n",soc_get_utc());
	// uart_print("soc_get_utc_ms %llu\n",soc_get_utc_ms());
}

//---------------------------------------------------------------------------------------------
void cmd_pwm(int argc, char** argv)
{
	uint32_t channel, freq, ratio, count;

	if((Str2Dec32(argv[1], &channel) == 0)){
		uart_print("channel error :%d\n", channel);
		return;
	}
	if((Str2Dec32(argv[2], &freq) == 0)){
		uart_print("freq error\n");
		return;
	}
	if((Str2Dec32(argv[3], &ratio) == 0)){
		uart_print("ratio error :%d\n", ratio);
		return;
	}
	if((Str2Dec32(argv[4], &count) == 0)){
		uart_print("count error\n");
		return;
	}
	if(channel != 0 && channel != 1 && channel != 2 && channel != 4){
		uart_print("ratio error :%d\n", ratio);
		return;
	}
	if(ratio > 1000){
		uart_print("ratio error :%d\n", ratio);
		return;
	}

	int param = 123;
	// uart_print("PWM Set CB %d\n", luat_pwm_set_callback(channel, pwm_callback, &param));
	uart_print("PWM Start %d\n", luat_pwm_open(channel, freq, ratio, count));
}

//---------------------------------------------------------------------------------------------
void cmd_sysinfo(int argc, char** argv)
{
	char* pcWriteBuffer = (char*)MALLOC(1024);
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
void cmd_rtc(int argc, char** argv)
{
	struct tm tblock = {0};
    luat_rtc_get(&tblock);
    uart_print("%04d/%02d/%02d/ %02d:%02d:%02d %02d\n",
			tblock.tm_year+1900,
			tblock.tm_mon+1,
			tblock.tm_mday,
			tblock.tm_hour,
			tblock.tm_min,
			tblock.tm_sec,
			tblock.tm_wday);
}

//---------------------------------------------------------------------------------------------
void cmd_stat(int argc, char** argv)
{
    uart_print("svCounterC %d\n", svCounterC);
    uart_print("svCounterD %d\n", svCounterD);
    uart_print("svUrlWXPay %s\n", svUrlWXPay);
    uart_print("svDeviceStatus %d\n", svDeviceStatus);
    uart_print("svDeviceType %d\n", svDeviceType);
    uart_print("svCoinPulseWidth %d\n", svCoinPulseWidth);
    uart_print("svCoinPulseWidthInLow %d\n", svCoinPulseWidthInLow);
    uart_print("svCoinPulseWidthInHigh %d\n", svCoinPulseWidthInHigh);
    uart_print("svPrizePulseWidthInLow %d\n", svPrizePulseWidthInLow);
    uart_print("svPrizePulseWidthInHigh %d\n", svPrizePulseWidthInHigh);
    uart_print("svCardDirection %d\n", svCardDirection);
    uart_print("svCoinPerPlay %d\n", svCoinPerPlay);
    uart_print("svCoinPerPlay2 %d\n", svCoinPerPlay2);
}

//---------------------------------------------------------------------------------------------
void cmd_sys_debugcoin(int argc, char** argv)
{
	if(svDbgCoin == 0) svDbgCoin = 1;
	else svDbgCoin = 0;
	uart_print("Debug Coin Mode : %s\r\n", svDbgCoin ? "ON" : "OFF");
}

//---------------------------------------------------------------------------------------------
void cmd_coin(int argc, char** argv)
{
	uint32_t count;

	if((Str2Dec32(argv[1], &count) == 0)){
		uart_print("coin count error :%d\n", count);
		return;
	}
	uart_print("coin emulate %d\n", count);
	svCoinInsert += count * 2;
}

//---------------------------------------------------------------------------------------------
void cmd_test1(int argc, char** argv)
{
	uart_print("123\n");
}
void cmd_test2(int argc, char** argv)
{
	uart_print("123\n");
}

//---------------------------------------------------------------------------------------------
/* COMMANDS LIST */
struct cli_command cli[] = {
	/* system */
	{"cls", 			"clear screen",		cmd_cls},
	{"help", 			"help",				cmd_help},
	{"sysinfo",			"os information",	cmd_sysinfo},
	{"tick",			"tick",				cmd_tick},
	{"pwm",				"pwm [ch] [Hz] [Ratio] [Count]",				cmd_pwm},
	{"time",            "time",             cmd_rtc},
	{"stat",            "stat",             cmd_stat},
	{"dbg",             "dbg",              cmd_sys_debugcoin},
	{"coin",            "coint [count]",         cmd_coin},
	// {"prize",           "prize [count]",         cmd_prize},
	{"t1",            "test1",         cmd_test1},
	{"t2",            "test2",         cmd_test2},


};
int32_t cli_num = sizeof(cli) / sizeof(cli[0]);
