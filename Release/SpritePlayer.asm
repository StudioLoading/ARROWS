;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpritePlayer
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Destroy_SpritePlayer
	.globl _Update_SpritePlayer
	.globl _Start_SpritePlayer
	.globl _PlayFx
	.globl _SpriteManagerRemoveSprite
	.globl _SpriteManagerAdd
	.globl _SetState
	.globl _CheckCollision
	.globl _TranslateSprite
	.globl _SetSpriteAnim
	.globl _empty
	.globl _bank_SpritePlayer
	.globl _archer_data
	.globl _hit_cooldown
	.globl _aimc
	.globl _tile_collision
	.globl _archer_accel_y
	.globl _archer_state
	.globl _princess_parent
	.globl _platform_vx
	.globl _jump_power
	.globl _shoot_cooldown
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _anim_flying
	.globl _anim_shoot
	.globl _anim_hit
	.globl _anim_shield
	.globl _anim_walk
	.globl _anim_dead
	.globl _anim_up
	.globl _anim_jump_up
	.globl _anim_jump
	.globl _anim_idle
	.globl _Die
	.globl _Shoot
	.globl _Jump
	.globl _MoveArcher
	.globl _MoveArcherRelativePlatform
	.globl _CheckCollisionTile
	.globl _Hit
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
_shoot_cooldown::
	.ds 1
_jump_power::
	.ds 1
_platform_vx::
	.ds 1
_princess_parent::
	.ds 2
_archer_state::
	.ds 1
_archer_accel_y::
	.ds 2
_tile_collision::
	.ds 1
_aimc::
	.ds 1
_hit_cooldown::
	.ds 1
_archer_data::
	.ds 2
;--------------------------------------------------------
; CODE rom data
;--------------------------------------------------------
	.area _CODE
_bank_SpritePlayer:
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
;SpritePlayer.c:25: INT8 shoot_cooldown = 0;
	ld	hl, #_shoot_cooldown
	ld	(hl), #0x00
;SpritePlayer.c:26: UINT8 jump_power = 0u;
	ld	hl, #_jump_power
	ld	(hl), #0x00
;SpritePlayer.c:27: INT8 platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
;SpritePlayer.c:29: struct Sprite* princess_parent = 0;
	ld	hl, #_princess_parent
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
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
;SpritePlayer.c:61: void Start_SpritePlayer() {
;	---------------------------------
; Function Start_SpritePlayer
; ---------------------------------
_Start_SpritePlayer::
	add	sp, #-2
;SpritePlayer.c:62: archer_data = (struct ArcherInfo*)THIS->custom_data;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0019
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	ldhl	sp,	#0
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_archer_data
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:65: THIS->coll_x = 5;
	ld	hl, #0x000d
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x05
;SpritePlayer.c:66: THIS->coll_y = 5;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000e
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x05
;SpritePlayer.c:67: THIS->coll_w = 6;
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
;SpritePlayer.c:68: THIS->coll_h = 11;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0010
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x0b
;SpritePlayer.c:70: archer_state = STATE_JUMPING;
	ld	hl, #_archer_state
	ld	(hl), #0x02
;SpritePlayer.c:72: hit_cooldown = 36u;
	ld	hl, #_hit_cooldown
	ld	(hl), #0x24
;SpritePlayer.c:74: }
	add	sp, #2
	ret
_anim_idle:
	.db #0x01	; 1
	.db #0x00	; 0
_anim_jump:
	.db #0x01	; 1
	.db #0x0a	; 10
_anim_jump_up:
	.db #0x01	; 1
	.db #0x0b	; 11
_anim_up:
	.db #0x01	; 1
	.db #0x00	; 0
_anim_dead:
	.db #0x01	; 1
	.db #0x00	; 0
_anim_walk:
	.db #0x04	; 4
	.db #0x07	; 7
	.db #0x06	; 6
	.db #0x05	; 5
	.db #0x04	; 4
_anim_shield:
	.db #0x01	; 1
	.db #0x03	; 3
_anim_hit:
	.db #0x02	; 2
	.db #0x08	; 8
	.db #0x09	; 9
_anim_shoot:
	.db #0x02	; 2
	.db #0x01	; 1
	.db #0x02	; 2
_anim_flying:
	.db #0x04	; 4
	.db #0x0c	; 12
	.db #0x0d	; 13
	.db #0x0e	; 14
	.db #0x0d	; 13
