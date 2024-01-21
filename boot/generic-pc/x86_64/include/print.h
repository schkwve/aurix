#ifndef PRINT_H
#define PRINT_H

#include <efi_types.h>

void
axboot_printf(char16_t *fmt, ...);

void
priv_printc(char16_t c);

#endif /* PRINT_H */
