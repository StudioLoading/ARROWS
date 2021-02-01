;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module enemy_b3_gbr
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _enemy_internal
	.globl _enemy_tiles
	.globl _empty
	.globl _enemy
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
_enemy:
	.db #0x03	; 3
	.dw _enemy_internal
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
;../res/src/enemy.b3.gbr.c:3: void empty(void) __nonbanked {}
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
_enemy_tiles:
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
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x1e	; 30
	.db #0x1a	; 26
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x1a	; 26
	.db #0x1a	; 26
	.db #0x98	; 152
	.db #0x00	; 0
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x9c	; 156
	.db #0x10	; 16
	.db #0x8e	; 142
	.db #0x8e	; 142
	.db #0xff	; 255
	.db #0x6d	; 109	'm'
	.db #0x7f	; 127
	.db #0x33	; 51	'3'
	.db #0x2a	; 42
	.db #0x2a	; 42
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
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x1e	; 30
	.db #0x1a	; 26
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x1a	; 26
	.db #0x1a	; 26
	.db #0x58	; 88	'X'
	.db #0x00	; 0
	.db #0x58	; 88	'X'
	.db #0x58	; 88	'X'
	.db #0x5c	; 92
	.db #0x10	; 16
	.db #0x46	; 70	'F'
	.db #0x46	; 70	'F'
	.db #0x7f	; 127
	.db #0x2d	; 45
	.db #0x3f	; 63
	.db #0x13	; 19
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x1e	; 30
	.db #0x1a	; 26
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x1a	; 26
	.db #0x1a	; 26
	.db #0x98	; 152
	.db #0x00	; 0
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x9c	; 156
	.db #0x10	; 16
	.db #0x8e	; 142
	.db #0x8e	; 142
	.db #0xff	; 255
	.db #0x6d	; 109	'm'
	.db #0x7f	; 127
	.db #0x33	; 51	'3'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x11	; 17
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x0c	; 12
	.db #0x1d	; 29
	.db #0x1f	; 31
	.db #0x1b	; 27
	.db #0x0e	; 14
	.db #0x0e	; 14
	.db #0x1c	; 28
	.db #0x1c	; 28
	.db #0x9a	; 154
	.db #0x02	; 2
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x9c	; 156
	.db #0x10	; 16
	.db #0x8e	; 142
	.db #0x8e	; 142
	.db #0xff	; 255
	.db #0x6d	; 109	'm'
	.db #0x7f	; 127
	.db #0x33	; 51	'3'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x11	; 17
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0x1d	; 29
	.db #0x1e	; 30
	.db #0x1a	; 26
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x1a	; 26
	.db #0x1a	; 26
	.db #0x98	; 152
	.db #0x00	; 0
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x9c	; 156
	.db #0x10	; 16
	.db #0x8e	; 142
	.db #0x8e	; 142
	.db #0xff	; 255
	.db #0x6d	; 109	'm'
	.db #0x7f	; 127
	.db #0x33	; 51	'3'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x0e	; 14
	.db #0x0e	; 14
	.db #0x0f	; 15
	.db #0x0b	; 11
	.db #0x1e	; 30
	.db #0x1e	; 30
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x18	; 24
	.db #0x18	; 24
	.db #0x98	; 152
	.db #0x00	; 0
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x9c	; 156
	.db #0x10	; 16
	.db #0x8e	; 142
	.db #0x8e	; 142
	.db #0xff	; 255
	.db #0x6d	; 109	'm'
	.db #0x7f	; 127
	.db #0x33	; 51	'3'
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x2a	; 42
	.db #0x7f	; 127
	.db #0x33	; 51	'3'
	.db #0xff	; 255
	.db #0x6d	; 109	'm'
	.db #0x8e	; 142
	.db #0x8e	; 142
	.db #0x9c	; 156
	.db #0x10	; 16
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x98	; 152
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x18	; 24
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x1e	; 30
	.db #0x1e	; 30
	.db #0x0f	; 15
	.db #0x0b	; 11
	.db #0x0e	; 14
	.db #0x0e	; 14
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
_enemy_internal:
	.db #0x08	; 8
	.db #0x10	; 16
	.db #0x07	; 7
	.dw _enemy_tiles
	.dw #0x0000
	.area _CABS (ABS)
