#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"

extern void task_uart(void);
extern void task_console(void);
extern void task_gpio(void);
extern void task_fskv(void);
extern void task_bootup(void);
extern void task_mobile(void);

INIT_TASK_EXPORT(task_uart, "0");   // usart first
INIT_TASK_EXPORT(task_fskv, "1");   // fskv , for some init values
INIT_TASK_EXPORT(task_gpio, "2");
INIT_TASK_EXPORT(task_mobile, "3");
INIT_TASK_EXPORT(task_bootup, "4");
INIT_TASK_EXPORT(task_console, "5");

