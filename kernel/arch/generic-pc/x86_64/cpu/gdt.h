/**
 * @file	kernel/arch/cpu/gdt.h
 * @brief	x86_64 GDT header
 */

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ENTRIES 5

typedef struct gdt {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t flags;
	uint8_t base_high;
} __attribute__((packed)) gdt_t;

typedef struct gdtr {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed)) gdtr_t;

void gdt_init(void);

void gdt_set_desc(int entry, uint32_t base, uint32_t limit, uint8_t access,
		  uint8_t flags);

/* these are located in gdt.asm */
extern void gdt_load(gdtr_t *gdtr);
extern void gdt_save(gdtr_t *gdtr);

#endif /* GDT_H */
