;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Frame
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _DrawFrame32x32
	.globl _FlushOAMSprite
	.globl _DrawFrame
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
;C:/GB/ZGB/common/src/Frame.c:12: void DrawFrame(FrameSize size, int idx, UINT8 x, UINT8 y, UINT8 flags){
;	---------------------------------
; Function DrawFrame
; ---------------------------------
_DrawFrame::
;C:/GB/ZGB/common/src/Frame.c:22: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx; next_oam_sprite_flags = flags; FlushOAMSprite();
	ldhl	sp,	#6
	ld	a, (hl)
	add	a, #0x10
	ld	c, a
	dec	hl
	ld	a, (hl)
	add	a, #0x08
	ld	b, a
	dec	hl
	dec	hl
	ld	e, (hl)
	ldhl	sp,	#7
	ld	d, (hl)
;C:/GB/ZGB/common/src/Frame.c:19: switch(size) {
	ldhl	sp,	#2
	ld	a, (hl)
	or	a, a
	jr	Z,00102$
	ldhl	sp,	#2
	ld	a, (hl)
	dec	a
	jr	Z,00102$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x02
	jr	Z,00103$
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00107$
	ret
;C:/GB/ZGB/common/src/Frame.c:21: case FRAME_8x16:
00102$:
;C:/GB/ZGB/common/src/Frame.c:22: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx; next_oam_sprite_flags = flags; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_y
	ld	(hl), c
	ld	hl, #_next_oam_sprite_x
	ld	(hl), b
	ld	hl, #_next_oam_sprite_idx
	ld	(hl), e
	ld	hl, #_next_oam_sprite_flags
	ld	(hl), d
;C:/GB/ZGB/common/src/Frame.c:23: break;
	jp	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame.c:25: case FRAME_16x16:
00103$:
;C:/GB/ZGB/common/src/Frame.c:26: if(flags & 32){
	bit	5, d
	jr	Z,00105$
;C:/GB/ZGB/common/src/Frame.c:27: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx + 2u; next_oam_sprite_flags = flags; FlushOAMSprite();				
	ld	hl, #_next_oam_sprite_y
	ld	(hl), c
	ld	hl, #_next_oam_sprite_x
	ld	(hl), b
	ldhl	sp,	#3
	ld	a, (hl)
	add	a, #0x02
	ld	hl, #_next_oam_sprite_idx
	ld	(hl), a
	ld	hl, #_next_oam_sprite_flags
	ld	(hl), d
	push	de
	call	_FlushOAMSprite
	pop	de
;C:/GB/ZGB/common/src/Frame.c:28: next_oam_sprite_x += 8u; next_oam_sprite_idx = idx; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	ld	(hl), e
	jp	_FlushOAMSprite
00105$:
;C:/GB/ZGB/common/src/Frame.c:30: next_oam_sprite_y = y + 16u; next_oam_sprite_x = x + 8u; next_oam_sprite_idx = idx; next_oam_sprite_flags = flags; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_y
	ld	(hl), c
	ld	hl, #_next_oam_sprite_x
	ld	(hl), b
	ld	hl, #_next_oam_sprite_idx
	ld	(hl), e
	ld	hl, #_next_oam_sprite_flags
	ld	(hl), d
	call	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame.c:31: next_oam_sprite_x += 8u; next_oam_sprite_idx += 2u; FlushOAMSprite();
	ld	hl, #_next_oam_sprite_x
	ld	a, (hl)
	add	a, #0x08
	ld	(hl), a
	ld	hl, #_next_oam_sprite_idx
	inc	(hl)
	inc	(hl)
;C:/GB/ZGB/common/src/Frame.c:33: break;
	jp	_FlushOAMSprite
;C:/GB/ZGB/common/src/Frame.c:35: case FRAME_32x32:
00107$:
;C:/GB/ZGB/common/src/Frame.c:36: DrawFrame32x32(idx, x, y, flags);
	ldhl	sp,	#7
	ld	a, (hl)
	push	af
	inc	sp
	dec	hl
	ld	a, (hl)
	push	af
	inc	sp
	dec	hl
	ld	a, (hl)
	push	af
	inc	sp
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	banked_call
	.dw	_DrawFrame32x32
	.dw 0     ; PENDING: bank support
	add	sp, #5
;C:/GB/ZGB/common/src/Frame.c:38: }
;C:/GB/ZGB/common/src/Frame.c:39: }
	ret
	.area _CODE
	.area _CABS (ABS)
