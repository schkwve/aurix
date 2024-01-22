#ifndef __AXBOOT_H
#define __AXBOOT_H

#include <Uefi.h>
#include <Protocol/SimpleFileSystem.h>

#define AXBOOT_VERSTR L"0.1"
#define AXBOOT_COPYRIGHT_NOTICESTR L"Copyright (c) 2023-2024 AurixOS"

extern EFI_HANDLE g_ImageHandle;
extern EFI_SYSTEM_TABLE *g_SystemTable;

typedef struct {
	CHAR16 *name;
	CHAR16 *kernel_path;
	CHAR16 *cmdline;

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs;
} axboot_sysent_t;

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle,
		 EFI_SYSTEM_TABLE *SystemTable);

void
AxBootFatal(void);

#endif /* __AXBOOT_H */
