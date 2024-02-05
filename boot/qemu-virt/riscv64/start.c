#include <stdint.h>

//TODO: move this to config.h
#define NCPU 4 // 4 harts max

__attribute__((aligned(16))) char stack0[4096 * NCPU];

unsigned char *uart0 = (unsigned char *)0x10000000;
unsigned int *syscon = (unsigned int *)0x100000;

void _start(void)
{
	//write hello world to UART
	*uart0 = 'H';
	*uart0 = 'e';
	*uart0 = 'l';
	*uart0 = 'l';
	*uart0 = 'o';
	*uart0 = ' ';
	*uart0 = 'W';
	*uart0 = 'o';
	*uart0 = 'r';
	*uart0 = 'l';
	*uart0 = 'd';
	*uart0 = '\r';
	*uart0 = '\n';

	while (1)
		;

	// power off since there is nothing to do yet
	*syscon = 0x5555;
}