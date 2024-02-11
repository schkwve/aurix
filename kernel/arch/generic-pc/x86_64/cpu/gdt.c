/**
 * @file	kernel/arch/cpu/gdt.c
 * @brief	x86_64 GDT functionality
 */

#include <cpu/gdt.h>

__attribute__((aligned(0x1000))) gdt_t gdt[GDT_ENTRIES];

/**
 * @brief	Initializes GDT descriptors, loads them into GDTR and reloads
 * 			segment registers.
 */
void gdt_init(void)
{
	// 0x00: NULL
	gdt_set_desc(0, 0, 0, 0x00, 0x00);

	// 0x08: 64-bit Kernel Code
	gdt_set_desc(1, 0, 0, 0x9A, 0xA0);

	// 0x10: 64-bit Kernel Data
	gdt_set_desc(2, 0, 0, 0x92, 0xC0);

	// 0x18: 64-bit User Code
	gdt_set_desc(3, 0, 0, 0xFA, 0xA0);

	// 0x20: 64-bit User Data
	gdt_set_desc(4, 0, 0, 0xF2, 0xC0);

	gdtr_t gdtr;
	gdtr.size = sizeof(gdt) - 1;
	gdtr.offset = (uint64_t)&gdt;

	gdt_load(&gdtr);
}

/**
 * @brief	Fills a GDT descriptor with specified values.
 * 
 * @param	entry
 * 			Descriptor to fill
 * 
 * @param	base
 * 			Descriptor's base
 * 
 * @param	limit
 * 			Descriptor's limit
 * 
 * @param	access
 * 			Descriptor's access byte
 * 
 * @param	flags
 * 			Descriptor's flags
 */
void gdt_set_desc(int entry, uint32_t base, uint32_t limit, uint8_t access,
		  uint8_t flags)
{
	gdt[entry].limit_low = limit & 0xFFFF;
	gdt[entry].base_low = base & 0xFFFF;
	gdt[entry].base_mid = (base >> 16) & 0xFF;
	gdt[entry].base_high = (base >> 24) & 0xFF;
	gdt[entry].flags = (limit >> 16) | flags;
	gdt[entry].access = access;
}
