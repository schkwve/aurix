QEMU := qemu-system-riscv64
QEMU_ARCH_FLAGS := -nographic -machine virt -bios none -kernel build/output/bootcode.bin -global virtio-mmio.force-legacy=false
