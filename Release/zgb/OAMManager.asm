;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module OAMManager
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _set_sprite_data
	.globl _next_oam_sprite_flags
	.globl _next_oam_sprite_idx
	.globl _next_oam_sprite_x
	.globl _next_oam_sprite_y
	.globl _oam_end
	.globl _oam1
	.globl _oam0
	.globl _oam
	.globl _oam_mirror
	.globl _sprites_pal
	.globl _last_sprite_loaded
	.globl _LoadSprite
	.globl _SwapOAMs
	.globl _ClearOAMs
	.globl _FlushOAMSprite
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_last_sprite_loaded::
	.ds 1
_sprites_pal::
	.ds 256
_oam_mirror	=	0xdf00
_oam::
	.ds 2
_oam0::
	.ds 2
_oam1::
	.ds 2
_oam_end::
	.ds 2
_next_oam_sprite_y::
	.ds 1
_next_oam_sprite_x::
	.ds 1
_next_oam_sprite_idx::
	.ds 1
_next_oam_sprite_flags::
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
;C:/GB/ZGB/common/src/OAMManager.c:4: UINT8 last_sprite_loaded = 0;
	ld	hl, #_last_sprite_loaded
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/OAMManager.c:36: UINT8* oam  = (UINT8*)0xC000;
	ld	hl, #_oam
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xc0
;C:/GB/ZGB/common/src/OAMManager.c:37: UINT8* oam0 = (UINT8*)0xC000;
	ld	hl, #_oam0
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xc0
;C:/GB/ZGB/common/src/OAMManager.c:38: UINT8* oam1 = (UINT8*)OAM_MIRROR_ADDRESS;
	ld	hl, #_oam1
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xdf
;C:/GB/ZGB/common/src/OAMManager.c:39: UINT8* oam_end = (UINT8*)0xC000;
	ld	hl, #_oam_end
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xc0
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;C:/GB/ZGB/common/src/OAMManager.c:7: UINT8 LoadSprite(struct TilesInfoInternal* data) {
;	---------------------------------
; Function LoadSprite
; ---------------------------------
_LoadSprite::
	add	sp, #-8
;C:/GB/ZGB/common/src/OAMManager.c:9: UINT8* sprites_pal_ptr = &sprites_pal[last_sprite_loaded];
	ld	bc, #_sprites_pal+0
	ld	a, c
	ld	hl, #_last_sprite_loaded
	add	a, (hl)
	ld	c, a
	jr	NC,00126$
	inc	b
00126$:
	ldhl	sp,	#6
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/OAMManager.c:10: UINT8 frame_size = data->width >> 3;
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	a,(de)
	swap	a
	rlca
	and	a, #0x1f
	inc	hl
	ld	(hl), a
;C:/GB/ZGB/common/src/OAMManager.c:11: UINT8 n_tiles = data->num_frames << frame_size;
	pop	bc
	push	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	a, (hl)
	inc	a
	jr	00128$
00127$:
	sla	c
00128$:
	dec	a
	jr	NZ,00127$
	inc	hl
	ld	(hl), c
;C:/GB/ZGB/common/src/OAMManager.c:12: UINT8* palette_idx = data->color_data;
	pop	de
	push	de
	ld	hl, #0x0005
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
;C:/GB/ZGB/common/src/OAMManager.c:14: set_sprite_data(last_sprite_loaded, n_tiles, data->data);
	pop	bc
	push	bc
	inc	bc
	inc	bc
	inc	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	ldhl	sp,	#5
	ld	a, (hl)
	push	af
	inc	sp
	ld	hl, #_last_sprite_loaded
	ld	a, (hl)
	push	af
	inc	sp
	call	_set_sprite_data
	add	sp, #4
;C:/GB/ZGB/common/src/OAMManager.c:15: last_sprite_loaded += n_tiles;
	ld	hl, #_last_sprite_loaded
	ld	a, (hl)
	ldhl	sp,	#3
	add	a, (hl)
	ld	hl, #_last_sprite_loaded
	ld	(hl), a
;C:/GB/ZGB/common/src/OAMManager.c:17: for(i = 0; i != n_tiles; ++i, sprites_pal_ptr ++) {
	ld	c, #0x00
00106$:
	ldhl	sp,	#3
	ld	a, (hl)
	sub	a, c
	jp	Z,00104$
;C:/GB/ZGB/common/src/OAMManager.c:18: if(palette_idx)
	ldhl	sp,	#5
	ld	a, (hl-)
	or	a, (hl)
	jr	Z,00102$
;C:/GB/ZGB/common/src/OAMManager.c:19: *sprites_pal_ptr = *(palette_idx + (i >> frame_size)); 
	dec	hl
	dec	hl
	ld	a, (hl)
	push	af
	ld	b, c
	pop	af
	inc	a
	jr	00131$
00130$:
	srl	b
00131$:
	dec	a
	jr	NZ, 00130$
	ld	e, b
	ld	d, #0x00
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	b,l
	ld	a,h
	ld	b, (hl)
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
	jr	00107$
00102$:
;C:/GB/ZGB/common/src/OAMManager.c:21: *sprites_pal_ptr = 0; 
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00107$:
;C:/GB/ZGB/common/src/OAMManager.c:17: for(i = 0; i != n_tiles; ++i, sprites_pal_ptr ++) {
	inc	c
	ldhl	sp,	#6
	inc	(hl)
	jp	NZ,00106$
	inc	hl
	inc	(hl)
	jp	00106$
00104$:
;C:/GB/ZGB/common/src/OAMManager.c:24: return last_sprite_loaded - n_tiles;
	ld	hl, #_last_sprite_loaded
	ld	a, (hl)
	ldhl	sp,	#3
	sub	a, (hl)
	ld	e, a
;C:/GB/ZGB/common/src/OAMManager.c:25: }
	add	sp, #8
	ret
;C:/GB/ZGB/common/src/OAMManager.c:40: void SwapOAMs() {
;	---------------------------------
; Function SwapOAMs
; ---------------------------------
_SwapOAMs::
;C:/GB/ZGB/common/src/OAMManager.c:42: UINT8* tmp = oam;
	ld	hl, #_oam + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;C:/GB/ZGB/common/src/OAMManager.c:43: while(oam < oam_end) {
00101$:
	ld	de, #_oam
	ld	hl, #_oam_end
	ld	a, (de)
	sub	a, (hl)
	inc	hl
	inc	de
	ld	a, (de)
	sbc	a, (hl)
	jr	NC,00103$
;C:/GB/ZGB/common/src/OAMManager.c:44: *oam = 200;
	ld	hl, #_oam + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, #0xc8
	ld	(de), a
;C:/GB/ZGB/common/src/OAMManager.c:45: oam += 4;
	dec	hl
	ld	a, (hl)
	add	a, #0x04
	ld	(hl+), a
	ld	a, (hl)
	adc	a, #0x00
	ld	(hl), a
	jr	00101$
00103$:
;C:/GB/ZGB/common/src/OAMManager.c:48: if((0xFF00 & (UINT16)oam) == 0xC000) {
	ld	hl, #_oam + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	e, #0x00
	ld	a, e
	or	a, a
	jr	NZ,00105$
	ld	a, d
	sub	a, #0xc0
	jr	NZ,00105$
;C:/GB/ZGB/common/src/OAMManager.c:49: *(UINT8*)0xFF81 = 0xC0;
	ld	hl, #0xff81
	ld	(hl), #0xc0
;C:/GB/ZGB/common/src/OAMManager.c:50: oam0 = tmp;
	ld	hl, #_oam0
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/OAMManager.c:51: oam = (UINT8*)OAM_MIRROR_ADDRESS;
	ld	hl, #_oam
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xdf
;C:/GB/ZGB/common/src/OAMManager.c:52: oam_end = oam1;
	ld	hl, #_oam1
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_oam_end
	ld	(hl+), a
	ld	(hl), e
	ret
00105$:
;C:/GB/ZGB/common/src/OAMManager.c:54: *(UINT8*)0xFF81 = OAM_MIRROR_ADDRESS_HI;
	ld	hl, #0xff81
	ld	(hl), #0xdf
;C:/GB/ZGB/common/src/OAMManager.c:55: oam1 = tmp;
	ld	hl, #_oam1
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/OAMManager.c:56: oam = (UINT8*)0xC000;
	ld	hl, #_oam
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xc0
;C:/GB/ZGB/common/src/OAMManager.c:57: oam_end = oam0;
	ld	hl, #_oam0
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_oam_end
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/OAMManager.c:59: }
	ret
;C:/GB/ZGB/common/src/OAMManager.c:61: void ClearOAMs() {
;	---------------------------------
; Function ClearOAMs
; ---------------------------------
_ClearOAMs::
;C:/GB/ZGB/common/src/OAMManager.c:63: oam0 = (UINT8*)0xC000;
	ld	hl, #_oam0
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xc0
;C:/GB/ZGB/common/src/OAMManager.c:64: oam1 = (UINT8*)OAM_MIRROR_ADDRESS;
	ld	hl, #_oam1
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0xdf
;C:/GB/ZGB/common/src/OAMManager.c:65: for(i = 0; i < 40; ++i, oam0 += 4, oam1 += 4) {
	ld	c, #0x00
00102$:
;C:/GB/ZGB/common/src/OAMManager.c:66: *oam0 = 200;
	ld	hl, #_oam0 + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, #0xc8
	ld	(de), a
;C:/GB/ZGB/common/src/OAMManager.c:67: *oam1 = 200;
	ld	hl, #_oam1 + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, #0xc8
	ld	(de), a
;C:/GB/ZGB/common/src/OAMManager.c:65: for(i = 0; i < 40; ++i, oam0 += 4, oam1 += 4) {
	inc	c
	ld	hl, #_oam0
	ld	a, (hl)
	add	a, #0x04
	ld	(hl+), a
	ld	a, (hl)
	adc	a, #0x00
	ld	(hl), a
	ld	hl, #_oam1
	ld	a, (hl)
	add	a, #0x04
	ld	(hl+), a
	ld	a, (hl)
	adc	a, #0x00
	ld	(hl), a
	ld	a, c
	sub	a, #0x28
	jp	C, 00102$
;C:/GB/ZGB/common/src/OAMManager.c:69: }
	ret
;C:/GB/ZGB/common/src/OAMManager.c:75: void FlushOAMSprite() {
;	---------------------------------
; Function FlushOAMSprite
; ---------------------------------
_FlushOAMSprite::
;C:/GB/ZGB/common/src/OAMManager.c:103: __endasm;
;store	in bc the address stored in oam ptr
	ld	hl,#_oam
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
;store	in hl the beginning of data (pointer to first param)
	ld	hl, #_next_oam_sprite_y
;OAMManager.c:35:	*(oam ++) = y;
	ld	a,(hl+)
	ld	(bc),a
	inc	c
;OAMManager.c:36:	*(oam ++) = x;
	ld	a,(hl+)
	ld	(bc),a
	inc	c
;OAMManager.c:37:	*(oam ++) = idx;
	ld	a,(hl+)
	ld	(bc),a
	inc	c
;OAMManager.c:38:	*(oam ++) = flags;
	ld	a,(hl+)
	ld	(bc),a
	inc	c
;refresh	oam value
	ld	hl,#_oam
	ld	(hl), c
;C:/GB/ZGB/common/src/OAMManager.c:104: }
	ret
	.area _CODE
	.area _CABS (ABS)
