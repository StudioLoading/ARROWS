;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module StateSecret
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Update_StateSecret
	.globl _populate_secret0
	.globl _Start_StateSecret
	.globl _WriteMap
	.globl _WriteUPS
	.globl _WriteHP
	.globl _WriteCOINS
	.globl _WriteAMULET
	.globl _SpriteManagerAdd
	.globl _SpriteManagerLoad
	.globl _ScrollFindTile
	.globl _GetMapSize
	.globl _InitWindow
	.globl _InitScroll
	.globl _ScrollSetTiles
	.globl _SetState
	.globl _empty
	.globl _bank_StateSecret
	.globl _secrets
	.globl _secret_1
	.globl _current_map_s
	.globl _current_level_s
	.globl _attack_wait
	.globl _damage_cooldown
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
_current_level_s::
	.ds 1
_current_map_s::
	.ds 1
_secret_1::
	.ds 2
_secrets::
	.ds 2
;--------------------------------------------------------
; CODE rom data
;--------------------------------------------------------
	.area _CODE
_bank_StateSecret:
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
;StateSecret.c:40: UINT8 current_level_s = 0;
	ld	hl, #_current_level_s
	ld	(hl), #0x00
;StateSecret.c:41: UINT8 current_map_s = 0;
	ld	hl, #_current_map_s
	ld	(hl), #0x00
