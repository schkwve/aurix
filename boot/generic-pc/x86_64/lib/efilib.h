#ifndef EFILIB_H
#define EFILIB_H

#include "efi.h"

#define EFI_ERROR(Status)								(((INTN)(EFI_STATUS)(Status)) < 0)

#endif /* EFILIB_H */
