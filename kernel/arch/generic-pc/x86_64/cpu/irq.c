#include <cpu/idt.h>
#include <cpu/irq.h>

#include <aurix.h>

#include <stddef.h>

void irq_register(uint8_t irq, interrupt_handler handler)
{
	g_int_handlers[irq] = handler;
	klog("registered handler for irq %i", irq);
}

void irq_deregister(uint8_t irq)
{
	g_int_handlers[irq] = NULL;
	klog("deregistered handler for irq %i", irq);
}