include config.mk

.PHONY: all
all: $(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE)

$(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE):
	@mkdir -p $(dir $@)
	@cp $(ROOT_DIR)/ex/limine/BOOTX64.EFI $@
