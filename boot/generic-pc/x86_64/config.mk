override BOOT_FILE := BOOTX64.EFI

override INCLUDE_DIRS := lib/Include lib/Include/X64 include

override AS := nasm
override CC := clang
override LD := clang

EDK2_OPTS_BOOL := PcdVerifyNodeInList=FALSE
EDK2_OPTS_BOOL += PcdComponentNameDisable=FALSE
EDK2_OPTS_BOOL += PcdDriverDiagnostics2Disable=FALSE
EDK2_OPTS_BOOL += PcdComponentName2Disable=FALSE
EDK2_OPTS_BOOL += PcdDriverDiagnosticsDisable=FALSE
EDK2_OPTS_BOOL += PcdUgaConsumeSupport=TRUE

EDK2_OPTS_UINT32 := PcdMaximumLinkedListLength=1000000
EDK2_OPTS_UINT32 += PcdMaximumUnicodeStringLength=1000000
EDK2_OPTS_UINT32 += PcdMaximumAsciiStringLength=1000000
EDK2_OPTS_UINT32 += PcdSpinLockTimeout=10000000
EDK2_OPTS_UINT32 += PcdFixedDebugPrintErrorLevel=0xFFFFFFFF
EDK2_OPTS_UINT32 += PcdDebugPrintErrorLevel=0xFFFFFFFF
EDK2_OPTS_UINT32 += PcdUefiLibMaxPrintBufferSize=320
EDK2_OPTS_UINT32 += PcdMaximumDevicePathNodeCount=0
EDK2_OPTS_UINT32 += PcdCpuLocalApicBaseAddress=0xfee00000
EDK2_OPTS_UINT32 += PcdCpuInitIpiDelayInMicroSeconds=10000

EDK2_OPTS_UINT16 := PcdUefiFileHandleLibPrintBufferSize=1536

EDK2_OPTS_UINT8 := PcdSpeculationBarrierType=0x1
EDK2_OPTS_UINT8 += PcdDebugPropertyMask=DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED
EDK2_OPTS_UINT8 += PcdDebugClearMemoryValue=0xAF

override INTERNAL_ASFLAGS := -fwin64

override INTERNAL_CFLAGS := -target x86_64-unknown-windows \
							-fno-delayed-template-parsing \
							$(foreach d, $(INCLUDE_DIRS), -I$d) \
							-DgEfiCallerBaseName=\"AxBoot\" \
							$(EDK2_OPTS_UINT32:%=-D_PCD_GET_MODE_32_%) \
							$(EDK2_OPTS_UINT16:%=-D_PCD_GET_MODE_16_%) \
							$(EDK2_OPTS_UINT8:%=-D_PCD_GET_MODE_8_%) \
							$(EDK2_OPTS_BOOL:%=-D_PCD_GET_MODE_BOOL_%) \

override INTERNAL_LDFLAGS := -target x86_64-unknown-windows \
							-nostdlib \
							-fuse-ld=lld-link \
							-Wl,-subsystem:efi_application \
							-Wl,-entry:efi_main
