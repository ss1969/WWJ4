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

luat_rtos_task_handle task_fskv_handle;

// return 1 success
static int ef_get_num(const char* key, uint32_t *data)
{
	char value[16] = {0};
	int ret = luat_fskv_get(key, value, sizeof(value));
	if(ret < 0) return ret;
	return Str2Hex32(value, data);
}

static int ef_get_num8(const char* key, uint8_t *data)
{
	char value[8] = {0};
	int ret = luat_fskv_get(key, value, sizeof(value));
	if(ret < 0) return ret;
	uint32_t v;
	ret = Str2Hex32(value, &v);
	*data = (uint8_t)(v & 0xFF);
	return ret;
}

// return >0 success
static int ef_set_num(const char* key, uint32_t data)
{
	char value[16] = {0};
	int len = sprintf(value, "%x", data);
	return luat_fskv_set(key, value, len);
}

static int ef_set_num8(const char* key, uint8_t data)
{
	char value[8] = {0};
	int len = sprintf(value, "%x", data);
	return luat_fskv_set(key, value, len);
}

static int ef_get_str(const char* key, char* data)
{
	return luat_fskv_get(key, data, sizeof(data));
}

static int ef_set_str(const char* key, char *data)
{
	return luat_fskv_set(key, data, strlen(data));
}

/* read settings  */
static void fskv_read_data(void)
{
	LUAT_DEBUG_PRINT("fskv_read_data");
	/* read counters */
	ef_get_num("c", &svCounterC);
	ef_get_num("d", &svCounterD);

	/* read settings */
	ef_get_str("wxurl", svUrlWXPay);
	ef_get_num8("dstatus", &svDeviceStatus);
	ef_get_num8("dtype", &svDeviceType);
	ef_get_num8("pulsewidth", &svCoinPulseWidth);
	ef_get_num8("pulsec1", &svCoinPulseWidthInLow);
	ef_get_num8("pulsec2", &svCoinPulseWidthInHigh);
	ef_get_num8("pulsec3", &svPrizePulseWidthInLow);
	ef_get_num8("pulsec4", &svPrizePulseWidthInHigh);
	ef_get_num8("dir", &svCardDirection);
	ef_get_num8("coinbtn1", &svCoinPerPlay);
	ef_get_num8("coinbtn2", &svCoinPerPlay2);
}

/* reset counters */
static void fskv_init_data(void)
{
	LUAT_DEBUG_PRINT("fskv_init_data");
	luat_fskv_clear();

	/* set counters */
	svCounterC = svCounterD = 0;
	ef_set_num("c", svCounterC);
	ef_set_num("d", svCounterD);

	/* set settings */
	strcpy(svUrlWXPay, "");
	svDeviceStatus = 1;
	svDeviceType = 1;
	svCoinPulseWidth = 40;
	svCoinPulseWidthInLow = 15;
	svCoinPulseWidthInHigh = 105;
	svPrizePulseWidthInLow = 15;
	svPrizePulseWidthInHigh = 105;
	svCardDirection = 0;
	svCoinPerPlay = 1;
	svCoinPerPlay2 = 2;
	ef_set_str("wxurl", svUrlWXPay);
	ef_set_num8("dstatus", svDeviceStatus);
	ef_set_num8("dtype", svDeviceType);
	ef_set_num8("pulsewidth", svCoinPulseWidth);
	ef_set_num8("pulsec1", svCoinPulseWidthInLow);
	ef_set_num8("pulsec2", svCoinPulseWidthInHigh);
	ef_set_num8("pulsec3", svPrizePulseWidthInLow);
	ef_set_num8("pulsec4", svPrizePulseWidthInHigh);
	ef_set_num8("dir", svCardDirection);
	ef_set_num8("coinbtn1", svCoinPerPlay);
	ef_set_num8("coinbtn2", svCoinPerPlay2);
}

