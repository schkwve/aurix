#ifndef EFILIB_H
#define EFILIB_H

#include "efi.h"

// EFI Scan Codes
#define EFI_SCANCODE_NULL										0x00
#define EFI_SCANCODE_ARROW_UP									0x01
#define EFI_SCANCODE_ARROW_DOWN									0x02
#define EFI_SCANCODE_ARROW_RIGHT								0x03
#define EFI_SCANCODE_ARROW_LEFT									0x04
#define EFI_SCANCODE_HOME										0x05
#define EFI_SCANCODE_END										0x06
#define EFI_SCANCODE_INSERT										0x07
#define EFI_SCANCODE_DELETE										0x08
#define EFI_SCANCODE_PGUP										0x09
#define EFI_SCANCODE_PGDN										0x0A
#define EFI_SCANCODE_FN1										0x0B
#define EFI_SCANCODE_FN2										0x0C
#define EFI_SCANCODE_FN3										0x0D
#define EFI_SCANCODE_FN4										0x0E
#define EFI_SCANCODE_FN5										0x0F
#define EFI_SCANCODE_FN6										0x10
#define EFI_SCANCODE_FN7										0x11
#define EFI_SCANCODE_FN8										0x12
#define EFI_SCANCODE_FN9										0x13
#define EFI_SCANCODE_FN10										0x14
#define EFI_SCANCODE_ESC										0x17
#define EFI_SCANCODE_FN11										0x15
#define EFI_SCANCODE_FN12										0x16
#define EFI_SCANCODE_PAUSE										0x48
#define EFI_SCANCODE_FN13										0x68
#define EFI_SCANCODE_FN14										0x69
#define EFI_SCANCODE_FN15										0x6A
#define EFI_SCANCODE_FN16										0x6B
#define EFI_SCANCODE_FN17										0x6C
#define EFI_SCANCODE_FN18										0x6D
#define EFI_SCANCODE_FN19										0x6E
#define EFI_SCANCODE_FN20										0x6F
#define EFI_SCANCODE_FN21										0x70
#define EFI_SCANCODE_FN22										0x71
#define EFI_SCANCODE_FN23										0x72
#define EFI_SCANCODE_FN24										0x73
#define EFI_SCANCODE_MUTE										0x7F
#define EFI_SCANCODE_VOL_UP										0x80
#define EFI_SCANCODE_VOL_DN										0x81
#define EFI_SCANCODE_BRIGHTNESS_UP								0x100
#define EFI_SCANCODE_BRIGHTNESS_DN								0x101
#define EFI_SCANCODE_SUSPEND									0x102
#define EFI_SCANCODE_HIBERNATE									0x103
#define EFI_SCANCODE_DISPLAY_TOGGLE								0x104
#define EFI_SCANCODE_RECOVERY									0x105
#define EFI_SCANCODE_EJECT										0x106
//

// EFI Unicode Controls
#define EFI_CHAR_BACKSPACE										0x08
#define EFI_CHAR_TAB											0x09
#define EFI_CHAR_LINEFEED										0x0A
#define EFI_CHAR_CARRIAGE_RETURN								0x0D
//

#define EFI_ERROR(Status)								(((INTN)(EFI_STATUS)(Status)) < 0)

const CHAR16 *EfiErrToStr(EFI_STATUS Status);

#endif /* EFILIB_H */
