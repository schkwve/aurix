override KERNEL_FILE := axkrnl.elf

override CC := riscv64-elf-gcc
override LD := riscv64-elf-ld
override AS := $(CC)


INTERNAL_CFLAGS = $(foreach d, $(INCLUDE_DIRS), -I$d) -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
INTERNAL_CFLAGS += -MD
INTERNAL_CFLAGS += -mcmodel=medany
INTERNAL_CFLAGS += -ffreestanding -fno-common -nostdlib
INTERNAL_CFLAGS += -I. -I$K -I$K/arch/riscv64 -I$K/arch/shared_bindings -I$K/vendor -I$K/util
INTERNAL_CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

override INTERNAL_LDFLAGS := -nostdlib -nodefaultlibs -nostartfiles 

ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
INTERNAL_CFLAGS += -fno-pie -no-pie
endif
ifneq ($(shell $(CC) -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
INTERNAL_CFLAGS += -fno-pie -nopie
endif
