
#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_uart.h"
#include "luat_mem.h"

#include "ringbuffer.h"

#include "usart.h"

typedef struct _UART_MSG
{
    int uart_id;
    int buffer_length;
    char *buffer;
}UART_MSG;

static luat_rtos_task_handle task_uart_handle;

#define UART_COUNT               (sizeof(uart_configs) / sizeof(uart_config_t))

static char rx_buffer[UART_COUNT][UART_RINGBUF_SIZE];  // 每个 UART 1KB 接收缓冲区
static luat_rtos_semaphore_t sema[UART_COUNT];
static RINGBUFFER_T rbuf[UART_COUNT];
static int uart_dbg_rbuf_id;

static int get_uart_config_index(int id) {
    for (int i = 0; i < UART_COUNT; i++) {
        if (uart_configs[i].id == id) {
            return i; // 找到对应的索引，返回
        }
    }
    return -1; // 如果没有找到，返回 -1
}

static void luat_uart_recv_cb(int uart_id, uint32_t data_len){
    uint8_t rx_buffer[UART_RXBUF_SIZE];
    int len = luat_uart_read(uart_id, rx_buffer, sizeof(rx_buffer));
    if (len > 0) {
        int id = get_uart_config_index(uart_id);
        if (id == -1)
            return;
        RingBufWrite(&rbuf[id], rx_buffer, len);
    }
}

static void uart_init() {
	LUAT_DEBUG_PRINT("uart_init start");

    for (int i = 0; i < UART_COUNT; i++) {
        luat_uart_t uart = {
            .id = uart_configs[i].id,
            .baud_rate = uart_configs[i].baud_rate,
            .data_bits = uart_configs[i].data_bits,
            .stop_bits = uart_configs[i].stop_bits,
            .parity    = uart_configs[i].parity
        };
        RingBufInit(&rbuf[i], rx_buffer[i], sizeof(rx_buffer[0]), 0);
        LUAT_DEBUG_PRINT("[UART] setup uart #%d result %d", uart_configs[i].id, luat_uart_setup(&uart));
        LUAT_DEBUG_PRINT("[UART] ctrl result %d", luat_uart_ctrl(uart_configs[i].id, LUAT_UART_SET_RECV_CALLBACK, luat_uart_recv_cb));
    }

    uart_dbg_rbuf_id = get_uart_config_index(UART_DEBUG);
    if (uart_dbg_rbuf_id == -1)
	    LUAT_DEBUG_PRINT("uart UART_DEBUG set ERROR!!");

	LUAT_DEBUG_PRINT("uart_init end");
}

static void uart_deinit() {
    for (int i = 0; i < UART_COUNT; i++) {
        luat_uart_close(uart_configs[i].id);
        luat_rtos_semaphore_delete(sema[i]);
    }
}

int uart_tx(int uart_id, const char* buffer, size_t buffersize)
{
    int id = get_uart_config_index(uart_id);
    if (id == -1)
        return -1;
    int result = luat_uart_write(uart_id, buffer, buffersize);
    return result;
}

int uart_getchar(char *ch)
{
	return RingBufRead1Ch(&rbuf[uart_dbg_rbuf_id], ch);
}


int uart_print(const char* format, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, format);
    int length = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (length > 0) {
        luat_uart_write(UART_DEBUG, buffer, length);
    }

    return length;
}

int uart_print_async(const char* format, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, format);
    int length = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (length > 0) {
        UART_MSG *data;
        data = (UART_MSG *)LUAT_MEM_MALLOC(sizeof(UART_MSG));
        data->uart_id = UART_DEBUG;
        data->buffer = (char *)LUAT_MEM_MALLOC(length);
        memcpy(data->buffer, buffer, length);
        data->buffer_length = length;
        int ret = luat_rtos_message_send(task_uart_handle, 0, data);
    }

    return length;
}

static void uart_main_routine(void *param)
{
    int ret;
	uint32_t message_id = 0;
    UART_MSG *data = NULL;

	while(true)
	{
		ret = luat_rtos_message_recv(task_uart_handle, &message_id, (void**)&data, LUAT_WAIT_FOREVER);
		if(ret){
			LUAT_DEBUG_PRINT("luat_rtos_message_recv ERROR %d", message_id);
			continue;
		}
        luat_uart_write(data->uart_id, data->buffer, data->buffer_length);
        LUAT_MEM_FREE(data->buffer);
        LUAT_MEM_FREE(data);
        data = NULL;
	}
}

void task_uart(void)
{
 	/*
		出现异常后默认为死机重启
		demo这里设置为 LUAT_DEBUG_FAULT_HANG_RESET 出现异常后尝试上传死机信息给PC工具，上传成功或者超时后重启
		如果为了方便调试，可以设置为 LUAT_DEBUG_FAULT_HANG ，出现异常后死机不重启
		但量产出货一定要设置为出现异常重启！！！！！！！！！
	*/
    luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_HANG_RESET);

    uart_init();  // 初始化 UART
    luat_rtos_task_create(&task_uart_handle, 4*1024, 50, "task_uart", uart_main_routine, NULL, 0);
}

