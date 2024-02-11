#ifndef BOOT_H
#define BOOT_H

#include "limine.h"

extern struct limine_rsdp_request rsdp_request;
extern struct limine_framebuffer_request framebuffer_request;
extern struct limine_memmap_request memmap_request;
extern struct limine_hhdm_request hhdm_request;

#endif /* BOOT_H */
