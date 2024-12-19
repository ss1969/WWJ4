#include "common_api.h"

extern void task_uart(void);
extern void task_console(void);
extern void task_gpio(void);
extern void task_fskv(void);


INIT_HW_EXPORT(task_uart, "1");   // usart first
INIT_HW_EXPORT(task_fskv, "5");   // fskv first, for some init values

INIT_TASK_EXPORT(task_gpio,"2");
INIT_TASK_EXPORT(task_console, "4");
