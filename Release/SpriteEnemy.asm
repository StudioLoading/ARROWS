;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpriteEnemy
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpriteEnemy
	.globl _Update_SpriteEnemy
	.globl _Start_SpriteEnemy
	.globl _PlayFx
	.globl _SpriteManagerRemoveSprite
	.globl _CheckCollision
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpriteEnemy
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _enemy_dead
	.globl _enemy_hit
	.globl _enemy_walk
	.globl _enemy_idle
	.globl _CheckCollisionETile
	.globl _ETurn
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
_bank_SpriteEnemy:
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
;SpriteEnemy.c:20: void Start_SpriteEnemy() {
;	---------------------------------
; Function Start_SpriteEnemy
; ---------------------------------
_Start_SpriteEnemy::
	add	sp, #-2
;SpriteEnemy.c:22: THIS->coll_x = 2;
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
;SpriteEnemy.c:23: THIS->coll_y = 4;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000e
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x04
;SpriteEnemy.c:24: THIS->coll_w = 6;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000f
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x06
;SpriteEnemy.c:25: THIS->coll_h = 12;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0010
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x0c
;SpriteEnemy.c:26: THIS->lim_x = 255u;
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
;SpriteEnemy.c:27: THIS->lim_y = 244u;
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
;SpriteEnemy.c:28: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
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
;SpriteEnemy.c:29: SetSpriteAnim(THIS, enemy_idle, 8u);
	push	bc
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_enemy_idle
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	pop	bc
;SpriteEnemy.c:30: data->enemy_accel_y = 24;
	ld	l, c
	ld	h, b
	ld	(hl), #0x18
	inc	hl
	ld	(hl), #0x00
;SpriteEnemy.c:31: data->vx = 1;
	ld	hl, #0x0004
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x01
;SpriteEnemy.c:32: data->wait = 0u;
	ld	hl, #0x0005
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x00
;SpriteEnemy.c:33: data->enemydamage = 5u;
	ld	hl, #0x0006
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x05
;SpriteEnemy.c:34: data->hp = 45u;
	ld	hl, #0x0007
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x2d
;SpriteEnemy.c:35: data->enemy_state = ENEMY_STATE_NORMAL;
	inc	bc
	inc	bc
	xor	a, a
	ld	(bc), a
;SpriteEnemy.c:36: }
	add	sp, #2
	ret
_enemy_idle:
	.db #0x01	; 1
	.db #0x00	; 0
_enemy_walk:
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x01	; 1
_enemy_hit:
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x04	; 4
_enemy_dead:
	.db #0x01	; 1
	.db #0x05	; 5
