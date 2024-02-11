export ARCH ?= x86_64
export MACHINE ?= generic-pc
export DEBUG ?= yes

export GIT_REV := $(shell git rev-parse --short HEAD)

# No matter where the makefile is run, this should always be equal to the root
# of this repo.
export ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export BUILD_DIR := $(ROOT_DIR)/build
export RELEASE_DIR := $(ROOT_DIR)/release

RELEASE_ISO := $(RELEASE_DIR)/aurixos-cdrom-$(GIT_REV)_$(ARCH)_$(MACHINE).iso
RELEASE_HDD := $(RELEASE_DIR)/aurixos-hdd-$(GIT_REV)_$(ARCH)_$(MACHINE).img
RELEASE_SDCARD := $(RELEASE_DIR)/aurixos-sdcard-$(GIT_REV)_$(ARCH)_$(MACHINE).img

# User-changeable flags
export CFLAGS ?= -O2 -g -Wall -Wextra
export ASFLAGS ?= 
export LDFLAGS ?=

include arch/$(MACHINE)/$(ARCH)/config.mk
QEMU_FLAGS ?= -m 2G -serial stdio

# Check if arch/machine are correct or supported
ifeq ($(ARCH),x86_64)
	ifneq ($(MACHINE),generic-pc)
		$(error Only generic-pc machine is available for x86_64!)
	endif
else ifeq ($(ARCH),i386)
	$(error Support for i386 is not yet available!)
else ifeq ($(ARCH),armv8)
	$(error Support for armv8 is not yet available!)
else ifeq ($(ARCH),riscv64)
	ifneq ($(MACHINE),qemu-virt)
		$(error Only qemu-virt machine is available for riscv64!)
	endif
else
	$(error Architecture '$(ARCH)' is not supported.)
endif

.PHONY: all
all: bootloader kernel

.PHONY: full_release
full_release: release_iso release_hdd release_sdcard

# try to generate a unique GDB port
GDBPORT = $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)
ifndef CPUS
CPUS := 1
endif

.PHONY: run
run: release_hdd
	@$(QEMU) $(QEMU_FLAGS) $(QEMU_ARCH_FLAGS) -drive file=$(RELEASE_HDD),format=raw

# TODO: Maybe add a nice message with instructions here before running qemu?
.PHONY: rundbg
rundbg: release_hdd
	@$(QEMU) $(QEMUGDB) $(QEMU_FLAGS) $(QEMU_ARCH_FLAGS) -drive file=$(RELEASE_HDD),format=raw

.PHONY: release_iso
release_iso: $(RELEASE_ISO)

.PHONY: release_hdd
release_hdd: $(RELEASE_HDD)

.PHONY: release_sdcard
release_sdcard: $(RELEASE_SDCARD)

.PHONY: bootloader
bootloader:
	@printf ">>> Building bootloader...\n"
	@$(MAKE) -C boot/$(MACHINE)/$(ARCH)

.PHONY: kernel
kernel:
	@printf ">>> Building kernel...\n"
	@$(MAKE) -C kernel

.PHONY: format
format:
	@printf ">>> Formatting code...\n"
	@find . -name "*.c" -not -path "*/ex/*" -o -name "*.h" -not -path "*/ex/*" | xargs clang-format -i

$(RELEASE_ISO): bootloader kernel release_hdd
ifeq ($(ARCH),x86_64)
	@printf ">>> Generating ISO image...\n"
	@mkdir -p $(RELEASE_DIR)
	@rm -rf iso_tmp
	@mkdir -p iso_tmp
	@cp $(RELEASE_HDD) iso_tmp
	@xorriso -as mkisofs -R -f -e $(notdir $(RELEASE_HDD)) -no-emul-boot -o $(RELEASE_ISO) iso_tmp 2>/dev/null
	@rm -rf iso_tmp
else
	@printf "ISO image generation is not supported for $(ARCH)/$(MACHINE).\n"
endif

$(RELEASE_HDD): bootloader kernel
	@printf ">>> Generating HDD image...\n"
	@mkdir -p $(RELEASE_DIR)
	@dd if=/dev/zero of=$(RELEASE_HDD) bs=1k count=1440 2>/dev/null
	@mformat -i $(RELEASE_HDD) -f 1440 ::
	@mcopy -s -i $(RELEASE_HDD) build/output/* sysroot/* ::

$(RELEASE_SDCARD): bootloader kernel
	@printf ">>> Generating SD Card image...\n"
	@mkdir -p $(RELEASE_DIR)
	@printf "SD Card image generation is not yet supported, skipping...\n"

.PHONY: clean
clean:
	@rm -rf iso_tmp hdd_tmp $(RELEASE_DIR) $(BUILD_DIR)
