;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Frame_b
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _DrawFrame32x32
	.globl _FlushOAMSprite
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
	.area _CODE_1
;C:/GB/ZGB/common/src/Frame_b.c:5: void DrawFrame32x32(int idx, UINT8 x, UINT8 y, UINT8 flags) BANKED {
;	---------------------------------
; Function DrawFrame32x32
; ---------------------------------
_DrawFrame32x32::
;C:/GB/ZGB/common/src/Frame_b.c:6: if(flags & 32){
	ldhl	sp,	#10
	ld	c, (hl)
;C:/GB/ZGB/common/src/Frame_b.c:7: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx + 6u; next_oam_sprite_flags = flags; FlushOAMSprite();
	dec	hl
	ld	a, (hl)
	add	a, #0x10
	ld	b, a
	dec	hl
	ld	a, (hl)
	add	a, #0x08
	ld	e, a
;C:/GB/ZGB/common/src/Frame_b.c:6: if(flags & 32){
	bit	5, c
	jp	Z,00102$
;C:/GB/ZGB/common/src/Frame_b.c:7: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx + 6u; next_oam_sprite_flags = flags; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_y
	ld	(hl), b
	ld	hl, #_next_oam_sprite_x
	ld	(hl), e
	ldhl	sp,	#6
	ld	a, (hl)
	add	a, #0x06
	ld	hl, #_next_oam_sprite_idx
	ld	(hl), a
	ld	hl, #_next_oam_sprite_flags
	ld	(hl), c
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:8: next_oam_sprite_x += 8u; next_oam_sprite_idx -= 2u;	FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	dec	(hl)
	dec	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:9: next_oam_sprite_x += 8u; next_oam_sprite_idx -= 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	dec	(hl)
	dec	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:10: next_oam_sprite_x += 8u; next_oam_sprite_idx -= 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	dec	(hl)
	dec	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:12: next_oam_sprite_y += 16u; next_oam_sprite_x -= 24u; next_oam_sprite_idx += 14u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_y
	ld	a, (hl)
	add	a, #0x10
	ld	(hl), a
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0xe8
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	ld	a, (hl)
	add	a, #0x0e
	ld	(hl), a
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:13: next_oam_sprite_x += 8u; next_oam_sprite_idx -= 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	dec	(hl)
	dec	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:14: next_oam_sprite_x += 8u; next_oam_sprite_idx -= 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	dec	(hl)
	dec	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:15: next_oam_sprite_x += 8u; next_oam_sprite_idx -= 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	dec	(hl)
	dec	(hl)
	jp	_FlushOAMSprite
00102$:
;C:/GB/ZGB/common/src/Frame_b.c:17: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx; next_oam_sprite_flags = flags; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_y
	ld	(hl), b
	ld	hl, #_next_oam_sprite_x
	ld	(hl), e
	push	hl
	ldhl	sp,	#8
	ld	a, (hl)
	ld	hl, #_next_oam_sprite_idx
	ld	(hl), a
	pop	hl
	ld	hl, #_next_oam_sprite_flags
	ld	(hl), c
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:18: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:19: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:20: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:22: next_oam_sprite_y += 16u; next_oam_sprite_x -= 24u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_y
	ld	a, (hl)
	add	a, #0x10
	ld	(hl), a
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0xe8
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:23: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:24: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame_b.c:25: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
;C:/GB/ZGB/common/src/Frame_b.c:27: }
	jp	_FlushOAMSprite
	.area _CODE_1
	.area _CABS (ABS)
