#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"
#include "luat_pm.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_gpio.h"
#include "luat_mobile.h"
#include "wdt.h"

#include "sysvars.h"
#include "wgpio.h"
#include "usart.h"

static luat_rtos_task_handle task_bootup_handle;

extern void uart_taskinit(void);
extern void cli_taskinit(void);
extern void gpio_taskinit(void);
extern void fskv_taskinit(void);
extern void mobile_taskinit(void);
extern void mqtt_taskinit(void);

static void boot_main_routine(void *param)
{
    while (1)
    {
        gpio_toggle(PIN_LED_D0);
        luat_rtos_task_sleep(1000);
    }
    // while (1)
    // {
    //     luat_rtos_task_sleep(5 * 1000);
    //     WDT_kick();
    // }
}

void getSystemID(void)
{
    extern const char* luat_mcu_unique_id(size_t* t);
    size_t len;
    char *id = luat_mcu_unique_id(&len);
    for(int i = 0; i<len; i++){
        sprintf(svSystemID + i * 2, "%02x", id[i]);
    }

    luat_mobile_get_imei(0, svIMEI, sizeof(svIMEI));
    LUAT_DEBUG_PRINT("IMEI: %s", svIMEI);
}

void task_bootup(void)
{
 	/*
		出现异常后默认为死机重启
		demo这里设置为 LUAT_DEBUG_FAULT_HANG_RESET 出现异常后尝试上传死机信息给PC工具，上传成功或者超时后重启
		如果为了方便调试，可以设置为 LUAT_DEBUG_FAULT_HANG ，出现异常后死机不重启
		但量产出货一定要设置为出现异常重启！！！！！！！！！
	*/
    luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_RESET);

    getSystemID();
    uart_taskinit();
    fskv_taskinit();
    gpio_taskinit();
    mobile_taskinit();
    mqtt_taskinit();

    luat_rtos_task_create(&task_bootup_handle, 2*1024, 1, "task_boot", boot_main_routine, NULL, 0);

    uart_print("BUILD %s %s\n", __DATE__, __TIME__);
	uart_print("Sys mode %d\n", svDeviceType);
    uart_print("System ID :");
    for(int i = 0; i<strlen(svSystemID); i++){
        uart_print("%c", svSystemID[i]);
    }
    uart_print("\n");
    uart_print("IMEI :");
    for(int i = 0; i<strlen(svIMEI); i++){
        uart_print("%c", svIMEI[i]);
    }
    uart_print("\n");
    uart_print("ICCID :");
    for(int i = 0; i<strlen(svICCID); i++){
        uart_print("%c", svICCID[i]);
    }
    uart_print("\n");

    cli_taskinit();
}

void boot_deinit(void)
{
    luat_rtos_task_suspend(task_bootup_handle);
	luat_rtos_task_delete(task_bootup_handle);
}

void system_halt_for_update(void)
{
	extern void cli_deinit(void);
	extern void uart_deinit(void);
	extern void gpio_deinit(void);
	extern void fskv_deinit(void);

	int step = 1;
	LUAT_DEBUG_PRINT("HALT STEP %d", step++);
	boot_deinit();
	LUAT_DEBUG_PRINT("HALT STEP %d", step++);
	gpio_deinit();
	LUAT_DEBUG_PRINT("HALT STEP %d", step++);
	fskv_deinit();
	LUAT_DEBUG_PRINT("HALT STEP %d", step++);
	uart_deinit();
	LUAT_DEBUG_PRINT("HALT STEP %d", step++);
	cli_deinit();
	LUAT_DEBUG_PRINT("HALT STEP %d", step++);
}


INIT_TASK_EXPORT(task_bootup, "0");

