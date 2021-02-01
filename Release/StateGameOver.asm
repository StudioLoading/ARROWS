;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module StateGameOver
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Update_StateGameOver
	.globl _Start_StateGameOver
	.globl _InitScroll
	.globl _SetState
	.globl _empty
	.globl _bank_StateGameOver
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; CODE rom data
;--------------------------------------------------------
	.area _CODE
_bank_StateGameOver:
	.db #0x02	; 2
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
;C:/GB/ZGB/common/include/Banks/SetBankCommon.h:4: void empty(void) __nonbanked {}
;	---------------------------------
; Function empty
; ---------------------------------
_empty::
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_2
;StateGameOver.c:11: void Start_StateGameOver() {
;	---------------------------------
; Function Start_StateGameOver
; ---------------------------------
_Start_StateGameOver::
;StateGameOver.c:12: InitScroll(&mapgameover, 0, 0);
	ld	hl, #0x0000
	push	hl
	ld	l, #0x00
	push	hl
	ld	hl, #_mapgameover
	push	hl
	call	_InitScroll
	add	sp, #6
;StateGameOver.c:13: SHOW_BKG;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x01
	ldh	(_LCDC_REG+0),a
;StateGameOver.c:14: }
	ret
;StateGameOver.c:16: void Update_StateGameOver() {
;	---------------------------------
; Function Update_StateGameOver
; ---------------------------------
_Update_StateGameOver::
;StateGameOver.c:17: if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
	ld	hl, #_keys
	ld	a, (hl)
	rlc	a
	and	a, #0x01
	bit	0, a
	jr	Z,00105$
	ld	hl, #_previous_keys
	ld	a, (hl)
	rlc	a
	and	a, #0x01
	bit	0, a
	jr	Z,00106$
00105$:
	ld	c, #0x00
	jr	00107$
00106$:
	ld	c, #0x01
00107$:
	ld	hl, #_keys
	ld	d, (hl)
	ld	hl, #_previous_keys
	ld	b, (hl)
	ld	e, #0x00
	bit	4, d
	jr	Z,00108$
	bit	4, b
	jr	Z,00109$
00108$:
	xor	a, a
	jr	00110$
00109$:
	ld	a, #0x01
00110$:
	or	a, c
	ld	c, a
	bit	5, d
	jr	Z,00111$
	bit	5, b
	jr	Z,00112$
00111$:
	xor	a, a
	jr	00113$
00112$:
	ld	a, #0x01
00113$:
	or	a, c
	bit	0, a
	ret	Z
;StateGameOver.c:18: SetState(StateGame);
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
;StateGameOver.c:20: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
