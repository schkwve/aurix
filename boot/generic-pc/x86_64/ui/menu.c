#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>

#include <axboot.h>
#include <ui/menu.h>

// TODO: Make a nice logo
static const CHAR16 *axboot_splash[] = {
	L"Press ENTER to boot AurixOS",
	L"Press F1 to Shutdown",
	L"Press F2 to Reboot",
};

void ui_boot_menu_draw(void)
{
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);

	Print(L"AxBoot v%s\r\n", AXBOOT_VERSTR);
	Print(L"%s\r\n\r\n", AXBOOT_COPYRIGHT_NOTICESTR);

	// Show splash screen
	for (size_t i = 0; i < (sizeof(axboot_splash) / sizeof(axboot_splash[0])); i++) {
		Print(L"%s\r\n", axboot_splash[i]);
	}
}
