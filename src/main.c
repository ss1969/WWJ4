#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"

extern void task_bootup(void);
INIT_TASK_EXPORT(task_bootup, "0");