;StateSecret.c:42: const struct MapInfo* secret_1[] = {
	ld	hl, #_secret_1
	ld	(hl), #<(_mapsecret0)
	inc	hl
	ld	(hl), #>(_mapsecret0)
;StateSecret.c:45: const struct MapInfo** secrets[] = {secret_1};
	ld	hl, #_secrets
	ld	(hl), #<(_secret_1)
	inc	hl
	ld	(hl), #>(_secret_1)
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
;StateSecret.c:50: void Start_StateSecret() {
;	---------------------------------
; Function Start_StateSecret
; ---------------------------------
_Start_StateSecret::
	add	sp, #-8
;StateSecret.c:55: SPRITES_8x16;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x04
	ldh	(_LCDC_REG+0),a
;StateSecret.c:57: for(i = 0; i != N_SPRITE_TYPES; ++ i) {
	ld	b, #0x00
00110$:
;StateSecret.c:58: SpriteManagerLoad(i);
	push	bc
	push	bc
	inc	sp
	call	_SpriteManagerLoad
	inc	sp
	pop	bc
;StateSecret.c:57: for(i = 0; i != N_SPRITE_TYPES; ++ i) {
	inc	b
	ld	a, b
	sub	a, #0x07
	jr	NZ,00110$
;StateSecret.c:60: SHOW_SPRITES;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x02
	ldh	(_LCDC_REG+0),a
;StateSecret.c:63: scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	ld	hl, #_scroll_bottom_movement_limit
	ld	(hl), #0x3c
;StateSecret.c:64: const struct MapInfo** level_maps_s = secrets[current_level_s];
	ld	hl, #_current_level_s
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_secrets
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
;StateSecret.c:66: GetMapSize(level_maps_s[current_map_s], &map_w, &map_h);
	ldhl	sp,	#3
	ld	c, l
	ld	b, h
	ldhl	sp,	#4
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ldhl	sp,	#2
	ld	c, l
	ld	b, h
	ldhl	sp,	#6
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	hl, #_current_map_s
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	pop	hl
	push	hl
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_GetMapSize
	add	sp, #6
;StateSecret.c:67: ScrollFindTile(level_maps_s[current_map_s], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	ld	hl, #_current_map_s
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	pop	hl
	push	hl
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_drop_player_y
	push	hl
	ld	hl, #_drop_player_x
	push	hl
	ldhl	sp,	#7
	ld	a, (hl)
	push	af
	inc	sp
	dec	hl
	ld	a, (hl)
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	ld	a, #0x09
	push	af
	inc	sp
	push	bc
	call	_ScrollFindTile
	add	sp, #11
;StateSecret.c:68: scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	ld	hl, #_drop_player_y
	ld	a, (hl)
	ld	e, a
	rla
	sbc	a, a
	ld	d, a
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	ld	hl, #_drop_player_x
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	push	de
	push	bc
	xor	a, a
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ld	hl, #_scroll_target
	ld	(hl), e
	inc	hl
	ld	(hl), d
;StateSecret.c:69: InitScroll(level_maps_s[current_map_s], collision_tiles, 0);
	ld	hl, #_current_map_s
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	pop	hl
	push	hl
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0000
	push	hl
	ld	hl, #_collision_tiles
	push	hl
	push	bc
	call	_InitScroll
	add	sp, #6
;StateSecret.c:70: SHOW_BKG;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x01
	ldh	(_LCDC_REG+0),a
;StateSecret.c:73: struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;
	ld	hl, #_scroll_target
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00159$
	inc	c
00159$:
	ldhl	sp,	#4
	ld	(hl), b
	inc	hl
	ld	(hl), c
;StateSecret.c:74: if (archer_data->ups > 0 & archer_data->ups != ups){
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	inc	hl
	ld	(hl), a
	ld	a, (hl)
	ld	e, a
	ld	a, #0x00
	ld	d, a
	xor	a, a
	sub	a, (hl)
	bit	7, e
	jr	Z,00160$
	bit	7, d
	jr	NZ,00161$
	cp	a, a
	jr	00161$
00160$:
	bit	7, d
	jr	Z,00161$
	scf
00161$:
	ld	a, #0x00
	rla
	ldhl	sp,	#7
	ld	(hl), a
	ld	hl, #_ups
	ld	a, (hl)
	ldhl	sp,	#6
	sub	a, (hl)
	ld	a, #0x01
	jr	Z,00163$
	xor	a, a
00163$:
	xor	a, #0x01
	ldhl	sp,	#7
	ld	e, (hl)
	and	a,e
	jr	Z,00103$
;StateSecret.c:75: ups = archer_data->ups;
	push	hl
	dec	hl
	ld	a, (hl)
	ld	hl, #_ups
	ld	(hl), a
	pop	hl
00103$:
;StateSecret.c:77: if (ups == -1){ //cioè vengo dal gameOver
	ld	hl, #_ups
	ld	a, (hl)
	inc	a
	jr	NZ,00105$
;StateSecret.c:78: ups = 3;
	ld	hl, #_ups
	ld	(hl), #0x03
;StateSecret.c:79: coins = 99u;
	ld	hl, #_coins
	ld	(hl), #0x63
00105$:
;StateSecret.c:81: archer_data->ups =ups;
	ld	hl, #_ups
	ld	a, (hl)
	ld	(bc), a
;StateSecret.c:82: archer_data->hp = hp;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	hl, #_hp
	ld	a, (hl)
	ld	(bc), a
;StateSecret.c:83: archer_data->coins = coins;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	hl, #_coins
	ld	a, (hl)
	ld	(bc), a
;StateSecret.c:87: INIT_FONT(font, PRINT_WIN);
	ld	hl, #_font
	push	hl
	ld	a, #0xcc
	push	af
	inc	sp
	call	_ScrollSetTiles
	add	sp, #3
	ld	hl, #_font_idx
	ld	(hl), #0xcc
	ld	hl, #_print_target
	ld	(hl), #0x01
;StateSecret.c:89: WX_REG = 7;
	ld	a, #0x07
	ldh	(_WX_REG+0),a
;StateSecret.c:90: WY_REG = 144 - 32;
	ld	a, #0x70
	ldh	(_WY_REG+0),a
;StateSecret.c:91: InitWindow(0, 0, &window);
	ld	hl, #_window
	push	hl
	xor	a, a
	push	af
	inc	sp
	xor	a, a
	push	af
	inc	sp
	call	_InitWindow
	add	sp, #4
;StateSecret.c:92: SHOW_WIN;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x20
	ldh	(_LCDC_REG+0),a
;StateSecret.c:93: WriteAMULET();
	call	_WriteAMULET
;StateSecret.c:94: WriteCOINS();
	call	_WriteCOINS
;StateSecret.c:95: WriteHP();
	call	_WriteHP
;StateSecret.c:96: WriteUPS();
	call	_WriteUPS
;StateSecret.c:97: WriteMap();
	call	_WriteMap
;StateSecret.c:99: switch(current_level_s){
	ld	hl, #_current_level_s
	ld	a, (hl)
	or	a, a
	jr	NZ,00109$
;StateSecret.c:101: switch(current_map_s){
	ld	hl, #_current_map_s
	ld	a, (hl)
	or	a, a
	jr	NZ,00109$
;StateSecret.c:103: populate_secret0();
	call	_populate_secret0
;StateSecret.c:107: }
00109$:
;StateSecret.c:110: NR52_REG = 0x80; //Enables sound, you should always setup this first
	ld	a, #0x80
	ldh	(_NR52_REG+0),a
;StateSecret.c:111: NR51_REG = 0xFF; //Enables all channels (left and right)
	ld	a, #0xff
	ldh	(_NR51_REG+0),a
;StateSecret.c:113: }
	add	sp, #8
	ret
;StateSecret.c:115: void populate_secret0(){
;	---------------------------------
; Function populate_secret0
; ---------------------------------
_populate_secret0::
	add	sp, #-22
;StateSecret.c:118: INT8 invitems_positions_x[] = {6,7,8};
	ldhl	sp,	#0
	ld	a, l
	ld	d, h
	ldhl	sp,	#9
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x06
	ldhl	sp,#(10 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x07
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x08
	ld	(bc), a
;StateSecret.c:119: INT8 invitems_positions_y[] = {14,14,14};
	ldhl	sp,	#3
	ld	a, l
	ld	d, h
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x0e
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x0e
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x0e
	ld	(bc), a
;StateSecret.c:120: INT8 iit [] = {7, 7, 7};
	ldhl	sp,	#6
	ld	a, l
	ld	d, h
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x07
	ldhl	sp,#(14 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x07
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x07
	ld	(bc), a
;StateSecret.c:121: for(invc=0; invc < invcount; invc++){
	xor	a, a
	ldhl	sp,	#21
	ld	(hl), a
00103$:
	ldhl	sp,	#21
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0x83
	jp	NC, 00105$
;StateSecret.c:122: struct Sprite* item_sprite = SpriteManagerAdd(SpriteItem, invitems_positions_x[invc]*8, invitems_positions_y[invc]*8);
	ld	a, (hl)
	ldhl	sp,	#15
	ld	(hl), a
	rla
	sbc	a, a
	inc	hl
	ld	(hl-), a
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	ldhl	sp,	#19
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ldhl	sp,#(16 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	ldhl	sp,	#19
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	ld	a, #0x03
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ld	c, e
	ld	b, d
;StateSecret.c:123: struct ItemInfo* dataitem = (struct ItemInfo*)item_sprite->custom_data;
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;StateSecret.c:124: dataitem->type = iit[invc];
	ld	hl, #0x0001
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#17
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#19
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#17
	push	af
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	pop	af
	ld	(hl), a
;StateSecret.c:125: dataitem->collided = 1u;
	ld	a, #0x01
	ld	(bc), a
;StateSecret.c:126: dataitem->setup = 1u;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x01
	ld	(bc), a
;StateSecret.c:121: for(invc=0; invc < invcount; invc++){
	ldhl	sp,	#21
	inc	(hl)
	jp	00103$
00105$:
;StateSecret.c:128: }
	add	sp, #22
	ret
;StateSecret.c:131: void Update_StateSecret() {
;	---------------------------------
; Function Update_StateSecret
; ---------------------------------
_Update_StateSecret::
	add	sp, #-2
;StateSecret.c:133: struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;
	ld	hl, #_scroll_target
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00151$
	inc	c
00151$:
	ldhl	sp,	#0
	ld	(hl), b
	inc	hl
	ld	(hl), c
;StateSecret.c:135: if (amulet != archer_data->amulet){
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	ld	hl, #_amulet
	ld	a, (hl)
	sub	a, c
	jr	Z,00102$
;StateSecret.c:136: amulet = archer_data->amulet;
	ld	hl, #_amulet
	ld	(hl), c
;StateSecret.c:137: WriteAMULET();		
	call	_WriteAMULET
00102$:
;StateSecret.c:139: if (coins != archer_data->coins){
	pop	bc
	push	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	hl, #_coins
	ld	a, (hl)
	sub	a, c
	jr	Z,00104$
;StateSecret.c:140: coins = archer_data->coins;
	ld	hl, #_coins
	ld	(hl), c
;StateSecret.c:141: WriteCOINS();
	call	_WriteCOINS
00104$:
;StateSecret.c:143: if (hp != archer_data->hp){
	pop	bc
	push	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	hl, #_hp
	ld	a, (hl)
	sub	a, c
	jr	Z,00106$
;StateSecret.c:144: hp = archer_data->hp;
	ld	hl, #_hp
	ld	(hl), c
;StateSecret.c:145: WriteHP();
	call	_WriteHP
00106$:
;StateSecret.c:147: if (ups != archer_data->ups){
	pop	bc
	push	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	hl, #_ups
	ld	a, (hl)
	sub	a, c
	jr	Z,00108$
;StateSecret.c:148: ups = archer_data->ups;
	ld	hl, #_ups
	ld	(hl), c
;StateSecret.c:149: WriteUPS();
	call	_WriteUPS
00108$:
;StateSecret.c:153: if(load_next_s){
	ld	hl, #_load_next_s
	ld	a, (hl)
	or	a, a
	jr	Z,00114$
;StateSecret.c:154: switch(load_next_s){
	ld	a, (hl)
	inc	a
	jr	Z,00110$
	ld	hl, #_load_next_s
	ld	a, (hl)
	dec	a
	jr	NZ,00114$
;StateSecret.c:156: current_map_s += load_next_s;
	ld	hl, #_current_map_s
	ld	a, (hl)
	ld	hl, #_load_next_s
	add	a, (hl)
	ld	hl, #_current_map_s
	ld	(hl), a
;StateSecret.c:157: WriteMap();
	call	_WriteMap
;StateSecret.c:158: load_next_s = 0;
	ld	hl, #_load_next_s
	ld	(hl), #0x00
;StateSecret.c:159: SetState(StateSecret);
	ld	a, #0x01
	push	af
	inc	sp
	call	_SetState
	inc	sp
;StateSecret.c:160: break;
	jr	00114$
;StateSecret.c:161: case -1: //torno dalla secret a game
00110$:
;StateSecret.c:163: SetState(StateGame);
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
;StateSecret.c:165: }
00114$:
;StateSecret.c:168: }
	add	sp, #2
	ret
	.area _CODE_2
	.area _CABS (ABS)
