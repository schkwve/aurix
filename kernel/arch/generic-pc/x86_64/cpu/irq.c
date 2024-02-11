#include <cpu/idt.h>
#include <cpu/irq.h>
#include <aurix.h>
#include <stddef.h>

static const char *g_exception_str[32] = { "division by zero",
										   "debug",
										   "nonmaskable interrupt",
										   "breakpoint",
										   "overflow",
										   "bound range exceeded",
										   "invalid opcode",
										   "device not available",
										   "double fault",
										   "coprocessor segment overrun",
										   "invalid tss",
										   "segment not present",
										   "stack segment fault",
										   "general protection fault",
										   "page fault",
										   "reserved",
										   "x87 fpu error"
										   "alignment check",
										   "machine check",
										   "simd exception",
										   "virtualization exception",
										   "control protection exception",
										   "reserved",
										   "reserved",
										   "reserved",
										   "reserved",
										   "reserved",
										   "reserved",
										   "hypervisor injection exception",
										   "vmm communication exception",
										   "security exception",
										   "reserved" };

void excp_handler(int_frame_t frame)
{
	// TODO: Get CPU number when SMP support is present
	// 
	// Message:
	// panic(cpu %d, 0x%.16llx): type %.02x (%s), registers:\n"
	// cpu_num, RIP, vector hex, vector, g_exception_str[vector]

	// TODO: dump registers
	// TODO: dump version/debug strings

	klog("exception!");

	for (;;) {
		__asm__ volatile("hlt");
	}
}
