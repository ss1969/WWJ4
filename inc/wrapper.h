#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#define MALLOC luat_heap_malloc
#define FREE luat_heap_free
#define DELAY luat_rtos_task_sleep
#define GPIO_PinState int

typedef unsigned long            uint32_t;
typedef unsigned short           uint16_t;
typedef unsigned char            uint8_t;
#define true                     1
#define false                    0



int uart_print(const char* format, ...);

#endif