#include <stdarg.h>
#include <efi.h>

#include <axboot.h>
#include <print.h>

void
axboot_printf(char16_t *fmt, ...)
{
	va_list args;

	va_start(args, fmt);

	for (size_t i = 0; fmt[i] != u'\0'; i++) {
		if (fmt[i] == L'%') {
			i++;

			switch (fmt[i]) {
				case L's': {
					char16_t *str = va_arg(args, char16_t *);
					while (*str) {
						priv_printc(*str++);
					}
					break;
				}
				case L'c': {
					priv_printc(va_arg(args, int));
					break;
				}
				default: {
					g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, L"%??");
					break;
				}
			}
		} else {
			priv_printc(fmt[i]);
		}
	}

	va_end(args);
}

void
priv_printc(char16_t c)
{
    char16_t buf[2];

    buf[0] = c;
    buf[1] = 0;
    g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, buf);
}
