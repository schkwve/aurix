#include "boot.h"

LIMINE_BASE_REVISION(1)

struct limine_rsdp_request rsdp_request = { .id = LIMINE_RSDP_REQUEST,
					    .revision = 0 };

struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 1
};

struct limine_memmap_request memmap_request = { .id = LIMINE_MEMMAP_REQUEST,
						.revision = 0 };

struct limine_hhdm_request hhdm_request = { .id = LIMINE_HHDM_REQUEST,
					    .revision = 0 };
