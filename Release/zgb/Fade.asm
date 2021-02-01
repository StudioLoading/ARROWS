;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Fade
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _FadeOut_b
	.globl _FadeIn_b
	.globl _PopBank
	.globl _PushBank
	.globl _FadeIn
	.globl _FadeOut
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
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
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;C:/GB/ZGB/common/src/Fade.c:5: void FadeIn() {
;	---------------------------------
; Function FadeIn
; ---------------------------------
_FadeIn::
;C:/GB/ZGB/common/src/Fade.c:6: PUSH_BANK(fade_bank);
	ld	hl, #_fade_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Fade.c:7: FadeIn_b();
	call	_FadeIn_b
;C:/GB/ZGB/common/src/Fade.c:8: POP_BANK;
;C:/GB/ZGB/common/src/Fade.c:9: }
	jp	_PopBank
;C:/GB/ZGB/common/src/Fade.c:12: void FadeOut() {
;	---------------------------------
; Function FadeOut
; ---------------------------------
_FadeOut::
;C:/GB/ZGB/common/src/Fade.c:13: PUSH_BANK(fade_bank);
	ld	hl, #_fade_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Fade.c:14: FadeOut_b();
	call	_FadeOut_b
;C:/GB/ZGB/common/src/Fade.c:15: POP_BANK;
;C:/GB/ZGB/common/src/Fade.c:16: }
	jp	_PopBank
	.area _CODE
	.area _CABS (ABS)
