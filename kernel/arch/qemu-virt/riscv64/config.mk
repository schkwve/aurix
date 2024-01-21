override KERNEL_FILE := axkrnl.elf

override AS := riscv64-elf-gas
override CC := riscv64-elf-gcc
override LD := riscv64-elf-ld

override INTERNAL_ASFLAGS := 

override INTERNAL_CFLAGS := -O -MD -mcmodel=medany -nostdlib \
							-fno-omit-frame-pointer -fno-pie \
							-ffreestanding -fno-common -fno-stack-protector \
							-nodefaultlibs -nostartfiles

override INTERNAL_LDFLAGS := -nostdlib
