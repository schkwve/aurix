override BOOT_FILE := bootcode.bin

override INCLUDE_DIRS := lib include

override CC := riscv64-elf-gcc
override LD := riscv64-elf-ld

INTERNAL_CFLAGS = $(foreach d, $(INCLUDE_DIRS), -I$d) 
INTERNAL_CFLAGS += -MD -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
INTERNAL_CFLAGS += -mcmodel=medany
INTERNAL_CFLAGS += -ffreestanding -fno-common -nostdlib -fno-stack-protector
INTERNAL_CFLAGS += -fno-pie -no-pie

INTERNAL_LDFLAGS = -nostdlib -nodefaultlibs -nostartfiles  -T linker.ld
