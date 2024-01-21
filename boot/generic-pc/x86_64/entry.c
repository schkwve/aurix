#include <efi.h>

#include <axboot.h>
#include <config.h>
#include <print.h>

EFI_HANDLE g_ImageHandle;
EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle,
		 EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status;

	// we should use these global variables from now on
	g_ImageHandle = ImageHandle;
	g_SystemTable = SystemTable;

	// clear the screen
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
	
	// disable watchdog
	Status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if (EFI_ERROR(Status)) {
		axboot_printf(L"Failed to disable UEFI watchdog!\r\n");
	}

	// parse the bootloader configuration
	axboot_config_t *config = axboot_read_config();

	for (;;);

	return EFI_SUCCESS;
}
