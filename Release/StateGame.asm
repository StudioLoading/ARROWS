;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module StateGame
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Update_StateGame
	.globl _Start_StateGame
	.globl _Printf
	.globl _SpriteManagerAdd
	.globl _SpriteManagerLoad
	.globl _ScrollFindTile
	.globl _GetMapSize
	.globl _InitWindow
	.globl _InitScroll
	.globl _ScrollSetTiles
	.globl _SetState
	.globl _empty
	.globl _bank_StateGame
	.globl _drop_player_y
	.globl _drop_player_x
	.globl _levels
	.globl _level_1
	.globl _current_map
	.globl _current_level
	.globl _load_next_s
	.globl _load_next
	.globl _level_tool
	.globl _hp
	.globl _ups
	.globl _coins
	.globl _amulet
	.globl _collision_tiles
	.globl _sprites_palette
	.globl _bg_palette
	.globl _attack_wait
	.globl _damage_cooldown
	.globl _level_names
	.globl _populate_01
	.globl _populate_00
	.globl _WriteAMULET
	.globl _WriteMap
	.globl _WriteCOINS
	.globl _WriteHP
	.globl _WriteTOOL
	.globl _WriteUPS
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
_bg_palette::
	.ds 64
_sprites_palette::
	.ds 64
_collision_tiles::
	.ds 24
_amulet::
	.ds 1
_coins::
	.ds 1
_ups::
	.ds 1
_hp::
	.ds 1
_level_tool::
	.ds 1
_load_next::
	.ds 1
_load_next_s::
	.ds 1
_current_level::
	.ds 1
_current_map::
	.ds 1
_level_1::
	.ds 4
_levels::
	.ds 2
_drop_player_x::
	.ds 2
_drop_player_y::
	.ds 2
;--------------------------------------------------------
; CODE rom data
;--------------------------------------------------------
	.area _CODE
_bank_StateGame:
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
;StateGame.c:27: UINT16 bg_palette[] = {PALETTE_FROM_HEADER(tiles)};
	ld	hl, #_bg_palette
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x0002)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_bg_palette + 0x0004)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_bg_palette + 0x0006)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_bg_palette + 0x0008)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x000a)
	ld	(hl), #0x18
	inc	hl
	ld	(hl), #0x00
	ld	hl, #(_bg_palette + 0x000c)
	ld	(hl), #0x10
	inc	hl
	ld	(hl), #0x00
	ld	hl, #(_bg_palette + 0x000e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_bg_palette + 0x0010)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x0012)
	ld	(hl), #0xd6
	inc	hl
	ld	(hl), #0x5a
	ld	hl, #(_bg_palette + 0x0014)
	ld	(hl), #0xf7
	inc	hl
	ld	(hl), #0x00
	ld	hl, #(_bg_palette + 0x0016)
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
	ld	hl, #(_bg_palette + 0x0018)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x001a)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_bg_palette + 0x001c)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_bg_palette + 0x001e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_bg_palette + 0x0020)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x0022)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_bg_palette + 0x0024)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_bg_palette + 0x0026)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_bg_palette + 0x0028)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x002a)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_bg_palette + 0x002c)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_bg_palette + 0x002e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_bg_palette + 0x0030)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x0032)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_bg_palette + 0x0034)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_bg_palette + 0x0036)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_bg_palette + 0x0038)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_bg_palette + 0x003a)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_bg_palette + 0x003c)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_bg_palette + 0x003e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
;StateGame.c:29: UINT16 sprites_palette[] = {
	ld	hl, #_sprites_palette
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x0002)
	ld	(hl), #0x5e
	inc	hl
	ld	(hl), #0x4f
	ld	hl, #(_sprites_palette + 0x0004)
	ld	(hl), #0xb3
	inc	hl
	ld	(hl), #0x01
	ld	hl, #(_sprites_palette + 0x0006)
	ld	(hl), #0x03
	inc	hl
	ld	(hl), #0x7e
	ld	hl, #(_sprites_palette + 0x0008)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x000a)
	ld	(hl), #0x5e
	inc	hl
	ld	(hl), #0x4f
	ld	hl, #(_sprites_palette + 0x000c)
	ld	(hl), #0xb3
	inc	hl
	ld	(hl), #0x01
	ld	hl, #(_sprites_palette + 0x000e)
	ld	(hl), #0x03
	inc	hl
	ld	(hl), #0x7e
	ld	hl, #(_sprites_palette + 0x0010)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x0012)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_sprites_palette + 0x0014)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_sprites_palette + 0x0016)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_sprites_palette + 0x0018)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x001a)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_sprites_palette + 0x001c)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_sprites_palette + 0x001e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_sprites_palette + 0x0020)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x0022)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_sprites_palette + 0x0024)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_sprites_palette + 0x0026)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_sprites_palette + 0x0028)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x002a)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_sprites_palette + 0x002c)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_sprites_palette + 0x002e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_sprites_palette + 0x0030)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x0032)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_sprites_palette + 0x0034)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_sprites_palette + 0x0036)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
	ld	hl, #(_sprites_palette + 0x0038)
	ld	(hl), #0xbc
	inc	hl
	ld	(hl), #0x17
	ld	hl, #(_sprites_palette + 0x003a)
	ld	(hl), #0xe7
	inc	hl
	ld	(hl), #0x22
	ld	hl, #(_sprites_palette + 0x003c)
	ld	(hl), #0xc4
	inc	hl
	ld	(hl), #0x19
	ld	hl, #(_sprites_palette + 0x003e)
	ld	(hl), #0xe0
	inc	hl
	ld	(hl), #0x14
