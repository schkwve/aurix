#include <efi.h>

#include <axboot.h>

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

	// disable watchdog
	Status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if (Status != EFI_SUCCESS) {
		// TODO: print error
	}
	
	for (;;);
	return 0;
}
