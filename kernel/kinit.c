#include <boot/boot.h>
#include <arch/arch.h>

void _start(void)
{
	arch_init();

	for (;;)
		;
}