;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module porcupine_b3_gbr
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _porcupine_internal
	.globl _porcupine_tiles
	.globl _empty
	.globl _porcupine
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
_porcupine:
	.db #0x03	; 3
	.dw _porcupine_internal
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
;../res/src/porcupine.b3.gbr.c:3: void empty(void) __nonbanked {}
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
_porcupine_tiles:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x54	; 84	'T'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x50	; 80	'P'
	.db #0x50	; 80	'P'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x54	; 84	'T'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x28	; 40
	.db #0x28	; 40
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x50	; 80	'P'
	.db #0x50	; 80	'P'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x11	; 17
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0x2a	; 42
	.db #0x3b	; 59
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x50	; 80	'P'
	.db #0x50	; 80	'P'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x11	; 17
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x54	; 84	'T'
	.db #0x2a	; 42
	.db #0x3b	; 59
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x50	; 80	'P'
	.db #0x50	; 80	'P'
	.db #0x50	; 80	'P'
	.db #0x50	; 80	'P'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x54	; 84	'T'
	.db #0x54	; 84	'T'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x54	; 84	'T'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x54	; 84	'T'
	.db #0x5e	; 94
	.db #0xaa	; 170
	.db #0xad	; 173
	.db #0x50	; 80	'P'
	.db #0x7e	; 126
	.db #0xa4	; 164
	.db #0xfc	; 252
	.db #0x48	; 72	'H'
	.db #0x70	; 112	'p'
	.db #0x10	; 16
	.db #0x60	; 96
	.db #0x20	; 32
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x02	; 2
	.db #0x02	; 2
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0xaa	; 170
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0xae	; 174
	.db #0xfe	; 254
	.db #0x47	; 71	'G'
	.db #0x7b	; 123
	.db #0x90	; 144
	.db #0xec	; 236
	.db #0x38	; 56	'8'
	.db #0xc8	; 200
	.db #0xc0	; 192
	.db #0xc0	; 192
_porcupine_internal:
	.db #0x08	; 8
	.db #0x10	; 16
	.db #0x08	; 8
	.dw _porcupine_tiles
	.dw #0x0000
	.area _CABS (ABS)
