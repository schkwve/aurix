#include <efi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	(void)ImageHandle;

	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
	
	for (;;);
	return 0;
}