;SpritePlayer.c:76: void Update_SpritePlayer() {
;	---------------------------------
; Function Update_SpritePlayer
; ---------------------------------
_Update_SpritePlayer::
	add	sp, #-18
;SpritePlayer.c:80: if(KEY_TICKED(J_START)){
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#18
	ld	(hl), a
	pop	hl
	push	hl
	ld	hl, #_previous_keys
	ld	a, (hl)
	ldhl	sp,	#19
	ld	(hl), a
	pop	hl
	ldhl	sp,	#16
	bit	7, (hl)
	jr	Z,00102$
	ldhl	sp,	#17
	bit	7, (hl)
	jr	NZ,00102$
;SpritePlayer.c:81: SetState(StateGame);
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
;SpritePlayer.c:82: return;
	jp	00261$
00102$:
;SpritePlayer.c:85: if (KEY_RELEASED(J_SELECT)){
	ldhl	sp,	#17
	bit	6, (hl)
	jp	Z,00107$
	ldhl	sp,	#16
	bit	6, (hl)
	jp	NZ,00107$
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	inc	a
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:87: archer_data->amulet %= 6u;
	ld	a, (bc)
	ld	e, a
	ld	d, #0x00
	push	bc
	ld	hl, #0x0006
	push	hl
	push	de
	call	__moduint
	add	sp, #4
	pop	bc
	ld	a, e
	ld	(bc), a
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:88: if(archer_data->amulet == 0u){
	ld	a, (bc)
	or	a, a
	jr	NZ,00107$
;SpritePlayer.c:89: archer_data->amulet = 1u;
	ld	a, #0x01
	ld	(bc), a
00107$:
;SpritePlayer.c:93: switch(archer_state) {
	ld	hl, #_archer_state
	ld	a, (hl)
	or	a, a
	jp	Z,00114$
	ld	hl, #_archer_state
	ld	a, (hl)
	dec	a
	jp	Z,00114$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	jp	Z,00147$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00166$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x05
	jp	NZ,00171$
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:95: archer_data->ups -= 1;
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	dec	a
	ld	(bc), a
;SpritePlayer.c:96: archer_data->hp = 100;
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	(hl), #0x64
;SpritePlayer.c:97: if (archer_data->ups == -1){SetState(StateGameOver);}
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	a, (hl)
	inc	a
	jr	NZ,00111$
	ld	a, #0x02
	push	af
	inc	sp
	call	_SetState
	inc	sp
	jp	00261$
00111$:
;SpritePlayer.c:98: else{SetState(StateGame);}
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
;SpritePlayer.c:99: return;
	jp	00261$
;SpritePlayer.c:102: case STATE_NORMAL_PLATFORM:
00114$:
;SpritePlayer.c:103: MoveArcher();
	call	_MoveArcher
;SpritePlayer.c:104: CheckCollisionTile();
	call	_CheckCollisionTile
;SpritePlayer.c:105: if(shoot_cooldown) {
	ld	hl, #_shoot_cooldown
	ld	a, (hl)
	or	a, a
	jr	Z,00130$
;SpritePlayer.c:106: SetSpriteAnim(THIS, anim_shoot, 12u);
	ld	a, #0x0c
	push	af
	inc	sp
	ld	hl, #_anim_shoot
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	jp	00131$
00130$:
;SpritePlayer.c:80: if(KEY_TICKED(J_START)){
	ld	hl, #_keys
	ld	a, (hl)
;SpritePlayer.c:108: if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
	bit	0, a
	jr	NZ,00118$
	bit	1, a
	jr	Z,00119$
00118$:
;SpritePlayer.c:109: SetSpriteAnim(THIS, anim_walk, 16u);
	ld	a, #0x10
	push	af
	inc	sp
	ld	hl, #_anim_walk
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	jp	00120$
00119$:
;SpritePlayer.c:111: if (archer_state == STATE_NORMAL_PLATFORM){SetSpriteAnim(THIS, anim_flying, 16u);}
	ld	hl, #_archer_state
	ld	a, (hl)
	dec	a
	jr	NZ,00116$
	ld	a, #0x10
	push	af
	inc	sp
	ld	hl, #_anim_flying
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	jr	00120$
00116$:
;SpritePlayer.c:112: else{SetSpriteAnim(THIS, anim_idle, 33u);}					
	ld	a, #0x21
	push	af
	inc	sp
	ld	hl, #_anim_idle
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
00120$:
;SpritePlayer.c:80: if(KEY_TICKED(J_START)){
	ld	hl, #_keys
	ld	a, (hl)
;SpritePlayer.c:114: if(KEY_PRESSED(J_UP)){
	and	a, #0x04
	ld	c, a
	ld	b, #0x00
	ld	a, b
	or	a, c
	jr	Z,00125$
;SpritePlayer.c:115: aimc += 1;
	ld	hl, #_aimc
	ld	a, (hl)
	inc	a
;SpritePlayer.c:116: if(aimc >= 16){
	ld	(hl),a
	sub	a, #0x10
	jr	C,00125$
;SpritePlayer.c:117: aimc=16;
	ld	(hl), #0x10
00125$:
;SpritePlayer.c:120: if(KEY_RELEASED(J_UP)){
	ld	hl, #_previous_keys
	ld	a, (hl)
	bit	2, a
	jr	Z,00131$
	ld	a, b
	or	a, c
	jr	NZ,00131$
;SpritePlayer.c:121: aimc = 0;
	ld	hl, #_aimc
	ld	(hl), #0x00
00131$:
;SpritePlayer.c:124: if (KEY_PRESSED(J_DOWN)){
	ld	hl, #_keys
	ld	a, (hl)
	bit	3, a
	jr	Z,00135$
;SpritePlayer.c:125: SetSpriteAnim(THIS, anim_shield, 8u);
	ld	a, #0x08
	push	af
	inc	sp
	ld	hl, #_anim_shield
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePlayer.c:126: THIS->coll_x = 8;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000d
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x08
	jr	00136$
00135$:
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:127: }else if (THIS->coll_x != 5){
	ld	hl, #0x000d
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	sub	a, #0x05
	jr	Z,00136$
;SpritePlayer.c:128: THIS->coll_x = 5;
	ld	a, #0x05
	ld	(bc), a
00136$:
;SpritePlayer.c:131: if(KEY_TICKED(J_A)) {
	ld	hl, #_keys
	ld	a, (hl)
	bit	4, a
	jr	Z,00138$
	ld	hl, #_previous_keys
	ld	a, (hl)
	bit	4, a
	jr	NZ,00138$
;SpritePlayer.c:132: Jump();
	call	_Jump
00138$:
;SpritePlayer.c:134: if(shoot_cooldown) {
	ld	hl, #_shoot_cooldown
	ld	a, (hl)
	or	a, a
	jr	Z,00143$
;SpritePlayer.c:135: shoot_cooldown -= 1u;
	dec	(hl)
	jp	00144$
00143$:
;SpritePlayer.c:137: if(KEY_TICKED(J_B) & (!KEY_PRESSED(J_DOWN) | (KEY_PRESSED(J_DOWN) & archer_state == STATE_JUMPING))) {
	ld	hl, #_keys
	ld	a, (hl)
	bit	5, a
	jr	Z,00263$
	ld	hl, #_previous_keys
	ld	c, (hl)
	xor	a, a
	bit	5, c
	jr	Z,00264$
00263$:
	ld	d, #0x00
	jr	00265$
00264$:
	ld	d, #0x01
00265$:
	ld	hl, #_keys
	ld	c, (hl)
	ld	b, #0x00
	ld	a, c
	and	a, #0x08
	ld	c, a
	ld	b, #0x00
	ld	a, b
	or	a, c
	sub	a,#0x01
	ld	a, #0x00
	rla
	ldhl	sp,	#17
	ld	(hl), a
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	ld	a, #0x01
	jr	Z,00714$
	xor	a, a
00714$:
	ld	e, a
	xor	a, a
	push	af
	ld	a, c
	and	a, e
	ld	c, a
	pop	af
	and	a, b
	ld	b, a
	ldhl	sp,	#17
	ld	e, (hl)
	xor	a, a
	push	af
	ld	a, c
	or	a, e
	ld	c, a
	pop	af
	or	a, b
	ld	b, a
	ld	e, d
	ld	d, #0x00
	ld	a, e
	and	a, c
	ld	c, a
	ld	a, d
	and	a, b
	or	a, c
	jr	Z,00144$
;SpritePlayer.c:138: Shoot();
	call	_Shoot
00144$:
;SpritePlayer.c:142: if((archer_accel_y >> 3) > 1) {
	ld	hl, #_archer_accel_y + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
	ld	a, b
	ld	e, a
	ld	a, #0x00
	ld	d, a
	ld	a, #0x01
	cp	a, c
	ld	a, #0x00
	sbc	a, b
	bit	7, e
	jr	Z,00715$
	bit	7, d
	jr	NZ,00716$
	cp	a, a
	jr	00716$
00715$:
	bit	7, d
	jr	Z,00716$
	scf
00716$:
	jp	NC, 00171$
;SpritePlayer.c:143: archer_state = STATE_JUMPING;
	ld	hl, #_archer_state
	ld	(hl), #0x02
;SpritePlayer.c:146: break;
	jp	00171$
;SpritePlayer.c:147: case STATE_JUMPING:
00147$:
;SpritePlayer.c:148: if(shoot_cooldown) {
	ld	hl, #_shoot_cooldown
	ld	a, (hl)
	or	a, a
	jr	Z,00164$
;SpritePlayer.c:149: shoot_cooldown -= 1u;
	dec	(hl)
	jp	00165$
00164$:
;SpritePlayer.c:80: if(KEY_TICKED(J_START)){
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#19
	ld	(hl), a
	pop	hl
	ld	hl, #_previous_keys
	ld	c, (hl)
;SpritePlayer.c:151: if(KEY_TICKED(J_B)) {
	ldhl	sp,	#17
	bit	5, (hl)
	jr	Z,00160$
	bit	5, c
	jr	NZ,00160$
;SpritePlayer.c:152: Shoot();
	call	_Shoot
	jp	00165$
00160$:
;SpritePlayer.c:154: if (archer_accel_y < 4){									
	ld	hl, #_archer_accel_y
	ld	a, (hl)
	sub	a, #0x04
	inc	hl
	ld	a, (hl)
	sbc	a, #0x00
	ld	d, (hl)
	ld	a, #0x00
	ld	e, a
	bit	7, e
	jr	Z,00720$
	bit	7, d
	jr	NZ,00721$
	cp	a, a
	jr	00721$
00720$:
	bit	7, d
	jr	Z,00721$
	scf
00721$:
	jp	NC, 00157$
;SpritePlayer.c:157: jump_power += 1u;
	ld	hl, #_jump_power
	ld	b, (hl)
	inc	b
;SpritePlayer.c:155: if(KEY_PRESSED(J_A)) {
	ldhl	sp,	#17
	ld	a, (hl)
	and	a, #0x10
	ld	e, a
	ld	d, #0x00
	ld	a, d
	or	a, e
	jr	Z,00154$
;SpritePlayer.c:156: if (jump_power < 12u){
	ld	hl, #_jump_power
	ld	a, (hl)
	sub	a, #0x0c
	jr	NC,00155$
;SpritePlayer.c:157: jump_power += 1u;
	ld	(hl), b
;SpritePlayer.c:158: archer_accel_y -= 2;
	ld	hl, #_archer_accel_y + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	dec	de
	dec	de
	dec	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
	jr	00155$
00154$:
;SpritePlayer.c:160: }else if (KEY_RELEASED(J_A)){
	bit	4, c
	jr	Z,00155$
	ld	a, d
	or	a, e
	jr	NZ,00155$
;SpritePlayer.c:161: jump_power += 1u;
	ld	hl, #_jump_power
	ld	(hl), b
;SpritePlayer.c:162: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
00155$:
;SpritePlayer.c:164: SetSpriteAnim(THIS, anim_jump_up, 33u);
	ld	a, #0x21
	push	af
	inc	sp
	ld	hl, #_anim_jump_up
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
	jr	00165$
00157$:
;SpritePlayer.c:166: jump_power = 0u;
	ld	hl, #_jump_power
	ld	(hl), #0x00
;SpritePlayer.c:167: archer_accel_y += 1;
	ld	hl, #_archer_accel_y
	inc	(hl)
	jr	NZ,00723$
	inc	hl
	inc	(hl)
00723$:
;SpritePlayer.c:168: SetSpriteAnim(THIS, anim_jump, 33u);
	ld	a, #0x21
	push	af
	inc	sp
	ld	hl, #_anim_jump
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
00165$:
;SpritePlayer.c:172: platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
;SpritePlayer.c:173: MoveArcher();
	call	_MoveArcher
;SpritePlayer.c:174: break;
	jr	00171$
;SpritePlayer.c:175: case STATE_HIT:
00166$:
;SpritePlayer.c:176: hit_cooldown -= 1;
	ld	hl, #_hit_cooldown
	ld	a, (hl)
	add	a, #0xff
	ld	(hl), a
;SpritePlayer.c:177: MoveArcher();
	call	_MoveArcher
;SpritePlayer.c:178: if (hit_cooldown == 0){
	ld	hl, #_hit_cooldown
	ld	a, (hl)
	or	a, a
	jr	NZ,00171$
;SpritePlayer.c:179: platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
;SpritePlayer.c:180: archer_state = STATE_NORMAL;
	ld	hl, #_archer_state
	ld	(hl), #0x00
;SpritePlayer.c:181: hit_cooldown = 24u;
	ld	hl, #_hit_cooldown
	ld	(hl), #0x18
;SpritePlayer.c:182: if(KEY_PRESSED(J_A)) {
	ld	hl, #_keys
	ld	a, (hl)
	bit	4, a
	jr	Z,00171$
;SpritePlayer.c:183: Jump();
	call	_Jump
;SpritePlayer.c:187: }//end switch archer_state
00171$:
;SpritePlayer.c:190: if(princess_parent == 0 && archer_state != STATE_LADDER && archer_state != STATE_HIT) {
	ld	hl, #_princess_parent + 1
	ld	a, (hl-)
	or	a, (hl)
	jp	NZ, 00184$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x03
	jp	Z,00184$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00184$
;SpritePlayer.c:192: if(archer_accel_y < 24) {
	ld	hl, #_archer_accel_y
	ld	a, (hl)
	sub	a, #0x18
	inc	hl
	ld	a, (hl)
	sbc	a, #0x00
	ld	d, (hl)
	ld	a, #0x00
	ld	e, a
	bit	7, e
	jr	Z,00727$
	bit	7, d
	jr	NZ,00728$
	cp	a, a
	jr	00728$
00727$:
	bit	7, d
	jr	Z,00728$
	scf
00728$:
	jr	NC,00173$
;SpritePlayer.c:193: archer_accel_y += 1;
	ld	hl, #_archer_accel_y
	inc	(hl)
	jr	NZ,00729$
	inc	hl
	inc	(hl)
00729$:
00173$:
;SpritePlayer.c:195: tile_collision = TranslateSprite(THIS, 0, archer_accel_y  >> 4 );
	ld	hl, #_archer_accel_y
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	sra	c
	rr	b
	sra	c
	rr	b
	sra	c
	rr	b
	sra	c
	rr	b
	push	bc
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
	ld	hl, #_tile_collision
	ld	(hl), e
;SpritePlayer.c:196: if(!tile_collision && delta_time != 0 && archer_accel_y < 24) { //Do another iteration if there is no collision
	ld	a, (hl)
	or	a, a
	jp	NZ, 00175$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00175$
	ld	hl, #_archer_accel_y
	ld	a, (hl)
	sub	a, #0x18
	inc	hl
	ld	a, (hl)
	sbc	a, #0x00
	ld	d, (hl)
	ld	a, #0x00
	ld	e, a
	bit	7, e
	jr	Z,00730$
	bit	7, d
	jr	NZ,00731$
	cp	a, a
	jr	00731$
00730$:
	bit	7, d
	jr	Z,00731$
	scf
00731$:
	jp	NC, 00175$
;SpritePlayer.c:197: archer_accel_y += 2;
	ld	hl, #_archer_accel_y
	ld	a, (hl)
	add	a, #0x02
	ld	(hl+), a
	ld	a, (hl)
	adc	a, #0x00
;SpritePlayer.c:198: tile_collision = TranslateSprite(THIS, 0, archer_accel_y >> 4);
	ld	(hl-), a
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	sra	c
	rr	b
	sra	c
	rr	b
	sra	c
	rr	b
	sra	c
	rr	b
	push	bc
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
	ld	hl, #_tile_collision
	ld	(hl), e
00175$:
;SpritePlayer.c:200: if(tile_collision) {
	ld	hl, #_tile_collision
	ld	a, (hl)
	or	a, a
	jp	Z, 00184$
;SpritePlayer.c:201: if(archer_state == STATE_JUMPING & archer_accel_y > 0) {
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	ld	a, #0x01
	jr	Z,00733$
	xor	a, a
00733$:
	ld	c, a
	ld	hl, #_archer_accel_y
	ld	a, #0x00
	sub	a, (hl)
	inc	hl
	ld	a, #0x00
	sbc	a, (hl)
	ld	a, #0x00
	ld	d, a
	ld	e, (hl)
	bit	7, e
	jr	Z,00734$
	bit	7, d
	jr	NZ,00735$
	cp	a, a
	jr	00735$
00734$:
	bit	7, d
	jr	Z,00735$
	scf
00735$:
	ld	a, #0x00
	rla
	and	a,c
	jr	Z,00179$
;SpritePlayer.c:202: archer_state = STATE_NORMAL;
	ld	hl, #_archer_state
	ld	(hl), #0x00
	jr	00180$
00179$:
;SpritePlayer.c:205: archer_accel_y = 0;	
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
00180$:
;SpritePlayer.c:207: CheckCollisionTile();
	call	_CheckCollisionTile
00184$:
;SpritePlayer.c:210: if(princess_parent && archer_state == STATE_JUMPING) {
	ld	hl, #_princess_parent + 1
	ld	a, (hl-)
	or	a, (hl)
	jr	Z,00188$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	jr	NZ,00188$
;SpritePlayer.c:211: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;SpritePlayer.c:212: archer_state = STATE_NORMAL;
	ld	hl, #_archer_state
	ld	(hl), #0x00
00188$:
;SpritePlayer.c:216: SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
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
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	xor	a, a
	ldhl	sp,	#17
	ld	(hl), a
00259$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#17
	ld	a, (hl)
	sub	a, c
	jp	Z,00261$
;SpritePlayer.c:217: if(ispr->type == SpriteItem) {
	pop	de
	push	de
	ld	hl, #0x0011
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
;SpritePlayer.c:219: struct ItemInfo* dataitem = (struct ItemInfo*)ispr->custom_data;
	pop	de
	push	de
	ld	hl, #0x0019
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:217: if(ispr->type == SpriteItem) {
	ld	a, c
	sub	a, #0x03
	jp	NZ,00208$
;SpritePlayer.c:218: if(CheckCollision(THIS, ispr)) {
	pop	hl
	push	hl
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
	jp	Z, 00208$
;SpritePlayer.c:219: struct ItemInfo* dataitem = (struct ItemInfo*)ispr->custom_data;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:220: if (dataitem->setup == 0u){ //se e' trasparente non faccio niente
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	or	a, a
	jp	NZ, 00208$
;SpritePlayer.c:221: switch(dataitem->type){
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, (bc)
	ld	c, a
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:223: archer_data->coins++;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0001
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:221: switch(dataitem->type){
	ld	a, c
	dec	a
	jr	Z,00190$
	ld	a,c
	cp	a,#0x02
	jp	Z,00193$
	cp	a,##0x03
	jp	Z,00194$
	cp	a,#0x06
	jp	Z,00195$
	cp	a,##0x07
	jp	Z,00198$
	sub	a, #0x0a
	jp	Z,00201$
	jp	00208$
;SpritePlayer.c:222: case 1u: //coins
00190$:
;SpritePlayer.c:223: archer_data->coins++;
	ldhl	sp,#(16 - 1)
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
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:223: archer_data->coins++;
	inc	bc
	ldhl	sp,	#15
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:224: if (archer_data->coins == 100){
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	sub	a, #0x64
	jr	NZ,00192$
;SpritePlayer.c:225: archer_data->coins = 0;
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:95: archer_data->ups -= 1;
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:226: archer_data->ups += 1;	
	ld	a, (bc)
	inc	a
	ld	(bc), a
00192$:
;SpritePlayer.c:228: PlayFx(CHANNEL_1, 3, 0x6d, 0x8c, 0x73, 0xff, 0xc7);
	ld	hl, #0x00c7
	push	hl
	ld	l, #0xff
	push	hl
	ld	l, #0x73
	push	hl
	ld	l, #0x8c
	push	hl
	ld	l, #0x6d
	push	hl
	ld	a, #0x03
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_PlayFx
	add	sp, #12
;SpritePlayer.c:229: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:230: break;
	jp	00208$
;SpritePlayer.c:231: case 2u: //hp
00193$:
;SpritePlayer.c:232: archer_data->hp = 100u;
	ldhl	sp,#(14 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x64
	ld	(bc), a
;SpritePlayer.c:233: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:234: break;
	jp	00208$
;SpritePlayer.c:235: case 3u: //up
00194$:
;SpritePlayer.c:95: archer_data->ups -= 1;
	ldhl	sp,#(14 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:236: archer_data->ups += 1;
	ld	a, (bc)
	inc	a
	ld	(bc), a
;SpritePlayer.c:237: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:238: break;
	jp	00208$
;SpritePlayer.c:239: case 6u: //wrench
00195$:
;SpritePlayer.c:240: if (archer_data->tool == 0){
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	or	a, a
	jp	NZ, 00208$
;SpritePlayer.c:241: archer_data->tool = 6;
	ld	a, #0x06
	ld	(bc), a
;SpritePlayer.c:242: SpriteManagerRemoveSprite(ispr);	
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:244: break;
	jp	00208$
;SpritePlayer.c:245: case 7u: //dcoin
00198$:
;SpritePlayer.c:246: archer_data->coins+=10;
	ldhl	sp,#(16 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	add	a, #0x0a
	ld	c, a
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:223: archer_data->coins++;
	inc	bc
	ld	a, (bc)
;SpritePlayer.c:247: if (archer_data->coins >= 100){
	cp	a, #0x64
	jr	C,00200$
;SpritePlayer.c:248: archer_data->coins = archer_data->coins - 100;
	add	a, #0x9c
	ld	(bc), a
;SpritePlayer.c:86: archer_data->amulet += 1u;
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:95: archer_data->ups -= 1;
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:249: archer_data->ups += 1;	
	ld	a, (bc)
	inc	a
	ld	(bc), a
00200$:
;SpritePlayer.c:251: PlayFx(CHANNEL_1, 3, 0x6d, 0x8c, 0x73, 0xff, 0xc7);
	ld	hl, #0x00c7
	push	hl
	ld	l, #0xff
	push	hl
	ld	l, #0x73
	push	hl
	ld	l, #0x8c
	push	hl
	ld	l, #0x6d
	push	hl
	ld	a, #0x03
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_PlayFx
	add	sp, #12
;SpritePlayer.c:252: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:253: break;
	jr	00208$
;SpritePlayer.c:254: case 10u: //scrigno
00201$:
;SpritePlayer.c:255: dataitem->collided = 1;
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpritePlayer.c:257: }
00208$:
;SpritePlayer.c:261: if(ispr->type == SpritePlatform) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
;SpritePlayer.c:269: THIS->y = ispr->y - ispr->coll_h;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:261: if(ispr->type == SpritePlatform) {
	ld	a, c
	sub	a, #0x02
	jp	NZ,00216$
;SpritePlayer.c:262: if(CheckCollision(THIS, ispr)) {
	pop	hl
	push	hl
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
	jp	Z, 00216$
;SpritePlayer.c:263: if (archer_accel_y > 0){//se sono in salita non collido !
	ld	hl, #_archer_accel_y
	ld	a, #0x00
	sub	a, (hl)
	inc	hl
	ld	a, #0x00
	sbc	a, (hl)
	ld	a, #0x00
	ld	d, a
	ld	e, (hl)
	bit	7, e
	jr	Z,00753$
	bit	7, d
	jr	NZ,00754$
	cp	a, a
	jr	00754$
00753$:
	bit	7, d
	jr	Z,00754$
	scf
00754$:
	jp	NC, 00216$
;SpritePlayer.c:264: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;SpritePlayer.c:265: struct PlatformInfo* datap = (struct PlatformInfo*)ispr->custom_data;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:266: platform_vx = datap->vx;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	hl, #_platform_vx
	ld	(hl), a
;SpritePlayer.c:267: if(archer_state != STATE_NORMAL & archer_state != STATE_NORMAL_PLATFORM){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a,#0x01
	ld	a, #0x00
	rla
	xor	a, #0x01
	ld	c, a
	ld	a, (hl)
	dec	a
	ld	a, #0x01
	jr	Z,00756$
	xor	a, a
00756$:
	xor	a, #0x01
	and	a, c
	bit	0, a
	jp	Z, 00216$
;SpritePlayer.c:268: archer_state = STATE_NORMAL_PLATFORM;
	ld	hl, #_archer_state
	ld	(hl), #0x01
;SpritePlayer.c:269: THIS->y = ispr->y - ispr->coll_h;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#15
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	pop	de
	push	de
	ld	hl, #0x0010
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,#(16 - 1)
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
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
00216$:
;SpritePlayer.c:274: if(ispr->type == SpriteEnemy || ispr->type == SpriteScorpion || ispr->type == SpritePorcupine) { //collision con l' enemy
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x04
	jr	Z,00237$
	cp	a, #0x05
	jr	Z,00237$
	sub	a, #0x06
	jp	NZ,00238$
00237$:
;SpritePlayer.c:275: if(CheckCollision(THIS, ispr) & archer_state != STATE_HIT) {
	pop	hl
	push	hl
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_CheckCollision
	add	sp, #4
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	ld	a, #0x01
	jr	Z,00762$
	xor	a, a
00762$:
	xor	a, #0x01
	and	a,e
	jp	Z, 00238$
;SpritePlayer.c:276: struct EnemyInfo* dataenemy = (struct EnemyInfo*)ispr->custom_data;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:277: if (dataenemy->enemy_state == ENEMY_STATE_DEAD){
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, (bc)
	sub	a, #0x03
	jp	Z,00261$
	jr	00218$
;SpritePlayer.c:278: return;
	jp	00261$
00218$:
;SpritePlayer.c:280: UINT8 being_hit = 1;
	ldhl	sp,	#10
	ld	(hl), #0x01
;SpritePlayer.c:281: if (KEY_PRESSED(J_DOWN)){ //se mi sto riparando e lo sono girato dove serve
	ld	hl, #_keys
	ld	c, (hl)
;SpritePlayer.c:282: if (ispr->x < THIS->x){
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:281: if (KEY_PRESSED(J_DOWN)){ //se mi sto riparando e lo sono girato dove serve
	bit	3, c
	jp	Z,00227$
;SpritePlayer.c:282: if (ispr->x < THIS->x){
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;SpritePlayer.c:126: THIS->coll_x = 8;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:282: if (ispr->x < THIS->x){
	ld	hl, #0x0008
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
	dec	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;SpritePlayer.c:283: if (SPRITE_GET_VMIRROR(THIS)){//mi sto riparando bene	
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	and	a, #0x20
	ld	c, a
	ld	b, #0x00
;SpritePlayer.c:282: if (ispr->x < THIS->x){
	ldhl	sp,	#13
	ld	e, l
	ld	d, h
	ldhl	sp,	#15
	ld	a, (de)
	sub	a, (hl)
	inc	hl
	inc	de
	ld	a, (de)
	sbc	a, (hl)
	jr	NC,00224$
;SpritePlayer.c:283: if (SPRITE_GET_VMIRROR(THIS)){//mi sto riparando bene	
	ld	a, b
	or	a, c
	jp	Z, 00227$
;SpritePlayer.c:284: ispr->x -= 16;
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0010
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ld	b, a
	ld	c, e
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:285: being_hit = 0;
	xor	a, a
	ldhl	sp,	#10
	ld	(hl), a
	jr	00227$
00224$:
;SpritePlayer.c:288: if (!SPRITE_GET_VMIRROR(THIS)){
	ld	a, b
	or	a, c
	jr	NZ,00227$
;SpritePlayer.c:289: ispr->x += 16;
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0010
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:290: being_hit = 0;
	xor	a, a
	ldhl	sp,	#10
	ld	(hl), a
00227$:
;SpritePlayer.c:294: if (being_hit & archer_state != STATE_DEAD){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x05
	ld	a, #0x01
	jr	Z,00767$
	xor	a, a
00767$:
	xor	a, #0x01
	ldhl	sp,	#10
	ld	c, (hl)
	and	a,c
	jp	Z, 00238$
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:232: archer_data->hp = 100u;
	inc	bc
	inc	bc
	ldhl	sp,	#15
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:295: archer_data->hp -=  dataenemy->enemydamage;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0006
	add	hl, de
	ld	b,l
	ld	a,h
	ld	b, (hl)
	ld	a, c
	sub	a, b
	ld	c, a
	ldhl	sp,	#15
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:232: archer_data->hp = 100u;
	inc	bc
	inc	bc
;SpritePlayer.c:296: if (archer_data->hp <= 0){
	ld	a, (bc)
	ldhl	sp,	#16
	ld	(hl),a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00768$
	bit	7, d
	jr	NZ,00769$
	cp	a, a
	jr	00769$
00768$:
	bit	7, d
	jr	Z,00769$
	scf
00769$:
	jr	C,00229$
;SpritePlayer.c:297: archer_data->hp = 0;
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:298: Die();
	call	_Die
00229$:
;SpritePlayer.c:300: Hit();
	call	_Hit
;SpritePlayer.c:301: if (ispr->x < THIS->x){
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#15
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x08
	ld	b, a
	jr	NC,00770$
	inc	c
00770$:
	ld	l, b
	ld	h, c
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#15
	ld	a, (hl)
	sub	a, c
	inc	hl
	ld	a, (hl)
	sbc	a, b
	jr	NC,00231$
;SpritePlayer.c:302: platform_vx = 1;
	ld	hl, #_platform_vx
	ld	(hl), #0x01
	jr	00238$
00231$:
;SpritePlayer.c:304: platform_vx = -1;
	ld	hl, #_platform_vx
	ld	(hl), #0xff
00238$:
;SpritePlayer.c:309: if(ispr->type == SpriteArrow) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	jp	NZ,00260$
;SpritePlayer.c:310: if(CheckCollision(THIS, ispr)) {
	pop	hl
	push	hl
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
	jp	Z, 00260$
;SpritePlayer.c:311: struct ArrowInfo* arrowdata = (struct ArrowInfo*)ispr->custom_data;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:312: if (arrowdata->type == 6u){ //spine from porcupine
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	ld	a, (hl)
	and	a, #0x0f
	sub	a, #0x06
	jp	NZ,00246$
;SpritePlayer.c:313: if(!KEY_PRESSED(J_DOWN)){
	ld	hl, #_keys
	ld	a, (hl)
	bit	3, a
	jp	NZ,00244$
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:232: archer_data->hp = 100u;
	inc	bc
	inc	bc
	ldhl	sp,	#13
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:314: archer_data->hp -=  arrowdata->arrowdamage;
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	b,l
	ld	a,h
	ld	b, (hl)
	ld	a, c
	sub	a, b
	ld	c, a
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpritePlayer.c:86: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:232: archer_data->hp = 100u;
	inc	bc
	inc	bc
;SpritePlayer.c:315: if (archer_data->hp <= 0){
	ld	a, (bc)
	ldhl	sp,	#17
	ld	(hl),a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00777$
	bit	7, d
	jr	NZ,00778$
	cp	a, a
	jr	00778$
00777$:
	bit	7, d
	jr	Z,00778$
	scf
00778$:
	jr	C,00242$
;SpritePlayer.c:316: archer_data->hp = 0;
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:317: Die();
	call	_Die
00242$:
;SpritePlayer.c:319: Hit();
	call	_Hit
00244$:
;SpritePlayer.c:321: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:322: return;
	jp	00261$
00246$:
;SpritePlayer.c:324: struct ArrowInfo* datap = (struct ArrowInfo*)ispr->custom_data;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#12
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:325: if (datap->arrowdir != 1){return;}//guardo solo se è orizzontale
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	dec	a
	jp	NZ,00261$
;SpritePlayer.c:326: if (archer_accel_y > 0 & THIS->y < (ispr->y-4)){//se sono in salita non collido !
	ld	hl, #_archer_accel_y
	ld	a, #0x00
	sub	a, (hl)
	inc	hl
	ld	a, #0x00
	sbc	a, (hl)
	ld	a, #0x00
	ld	d, a
	ld	e, (hl)
	bit	7, e
	jr	Z,00780$
	bit	7, d
	jr	NZ,00781$
	cp	a, a
	jr	00781$
00780$:
	bit	7, d
	jr	Z,00781$
	scf
00781$:
	ld	a, #0x00
	rla
	ldhl	sp,	#14
	ld	(hl), a
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x0a
	ld	b, a
	jr	NC,00782$
	inc	c
00782$:
	ld	e, b
	ld	d, c
	ld	a,(de)
	ldhl	sp,	#15
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,#(7 - 1)
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
	ldhl	sp,	#15
	ld	a, (hl)
	sub	a, c
	inc	hl
	ld	a, (hl)
	sbc	a, b
	ld	a, #0x00
	rla
	ldhl	sp,	#14
	and	a,(hl)
	jp	Z, 00260$
;SpritePlayer.c:328: ispr->coll_x = 0;
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:329: ispr->coll_w = 8;	
	pop	de
	push	de
	ld	hl, #0x000f
	add	hl, de
	ld	c,l
	ld	a,h
	ld	(hl), #0x08
;SpritePlayer.c:330: platform_vx = datap->vx;
	ldhl	sp,#(13 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	l, c
	ld	h, b
	ld	a, (hl)
	and	a, #0x0f
	ld	hl, #_platform_vx
	ld	(hl), a
;SpritePlayer.c:331: if(archer_state != STATE_NORMAL & archer_state != STATE_NORMAL_PLATFORM){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a,#0x01
	ld	a, #0x00
	rla
	xor	a, #0x01
	ld	c, a
	ld	a, (hl)
	dec	a
	ld	a, #0x01
	jr	Z,00784$
	xor	a, a
00784$:
	xor	a, #0x01
	and	a, c
	bit	0, a
	jp	Z, 00260$
;SpritePlayer.c:332: archer_state = STATE_NORMAL_PLATFORM;
	ld	hl, #_archer_state
	ld	(hl), #0x01
;SpritePlayer.c:333: THIS->y = ispr->y - 12;
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
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	ld	a, c
	add	a, #0xf4
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
	ldhl	sp,	#15
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
00260$:
;SpritePlayer.c:216: SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
	ldhl	sp,	#17
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
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	jp	00259$
00261$:
;SpritePlayer.c:340: }
	add	sp, #18
	ret
;SpritePlayer.c:342: void Die(){
;	---------------------------------
; Function Die
; ---------------------------------
_Die::
;SpritePlayer.c:343: SetSpriteAnim(THIS, anim_dead, 12u);	
	ld	a, #0x0c
	push	af
	inc	sp
	ld	hl, #_anim_dead
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePlayer.c:344: archer_state = STATE_DEAD;
	ld	hl, #_archer_state
	ld	(hl), #0x05
;SpritePlayer.c:345: }
	ret
;SpritePlayer.c:347: void Shoot() {
;	---------------------------------
; Function Shoot
; ---------------------------------
_Shoot::
	add	sp, #-5
;SpritePlayer.c:348: SetSpriteAnim(THIS, anim_shoot, 16u);
	ld	a, #0x10
	push	af
	inc	sp
	ld	hl, #_anim_shoot
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePlayer.c:349: struct Sprite* arrow_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
	ld	hl, #0x0000
	push	hl
	ld	l, #0x00
	push	hl
	ld	a, #0x01
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	inc	sp
	inc	sp
	push	de
;SpritePlayer.c:352: arrow_sprite->flags = THIS->flags;
	pop	de
	push	de
	ld	hl, #0x000c
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
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
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;SpritePlayer.c:353: arrow_sprite->x = THIS->x;
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), d
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x08
	ld	b, a
	jr	NC,00141$
	inc	c
00141$:
	ld	l, b
	ld	h, c
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:354: arrow_sprite->x += 4;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:355: arrow_sprite->y = THIS->y;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
	ld	hl, #_THIS
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x0a
	ld	b, a
	jr	NC,00142$
	inc	c
00142$:
	ld	l, b
	ld	h, c
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:356: struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_sprite->custom_data;
	pop	de
	push	de
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
;SpritePlayer.c:357: if (archer_data->amulet){arrow_data->type = archer_data->amulet;}
	ld	hl, #_archer_data + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	or	a, a
	jr	Z,00102$
	ld	e, c
	ld	d, b
	and	a, #0x0f
	ld	l, a
	ld	a, (de)
	and	a, #0xf0
	or	a, l
	ld	(de), a
	jr	00103$
00102$:
;SpritePlayer.c:358: else{arrow_data->type = 1;}
	ld	e, c
	ld	d, b
	ld	a, (de)
	and	a, #0xf0
	or	a, #0x01
	ld	(de),a
00103$:
;SpritePlayer.c:359: if (KEY_PRESSED(J_DOWN)){
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#6
	ld	(hl), a
	pop	hl
;SpritePlayer.c:360: arrow_data->arrowdir = 4; // verticale in giu
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:359: if (KEY_PRESSED(J_DOWN)){
	ldhl	sp,	#4
	bit	3, (hl)
	jr	Z,00112$
;SpritePlayer.c:360: arrow_data->arrowdir = 4; // verticale in giu
	ld	a, #0x04
	ld	(bc), a
;SpritePlayer.c:361: arrow_sprite->y += 8;
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, a
	inc	de
	ld	a,(de)
	ld	c, a
	ld	a, b
	add	a, #0x08
	ld	b, a
	jr	NC,00144$
	inc	c
00144$:
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), b
	inc	hl
	ld	(hl), c
	jp	00113$
00112$:
;SpritePlayer.c:363: if (KEY_PRESSED(J_UP)){ //diagonale
	ldhl	sp,	#4
	bit	2, (hl)
	jr	Z,00107$
;SpritePlayer.c:364: arrow_data->arrowdir = 2;
	ld	a, #0x02
	ld	(bc), a
	jr	00108$
00107$:
;SpritePlayer.c:366: if(aimc < 16){ //orizzontale
	ld	hl, #_aimc
	ld	a, (hl)
	sub	a, #0x10
	jr	NC,00108$
;SpritePlayer.c:367: arrow_data->arrowdir = 1;
	ld	a, #0x01
	ld	(bc), a
00108$:
;SpritePlayer.c:370: if (aimc == 16){ // verticale in su
	ld	hl, #_aimc
	ld	a, (hl)
	sub	a, #0x10
	jr	NZ,00113$
;SpritePlayer.c:371: arrow_data->arrowdir = 3;
	ld	a, #0x03
	ld	(bc), a
;SpritePlayer.c:372: arrow_sprite->y -= 4;
	ldhl	sp,#(3 - 1)
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
00113$:
;SpritePlayer.c:375: shoot_cooldown = 4;//8
	ld	hl, #_shoot_cooldown
	ld	(hl), #0x04
;SpritePlayer.c:376: aimc = 0;
	ld	hl, #_aimc
	ld	(hl), #0x00
;SpritePlayer.c:377: }
	add	sp, #5
	ret
;SpritePlayer.c:379: void Jump() {
;	---------------------------------
; Function Jump
; ---------------------------------
_Jump::
;SpritePlayer.c:380: if(archer_state != STATE_JUMPING) {
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	ret	Z
;SpritePlayer.c:381: NR50_REG = 0x22; //Max volume		
	ld	a, #0x22
	ldh	(_NR50_REG+0),a
;SpritePlayer.c:383: archer_state = STATE_JUMPING;
	ld	hl, #_archer_state
	ld	(hl), #0x02
;SpritePlayer.c:384: archer_accel_y = -8;
	ld	hl, #_archer_accel_y
	ld	(hl), #0xf8
	inc	hl
	ld	(hl), #0xff
;SpritePlayer.c:385: princess_parent = 0;
	ld	hl, #_princess_parent
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;SpritePlayer.c:386: SetSpriteAnim(THIS, anim_jump_up, 12u);
	ld	a, #0x0c
	push	af
	inc	sp
	ld	hl, #_anim_jump_up
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePlayer.c:388: }
	ret
;SpritePlayer.c:390: void MoveArcher() {
;	---------------------------------
; Function MoveArcher
; ---------------------------------
_MoveArcher::
	add	sp, #-3
;SpritePlayer.c:392: if(KEY_PRESSED(J_LEFT)) {
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	pop	hl
;SpritePlayer.c:396: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#1
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:397: tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
	ld	hl, #_delta_time
	ld	c, (hl)
;SpritePlayer.c:396: if (SPRITE_GET_VMIRROR(THIS)){
	ldhl	sp,#(2 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000c
	add	hl, de
	ld	b, l
	ld	a, h
;SpritePlayer.c:392: if(KEY_PRESSED(J_LEFT)) {
	ldhl	sp,	#0
	bit	1, (hl)
	jp	Z,00111$
;SpritePlayer.c:393: if(KEY_PRESSED(J_DOWN)){
	ldhl	sp,	#0
	bit	3, (hl)
	jr	NZ,00105$
;SpritePlayer.c:396: if (SPRITE_GET_VMIRROR(THIS)){
	ld	l, b
	ld	h, a
	ld	a, (hl)
	bit	5, a
	jr	Z,00105$
;SpritePlayer.c:397: tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
	ld	b, #0xff
	inc	c
	jr	00145$
00144$:
	sla	b
00145$:
	dec	c
	jr	NZ,00144$
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
	ld	hl, #_tile_collision
	ld	(hl), e
00105$:
;SpritePlayer.c:396: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
;SpritePlayer.c:400: SPRITE_SET_VMIRROR(THIS);
	ld	a, (bc)
	set	5, a
	ld	(bc), a
	jp	00112$
00111$:
;SpritePlayer.c:402: else if(KEY_PRESSED(J_RIGHT)) {
	ldhl	sp,	#0
	bit	0, (hl)
	jp	Z,00112$
;SpritePlayer.c:403: if(!SPRITE_GET_VMIRROR(THIS) & !KEY_PRESSED(J_DOWN)){
	ld	l, b
	ld	h, a
	ld	a, (hl)
	ld	e, a
	ld	d, #0x00
	ld	a, e
	and	a, #0x20
	ld	e, a
	ld	d, #0x00
	ld	a, d
	or	a, e
	sub	a,#0x01
	ld	a, #0x00
	rla
	ld	b, a
	ld	hl, #_keys
	ld	e, (hl)
	ld	d, #0x00
	ld	a, e
	and	a, #0x08
	ld	e, a
	ld	d, #0x00
	ld	a, d
	or	a, e
	sub	a,#0x01
	ld	a, #0x00
	rla
	and	a, b
	bit	0, a
	jr	Z,00107$
;SpritePlayer.c:404: tile_collision = TranslateSprite(THIS, 1 << delta_time, 0);
	ld	b, #0x01
	inc	c
	jr	00148$
00147$:
	sla	b
00148$:
	dec	c
	jr	NZ,00147$
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
	ld	hl, #_tile_collision
	ld	(hl), e
00107$:
;SpritePlayer.c:396: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
;SpritePlayer.c:406: SPRITE_UNSET_VMIRROR(THIS);
	ld	a, (bc)
	res	5, a
	ld	(bc), a
00112$:
;SpritePlayer.c:408: MoveArcherRelativePlatform();
	call	_MoveArcherRelativePlatform
;SpritePlayer.c:409: }
	add	sp, #3
	ret
;SpritePlayer.c:411: void MoveArcherRelativePlatform(){
;	---------------------------------
; Function MoveArcherRelativePlatform
; ---------------------------------
_MoveArcherRelativePlatform::
;SpritePlayer.c:412: tile_collision = TranslateSprite(THIS, platform_vx << delta_time, 0);
	ld	hl, #_delta_time
	ld	c, (hl)
	ld	hl, #_platform_vx
	ld	b, (hl)
	inc	c
	jr	00104$
00103$:
	sla	b
00104$:
	dec	c
	jr	NZ,00103$
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
	ld	hl, #_tile_collision
	ld	(hl), e
;SpritePlayer.c:413: }
	ret
;SpritePlayer.c:415: void CheckCollisionTile() {
;	---------------------------------
; Function CheckCollisionTile
; ---------------------------------
_CheckCollisionTile::
	dec	sp
;SpritePlayer.c:416: if(tile_collision){
	ld	hl, #_tile_collision
	ld	a, (hl)
	or	a, a
	jr	Z,00102$
;SpritePlayer.c:417: platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
00102$:
;SpritePlayer.c:419: switch(tile_collision) {
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x02
	jr	Z,00103$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x07
	jp	Z,00110$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x13
	jp	Z,00111$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x29
	jp	Z,00108$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x2a
	jp	Z,00109$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x2e
	jp	Z,00112$
	jp	00114$
;SpritePlayer.c:420: case 2u:
00103$:
;SpritePlayer.c:421: if (archer_state != STATE_HIT){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00114$
;SpritePlayer.c:422: archer_data->hp -=  5;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, (bc)
	add	a, #0xfb
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
;SpritePlayer.c:423: if (archer_data->hp <= 0){
	ld	a, (bc)
	ldhl	sp,	#0
	ld	(hl),a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00168$
	bit	7, d
	jr	NZ,00169$
	cp	a, a
	jr	00169$
00168$:
	bit	7, d
	jr	Z,00169$
	scf
00169$:
	jr	C,00105$
;SpritePlayer.c:424: archer_data->hp = 0;
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:425: archer_state = STATE_DEAD;
	ld	hl, #_archer_state
	ld	(hl), #0x05
00105$:
;SpritePlayer.c:427: Hit();
	call	_Hit
;SpritePlayer.c:429: break;
	jr	00114$
;SpritePlayer.c:430: case 41u: //next map
00108$:
;SpritePlayer.c:431: load_next = 1;
	ld	hl, #_load_next
	ld	(hl), #0x01
;SpritePlayer.c:432: break;
	jr	00114$
;SpritePlayer.c:433: case 42u: //previous map
00109$:
;SpritePlayer.c:434: load_next = -1;
	ld	hl, #_load_next
	ld	(hl), #0xff
;SpritePlayer.c:435: break;
	jr	00114$
;SpritePlayer.c:436: case 7u: //fine level
00110$:
;SpritePlayer.c:437: load_next = 10;
	ld	hl, #_load_next
	ld	(hl), #0x0a
;SpritePlayer.c:438: break;
	jr	00114$
;SpritePlayer.c:439: case 19u: //exit secret room
00111$:
;SpritePlayer.c:440: load_next_s = -1;
	ld	hl, #_load_next_s
	ld	(hl), #0xff
;SpritePlayer.c:441: break;
	jr	00114$
;SpritePlayer.c:442: case 46u: //secret room
00112$:
;SpritePlayer.c:443: load_next_s = 1;
	ld	hl, #_load_next_s
	ld	(hl), #0x01
;SpritePlayer.c:449: }
00114$:
;SpritePlayer.c:450: }
	inc	sp
	ret
;SpritePlayer.c:452: void Hit() {
;	---------------------------------
; Function Hit
; ---------------------------------
_Hit::
	add	sp, #-2
;SpritePlayer.c:453: if (archer_state != STATE_DEAD){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x05
	jp	Z,00103$
;SpritePlayer.c:454: archer_state = STATE_HIT;	
	ld	hl, #_archer_state
	ld	(hl), #0x04
;SpritePlayer.c:455: platform_vx = 1;
	ld	hl, #_platform_vx
	ld	(hl), #0x01
;SpritePlayer.c:456: THIS->y -= 6;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000a
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	ld	a, c
	add	a, #0xfa
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:457: SetSpriteAnim(THIS, anim_hit, 32u);
	ld	a, #0x20
	push	af
	inc	sp
	ld	hl, #_anim_hit
	push	hl
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_SetSpriteAnim
	add	sp, #5
;SpritePlayer.c:458: NR50_REG = 0x55; //Max volume
	ld	a, #0x55
	ldh	(_NR50_REG+0),a
;SpritePlayer.c:459: PlayFx(CHANNEL_1, 2, 0x4c, 0x81, 0x43, 0x73, 0x86);
	ld	hl, #0x0086
	push	hl
	ld	l, #0x73
	push	hl
	ld	l, #0x43
	push	hl
	ld	l, #0x81
	push	hl
	ld	l, #0x4c
	push	hl
	ld	a, #0x02
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_PlayFx
	add	sp, #12
00103$:
;SpritePlayer.c:461: }
	add	sp, #2
	ret
;SpritePlayer.c:464: void Destroy_SpritePlayer() {
;	---------------------------------
; Function Destroy_SpritePlayer
; ---------------------------------
_Destroy_SpritePlayer::
;SpritePlayer.c:466: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
