;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpriteArrow
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpriteArrow
	.globl _Update_SpriteArrow
	.globl _Start_SpriteArrow
	.globl _SpriteManagerRemove
	.globl _CheckCollision
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpriteArrow
	.globl _internal_t
	.globl _tile_a_collision
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _spine
	.globl _arrow_fire_g
	.globl _arrow_blast_g
	.globl _arrow_stone_g
	.globl _arrow_water_g
	.globl _arrow_normal_g
	.globl _arrow_fire_v
	.globl _arrow_blast_v
	.globl _arrow_stone_v
	.globl _arrow_water_v
	.globl _arrow_normal_v
	.globl _arrow_fire_d
	.globl _arrow_blast_d
	.globl _arrow_stone_d
	.globl _arrow_water_d
	.globl _arrow_normal_d
	.globl _arrow_fire
	.globl _arrow_blast
	.globl _arrow_stone
	.globl _arrow_water
	.globl _arrow_normal
	.globl _SetupArrow
	.globl _CheckCollisionArrowTile
	.globl _RedirectArrow
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
_tile_a_collision::
	.ds 1
_internal_t::
	.ds 1
;--------------------------------------------------------
; CODE rom data
;--------------------------------------------------------
	.area _CODE
_bank_SpriteArrow:
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
;SpriteArrow.c:38: void Start_SpriteArrow() {
;	---------------------------------
; Function Start_SpriteArrow
; ---------------------------------
_Start_SpriteArrow::
;SpriteArrow.c:40: THIS->coll_x = 5;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000d
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x05
;SpriteArrow.c:41: THIS->coll_y = 6;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000e
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x06
;SpriteArrow.c:42: THIS->coll_w = 3;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000f
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x03
;SpriteArrow.c:43: THIS->coll_h = 3;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0010
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x03
;SpriteArrow.c:45: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
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
;SpriteArrow.c:46: data->type = 0;
	ld	e, c
	ld	d, b
	ld	a, (de)
	and	a, #0xf0
	ld	(de),a
;SpriteArrow.c:47: data->original_type = 0;
	ld	e, c
	ld	d, b
	ld	a, (de)
	and	a, #0x0f
	ld	(de),a
;SpriteArrow.c:48: data->arrowdir = -1;
	inc	bc
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	(hl), #0xff
;SpriteArrow.c:49: }
	ret
_arrow_normal:
	.db #0x01	; 1
	.db #0x00	; 0
_arrow_water:
	.db #0x01	; 1
	.db #0x01	; 1
_arrow_stone:
	.db #0x01	; 1
	.db #0x02	; 2
_arrow_blast:
	.db #0x01	; 1
	.db #0x03	; 3
_arrow_fire:
	.db #0x01	; 1
	.db #0x04	; 4
_arrow_normal_d:
	.db #0x01	; 1
	.db #0x05	; 5
_arrow_water_d:
	.db #0x01	; 1
	.db #0x06	; 6
_arrow_stone_d:
	.db #0x01	; 1
	.db #0x07	; 7
_arrow_blast_d:
	.db #0x01	; 1
	.db #0x08	; 8
_arrow_fire_d:
	.db #0x01	; 1
	.db #0x09	; 9
_arrow_normal_v:
	.db #0x01	; 1
	.db #0x0a	; 10
_arrow_water_v:
	.db #0x01	; 1
	.db #0x0b	; 11
_arrow_stone_v:
	.db #0x01	; 1
	.db #0x0c	; 12
_arrow_blast_v:
	.db #0x01	; 1
	.db #0x0d	; 13
_arrow_fire_v:
	.db #0x01	; 1
	.db #0x0e	; 14
_arrow_normal_g:
	.db #0x01	; 1
	.db #0x0f	; 15
_arrow_water_g:
	.db #0x01	; 1
	.db #0x10	; 16
_arrow_stone_g:
	.db #0x01	; 1
	.db #0x11	; 17
_arrow_blast_g:
	.db #0x01	; 1
	.db #0x12	; 18
