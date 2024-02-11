#include <cpu/idt.h>
#include <aurix.h>
#include <stddef.h>

#define IDT_ENTRIES 256

idt_t idt[IDT_ENTRIES];
interrupt_handler g_int_handlers[16];

extern uint64_t isr_tbl[];

void idt_init()
{
	for (size_t i = 0; i < IDT_ENTRIES; i++) {
		idt_set_descriptor(i, isr_tbl[i], 0x8E);
	}
	idt_set_descriptor(255, isr_tbl[255], 0x8F);

	for (size_t i = 0; i < 16; i++) {
		g_int_handlers[i] = NULL;
	}

	idtr_t idtr;
	idtr.size = sizeof(idt) - 1;
	idtr.offset = (uint64_t)&idt;

	idt_load(&idtr);

	klog("loaded at 0x%llx (size: %d bytes)", &idt, sizeof(idt));
}

void idt_set_descriptor(int entry, uint64_t base, uint8_t flags)
{
	idt[entry].base_low = base & 0xFFFF;
	idt[entry].cs = 0x08; /* Kernel Code */
	idt[entry].ist = 0;
	idt[entry].flags = flags;
	idt[entry].base_mid = (base >> 16) & 0xFFFF;
	idt[entry].base_high = (base >> 32);
	idt[entry].reserved = 0;
}