;StateGame.c:40: UINT8 collision_tiles[] = {1, 2, 3, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 40, 41, 42, 46, 0};//numero delle tile con collisioni e ultimo sempre zero
	ld	hl, #_collision_tiles
	ld	(hl), #0x01
	ld	hl, #(_collision_tiles + 0x0001)
	ld	(hl), #0x02
	ld	hl, #(_collision_tiles + 0x0002)
	ld	(hl), #0x03
	ld	hl, #(_collision_tiles + 0x0003)
	ld	(hl), #0x07
	ld	hl, #(_collision_tiles + 0x0004)
	ld	(hl), #0x09
	ld	hl, #(_collision_tiles + 0x0005)
	ld	(hl), #0x0a
	ld	hl, #(_collision_tiles + 0x0006)
	ld	(hl), #0x0b
	ld	hl, #(_collision_tiles + 0x0007)
	ld	(hl), #0x0c
	ld	hl, #(_collision_tiles + 0x0008)
	ld	(hl), #0x0d
	ld	hl, #(_collision_tiles + 0x0009)
	ld	(hl), #0x0e
	ld	hl, #(_collision_tiles + 0x000a)
	ld	(hl), #0x0f
	ld	hl, #(_collision_tiles + 0x000b)
	ld	(hl), #0x10
	ld	hl, #(_collision_tiles + 0x000c)
	ld	(hl), #0x11
	ld	hl, #(_collision_tiles + 0x000d)
	ld	(hl), #0x12
	ld	hl, #(_collision_tiles + 0x000e)
	ld	(hl), #0x13
	ld	hl, #(_collision_tiles + 0x000f)
	ld	(hl), #0x14
	ld	hl, #(_collision_tiles + 0x0010)
	ld	(hl), #0x15
	ld	hl, #(_collision_tiles + 0x0011)
	ld	(hl), #0x16
	ld	hl, #(_collision_tiles + 0x0012)
	ld	(hl), #0x17
	ld	hl, #(_collision_tiles + 0x0013)
	ld	(hl), #0x28
	ld	hl, #(_collision_tiles + 0x0014)
	ld	(hl), #0x29
	ld	hl, #(_collision_tiles + 0x0015)
	ld	(hl), #0x2a
	ld	hl, #(_collision_tiles + 0x0016)
	ld	(hl), #0x2e
	ld	hl, #(_collision_tiles + 0x0017)
	ld	(hl), #0x00
;StateGame.c:42: UINT8 amulet = 2u;
	ld	hl, #_amulet
	ld	(hl), #0x02
;StateGame.c:43: UINT8 coins = 99u;
	ld	hl, #_coins
	ld	(hl), #0x63
;StateGame.c:44: INT8 ups = 3;
	ld	hl, #_ups
	ld	(hl), #0x03
;StateGame.c:45: INT8 hp = 100;
	ld	hl, #_hp
	ld	(hl), #0x64
;StateGame.c:46: INT8 level_tool = -1;
	ld	hl, #_level_tool
	ld	(hl), #0xff
;StateGame.c:58: INT8 load_next = 0;
	ld	hl, #_load_next
	ld	(hl), #0x00
;StateGame.c:59: INT8 load_next_s = 0;
	ld	hl, #_load_next_s
	ld	(hl), #0x00
;StateGame.c:60: UINT8 current_level = 0;
	ld	hl, #_current_level
	ld	(hl), #0x00
;StateGame.c:61: UINT8 current_map = 0;
	ld	hl, #_current_map
	ld	(hl), #0x00