_arrow_fire_g:
	.db #0x01	; 1
	.db #0x13	; 19
_spine:
	.db #0x01	; 1
	.db #0x14	; 20
;SpriteArrow.c:51: void Update_SpriteArrow() {
;	---------------------------------
; Function Update_SpriteArrow
; ---------------------------------
_Update_SpriteArrow::
	add	sp, #-7
;SpriteArrow.c:54: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00161$
	inc	c
00161$:
	ldhl	sp,	#5
	ld	(hl), b
	inc	hl
	ld	(hl), c
;SpriteArrow.c:55: internal_t = data->type;
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	ld	a, (hl)
	and	a, #0x0f
	ld	hl, #_internal_t
;SpriteArrow.c:56: if (internal_t != 0 & data->arrowdir != -1) {
	ld	(hl),a
	sub	a,#0x01
	ld	a, #0x00
	rla
	xor	a, #0x01
	ldhl	sp,	#4
	ld	(hl+), a
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	inc	a
	ld	a, #0x01
	jr	Z,00163$
	xor	a, a
00163$:
	xor	a, #0x01
	ldhl	sp,	#4
	and	a, (hl)
	bit	0, a
	jr	Z,00102$
;SpriteArrow.c:57: SetupArrow();
	call	_SetupArrow
;SpriteArrow.c:58: data->original_type = internal_t;
	ldhl	sp,#(6 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_internal_t
	ld	a, (hl)
	swap	a
	and	a, #0xf0
	ld	l, a
	ld	a, (bc)
	and	a, #0x0f
	or	a, l
	ld	(bc), a
00102$:
;SpriteArrow.c:54: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
;SpriteArrow.c:60: if(SPRITE_GET_VMIRROR(THIS)) {
	pop	de
	push	de
	ld	hl, #0x000c
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#2
	ld	(hl), a
;SpriteArrow.c:62: tile_a_collision = TranslateSprite(THIS, -data->vx << delta_time, data->vy << delta_time);
	ldhl	sp,#(6 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0001
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:61: THIS->coll_x = 0;
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:60: if(SPRITE_GET_VMIRROR(THIS)) {
	ldhl	sp,	#2
	bit	5, (hl)
	jp	Z,00104$
;SpriteArrow.c:61: THIS->coll_x = 0;
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpriteArrow.c:62: tile_a_collision = TranslateSprite(THIS, -data->vx << delta_time, data->vy << delta_time);
	ld	a, (bc)
	ld	b, a
	ld	hl, #_delta_time
	ld	c, (hl)
	ld	a, c
	inc	a
	jr	00166$
00165$:
	sla	b
00166$:
	dec	a
	jr	NZ,00165$
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	and	a, #0x0f
	inc	hl
	inc	hl
	ld	(hl), a
	xor	a, a
	sub	a, (hl)
	ld	(hl), a
	ld	d, (hl)
	inc	c
	jr	00168$
00167$:
	sla	d
00168$:
	dec	c
	jr	NZ,00167$
	push	bc
	inc	sp
	push	de
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	ld	hl, #_tile_a_collision
	ld	(hl), e
	jp	00105$
00104$:
;SpriteArrow.c:64: THIS->coll_x = 5;
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x05
;SpriteArrow.c:65: tile_a_collision = TranslateSprite(THIS, data->vx << delta_time, data->vy << delta_time);
	ld	a, (bc)
	ld	b, a
	ld	hl, #_delta_time
	ld	c, (hl)
	ld	a, c
	inc	a
	jr	00170$
00169$:
	sla	b
00170$:
	dec	a
	jr	NZ,00169$
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	and	a, #0x0f
	ld	d, a
	inc	c
	jr	00172$
00171$:
	sla	d
00172$:
	dec	c
	jr	NZ,00171$
	push	bc
	inc	sp
	push	de
	inc	sp
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_TranslateSprite
	add	sp, #4
	ld	hl, #_tile_a_collision
	ld	(hl), e
00105$:
;SpriteArrow.c:67: if(tile_a_collision){
	ld	hl, #_tile_a_collision
	ld	a, (hl)
	or	a, a
	jr	Z,00107$
;SpriteArrow.c:68: CheckCollisionArrowTile();
	call	_CheckCollisionArrowTile
00107$:
;SpriteArrow.c:70: SPRITEMANAGER_ITERATE(scroll_a_tile, iaspr) {
	ld	a, (#(_sprite_manager_updatables + 0x0001) + 0)
	ld	c, a
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_sprite_manager_sprites
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	xor	a, a
	ldhl	sp,	#6
	ld	(hl), a
00116$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	a, (hl)
	ldhl	sp,	#5
	ld	(hl), a
	ldhl	sp,	#6
	ld	a, (hl-)
	sub	a, (hl)
	jp	Z,00118$
;SpriteArrow.c:71: if(iaspr->type == SpriteItem) {
	ld	hl, #0x0011
	add	hl, bc
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
	sub	a, #0x03
	jp	NZ,00117$
;SpriteArrow.c:72: if(CheckCollision(THIS, iaspr)) {
	push	bc
	push	bc
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_CheckCollision
	add	sp, #4
	ld	a, e
	pop	bc
	or	a, a
	jr	Z,00117$
;SpriteArrow.c:73: struct ItemInfo* item_data = (struct ItemInfo*)iaspr->custom_data;
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;SpriteArrow.c:74: if (item_data->collided == 0u){
	ld	a, (bc)
	or	a, a
	jr	NZ,00109$
;SpriteArrow.c:75: SpriteManagerRemove(THIS_IDX);
	ld	hl, #_THIS_IDX
	ld	e, (hl)
	ld	d, #0x00
	push	bc
	push	de
	call	_SpriteManagerRemove
	add	sp, #2
	pop	bc
00109$:
;SpriteArrow.c:77: item_data->collided = 1u;
	ld	a, #0x01
	ld	(bc), a
00117$:
;SpriteArrow.c:70: SPRITEMANAGER_ITERATE(scroll_a_tile, iaspr) {
	ldhl	sp,	#6
	inc	(hl)
	ld	c, (hl)
	ld	b, #0x00
	inc	bc
	ld	hl, #_sprite_manager_updatables
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_sprite_manager_sprites
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	jp	00116$
00118$:
;SpriteArrow.c:86: }
	add	sp, #7
	ret
;SpriteArrow.c:88: void SetupArrow(){
;	---------------------------------
; Function SetupArrow
; ---------------------------------
_SetupArrow::
	add	sp, #-6
;SpriteArrow.c:89: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00247$
	inc	c
00247$:
	ldhl	sp,	#0
	ld	(hl), b
	inc	hl
	ld	(hl), c
;SpriteArrow.c:90: data->arrowdamage = 10u;
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	c,l
	ld	a,h
	ld	(hl), #0x0a
;SpriteArrow.c:91: switch(internal_t) {
	ld	a, #0x06
	ld	hl, #_internal_t
	sub	a, (hl)
	jp	C, 00135$
;SpriteArrow.c:93: switch(data->arrowdir){
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:95: data->vy = 0;
	pop	bc
	push	bc
	inc	bc
	inc	bc
;SpriteArrow.c:96: data->vx = 2;
	pop	de
	push	de
	ld	hl, #0x0001
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:91: switch(internal_t) {
	ld	hl, #_internal_t
	ld	e, (hl)
	ld	d, #0x00
	ld	hl, #00248$
	add	hl, de
	add	hl, de
	add	hl, de
	jp	(hl)
00248$:
	jp	00135$
	jp	00101$
	jp	00107$
	jp	00113$
	jp	00119$
	jp	00125$
	jp	00131$
;SpriteArrow.c:92: case 1:
00101$:
;SpriteArrow.c:93: switch(data->arrowdir){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x01
	jr	Z,00102$
	cp	a, #0x02
	jr	Z,00103$
	cp	a, #0x03
	jp	Z,00104$
	sub	a, #0x04
	jp	Z,00105$
	jp	00106$
;SpriteArrow.c:94: case 1: //orizzontale
00102$:
;SpriteArrow.c:95: data->vy = 0;
	xor	a, a
	ld	(bc), a
;SpriteArrow.c:96: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:97: SetSpriteAnim(THIS, arrow_normal, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_normal
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:98: break;
	jp	00106$
;SpriteArrow.c:99: case 2: //diagonale
00103$:
;SpriteArrow.c:100: data->vy = -1;
	ld	a, #0xff
	ld	(bc), a
;SpriteArrow.c:101: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:102: SetSpriteAnim(THIS, arrow_normal_d, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_normal_d
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:103: break;
	jp	00106$
;SpriteArrow.c:104: case 3: //verticale in su
00104$:
;SpriteArrow.c:105: data->vy = -2;
	ld	a, #0xfe
	ld	(bc), a
;SpriteArrow.c:106: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:107: SetSpriteAnim(THIS, arrow_normal_v, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_normal_v
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:108: break;
	jr	00106$
;SpriteArrow.c:109: case 4: //verticale in giu
00105$:
;SpriteArrow.c:110: data->vy = 2;
	ld	a, #0x02
	ld	(bc), a
;SpriteArrow.c:111: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:112: SetSpriteAnim(THIS, arrow_normal_g, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_normal_g
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:114: }
00106$:
;SpriteArrow.c:115: data->type = 0;
	pop	bc
	push	bc
	ld	a, (bc)
	and	a, #0xf0
	ld	(bc),a
;SpriteArrow.c:116: break;
	jp	00135$
;SpriteArrow.c:117: case 2:
00107$:
;SpriteArrow.c:118: switch(data->arrowdir){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x01
	jr	Z,00108$
	cp	a, #0x02
	jr	Z,00109$
	cp	a, #0x03
	jp	Z,00110$
	sub	a, #0x04
	jp	Z,00111$
	jp	00112$
;SpriteArrow.c:119: case 1:
00108$:
;SpriteArrow.c:120: data->vy = 0;
	xor	a, a
	ld	(bc), a
;SpriteArrow.c:121: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:122: SetSpriteAnim(THIS, arrow_water, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_water
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:123: break;
	jp	00112$
;SpriteArrow.c:124: case 2:
00109$:
;SpriteArrow.c:125: data->vy = -1;
	ld	a, #0xff
	ld	(bc), a
;SpriteArrow.c:126: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:127: SetSpriteAnim(THIS, arrow_water_d, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_water_d
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:128: break;
	jp	00112$
;SpriteArrow.c:129: case 3:
00110$:
;SpriteArrow.c:130: data->vy = -2;
	ld	a, #0xfe
	ld	(bc), a
;SpriteArrow.c:131: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:132: SetSpriteAnim(THIS, arrow_water_v, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_water_v
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:133: break;
	jr	00112$
;SpriteArrow.c:134: case 4:
00111$:
;SpriteArrow.c:135: data->vy = 2;
	ld	a, #0x02
	ld	(bc), a
;SpriteArrow.c:136: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:137: SetSpriteAnim(THIS, arrow_water_g, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_water_g
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:139: }						
00112$:
;SpriteArrow.c:140: data->type = 0;
	pop	bc
	push	bc
	ld	a, (bc)
	and	a, #0xf0
	ld	(bc),a
;SpriteArrow.c:141: break;
	jp	00135$
;SpriteArrow.c:142: case 3:
00113$:
;SpriteArrow.c:143: switch(data->arrowdir){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x01
	jr	Z,00114$
	cp	a, #0x02
	jr	Z,00115$
	cp	a, #0x03
	jp	Z,00116$
	sub	a, #0x04
	jp	Z,00117$
	jp	00118$
;SpriteArrow.c:144: case 1:
00114$:
;SpriteArrow.c:145: data->vy = 0;
	xor	a, a
	ld	(bc), a
;SpriteArrow.c:146: data->vx = 1;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x01
	ld	(hl),a
;SpriteArrow.c:147: SetSpriteAnim(THIS, arrow_stone, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_stone
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:148: break;
	jp	00118$
;SpriteArrow.c:149: case 2:
00115$:
;SpriteArrow.c:150: data->vy = -1;
	ld	a, #0xff
	ld	(bc), a
;SpriteArrow.c:151: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:152: SetSpriteAnim(THIS, arrow_stone_d, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_stone_d
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:153: break;
	jp	00118$
;SpriteArrow.c:154: case 3:
00116$:
;SpriteArrow.c:155: data->vy = -1;
	ld	a, #0xff
	ld	(bc), a
;SpriteArrow.c:156: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:157: SetSpriteAnim(THIS, arrow_stone_v, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_stone_v
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:158: break;
	jr	00118$
;SpriteArrow.c:159: case 4:
00117$:
;SpriteArrow.c:160: data->vy = 1;
	ld	a, #0x01
	ld	(bc), a
;SpriteArrow.c:161: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:162: SetSpriteAnim(THIS, arrow_stone_g, 18u);
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_stone_g
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:164: }						
00118$:
;SpriteArrow.c:165: data->type = 0;
	pop	bc
	push	bc
	ld	a, (bc)
	and	a, #0xf0
	ld	(bc),a
;SpriteArrow.c:166: break;
	jp	00135$
;SpriteArrow.c:167: case 4:
00119$:
;SpriteArrow.c:168: switch(data->arrowdir){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x01
	jr	Z,00120$
	cp	a, #0x02
	jr	Z,00121$
	cp	a, #0x03
	jp	Z,00122$
	sub	a, #0x04
	jp	Z,00123$
	jp	00124$
;SpriteArrow.c:169: case 1:
00120$:
;SpriteArrow.c:170: data->vy = 0;
	xor	a, a
	ld	(bc), a
;SpriteArrow.c:171: data->vx = 3;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x03
	ld	(hl),a
;SpriteArrow.c:172: SetSpriteAnim(THIS, arrow_blast, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_blast
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:173: break;
	jp	00124$
;SpriteArrow.c:174: case 2:
00121$:
;SpriteArrow.c:175: data->vy = -2;
	ld	a, #0xfe
	ld	(bc), a
;SpriteArrow.c:176: data->vx = 3;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x03
	ld	(hl),a
;SpriteArrow.c:177: SetSpriteAnim(THIS, arrow_blast_d, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_blast_d
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:178: break;
	jp	00124$
;SpriteArrow.c:179: case 3:
00122$:
;SpriteArrow.c:180: data->vy = -3;
	ld	a, #0xfd
	ld	(bc), a
;SpriteArrow.c:181: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:182: SetSpriteAnim(THIS, arrow_blast_v, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_blast_v
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:183: break;
	jr	00124$
;SpriteArrow.c:184: case 4:
00123$:
;SpriteArrow.c:185: data->vy = 3;
	ld	a, #0x03
	ld	(bc), a
;SpriteArrow.c:186: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:187: SetSpriteAnim(THIS, arrow_blast_g, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_blast_g
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:189: }						
00124$:
;SpriteArrow.c:190: data->type = 0;
	pop	bc
	push	bc
	ld	a, (bc)
	and	a, #0xf0
	ld	(bc),a
;SpriteArrow.c:191: break;
	jp	00135$
;SpriteArrow.c:192: case 5:
00125$:
;SpriteArrow.c:193: switch(data->arrowdir){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x01
	jr	Z,00126$
	cp	a, #0x02
	jr	Z,00127$
	cp	a, #0x03
	jp	Z,00128$
	sub	a, #0x04
	jp	Z,00129$
	jp	00130$
;SpriteArrow.c:194: case 1:
00126$:
;SpriteArrow.c:195: data->vy = 0;
	xor	a, a
	ld	(bc), a
;SpriteArrow.c:196: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:197: SetSpriteAnim(THIS, arrow_fire, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_fire
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:198: break;
	jp	00130$
;SpriteArrow.c:199: case 2:
00127$:
;SpriteArrow.c:200: data->vy = -1;
	ld	a, #0xff
	ld	(bc), a
;SpriteArrow.c:201: data->vx = 2;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:202: SetSpriteAnim(THIS, arrow_fire_d, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_fire_d
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:203: break;
	jp	00130$
;SpriteArrow.c:204: case 3:
00128$:
;SpriteArrow.c:205: data->vy = -2;
	ld	a, #0xfe
	ld	(bc), a
;SpriteArrow.c:206: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:207: SetSpriteAnim(THIS, arrow_fire_v, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_fire_v
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:208: break;
	jr	00130$
;SpriteArrow.c:209: case 4:
00129$:
;SpriteArrow.c:210: data->vy = 2;
	ld	a, #0x02
	ld	(bc), a
;SpriteArrow.c:211: data->vx = 0;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	ld	(hl),a
;SpriteArrow.c:212: SetSpriteAnim(THIS, arrow_fire_g, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_arrow_fire_g
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:214: }						
00130$:
;SpriteArrow.c:215: data->type = 0;
	pop	bc
	push	bc
	ld	a, (bc)
	and	a, #0xf0
	ld	(bc),a
;SpriteArrow.c:216: break;
	jp	00135$
;SpriteArrow.c:217: case 6:
00131$:
;SpriteArrow.c:218: switch(data->arrowdir){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	jr	NZ,00135$
;SpriteArrow.c:220: data->vy = 0;
	xor	a, a
	ld	(bc), a
;SpriteArrow.c:221: data->vx = 2;
	inc	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, (hl)
	and	a, #0xf0
	or	a, #0x02
	ld	(hl),a
;SpriteArrow.c:222: SetSpriteAnim(THIS, spine, 18u);	
	ld	a, #0x12
	push	af
	inc	sp
	ld	hl, #_spine
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteArrow.c:227: }
00135$:
;SpriteArrow.c:228: }
	add	sp, #6
	ret
;SpriteArrow.c:230: void CheckCollisionArrowTile() {	
;	---------------------------------
; Function CheckCollisionArrowTile
; ---------------------------------
_CheckCollisionArrowTile::
;SpriteArrow.c:231: if (tile_a_collision < 18u & tile_a_collision > 9u){
	ld	hl, #_tile_a_collision
	ld	a, (hl)
	sub	a, #0x12
	ld	a, #0x00
	rla
	ld	c, a
	ld	a, #0x09
	sub	a, (hl)
	ld	a, #0x00
	rla
	and	a,c
	jr	Z,00102$
;SpriteArrow.c:232: RedirectArrow();
	jp	_RedirectArrow
00102$:
;SpriteArrow.c:234: SpriteManagerRemove(THIS_IDX);
	ld	hl, #_THIS_IDX
	ld	c, (hl)
	ld	b, #0x00
	push	bc
	call	_SpriteManagerRemove
	add	sp, #2
;SpriteArrow.c:236: }
	ret
;SpriteArrow.c:238: void RedirectArrow(){
;	---------------------------------
; Function RedirectArrow
; ---------------------------------
_RedirectArrow::
	add	sp, #-5
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0019
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
;SpriteArrow.c:240: switch(tile_a_collision) {
	ld	hl, #_tile_a_collision
	ld	a, (hl)
	sub	a, #0x0a
	jp	C, 00109$
	ld	a, #0x11
	sub	a, (hl)
	jp	C, 00109$
	ld	a, (hl)
	add	a, #0xf6
	ldhl	sp,	#2
	ld	(hl), a
;SpriteArrow.c:242: data->arrowdir = 4;
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:260: SPRITE_SET_VMIRROR(THIS);
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
;SpriteArrow.c:240: switch(tile_a_collision) {
	ldhl	sp,	#2
	ld	e, (hl)
	ld	d, #0x00
	ld	hl, #00122$
	add	hl, de
	add	hl, de
	add	hl, de
	jp	(hl)
00122$:
	jp	00101$
	jp	00102$
	jp	00103$
	jp	00104$
	jp	00105$
	jp	00106$
	jp	00107$
	jp	00108$
;SpriteArrow.c:241: case 10u: //da SX a GIU
00101$:
;SpriteArrow.c:242: data->arrowdir = 4;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x04
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
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
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:244: THIS->y += 4;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
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
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:245: break;
	jp	00109$
;SpriteArrow.c:246: case 11u: //da DX a GIU
00102$:
;SpriteArrow.c:247: data->arrowdir = 4;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x04
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:248: THIS->x -= 2;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	dec	bc
	dec	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:244: THIS->y += 4;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:249: THIS->y += 4;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:250: break;
	jp	00109$
;SpriteArrow.c:251: case 12u: //da SX a SU
00103$:
;SpriteArrow.c:252: data->arrowdir = 3;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x03
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:253: THIS->x += 4;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:254: break;
	jp	00109$
;SpriteArrow.c:255: case 13u: // da DX a SU
00104$:
;SpriteArrow.c:256: data->arrowdir = 3;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x03
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:257: THIS->x -= 4;
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
	add	a, #0xfc
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
;SpriteArrow.c:258: break;
	jp	00109$
;SpriteArrow.c:259: case 14u: //da SU a SX
00105$:
;SpriteArrow.c:260: SPRITE_SET_VMIRROR(THIS);
	ld	a, (bc)
	set	5, a
	ld	(bc), a
;SpriteArrow.c:261: data->arrowdir = 1;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:262: THIS->x -= 4;
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
	add	a, #0xfc
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
;SpriteArrow.c:263: break;
	jp	00109$
;SpriteArrow.c:264: case 15u: //da SU a DX
00106$:
;SpriteArrow.c:265: SPRITE_UNSET_VMIRROR(THIS);
	ld	a, (bc)
	res	5, a
	ld	(bc), a
;SpriteArrow.c:266: data->arrowdir = 1;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:267: THIS->x += 4;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:244: THIS->y += 4;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:268: THIS->y += 6;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	inc	de
	ld	a,(de)
	ld	c, a
	ld	a, b
	add	a, #0x06
	ld	b, a
	jr	NC,00123$
	inc	c
00123$:
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
	inc	hl
	ld	(hl), c
;SpriteArrow.c:269: break;
	jp	00109$
;SpriteArrow.c:270: case 16u://da GIU a DX
00107$:
;SpriteArrow.c:271: SPRITE_UNSET_VMIRROR(THIS);
	ld	a, (bc)
	res	5, a
	ld	(bc), a
;SpriteArrow.c:272: data->arrowdir = 1;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:273: THIS->x += 4;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:244: THIS->y += 4;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:274: THIS->y -= 4;
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
	add	a, #0xfc
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
;SpriteArrow.c:275: break;
	jp	00109$
;SpriteArrow.c:276: case 17u: //da GIU a SX
00108$:
;SpriteArrow.c:277: SPRITE_SET_VMIRROR(THIS);
	ld	a, (bc)
	set	5, a
	ld	(bc), a
;SpriteArrow.c:278: data->arrowdir = 1;
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:243: THIS->x += 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:279: THIS->x -= 4;
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
	add	a, #0xfc
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
;SpriteArrow.c:239: struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteArrow.c:244: THIS->y += 4;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
;SpriteArrow.c:280: THIS->y -= 4;
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
	add	a, #0xfc
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
;SpriteArrow.c:282: }
00109$:
;SpriteArrow.c:283: data->type = data->original_type;
	pop	bc
	push	bc
	pop	de
	push	de
	ld	l, e
	ld	h, d
	ld	a, (hl)
	swap	a
	and	a, #0x0f
	and	a, #0x0f
	ld	l, a
	ld	a, (bc)
	and	a, #0xf0
	or	a, l
	ld	(bc), a
;SpriteArrow.c:284: }
	add	sp, #5
	ret
;SpriteArrow.c:286: void Destroy_SpriteArrow() {
;	---------------------------------
; Function Destroy_SpriteArrow
; ---------------------------------
_Destroy_SpriteArrow::
;SpriteArrow.c:287: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
