;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpritePorcupine
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpritePorcupine
	.globl _Update_SpritePorcupine
	.globl _Start_SpritePorcupine
	.globl _SpriteManagerRemoveSprite
	.globl _SpriteManagerAdd
	.globl _CheckCollision
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpritePorcupine
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _porcupine_attack
	.globl _porcupine_dead
	.globl _porcupine_hit
	.globl _porcupine_walk
	.globl _porcupine_idle
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
_bank_SpritePorcupine:
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
;SpritePorcupine.c:18: void Start_SpritePorcupine() {
;	---------------------------------
; Function Start_SpritePorcupine
; ---------------------------------
_Start_SpritePorcupine::
	add	sp, #-2
;SpritePorcupine.c:20: THIS->coll_x = 2;
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
;SpritePorcupine.c:21: THIS->coll_y = 0;
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
;SpritePorcupine.c:22: THIS->coll_w = 12;
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
;SpritePorcupine.c:23: THIS->coll_h = 16;
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
;SpritePorcupine.c:24: THIS->lim_x = 255u;
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
;SpritePorcupine.c:25: THIS->lim_y = 244u;
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
;SpritePorcupine.c:26: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
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
;SpritePorcupine.c:27: SetSpriteAnim(THIS, porcupine_idle, 8u);
	push	bc
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_porcupine_idle
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	pop	bc
;SpritePorcupine.c:28: data->enemy_accel_y = 24;
	ld	l, c
	ld	h, b
	ld	(hl), #0x18
	inc	hl
	ld	(hl), #0x00
;SpritePorcupine.c:29: data->vx = 1;
	ld	hl, #0x0004
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x01
;SpritePorcupine.c:30: data->wait = 0u;
	ld	hl, #0x0005
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x00
;SpritePorcupine.c:31: data->enemydamage = 15u;
	ld	hl, #0x0006
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x0f
;SpritePorcupine.c:32: data->hp = 30u;
	ld	hl, #0x0007
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	hl
	push	hl
	ld	(hl), #0x1e
;SpritePorcupine.c:33: data->enemy_state = ENEMY_STATE_NORMAL;
	inc	bc
	inc	bc
	xor	a, a
	ld	(bc), a
;SpritePorcupine.c:34: }
	add	sp, #2
	ret
_porcupine_idle:
	.db #0x01	; 1
	.db #0x00	; 0
_porcupine_walk:
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x01	; 1
_porcupine_hit:
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x04	; 4
_porcupine_dead:
	.db #0x01	; 1
	.db #0x05	; 5
