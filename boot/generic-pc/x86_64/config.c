#include <Uefi.h>
#include <Protocol/LoadedImage.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/FileHandleLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#include <axboot.h>
#include <config.h>

static CHAR16 *config_file_locations[] = {
	L"System\\axboot.cfg",
	L"boot\\axboot.cfg",
	L"axboot.cfg"
};

axboot_sysent_t g_axos_entry;

EFI_STATUS config_get_entry()
{
	EFI_STATUS status;
	EFI_LOADED_IMAGE_PROTOCOL* loaded_image = NULL;
	EFI_DEVICE_PATH_PROTOCOL* boot_device_path = NULL;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* boot_fs = NULL;
	EFI_HANDLE fs_handle = NULL;

	status = g_SystemTable->BootServices->HandleProtocol(g_ImageHandle, &gEfiLoadedImageProtocolGuid, (void **)&loaded_image);
	if (EFI_ERROR(status)) {
		Print(L"config_get_entry: An error has occured while loading AxBoot configuration! (Status code: %r)\n", status);
		AxBootFatal();
	}

	status = g_SystemTable->BootServices->HandleProtocol(loaded_image->DeviceHandle, &gEfiDevicePathProtocolGuid, (void **)&boot_device_path);
	if (EFI_ERROR(status)) {
		Print(L"config_get_entry: An error has occured while loading AxBoot configuration! (Status code: %r)\n", status);
		AxBootFatal();
	}

	status = g_SystemTable->BootServices->LocateDevicePath(&gEfiSimpleFileSystemProtocolGuid, &boot_device_path, &fs_handle);
	if (EFI_ERROR(status)) {
		Print(L"config_get_entry: An error has occured while loading AxBoot configuration! (Status code: %r)\n", status);
		AxBootFatal();
	}

	status = g_SystemTable->BootServices->HandleProtocol(fs_handle, &gEfiSimpleFileSystemProtocolGuid, (void **)&boot_fs);
	if (EFI_ERROR(status)) {
		Print(L"config_get_entry: An error has occured while loading AxBoot configuration! (Status code: %r)\n", status);
		AxBootFatal();
	}

	status = config_load_boot_entry(boot_fs, &g_axos_entry);
	if (EFI_ERROR(status)) {
		Print(L"config_get_entry: An error has occured while loading AxBoot configuration! (Status code: %r)\n", status);
		AxBootFatal();
	}

	if (g_axos_entry.kernel_path == NULL) {
		Print(L"config_get_entry: g_axos_entry.kernel_path == NULL\n");
		AxBootFatal();
	}

	return EFI_SUCCESS;
}

EFI_STATUS config_load_boot_entry(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs, axboot_sysent_t *entry)
{
	EFI_STATUS status;
	EFI_FILE_PROTOCOL *root = NULL;
	EFI_FILE_PROTOCOL *config_file = NULL;

	if (fs == NULL) {
		Print(L"config_load_boot_entry: No filesystem specified!\n");
		AxBootFatal();
	}

	status = fs->OpenVolume(fs, &root);
	if (EFI_ERROR(status)) {
		Print(L"config_load_boot_entry: Failed to open Boot filesystem! (Status code: %r)\n", status);
		AxBootFatal();
	}

	for (size_t i = 0; i < sizeof(config_file_locations) / sizeof(config_file_locations[0]); i++) {
		status = root->Open(root, &config_file, config_file_locations[i], EFI_FILE_MODE_READ, 0);
		if (!EFI_ERROR(status)) {
			break;
		}

		config_file = NULL;
	}

	if (config_file == NULL) {
		Print(L"config_load_boot_entry: No configuration file found!\n");
		AxBootFatal();
	}

	for (;;) {
		CHAR16 line[255];
		UINTN line_size = 255;
		BOOLEAN ascii = TRUE;

		if(FileHandleEof(config_file))
			break;

		status = FileHandleReadLine(config_file, line, &line_size, FALSE, &ascii);
		if (EFI_ERROR(status)) {
			Print(L"config_load_boot_entry: Failed to read configuration file!\n");
			FileHandleClose(config_file);
			FileHandleClose(root);
			AxBootFatal();
		}

		if (line[0] == L'!') {
			CHAR16 *name = line + 1;

			entry->fs = fs;
			entry->name = AllocateCopyPool((StrLen(name) + 1) * sizeof(CHAR16), name);
			entry->cmdline = L"";
		} else {
			if (entry->name == NULL) {
				continue;
			}

			if (StrnCmp(line, L"kernel", StrLen(L"kernel")) == 0) {
				CHAR16 *kernel_path = StrStr(line, L"=") + 1;
				entry->kernel_path = AllocateCopyPool((StrLen(kernel_path) + 1) * sizeof(CHAR16), kernel_path);
			} else if (StrnCmp(line, L"cmdline", StrLen(L"cmdline")) == 0) {
				CHAR16 *cmdline = StrStr(line, L"=") + 1;
				entry->cmdline = AllocateCopyPool((StrLen(cmdline) + 1) * sizeof(CHAR16), cmdline);
			}
		}
	}

	return EFI_SUCCESS;
}