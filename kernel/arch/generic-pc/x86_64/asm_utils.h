#ifndef ASM_UTILS_H
#define ASM_UTILS_H

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t value)
{
	__asm__ volatile("outb %0, %1" ::"a"(value), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t retval;
	__asm__ volatile("inb %1, %0" : "=a"(retval) : "Nd"(port) : "memory");
	return retval;
}

static inline void wrmsr(uint64_t msr, uint64_t value)
{
	uint32_t lower = value & 0xFFFFFFFF;
	uint32_t upper = value >> 32;
	__asm__ volatile("wrmsr" ::"c"(msr), "a"(lower), "d"(upper));
}

static inline uint64_t rdmsr(uint64_t msr)
{
	uint32_t lower, upper;
	__asm__ volatile("rdmsr" : "=a"(lower), "=d"(upper) : "c"(msr));
	return (((uint64_t)upper << 32) | lower);
}

static inline void invlpg(void *m)
{
	__asm__ volatile("invlpg (%0)" ::"b"(m) : "memory");
}

static inline uint64_t read_cr0()
{
	uint64_t cr0;
	__asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
	return cr0;
}

static inline uint64_t read_cr2()
{
	uint64_t cr2;
	__asm__ volatile("mov %%cr2, %0" : "=r"(cr2));
	return cr2;
}

static inline uint64_t read_cr3()
{
	uint64_t cr3;
	__asm__ volatile("mov %%cr3, %0" : "=r"(cr3));
	return cr3;
}

static inline uint64_t read_cr4()
{
	uint64_t cr4;
	__asm__ volatile("mov %%cr4, %0" : "=r"(cr4));
	return cr4;
}

static inline uint64_t read_cr8()
{
	uint64_t cr8;
	__asm__ volatile("mov %%cr8, %0" : "=r"(cr8));
	return cr8;
}

static inline void write_cr0(uint64_t value)
{
	__asm__ volatile("mov %0, %%cr0" ::"r"(value) : "memory");
}

static inline void write_cr2(uint64_t value)
{
	__asm__ volatile("mov %0, %%cr2" ::"r"(value) : "memory");
}

static inline void write_cr3(uint64_t value)
{
	__asm__ volatile("mov %0, %%cr3" ::"r"(value) : "memory");
}

static inline void write_cr4(uint64_t value)
{
	__asm__ volatile("mov %0, %%cr4" ::"r"(value) : "memory");
}

static inline void write_cr8(uint64_t value)
{
	__asm__ volatile("mov %0, %%cr8" ::"r"(value) : "memory");
}

static inline void cli()
{
	__asm__ volatile("cli");
}

static inline void sti()
{
	__asm__ volatile("sti");
}

#endif /* ASM_UTILS_H */