_porcupine_attack:
	.db #0x04	; 4
	.db #0x06	; 6
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x07	; 7
;SpritePorcupine.c:36: void Update_SpritePorcupine() {
;	---------------------------------
; Function Update_SpritePorcupine
; ---------------------------------
_Update_SpritePorcupine::
	add	sp, #-11
;SpritePorcupine.c:38: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#7
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
;SpritePorcupine.c:40: if (data->enemy_state == ENEMY_STATE_DEAD){
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
	ldhl	sp,	#9
	ld	(hl), a
;SpritePorcupine.c:41: if (data->wait > 0){
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
	ldhl	sp,	#10
;SpritePorcupine.c:40: if (data->enemy_state == ENEMY_STATE_DEAD){
	ld	(hl-), a
	ld	a, (hl)
	sub	a, #0x03
	jp	NZ,00105$
;SpritePorcupine.c:42: THIS->y--;
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
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
	inc	de
	ld	a,(de)
	ld	b, a
;SpritePorcupine.c:41: if (data->wait > 0){
	ldhl	sp,	#10
	ld	a, (hl)
	or	a, a
	jr	Z,00102$
;SpritePorcupine.c:42: THIS->y--;
	dec	bc
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePorcupine.c:43: data->wait--;
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
	jp	00139$
00102$:
;SpritePorcupine.c:45: THIS->y++;	
	inc	bc
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePorcupine.c:46: THIS->y++;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
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
;SpritePorcupine.c:48: return;
	jp	00139$
00105$:
;SpritePorcupine.c:51: if (data->enemy_state == ENEMY_STATE_ATTACK){
	ldhl	sp,	#9
	ld	a, (hl)
	sub	a, #0x04
	jp	NZ,00114$
;SpritePorcupine.c:52: if (data->wait == attack_wait){SetSpriteAnim(THIS, porcupine_attack, 8u);}
	ld	hl, #_attack_wait
	ld	a, (hl)
	ldhl	sp,	#10
	sub	a, (hl)
	jr	NZ,00107$
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_porcupine_attack
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
00107$:
;SpritePorcupine.c:53: if (data->wait == 1u){
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	jp	NZ,00114$
;SpritePorcupine.c:54: struct Sprite* arrow_e_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
	ld	hl, #0x0000
	push	hl
	ld	l, #0x00
	push	hl
	ld	a, #0x01
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ldhl	sp,	#6
	ld	(hl), e
	inc	hl
	ld	(hl), d
;SpritePorcupine.c:55: struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_e_sprite->custom_data;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
;SpritePorcupine.c:56: arrow_data->arrowdir = 1;
	ld	hl, #0x0003
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpritePorcupine.c:57: arrow_data->type = 6;
	ld	e, c
	ld	d, b
	ld	a, (de)
	and	a, #0xf0
	or	a, #0x06
	ld	(de),a
;SpritePorcupine.c:58: arrow_data->arrowdamage = 10u;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x0a
	ld	(bc), a
;SpritePorcupine.c:59: arrow_e_sprite->flags = THIS->flags;
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000c
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000c
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpritePorcupine.c:38: struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePorcupine.c:60: if(SPRITE_GET_VMIRROR(THIS)){arrow_e_sprite->x = THIS->x-16;}
	ld	hl, #0x000c
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	hl
	dec	hl
	ld	(hl-), a
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
	ld	hl, #0x0008
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ldhl	sp,	#8
	bit	5, (hl)
	jr	Z,00109$
	ld	a, b
	add	a, #0xf0
	ld	b, a
	ld	a, c
	adc	a, #0xff
	ld	c, a
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
	inc	hl
	ld	(hl), c
	jr	00110$
00109$:
;SpritePorcupine.c:61: else{arrow_e_sprite->x = THIS->x+10;}
	ld	a, b
	add	a, #0x0a
	ld	b, a
	jr	NC,00241$
	inc	c
00241$:
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
	inc	hl
	ld	(hl), c
00110$:
;SpritePorcupine.c:62: arrow_e_sprite->y = THIS->y + 2;
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x0a
	ld	b, a
	jr	NC,00242$
	inc	c
00242$:
	ld	l, b
	ld	h, c
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
00114$:
;SpritePorcupine.c:66: if (data->wait > 0u){
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#10
	ld	(hl),a
	or	a, a
	jr	Z,00129$
;SpritePorcupine.c:67: data->wait -= 1u;
	ld	c, (hl)
	dec	c
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
;SpritePorcupine.c:68: if (data->wait == 0u){
	ld	a,c
	ld	(hl),a
	or	a, a
	jp	NZ, 00130$
;SpritePorcupine.c:69: SetSpriteAnim(THIS, porcupine_walk, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_porcupine_walk
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePorcupine.c:70: data->enemy_state = ENEMY_STATE_NORMAL;
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x00
	jp	00130$
00129$:
;SpritePorcupine.c:73: if(data->enemy_accel_y < 24) {
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
	jr	NC,00118$
;SpritePorcupine.c:74: data->enemy_accel_y += 1;
	inc	bc
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
00118$:
;SpritePorcupine.c:76: data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, (data->enemy_accel_y >> 4)<< delta_time);
	pop	de
	push	de
	ld	hl, #0x0003
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), d
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
	push	hl
	ld	hl, #_delta_time
	ld	a, (hl)
	ldhl	sp,	#12
	ld	(hl), a
	pop	hl
	ldhl	sp,	#10
	ld	a, (hl)
	inc	a
	jr	00244$
00243$:
	sla	b
00244$:
	dec	a
	jr	NZ,00243$
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ldhl	sp,	#10
	ld	a, (hl)
	inc	a
	jr	00246$
00245$:
	sla	c
00246$:
	dec	a
	jr	NZ,00245$
	push	bc
	inc	sp
	ld	a, c
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
	ldhl	sp,	#8
	push	af
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	pop	af
	ld	(hl), a
;SpritePorcupine.c:78: if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
	or	a, a
	jp	NZ, 00120$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00120$
;SpritePorcupine.c:73: if(data->enemy_accel_y < 24) {
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
;SpritePorcupine.c:78: if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
	ld	a, c
	sub	a, #0x18
	ld	a, b
	rla
	ccf
	rra
	sbc	a, #0x80
	jp	NC, 00120$
;SpritePorcupine.c:79: data->enemy_accel_y += 2;
	inc	bc
	inc	bc
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePorcupine.c:80: data->tile_e_collision = TranslateSprite(THIS, 0, (data->enemy_accel_y >> 4) << delta_time);
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
	jr	00248$
00247$:
	sla	c
00248$:
	dec	a
	jr	NZ,00247$
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
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
00120$:
;SpritePorcupine.c:82: if(data->tile_e_collision) {
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	or	a, a
	jp	Z, 00130$
;SpritePorcupine.c:83: if(data->enemy_state == ENEMY_STATE_JUMPING & data->enemy_accel_y > 0) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	ld	a, #0x01
	jr	Z,00250$
	xor	a, a
00250$:
	ldhl	sp,	#10
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
	jr	Z,00251$
	bit	7, d
	jr	NZ,00252$
	cp	a, a
	jr	00252$
00251$:
	bit	7, d
	jr	Z,00252$
	scf
00252$:
	ld	a, #0x00
	rla
	ldhl	sp,	#10
	and	a,(hl)
	jr	Z,00124$
;SpritePorcupine.c:84: data->enemy_state = ENEMY_STATE_NORMAL;
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(hl), #0x00
	jr	00125$
00124$:
;SpritePorcupine.c:86: data->enemy_accel_y = 0;	
	pop	hl
	push	hl
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
00125$:
;SpritePorcupine.c:88: CheckCollisionETile();
	call	_CheckCollisionETile
00130$:
;SpritePorcupine.c:96: SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
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
	ldhl	sp,	#10
	ld	(hl), a
00137$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	a, (hl)
	ldhl	sp,	#9
	ld	(hl), a
	ldhl	sp,	#10
	ld	a, (hl-)
	sub	a, (hl)
	jp	Z,00139$
;SpritePorcupine.c:97: if(iespr->type == SpriteArrow) {
	ld	hl, #0x0011
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	jr	NZ,00138$
;SpritePorcupine.c:98: if(CheckCollision(THIS, iespr)) {
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
	jr	Z,00138$
;SpritePorcupine.c:99: SpriteManagerRemoveSprite(iespr);
	push	bc
	call	_SpriteManagerRemoveSprite
	add	sp, #2
00138$:
;SpritePorcupine.c:96: SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
	ldhl	sp,	#10
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
	jp	00137$
00139$:
;SpritePorcupine.c:104: }
	add	sp, #11
	ret
;SpritePorcupine.c:106: void Destroy_SpritePorcupine() {
;	---------------------------------
; Function Destroy_SpritePorcupine
; ---------------------------------
_Destroy_SpritePorcupine::
;SpritePorcupine.c:107: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
