/**
 * @file	kernel/arch/cpu/idt.h
 * @brief	x86_64 IDT header
 */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct idtr {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed)) idtr_t;

typedef struct idt {
	uint16_t base_low;
	uint16_t cs;
	uint8_t ist;
	uint8_t flags;
	uint16_t base_mid;
	uint32_t base_high;
	uint32_t reserved;
} __attribute__((packed)) idt_t;

typedef void (*interrupt_handler)();

extern interrupt_handler g_int_handlers[16];

extern void idt_load(idtr_t *idtr);

void idt_init();
void idt_set_descriptor(int entry, uint64_t base, uint8_t flags);

#endif /* IDT_H */
