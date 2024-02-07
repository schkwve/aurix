override KERNEL_FILE := System/axkrnl.elf

override AS := nasm
override CC := x86_64-elf-gcc
override LD := x86_64-elf-ld

override INTERNAL_ASFLAGS := $(foreach d, $(INCLUDE_DIRS), -I$d) \
							-felf64

override INTERNAL_CFLAGS := $(foreach d, $(INCLUDE_DIRS), -I$d) \
							-std=c11 \
							-ffreestanding \
							-fno-stack-protector \
							-fno-stack-check \
							-fno-pie \
							-fno-pic \
							-m64 \
							-march=x86-64 \
							-mabi=sysv \
							-mno-80387 \
							-mno-mmx \
							-mno-sse \
							-mno-sse2 \
							-mno-red-zone \
							-mcmodel=kernel \
							-MMD

override INTERNAL_LDFLAGS := -nostdlib \
							-zmax-page-size=0x1000 \
							-static