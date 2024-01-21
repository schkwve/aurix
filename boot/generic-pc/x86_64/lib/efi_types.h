#ifndef EFI_TYPES_H
#define EFI_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Wide character
typedef uint_least16_t char16_t;

// Common UEFI Data types
typedef uint8_t BOOLEAN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef char CHAR8;
typedef char16_t CHAR16;
typedef void VOID;

typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

// https://github.com/tianocore/edk2/blob/master/MdePkg/Include/Base.h
#define IN
#define OUT
#define OPTIONAL
#define CONST const

// x86_64 Microsoft calling convention
// https://github.com/vathpela/gnu-efi/blob/master/inc/x86_64/efibind.h
#define EFIAPI __attribute__((ms_abi))

// EFI Physical Address
typedef UINT64 EFI_PHYSICAL_ADDRESS;

// EFI Virtual Address
typedef UINT64 EFI_VIRTUAL_ADDRESS;

// Task Priority Level
typedef UINTN EFI_TPL;

// EFI Status Codes
#define EFI_SUCCESS													(0x00)
#define EFI_LOAD_ERROR												(0x8000000000000001)
#define EFI_INVALID_PARAMETER										(0x8000000000000002)
#define EFI_UNSUPPORTED												(0x8000000000000003)
#define EFI_BAD_BUFFER_SIZE											(0x8000000000000004)
#define EFI_BUFFER_TOO_SMALL										(0x8000000000000005)
#define EFI_NOT_READY												(0x8000000000000006)
#define EFI_DEVICE_ERROR											(0x8000000000000007)
#define EFI_WRITE_PROTECTED											(0x8000000000000008)
#define EFI_OUT_OF_RESOURCES										(0x8000000000000009)
#define EFI_VOLUME_CORRUPTED										(0x800000000000000A)
#define EFI_VOLUME_FULL												(0x800000000000000B)
#define EFI_NO_MEDIA												(0x800000000000000C)
#define EFI_MEDIA_CHANGED											(0x800000000000000D)
#define EFI_NOT_FOUND												(0x800000000000000E)
#define EFI_ACCESS_DENIED											(0x800000000000000F)
#define EFI_NO_RESPONSE												(0x8000000000000010)
#define EFI_NO_MAPPING												(0x8000000000000011)
#define EFI_TIMEOUT													(0x8000000000000012)
#define EFI_NOT_STARTED												(0x8000000000000013)
#define EFI_ALREADY_STARTED											(0x8000000000000014)
#define EFI_ABORTED													(0x8000000000000015)
#define EFI_ICMP_ERROR												(0x8000000000000016)
#define EFI_TFTP_ERROR												(0x8000000000000017)
#define EFI_PROTOCOL_ERROR											(0x8000000000000018)
#define EFI_INCOMPATIBLE_VERSION									(0x8000000000000019)
#define EFI_SECURITY_VIOLATION										(0x800000000000001A)
#define EFI_CRC_ERROR												(0x800000000000001B)
#define EFI_END_OF_MEDIA											(0x800000000000001C)
#define EFI_END_OF_FILE												(0x800000000000001F)
#define EFI_INVALID_LANGUAGE										(0x8000000000000020)
#define EFI_COMPROMISED_DATA										(0x8000000000000021)
#define EFI_IP_ADDRESS_CONFLICT										(0x8000000000000022)
#define EFI_HTTP_ERROR												(0x8000000000000023)

// Text color attributes
#define EFI_BLACK										0x00
#define EFI_BLUE										0x01
#define EFI_GREEN										0x02
#define EFI_CYAN										0x03
#define EFI_RED											0x04
#define EFI_MAGENTA										0x05
#define EFI_BROWN										0x06
#define EFI_LIGHTGRAY									0x07
#define EFI_BRIGHT										0x08
#define EFI_DARKGRAY									(EFI_BLACK | EFI_BRIGHT) 0x08
#define EFI_LIGHTBLUE									0x09
#define EFI_LIGHTGREEN									0x0A
#define EFI_LIGHTCYAN									0x0B
#define EFI_LIGHTRED									0x0C
#define EFI_LIGHTMAGENTA								0x0D
#define EFI_YELLOW										0x0E
#define EFI_WHITE										0x0F

// Text background colors
#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN 0x30
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA 0x50
#define EFI_BACKGROUND_BROWN 0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70

// Converts Foreground and Background colors into a single value
#define EFI_TEXT_ATTR(Foreground,Background) \
	((Foreground) | ((Background) << 4))

#endif /* EFI_TYPES_H */
