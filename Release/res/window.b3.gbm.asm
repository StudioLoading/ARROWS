;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module window_b3_gbm
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _window_internal
	.globl _window_map
	.globl _empty
	.globl _window
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
_window:
	.db #0x03	; 3
	.dw _window_internal
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
;../res/src/window.b3.gbm.c:3: void empty(void) __nonbanked {}
;	---------------------------------
; Function empty
; ---------------------------------
_empty::
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_3
	.area _CODE_3
_window_map:
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x21	; 33
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x23	; 35
	.db #0x08	; 8
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
	.db #0x23	; 35
_window_internal:
	.dw _window_map
	.db #0x14	; 20
	.db #0x04	; 4
	.dw #0x0000
	.dw _tiles
	.area _CABS (ABS)
