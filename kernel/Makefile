INCLUDE_DIRS := libc arch/$(MACHINE)/$(ARCH) .

include arch/$(MACHINE)/$(ARCH)/config.mk

ifeq ($(DEBUG),yes)
INTERNAL_CFLAGS += -g -D_DEBUG
endif

ARCH_CFILES := $(shell find arch/$(MACHINE)/$(ARCH) -type f -name '*.c')
ARCH_ASFILES := $(shell find arch/$(MACHINE)/$(ARCH) -type f -name '*.asm')

CFILES := $(shell find . -type f -name '*.c' -not -path "./arch/*")
ASFILES := $(shell find . -type f -name '*.asm' -not -path "./arch/*")

KERNEL_OBJS := $(ARCH_CFILES:%.c=$(BUILD_DIR)/%.c.o) $(CFILES:%.c=$(BUILD_DIR)/%.c.o) \
				$(ARCH_ASFILES:%.asm=$(BUILD_DIR)/%.asm.o) $(ASFILES:%.asm=$(BUILD_DIR)/%.asm.o)

HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(BUILD_DIR)/output/$(KERNEL_FILE)

-include $(HEADER_DEPS)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.asm.o: %.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/output/$(KERNEL_FILE): $(KERNEL_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) -T$(ROOT_DIR)/kernel/arch/$(MACHINE)/$(ARCH)/linker.x $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
