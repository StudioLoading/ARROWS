;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpritePlatform
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpritePlatform
	.globl _Update_SpritePlatform
	.globl _Start_SpritePlatform
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpritePlatform
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _platform_normal
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_damage_cooldown::
	.ds 1
_attack_wait::
	.ds 1
;--------------------------------------------------------
; CODE rom data
;--------------------------------------------------------
	.area _CODE
_bank_SpritePlatform:
	.db #0x02	; 2
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
;custom_datas.h:54: UINT8 damage_cooldown = 30u;
	ld	hl, #_damage_cooldown
	ld	(hl), #0x1e
;custom_datas.h:55: UINT8 attack_wait = 32u;
	ld	hl, #_attack_wait
	ld	(hl), #0x20
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
;C:/GB/ZGB/common/include/Banks/SetBankCommon.h:4: void empty(void) __nonbanked {}
;	---------------------------------
; Function empty
; ---------------------------------
_empty::
	ret
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_2
;SpritePlatform.c:11: void Start_SpritePlatform() {
;	---------------------------------
; Function Start_SpritePlatform
; ---------------------------------
_Start_SpritePlatform::
	add	sp, #-2
;SpritePlatform.c:13: THIS->coll_x = 2;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000d
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x02
;SpritePlatform.c:14: THIS->coll_y = 12;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000e
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x0c
;SpritePlatform.c:15: THIS->coll_w = 12;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000f
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x0c
;SpritePlatform.c:16: THIS->coll_h = 4;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0010
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x04
;SpritePlatform.c:17: THIS->lim_x = 255;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x13
	ld	b, a
	jr	NC,00103$
	inc	c
00103$:
	ld	l, b
	ld	h, c
	ld	(hl), #0xff
	inc	hl
	ld	(hl), #0x00
;SpritePlatform.c:18: THIS->lim_y = 255;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x15
	ld	b, a
	jr	NC,00104$
	inc	c
00104$:
	ld	l, b
	ld	h, c
	ld	(hl), #0xff
	inc	hl
	ld	(hl), #0x00
;SpritePlatform.c:19: SetSpriteAnim(THIS, platform_normal, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_platform_normal
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePlatform.c:20: struct PlatformInfo* data_platform = (struct PlatformInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;SpritePlatform.c:21: data_platform->type = 0;
	ld	e, c
	ld	d, b
	ld	a, (de)
	and	a, #0xf8
	ld	(de),a
;SpritePlatform.c:22: data_platform->distance = 200;
	ld	hl, #0x0001
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0xc8
;SpritePlatform.c:23: data_platform->step = 0;
	inc	bc
	inc	bc
	xor	a, a
	ld	(bc), a
;SpritePlatform.c:24: }
	add	sp, #2
	ret
_platform_normal:
	.db #0x01	; 1
	.db #0x00	; 0
;SpritePlatform.c:26: void Update_SpritePlatform() {
;	---------------------------------
; Function Update_SpritePlatform
; ---------------------------------
_Update_SpritePlatform::
	add	sp, #-12
;SpritePlatform.c:27: struct PlatformInfo* data_platform = (struct PlatformInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00146$
	inc	c
00146$:
	ldhl	sp,	#2
	ld	(hl), b
	inc	hl
	ld	(hl), c
;SpritePlatform.c:28: UINT8 r = 0x1;//2;
	ld	b, #0x01
;SpritePlatform.c:29: if (data_platform->step < 30 | data_platform->step > 170){
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c,a
	sub	a, #0x1e
	ld	a, #0x00
	rla
	ldhl	sp,	#11
	ld	(hl), a
	ld	a, #0xaa
	sub	a, c
	ld	a, #0x00
	rla
	or	a, (hl)
	or	a, a
	jr	Z,00102$
;SpritePlatform.c:30: r=0x7;//8;
	ld	b, #0x07
00102$:
;SpritePlatform.c:32: if(data_platform->step > 70 & data_platform->step < 130){
	ld	a, #0x46
	sub	a, c
	ld	a, #0x00
	rla
	ldhl	sp,	#11
	ld	(hl), a
	ld	a, c
	sub	a, #0x82
	ld	a, #0x00
	rla
	and	a,(hl)
	jr	Z,00104$
;SpritePlatform.c:33: r=0x7;//8;
	ld	b, #0x07
00104$:
;SpritePlatform.c:36: if (data_platform->step < (data_platform->distance/2)){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0001
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpritePlatform.c:37: data_platform->vx = 1;
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), d
;SpritePlatform.c:35: if ((data_platform->step & r) == 0){
	ld	a, c
	and	a, b
	ld	e,a
	or	a, a
	jp	NZ, 00109$
;SpritePlatform.c:36: if (data_platform->step < (data_platform->distance/2)){
	inc	hl
	inc	hl
	ld	(hl), c
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	inc	sp
	inc	sp
	push	bc
	bit	7, b
	jr	Z,00115$
	inc	bc
	inc	sp
	inc	sp
	push	bc
00115$:
	pop	bc
	push	bc
	sra	b
	rr	c
	ldhl	sp,	#11
	ld	a, (hl-)
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl-), a
	ld	a, (hl)
	sub	a, c
	inc	hl
	ld	a, (hl)
	sbc	a, b
	ld	d, (hl)
	ld	a, b
	ld	e, a
	bit	7, e
	jr	Z,00147$
	bit	7, d
	jr	NZ,00148$
	cp	a, a
	jr	00148$
00147$:
	bit	7, d
	jr	Z,00148$
	scf
00148$:
	jr	NC,00106$
;SpritePlatform.c:37: data_platform->vx = 1;
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
	jr	00107$
00106$:
;SpritePlatform.c:39: data_platform->vx = -1;
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0xff
00107$:
;SpritePlatform.c:41: TranslateSprite(THIS, data_platform->vx, 0);	
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	xor	a, a
	push	af
	inc	sp
	push	bc
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	jr	00110$
00109$:
;SpritePlatform.c:43: data_platform->vx = 0;
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00110$:
;SpritePlatform.c:45: data_platform->step += 1;
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	c
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpritePlatform.c:46: if (data_platform->step >= data_platform->distance){
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	af
	ld	a,(de)
	ld	c, a
	pop	af
	sub	a, c
	jp	C, 00113$
;SpritePlatform.c:47: data_platform->step = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpritePlatform.c:48: THIS->x = data_platform->initx;		
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#10
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,#(3 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
00113$:
;SpritePlatform.c:50: }
	add	sp, #12
	ret
;SpritePlatform.c:52: void Destroy_SpritePlatform() {
;	---------------------------------
; Function Destroy_SpritePlatform
; ---------------------------------
_Destroy_SpritePlatform::
;SpritePlatform.c:53: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
