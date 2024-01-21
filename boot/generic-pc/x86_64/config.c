#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <config.h>
#include <print.h>

axboot_config_t *
axboot_read_config(void)
{
	EFI_STATUS status;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *filesystem;
	EFI_FILE_PROTOCOL *root;
	EFI_FILE_PROTOCOL *config_file;
	axboot_config_t *config;

	// open axboot.conf
	status = g_SystemTable->BootServices->AllocatePool(EfiBootServicesData, sizeof(*config), (void **)&config);
	if (EFI_ERROR(status)) {
		axboot_printf(L"axboot_read_config: Failed to allocate pool for configuration! (Status code: %s)\r\n", EfiErrToStr(status));
		return NULL;
	}

	status = g_SystemTable->BootServices->LocateProtocol(&gEfiSimpleFileSystemProtocolGuid, NULL, (void **)&filesystem);
	if (EFI_ERROR(status)) {
		axboot_printf(L"axboot_read_config: Failed to locate EFI Simple File System Protocol! (Status code: %s)\r\n", EfiErrToStr(status));
		return NULL;
	}

	status = filesystem->OpenVolume(filesystem, &root);
	if (EFI_ERROR(status)) {
		axboot_printf(L"axboot_read_config: Failed to open root volume! (Status code: %s)\r\n", EfiErrToStr(status));
		return NULL;
	}

	status = root->Open(root, &config_file, L"axboot.cfg", EFI_FILE_MODE_READ, 0);
	if (EFI_ERROR(status)) {
		axboot_printf(L"axboot_read_config: Failed to open axboot.cfg! (Status code: %s)\r\n", EfiErrToStr(status));
		return NULL;
	}

	return config;
}
