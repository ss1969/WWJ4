#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"
#include "luat_pm.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_gpio.h"
#include "wdt.h"

#include "sysvars.h"
#include "wgpio.h"
#include "usart.h"


static luat_rtos_task_handle task_bootup_handle;

extern const char* luat_mcu_unique_id(size_t* t);
extern void task_uart(void);
extern void task_console(void);
extern void task_gpio(void);
extern void task_fskv(void);
extern void task_bootup(void);
extern void task_mobile(void);


static void boot_main_routine(void *param)
{
    while (1)
    {
        gpio_toggle(PIN_LED_D1);
        luat_rtos_task_sleep(1000);
    }
    // while (1)
    // {
    //     luat_rtos_task_sleep(5 * 1000);
    //     WDT_kick();
    // }
}

/*
0   powerkey 或者上电开机
1   充电或者 AT 指今下载完成后开机
2   闹钟开机
3   软件重启
4   未知原因
5   RESET 键重启
6   异常重启
7   工具控制重启
8   内部看门狗重启
9   外部重启
10  充电开机
*/
void task_bootup(void)
{
 	/*
		出现异常后默认为死机重启
		demo这里设置为 LUAT_DEBUG_FAULT_HANG_RESET 出现异常后尝试上传死机信息给PC工具，上传成功或者超时后重启
		如果为了方便调试，可以设置为 LUAT_DEBUG_FAULT_HANG ，出现异常后死机不重启
		但量产出货一定要设置为出现异常重启！！！！！！！！！
	*/
    luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_HANG);

    task_uart();
    task_fskv();
    task_gpio();
    luat_rtos_task_create(&task_bootup_handle, 2*1024, 1, "task_boot", boot_main_routine, NULL, 0);

    usart_print("BUILD %s %s\n", __DATE__, __TIME__);
    usart_print("Power on reason: %d\n", luat_pm_get_poweron_reason());
    size_t len;
    char *id = luat_mcu_unique_id(&len);
    usart_print("System ID :");
    for(int i = 0; i<len; i++){
        svSystemID[i] = id[i];
        usart_print("%02x", id[i]);
    }
    usart_print("\n");

    task_console();
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

