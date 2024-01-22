#ifndef AURIXOS_H
#define AURIXOS_H

#include <Uefi.h>
#include <axboot.h>

EFI_STATUS
aurixos_boot(axboot_sysent_t *entry);

#endif /* AURIXOS_H */
