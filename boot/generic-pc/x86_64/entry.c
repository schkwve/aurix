#include <efi.h>

#include <axboot.h>
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

	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);

	char16_t *world = L"world";
	axboot_printf(L"Hello %s!", world);
	
	// disable watchdog
	Status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if (EFI_ERROR(Status)) {
		axboot_printf(u"Failed to disable UEFI watchdog!");
	}
	
	for (;;);
	return 0;
}
