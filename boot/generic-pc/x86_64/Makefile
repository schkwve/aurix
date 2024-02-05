include config.mk

ifeq ($(DEBUG),yes)
INTERNAL_CFLAGS += -g -D_DEBUG
endif

CFILES := $(shell find . -type f -name '*.c')
ASFILES := $(shell find . -type f -name '*.nasm')

BOOT_OBJS := $(CFILES:%.c=$(BUILD_DIR)/%.c.o) \
			$(ASFILES:%.nasm=$(BUILD_DIR)/%.nasm.o)

HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE)

-include $(HEADER_DEPS)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.nasm.o: %.nasm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