;SpriteEnemy.c:38: void Update_SpriteEnemy() {
;	---------------------------------
; Function Update_SpriteEnemy
; ---------------------------------
_Update_SpriteEnemy::
	add	sp, #-17
;SpriteEnemy.c:40: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#14
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	b, h
	inc	sp
	inc	sp
	push	bc
;SpriteEnemy.c:42: if (data->enemy_state == ENEMY_STATE_DEAD){
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
	ld	c, a
;SpriteEnemy.c:43: if (data->wait > 0){
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
	ld	(hl), a
;SpriteEnemy.c:42: if (data->enemy_state == ENEMY_STATE_DEAD){
	ld	a, c
	sub	a, #0x03
	jp	NZ,00105$
;SpriteEnemy.c:44: THIS->y--;
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
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
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
;SpriteEnemy.c:43: if (data->wait > 0){
	ldhl	sp,	#16
	ld	a, (hl)
	or	a, a
	jr	Z,00102$
;SpriteEnemy.c:44: THIS->y--;
	dec	bc
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteEnemy.c:45: data->wait--;
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
	jp	00145$
00102$:
;SpriteEnemy.c:47: THIS->y++;	
	inc	bc
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteEnemy.c:48: THIS->y++;
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
;SpriteEnemy.c:50: return;
	jp	00145$
00105$:
;SpriteEnemy.c:62: data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, (data->enemy_accel_y >> 4)<< delta_time);
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpriteEnemy.c:53: if (data->wait > 0u){
	ldhl	sp,	#16
	ld	a, (hl)
	or	a, a
	jr	Z,00120$
;SpriteEnemy.c:54: data->wait -= 1u;
	ld	c, (hl)
	dec	c
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpriteEnemy.c:55: if (data->wait == 0u){
	ld	a, c
	or	a, a
	jp	NZ, 00121$
;SpriteEnemy.c:56: SetSpriteAnim(THIS, enemy_walk, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_enemy_walk
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
;SpriteEnemy.c:59: if(data->enemy_accel_y < 24) {
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
;SpriteEnemy.c:60: data->enemy_accel_y += 1;
	inc	bc
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
00109$:
;SpriteEnemy.c:62: data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, (data->enemy_accel_y >> 4)<< delta_time);
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
	jr	00255$
00254$:
	ldhl	sp,	#14
	sla	(hl)
00255$:
	dec	a
	jr	NZ,00254$
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
	jr	00257$
00256$:
	sla	b
00257$:
	dec	a
	jr	NZ,00256$
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
;SpriteEnemy.c:64: if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
	or	a, a
	jp	NZ, 00111$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00111$
;SpriteEnemy.c:59: if(data->enemy_accel_y < 24) {
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
;SpriteEnemy.c:64: if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
	ld	a, c
	sub	a, #0x18
	ld	a, b
	rla
	ccf
	rra
	sbc	a, #0x80
	jp	NC, 00111$
;SpriteEnemy.c:65: data->enemy_accel_y += 2;
	inc	bc
	inc	bc
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpriteEnemy.c:66: data->tile_e_collision = TranslateSprite(THIS, 0, (data->enemy_accel_y >> 4) << delta_time);
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
	jr	00259$
00258$:
	sla	c
00259$:
	dec	a
	jr	NZ,00258$
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
;SpriteEnemy.c:68: if(data->tile_e_collision) {
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jp	Z, 00121$
;SpriteEnemy.c:69: if(data->enemy_state == ENEMY_STATE_JUMPING & data->enemy_accel_y > 0) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	ld	a, #0x01
	jr	Z,00261$
	xor	a, a
00261$:
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
	jr	Z,00262$
	bit	7, d
	jr	NZ,00263$
	cp	a, a
	jr	00263$
00262$:
	bit	7, d
	jr	Z,00263$
	scf
00263$:
	ld	a, #0x00
	rla
	ldhl	sp,	#16
	and	a,(hl)
	jr	Z,00115$
;SpriteEnemy.c:70: data->enemy_state = ENEMY_STATE_NORMAL;
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x00
	jr	00116$
00115$:
;SpriteEnemy.c:72: data->enemy_accel_y = 0;	
	pop	hl
	push	hl
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
00116$:
;SpriteEnemy.c:74: CheckCollisionETile();
	call	_CheckCollisionETile
00121$:
;SpriteEnemy.c:82: SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
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
00143$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#16
	ld	a, (hl)
	sub	a, c
	jp	Z,00145$
;SpriteEnemy.c:83: if(iespr->type == SpritePlayer) {
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0011
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
	or	a, a
	jr	NZ,00125$
;SpriteEnemy.c:84: if(CheckCollision(THIS, iespr)) {
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
	jr	Z,00125$
;SpriteEnemy.c:85: data->wait = 24u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
00125$:
;SpriteEnemy.c:88: if(iespr->type == SpriteArrow) {
	ldhl	sp,#(15 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	jp	NZ,00144$
;SpriteEnemy.c:89: if(CheckCollision(THIS, iespr)) {
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
	jp	Z, 00144$
;SpriteEnemy.c:90: struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
;SpriteEnemy.c:91: if (arrowdata->type == 6u){ //spine from porcupine
	ld	e, c
	ld	d, b
	ld	l, e
	ld	h, d
	ld	a, (hl)
	and	a, #0x0f
	sub	a, #0x06
	jp	Z,00145$
	jr	00127$
;SpriteEnemy.c:92: return;
	jp	00145$
00127$:
;SpriteEnemy.c:94: data->wait = 24u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x18
;SpriteEnemy.c:95: SetSpriteAnim(THIS, enemy_hit, 24u); 
	push	bc
	ld	a, #0x18
	push	af
	inc	sp
	ld	hl, #_enemy_hit
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	pop	bc
;SpriteEnemy.c:96: data->hp -= arrowdata->arrowdamage;
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
;SpriteEnemy.c:40: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteEnemy.c:97: if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
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
;SpriteEnemy.c:98: if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	and	a, #0x20
	ld	c, a
	ld	b, #0x00
;SpriteEnemy.c:97: if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
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
	jp	NC, 00133$
;SpriteEnemy.c:98: if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
	ld	a, b
	or	a, c
	jr	Z,00129$
;SpriteEnemy.c:99: ETurn();
	call	_ETurn
00129$:
;SpriteEnemy.c:101: data->tile_e_collision = TranslateSprite(THIS, -4 << delta_time, (data->enemy_accel_y >> 4));
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
	jr	00272$
00271$:
	sla	d
00272$:
	dec	c
	jr	NZ,00271$
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
	jp	00134$
00133$:
;SpriteEnemy.c:103: if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
	ld	a, b
	or	a, c
	jr	NZ,00131$
;SpriteEnemy.c:104: ETurn();
	call	_ETurn
00131$:
;SpriteEnemy.c:106: data->tile_e_collision = TranslateSprite(THIS, 4 << delta_time, (data->enemy_accel_y >> 4));
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
	jr	00274$
00273$:
	sla	d
00274$:
	dec	b
	jr	NZ,00273$
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
00134$:
;SpriteEnemy.c:108: SpriteManagerRemoveSprite(iespr);
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpriteEnemy.c:109: if (data->hp <= 0){
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
	jr	Z,00275$
	bit	7, d
	jr	NZ,00276$
	cp	a, a
	jr	00276$
00275$:
	bit	7, d
	jr	Z,00276$
	scf
00276$:
	jp	C, 00144$
;SpriteEnemy.c:110: NR50_REG = 0x55; //Max volume		
	ld	a, #0x55
	ldh	(_NR50_REG+0),a
;SpriteEnemy.c:111: PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
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
;SpriteEnemy.c:112: data->enemy_state = ENEMY_STATE_DEAD;
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x03
;SpriteEnemy.c:113: SetSpriteAnim(THIS, enemy_dead, 16u);
	ld	a, #0x10
	push	af
	inc	sp
	ld	hl, #_enemy_dead
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpriteEnemy.c:114: data->wait = 8u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x08
;SpriteEnemy.c:115: THIS->lim_x = 8u;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x13
	ld	b, a
	jr	NC,00277$
	inc	c
00277$:
	ld	l, b
	ld	h, c
	ld	(hl), #0x08
	inc	hl
	ld	(hl), #0x00
;SpriteEnemy.c:116: THIS->lim_y = 16u;
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x15
	ld	b, a
	jr	NC,00278$
	inc	c
00278$:
	ld	l, b
	ld	h, c
	ld	(hl), #0x10
	inc	hl
	ld	(hl), #0x00
00144$:
;SpriteEnemy.c:82: SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
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
	jp	00143$
00145$:
;SpriteEnemy.c:122: }
	add	sp, #17
	ret
;SpriteEnemy.c:124: void CheckCollisionETile() {
;	---------------------------------
; Function CheckCollisionETile
; ---------------------------------
_CheckCollisionETile::
;SpriteEnemy.c:125: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
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
;SpriteEnemy.c:126: switch(data->tile_e_collision) {
	inc	bc
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	a, (hl)
	cp	a, #0x04
	jr	Z,00106$
	cp	a, #0x05
	jr	Z,00106$
	cp	a, #0x06
	jr	Z,00106$
	cp	a, #0x07
	jr	Z,00106$
	cp	a, #0x12
	jr	Z,00106$
	sub	a, #0x13
	ret	NZ
;SpriteEnemy.c:132: case 19u:
00106$:
;SpriteEnemy.c:133: ETurn();
;SpriteEnemy.c:135: }
;SpriteEnemy.c:136: }
	jp	_ETurn
;SpriteEnemy.c:138: void ETurn(){
;	---------------------------------
; Function ETurn
; ---------------------------------
_ETurn::
	add	sp, #-8
;SpriteEnemy.c:139: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0019
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
;SpriteEnemy.c:140: if (data->vx == 1){
	pop	de
	push	de
	ld	hl, #0x0004
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
	ldhl	sp,	#7
	ld	(hl), a
;SpriteEnemy.c:143: data->wait = 48u;
	pop	de
	push	de
	ld	hl, #0x0005
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
;SpriteEnemy.c:140: if (data->vx == 1){
	inc	hl
	inc	hl
	ld	a, (hl)
	dec	a
	jp	NZ,00102$
;SpriteEnemy.c:141: SPRITE_SET_VMIRROR(THIS);
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	set	5, a
	ld	(bc), a
;SpriteEnemy.c:139: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteEnemy.c:142: THIS->x -= 4;
	ld	hl, #0x0008
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
;SpriteEnemy.c:143: data->wait = 48u;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x30
00102$:
;SpriteEnemy.c:145: if (data->vx == -1){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	a
	jp	NZ,00104$
;SpriteEnemy.c:139: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteEnemy.c:141: SPRITE_SET_VMIRROR(THIS);
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
;SpriteEnemy.c:146: SPRITE_UNSET_VMIRROR(THIS);
	ld	a, (bc)
	res	5, a
	ld	(bc), a
;SpriteEnemy.c:139: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpriteEnemy.c:142: THIS->x -= 4;
	ld	hl, #0x0008
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpriteEnemy.c:147: THIS->x += 4;
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
;SpriteEnemy.c:148: data->wait = 48u;			
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x30
00104$:
;SpriteEnemy.c:150: data->vx = -data->vx;
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	xor	a, a
	sub	a, c
	ld	c, a
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpriteEnemy.c:151: if(THIS->type == SpritePorcupine){
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0011
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	sub	a, #0x08
	jr	NZ,00107$
;SpriteEnemy.c:152: data->enemy_state = ENEMY_STATE_ATTACK;
	pop	bc
	push	bc
	inc	bc
	inc	bc
	ld	a, #0x04
	ld	(bc), a
;SpriteEnemy.c:153: data->wait = attack_wait;
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #_attack_wait
	ld	a, (hl)
	ld	(de), a
00107$:
;SpriteEnemy.c:156: }
	add	sp, #8
	ret
;SpriteEnemy.c:158: void Destroy_SpriteEnemy() {
;	---------------------------------
; Function Destroy_SpriteEnemy
; ---------------------------------
_Destroy_SpriteEnemy::
;SpriteEnemy.c:159: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
