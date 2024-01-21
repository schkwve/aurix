#ifndef CONFIG_H
#define CONFIG_H

#include <axboot.h>

typedef struct axboot_sysent {
	char *name;
	char *cmdline;
} axboot_sysent_t;

typedef struct axboot_config {
	uint8_t default_entry;
	uint8_t entry_count;
	axboot_sysent_t *entries;
} axboot_config_t;

axboot_config_t *
axboot_read_config(void);

#endif /* CONFIG_H */
