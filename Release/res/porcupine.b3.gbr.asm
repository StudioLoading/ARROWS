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
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x56	; 86	'V'
	.db #0x01	; 1
	.db #0xa5	; 165
	.db #0x0a	; 10
	.db #0x6a	; 106	'j'
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x2f	; 47
	.db #0x50	; 80	'P'
	.db #0x1c	; 28
	.db #0x20	; 32
	.db #0x38	; 56	'8'
	.db #0x01	; 1
	.db #0x14	; 20
	.db #0x0a	; 10
	.db #0x0c	; 12
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0xa0	; 160
	.db #0x00	; 0
	.db #0x90	; 144
	.db #0x40	; 64
	.db #0x40	; 64
	.db #0xa8	; 168
	.db #0xac	; 172
	.db #0x50	; 80	'P'
	.db #0xfa	; 250
	.db #0x04	; 4
	.db #0xfe	; 254
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x38	; 56	'8'
	.db #0x40	; 64
	.db #0x40	; 64
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
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x56	; 86	'V'
	.db #0x01	; 1
	.db #0xa5	; 165
	.db #0x0a	; 10
	.db #0x6a	; 106	'j'
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x2f	; 47
	.db #0x50	; 80	'P'
	.db #0x5c	; 92
	.db #0xa0	; 160
	.db #0x38	; 56	'8'
	.db #0x41	; 65	'A'
	.db #0x14	; 20
	.db #0x6a	; 106	'j'
	.db #0x74	; 116	't'
	.db #0x68	; 104	'h'
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0xa0	; 160
	.db #0x00	; 0
	.db #0x90	; 144
	.db #0x40	; 64
	.db #0x40	; 64
	.db #0xa8	; 168
	.db #0xac	; 172
	.db #0x50	; 80	'P'
	.db #0xfa	; 250
	.db #0x04	; 4
	.db #0xfe	; 254
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x50	; 80	'P'
	.db #0x40	; 64
	.db #0x50	; 80	'P'
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x05	; 5
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x25	; 37
	.db #0x55	; 85	'U'
	.db #0x02	; 2
	.db #0x2a	; 42
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0x0a	; 10
	.db #0xab	; 171
	.db #0x54	; 84	'T'
	.db #0x55	; 85	'U'
	.db #0x2a	; 42
	.db #0xaa	; 170
	.db #0x54	; 84	'T'
	.db #0x15	; 21
	.db #0x68	; 104	'h'
	.db #0xa9	; 169
	.db #0x50	; 80	'P'
	.db #0x5a	; 90	'Z'
	.db #0x20	; 32
	.db #0x2c	; 44
	.db #0x08	; 8
	.db #0x18	; 24
	.db #0x18	; 24
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x12	; 18
	.db #0xcc	; 204
	.db #0x00	; 0
	.db #0x6c	; 108	'l'
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x32	; 50	'2'
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0x80	; 128
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
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x05	; 5
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x25	; 37
	.db #0x55	; 85	'U'
	.db #0x02	; 2
	.db #0x2a	; 42
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0x0a	; 10
	.db #0xab	; 171
	.db #0x54	; 84	'T'
	.db #0x55	; 85	'U'
	.db #0x2a	; 42
	.db #0xaa	; 170
	.db #0x54	; 84	'T'
	.db #0x15	; 21
	.db #0x68	; 104	'h'
	.db #0xa9	; 169
	.db #0x50	; 80	'P'
	.db #0x5a	; 90	'Z'
	.db #0x20	; 32
	.db #0x2c	; 44
	.db #0x08	; 8
	.db #0x18	; 24
	.db #0x18	; 24
	.db #0x80	; 128
	.db #0x21	; 33
	.db #0x40	; 64
	.db #0x12	; 18
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x32	; 50	'2'
	.db #0xd0	; 208
	.db #0x21	; 33
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0x80	; 128
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
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x05	; 5
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x25	; 37
	.db #0x55	; 85	'U'
	.db #0x02	; 2
	.db #0x2a	; 42
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0x0a	; 10
	.db #0xab	; 171
	.db #0x54	; 84	'T'
	.db #0x55	; 85	'U'
	.db #0x2a	; 42
	.db #0xaa	; 170
	.db #0x54	; 84	'T'
	.db #0x15	; 21
	.db #0x68	; 104	'h'
	.db #0xa9	; 169
	.db #0x50	; 80	'P'
	.db #0x5a	; 90	'Z'
	.db #0x20	; 32
	.db #0x3e	; 62
	.db #0x12	; 18
	.db #0x36	; 54	'6'
	.db #0x36	; 54	'6'
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x80	; 128
	.db #0xd0	; 208
	.db #0x20	; 32
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0xf0	; 240
	.db #0x10	; 16
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0xe0	; 224
	.db #0x60	; 96
	.db #0x80	; 128
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
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x74	; 116	't'
	.db #0x68	; 104	'h'
	.db #0x14	; 20
	.db #0x6a	; 106	'j'
	.db #0x38	; 56	'8'
	.db #0x41	; 65	'A'
	.db #0x5c	; 92
	.db #0xa0	; 160
	.db #0x2f	; 47
	.db #0x50	; 80	'P'
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x6a	; 106	'j'
	.db #0x15	; 21
	.db #0x25	; 37
	.db #0x0a	; 10
	.db #0x1a	; 26
	.db #0x00	; 0
	.db #0x05	; 5
	.db #0x00	; 0
	.db #0x02	; 2
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
	.db #0x40	; 64
	.db #0x40	; 64
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x50	; 80	'P'
	.db #0x20	; 32
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0x80	; 128
	.db #0xa8	; 168
	.db #0x40	; 64
	.db #0x54	; 84	'T'
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x10	; 16
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x00	; 0
	.db #0x15	; 21
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x05	; 5
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0x0a	; 10
	.db #0x25	; 37
	.db #0x55	; 85	'U'
	.db #0x02	; 2
	.db #0x2a	; 42
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0x0a	; 10
	.db #0xab	; 171
	.db #0x54	; 84	'T'
	.db #0x55	; 85	'U'
	.db #0x2a	; 42
	.db #0xaa	; 170
	.db #0x54	; 84	'T'
	.db #0x15	; 21
	.db #0x68	; 104	'h'
	.db #0xa9	; 169
	.db #0x50	; 80	'P'
	.db #0x5a	; 90	'Z'
	.db #0x20	; 32
	.db #0x3e	; 62
	.db #0x12	; 18
	.db #0x36	; 54	'6'
	.db #0x36	; 54	'6'
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x80	; 128
	.db #0xd0	; 208
	.db #0x20	; 32
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0xf0	; 240
	.db #0x10	; 16
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0xe0	; 224
	.db #0x60	; 96
	.db #0x80	; 128
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
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x05	; 5
	.db #0x00	; 0
	.db #0x1a	; 26
	.db #0x00	; 0
	.db #0x25	; 37
	.db #0x0a	; 10
	.db #0x6a	; 106	'j'
	.db #0x15	; 21
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x2f	; 47
	.db #0x50	; 80	'P'
	.db #0x5c	; 92
	.db #0xa0	; 160
	.db #0x38	; 56	'8'
	.db #0x41	; 65	'A'
	.db #0x14	; 20
	.db #0x6a	; 106	'j'
	.db #0x74	; 116	't'
	.db #0x68	; 104	'h'
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x10	; 16
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x54	; 84	'T'
	.db #0x00	; 0
	.db #0xa8	; 168
	.db #0x40	; 64
	.db #0x30	; 48	'0'
	.db #0x80	; 128
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x50	; 80	'P'
	.db #0x20	; 32
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
_porcupine_internal:
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x08	; 8
	.dw _porcupine_tiles
	.dw #0x0000
	.area _CABS (ABS)