void fskv_init(void)
{
	LUAT_DEBUG_PRINT("fskv_init start");
	/*
		出现异常后默认为死机重启
		demo这里设置为LUAT_DEBUG_FAULT_HANG_RESET出现异常后尝试上传死机信息给PC工具，上传成功或者超时后重启
		如果为了方便调试，可以设置为LUAT_DEBUG_FAULT_HANG，出现异常后死机不重启
		但量产出货一定要设置为出现异常重启！！！！！！！！！
	*/
	luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_HANG_RESET);
	luat_fskv_init();

	size_t using_sz, max_sz, kv_count;
	luat_fskv_stat(&using_sz, &max_sz, &kv_count);
	LUAT_DEBUG_PRINT("luat_fskv_stat using %d, max %d, count %d", using_sz, max_sz, kv_count);
	if(kv_count == 0){
		fskv_init_data();
	}
	fskv_read_data();

	LUAT_DEBUG_PRINT("fskv_init end");
}

static void fskv_main_rountine(void *param)
{
	int ret;
	luat_event_t event;
	while(true)
	{
		ret = luat_rtos_event_recv(task_fskv_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);

		if(ret){
			LUAT_DEBUG_PRINT("luat_rtos_event_recv ERROR %d", event.id);
			continue;
		}

		int p1 = event.param1;
		LUAT_DEBUG_PRINT("luat_rtos_event_recv id:%d p1:%d", event.id, p1);
		switch(event.id)
		{
			case FSKV_EVT_COUNTER_C:
				ef_set_num("c", svCounterC);
				break;
			case FSKV_EVT_COUNTER_D:
				ef_set_num("d", svCounterD);
				break;
			case FSKV_EVT_COINER_PULSE:
				svCoinPulseWidth = p1;
				ef_set_num8("pulsewidth", svCoinPulseWidth);
				break;
			case FSKV_EVT_COIN_IN_LOW:
				svCoinPulseWidthInLow = p1;
				ef_set_num8("pulsec1", svCoinPulseWidthInLow);
				break;
			case FSKV_EVT_COIN_IN_HIGH:
				svCoinPulseWidthInHigh = p1;
				ef_set_num8("pulsec2", svCoinPulseWidthInHigh);
				break;
			case FSKV_EVT_PRZ_IN_LOW:
				svPrizePulseWidthInLow = p1;
				ef_set_num8("pulsec3", svPrizePulseWidthInLow);
				break;
			case FSKV_EVT_PRZ_IN_HIGH:
				svPrizePulseWidthInHigh = p1;
				ef_set_num8("pulsec4", svPrizePulseWidthInHigh);
				break;
			case FSKV_EVT_DEV_STATUS:
				svDeviceStatus = p1;
				ef_set_num8("dstatus", svDeviceStatus);
				break;
			case FSKV_EVT_DEV_TYPE:
				svDeviceType = p1;
				ef_set_num8("dtype", svDeviceType);
				break;
			case FSKV_EVT_DEV_DIR:
				svCardDirection = p1;
				ef_set_num8("pulsewidth", svCardDirection);
				break;
			case FSKV_EVT_WX_URL:
				strncpy(svUrlWXPay, (char *)p1, sizeof(svUrlWXPay));
				ef_set_str("wxurl", svUrlWXPay);
				break;
			case FSKV_EVT_COIN_BTN1:
				svCoinPerPlay = p1;
				ef_set_num8("coinbtn1", svCoinPerPlay);
				break;
			case FSKV_EVT_COIN_BTN2:
				svCoinPerPlay2 = p1;
				ef_set_num8("coinbtn2", svCoinPerPlay2);
				break;
			default:
				break;
		}
	}
}

void fskv_save_async(FSKV_ITEM item, uint32_t p1)
{
	luat_rtos_event_send(task_fskv_handle, item, p1, 0, 0, 1000);
}

void task_fskv(void)
{
	int ret;
	fskv_init();

	luat_rtos_task_create(&task_fskv_handle, 4*1024, 50, "task_fskv", fskv_main_rountine, NULL, 0);
}
