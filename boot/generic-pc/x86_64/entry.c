#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>
#include <ui/menu.h>

EFI_HANDLE g_ImageHandle;
EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle,
		 EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status;
	EFI_INPUT_KEY key;
	UINTN rows;

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

	// Query number of rows
	g_SystemTable->ConOut->QueryMode(g_SystemTable->ConOut, 0, NULL, &rows);

	ui_boot_menu_draw();
	g_SystemTable->ConIn->Reset(g_SystemTable->ConIn, 0);
	for (;;) {
		g_SystemTable->ConIn->ReadKeyStroke(g_SystemTable->ConIn, &key);
		
		if (key.ScanCode == EFI_SCANCODE_FN1) {
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
		} else if (key.ScanCode == EFI_SCANCODE_FN2) {
			g_SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
		}
		
		if (key.UnicodeChar == EFI_CHAR_CARRIAGE_RETURN) {
			// Boot System
			g_SystemTable->ConOut->SetCursorPosition(g_SystemTable->ConOut, 0, rows - 2);
			axboot_printf(L"Booting AurixOS...");
		}
	}

	return EFI_SUCCESS;
}
