#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_mem.h"
#include "usart.h"

#define LOG_TO_LUAT
#define LOG_TO_UART

#define nameof(var) #var

#define MALLOC        luat_heap_malloc
#define REALLOC       luat_heap_realloc
#define FREE          luat_heap_free
#define DELAY         luat_rtos_task_sleep
#define GPIO_PinState int
#define SYSTICK       soc_get_poweron_time_tick

void LOG(const char *format, ...);
void LOG_HEX(char *prefix, char *hex, size_t len);

typedef unsigned long  uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
#define true  1
#define false 0

#define TICK_PER_MS 26000
#define TICK2MS(x)  ((x) / TICK_PER_MS)
#define MS2TICK(x)  ((x) * TICK_PER_MS)

#endif