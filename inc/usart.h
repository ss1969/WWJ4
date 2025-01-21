#ifndef _UART_H_
#define _UART_H_
#include "luat_rtos.h"
#include "ringbuffer.h"

#define UART_1 1
#define UART_2 2

typedef struct _UART_CONFIG{
    int id;
    int baud_rate;
    int data_bits;
    int stop_bits;
    int parity;
} UART_CONFIG;

static UART_CONFIG uart_configs[] = {
    {1, 115200, 8, 1, 0},
    {2, 115200, 8, 1, 0},
};

#define UART_DEBUG               UART_1
#define UART_RXBUF_SIZE          128
#define UART_RINGBUF_SIZE        1024

int uart_tx(int uart_id, const char* buffer, size_t buffersize);
int uart_getchar(char *ch);
int uart_print(const char* format, ...);
int uart_print_async(const char* format, ...);

#endif
