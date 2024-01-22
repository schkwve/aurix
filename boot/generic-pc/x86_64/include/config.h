#ifndef CONFIG_H
#define CONFIG_H

#include <Uefi.h>

#include <axboot.h>

EFI_STATUS config_get_entry();
EFI_STATUS config_load_boot_entry(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs, axboot_sysent_t *entry);

extern axboot_sysent_t g_axos_entry;

#endif /* CONFIG_H */
