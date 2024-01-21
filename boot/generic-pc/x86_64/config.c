#include <efi.h>

#include <axboot.h>
#include <config.h>
#include <print.h>

axboot_config_t *
axboot_read_config(void)
{
	EFI_STATUS status;
	axboot_config_t *config;

	status = g_SystemTable->BootServices->AllocatePool(EfiBootServicesData, sizeof(*config), (void **)&config);
	if (EFI_ERROR(status)) {
		axboot_printf(L"axboot_read_config: Failed to allocate pool for configuration! (Status code: %s)\r\n", EfiErrToStr(status));
		return NULL;
	}

	return NULL;
}
