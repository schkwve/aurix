#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

#include <axboot.h>
#include <ui/menu.h>

EFI_HANDLE g_ImageHandle;
EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS EFIAPI UefiBootServicesTableLibConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);
EFI_STATUS EFIAPI UefiRuntimeServicesTableLibConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);
EFI_STATUS EFIAPI RuntimeDriverLibConstruct(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);
EFI_STATUS EFIAPI DxeDebugLibConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);
EFI_STATUS EFIAPI BaseRngLibConstructor();

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle,
		 EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status;
	EFI_INPUT_KEY Key;

	// we should use these global variables from now on
	g_ImageHandle = ImageHandle;
	g_SystemTable = SystemTable;

	if (EFI_ERROR(UefiBootServicesTableLibConstructor(ImageHandle, SystemTable))) {
		Print(L"EfiMain: An error has been invoked during the execution of the program (Status code: %r)\n", Status);
		AxBootFatal();
	}
    if (EFI_ERROR(UefiRuntimeServicesTableLibConstructor(ImageHandle, SystemTable))) {
		Print(L"EfiMain: An error has been invoked during the execution of the program (Status code: %r)\n", Status);
		AxBootFatal();
	}
    if (EFI_ERROR(RuntimeDriverLibConstruct(ImageHandle, SystemTable))) {
		Print(L"EfiMain: An error has been invoked during the execution of the program (Status code: %r)\n", Status);
		AxBootFatal();
	}
    if (EFI_ERROR(DxeDebugLibConstructor(ImageHandle, SystemTable))) {
		Print(L"EfiMain: An error has been invoked during the execution of the program (Status code: %r)\n", Status);
		AxBootFatal();
	}
    if (EFI_ERROR(BaseRngLibConstructor())) {
		Print(L"EfiMain: An error has been invoked during the execution of the program (Status code: %r)\n", Status);
		AxBootFatal();
	}

	// clear the screen
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
	
	// disable watchdog
	Status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if (EFI_ERROR(Status)) {
		Print(L"Failed to disable UEFI watchdog!\r\n");
	}

	UINTN Rows = 0;
	g_SystemTable->ConOut->QueryMode(g_SystemTable->ConOut, 0, NULL, &Rows);

	ui_boot_menu_draw();
	g_SystemTable->ConIn->Reset(g_SystemTable->ConIn, 0);
	for (;;) {
		g_SystemTable->ConIn->ReadKeyStroke(g_SystemTable->ConIn, &Key);

		if (Key.ScanCode == SCAN_F1) {
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
		} else if (Key.ScanCode == SCAN_F2) {
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
		} else if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
			g_SystemTable->ConOut->SetCursorPosition(g_SystemTable->ConOut, 0, Rows - 2);
			Print(L"Booting AurixOS...");
		}
	}

	return EFI_SUCCESS;
}

void
AxBootFatal(void)
{
	Print(L"\r\nFailed to boot AurixOS!\r\n");
	Print(L"Rebooting in 5 seconds...");
	g_SystemTable->BootServices->Stall(5000000);
	g_SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}
