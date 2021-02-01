;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module BankManager
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _bank_stack
	.globl _bank_stackSTACK
	.globl _PushBank
	.globl _PopBank
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_bank_stackSTACK::
	.ds 10
_bank_stack::
	.ds 2
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;C:/GB/ZGB/common/src/BankManager.c:3: DECLARE_STACK(bank_stack, N_PUSH_BANKS);
	ld	hl, #_bank_stack
	ld	(hl), #<((_bank_stackSTACK - 0x0001))
	inc	hl
	ld	(hl), #>((_bank_stackSTACK - 0x0001))
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;C:/GB/ZGB/common/src/BankManager.c:7: void PushBank(UINT8 b) {
;	---------------------------------
; Function PushBank
; ---------------------------------
_PushBank::
;C:/GB/ZGB/common/src/BankManager.c:25: __endasm;
	ld	hl, #_bank_stack
	inc	(hl)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (#__current_bank)
	ld	(bc), a
	ldhl	sp, #2
	ld	a, (hl)
	ld	(#__current_bank), a
	ld	(#0x2000), a
;C:/GB/ZGB/common/src/BankManager.c:26: }
	ret
;C:/GB/ZGB/common/src/BankManager.c:28: void PopBank() {
;	---------------------------------
; Function PopBank
; ---------------------------------
_PopBank::
;C:/GB/ZGB/common/src/BankManager.c:42: __endasm;
	ld	hl, #_bank_stack
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	ld	(#__current_bank), a
	ld	(#0x2000), a
	dec	hl
	dec	(hl)
;C:/GB/ZGB/common/src/BankManager.c:43: }
	ret
	.area _CODE
	.area _CABS (ABS)
