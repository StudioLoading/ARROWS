;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpriteScorpion
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpriteScorpion
	.globl _Update_SpriteScorpion
	.globl _Start_SpriteScorpion
	.globl _PlayFx
	.globl _SpriteManagerRemoveSprite
	.globl _CheckCollision
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpriteScorpion
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _scorpion_dead
	.globl _scorpion_hit
	.globl _scorpion_walk
	.globl _scorpion_idle
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
_bank_SpriteScorpion:
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
;SpriteScorpion.c:20: void Start_SpriteScorpion() {
;	---------------------------------
; Function Start_SpriteScorpion
; ---------------------------------
_Start_SpriteScorpion::
	add	sp, #-2
;SpriteScorpion.c:22: THIS->coll_x = 2;
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
;SpriteScorpion.c:23: THIS->coll_y = 0;
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
;SpriteScorpion.c:24: THIS->coll_w = 12;
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
;SpriteScorpion.c:25: THIS->coll_h = 16;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0010
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x10
;SpriteScorpion.c:26: THIS->lim_x = 255u;
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
;SpriteScorpion.c:27: THIS->lim_y = 244u;
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
	ld	(hl), #0xf4
	inc	hl
	ld	(hl), #0x00
;SpriteScorpion.c:28: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
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
;SpriteScorpion.c:29: SetSpriteAnim(THIS, scorpion_idle, 8u);
	push	bc
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_scorpion_idle
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	pop	bc
;SpriteScorpion.c:30: data->enemy_accel_y = 24;
	ld	l, c
	ld	h, b
	ld	(hl), #0x18
	inc	hl
	ld	(hl), #0x00
;SpriteScorpion.c:31: data->vx = 1;
	ld	hl, #0x0004
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x01
;SpriteScorpion.c:32: data->wait = 0u;
	ld	hl, #0x0005
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x00
;SpriteScorpion.c:33: data->enemydamage = 15u;
	ld	hl, #0x0006
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x0f
;SpriteScorpion.c:34: data->hp = 60u;
	ld	hl, #0x0007
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x3c
;SpriteScorpion.c:35: data->enemy_state = ENEMY_STATE_NORMAL;
	inc	bc
	inc	bc
	xor	a, a
	ld	(bc), a
;SpriteScorpion.c:36: }
	add	sp, #2
	ret
_scorpion_idle:
	.db #0x01	; 1
	.db #0x00	; 0
_scorpion_walk:
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x01	; 1
_scorpion_hit:
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x04	; 4
_scorpion_dead:
	.db #0x01	; 1
	.db #0x05	; 5
