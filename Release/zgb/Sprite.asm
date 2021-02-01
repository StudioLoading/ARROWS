;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Sprite
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _SpriteManagerRemove
	.globl _PopBank
	.globl _PushBank
	.globl _GetScrollTilePtr
	.globl _DrawFrame
	.globl _tile_coll
	.globl _InitSprite
	.globl _SetSpriteAnim
	.globl _DrawSprite
	.globl _TranslateSprite
	.globl _CheckCollision
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_tile_coll::
	.ds 2
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
;C:/GB/ZGB/common/src/Sprite.c:6: void InitSprite(struct Sprite* sprite, FrameSize size, UINT8 first_tile) {
;	---------------------------------
; Function InitSprite
; ---------------------------------
_InitSprite::
	add	sp, #-4
;C:/GB/ZGB/common/src/Sprite.c:7: sprite->size = size;
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ldhl	sp,	#8
	ld	a, (hl)
	ld	(de), a
;C:/GB/ZGB/common/src/Sprite.c:8: sprite->first_tile = first_tile;
	pop	bc
	push	bc
	inc	bc
	inc	hl
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:9: sprite->anim_data = 0u;
	pop	bc
	push	bc
	inc	bc
	inc	bc
	xor	a, a
	ld	(bc), a
	inc	bc
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:10: SET_FRAME(sprite, 0);
	pop	de
	push	de
	ld	hl, #0x0006
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
	pop	de
	push	de
	ld	hl, #0x0007
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#8
	ld	d, (hl)
	ld	e, #0x00
	inc	d
	jr	00129$
00128$:
	sla	e
00129$:
	dec	d
	jr	NZ,00128$
	inc	hl
	ld	a, (hl)
	add	a, e
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:11: sprite->anim_speed = 33u;
	pop	de
	push	de
	ld	hl, #0x0005
	add	hl, de
	ld	c,l
	ld	a,h
	ld	(hl), #0x21
;C:/GB/ZGB/common/src/Sprite.c:13: sprite->x = 0;
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
	inc	bc
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:14: sprite->y = 0;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
	inc	bc
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:16: sprite->coll_x = 0u;
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:17: sprite->coll_y = 0u;
	pop	de
	push	de
	ld	hl, #0x000e
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:19: case FRAME_8x8:   sprite->coll_w =  8u; sprite->coll_h =  8u; break;
	pop	de
	push	de
	ld	hl, #0x000f
	add	hl, de
	ld	c, l
	ld	b, h
	pop	de
	push	de
	ld	hl, #0x0010
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:18: switch(size) {
	ldhl	sp,	#8
	ld	a, (hl)
	or	a, a
	jr	Z,00101$
	ldhl	sp,	#8
	ld	a, (hl)
	dec	a
	jr	Z,00102$
	ldhl	sp,	#8
	ld	a, (hl)
	sub	a, #0x02
	jr	Z,00103$
	ldhl	sp,	#8
	ld	a, (hl)
	sub	a, #0x04
	jr	Z,00104$
	jp	00106$
;C:/GB/ZGB/common/src/Sprite.c:19: case FRAME_8x8:   sprite->coll_w =  8u; sprite->coll_h =  8u; break;
00101$:
	ld	a, #0x08
	ld	(bc), a
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x08
	jr	00106$
;C:/GB/ZGB/common/src/Sprite.c:20: case FRAME_8x16:  sprite->coll_w =  8u; sprite->coll_h = 16u; break;
00102$:
	ld	a, #0x08
	ld	(bc), a
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x10
	jr	00106$
;C:/GB/ZGB/common/src/Sprite.c:21: case FRAME_16x16: sprite->coll_w = 16u; sprite->coll_h = 16u; break;
00103$:
	ld	a, #0x10
	ld	(bc), a
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x10
	jr	00106$
;C:/GB/ZGB/common/src/Sprite.c:22: case FRAME_32x32: sprite->coll_w = 32u; sprite->coll_h = 32u; break;
00104$:
	ld	a, #0x20
	ld	(bc), a
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x20
;C:/GB/ZGB/common/src/Sprite.c:23: }
00106$:
;C:/GB/ZGB/common/src/Sprite.c:24: }
	add	sp, #4
	ret
