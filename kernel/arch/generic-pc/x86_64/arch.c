/**
 * @file	kernel/arch/arch.h
 * @brief	Architecture initialization
 */

#include <arch/arch.h>
#include <cpu/gdt.h>

/**
 * @brief	Initializes architecture-specific functionality and devices
 * 
 * This function is pretty straightforward:
 *     - Step one:   Initialize CPU (GDT, IDT, ...)
 *     - Step two:   Set up internal device drivers (PIC, Framebuffer, ...)
 *     - Step three: ???
 *     - Step four:  Profit.
 */
void arch_init(void)
{
	gdt_init();
	// idt_init();
}
