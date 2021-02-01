;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Sound
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _gbt_enable_channels
	.globl _FX_ADDRESS
	.globl _FX_REG_SIZES
	.globl _PlayFx
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
;C:/GB/ZGB/common/src/Sound.c:11: void PlayFx(SOUND_CHANNEL channel, UINT8 mute_frames, ...) {
;	---------------------------------
; Function PlayFx
; ---------------------------------
_PlayFx::
	add	sp, #-7
;C:/GB/ZGB/common/src/Sound.c:13: UINT8* reg = (UINT8*)FX_ADDRESS[channel];
	ldhl	sp,	#9
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_FX_ADDRESS
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#4
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Sound.c:16: va_start(list, mute_frames);
	ldhl	sp,	#10
	ld	c, l
	ld	b, h
	inc	bc
	inc	sp
	inc	sp
	push	bc
;C:/GB/ZGB/common/src/Sound.c:17: for(i = 0; i < FX_REG_SIZES[channel]; ++i, ++reg) {
	ld	de, #_FX_REG_SIZES
	ldhl	sp,	#9
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
	xor	a, a
	ldhl	sp,	#6
	ld	(hl), a
00105$:
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ldhl	sp,	#6
	ld	a, (hl)
	sub	a, c
	jr	NC,00101$
;C:/GB/ZGB/common/src/Sound.c:18: *reg = va_arg(list, INT16);
	pop	bc
	push	bc
	inc	bc
	inc	bc
	inc	sp
	inc	sp
	push	bc
	dec	bc
	dec	bc
	ld	a, (bc)
	ld	c, a
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Sound.c:17: for(i = 0; i < FX_REG_SIZES[channel]; ++i, ++reg) {
	ldhl	sp,	#6
	inc	(hl)
	dec	hl
	dec	hl
	inc	(hl)
	jp	NZ,00105$
	inc	hl
	inc	(hl)
	jp	00105$
00101$:
;C:/GB/ZGB/common/src/Sound.c:22: if(channel != CHANNEL_5) {
	ldhl	sp,	#9
	ld	a, (hl)
	sub	a, #0x04
	jr	Z,00103$
;C:/GB/ZGB/common/src/Sound.c:23: gbt_enable_channels(~(0xF & (1 << channel)));
	ldhl	sp,	#9
	ld	c, (hl)
	ld	b, #0x01
	inc	c
	jr	00130$
00129$:
	sla	b
00130$:
	dec	c
	jr	NZ,00129$
	ld	a, b
	and	a, #0x0f
	cpl
	push	af
	inc	sp
	call	_gbt_enable_channels
	inc	sp
00103$:
;C:/GB/ZGB/common/src/Sound.c:26: music_mute_frames = mute_frames;
	push	hl
	ldhl	sp,	#12
	ld	a, (hl)
	ld	hl, #_music_mute_frames
	ld	(hl), a
	pop	hl
;C:/GB/ZGB/common/src/Sound.c:27: }
	add	sp, #7
	ret
_FX_REG_SIZES:
	.db #0x05	; 5
	.db #0x04	; 4
	.db #0x05	; 5
	.db #0x04	; 4
	.db #0x03	; 3
_FX_ADDRESS:
	.dw #0xff10
	.dw #0xff16
	.dw #0xff1a
	.dw #0xff20
	.dw #0xff24
	.area _CODE
	.area _CABS (ABS)