;SpriteScorpion.c:38: void Update_SpriteScorpion() {
;	---------------------------------
; Function Update_SpriteScorpion
; ---------------------------------
_Update_SpriteScorpion::
	add	sp, #-17
;SpriteScorpion.c:40: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0019
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
;SpriteScorpion.c:42: if (data->enemy_state == ENEMY_STATE_DEAD){
	pop	de
	push	de
	ld	hl, #0x0002
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
	ldhl	sp,	#15
	ld	(hl), a
;SpriteScorpion.c:43: if (data->wait > 0){
	pop	de
	push	de
	ld	hl, #0x0005
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
	ldhl	sp,	#16
;SpriteScorpion.c:42: if (data->enemy_state == ENEMY_STATE_DEAD){
	ld	(hl-), a
	ld	a, (hl)
	sub	a, #0x03
	jp	NZ,00105$
;SpriteScorpion.c:44: THIS->y--;
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#14
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
;SpriteScorpion.c:43: if (data->wait > 0){
	inc	hl
	ld	a, (hl)
	or	a, a
	jr	Z,00102$
;SpriteScorpion.c:44: THIS->y--;
	dec	bc
	dec	hl
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteScorpion.c:45: data->wait--;
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	dec	c
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	jp	00143$
00102$:
;SpriteScorpion.c:47: THIS->y++;	
	inc	bc
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteScorpion.c:48: THIS->y++;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
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
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteScorpion.c:50: return;
	jp	00143$
00105$:
;SpriteScorpion.c:61: data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, (data->enemy_accel_y >> 4)<< delta_time);
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpriteScorpion.c:52: if (data->wait > 0u){
	ldhl	sp,	#16
	ld	a, (hl)
	or	a, a
	jr	Z,00120$
;SpriteScorpion.c:53: data->wait -= 1u;
	ld	c, (hl)
	dec	c
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpriteScorpion.c:54: if (data->wait == 0u){
	ld	a, c
	or	a, a
	jp	NZ, 00121$
;SpriteScorpion.c:55: SetSpriteAnim(THIS, scorpion_walk, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_scorpion_walk
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	jp	00121$
00120$:
;SpriteScorpion.c:58: if(data->enemy_accel_y < 24) {
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	ld	a, c
	sub	a, #0x18
	ld	a, b
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	NC,00109$
;SpriteScorpion.c:59: data->enemy_accel_y += 1;
	inc	bc
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
00109$:
;SpriteScorpion.c:61: data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, (data->enemy_accel_y >> 4)<< delta_time);
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	ldhl	sp,	#16
	ld	(hl), c
	push	hl
	ld	hl, #_delta_time
	ld	a, (hl)
	ldhl	sp,	#15
	ld	(hl), a
	pop	hl
	ldhl	sp,	#13
	ld	a, (hl)
	push	af
	ldhl	sp,	#18
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	pop	af
	inc	a
	jr	00249$
00248$:
	ldhl	sp,	#14
	sla	(hl)
00249$:
	dec	a
	jr	NZ,00248$
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	ldhl	sp,	#13
	ld	a, (hl)
	inc	a
	jr	00251$
00250$:
	sla	b
00251$:
	dec	a
	jr	NZ,00250$
	inc	hl
	ld	a, (hl)
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
	ld	a, e
	ldhl	sp,	#6
	push	af
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	pop	af
	ld	(hl), a
;SpriteScorpion.c:63: if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
	or	a, a
	jp	NZ, 00111$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00111$
;SpriteScorpion.c:58: if(data->enemy_accel_y < 24) {
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
;SpriteScorpion.c:63: if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
	ld	a, c
	sub	a, #0x18
	ld	a, b
	rla
	ccf
	rra
	sbc	a, #0x80
	jp	NC, 00111$
;SpriteScorpion.c:64: data->enemy_accel_y += 2;
	inc	bc
	inc	bc
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteScorpion.c:65: data->tile_e_collision = TranslateSprite(THIS, 0, (data->enemy_accel_y >> 4) << delta_time);
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	ld	hl, #_delta_time
	ld	a, (hl)
	inc	a
	jr	00253$
00252$:
	sla	c
00253$:
	dec	a
	jr	NZ,00252$
	ld	a, c
	push	af
	inc	sp
	xor	a, a
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
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00111$:
;SpriteScorpion.c:67: if(data->tile_e_collision) {
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jp	Z, 00121$
;SpriteScorpion.c:68: if(data->enemy_state == ENEMY_STATE_JUMPING & data->enemy_accel_y > 0) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	ld	a, #0x01
	jr	Z,00255$
	xor	a, a
00255$:
	ldhl	sp,	#16
	ld	(hl), a
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b,a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	cp	a, c
	sbc	a, b
	bit	7, e
	jr	Z,00256$
	bit	7, d
	jr	NZ,00257$
	cp	a, a
	jr	00257$
00256$:
	bit	7, d
	jr	Z,00257$
	scf
00257$:
	ld	a, #0x00
	rla
	ldhl	sp,	#16
	and	a,(hl)
	jr	Z,00115$
;SpriteScorpion.c:69: data->enemy_state = ENEMY_STATE_NORMAL;
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x00
	jr	00116$
00115$:
;SpriteScorpion.c:71: data->enemy_accel_y = 0;	
	pop	hl
	push	hl
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
00116$:
;SpriteScorpion.c:73: CheckCollisionETile();
	call	_CheckCollisionETile
00121$:
;SpriteScorpion.c:81: SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
	ld	a, (#(_sprite_manager_updatables + 0x0001) + 0)
	ld	c, a
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_sprite_manager_sprites
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#8
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	xor	a, a
	ldhl	sp,	#16
	ld	(hl), a
00141$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#16
	ld	a, (hl)
	sub	a, c
	jp	Z,00143$
;SpriteScorpion.c:82: if(iespr->type == SpritePlayer) {
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0011
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	or	a, a
	jr	NZ,00125$
;SpriteScorpion.c:83: if(CheckCollision(THIS, iespr)) {
	push	bc
	ldhl	sp,	#10
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
	pop	bc
	or	a, a
	jr	Z,00125$
;SpriteScorpion.c:84: data->wait = 24u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
00125$:
;SpriteScorpion.c:87: if(iespr->type == SpriteArrow) {
	ld	a, (bc)
	dec	a
	jp	NZ,00142$
;SpriteScorpion.c:88: if(CheckCollision(THIS, iespr)) {
	ldhl	sp,	#8
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
	jp	Z, 00142$
;SpriteScorpion.c:89: data->wait = 24u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
;SpriteScorpion.c:90: SetSpriteAnim(THIS, scorpion_hit, 24u); 
	ld	a, #0x18
	push	af
	inc	sp
	ld	hl, #_scorpion_hit
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteScorpion.c:91: struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
;SpriteScorpion.c:92: data->hp -= arrowdata->arrowdamage;
	pop	de
	push	de
	ld	hl, #0x0007
	add	hl, de
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
	ldhl	sp,	#15
	ld	(hl), a
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	a, (hl)
	sub	a, c
	ld	c, a
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpriteScorpion.c:40: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteScorpion.c:93: if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#14
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#12
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#14
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
;SpriteScorpion.c:94: if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	and	a, #0x20
	ld	c, a
	ld	b, #0x00
;SpriteScorpion.c:93: if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
	ldhl	sp,	#12
	ld	e, l
	ld	d, h
	ldhl	sp,	#14
	ld	a, (de)
	sub	a, (hl)
	inc	hl
	inc	de
	ld	a, (de)
	sbc	a, (hl)
	jp	NC, 00131$
;SpriteScorpion.c:94: if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
	ld	a, b
	or	a, c
	jr	Z,00127$
;SpriteScorpion.c:95: ETurn();
	call	_ETurn
00127$:
;SpriteScorpion.c:97: data->tile_e_collision = TranslateSprite(THIS, -4 << delta_time, (data->enemy_accel_y >> 4));
	pop	de
	push	de
	ld	a,(de)
	ld	b, a
	inc	de
	ld	a,(de)
	ld	c, a
	sra	c
	rr	b
	sra	c
	rr	b
	sra	c
	rr	b
	sra	c
	rr	b
	ld	hl, #_delta_time
	ld	c, (hl)
	ld	d, #0xfc
	inc	c
	jr	00264$
00263$:
	sla	d
00264$:
	dec	c
	jr	NZ,00263$
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
	ld	c, e
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	jp	00132$
00131$:
;SpriteScorpion.c:99: if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
	ld	a, b
	or	a, c
	jr	NZ,00129$
;SpriteScorpion.c:100: ETurn();
	call	_ETurn
00129$:
;SpriteScorpion.c:102: data->tile_e_collision = TranslateSprite(THIS, 4 << delta_time, (data->enemy_accel_y >> 4));
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	ld	hl, #_delta_time
	ld	b, (hl)
	ld	d, #0x04
	inc	b
	jr	00266$
00265$:
	sla	d
00266$:
	dec	b
	jr	NZ,00265$
	ld	a, c
	push	af
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
	ld	c, e
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00132$:
;SpriteScorpion.c:104: SpriteManagerRemoveSprite(iespr);
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpriteScorpion.c:105: if (data->hp <= 0){
	ldhl	sp,#(11 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c,a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, c
	bit	7, e
	jr	Z,00267$
	bit	7, d
	jr	NZ,00268$
	cp	a, a
	jr	00268$
00267$:
	bit	7, d
	jr	Z,00268$
	scf
00268$:
	jp	C, 00142$
;SpriteScorpion.c:106: data->enemy_state = ENEMY_STATE_DEAD;
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x03
;SpriteScorpion.c:107: SetSpriteAnim(THIS, scorpion_dead, 16u);
	ld	a, #0x10
	push	af
	inc	sp
	ld	hl, #_scorpion_dead
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteScorpion.c:108: NR50_REG = 0x55; //Max volume		
	ld	a, #0x55
	ldh	(_NR50_REG+0),a
;SpriteScorpion.c:109: PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
	ld	hl, #0x0086
	push	hl
	ld	l, #0x68
	push	hl
	ld	l, #0x43
	push	hl
	ld	l, #0xc2
	push	hl
	ld	l, #0x4b
	push	hl
	ld	a, #0x05
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_PlayFx
	add	sp, #12
;SpriteScorpion.c:110: data->wait = 8u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x08
;SpriteScorpion.c:111: THIS->lim_x = 8u;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x13
	ld	b, a
	jr	NC,00269$
	inc	c
00269$:
	ld	l, b
	ld	h, c
	ld	(hl), #0x08
	inc	hl
	ld	(hl), #0x00
;SpriteScorpion.c:112: THIS->lim_y = 16u;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x15
	ld	b, a
	jr	NC,00270$
	inc	c
00270$:
	ld	l, b
	ld	h, c
	ld	(hl), #0x10
	inc	hl
	ld	(hl), #0x00
00142$:
;SpriteScorpion.c:81: SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
	ldhl	sp,	#16
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
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#8
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	jp	00141$
00143$:
;SpriteScorpion.c:118: }
	add	sp, #17
	ret
;SpriteScorpion.c:122: void Destroy_SpriteScorpion() {
;	---------------------------------
; Function Destroy_SpriteScorpion
; ---------------------------------
_Destroy_SpriteScorpion::
;SpriteScorpion.c:123: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