;StateGame.c:62: const struct MapInfo* level_1[] = {
	ld	hl, #_level_1
	ld	(hl), #<(_map)
	inc	hl
	ld	(hl), #>(_map)
	ld	hl, #(_level_1 + 0x0002)
	ld	(hl), #<(_map2)
	inc	hl
	ld	(hl), #>(_map2)
;StateGame.c:66: const struct MapInfo** levels[] = {level_1};
	ld	hl, #_levels
	ld	(hl), #<(_level_1)
	inc	hl
	ld	(hl), #>(_level_1)
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
;StateGame.c:76: void Start_StateGame() {
;	---------------------------------
; Function Start_StateGame
; ---------------------------------
_Start_StateGame::
	add	sp, #-8
;StateGame.c:81: SPRITES_8x16;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x04
	ldh	(_LCDC_REG+0),a
;StateGame.c:83: for(i = 0; i != N_SPRITE_TYPES; ++ i) {
	ld	b, #0x00
00118$:
;StateGame.c:84: SpriteManagerLoad(i);
	push	bc
	push	bc
	inc	sp
	call	_SpriteManagerLoad
	inc	sp
	pop	bc
;StateGame.c:83: for(i = 0; i != N_SPRITE_TYPES; ++ i) {
	inc	b
	ld	a, b
	sub	a, #0x07
	jr	NZ,00118$
;StateGame.c:86: SHOW_SPRITES;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x02
	ldh	(_LCDC_REG+0),a
;StateGame.c:89: scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	ld	hl, #_scroll_bottom_movement_limit
	ld	(hl), #0x3c
;StateGame.c:91: const struct MapInfo** lvls = levels[current_level];
	ld	hl, #_current_level
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_levels
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
;StateGame.c:93: GetMapSize(lvls[current_map], &map_w, &map_h);
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
	ld	hl, #_current_map
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
	ld	hl, #_current_map
	ld	c, (hl)
	ld	b, #0x00
;StateGame.c:96: ScrollFindTile(lvls[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	sla	c
	rl	b
	pop	hl
	push	hl
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
;StateGame.c:94: if (load_next_s){ //vengo da secret!
	ld	hl, #_load_next_s
	ld	a, (hl)
	or	a, a
	jp	Z, 00103$
;StateGame.c:95: load_next_s = 0;
	ld	(hl), #0x00
;StateGame.c:96: ScrollFindTile(lvls[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
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
	ld	a, #0x2d
	push	af
	inc	sp
	push	bc
	call	_ScrollFindTile
	add	sp, #11
	jp	00104$
00103$:
;StateGame.c:98: ScrollFindTile(lvls[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
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
00104$:
;StateGame.c:100: scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	ld	hl, #_drop_player_y + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	ld	hl, #_drop_player_x + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	push	bc
	push	de
	xor	a, a
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ld	hl, #_scroll_target
	ld	(hl), e
	inc	hl
	ld	(hl), d
;StateGame.c:101: InitScroll(lvls[current_map], collision_tiles, 0);
	ld	hl, #_current_map
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
;StateGame.c:102: SHOW_BKG;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x01
	ldh	(_LCDC_REG+0),a
;StateGame.c:105: struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;
	ld	hl, #_scroll_target
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00182$
	inc	c
00182$:
	ldhl	sp,	#4
	ld	(hl), b
	inc	hl
	ld	(hl), c
;StateGame.c:106: if (archer_data->ups > 0 & archer_data->ups != ups){
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
	jr	Z,00183$
	bit	7, d
	jr	NZ,00184$
	cp	a, a
	jr	00184$
00183$:
	bit	7, d
	jr	Z,00184$
	scf
00184$:
	ld	a, #0x00
	rla
	ldhl	sp,	#7
	ld	(hl), a
	ld	hl, #_ups
	ld	a, (hl)
	ldhl	sp,	#6
	sub	a, (hl)
	ld	a, #0x01
	jr	Z,00186$
	xor	a, a
00186$:
	xor	a, #0x01
	ldhl	sp,	#7
	ld	e, (hl)
	and	a,e
	jr	Z,00106$
;StateGame.c:107: ups = archer_data->ups;
	push	hl
	dec	hl
	ld	a, (hl)
	ld	hl, #_ups
	ld	(hl), a
	pop	hl
00106$:
;StateGame.c:109: if (ups == -1){ //cioè vengo dal gameOver
	ld	hl, #_ups
	ld	a, (hl)
	inc	a
	jr	NZ,00108$
;StateGame.c:110: ups = 3;
	ld	hl, #_ups
	ld	(hl), #0x03
;StateGame.c:111: coins = 99u;
	ld	hl, #_coins
	ld	(hl), #0x63
00108$:
;StateGame.c:113: archer_data->ups =ups;
	ld	hl, #_ups
	ld	a, (hl)
	ld	(bc), a
;StateGame.c:114: archer_data->hp = hp;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	hl, #_hp
	ld	a, (hl)
	ld	(bc), a
;StateGame.c:115: archer_data->coins = coins;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	hl, #_coins
	ld	a, (hl)
	ld	(bc), a
;StateGame.c:119: INIT_FONT(font, PRINT_WIN);
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
;StateGame.c:121: WX_REG = 7;
	ld	a, #0x07
	ldh	(_WX_REG+0),a
;StateGame.c:122: WY_REG = 144 - 32;
	ld	a, #0x70
	ldh	(_WY_REG+0),a
;StateGame.c:123: InitWindow(0, 0, &window);
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
;StateGame.c:124: SHOW_WIN;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x20
	ldh	(_LCDC_REG+0),a
;StateGame.c:125: WriteAMULET();
	call	_WriteAMULET
;StateGame.c:126: WriteCOINS();
	call	_WriteCOINS
;StateGame.c:127: WriteHP();
	call	_WriteHP
;StateGame.c:128: WriteUPS();
	call	_WriteUPS
;StateGame.c:129: WriteMap();
	call	_WriteMap
;StateGame.c:132: switch(current_level){
	ld	hl, #_current_level
	ld	a, (hl)
	or	a, a
	jp	NZ,00116$
;StateGame.c:134: switch(current_map){
	ld	hl, #_current_map
	ld	a, (hl)
	or	a, a
	jr	Z,00110$
	ld	hl, #_current_map
	ld	a, (hl)
	dec	a
	jp	Z,00113$
	jp	00114$
;StateGame.c:135: case 0:
00110$:
;StateGame.c:136: populate_00();
	call	_populate_00
;StateGame.c:137: level_tool = 6;
	ld	hl, #_level_tool
	ld	(hl), #0x06
;StateGame.c:139: if(archer_data->tool == 0){
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	or	a, a
	jp	NZ, 00117$
;StateGame.c:140: struct Sprite* wrench_sprite = SpriteManagerAdd(SpriteItem, 46*8, 2*8);
	ld	hl, #0x0010
	push	hl
	ld	hl, #0x0170
	push	hl
	ld	a, #0x03
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ld	c, e
	ld	b, d
;StateGame.c:141: struct ItemInfo* datawrench = (struct ItemInfo*)wrench_sprite->custom_data;
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;StateGame.c:142: datawrench->type = 6;
	ld	hl, #0x0001
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x06
;StateGame.c:143: datawrench->collided = 1;
	ld	a, #0x01
	ld	(bc), a
;StateGame.c:144: datawrench->setup = 1u;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x01
	ld	(bc), a
;StateGame.c:146: break;
	jr	00117$
;StateGame.c:147: case 1:
00113$:
;StateGame.c:148: populate_01();
	call	_populate_01
;StateGame.c:149: break;
	jr	00117$
;StateGame.c:150: default:
00114$:
;StateGame.c:151: current_map = 0;
	ld	hl, #_current_map
	ld	(hl), #0x00
;StateGame.c:152: populate_00();
	call	_populate_00
;StateGame.c:155: break;
	jr	00117$
;StateGame.c:156: default:
00116$:
;StateGame.c:157: current_level = 0;
	ld	hl, #_current_level
	ld	(hl), #0x00
;StateGame.c:158: current_map = 0;
	ld	hl, #_current_map
	ld	(hl), #0x00
;StateGame.c:159: populate_00();
	call	_populate_00
;StateGame.c:161: }
00117$:
;StateGame.c:164: NR52_REG = 0x80; //Enables sound, you should always setup this first
	ld	a, #0x80
	ldh	(_NR52_REG+0),a
;StateGame.c:165: NR51_REG = 0xFF; //Enables all channels (left and right)
	ld	a, #0xff
	ldh	(_NR51_REG+0),a
;StateGame.c:167: }
	add	sp, #8
	ret
_level_names:
	.dw __str_0
	.dw __str_1
__str_0:
	.ascii "THE ZOO"
	.db 0x00
__str_1:
	.ascii "THE SEWERS"
	.db 0x00
;StateGame.c:170: void populate_01(){
;	---------------------------------
; Function populate_01
; ---------------------------------
_populate_01::
	add	sp, #-18
;StateGame.c:173: UINT8 platform_positions_x[] = {9}; //10
	ldhl	sp,	#0
	ld	a, l
	ld	d, h
	ldhl	sp,	#11
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x09
;StateGame.c:174: UINT8 platform_positions_y[] = {21}; //30
	ldhl	sp,	#1
	ld	a, l
	ld	d, h
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x15
;StateGame.c:176: for(plc=0; plc < platform_count; plc++){
	xor	a, a
	ldhl	sp,	#17
	ld	(hl), a
00108$:
	ldhl	sp,	#17
	ld	a, (hl)
	sub	a, #0x01
	jp	NC, 00101$
;StateGame.c:177: struct Sprite* platform_sprite = SpriteManagerAdd(SpritePlatform, platform_positions_x[plc]*8, platform_positions_y[plc]*8);
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#17
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	c, a
	ld	b, #0x00
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#17
	ld	l, (hl)
	ld	h, #0x00
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
	ld	e, a
	ld	d, #0x00
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	push	bc
	push	de
	ld	a, #0x02
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ld	c, e
	ld	b, d
;StateGame.c:178: struct PlatformInfo* dataplatform = (struct PlatformInfo*)platform_sprite->custom_data;
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;StateGame.c:179: dataplatform->initx = platform_positions_x[plc]*8;	
	inc	bc
	inc	bc
	inc	bc
	ldhl	sp,#(16 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	add	a, a
	add	a, a
	add	a, a
	ld	(bc), a
;StateGame.c:176: for(plc=0; plc < platform_count; plc++){
	inc	hl
	inc	(hl)
	jp	00108$
00101$:
;StateGame.c:184: UINT8 e_positions_x[] = {32, 17};
	ldhl	sp,	#2
	ld	a, l
	ld	d, h
	ldhl	sp,	#8
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x20
	ldhl	sp,#(9 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x11
	ld	(bc), a
;StateGame.c:185: UINT8 e_positions_y[] = {9, 39};
	ldhl	sp,	#4
	ld	a, l
	ld	d, h
	ldhl	sp,	#10
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x09
	ldhl	sp,#(11 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x27
	ld	(bc), a
;StateGame.c:186: INT8 e_types[] = {1, 2}; //0=snake, 1=scorpion, 2=porcupine
	ldhl	sp,	#6
	ld	a, l
	ld	d, h
	ldhl	sp,	#12
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
	ldhl	sp,#(13 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x02
	ld	(bc), a
;StateGame.c:187: for(plc=0; plc < e_count; plc++){
	xor	a, a
	ldhl	sp,	#17
	ld	(hl), a
00111$:
	ldhl	sp,	#17
	ld	a, (hl)
	sub	a, #0x02
	jp	NC, 00113$
;StateGame.c:188: switch(e_types[plc]){
	ldhl	sp,#(13 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#17
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#14
	ld	(hl), a
;StateGame.c:189: case 1: SpriteManagerAdd(SpriteEnemy, e_positions_x[plc]*8, e_positions_y[plc]*8); break;
	ldhl	sp,#(11 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#17
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,#(9 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#17
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#15
	ld	(hl+), a
	ld	(hl), d
	ld	a, (bc)
	ld	c, a
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	b, #0x00
	ld	e, a
	ld	d, #0x00
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
;StateGame.c:188: switch(e_types[plc]){
	dec	hl
	dec	hl
	ld	a, (hl)
	dec	a
	jr	Z,00102$
	ldhl	sp,	#14
	ld	a, (hl)
	sub	a, #0x02
	jr	Z,00103$
	jr	00104$
;StateGame.c:189: case 1: SpriteManagerAdd(SpriteEnemy, e_positions_x[plc]*8, e_positions_y[plc]*8); break;
00102$:
	push	bc
	push	de
	ld	a, #0x04
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	jr	00112$
;StateGame.c:190: case 2: SpriteManagerAdd(SpritePorcupine, e_positions_x[plc]*8, e_positions_y[plc]*8); break;
00103$:
	push	bc
	push	de
	ld	a, #0x06
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	jr	00112$
;StateGame.c:191: default: SpriteManagerAdd(SpriteScorpion, e_positions_x[plc]*8, e_positions_y[plc]*8);
00104$:
	push	bc
	push	de
	ld	a, #0x05
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
;StateGame.c:192: }
00112$:
;StateGame.c:187: for(plc=0; plc < e_count; plc++){
	ldhl	sp,	#17
	inc	(hl)
	jp	00111$
00113$:
;StateGame.c:194: }
	add	sp, #18
	ret
;StateGame.c:196: void populate_00(){
;	---------------------------------
; Function populate_00
; ---------------------------------
_populate_00::
	add	sp, #-29
;StateGame.c:199: INT8 scrigni_positions_x[] = {7, 12, 9, 17};
	ldhl	sp,	#0
	ld	a, l
	ld	d, h
	ldhl	sp,	#18
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x07
	ldhl	sp,#(19 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x0c
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x09
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x11
	ld	(bc), a
;StateGame.c:200: INT8 scrigni_positions_y[] = {14, 23, 7, 36};
	ldhl	sp,	#4
	ld	a, l
	ld	d, h
	ldhl	sp,	#20
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x0e
	ldhl	sp,#(21 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x17
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x07
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x24
	ld	(bc), a
;StateGame.c:201: INT8 st [] = {1, 1, 1, 3};
	ldhl	sp,	#8
	ld	a, l
	ld	d, h
	ldhl	sp,	#22
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
	ldhl	sp,#(23 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x01
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x01
	ld	(bc), a
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x03
	ld	(bc), a
;StateGame.c:204: for(c=0; c < count; c++){
	xor	a, a
	ldhl	sp,	#28
	ld	(hl), a
00104$:
	ldhl	sp,	#28
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0x83
	jp	NC, 00101$
;StateGame.c:205: struct Sprite* scrigno_sprite = SpriteManagerAdd(SpriteItem, scrigni_positions_x[c]*8, scrigni_positions_y[c]*8);
	ld	a, (hl)
	ldhl	sp,	#24
	ld	(hl), a
	rla
	sbc	a, a
	inc	hl
	ld	(hl-), a
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#20
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
	ldhl	sp,	#26
	ld	(hl), c
	inc	hl
	ld	(hl), b
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#18
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
	ldhl	sp,	#26
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
;StateGame.c:206: struct ItemInfo* datascrigno = (struct ItemInfo*)scrigno_sprite->custom_data;
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;StateGame.c:207: datascrigno->type = 10;
	ld	hl, #0x0001
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#26
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x0a
;StateGame.c:208: datascrigno->setup = 1u;
	ld	hl, #0x0004
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#26
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x01
;StateGame.c:209: datascrigno->content_type = st[c]; 
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ldhl	sp,#(25 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#22
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#26
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	(bc), a
;StateGame.c:204: for(c=0; c < count; c++){
	inc	hl
	inc	(hl)
	jp	00104$
00101$:
;StateGame.c:215: INT8 invitems_positions_x[] = {31}; //13
	ldhl	sp,	#12
	ld	a, l
	ld	d, h
	ldhl	sp,	#16
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x1f
;StateGame.c:216: INT8 invitems_positions_y[] = {27};//11
	ldhl	sp,	#13
	ld	a, l
	ld	d, h
	ldhl	sp,	#18
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x1b
;StateGame.c:217: INT8 iit [] = {3, 1};
	ldhl	sp,	#14
	ld	a, l
	ld	d, h
	ldhl	sp,	#20
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), #0x03
	ldhl	sp,#(21 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	ld	a, #0x01
	ld	(bc), a
;StateGame.c:218: for(invc=0; invc < invcount; invc++){
	xor	a, a
	ldhl	sp,	#28
	ld	(hl), a
00107$:
	ldhl	sp,	#28
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0x81
	jp	NC, 00109$
;StateGame.c:219: struct Sprite* item_sprite = SpriteManagerAdd(SpriteItem, invitems_positions_x[invc]*8, invitems_positions_y[invc]*8);
	ld	a, (hl)
	ldhl	sp,	#22
	ld	(hl), a
	rla
	sbc	a, a
	inc	hl
	ld	(hl-), a
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#18
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
	ldhl	sp,	#26
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ldhl	sp,#(23 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#16
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
	ldhl	sp,	#26
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
;StateGame.c:220: struct ItemInfo* dataitem = (struct ItemInfo*)item_sprite->custom_data;
	ld	hl, #0x0019
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
;StateGame.c:221: dataitem->type = iit[invc];
	ld	hl, #0x0001
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#24
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#20
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#26
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#24
	push	af
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	pop	af
	ld	(hl), a
;StateGame.c:222: dataitem->setup = 1u;
	inc	bc
	inc	bc
	inc	bc
	inc	bc
	ld	a, #0x01
	ld	(bc), a
;StateGame.c:218: for(invc=0; invc < invcount; invc++){
	ldhl	sp,	#28
	inc	(hl)
	jp	00107$
00109$:
;StateGame.c:226: }
	add	sp, #29
	ret
;StateGame.c:228: void Update_StateGame() {
;	---------------------------------
; Function Update_StateGame
; ---------------------------------
_Update_StateGame::
	add	sp, #-2
;StateGame.c:230: struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;
	ld	hl, #_scroll_target
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x19
	ld	b, a
	jr	NC,00178$
	inc	c
00178$:
	ldhl	sp,	#0
	ld	(hl), b
	inc	hl
	ld	(hl), c
;StateGame.c:232: if (amulet != archer_data->amulet){
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	ld	hl, #_amulet
	ld	a, (hl)
	sub	a, c
	jr	Z,00102$
;StateGame.c:233: amulet = archer_data->amulet;
	ld	hl, #_amulet
	ld	(hl), c
;StateGame.c:234: WriteAMULET();		
	call	_WriteAMULET
00102$:
;StateGame.c:236: if (coins != archer_data->coins){
	pop	bc
	push	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	hl, #_coins
	ld	a, (hl)
	sub	a, c
	jr	Z,00104$
;StateGame.c:237: coins = archer_data->coins;
	ld	hl, #_coins
	ld	(hl), c
;StateGame.c:238: WriteCOINS();
	call	_WriteCOINS
00104$:
;StateGame.c:240: if (hp != archer_data->hp){
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
;StateGame.c:241: hp = archer_data->hp;
	ld	hl, #_hp
	ld	(hl), c
;StateGame.c:242: WriteHP();
	call	_WriteHP
00106$:
;StateGame.c:244: if (ups != archer_data->ups){
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
;StateGame.c:245: ups = archer_data->ups;
	ld	hl, #_ups
	ld	(hl), c
;StateGame.c:246: WriteUPS();
	call	_WriteUPS
00108$:
;StateGame.c:248: if(archer_data->tool == level_tool){
	pop	de
	push	de
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ld	e, a
	ld	hl, #_level_tool
	ld	a, (hl)
	sub	a, e
	jr	NZ,00110$
;StateGame.c:249: WriteTOOL();
	push	bc
	call	_WriteTOOL
	pop	bc
;StateGame.c:250: level_tool = -1; //TODO non sono sicurissimo
	ld	hl, #_level_tool
	ld	(hl), #0xff
00110$:
;StateGame.c:253: if(load_next) {
	ld	hl, #_load_next
	ld	a, (hl)
	or	a, a
	jp	Z, 00118$
;StateGame.c:254: switch(load_next){
	ld	a, (hl)
	inc	a
	jr	Z,00112$
	ld	hl, #_load_next
	ld	a, (hl)
	dec	a
	jr	Z,00112$
	ld	hl, #_load_next
	ld	a, (hl)
	sub	a, #0x0a
	jr	Z,00113$
	jr	00116$
;StateGame.c:256: case -1:
00112$:
;StateGame.c:257: current_map += load_next;
	ld	hl, #_current_map
	ld	a, (hl)
	ld	hl, #_load_next
	add	a, (hl)
	ld	hl, #_current_map
	ld	(hl), a
;StateGame.c:258: break;
	jr	00116$
;StateGame.c:259: case 10: //level
00113$:
;StateGame.c:260: if (archer_data->tool == level_tool){
	ld	a, (bc)
	ld	c, a
	ld	hl, #_level_tool
	ld	a, (hl)
	sub	a, c
	jr	NZ,00116$
;StateGame.c:261: current_level++;
	ld	hl, #_current_level
	inc	(hl)
;StateGame.c:262: current_map = 0;
	ld	hl, #_current_map
	ld	(hl), #0x00
;StateGame.c:267: }
00116$:
;StateGame.c:269: load_next = 0;
	ld	hl, #_load_next
	ld	(hl), #0x00
;StateGame.c:270: SetState(StateGame);
	xor	a, a
	push	af
	inc	sp
	call	_SetState
	inc	sp
00118$:
;StateGame.c:273: if(load_next_s){
	ld	hl, #_load_next_s
	ld	a, (hl)
	or	a, a
	jr	Z,00121$
;StateGame.c:274: load_next_s = 0;
	ld	(hl), #0x00
;StateGame.c:275: SetState(StateSecret);
	ld	a, #0x01
	push	af
	inc	sp
	call	_SetState
	inc	sp
00121$:
;StateGame.c:278: }
	add	sp, #2
	ret
;StateGame.c:280: void WriteAMULET(){
;	---------------------------------
; Function WriteAMULET
; ---------------------------------
_WriteAMULET::
;StateGame.c:281: PRINT_POS(13,1);
	ld	hl, #_print_x
	ld	(hl), #0x0d
	ld	hl, #_print_y
	ld	(hl), #0x01
;StateGame.c:282: switch (amulet){
	ld	hl, #_amulet
	ld	a, (hl)
	dec	a
	jr	Z,00101$
	ld	hl, #_amulet
	ld	a, (hl)
	sub	a, #0x02
	jr	Z,00102$
	ld	hl, #_amulet
	ld	a, (hl)
	sub	a, #0x03
	jr	Z,00103$
	ld	hl, #_amulet
	ld	a, (hl)
	sub	a, #0x04
	jr	Z,00104$
	ld	hl, #_amulet
	ld	a, (hl)
	sub	a, #0x05
	jr	Z,00105$
	jr	00106$
;StateGame.c:283: case 1: Printf("$"); break;
00101$:
	ld	hl, #___str_2
	push	hl
	call	_Printf
	add	sp, #2
	ret
;StateGame.c:284: case 2: Printf("]"); break;
00102$:
	ld	hl, #___str_3
	push	hl
	call	_Printf
	add	sp, #2
	ret
;StateGame.c:285: case 3: Printf("["); break;
00103$:
	ld	hl, #___str_4
	push	hl
	call	_Printf
	add	sp, #2
	ret
;StateGame.c:286: case 4: Printf("#"); break;
00104$:
	ld	hl, #___str_5
	push	hl
	call	_Printf
	add	sp, #2
	ret
;StateGame.c:287: case 5: Printf("@"); break;
00105$:
	ld	hl, #___str_6
	push	hl
	call	_Printf
	add	sp, #2
	ret
;StateGame.c:288: default: Printf("$"); break;
00106$:
	ld	hl, #___str_2
	push	hl
	call	_Printf
	add	sp, #2
;StateGame.c:289: }	
;StateGame.c:290: }
	ret
___str_2:
	.ascii "$"
	.db 0x00
___str_3:
	.ascii "]"
	.db 0x00
___str_4:
	.ascii "["
	.db 0x00
___str_5:
	.ascii "#"
	.db 0x00
___str_6:
	.ascii "@"
	.db 0x00
;StateGame.c:292: void WriteMap(){
;	---------------------------------
; Function WriteMap
; ---------------------------------
_WriteMap::
;StateGame.c:293: PRINT_POS(1, 3);
	ld	hl, #_print_x
	ld	(hl), #0x01
	ld	hl, #_print_y
	ld	(hl), #0x03
;StateGame.c:294: Printf(level_names[current_level]);	
	ld	hl, #_current_level
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_level_names
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	call	_Printf
	add	sp, #2
;StateGame.c:295: }
	ret
;StateGame.c:297: void WriteCOINS(){
;	---------------------------------
; Function WriteCOINS
; ---------------------------------
_WriteCOINS::
;StateGame.c:298: PRINT_POS(17, 1);
	ld	hl, #_print_x
	ld	(hl), #0x11
	ld	hl, #_print_y
	ld	(hl), #0x01
;StateGame.c:300: Printf("%d", coins);
	ld	hl, #_coins
	ld	c, (hl)
	ld	b, #0x00
;StateGame.c:299: if (coins > 9u){
	ld	a, #0x09
	sub	a, (hl)
	jr	NC,00102$
;StateGame.c:300: Printf("%d", coins);
	push	bc
	ld	hl, #___str_7
	push	hl
	call	_Printf
	add	sp, #4
	ret
00102$:
;StateGame.c:302: Printf("0%d", coins);
	push	bc
	ld	hl, #___str_8
	push	hl
	call	_Printf
	add	sp, #4
;StateGame.c:304: }
	ret
___str_7:
	.ascii "%d"
	.db 0x00
___str_8:
	.ascii "0%d"
	.db 0x00
;StateGame.c:306: void WriteHP(){	
;	---------------------------------
; Function WriteHP
; ---------------------------------
_WriteHP::
;StateGame.c:307: PRINT_POS(7, 1);
	ld	hl, #_print_x
	ld	(hl), #0x07
	ld	hl, #_print_y
	ld	(hl), #0x01
;StateGame.c:308: if (hp < 10){
	ld	hl, #_hp
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0x8a
	jr	NC,00102$
;StateGame.c:309: Printf("00%d", hp);
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	push	bc
	ld	hl, #___str_9
	push	hl
	call	_Printf
	add	sp, #4
00102$:
;StateGame.c:311: if (hp > 9 & hp < 100){
	ld	hl, #_hp
	ld	a, (hl)
	ld	e, a
	ld	a, #0x09
	ld	d, a
	ld	a, #0x09
	sub	a, (hl)
	bit	7, e
	jr	Z,00124$
	bit	7, d
	jr	NZ,00125$
	cp	a, a
	jr	00125$
00124$:
	bit	7, d
	jr	Z,00125$
	scf
00125$:
	ld	a, #0x00
	rla
	ld	c, a
	ld	hl, #_hp
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0xe4
	ld	a, #0x00
	rla
	and	a,c
	jr	Z,00104$
;StateGame.c:312: Printf("0%d", hp);
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	push	bc
	ld	hl, #___str_10
	push	hl
	call	_Printf
	add	sp, #4
00104$:
;StateGame.c:314: if (hp >= 100){
	ld	hl, #_hp
	ld	a, (hl)
	xor	a, #0x80
	sub	a, #0xe4
	ret	C
;StateGame.c:315: Printf("%d", hp);	
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	push	bc
	ld	hl, #___str_11
	push	hl
	call	_Printf
	add	sp, #4
;StateGame.c:317: }
	ret
___str_9:
	.ascii "00%d"
	.db 0x00
___str_10:
	.ascii "0%d"
	.db 0x00
___str_11:
	.ascii "%d"
	.db 0x00
;StateGame.c:319: void WriteTOOL(){
;	---------------------------------
; Function WriteTOOL
; ---------------------------------
_WriteTOOL::
;StateGame.c:320: switch(level_tool){
	ld	hl, #_level_tool
	ld	a, (hl)
	sub	a, #0x06
	ret	NZ
;StateGame.c:322: PRINT_POS(11, 1);
	ld	hl, #_print_x
	ld	(hl), #0x0b
	ld	hl, #_print_y
	ld	(hl), #0x01
;StateGame.c:323: Printf("<", level_tool);
	ld	hl, #_level_tool
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	push	bc
	ld	hl, #___str_12
	push	hl
	call	_Printf
	add	sp, #4
;StateGame.c:325: }
;StateGame.c:326: }
	ret
___str_12:
	.ascii "<"
	.db 0x00
;StateGame.c:328: void WriteUPS(){
;	---------------------------------
; Function WriteUPS
; ---------------------------------
_WriteUPS::
;StateGame.c:329: PRINT_POS(2, 1); //up
	ld	hl, #_print_x
	ld	(hl), #0x02
	ld	hl, #_print_y
	ld	(hl), #0x01
;StateGame.c:330: if (ups > 9){Printf("%d", ups);}
	ld	hl, #_ups
	ld	a, (hl)
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ld	a, (hl)
	ld	e, a
	ld	a, #0x09
	ld	d, a
	ld	a, #0x09
	sub	a, (hl)
	bit	7, e
	jr	Z,00111$
	bit	7, d
	jr	NZ,00112$
	cp	a, a
	jr	00112$
00111$:
	bit	7, d
	jr	Z,00112$
	scf
00112$:
	jr	NC,00102$
	push	bc
	ld	hl, #___str_13
	push	hl
	call	_Printf
	add	sp, #4
	ret
00102$:
;StateGame.c:331: else{Printf("0%d", ups);}
	push	bc
	ld	hl, #___str_14
	push	hl
	call	_Printf
	add	sp, #4
;StateGame.c:332: }
	ret
___str_13:
	.ascii "%d"
	.db 0x00
___str_14:
	.ascii "0%d"
	.db 0x00
	.area _CODE_2
	.area _CABS (ABS)
