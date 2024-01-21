#include <efi.h>

#include <axboot.h>
#include <print.h>
#include <ui/menu.h>

void ui_boot_menu_draw(void)
{
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);

	axboot_printf(L"AxBoot v%s\r\n", AXBOOT_VERSTR);
	axboot_printf(L"%s\r\n", AXBOOT_COPYRIGHT_NOTICESTR);
}
