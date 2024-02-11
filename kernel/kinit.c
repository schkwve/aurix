#include <boot/boot.h>
#include <arch/arch.h>
#include <dd/uart/uart.h>

void _start(void)
{
	uart_init();
	arch_init();

	for (;;)
		;
}