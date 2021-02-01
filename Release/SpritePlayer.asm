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
	.globl _princess_parent
	.globl _death_cooldown
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
_death_cooldown::
	.ds 1
_princess_parent::
	.ds 2
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
;custom_datas.h:54: UINT8 damage_cooldown = 30u;
	ld	hl, #_damage_cooldown
	ld	(hl), #0x1e
;custom_datas.h:55: UINT8 attack_wait = 32u;
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
;SpritePlayer.c:28: UINT8 death_cooldown = 0;
	ld	hl, #_death_cooldown
	ld	(hl), #0x00
;SpritePlayer.c:30: struct Sprite* princess_parent = 0;
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
;SpritePlayer.c:57: void Start_SpritePlayer() {
;	---------------------------------
; Function Start_SpritePlayer
; ---------------------------------
_Start_SpritePlayer::
	add	sp, #-2
;SpritePlayer.c:58: archer_data = (struct ArcherInfo*)THIS->custom_data;
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
;SpritePlayer.c:61: THIS->coll_x = 5;
	ld	hl, #0x000d
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x05
;SpritePlayer.c:62: THIS->coll_y = 5;
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
;SpritePlayer.c:63: THIS->coll_w = 6;
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
;SpritePlayer.c:64: THIS->coll_h = 11;
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
;SpritePlayer.c:66: archer_state = STATE_JUMPING;
	ld	hl, #_archer_state
	ld	(hl), #0x02
;SpritePlayer.c:68: hit_cooldown = 36u;
	ld	hl, #_hit_cooldown
	ld	(hl), #0x24
;SpritePlayer.c:70: }
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
	.db #0x0f	; 15
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
;SpritePlayer.c:72: void Update_SpritePlayer() {
;	---------------------------------
; Function Update_SpritePlayer
; ---------------------------------
_Update_SpritePlayer::
	add	sp, #-18
;SpritePlayer.c:74: if(archer_state == STATE_DIAG ){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x05
	jr	NZ,00104$
;SpritePlayer.c:75: if(ANY_KEY_PRESSED){
	ld	hl, #_keys
	ld	a, (hl)
	or	a, a
	jp	Z,00281$
;SpritePlayer.c:76: show_diag = -1;
	ld	hl, #_show_diag
	ld	(hl), #0xff
;SpritePlayer.c:78: return;
	jp	00281$
00104$:
;SpritePlayer.c:81: if(KEY_TICKED(J_START)){
	ld	hl, #_keys
	ld	c, (hl)
	ld	hl, #_previous_keys
	ld	a, (hl)
	bit	7, c
	jr	Z,00106$
	bit	7, a
	jr	NZ,00106$
;SpritePlayer.c:82: SetState(StateGame);
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
;SpritePlayer.c:83: return;
	jp	00281$
00106$:
;SpritePlayer.c:86: if (KEY_RELEASED(J_SELECT)){
	bit	6, a
	jp	Z,00111$
	bit	6, c
	jp	NZ,00111$
;SpritePlayer.c:87: archer_data->amulet += 1u;
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
;SpritePlayer.c:88: archer_data->amulet %= 6u;
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
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:89: if(archer_data->amulet == 0u){
	ld	a, (bc)
	or	a, a
	jr	NZ,00111$
;SpritePlayer.c:90: archer_data->amulet = 1u;
	ld	a, #0x01
	ld	(bc), a
00111$:
;SpritePlayer.c:94: switch(archer_state) {
	ld	hl, #_archer_state
	ld	a, (hl)
	or	a, a
	jp	Z,00126$
	ld	hl, #_archer_state
	ld	a, (hl)
	dec	a
	jp	Z,00126$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	jp	Z,00161$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00180$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x06
	jp	NZ,00185$
;SpritePlayer.c:96: death_cooldown ++;
	ld	hl, #_death_cooldown
	inc	(hl)
;SpritePlayer.c:97: if(death_cooldown == 6){
	ld	a, (hl)
	sub	a, #0x06
	jr	NZ,00115$
;SpritePlayer.c:98: SetSpriteAnim(THIS, anim_dead, 12u);	
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
00115$:
;SpritePlayer.c:100: if (death_cooldown < 12){
	ld	hl, #_death_cooldown
	ld	a, (hl)
	sub	a, #0x0c
	jr	NC,00123$
;SpritePlayer.c:101: TranslateSprite(THIS, 0, -2 );
	ld	a, #0xfe
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
	jp	00281$
00123$:
;SpritePlayer.c:103: if (death_cooldown < 160){
	ld	hl, #_death_cooldown
	ld	a, (hl)
	sub	a, #0xa0
	jr	NC,00120$
;SpritePlayer.c:104: TranslateSprite(THIS, 0, 1);
	ld	a, #0x01
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
	jp	00281$
00120$:
;SpritePlayer.c:106: death_cooldown = 0;
	ld	hl, #_death_cooldown
	ld	(hl), #0x00
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:107: archer_data->ups -= 1;
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	dec	a
	ld	(bc), a
;SpritePlayer.c:108: archer_data->hp = 100;	
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
;SpritePlayer.c:109: if (archer_data->ups == -1){SetState(StateGameOver);}
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
	jr	NZ,00117$
	ld	a, #0x03
	push	af
	inc	sp
	call	_SetState
	inc	sp
	jp	00281$
00117$:
;SpritePlayer.c:110: else{SetState(StateGame);}	
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
;SpritePlayer.c:113: return;
	jp	00281$
;SpritePlayer.c:116: case STATE_NORMAL_PLATFORM:
00126$:
;SpritePlayer.c:117: MoveArcher();
	call	_MoveArcher
;SpritePlayer.c:118: CheckCollisionTile();
	call	_CheckCollisionTile
;SpritePlayer.c:119: if(shoot_cooldown) {
	ld	hl, #_shoot_cooldown
	ld	a, (hl)
	or	a, a
	jr	Z,00144$
;SpritePlayer.c:120: SetSpriteAnim(THIS, anim_shoot, 12u);
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
	jp	00145$
00144$:
;SpritePlayer.c:81: if(KEY_TICKED(J_START)){
	ld	hl, #_keys
	ld	a, (hl)
;SpritePlayer.c:122: if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
	bit	0, a
	jr	NZ,00130$
	bit	1, a
	jr	Z,00131$
00130$:
;SpritePlayer.c:123: SetSpriteAnim(THIS, anim_walk, 16u);
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
	jp	00132$
00131$:
;SpritePlayer.c:125: if (archer_state == STATE_NORMAL_PLATFORM){SetSpriteAnim(THIS, anim_flying, 16u);}
	ld	hl, #_archer_state
	ld	a, (hl)
	dec	a
	jr	NZ,00128$
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
	jr	00132$
00128$:
;SpritePlayer.c:126: else{SetSpriteAnim(THIS, anim_idle, 33u);}					
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
00132$:
;SpritePlayer.c:81: if(KEY_TICKED(J_START)){
	ld	hl, #_keys
	ld	a, (hl)
;SpritePlayer.c:128: if(KEY_PRESSED(J_UP)){
	and	a, #0x04
	ld	c, a
	ld	b, #0x00
	ld	a, b
	or	a, c
	jr	Z,00137$
;SpritePlayer.c:129: aimc += 1;
	ld	hl, #_aimc
	ld	a, (hl)
	inc	a
;SpritePlayer.c:130: if(aimc >= 16){
	ld	(hl),a
	sub	a, #0x10
	jr	C,00137$
;SpritePlayer.c:131: aimc=16;
	ld	(hl), #0x10
00137$:
;SpritePlayer.c:134: if(KEY_RELEASED(J_UP)){
	ld	hl, #_previous_keys
	ld	a, (hl)
	bit	2, a
	jr	Z,00145$
	ld	a, b
	or	a, c
	jr	NZ,00145$
;SpritePlayer.c:135: aimc = 0;
	ld	hl, #_aimc
	ld	(hl), #0x00
;SpritePlayer.c:140: return;
	jp	00281$
00145$:
;SpritePlayer.c:143: if (KEY_PRESSED(J_DOWN)){
	ld	hl, #_keys
	ld	a, (hl)
	bit	3, a
	jr	Z,00149$
;SpritePlayer.c:144: SetSpriteAnim(THIS, anim_shield, 8u);
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
;SpritePlayer.c:145: THIS->coll_x = 8;
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
	jr	00150$
00149$:
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:146: }else if (THIS->coll_x != 5){
	ld	hl, #0x000d
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	sub	a, #0x05
	jr	Z,00150$
;SpritePlayer.c:147: THIS->coll_x = 5;
	ld	a, #0x05
	ld	(bc), a
00150$:
;SpritePlayer.c:150: if(KEY_TICKED(J_A)) {
	ld	hl, #_keys
	ld	a, (hl)
	bit	4, a
	jr	Z,00152$
	ld	hl, #_previous_keys
	ld	a, (hl)
	bit	4, a
	jr	NZ,00152$
;SpritePlayer.c:151: Jump();
	call	_Jump
00152$:
;SpritePlayer.c:153: if(shoot_cooldown) {
	ld	hl, #_shoot_cooldown
	ld	a, (hl)
	or	a, a
	jr	Z,00157$
;SpritePlayer.c:154: shoot_cooldown -= 1u;
	dec	(hl)
	jp	00158$
00157$:
;SpritePlayer.c:156: if(KEY_TICKED(J_B) & (!KEY_PRESSED(J_DOWN) | (KEY_PRESSED(J_DOWN) & archer_state == STATE_JUMPING))) {
	ld	hl, #_keys
	ld	a, (hl)
	bit	5, a
	jr	Z,00283$
	ld	hl, #_previous_keys
	ld	c, (hl)
	xor	a, a
	bit	5, c
	jr	Z,00284$
00283$:
	ld	d, #0x00
	jr	00285$
00284$:
	ld	d, #0x01
00285$:
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
	jr	Z,00784$
	xor	a, a
00784$:
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
	jr	Z,00158$
;SpritePlayer.c:157: Shoot();
	call	_Shoot
00158$:
;SpritePlayer.c:161: if((archer_accel_y >> 3) > 1) {
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
	jr	Z,00785$
	bit	7, d
	jr	NZ,00786$
	cp	a, a
	jr	00786$
00785$:
	bit	7, d
	jr	Z,00786$
	scf
00786$:
	jp	NC, 00185$
;SpritePlayer.c:162: archer_state = STATE_JUMPING;
	ld	hl, #_archer_state
	ld	(hl), #0x02
;SpritePlayer.c:165: break;
	jp	00185$
;SpritePlayer.c:166: case STATE_JUMPING:
00161$:
;SpritePlayer.c:167: if(shoot_cooldown) {
	ld	hl, #_shoot_cooldown
	ld	a, (hl)
	or	a, a
	jr	Z,00178$
;SpritePlayer.c:168: shoot_cooldown -= 1u;
	dec	(hl)
	jp	00179$
00178$:
;SpritePlayer.c:81: if(KEY_TICKED(J_START)){
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#19
	ld	(hl), a
	pop	hl
	ld	hl, #_previous_keys
	ld	c, (hl)
;SpritePlayer.c:170: if(KEY_TICKED(J_B)) {
	ldhl	sp,	#17
	bit	5, (hl)
	jr	Z,00174$
	bit	5, c
	jr	NZ,00174$
;SpritePlayer.c:171: Shoot();
	call	_Shoot
	jp	00179$
00174$:
;SpritePlayer.c:173: if (archer_accel_y < 4){									
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
	jr	Z,00790$
	bit	7, d
	jr	NZ,00791$
	cp	a, a
	jr	00791$
00790$:
	bit	7, d
	jr	Z,00791$
	scf
00791$:
	jp	NC, 00171$
;SpritePlayer.c:176: jump_power += 1u;
	ld	hl, #_jump_power
	ld	b, (hl)
	inc	b
;SpritePlayer.c:174: if(KEY_PRESSED(J_A)) {
	ldhl	sp,	#17
	ld	a, (hl)
	and	a, #0x10
	ld	e, a
	ld	d, #0x00
	ld	a, d
	or	a, e
	jr	Z,00168$
;SpritePlayer.c:175: if (jump_power < 12u){
	ld	hl, #_jump_power
	ld	a, (hl)
	sub	a, #0x0c
	jr	NC,00169$
;SpritePlayer.c:176: jump_power += 1u;
	ld	(hl), b
;SpritePlayer.c:177: archer_accel_y -= 2;
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
	jr	00169$
00168$:
;SpritePlayer.c:179: }else if (KEY_RELEASED(J_A)){
	bit	4, c
	jr	Z,00169$
	ld	a, d
	or	a, e
	jr	NZ,00169$
;SpritePlayer.c:180: jump_power += 1u;
	ld	hl, #_jump_power
	ld	(hl), b
;SpritePlayer.c:181: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
00169$:
;SpritePlayer.c:183: SetSpriteAnim(THIS, anim_jump_up, 33u);
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
	jr	00179$
00171$:
;SpritePlayer.c:185: jump_power = 0u;
	ld	hl, #_jump_power
	ld	(hl), #0x00
;SpritePlayer.c:186: archer_accel_y += 1;
	ld	hl, #_archer_accel_y
	inc	(hl)
	jr	NZ,00793$
	inc	hl
	inc	(hl)
00793$:
;SpritePlayer.c:187: SetSpriteAnim(THIS, anim_jump, 32u);
	ld	a, #0x20
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
00179$:
;SpritePlayer.c:191: platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
;SpritePlayer.c:192: MoveArcher();
	call	_MoveArcher
;SpritePlayer.c:193: break;
	jr	00185$
;SpritePlayer.c:194: case STATE_HIT:
00180$:
;SpritePlayer.c:195: hit_cooldown -= 1;
	ld	hl, #_hit_cooldown
	ld	a, (hl)
	add	a, #0xff
	ld	(hl), a
;SpritePlayer.c:196: MoveArcher();
	call	_MoveArcher
;SpritePlayer.c:197: if (hit_cooldown == 0){
	ld	hl, #_hit_cooldown
	ld	a, (hl)
	or	a, a
	jr	NZ,00185$
;SpritePlayer.c:198: platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
;SpritePlayer.c:199: hit_cooldown = 24u;
	ld	hl, #_hit_cooldown
	ld	(hl), #0x18
;SpritePlayer.c:200: if(KEY_PRESSED(J_A)) {
	ld	hl, #_keys
	ld	a, (hl)
	bit	4, a
	jr	Z,00182$
;SpritePlayer.c:201: Jump();
	call	_Jump
00182$:
;SpritePlayer.c:203: archer_state = STATE_NORMAL;
	ld	hl, #_archer_state
	ld	(hl), #0x00
;SpritePlayer.c:206: }//end switch archer_state
00185$:
;SpritePlayer.c:209: if(princess_parent == 0 && archer_state != STATE_LADDER && archer_state != STATE_HIT && archer_state != STATE_DEAD) {
	ld	hl, #_princess_parent + 1
	ld	a, (hl-)
	or	a, (hl)
	jp	NZ, 00198$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x03
	jp	Z,00198$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00198$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x06
	jp	Z,00198$
;SpritePlayer.c:211: if(archer_accel_y < 24) {
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
	jr	Z,00798$
	bit	7, d
	jr	NZ,00799$
	cp	a, a
	jr	00799$
00798$:
	bit	7, d
	jr	Z,00799$
	scf
00799$:
	jr	NC,00187$
;SpritePlayer.c:212: archer_accel_y += 1;
	ld	hl, #_archer_accel_y
	inc	(hl)
	jr	NZ,00800$
	inc	hl
	inc	(hl)
00800$:
00187$:
;SpritePlayer.c:214: tile_collision = TranslateSprite(THIS, 0, archer_accel_y  >> 4 );
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
;SpritePlayer.c:215: if(!tile_collision && delta_time != 0 && archer_accel_y < 24) { //Do another iteration if there is no collision
	ld	a, (hl)
	or	a, a
	jp	NZ, 00189$
	ld	hl, #_delta_time
	ld	a, (hl)
	or	a, a
	jp	Z, 00189$
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
	jr	Z,00801$
	bit	7, d
	jr	NZ,00802$
	cp	a, a
	jr	00802$
00801$:
	bit	7, d
	jr	Z,00802$
	scf
00802$:
	jp	NC, 00189$
;SpritePlayer.c:216: archer_accel_y += 2;
	ld	hl, #_archer_accel_y
	ld	a, (hl)
	add	a, #0x02
	ld	(hl+), a
	ld	a, (hl)
	adc	a, #0x00
;SpritePlayer.c:217: tile_collision = TranslateSprite(THIS, 0, archer_accel_y >> 4);
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
00189$:
;SpritePlayer.c:219: if(tile_collision) {
	ld	hl, #_tile_collision
	ld	a, (hl)
	or	a, a
	jp	Z, 00198$
;SpritePlayer.c:220: if(archer_state == STATE_JUMPING & archer_accel_y > 0) {
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	ld	a, #0x01
	jr	Z,00804$
	xor	a, a
00804$:
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
	jr	Z,00805$
	bit	7, d
	jr	NZ,00806$
	cp	a, a
	jr	00806$
00805$:
	bit	7, d
	jr	Z,00806$
	scf
00806$:
	ld	a, #0x00
	rla
	and	a,c
	jr	Z,00193$
;SpritePlayer.c:221: archer_state = STATE_NORMAL;
	ld	hl, #_archer_state
	ld	(hl), #0x00
;SpritePlayer.c:222: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
	jr	00194$
00193$:
;SpritePlayer.c:225: archer_accel_y = 0;	
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
00194$:
;SpritePlayer.c:227: CheckCollisionTile();
	call	_CheckCollisionTile
00198$:
;SpritePlayer.c:230: if(princess_parent && archer_state == STATE_JUMPING) {
	ld	hl, #_princess_parent + 1
	ld	a, (hl-)
	or	a, (hl)
	jr	Z,00203$
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	jr	NZ,00203$
;SpritePlayer.c:231: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;SpritePlayer.c:232: archer_state = STATE_NORMAL;
	ld	hl, #_archer_state
	ld	(hl), #0x00
00203$:
;SpritePlayer.c:238: SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
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
00279$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#17
	ld	a, (hl)
	sub	a, c
	jp	Z,00281$
;SpritePlayer.c:239: if(ispr->type == SpriteItem) {
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
;SpritePlayer.c:241: struct ItemInfo* dataitem = (struct ItemInfo*)ispr->custom_data;
	pop	de
	push	de
	ld	hl, #0x0019
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:239: if(ispr->type == SpriteItem) {
	ld	a, c
	sub	a, #0x03
	jp	NZ,00220$
;SpritePlayer.c:240: if(CheckCollision(THIS, ispr)) {
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
	jp	Z, 00220$
;SpritePlayer.c:241: struct ItemInfo* dataitem = (struct ItemInfo*)ispr->custom_data;
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	e, (hl)
	inc	hl
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:242: if (dataitem->setup == 0u){ //se e' trasparente non faccio niente
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
	jp	NZ, 00220$
;SpritePlayer.c:243: switch(dataitem->type){
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, (bc)
	ld	c, a
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:245: archer_data->coins++;
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
;SpritePlayer.c:243: switch(dataitem->type){
	ld	a, c
	dec	a
	jr	Z,00205$
	ld	a,c
	cp	a,#0x02
	jp	Z,00208$
	cp	a,##0x03
	jp	Z,00209$
	cp	a,#0x07
	jp	Z,00210$
	sub	a, #0x0a
	jp	Z,00213$
	jp	00220$
;SpritePlayer.c:244: case 1u: //coins
00205$:
;SpritePlayer.c:245: archer_data->coins++;
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
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:245: archer_data->coins++;
	inc	bc
	ldhl	sp,	#15
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:246: if (archer_data->coins == 100){
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	sub	a, #0x64
	jr	NZ,00207$
;SpritePlayer.c:247: archer_data->coins = 0;
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x00
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:107: archer_data->ups -= 1;
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:248: archer_data->ups += 1;	
	ld	a, (bc)
	inc	a
	ld	(bc), a
00207$:
;SpritePlayer.c:250: PlayFx(CHANNEL_1, 3, 0x6d, 0x8c, 0x73, 0xff, 0xc7);
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
;SpritePlayer.c:251: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:252: break;
	jp	00220$
;SpritePlayer.c:253: case 2u: //hp
00208$:
;SpritePlayer.c:254: archer_data->hp = 100u;
	ldhl	sp,#(14 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x64
	ld	(bc), a
;SpritePlayer.c:255: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:256: break;
	jp	00220$
;SpritePlayer.c:257: case 3u: //up
00209$:
;SpritePlayer.c:107: archer_data->ups -= 1;
	ldhl	sp,#(14 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:258: archer_data->ups += 1;
	ld	a, (bc)
	inc	a
	ld	(bc), a
;SpritePlayer.c:259: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:260: break;
	jp	00220$
;SpritePlayer.c:261: case 7u: //dcoin
00210$:
;SpritePlayer.c:262: archer_data->coins+=10;
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
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:245: archer_data->coins++;
	inc	bc
	ld	a, (bc)
;SpritePlayer.c:263: if (archer_data->coins >= 100){
	cp	a, #0x64
	jr	C,00212$
;SpritePlayer.c:264: archer_data->coins = archer_data->coins - 100;
	add	a, #0x9c
	ld	(bc), a
;SpritePlayer.c:87: archer_data->amulet += 1u;
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:107: archer_data->ups -= 1;
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:265: archer_data->ups += 1;	
	ld	a, (bc)
	inc	a
	ld	(bc), a
00212$:
;SpritePlayer.c:267: PlayFx(CHANNEL_1, 3, 0x6d, 0x8c, 0x73, 0xff, 0xc7);
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
;SpritePlayer.c:268: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:269: break;
	jr	00220$
;SpritePlayer.c:270: case 10u: //scrigno
00213$:
;SpritePlayer.c:271: dataitem->collided = 1;
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;SpritePlayer.c:273: }
00220$:
;SpritePlayer.c:277: if(ispr->type == SpriteKey) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	sub	a, #0x04
	jp	NZ,00227$
;SpritePlayer.c:278: if(CheckCollision(THIS, ispr)) {
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
	jp	Z, 00227$
;SpritePlayer.c:279: struct ItemInfo* datakey = (struct ItemInfo*)ispr->custom_data;
	ldhl	sp,#(10 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:280: switch(datakey->type){
	inc	bc
	ld	a, (bc)
	ldhl	sp,	#16
	ld	(hl), a
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:282: archer_data->tool = 6;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:280: switch(datakey->type){
	ldhl	sp,	#16
	ld	a, (hl)
	dec	a
	jr	Z,00221$
	ldhl	sp,	#16
	ld	a, (hl)
	sub	a, #0x02
	jr	Z,00222$
	jr	00227$
;SpritePlayer.c:281: case 1: //wrench
00221$:
;SpritePlayer.c:282: archer_data->tool = 6;
	ld	a, #0x06
	ld	(bc), a
;SpritePlayer.c:283: SpriteManagerRemoveSprite(ispr);	
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:284: break;
	jr	00227$
;SpritePlayer.c:285: case 2: //key
00222$:
;SpritePlayer.c:286: archer_data->tool = 7;
	ld	a, #0x07
	ld	(bc), a
;SpritePlayer.c:287: SpriteManagerRemoveSprite(ispr);	
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:289: }
00227$:
;SpritePlayer.c:292: if(ispr->type == SpritePlatform) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
;SpritePlayer.c:300: THIS->y = ispr->y - ispr->coll_h;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:292: if(ispr->type == SpritePlatform) {
	ld	a, c
	sub	a, #0x02
	jp	NZ,00235$
;SpritePlayer.c:293: if(CheckCollision(THIS, ispr)) {
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
	jp	Z, 00235$
;SpritePlayer.c:294: if (archer_accel_y > 0){//se sono in salita non collido !
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
	jr	Z,00827$
	bit	7, d
	jr	NZ,00828$
	cp	a, a
	jr	00828$
00827$:
	bit	7, d
	jr	Z,00828$
	scf
00828$:
	jp	NC, 00235$
;SpritePlayer.c:295: archer_accel_y = 0;
	ld	hl, #_archer_accel_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;SpritePlayer.c:296: struct PlatformInfo* datap = (struct PlatformInfo*)ispr->custom_data;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:297: platform_vx = datap->vx;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	hl, #_platform_vx
	ld	(hl), a
;SpritePlayer.c:298: if(archer_state != STATE_NORMAL & archer_state != STATE_NORMAL_PLATFORM){
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
	jr	Z,00830$
	xor	a, a
00830$:
	xor	a, #0x01
	and	a, c
	bit	0, a
	jp	Z, 00235$
;SpritePlayer.c:299: archer_state = STATE_NORMAL_PLATFORM;
	ld	hl, #_archer_state
	ld	(hl), #0x01
;SpritePlayer.c:300: THIS->y = ispr->y - ispr->coll_h;
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
00235$:
;SpritePlayer.c:305: if(ispr->type == SpriteEnemy || ispr->type == SpriteScorpion || ispr->type == SpritePorcupine || ispr->type == SpriteWolf) { //collision con l' enemy
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	cp	a, #0x06
	jr	Z,00256$
	cp	a, #0x07
	jr	Z,00256$
	cp	a, #0x08
	jr	Z,00256$
	sub	a, #0x09
	jp	NZ,00257$
00256$:
;SpritePlayer.c:306: if(CheckCollision(THIS, ispr) & archer_state != STATE_HIT) {
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
	jr	Z,00837$
	xor	a, a
00837$:
	xor	a, #0x01
	and	a,e
	jp	Z, 00257$
;SpritePlayer.c:307: struct EnemyInfo* dataenemy = (struct EnemyInfo*)ispr->custom_data;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:308: if (dataenemy->enemy_state == ENEMY_STATE_DEAD){
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, (bc)
	sub	a, #0x03
	jp	Z,00281$
	jr	00237$
;SpritePlayer.c:309: return;
	jp	00281$
00237$:
;SpritePlayer.c:311: UINT8 being_hit = 1;
	ldhl	sp,	#10
	ld	(hl), #0x01
;SpritePlayer.c:312: if (KEY_PRESSED(J_DOWN) & ispr->type != SpriteWolf){ //se mi sto riparando e lo sono girato dove serve
	ld	hl, #_keys
	ld	c, (hl)
	ld	b, #0x00
	ld	a, c
	and	a, #0x08
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), #0x00
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	sub	a, #0x09
	ld	a, #0x01
	jr	Z,00841$
	xor	a, a
00841$:
	xor	a, #0x01
	ld	c, a
	ld	b, #0x00
;SpritePlayer.c:313: if (ispr->x < THIS->x){
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:312: if (KEY_PRESSED(J_DOWN) & ispr->type != SpriteWolf){ //se mi sto riparando e lo sono girato dove serve
	ldhl	sp,	#15
	ld	a, (hl)
	and	a, c
	ld	c, a
	inc	hl
	ld	a, (hl)
	and	a, b
	or	a, c
	jp	Z, 00246$
;SpritePlayer.c:313: if (ispr->x < THIS->x){
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
;SpritePlayer.c:145: THIS->coll_x = 8;
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:313: if (ispr->x < THIS->x){
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
;SpritePlayer.c:314: if (SPRITE_GET_VMIRROR(THIS)){//mi sto riparando bene	
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	and	a, #0x20
	ld	c, a
	ld	b, #0x00
;SpritePlayer.c:313: if (ispr->x < THIS->x){
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
	jr	NC,00243$
;SpritePlayer.c:314: if (SPRITE_GET_VMIRROR(THIS)){//mi sto riparando bene	
	ld	a, b
	or	a, c
	jp	Z, 00246$
;SpritePlayer.c:315: ispr->x -= 16;
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
;SpritePlayer.c:316: being_hit = 0;
	xor	a, a
	ldhl	sp,	#10
	ld	(hl), a
	jr	00246$
00243$:
;SpritePlayer.c:319: if (!SPRITE_GET_VMIRROR(THIS)){
	ld	a, b
	or	a, c
	jr	NZ,00246$
;SpritePlayer.c:320: ispr->x += 16;
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
;SpritePlayer.c:321: being_hit = 0;
	xor	a, a
	ldhl	sp,	#10
	ld	(hl), a
00246$:
;SpritePlayer.c:325: if (being_hit & archer_state != STATE_DEAD){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x06
	ld	a, #0x01
	jr	Z,00843$
	xor	a, a
00843$:
	xor	a, #0x01
	ldhl	sp,	#10
	ld	c, (hl)
	and	a,c
	jp	Z, 00257$
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:254: archer_data->hp = 100u;
	inc	bc
	inc	bc
	ldhl	sp,	#15
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:326: archer_data->hp -=  dataenemy->enemydamage;
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
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:254: archer_data->hp = 100u;
	inc	bc
	inc	bc
;SpritePlayer.c:327: if (archer_data->hp <= 0){
	ld	a, (bc)
	ldhl	sp,	#16
	ld	(hl),a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00844$
	bit	7, d
	jr	NZ,00845$
	cp	a, a
	jr	00845$
00844$:
	bit	7, d
	jr	Z,00845$
	scf
00845$:
	jr	C,00248$
;SpritePlayer.c:328: archer_data->hp = 0;
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:329: Die();
	call	_Die
00248$:
;SpritePlayer.c:331: Hit();
	call	_Hit
;SpritePlayer.c:332: if (ispr->x < THIS->x){
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
	jr	NC,00846$
	inc	c
00846$:
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
	jr	NC,00250$
;SpritePlayer.c:333: platform_vx = 1;
	ld	hl, #_platform_vx
	ld	(hl), #0x01
	jr	00257$
00250$:
;SpritePlayer.c:335: platform_vx = -1;
	ld	hl, #_platform_vx
	ld	(hl), #0xff
00257$:
;SpritePlayer.c:340: if(ispr->type == SpriteArrow) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	dec	a
	jp	NZ,00280$
;SpritePlayer.c:341: if(CheckCollision(THIS, ispr)) {
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
	jp	Z, 00280$
;SpritePlayer.c:342: struct ArrowInfo* arrowdata = (struct ArrowInfo*)ispr->custom_data;
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), e
;SpritePlayer.c:343: if (arrowdata->type == 6u){ //spine from porcupine
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	ld	a, (hl)
	and	a, #0x0f
	sub	a, #0x06
	jp	NZ,00266$
;SpritePlayer.c:344: if(!KEY_PRESSED(J_DOWN)){
	ld	hl, #_keys
	ld	a, (hl)
	bit	3, a
	jp	NZ,00264$
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:254: archer_data->hp = 100u;
	inc	bc
	inc	bc
	ldhl	sp,	#13
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:345: archer_data->hp -=  arrowdata->arrowdamage;
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
;SpritePlayer.c:87: archer_data->amulet += 1u;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:254: archer_data->hp = 100u;
	inc	bc
	inc	bc
;SpritePlayer.c:346: if (archer_data->hp <= 0){
	ld	a, (bc)
	ldhl	sp,	#17
	ld	(hl),a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00853$
	bit	7, d
	jr	NZ,00854$
	cp	a, a
	jr	00854$
00853$:
	bit	7, d
	jr	Z,00854$
	scf
00854$:
	jr	C,00262$
;SpritePlayer.c:347: archer_data->hp = 0;
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:348: Die();
	call	_Die
00262$:
;SpritePlayer.c:350: Hit();
	call	_Hit
00264$:
;SpritePlayer.c:352: SpriteManagerRemoveSprite(ispr);
	pop	hl
	push	hl
	push	hl
	call	_SpriteManagerRemoveSprite
	add	sp, #2
;SpritePlayer.c:353: return;
	jp	00281$
00266$:
;SpritePlayer.c:355: struct ArrowInfo* datap = (struct ArrowInfo*)ispr->custom_data;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#12
	ld	(hl), c
	inc	hl
	ld	(hl), b
;SpritePlayer.c:356: if (datap->arrowdir != 1){return;}//guardo solo se è orizzontale
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	dec	a
	jp	NZ,00281$
;SpritePlayer.c:357: if (archer_accel_y > 0 & THIS->y < (ispr->y-4)){//se sono in salita non collido !
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
	jr	Z,00856$
	bit	7, d
	jr	NZ,00857$
	cp	a, a
	jr	00857$
00856$:
	bit	7, d
	jr	Z,00857$
	scf
00857$:
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
	jr	NC,00858$
	inc	c
00858$:
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
	jp	Z, 00280$
;SpritePlayer.c:359: ispr->coll_x = 0;
	pop	de
	push	de
	ld	hl, #0x000d
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:360: ispr->coll_y = 2;
	pop	de
	push	de
	ld	hl, #0x000e
	add	hl, de
	ld	c,l
	ld	a,h
	ld	(hl), #0x02
;SpritePlayer.c:361: ispr->coll_w = 8;	
	pop	de
	push	de
	ld	hl, #0x000f
	add	hl, de
	ld	c,l
	ld	a,h
	ld	(hl), #0x08
;SpritePlayer.c:362: platform_vx = datap->vx;
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
;SpritePlayer.c:363: if(archer_state != STATE_NORMAL & archer_state != STATE_NORMAL_PLATFORM){
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
	jr	Z,00860$
	xor	a, a
00860$:
	xor	a, #0x01
	and	a, c
	bit	0, a
	jp	Z, 00280$
;SpritePlayer.c:364: archer_state = STATE_NORMAL_PLATFORM;
	ld	hl, #_archer_state
	ld	(hl), #0x01
;SpritePlayer.c:365: THIS->y = ispr->y - 12;
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
00280$:
;SpritePlayer.c:238: SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
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
	jp	00279$
00281$:
;SpritePlayer.c:372: }
	add	sp, #18
	ret
;SpritePlayer.c:374: void Die(){
;	---------------------------------
; Function Die
; ---------------------------------
_Die::
;SpritePlayer.c:375: archer_state = STATE_DEAD;
	ld	hl, #_archer_state
	ld	(hl), #0x06
;SpritePlayer.c:376: }
	ret
;SpritePlayer.c:378: void Shoot() {
;	---------------------------------
; Function Shoot
; ---------------------------------
_Shoot::
	add	sp, #-5
;SpritePlayer.c:379: SetSpriteAnim(THIS, anim_shoot, 16u);
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
;SpritePlayer.c:380: struct Sprite* arrow_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
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
;SpritePlayer.c:383: arrow_sprite->flags = THIS->flags;
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
;SpritePlayer.c:384: arrow_sprite->x = THIS->x;
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
;SpritePlayer.c:385: arrow_sprite->x += 4;
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
;SpritePlayer.c:386: arrow_sprite->y = THIS->y;
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
;SpritePlayer.c:387: struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_sprite->custom_data;
	pop	de
	push	de
	ld	hl, #0x0019
	add	hl, de
	ld	c, l
	ld	a, h
	ld	b, a
;SpritePlayer.c:388: if (archer_data->amulet){arrow_data->type = archer_data->amulet;}
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
;SpritePlayer.c:389: else{arrow_data->type = 1;}
	ld	e, c
	ld	d, b
	ld	a, (de)
	and	a, #0xf0
	or	a, #0x01
	ld	(de),a
00103$:
;SpritePlayer.c:390: if (KEY_PRESSED(J_DOWN)){
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#6
	ld	(hl), a
	pop	hl
;SpritePlayer.c:391: arrow_data->arrowdir = 4; // verticale in giu
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:390: if (KEY_PRESSED(J_DOWN)){
	ldhl	sp,	#4
	bit	3, (hl)
	jr	Z,00112$
;SpritePlayer.c:391: arrow_data->arrowdir = 4; // verticale in giu
	ld	a, #0x04
	ld	(bc), a
;SpritePlayer.c:392: arrow_sprite->y += 8;
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
;SpritePlayer.c:394: if (KEY_PRESSED(J_UP)){ //diagonale
	ldhl	sp,	#4
	bit	2, (hl)
	jr	Z,00107$
;SpritePlayer.c:395: arrow_data->arrowdir = 2;
	ld	a, #0x02
	ld	(bc), a
	jr	00108$
00107$:
;SpritePlayer.c:397: if(aimc < 16){ //orizzontale
	ld	hl, #_aimc
	ld	a, (hl)
	sub	a, #0x10
	jr	NC,00108$
;SpritePlayer.c:398: arrow_data->arrowdir = 1;
	ld	a, #0x01
	ld	(bc), a
00108$:
;SpritePlayer.c:401: if (aimc == 16){ // verticale in su
	ld	hl, #_aimc
	ld	a, (hl)
	sub	a, #0x10
	jr	NZ,00113$
;SpritePlayer.c:402: arrow_data->arrowdir = 3;
	ld	a, #0x03
	ld	(bc), a
;SpritePlayer.c:403: arrow_sprite->y -= 4;
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
;SpritePlayer.c:406: shoot_cooldown = 4;//8
	ld	hl, #_shoot_cooldown
	ld	(hl), #0x04
;SpritePlayer.c:407: aimc = 0;
	ld	hl, #_aimc
	ld	(hl), #0x00
;SpritePlayer.c:408: }
	add	sp, #5
	ret
;SpritePlayer.c:410: void Jump() {
;	---------------------------------
; Function Jump
; ---------------------------------
_Jump::
;SpritePlayer.c:411: if(archer_state != STATE_JUMPING) {
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x02
	ret	Z
;SpritePlayer.c:412: NR50_REG = 0x22; //Max volume		
	ld	a, #0x22
	ldh	(_NR50_REG+0),a
;SpritePlayer.c:414: archer_state = STATE_JUMPING;
	ld	hl, #_archer_state
	ld	(hl), #0x02
;SpritePlayer.c:415: archer_accel_y = -8;
	ld	hl, #_archer_accel_y
	ld	(hl), #0xf8
	inc	hl
	ld	(hl), #0xff
;SpritePlayer.c:416: princess_parent = 0;
	ld	hl, #_princess_parent
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;SpritePlayer.c:417: SetSpriteAnim(THIS, anim_jump_up, 12u);
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
;SpritePlayer.c:419: }
	ret
;SpritePlayer.c:421: void MoveArcher() {
;	---------------------------------
; Function MoveArcher
; ---------------------------------
_MoveArcher::
	add	sp, #-4
;SpritePlayer.c:423: if(KEY_PRESSED(J_LEFT)) {
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	pop	hl
;SpritePlayer.c:427: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;SpritePlayer.c:428: tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
	push	hl
	ld	hl, #_delta_time
	ld	a, (hl)
	ldhl	sp,	#3
	ld	(hl), a
	pop	hl
;SpritePlayer.c:427: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #0x000c
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
;SpritePlayer.c:423: if(KEY_PRESSED(J_LEFT)) {
	ldhl	sp,	#0
	bit	1, (hl)
	jp	Z,00111$
;SpritePlayer.c:424: if(KEY_PRESSED(J_DOWN)){
	ldhl	sp,	#0
	bit	3, (hl)
	jp	NZ,00105$
;SpritePlayer.c:427: if (SPRITE_GET_VMIRROR(THIS)){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	bit	5, a
	jr	Z,00105$
;SpritePlayer.c:428: tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
	ldhl	sp,	#1
	ld	a, (hl)
	push	af
	ld	b, #0xff
	pop	af
	inc	a
	jr	00145$
00144$:
	sla	b
00145$:
	dec	a
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
;SpritePlayer.c:427: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
;SpritePlayer.c:431: SPRITE_SET_VMIRROR(THIS);
	ld	a, (bc)
	set	5, a
	ld	(bc), a
	jp	00112$
00111$:
;SpritePlayer.c:433: else if(KEY_PRESSED(J_RIGHT)) {
	ldhl	sp,	#0
	bit	0, (hl)
	jp	Z,00112$
;SpritePlayer.c:434: if(!SPRITE_GET_VMIRROR(THIS) & !KEY_PRESSED(J_DOWN)){
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ld	a, c
	and	a, #0x20
	ld	c, a
	ld	b, #0x00
	ld	a, b
	or	a, c
	sub	a,#0x01
	ld	a, #0x00
	rla
	ld	c, a
	ld	hl, #_keys
	ld	b, (hl)
	ld	e, #0x00
	ld	a, b
	and	a, #0x08
	ld	b, a
	ld	e, #0x00
	ld	a, e
	or	a, b
	sub	a,#0x01
	ld	a, #0x00
	rla
	and	a, c
	bit	0, a
	jr	Z,00107$
;SpritePlayer.c:435: tile_collision = TranslateSprite(THIS, 1 << delta_time, 0);
	ldhl	sp,	#1
	ld	a, (hl)
	push	af
	ld	b, #0x01
	pop	af
	inc	a
	jr	00148$
00147$:
	sla	b
00148$:
	dec	a
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
;SpritePlayer.c:427: if (SPRITE_GET_VMIRROR(THIS)){
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x000c
	add	hl, bc
	ld	c, l
	ld	b, h
;SpritePlayer.c:437: SPRITE_UNSET_VMIRROR(THIS);
	ld	a, (bc)
	res	5, a
	ld	(bc), a
00112$:
;SpritePlayer.c:439: tile_collision = TranslateSprite(THIS, platform_vx << delta_time, 0);
	ld	hl, #_delta_time
	ld	c, (hl)
	ld	hl, #_platform_vx
	ld	b, (hl)
	inc	c
	jr	00150$
00149$:
	sla	b
00150$:
	dec	c
	jr	NZ,00149$
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
;SpritePlayer.c:440: }
	add	sp, #4
	ret
;SpritePlayer.c:442: void CheckCollisionTile() {
;	---------------------------------
; Function CheckCollisionTile
; ---------------------------------
_CheckCollisionTile::
	add	sp, #-2
;SpritePlayer.c:443: if(tile_collision){
	ld	hl, #_tile_collision
	ld	a, (hl)
	or	a, a
	jr	Z,00102$
;SpritePlayer.c:444: platform_vx = 0;
	ld	hl, #_platform_vx
	ld	(hl), #0x00
00102$:
;SpritePlayer.c:449: archer_data->hp -=  5;
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0002
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
;SpritePlayer.c:446: switch(tile_collision) {
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x02
	jp	Z,00103$
;SpritePlayer.c:458: if(archer_data->tool){
	inc	bc
	inc	bc
	inc	bc
	inc	bc
;SpritePlayer.c:446: switch(tile_collision) {
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x07
	jp	Z,00108$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x08
	jp	Z,00111$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x13
	jp	Z,00114$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x28
	jp	Z,00115$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x29
	jp	Z,00116$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x2a
	jp	Z,00117$
	ld	hl, #_tile_collision
	ld	a, (hl)
	sub	a, #0x2e
	jp	Z,00118$
	jp	00120$
;SpritePlayer.c:447: case 2u:
00103$:
;SpritePlayer.c:448: if (archer_state != STATE_HIT){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x04
	jp	Z,00120$
;SpritePlayer.c:449: archer_data->hp -=  5;
	pop	de
	push	de
	ld	a,(de)
	add	a, #0xfb
	ld	c, a
	pop	hl
	push	hl
	ld	(hl), c
	ld	hl, #_archer_data + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
;SpritePlayer.c:450: if (archer_data->hp <= 0){
	ld	a, (bc)
	ldhl	sp,	#1
	ld	(hl),a
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00196$
	bit	7, d
	jr	NZ,00197$
	cp	a, a
	jr	00197$
00196$:
	bit	7, d
	jr	Z,00197$
	scf
00197$:
	jr	C,00105$
;SpritePlayer.c:451: archer_data->hp = 0;
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:452: archer_state = STATE_DEAD;
	ld	hl, #_archer_state
	ld	(hl), #0x06
00105$:
;SpritePlayer.c:454: Hit();
	call	_Hit
;SpritePlayer.c:456: break;
	jp	00120$
;SpritePlayer.c:457: case 7u: //fine level - goto boss!
00108$:
;SpritePlayer.c:458: if(archer_data->tool){
	ld	a, (bc)
	or	a, a
	jr	Z,00120$
;SpritePlayer.c:459: archer_data->tool = 0; //tool consumato
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:460: load_next_b = 1;
	ld	hl, #_load_next_b
	ld	(hl), #0x01
;SpritePlayer.c:462: break;
	jr	00120$
;SpritePlayer.c:463: case 8u: //fine boss!
00111$:
;SpritePlayer.c:464: if(archer_data->tool){
	ld	a, (bc)
	or	a, a
	jr	Z,00120$
;SpritePlayer.c:465: archer_data->tool = 0; //tool consumato
	xor	a, a
	ld	(bc), a
;SpritePlayer.c:466: load_next_b = 2;
	ld	hl, #_load_next_b
	ld	(hl), #0x02
;SpritePlayer.c:468: break;
	jr	00120$
;SpritePlayer.c:469: case 19u: //exit secret room
00114$:
;SpritePlayer.c:470: load_next_s = -1;
	ld	hl, #_load_next_s
	ld	(hl), #0xff
;SpritePlayer.c:471: break;
	jr	00120$
;SpritePlayer.c:472: case 40u: //instant death
00115$:
;SpritePlayer.c:473: archer_data->hp = 0;
	pop	hl
	push	hl
	ld	(hl), #0x00
;SpritePlayer.c:474: Die();
	call	_Die
;SpritePlayer.c:475: break;
	jr	00120$
;SpritePlayer.c:476: case 41u: //next map
00116$:
;SpritePlayer.c:477: load_next = 1;
	ld	hl, #_load_next
	ld	(hl), #0x01
;SpritePlayer.c:478: break;
	jr	00120$
;SpritePlayer.c:479: case 42u: //previous map
00117$:
;SpritePlayer.c:480: load_next = -1;
	ld	hl, #_load_next
	ld	(hl), #0xff
;SpritePlayer.c:481: break;
	jr	00120$
;SpritePlayer.c:482: case 46u: //secret room
00118$:
;SpritePlayer.c:483: load_next_s = 1;
	ld	hl, #_load_next_s
	ld	(hl), #0x01
;SpritePlayer.c:489: }
00120$:
;SpritePlayer.c:490: }
	add	sp, #2
	ret
;SpritePlayer.c:492: void Hit() {
;	---------------------------------
; Function Hit
; ---------------------------------
_Hit::
	add	sp, #-2
;SpritePlayer.c:493: if (archer_state != STATE_DEAD){
	ld	hl, #_archer_state
	ld	a, (hl)
	sub	a, #0x06
	jp	Z,00103$
;SpritePlayer.c:494: archer_state = STATE_HIT;	
	ld	hl, #_archer_state
	ld	(hl), #0x04
;SpritePlayer.c:495: platform_vx = 1;
	ld	hl, #_platform_vx
	ld	(hl), #0x01
;SpritePlayer.c:496: THIS->y -= 6;
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
;SpritePlayer.c:497: SetSpriteAnim(THIS, anim_hit, 32u);
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
;SpritePlayer.c:498: NR50_REG = 0x55; //Max volume
	ld	a, #0x55
	ldh	(_NR50_REG+0),a
;SpritePlayer.c:499: PlayFx(CHANNEL_1, 2, 0x4c, 0x81, 0x43, 0x73, 0x86);
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
;SpritePlayer.c:501: }
	add	sp, #2
	ret
;SpritePlayer.c:504: void Destroy_SpritePlayer() {
;	---------------------------------
; Function Destroy_SpritePlayer
; ---------------------------------
_Destroy_SpritePlayer::
;SpritePlayer.c:506: }
	ret
	.area _CODE_2
	.area _CABS (ABS)