;C:/GB/ZGB/common/src/Sprite.c:26: void SetSpriteAnim(struct Sprite* sprite, UINT8* data, UINT8 speed) {
;	---------------------------------
; Function SetSpriteAnim
; ---------------------------------
_SetSpriteAnim::
	add	sp, #-5
;C:/GB/ZGB/common/src/Sprite.c:27: if(sprite->anim_data !=  data) {
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	bc
	push	bc
	inc	bc
	inc	bc
	ld	e, c
	ld	d, b
	ld	a,(de)
	inc	hl
	inc	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#9
	ld	a, (hl)
	ldhl	sp,	#3
	sub	a, (hl)
	jr	NZ,00110$
	ldhl	sp,	#10
	ld	a, (hl)
	ldhl	sp,	#4
	sub	a, (hl)
	jp	Z,00103$
00110$:
;C:/GB/ZGB/common/src/Sprite.c:28: sprite->anim_data = data;
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	(bc), a
	inc	bc
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:29: sprite->anim_frame = 0;
	pop	de
	push	de
	ld	hl, #0x0006
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:30: sprite->frame = sprite->first_tile + (data[1] << sprite->size);
	pop	de
	push	de
	ld	hl, #0x0007
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
	pop	bc
	push	bc
	inc	bc
	ld	a, (bc)
	inc	hl
	ld	(hl), a
	ldhl	sp,#(10 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, (bc)
	ld	c, a
	pop	de
	push	de
	ld	a,(de)
	inc	a
	jr	00112$
00111$:
	sla	c
00112$:
	dec	a
	jr	NZ,00111$
	ldhl	sp,	#4
	ld	a, (hl)
	add	a, c
	ld	c, a
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Sprite.c:31: sprite->anim_accum_ticks = 0;
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:32: sprite->anim_speed = speed;
	pop	de
	push	de
	ld	hl, #0x0005
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#11
	ld	a, (hl)
	ld	(bc), a
00103$:
;C:/GB/ZGB/common/src/Sprite.c:34: }
	add	sp, #5
	ret
;C:/GB/ZGB/common/src/Sprite.c:39: void DrawSprite() {
;	---------------------------------
; Function DrawSprite
; ---------------------------------
_DrawSprite::
	add	sp, #-8
;C:/GB/ZGB/common/src/Sprite.c:42: if(THIS->anim_data) {	
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	a, (hl)
	or	a, c
	jp	Z, 00106$
;C:/GB/ZGB/common/src/Sprite.c:43: THIS->anim_accum_ticks += THIS->anim_speed << delta_time;
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0005
	add	hl, de
	ld	b,l
	ld	a,h
	ld	b, (hl)
	ld	hl, #_delta_time
	ld	a, (hl)
	inc	a
	jr	00147$
00146$:
	sla	b
00147$:
	dec	a
	jr	NZ,00146$
	ld	a, c
	add	a, b
	ld	c, a
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Sprite.c:42: if(THIS->anim_data) {	
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;C:/GB/ZGB/common/src/Sprite.c:44: if(THIS->anim_accum_ticks > (UINT8)100u) {
	ld	hl, #0x0004
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	(hl), a
	ld	a, #0x64
	sub	a, (hl)
	jp	NC, 00106$
;C:/GB/ZGB/common/src/Sprite.c:45: THIS->anim_frame ++;
	ld	hl, #0x0006
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	inc	a
	ld	(bc), a
;C:/GB/ZGB/common/src/Sprite.c:42: if(THIS->anim_data) {	
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;C:/GB/ZGB/common/src/Sprite.c:45: THIS->anim_frame ++;
	ld	hl, #0x0006
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:46: if(THIS->anim_frame == THIS->anim_data[0]){
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	hl
	ld	(hl), a
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	c, (hl)
	inc	hl
	ld	a, (hl)
	ld	l, c
	ld	h, a
	ld	c, (hl)
	ldhl	sp,	#7
	ld	a, (hl)
	sub	a, c
	jr	NZ,00102$
;C:/GB/ZGB/common/src/Sprite.c:47: THIS->anim_frame = 0;
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00102$:
;C:/GB/ZGB/common/src/Sprite.c:42: if(THIS->anim_data) {	
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#1
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Sprite.c:50: THIS->frame = THIS->first_tile + ((THIS->anim_data[(UINT8)1u + THIS->anim_frame]) << THIS->size);
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0007
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	dec	hl
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, (bc)
	ldhl	sp,	#5
	ld	(hl), a
	ldhl	sp,#(2 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#6
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(2 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0006
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	c, a
	ld	b, #0x00
	inc	bc
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ldhl	sp,#(2 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	a
	jr	00151$
00150$:
	sla	c
00151$:
	dec	a
	jr	NZ,00150$
	ldhl	sp,	#5
	ld	a, (hl)
	add	a, c
	ld	c, a
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Sprite.c:42: if(THIS->anim_data) {	
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;C:/GB/ZGB/common/src/Sprite.c:43: THIS->anim_accum_ticks += THIS->anim_speed << delta_time;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
;C:/GB/ZGB/common/src/Sprite.c:51: THIS->anim_accum_ticks -= 100u;
	ld	a, (bc)
	add	a, #0x9c
	ld	(bc), a
00106$:
;C:/GB/ZGB/common/src/Sprite.c:42: if(THIS->anim_data) {	
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Sprite.c:55: screen_x = THIS->x - scroll_x;
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_scroll_x
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	ldhl	sp,	#2
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:56: screen_y = THIS->y - scroll_y;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_scroll_y
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	ldhl	sp,	#4
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:58: if((screen_x + 32u < SCREENWIDTH_PLUS_32) && (screen_y + 32 < SCREENHEIGHT_PLUS_32)) {
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0020
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, c
	sub	a, #0xc0
	ld	a, b
	sbc	a, #0x00
	jp	NC, 00111$
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0020
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, c
	sub	a, #0xb0
	ld	a, b
	sbc	a, #0x00
	jp	NC, 00111$
;C:/GB/ZGB/common/src/Sprite.c:59: DrawFrame(THIS->size, THIS->frame, screen_x, screen_y, THIS->flags);		
	pop	de
	push	de
	ld	hl, #0x000c
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#6
	ld	(hl-), a
	dec	hl
	ld	a, (hl)
	ldhl	sp,	#7
	ld	(hl), a
	ldhl	sp,	#2
	ld	b, (hl)
	pop	de
	push	de
	ld	hl, #0x0007
	add	hl, de
	ld	c,l
	ld	a,h
	ld	a, (hl)
	ldhl	sp,	#4
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	hl
	ld	a, (hl)
	push	af
	inc	sp
	inc	hl
	ld	a, (hl)
	push	af
	inc	sp
	push	bc
	inc	sp
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ld	a, c
	push	af
	inc	sp
	call	_DrawFrame
	add	sp, #6
	jp	00114$
00111$:
;C:/GB/ZGB/common/src/Sprite.c:61: if((screen_x + THIS->lim_x + 16) > ((THIS->lim_x << 1) + 16 + SCREENWIDTH) ||
	pop	de
	push	de
	ld	hl, #0x0013
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0010
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
	sla	c
	rl	b
	ld	hl, #0x00b0
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#2
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jp	C, 00107$
;C:/GB/ZGB/common/src/Sprite.c:62: (screen_y + THIS->lim_y + 16) > ((THIS->lim_y << 1) + 16 + SCREENHEIGHT)
	pop	de
	push	de
	ld	hl, #0x0015
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0010
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
	sla	c
	rl	b
	ld	hl, #0x00a0
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#4
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jr	NC,00114$
00107$:
;C:/GB/ZGB/common/src/Sprite.c:64: SpriteManagerRemove(THIS_IDX);
	ld	hl, #_THIS_IDX
	ld	c, (hl)
	ld	b, #0x00
	push	bc
	call	_SpriteManagerRemove
	add	sp, #2
00114$:
;C:/GB/ZGB/common/src/Sprite.c:67: }
	add	sp, #8
	ret
;C:/GB/ZGB/common/src/Sprite.c:70: UINT8 TranslateSprite(struct Sprite* sprite, INT8 x, INT8 y) {
;	---------------------------------
; Function TranslateSprite
; ---------------------------------
_TranslateSprite::
	add	sp, #-20
;C:/GB/ZGB/common/src/Sprite.c:73: UINT8 ret = 0;
	xor	a, a
	ldhl	sp,	#2
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:77: tmp = (sprite->x + sprite->coll_x + sprite->coll_w - 1);
	ldhl	sp,	#22
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#16
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Sprite.c:121: tmp = sprite->y + sprite->coll_y + sprite->coll_h - 1;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:75: if(scroll_map) {
	ld	hl, #_scroll_map + 1
	ld	a, (hl-)
	or	a, (hl)
	jp	Z, 00143$
;C:/GB/ZGB/common/src/Sprite.c:78: start_x = tmp + x;
	ldhl	sp,	#24
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
;C:/GB/ZGB/common/src/Sprite.c:121: tmp = sprite->y + sprite->coll_y + sprite->coll_h - 1;
	ldhl	sp,#(17 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000e
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:124: start_x = (sprite->x + sprite->coll_x);
	ldhl	sp,#(17 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000d
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#7
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:126: n_its = ((start_x + sprite->coll_w - 1u) >> 3) - (start_x >> 3) + 1u;
	ldhl	sp,#(17 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000f
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:77: tmp = (sprite->x + sprite->coll_x + sprite->coll_w - 1);
	ldhl	sp,#(17 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:78: start_x = tmp + x;
	ldhl	sp,	#18
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:82: n_its = ((start_y + sprite->coll_h - 1u) >> 3) - (start_y >> 3) + 1u;
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0010
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:118: sprite->x += (INT16)x;
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:76: if(x > 0) {
	ldhl	sp,	#24
	ld	a, (hl)
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00293$
	bit	7, d
	jr	NZ,00294$
	cp	a, a
	jr	00294$
00293$:
	bit	7, d
	jr	Z,00294$
	scf
00294$:
	jp	NC, 00118$
;C:/GB/ZGB/common/src/Sprite.c:77: tmp = (sprite->x + sprite->coll_x + sprite->coll_w - 1);
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	pop	hl
	push	hl
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#16
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,#(10 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	dec	bc
;C:/GB/ZGB/common/src/Sprite.c:78: start_x = tmp + x;
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:79: if(((INT8)tmp & (INT8)0xF8) != ((INT8)start_x & (INT8)0xF8)) {
	ld	a, c
	and	a, #0xf8
	ld	c, a
	dec	hl
	ld	a, (hl)
	and	a, #0xf8
	sub	a, c
	jp	Z,00119$
;C:/GB/ZGB/common/src/Sprite.c:80: start_y = (sprite->y + sprite->coll_y);
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	pop	hl
	push	hl
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#18
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:81: if(((start_y & 0xF000) | (start_x & 0xF000)) == 0u) {
	ld	c, #0x00
	ld	a, (hl)
	and	a, #0xf0
	ld	b, a
	ld	e, #0x00
	ldhl	sp,	#16
	ld	a, (hl)
	and	a, #0xf0
	push	af
	ld	a, c
	or	a, e
	ld	c, a
	pop	af
	or	a, b
	or	a, c
	jp	NZ, 00119$
;C:/GB/ZGB/common/src/Sprite.c:82: n_its = ((start_y + sprite->coll_h - 1u) >> 3) - (start_y >> 3) + 1u;
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	dec	bc
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ldhl	sp,	#18
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	ldhl	sp,	#19
	ld	a, (hl)
	ldhl	sp,	#1
	ld	(hl), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	pop	de
	push	de
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	inc	bc
	ldhl	sp,	#17
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:83: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Sprite.c:84: tile_coll = GetScrollTilePtr(start_x >> 3, start_y >> 3);
	ldhl	sp,#(16 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	pop	hl
	push	hl
	push	hl
	push	bc
	call	_GetScrollTilePtr
	add	sp, #4
	ld	hl, #_tile_coll
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:86: for(i = 0u; i != n_its; ++i, tile_coll += scroll_tiles_w) {
	xor	a, a
	ldhl	sp,	#19
	ld	(hl), a
00145$:
	ldhl	sp,	#19
	ld	c, (hl)
	ld	b, #0x00
	dec	hl
	dec	hl
	ld	a, (hl)
	sub	a, c
	jr	NZ,00296$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jp	Z,00103$
00296$:
;C:/GB/ZGB/common/src/Sprite.c:87: if(scroll_collisions[*tile_coll] == 1u) {
	ld	hl, #_tile_coll + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	ld	c, a
	ld	a, #<(_scroll_collisions)
	add	a, c
	ld	b, a
	ld	a, #>(_scroll_collisions)
	adc	a, #0x00
	ld	l, b
	ld	h, a
	ld	a, (hl)
	dec	a
	jr	NZ,00146$
;C:/GB/ZGB/common/src/Sprite.c:88: x -= (start_x & (UINT16)7u) + 1;
	ldhl	sp,	#15
	ld	a, (hl)
	and	a, #0x07
	ld	b, a
	inc	b
	ldhl	sp,	#24
	ld	a, (hl)
	sub	a, b
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:89: ret = *tile_coll;
	ldhl	sp,	#2
	ld	(hl), c
;C:/GB/ZGB/common/src/Sprite.c:90: break;
	jr	00103$
00146$:
;C:/GB/ZGB/common/src/Sprite.c:86: for(i = 0u; i != n_its; ++i, tile_coll += scroll_tiles_w) {
	ldhl	sp,	#19
	inc	(hl)
	ld	hl, #_tile_coll
	ld	a, (hl)
	ld	hl, #_scroll_tiles_w
	add	a, (hl)
	ld	hl, #_tile_coll
	ld	(hl+), a
	ld	a, (hl)
	ld	hl, #_scroll_tiles_w + 1
	adc	a, (hl)
	ld	hl, #_tile_coll + 1
	ld	(hl), a
	jp	00145$
00103$:
;C:/GB/ZGB/common/src/Sprite.c:93: POP_BANK;
	call	_PopBank
	jp	00119$
00118$:
;C:/GB/ZGB/common/src/Sprite.c:97: else if(x < 0) {
	ldhl	sp,	#24
	ld	a, (hl)
	bit	7, a
	jp	Z, 00119$
;C:/GB/ZGB/common/src/Sprite.c:98: tmp = sprite->x + sprite->coll_x;
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	pop	hl
	push	hl
	add	hl, bc
	ld	c, l
	ld	b, h
;C:/GB/ZGB/common/src/Sprite.c:99: start_x = tmp + (INT16)x;
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:100: if(((INT8)tmp & (INT8)0xF8) != ((INT8)start_x & (INT8)0xF8)) {
	ld	a, c
	and	a, #0xf8
	ld	c, a
	dec	hl
	ld	a, (hl)
	and	a, #0xf8
	sub	a, c
	jp	Z,00119$
;C:/GB/ZGB/common/src/Sprite.c:101: start_y = (sprite->y + sprite->coll_y);
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	pop	hl
	push	hl
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#18
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:102: if(((start_y & 0xF000) | (start_x & 0xF000)) == 0u) {
	ld	c, #0x00
	ld	a, (hl)
	and	a, #0xf0
	ld	b, a
	ld	e, #0x00
	ldhl	sp,	#16
	ld	a, (hl)
	and	a, #0xf0
	push	af
	ld	a, c
	or	a, e
	ld	c, a
	pop	af
	or	a, b
	or	a, c
	jp	NZ, 00119$
;C:/GB/ZGB/common/src/Sprite.c:103: n_its = ((start_y + sprite->coll_h - 1u) >> 3) - (start_y >> 3) + 1u;
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	dec	bc
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ldhl	sp,	#18
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	ldhl	sp,	#19
	ld	a, (hl)
	ldhl	sp,	#1
	ld	(hl), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	pop	de
	push	de
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	inc	bc
	ldhl	sp,	#17
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:104: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Sprite.c:105: tile_coll = GetScrollTilePtr(start_x >> 3, start_y >> 3);
	ldhl	sp,#(16 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	pop	hl
	push	hl
	push	hl
	push	bc
	call	_GetScrollTilePtr
	add	sp, #4
	ld	hl, #_tile_coll
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:107: for(i = 0u; i != n_its; ++i, tile_coll += scroll_tiles_w) {
	ld	c, #0x00
00148$:
	ldhl	sp,	#0
	ld	(hl), c
	xor	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,	#17
	ld	a, (hl)
	ldhl	sp,	#0
	sub	a, (hl)
	jr	NZ,00300$
	ldhl	sp,	#18
	ld	a, (hl)
	ldhl	sp,	#1
	sub	a, (hl)
	jp	Z,00110$
00300$:
;C:/GB/ZGB/common/src/Sprite.c:87: if(scroll_collisions[*tile_coll] == 1u) {
	ld	hl, #_tile_coll + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#19
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:108: if(scroll_collisions[*tile_coll] == 1u) {
	ld	de, #_scroll_collisions
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	b,l
	ld	a,h
	ld	a, (hl)
	dec	a
	jr	NZ,00149$
;C:/GB/ZGB/common/src/Sprite.c:109: x = (INT16)x + (8u - (start_x & (UINT16)7u));
	ldhl	sp,	#24
	ld	c, (hl)
	ldhl	sp,	#15
	ld	a, (hl)
	and	a, #0x07
	ld	b, a
	ld	a, #0x08
	sub	a, b
	add	a, c
	ldhl	sp,	#24
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:110: ret = *tile_coll;
	ldhl	sp,	#19
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:111: break;
	jr	00110$
00149$:
;C:/GB/ZGB/common/src/Sprite.c:107: for(i = 0u; i != n_its; ++i, tile_coll += scroll_tiles_w) {
	inc	c
	ld	hl, #_tile_coll
	ld	a, (hl)
	ld	hl, #_scroll_tiles_w
	add	a, (hl)
	ld	hl, #_tile_coll
	ld	(hl+), a
	ld	a, (hl)
	ld	hl, #_scroll_tiles_w + 1
	adc	a, (hl)
	ld	hl, #_tile_coll + 1
	ld	(hl), a
	jp	00148$
00110$:
;C:/GB/ZGB/common/src/Sprite.c:114: POP_BANK;
	call	_PopBank
00119$:
;C:/GB/ZGB/common/src/Sprite.c:118: sprite->x += (INT16)x;
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#18
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#24
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:122: start_y = tmp + y;
	ldhl	sp,	#25
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
;C:/GB/ZGB/common/src/Sprite.c:80: start_y = (sprite->y + sprite->coll_y);
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#16
	ld	(hl+), a
	inc	de
	ld	a, (de)
;C:/GB/ZGB/common/src/Sprite.c:122: start_y = tmp + y;
	ld	(hl+), a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:120: if(y > 0) {
	ldhl	sp,	#25
	ld	a, (hl)
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00303$
	bit	7, d
	jr	NZ,00304$
	cp	a, a
	jr	00304$
00303$:
	bit	7, d
	jr	Z,00304$
	scf
00304$:
	jp	NC, 00140$
;C:/GB/ZGB/common/src/Sprite.c:121: tmp = sprite->y + sprite->coll_y + sprite->coll_h - 1;
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	dec	bc
;C:/GB/ZGB/common/src/Sprite.c:122: start_y = tmp + y;
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#16
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:123: if(((INT8)tmp & (INT8)0xF8) != ((INT8)start_y & (INT8)0xF8)) {
	ld	a, c
	and	a, #0xf8
	ld	c, a
	dec	hl
	ld	a, (hl)
	and	a, #0xf8
	ld	b, a
	ld	a, c
	sub	a, b
	jp	Z,00143$
;C:/GB/ZGB/common/src/Sprite.c:124: start_x = (sprite->x + sprite->coll_x);
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	hl
	inc	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#14
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:125: if(((start_y & 0xF000) | (start_x & 0xF000)) == 0u) {
	ld	c, #0x00
	inc	hl
	inc	hl
	ld	a, (hl)
	and	a, #0xf0
	ld	b, a
	ld	e, #0x00
	dec	hl
	dec	hl
	ld	a, (hl)
	and	a, #0xf0
	push	af
	ld	a, c
	or	a, e
	ld	c, a
	pop	af
	or	a, b
	or	a, c
	jp	NZ, 00143$
;C:/GB/ZGB/common/src/Sprite.c:126: n_its = ((start_x + sprite->coll_w - 1u) >> 3) - (start_x >> 3) + 1u;
	ldhl	sp,#(10 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	dec	bc
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ldhl	sp,	#14
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#15
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	inc	bc
	inc	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:127: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Sprite.c:128: tile_coll = GetScrollTilePtr(start_x >> 3, start_y >> 3);
	ldhl	sp,#(17 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	push	bc
	push	bc
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_GetScrollTilePtr
	add	sp, #4
	pop	bc
	ld	hl, #_tile_coll
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:130: for(i = 0u; i != n_its; ++i, tile_coll += 1u) {
	ldhl	sp,#(17 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	inc	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#13
	ld	(hl-), a
	ld	(hl), e
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	ld	a, e
	sub	a, c
	jr	NZ,00306$
	ld	a, d
	sub	a, b
	ld	a, #0x01
	jr	Z,00307$
00306$:
	xor	a, a
00307$:
	ldhl	sp,	#11
	ld	(hl), a
	xor	a, a
	ldhl	sp,	#19
	ld	(hl), a
00151$:
	ldhl	sp,	#19
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#14
	ld	a, (hl)
	sub	a, c
	jr	NZ,00308$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jp	Z,00125$
00308$:
;C:/GB/ZGB/common/src/Sprite.c:87: if(scroll_collisions[*tile_coll] == 1u) {
	ld	hl, #_tile_coll
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#12
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#18
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:131: if(scroll_collisions[*tile_coll] == 1u || 
	ld	de, #_scroll_collisions
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	dec	a
	jp	Z,00120$
;C:/GB/ZGB/common/src/Sprite.c:132: (scroll_collisions_down[*tile_coll] == 1u && //Tile that only checks collisions when going down
	ld	de, #_scroll_collisions_down
	ldhl	sp,	#18
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	dec	a
	jp	NZ,00152$
;C:/GB/ZGB/common/src/Sprite.c:133: scroll_collisions_down[*(tile_coll - scroll_tiles_w)] == 0) &&  //The one above is not collidable (so we can crate a big block putting some of there together)
	ld	hl, #_scroll_tiles_w + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_tile_coll
	ld	a, (hl)
	sub	a, c
	ld	c, a
	inc	hl
	ld	a, (hl)
	sbc	a, b
	ld	b, a
	ld	a, (bc)
	add	a, #<(_scroll_collisions_down)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_scroll_collisions_down)
	ld	b, a
	ld	a, (bc)
	or	a, a
	jr	NZ,00152$
;C:/GB/ZGB/common/src/Sprite.c:134: (((start_y - y) >> 3) != (start_y >> 3)) //The is entering the collidable tile in this moment
	ldhl	sp,	#11
	bit	0, (hl)
	jr	NZ,00152$
00120$:
;C:/GB/ZGB/common/src/Sprite.c:136: y -= (start_y & (UINT16)7u) + 1;
	ldhl	sp,	#16
	ld	a, (hl)
	and	a, #0x07
	ld	c, a
	inc	c
	ldhl	sp,	#25
	ld	a, (hl)
	sub	a, c
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:137: ret = *tile_coll;
	ldhl	sp,	#18
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:138: break;
	jr	00125$
00152$:
;C:/GB/ZGB/common/src/Sprite.c:130: for(i = 0u; i != n_its; ++i, tile_coll += 1u) {
	ldhl	sp,	#19
	inc	(hl)
	ld	hl, #_tile_coll
	inc	(hl)
	jp	NZ,00151$
	inc	hl
	inc	(hl)
	jp	00151$
00125$:
;C:/GB/ZGB/common/src/Sprite.c:141: POP_BANK;
	call	_PopBank
	jp	00143$
00140$:
;C:/GB/ZGB/common/src/Sprite.c:145: else if(y < 0) {
	ldhl	sp,	#25
	ld	a, (hl)
	bit	7, a
	jp	Z, 00143$
;C:/GB/ZGB/common/src/Sprite.c:146: tmp = sprite->y + sprite->coll_y;
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
;C:/GB/ZGB/common/src/Sprite.c:147: start_y = tmp + (INT16)y;
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#16
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:148: if(((INT8)tmp & (INT8)0xF8) != ((INT8)start_y & (INT8)0xF8)) {
	ld	a, c
	and	a, #0xf8
	ld	c, a
	dec	hl
	ld	a, (hl)
	and	a, #0xf8
	ld	b, a
	ld	a, c
	sub	a, b
	jp	Z,00143$
;C:/GB/ZGB/common/src/Sprite.c:149: start_x = (sprite->x + sprite->coll_x);
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#18
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#14
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:150: if(((start_y & 0xF000) | (start_x & 0xF000)) == 0u) {
	ld	c, #0x00
	inc	hl
	inc	hl
	ld	a, (hl)
	and	a, #0xf0
	ld	b, a
	ld	e, #0x00
	dec	hl
	dec	hl
	ld	a, (hl)
	and	a, #0xf0
	push	af
	ld	a, c
	or	a, e
	ld	c, a
	pop	af
	or	a, b
	or	a, c
	jp	NZ, 00143$
;C:/GB/ZGB/common/src/Sprite.c:151: n_its = ((start_x + sprite->coll_w - 1u) >> 3) - (start_x >> 3) + 1u;
	ldhl	sp,#(10 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	dec	bc
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	ldhl	sp,	#14
	ld	a, (hl)
	ldhl	sp,	#18
	ld	(hl), a
	ldhl	sp,	#15
	ld	a, (hl)
	ldhl	sp,	#19
	ld	(hl), a
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	srl	(hl)
	dec	hl
	rr	(hl)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	inc	bc
	ldhl	sp,	#14
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:152: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Sprite.c:153: tile_coll = GetScrollTilePtr(start_x >> 3, start_y >> 3);
	ldhl	sp,#(17 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	srl	b
	rr	c
	srl	b
	rr	c
	srl	b
	rr	c
	push	bc
	inc	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_GetScrollTilePtr
	add	sp, #4
	ld	hl, #_tile_coll
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/Sprite.c:155: for(i = 0u; i != n_its; ++i, tile_coll += 1u) {
	ld	c, #0x00
00154$:
	ld	b, c
	ld	e, #0x00
	ldhl	sp,	#14
	ld	a, (hl)
	sub	a, b
	jr	NZ,00314$
	inc	hl
	ld	a, (hl)
	sub	a, e
	jp	Z,00132$
00314$:
;C:/GB/ZGB/common/src/Sprite.c:87: if(scroll_collisions[*tile_coll] == 1u) {
	ld	hl, #_tile_coll + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	ldhl	sp,	#19
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:156: if(scroll_collisions[*tile_coll] == 1u) {
	ld	de, #_scroll_collisions
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	b,l
	ld	a,h
	ld	a, (hl)
	dec	a
	jr	NZ,00155$
;C:/GB/ZGB/common/src/Sprite.c:157: y = (INT16)y + (8u - (start_y & (UINT16)7u));
	ldhl	sp,	#25
	ld	c, (hl)
	ldhl	sp,	#16
	ld	a, (hl)
	and	a, #0x07
	ld	b, a
	ld	a, #0x08
	sub	a, b
	add	a, c
	ldhl	sp,	#25
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:158: ret = *tile_coll;
	ldhl	sp,	#19
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:159: break;
	jr	00132$
00155$:
;C:/GB/ZGB/common/src/Sprite.c:155: for(i = 0u; i != n_its; ++i, tile_coll += 1u) {
	inc	c
	ld	hl, #_tile_coll
	inc	(hl)
	jp	NZ,00154$
	inc	hl
	inc	(hl)
	jp	00154$
00132$:
;C:/GB/ZGB/common/src/Sprite.c:162: POP_BANK;
	call	_PopBank
00143$:
;C:/GB/ZGB/common/src/Sprite.c:167: sprite->y += (INT16)y;
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#18
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#25
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:169: return ret;
	ldhl	sp,	#2
	ld	e, (hl)
;C:/GB/ZGB/common/src/Sprite.c:170: }
	add	sp, #20
	ret
;C:/GB/ZGB/common/src/Sprite.c:172: UINT8 CheckCollision(struct Sprite* sprite1, struct Sprite* sprite2) {
;	---------------------------------
; Function CheckCollision
; ---------------------------------
_CheckCollision::
	add	sp, #-8
;C:/GB/ZGB/common/src/Sprite.c:176: diff16 = sprite1->x - sprite2->x;
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#4
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	sub	a, c
	ld	e, a
	ld	a, d
	sbc	a, b
	inc	hl
	inc	hl
	ld	(hl-), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Sprite.c:177: if((UINT16)(diff16 + 32) > 64) //diff16 > 32 || diff16 < -32
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0020
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
	ld	a, #0x40
	cp	a, c
	ld	a, #0x00
	sbc	a, b
	jr	NC,00102$
;C:/GB/ZGB/common/src/Sprite.c:178: return 0;
	ld	e, #0x00
	jp	00111$
00102$:
;C:/GB/ZGB/common/src/Sprite.c:180: diff = (INT8)diff16 + sprite1->coll_x - sprite2->coll_x;
	ldhl	sp,	#6
	ld	c, (hl)
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	b,l
	ld	a,h
	ld	a, (hl)
	add	a, c
	ld	c, a
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000d
	add	hl, de
	ld	b,l
	ld	a,h
	ld	b, (hl)
	ld	a, c
	sub	a, b
	ldhl	sp,	#7
	ld	(hl), a
;C:/GB/ZGB/common/src/Sprite.c:182: diff16 = sprite1->y - sprite2->y;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#5
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	sub	a, c
	ld	e, a
	ld	a, d
	sbc	a, b
	ld	b, a
	ld	c, e
	dec	hl
	dec	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sprite.c:183: if((UINT16)(diff16 + 32) > 64)
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0020
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
	ld	a, #0x40
	cp	a, c
	ld	a, #0x00
	sbc	a, b
	jr	NC,00104$
;C:/GB/ZGB/common/src/Sprite.c:184: return 0;
	ld	e, #0x00
	jp	00111$
00104$:
;C:/GB/ZGB/common/src/Sprite.c:186: if( (diff + sprite1->coll_w) < 0 ||
	ldhl	sp,	#7
	ld	a, (hl-)
	ld	(hl), a
	rla
	sbc	a, a
	inc	hl
	ld	(hl), a
	pop	de
	push	de
	ld	hl, #0x000f
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	bit	7, b
	jr	NZ,00105$
;C:/GB/ZGB/common/src/Sprite.c:187: (sprite2->coll_w - diff) < 0) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000f
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	bit	7, b
	jr	Z,00106$
00105$:
;C:/GB/ZGB/common/src/Sprite.c:188: return 0;
	ld	e, #0x00
	jp	00111$
00106$:
;C:/GB/ZGB/common/src/Sprite.c:191: diff = (INT8)diff16 + sprite1->coll_y - sprite2->coll_y; 
	ldhl	sp,	#4
	ld	c, (hl)
	pop	de
	push	de
	ld	hl, #0x000e
	add	hl, de
	ld	b,l
	ld	a,h
	ld	a, (hl)
	add	a, c
	ld	c, a
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000e
	add	hl, de
	ld	b,l
	ld	a,h
	ld	b, (hl)
	ld	a, c
	sub	a, b
;C:/GB/ZGB/common/src/Sprite.c:192: if( (diff + sprite1->coll_h) < 0 ||
	ldhl	sp,	#6
	ld	(hl), a
	rla
	sbc	a, a
	inc	hl
	ld	(hl), a
	pop	de
	push	de
	ld	hl, #0x0010
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	bit	7, b
	jr	NZ,00108$
;C:/GB/ZGB/common/src/Sprite.c:193: (sprite2->coll_h - diff) < 0) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0010
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	b, a
	ld	c, e
	bit	7, b
	jr	Z,00109$
00108$:
;C:/GB/ZGB/common/src/Sprite.c:194: return 0;
	ld	e, #0x00
	jr	00111$
00109$:
;C:/GB/ZGB/common/src/Sprite.c:197: return 1;
	ld	e, #0x01
00111$:
;C:/GB/ZGB/common/src/Sprite.c:198: }
	add	sp, #8
	ret
	.area _CODE
	.area _CABS (ABS)
