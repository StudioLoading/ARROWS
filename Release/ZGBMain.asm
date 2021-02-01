;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module ZGBMain
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _GetTileReplacement
	.globl _next_state
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_next_state::
	.ds 1
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
;ZGBMain.c:4: UINT8 next_state = StateGame;
	ld	hl, #_next_state
	ld	(hl), #0x00
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;ZGBMain.c:6: UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
;	---------------------------------
; Function GetTileReplacement
; ---------------------------------
_GetTileReplacement::
;ZGBMain.c:17: return 255u;
	ld	e, #0xff
;ZGBMain.c:18: }
	ret
	.area _CODE
	.area _CABS (ABS)
