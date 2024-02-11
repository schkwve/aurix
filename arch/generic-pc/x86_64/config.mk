QEMU := qemu-system-x86_64
QEMU_ARCH_FLAGS := -bios arch/$(MACHINE)/$(ARCH)/ovmf_x64.fd -serial stdio
