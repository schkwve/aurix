override BOOT_FILE := bootcode.bin

override INCLUDE_DIRS := lib include

override CC := riscv64-elf-gcc
override LD := riscv64-elf-ld

INTERNAL_CFLAGS = $(foreach d, $(INCLUDE_DIRS), -I$d) \
					-MD -Wall -Werror -O -fno-omit-frame-pointer \
					-mcmodel=medany \
					-ffreestanding -fno-common -nostdlib -fno-stack-protector \
					-fno-pie -no-pie -nostartfiles -nodefaultlibs

INTERNAL_LDFLAGS = -nostdlib -T linker.x
