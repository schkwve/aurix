;;
; @file		kernel/arch/cpu/gdt.asm
; @brief	GDT-related functions
;

;;
; @brief	Loads GDTR from gdtr parameter and reloads segment registers.
;
; @param	[rdi] gdtr
;			GDTR structure which will be loaded.
;
global gdt_load
gdt_load:
	lgdt [rdi]
	push 0x08
	lea rax, [rel .relcs]
	push rax
	retfq
.relcs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret

;;
; @brief	Saves current GDTR to the supplied variable.
;
; @param	[rdi] gdtr
;			Pointer to GDTR structure where the GDTR will be saved.
;
global gdt_save
gdt_save:
	sgdt [rdi]
	ret
