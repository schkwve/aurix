include config.mk

ifeq ($(DEBUG),yes)
INTERNAL_CFLAGS += -g -D_DEBUG
INTERNAL_ASFLAGS += -g -D_DEBUG
endif

override AS := $(CC)

CFILES := $(shell find . -type f -name '*.c')
ASFILES := $(shell find . -type f -name '*.S')

BOOT_OBJS := $(CFILES:%.c=$(BUILD_DIR)/%.c.o) $(ASFILES:%.S=$(BUILD_DIR)/%.S.o)

HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(BUILD_DIR)/output/$(BOOT_FILE)

-include $(HEADER_DEPS)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.S.o: %.S
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/output/$(BOOT_FILE): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
