;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Vector
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _memcpy
	.globl _VectorAdd
	.globl _VectorRemovePos
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
;C:/GB/ZGB/common/src/Vector.c:5: void VectorAdd(UINT8* v, UINT8 elem) {
;	---------------------------------
; Function VectorAdd
; ---------------------------------
_VectorAdd::
;C:/GB/ZGB/common/src/Vector.c:6: v[++ v[0]] = elem;
	ldhl	sp,#(3 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	inc	a
	ld	(bc), a
	add	a, c
	ld	c, a
	ld	a, #0x00
	adc	a, b
	ld	b, a
	inc	hl
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/Vector.c:7: }
	ret
;C:/GB/ZGB/common/src/Vector.c:9: void VectorRemovePos(UINT8* v, UINT8 pos) {
;	---------------------------------
; Function VectorRemovePos
; ---------------------------------
_VectorRemovePos::
	add	sp, #-8
;C:/GB/ZGB/common/src/Vector.c:10: memcpy(&v[pos + 1], &v[pos + 2], v[0] - pos);
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#12
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl-), a
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	inc	hl
	inc	hl
	ld	(hl-), a
	ld	(hl), e
	dec	hl
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	pop	hl
	push	hl
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#6
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ldhl	sp,#(3 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	pop	hl
	push	hl
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_memcpy
	add	sp, #6
;C:/GB/ZGB/common/src/Vector.c:11: v[0] --;
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	dec	c
	pop	hl
	push	hl
	ld	(hl), c
;C:/GB/ZGB/common/src/Vector.c:12: }
	add	sp, #8
	ret
	.area _CODE
	.area _CABS (ABS)
