#include <stdarg.h>
#include "wrapper.h"
#include "luat_uart.h"
#include "usart.h"

void system_halt_for_update(void)
{
	extern void cli_deinit(void);
	extern void uart_deinit(void);
	extern void gpio_deinit(void);
	extern void fskv_deinit(void);
	extern void boot_deinit(void);

	boot_deinit();
	cli_deinit();
	gpio_deinit();
	fskv_deinit();
	uart_deinit();
}

