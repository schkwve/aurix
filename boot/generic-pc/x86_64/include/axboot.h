#ifndef __AXBOOT_H
#define __AXBOOT_H

#include <stdint.h>

#include <efi.h>

#define AXBOOT_VERSTR L"0.1"
#define AXBOOT_COPYRIGHT_NOTICESTR L"Copyright (c) 2023-2024 AurixOS"

extern EFI_HANDLE g_ImageHandle;
extern EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle,
		 EFI_SYSTEM_TABLE *SystemTable);

#endif /* __AXBOOT_H */
