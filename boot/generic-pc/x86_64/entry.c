#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

#include <axboot.h>
#include <config.h>
#include <loader/aurixos.h>
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
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	// we should use these global variables from now on
	g_ImageHandle = ImageHandle;
	g_SystemTable = SystemTable;

	if (EFI_ERROR(UefiBootServicesTableLibConstructor(ImageHandle, SystemTable))) {
		Print(L"efi_main: An error has occured while initializing UEFI! (Status code: %r)\n", status);
		AxBootFatal();
	}
    if (EFI_ERROR(UefiRuntimeServicesTableLibConstructor(ImageHandle, SystemTable))) {
		Print(L"efi_main: An error has occured while initializing UEFI! (Status code: %r)\n", status);
		AxBootFatal();
	}
    if (EFI_ERROR(RuntimeDriverLibConstruct(ImageHandle, SystemTable))) {
		Print(L"efi_main: An error has occured while initializing UEFI! (Status code: %r)\n", status);
		AxBootFatal();
	}
    if (EFI_ERROR(DxeDebugLibConstructor(ImageHandle, SystemTable))) {
		Print(L"efi_main: An error has occured while initializing UEFI! (Status code: %r)\n", status);
		AxBootFatal();
	}
    if (EFI_ERROR(BaseRngLibConstructor())) {
		Print(L"efi_main: An error has occured while initializing UEFI! (Status code: %r)\n", status);
		AxBootFatal();
	}

	// clear the screen
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
	
	// disable watchdog
	status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if (EFI_ERROR(status)) {
		Print(L"Failed to disable UEFI watchdog!\r\n");
	}

	UINTN rows = 0;
	g_SystemTable->ConOut->QueryMode(g_SystemTable->ConOut, 0, NULL, &rows);

	ui_boot_menu_draw();
	g_SystemTable->ConIn->Reset(g_SystemTable->ConIn, 0);
	for (;;) {
		g_SystemTable->ConIn->ReadKeyStroke(g_SystemTable->ConIn, &key);

		if (key.ScanCode == SCAN_F1) {
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
		} else if (key.ScanCode == SCAN_F2) {
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
		} else if (key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
			g_SystemTable->ConOut->SetCursorPosition(g_SystemTable->ConOut, 0, rows - 2);
			Print(L"Booting AurixOS...\n");
			
			status = config_get_entry();
			if (EFI_ERROR(status)) {
				Print(L"efi_main: An error has occured while loading AurixOS! (Status code: %r)\n", status);
				AxBootFatal();
			}

			status = aurixos_boot(&g_axos_entry);
			if (EFI_ERROR(status)) {
				Print(L"efi_main: An error has occured while loading AurixOS! (Status code: %r)\n", status);
				AxBootFatal();
			}

			// the kernel returned, which means nothing good
			g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
			Print(L"A fatal error has occured and AurixOS cannot continue execution.\r\n");
			Print(L"The system will reboot in 10 seconds...\r\n");
			g_SystemTable->BootServices->Stall(10000000);
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
		}
	}

	return EFI_SUCCESS;
}

void
AxBootFatal(void)
{
	Print(L"\r\nFailed to boot AurixOS!\r\n");
	Print(L"The system will reboot in 5 seconds...");
	g_SystemTable->BootServices->Stall(5000000);
	g_SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}
