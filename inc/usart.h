#ifndef _UART_H_
#define _UART_H_
#include "luat_rtos.h"
#include "ringbuffer.h"

#define UART_1 1
#define UART_2 3
#define UART_3 2

typedef struct {
    int id;
    int baud_rate;
    int data_bits;
    int stop_bits;
    int parity;
} uart_config_t;

static uart_config_t uart_configs[] = {
    {1, 115200, 8, 1, 0},
    {2, 115200, 8, 1, 0},
    {3, 115200, 8, 1, 0},
};

#define UART_DEBUG               UART_1
#define UART_RXBUF_SIZE          128
#define UART_RINGBUF_SIZE        1024

int uart_tx(int uart_id, const char* buffer, size_t buffersize);
int GETC(char *ch);
int uart_print(const char* format, ...);
int uart_print_async(const char* format, ...);

#endif
