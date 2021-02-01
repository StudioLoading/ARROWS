;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpriteItem
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpriteItem
	.globl _Update_SpriteItem
	.globl _Start_SpriteItem
	.globl _CheckCollision
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpriteItem
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _item_dcoin
	.globl _item_wrench
	.globl _item_scrignoaperto
	.globl _item_scrigno
	.globl _item_up
	.globl _item_hp
	.globl _item_coin
	.globl _item_hidden
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
_bank_SpriteItem:
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
;custom_datas.h:44: UINT8 damage_cooldown = 30u;
	ld	hl, #_damage_cooldown
	ld	(hl), #0x1e
;custom_datas.h:45: UINT8 attack_wait = 32u;
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
;SpriteItem.c:19: void Start_SpriteItem() {
;	---------------------------------
; Function Start_SpriteItem
; ---------------------------------
_Start_SpriteItem::
	add	sp, #-2
;SpriteItem.c:21: SetSpriteAnim(THIS, item_hidden, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_hidden
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:23: struct ItemInfo* data = (struct ItemInfo*)THIS->custom_data;
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
;SpriteItem.c:24: data->collided = 0;
	xor	a, a
	ld	(bc), a
;SpriteItem.c:25: data->setup = 1u;
	ld	hl, #0x0004
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x01
;SpriteItem.c:26: data->counter = -1;
	ld	hl, #0x0006
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0xff
;SpriteItem.c:27: data->item_accel_y = 0;
	ld	hl, #0x0002
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x00
;SpriteItem.c:28: data->type = 0;
	inc	bc
	xor	a, a
	ld	(bc), a
;SpriteItem.c:29: THIS->coll_x = 0;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000d
	add	hl, bc
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;SpriteItem.c:30: THIS->coll_y = 0;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000e
	add	hl, bc
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;SpriteItem.c:31: THIS->coll_w = 8;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000f
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x08
;SpriteItem.c:32: THIS->coll_h = 8;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0010
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x08
;SpriteItem.c:33: THIS->lim_x = 255;
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
;SpriteItem.c:34: THIS->lim_y = 255;
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
;SpriteItem.c:35: }
	add	sp, #2
	ret
_item_hidden:
	.db #0x01	; 1
	.db #0x00	; 0
_item_coin:
	.db #0x01	; 1
	.db #0x01	; 1
_item_hp:
	.db #0x01	; 1
	.db #0x03	; 3
_item_up:
	.db #0x01	; 1
	.db #0x02	; 2
_item_scrigno:
	.db #0x01	; 1
	.db #0x04	; 4
_item_scrignoaperto:
	.db #0x01	; 1
	.db #0x05	; 5
_item_wrench:
	.db #0x01	; 1
	.db #0x06	; 6
_item_dcoin:
	.db #0x01	; 1
	.db #0x07	; 7
;SpriteItem.c:37: void Update_SpriteItem() {
;	---------------------------------
; Function Update_SpriteItem
; ---------------------------------
_Update_SpriteItem::
	add	sp, #-15
;SpriteItem.c:39: struct ItemInfo* data = (struct ItemInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00273$
	inc	c
00273$:
	ldhl	sp,	#0
	ld	(hl), b
	inc	hl
	ld	(hl), c
;SpriteItem.c:40: if (data->type == 10){ //gestione scrigno dedicata
	pop	de
	push	de
	ld	hl, #0x0001
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
;SpriteItem.c:41: if (data->setup){
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
;SpriteItem.c:44: data->item_accel_y = 24;
	pop	de
	push	de
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpriteItem.c:49: if(!data->tile_i_collision && delta_time != 0 && data->item_accel_y < 36) { //Do another iteration if there is no collision
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), d
;SpriteItem.c:51: data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
	pop	de
	push	de
	ld	hl, #0x0007
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), d
;SpriteItem.c:57: if (data->counter == -1 & data->collided & data->type != data->content_type){
	pop	de
	push	de
	ld	hl, #0x0006
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#10
	ld	(hl+), a
	ld	(hl), d
;SpriteItem.c:40: if (data->type == 10){ //gestione scrigno dedicata
	ld	a, c
	sub	a, #0x0a
	jp	NZ,00135$
;SpriteItem.c:41: if (data->setup){
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jr	Z,00116$
;SpriteItem.c:42: SetSpriteAnim(THIS, item_scrigno, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_scrigno
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:43: data->setup = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpriteItem.c:44: data->item_accel_y = 24;
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
	jp	00136$
00116$:
;SpriteItem.c:46: if(data->item_accel_y < 24) {
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c,a
	xor	a, #0x80
	sub	a, #0x98
	jr	NC,00102$
;SpriteItem.c:47: data->item_accel_y += 1;
	inc	c
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00102$:
;SpriteItem.c:49: if(!data->tile_i_collision && delta_time != 0 && data->item_accel_y < 36) { //Do another iteration if there is no collision
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jp	NZ, 00104$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00104$
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b,a
	xor	a, #0x80
	sub	a, #0xa4
	jp	NC, 00104$
;SpriteItem.c:50: data->item_accel_y += 2;
	inc	b
	inc	b
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
;SpriteItem.c:51: data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
	sra	b
	sra	b
	sra	b
	sra	b
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	push	bc
	inc	sp
	push	af
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	ld	c, e
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00104$:
;SpriteItem.c:53: data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	sra	b
	sra	b
	sra	b
	sra	b
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	push	bc
	inc	sp
	push	af
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	ld	a, e
	ldhl	sp,	#13
	push	af
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	pop	af
	ld	(hl), a
;SpriteItem.c:54: if(data->tile_i_collision) {
	or	a, a
	jr	Z,00108$
;SpriteItem.c:55: data->item_accel_y = 0;	
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
00108$:
;SpriteItem.c:57: if (data->counter == -1 & data->collided & data->type != data->content_type){
	ldhl	sp,#(11 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	a
	ld	a, #0x01
	jr	Z,00277$
	xor	a, a
00277$:
	ld	c, a
	pop	de
	push	de
	ld	a,(de)
	and	a, c
	ld	c, a
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	pop	de
	push	de
	ld	hl, #0x0005
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#12
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	hl
	ld	(hl), a
	ld	a, b
	sub	a, (hl)
	ld	a, #0x01
	jr	Z,00279$
	xor	a, a
00279$:
	xor	a, #0x01
	and	a,c
	jr	Z,00110$
;SpriteItem.c:58: SetSpriteAnim(THIS, item_scrignoaperto, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_scrignoaperto
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:59: data->counter = 24;
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
00110$:
;SpriteItem.c:57: if (data->counter == -1 & data->collided & data->type != data->content_type){
	ldhl	sp,#(11 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
;SpriteItem.c:61: if(data->counter > 0){
	ld	c,a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, c
	bit	7, e
	jr	Z,00280$
	bit	7, d
	jr	NZ,00281$
	cp	a, a
	jr	00281$
00280$:
	bit	7, d
	jr	Z,00281$
	scf
00281$:
	jr	NC,00112$
;SpriteItem.c:62: data->counter -= 1;
	dec	c
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00112$:
;SpriteItem.c:64: if (data->counter == 0){
	ldhl	sp,#(11 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jp	NZ, 00136$
;SpriteItem.c:39: struct ItemInfo* data = (struct ItemInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteItem.c:65: THIS->y -= 20;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#10
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	ld	a, c
	add	a, #0xec
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteItem.c:66: data->type = data->content_type;
	ldhl	sp,#(13 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpriteItem.c:67: data->setup = 1u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpriteItem.c:68: data->item_accel_y = 24;
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
;SpriteItem.c:69: return;
	jp	00145$
00135$:
;SpriteItem.c:73: if (data->collided | data->item_accel_y | data->counter == 0){
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, c
	ld	c, a
	ldhl	sp,#(11 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	sub	a,#0x01
	ld	a, #0x00
	rla
	or	a, c
	or	a, a
	jp	Z, 00136$
;SpriteItem.c:74: if (data->setup){ //inizio setup
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jp	Z, 00125$
;SpriteItem.c:75: data->setup = 0u;
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpriteItem.c:76: switch(data->type){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x01
	jr	Z,00118$
	cp	a, #0x02
	jr	Z,00119$
	cp	a, #0x03
	jp	Z,00120$
	cp	a, #0x06
	jp	Z,00121$
	sub	a, #0x07
	jp	Z,00122$
	jp	00125$
;SpriteItem.c:77: case 1: //coin
00118$:
;SpriteItem.c:78: SetSpriteAnim(THIS, item_coin, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_coin
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:79: break;
	jp	00125$
;SpriteItem.c:80: case 2: //hp
00119$:
;SpriteItem.c:81: SetSpriteAnim(THIS, item_hp, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_hp
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:82: break;
	jp	00125$
;SpriteItem.c:83: case 3: //up
00120$:
;SpriteItem.c:84: SetSpriteAnim(THIS, item_up, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_up
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:85: break;
	jp	00125$
;SpriteItem.c:86: case 6: //wrench
00121$:
;SpriteItem.c:87: SetSpriteAnim(THIS, item_wrench, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_wrench
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:88: break;
	jr	00125$
;SpriteItem.c:89: case 7: //dcoin
00122$:
;SpriteItem.c:90: SetSpriteAnim(THIS, item_dcoin, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_item_dcoin
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteItem.c:91: THIS->coll_y = 8;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000e
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x08
;SpriteItem.c:93: }
00125$:
;SpriteItem.c:96: if(data->item_accel_y < 24) {
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c,a
	xor	a, #0x80
	sub	a, #0x98
	jr	NC,00127$
;SpriteItem.c:97: data->item_accel_y += 1;
	inc	c
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00127$:
;SpriteItem.c:99: data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	sra	b
	sra	b
	sra	b
	sra	b
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	push	bc
	inc	sp
	push	af
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	ld	a, e
	ldhl	sp,	#13
	push	af
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	pop	af
	ld	(hl), a
;SpriteItem.c:100: if(!data->tile_i_collision && delta_time != 0 && data->item_accel_y < 24) { //Do another iteration if there is no collision
	or	a, a
	jp	NZ, 00136$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00136$
;SpriteItem.c:96: if(data->item_accel_y < 24) {
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
;SpriteItem.c:100: if(!data->tile_i_collision && delta_time != 0 && data->item_accel_y < 24) { //Do another iteration if there is no collision
	ld	b,a
	xor	a, #0x80
	sub	a, #0x98
	jp	NC, 00136$
;SpriteItem.c:101: data->item_accel_y += 2;
	inc	b
	inc	b
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
;SpriteItem.c:102: data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
	sra	b
	sra	b
	sra	b
	sra	b
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	push	bc
	inc	sp
	push	af
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	ld	c, e
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00136$:
;SpriteItem.c:110: SPRITEMANAGER_ITERATE(scroll_i_tile, iispr) {
	ld	hl, #(_sprite_manager_updatables + 0x0001) + 0
	ld	a, (hl)
	ldhl	sp,	#14
	ld	(hl), a
	ldhl	sp,	#14
	ld	a, (hl-)
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl-), a
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	sla	c
	rl	b
	ld	hl, #_sprite_manager_sprites
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#12
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
00143$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#14
	ld	a, (hl)
	sub	a, c
	jp	Z,00145$
;SpriteItem.c:111: if(iispr->type == SpritePlatform) {
	ldhl	sp,#(13 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0011
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	sub	a, #0x02
	jp	NZ,00144$
;SpriteItem.c:112: if(CheckCollision(THIS, iispr)) {
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_CheckCollision
	add	sp, #4
	ld	a, e
	or	a, a
	jr	Z,00144$
;SpriteItem.c:113: data->item_accel_y = 0;
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpriteItem.c:114: struct PlatformInfo* datapl = (struct PlatformInfo*)iispr->custom_data;
	ldhl	sp,#(13 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
;SpriteItem.c:115: data->vx = datapl->vx;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00144$:
;SpriteItem.c:110: SPRITEMANAGER_ITERATE(scroll_i_tile, iispr) {
	ldhl	sp,	#14
	inc	(hl)
	ld	c, (hl)
	ld	b, #0x00
	inc	bc
	ldhl	sp,	#10
	ld	(hl), c
	inc	hl
	ld	(hl), b
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #_sprite_manager_updatables
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#12
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	(hl-), a
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl-), a
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#13
	ld	a, (hl-)
	dec	hl
	ld	(hl-), a
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #_sprite_manager_sprites
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#12
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	jp	00143$
00145$:
;SpriteItem.c:119: }
	add	sp, #15
	ret
;SpriteItem.c:121: void Destroy_SpriteItem() {
;	---------------------------------
; Function Destroy_SpriteItem
; ---------------------------------
_Destroy_SpriteItem::
;SpriteItem.c:122: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
