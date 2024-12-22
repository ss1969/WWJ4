#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"
#include "luat_pm.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_gpio.h"
#include "wdt.h"

#include "wgpio.h"
#include "usart.h"


static luat_rtos_task_handle task_bootup_handle;

extern const char* luat_mcu_unique_id(size_t* t);

static void boot_main_routine(void *param)
{
    while (1)
    {
        luat_rtos_task_sleep(5 * 1000);
        WDT_kick();
    }
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
    LUAT_DEBUG_PRINT("Power on reason : %d", luat_pm_get_poweron_reason());
    usart_print("Power on reason : %d", luat_pm_get_poweron_reason());

    size_t len;
    char *id = luat_mcu_unique_id(&len);
    usart_print("System ID :");
    for(int i = 0; i<len; i++){
        usart_print("%02x", id[i]);
    }
    usart_print("\n");

    luat_rtos_task_create(&task_bootup_handle, 2*1024, 1, "task_boot", boot_main_routine, NULL, 0);
}

void boot_deinit(void)
{
    luat_rtos_task_suspend(task_bootup_handle);
	luat_rtos_task_delete(task_bootup_handle);
}