#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/CpuLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <config/BootEntries.h>
#include <util/Except.h>
#include <config/BootConfig.h>
#include <uefi/AcpiTimerLib.h>
#include <loaders/Loaders.h>
#include <loaders/elf/ElfLoader.h>
#include <Library/TimerLib.h>
#include <util/DrawUtils.h>
#include <config/BootEntries.h>
#include <axboot.h>

// define all constructors
extern EFI_STATUS EFIAPI UefiBootServicesTableLibConstructor(
	IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);
extern EFI_STATUS EFIAPI DxeDebugLibConstructor(
	IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);
extern EFI_STATUS EFIAPI UefiRuntimeServicesTableLibConstructor(
	IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);

/**
 * The entry of the os
 */
EFI_STATUS EFIAPI EfiMain(IN EFI_HANDLE ImageHandle,
			  IN EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status = EFI_SUCCESS;

	// Call constructors
	EFI_CHECK(DxeDebugLibConstructor(ImageHandle, SystemTable));
	EFI_CHECK(
		UefiBootServicesTableLibConstructor(ImageHandle, SystemTable));
	EFI_CHECK(UefiRuntimeServicesTableLibConstructor(ImageHandle,
							 SystemTable));

	// make sure we got everything nice and dandy
	CHECK(gST != NULL);
	CHECK(gBS != NULL);
	CHECK(gRT != NULL);

	// run our own constructors
	CHECK_AND_RETHROW(AcpiTimerLibConstructor());

	// disable the watchdog timer
	EFI_CHECK(gST->BootServices->SetWatchdogTimer(0, 0, 0, NULL));

	// just a signature that we booted
	EFI_CHECK(gST->ConOut->ClearScreen(gST->ConOut));

	// Prepare workaround for custom memory type
	if (
		// for AMI bioses
		(StrCmp(gST->FirmwareVendor, L"American Megatrends") == 0 &&
		 gST->FirmwareRevision <= 0x0005000C)) {
		TRACE("Need workaround for memory type :(");
		gKernelAndModulesMemoryType = EfiMemoryMappedIOPortSpace;
	}

	// Load the boot configs and set the default one
	BOOT_CONFIG config;
	LoadBootConfig(&config);
	CHECK_AND_RETHROW(GetBootEntries(&gBootEntries));
	gDefaultEntry = GetBootEntryAt(config.DefaultOS);

	// we are ready to do shit :yay:
	UINTN width = 0;
	UINTN height = 0;
	ASSERT_EFI_ERROR(gST->ConOut->QueryMode(
		gST->ConOut, gST->ConOut->Mode->Mode, &width, &height));

	INTN selected = 0;
	BOOT_ENTRY *selectedEntry = NULL;

	gST->ConOut->ClearScreen(gST->ConOut);
	WriteAt(0, 0, "AxBoot v" AXBOOT_VERSION_STR);
	WriteAt(0, 1, AXBOOT_COPYRIGHT_STR);
	while (TRUE) {
		// draw the entries
		// TODO: Add a way to edit the command line
		INTN i = 0;
		for (LIST_ENTRY *link = gBootEntries.ForwardLink;
		     link != &gBootEntries; link = link->ForwardLink, i++) {
			BOOT_ENTRY *entry = BASE_CR(link, BOOT_ENTRY, Link);

			// draw the correct background
			if (i == selected) {
				selectedEntry = entry;
				WriteAt(6, 4 + i, " > %s <", entry->Name);
			} else {
				WriteAt(6, 4 + i, "   %s  ", entry->Name);
			}

			// write the option
		}

		// get key press
		UINTN which = 0;
		EFI_INPUT_KEY key = {};
		ASSERT_EFI_ERROR(
			gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &which));
		EFI_STATUS status = gST->ConIn->ReadKeyStroke(gST->ConIn, &key);
		if (status == EFI_NOT_READY) {
			continue;
		}
		ASSERT_EFI_ERROR(status);

		// decrease value
		if (key.ScanCode == SCAN_DOWN) {
			selected++;
			if (selected >= i) {
				selected = 0;
			}

			// prev potion
		} else if (key.ScanCode == SCAN_UP) {
			selected--;
			if (selected < 0) {
				selected = i - 1;
			}

			// save and exit
		} else if (key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
			LoadKernel(selectedEntry);
			while (1)
				CpuSleep();
		}
	}

cleanup:
	if (EFI_ERROR(Status)) {
		ASSERT_EFI_ERROR(Status);
	}

	while (1)
		CpuSleep();

	return EFI_SUCCESS;
}
