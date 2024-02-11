#include <dd/uart/uart.h>
#include <aurix.h>

void uart_init()
{
	outb(COM1 + 1, 0x00);

	// Set divisor to 1
	// -> 115200 baud
	outb(COM1 + 3, 0x80);
	outb(COM1, 0x01);
	outb(COM1 + 1, 0x00);

	// 8 bits, no parity, one stop bit
	outb(COM1 + 3, 0x03);
	outb(COM1 + 2, 0xC7);
	outb(COM1 + 4, 0x0B);
	outb(COM1 + 4, 0x0F);
}

void uart_write(char *str)
{
	while (*str) {
		while ((inb(COM1 + 5) & 0x20) == 0)
			;
		outb(COM1, *str++);
	}
}