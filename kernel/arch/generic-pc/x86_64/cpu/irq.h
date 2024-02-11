#ifndef IRQ_H
#define IRQ_H

#include <cpu/idt.h>

void irq_register(uint8_t irq, interrupt_handler handler);
void irq_deregister(uint8_t irq);

#endif /* IRQ_H */
