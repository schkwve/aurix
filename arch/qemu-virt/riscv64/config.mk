QEMU := qemu-system-riscv64
QEMU_ARCH_FLAGS := -machine virt -bios none -m 128M -smp 1 -nographic -global virtio-mmio.force-legacy=false
