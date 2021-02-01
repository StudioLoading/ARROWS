;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Scroll
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _ScrollUpdateColumnWithDelay
	.globl _ScrollUpdateColumnR
	.globl _ScrollUpdateRowWithDelay
	.globl _ScrollUpdateRowR
	.globl _ClampScrollLimits
	.globl _UPDATE_TILE
	.globl _SetTile
	.globl _GetTileReplacement
	.globl _PopBank
	.globl _PushBank
	.globl _SpriteManagerAdd
	.globl _set_win_tiles
	.globl _set_bkg_data
	.globl _clamp_enabled
	.globl _scroll_h_border
	.globl _current_vbl_count
	.globl _pending_w_i
	.globl _pending_w_y
	.globl _pending_w_x
	.globl _pending_w_map
	.globl _pending_h_map
	.globl _pending_h_i
	.globl _pending_h_y
	.globl _pending_h_x
	.globl _scroll_offset_y
	.globl _scroll_offset_x
	.globl _scroll_bank
	.globl _scroll_tile_info
	.globl _scroll_collisions_down
	.globl _scroll_collisions
	.globl _scroll_target_offset_y
	.globl _scroll_target_offset_x
	.globl _scroll_target
	.globl _scroll_tiles_h
	.globl _scroll_tiles_w
	.globl _scroll_h
	.globl _scroll_w
	.globl _scroll_y
	.globl _scroll_x
	.globl _scroll_cmap
	.globl _scroll_map
	.globl _scroll_bottom_movement_limit
	.globl _scroll_top_movement_limit
	.globl _ScrollSetTiles
	.globl _InitWindow
	.globl _ScrollSetMap
	.globl _InitScroll
	.globl _InitScrollWithTiles
	.globl _ScrollUpdateRow
	.globl _ScrollUpdateColumn
	.globl _RefreshScroll
	.globl _MoveScroll
	.globl _GetScrollTilePtr
	.globl _GetScrollTile
	.globl _GetMapSize
	.globl _ScrollFindTile
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_scroll_top_movement_limit::
	.ds 1
_scroll_bottom_movement_limit::
	.ds 1
_scroll_map::
	.ds 2
_scroll_cmap::
	.ds 2
_scroll_x::
	.ds 2
_scroll_y::
	.ds 2
_scroll_w::
	.ds 2
_scroll_h::
	.ds 2
_scroll_tiles_w::
	.ds 2
_scroll_tiles_h::
	.ds 2
_scroll_target::
	.ds 2
_scroll_target_offset_x::
	.ds 2
_scroll_target_offset_y::
	.ds 2
_scroll_collisions::
	.ds 128
_scroll_collisions_down::
	.ds 128
_scroll_tile_info::
	.ds 256
_scroll_bank::
	.ds 1
_scroll_offset_x::
	.ds 1
_scroll_offset_y::
	.ds 1
_pending_h_x::
	.ds 2
_pending_h_y::
	.ds 2
_pending_h_i::
	.ds 1
_pending_h_map::
	.ds 2
_pending_w_map::
	.ds 2
_pending_w_x::
	.ds 2
_pending_w_y::
	.ds 2
_pending_w_i::
	.ds 1
_current_vbl_count::
	.ds 1
_scroll_h_border::
	.ds 1
_clamp_enabled::
	.ds 1
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
;C:/GB/ZGB/common/src/Scroll.c:19: extern UINT8 scroll_top_movement_limit = 30;
	ld	hl, #_scroll_top_movement_limit
	ld	(hl), #0x1e
;C:/GB/ZGB/common/src/Scroll.c:20: extern UINT8 scroll_bottom_movement_limit = 100;
	ld	hl, #_scroll_bottom_movement_limit
	ld	(hl), #0x64
;C:/GB/ZGB/common/src/Scroll.c:25: unsigned char* scroll_map = 0;
	ld	hl, #_scroll_map
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:26: unsigned char* scroll_cmap = 0;
	ld	hl, #_scroll_cmap
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:33: struct Sprite* scroll_target = 0;
	ld	hl, #_scroll_target
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:34: INT16 scroll_target_offset_x = 0;
	ld	hl, #_scroll_target_offset_x
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:35: INT16 scroll_target_offset_y = 0;
	ld	hl, #_scroll_target_offset_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:40: UINT8 scroll_offset_x = 0;
	ld	hl, #_scroll_offset_x
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:41: UINT8 scroll_offset_y = 0;
	ld	hl, #_scroll_offset_y
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:45: unsigned char* pending_h_map = 0;
	ld	hl, #_pending_h_map
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:46: unsigned char* pending_w_map = 0;
	ld	hl, #_pending_w_map
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:179: INT8 scroll_h_border = 0;
	ld	hl, #_scroll_h_border
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:180: UINT8 clamp_enabled = 1;
	ld	hl, #_clamp_enabled
	ld	(hl), #0x01
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;C:/GB/ZGB/common/src/Scroll.c:56: void SetTile(UINT16 r, UINT8 t) {
;	---------------------------------
; Function SetTile
; ---------------------------------
_SetTile::
;C:/GB/ZGB/common/src/Scroll.c:78: __endasm;
;bc	= r, hl = t
	ldhl	sp,#2
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ldhl	sp,#4
;while	0xff41 & 02 != 0 (cannot write)
	1$:
	ld	a,(#_STAT_REG)
	and	a, #0x02
	jr	NZ,1$
;Write	tile
	ld	a,(hl)
	ld	(bc),a
	ret
;C:/GB/ZGB/common/src/Scroll.c:79: }
	ret
;C:/GB/ZGB/common/src/Scroll.c:81: void UPDATE_TILE(INT16 x, INT16 y, UINT8* t, UINT8* c) {
;	---------------------------------
; Function UPDATE_TILE
; ---------------------------------
_UPDATE_TILE::
	add	sp, #-8
;C:/GB/ZGB/common/src/Scroll.c:82: UINT8 replacement = *t;
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#4
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ldhl	sp,	#0
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:89: if(x < 0 || y < 0 || U_LESS_THAN(scroll_tiles_w - 1, x) || U_LESS_THAN(scroll_tiles_h - 1, y)) {
	ldhl	sp,	#10
	ld	a, (hl)
	sub	a, #0x00
	inc	hl
	ld	a, (hl)
	sbc	a, #0x00
	ld	d, (hl)
	ld	a, #0x00
	ld	e, a
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
	jp	C, 00111$
	ldhl	sp,	#12
	ld	a, (hl)
	sub	a, #0x00
	inc	hl
	ld	a, (hl)
	sbc	a, #0x00
	ld	d, (hl)
	ld	a, #0x00
	ld	e, a
	bit	7, e
	jr	Z,00170$
	bit	7, d
	jr	NZ,00171$
	cp	a, a
	jr	00171$
00170$:
	bit	7, d
	jr	Z,00171$
	scf
00171$:
	jp	C, 00111$
	ld	hl, #_scroll_tiles_w + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	dec	bc
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	c, e
	bit	7, a
	jr	NZ,00111$
	ld	hl, #_scroll_tiles_h + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	dec	bc
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	c, e
	bit	7, a
	jr	Z,00112$
00111$:
;C:/GB/ZGB/common/src/Scroll.c:90: replacement = 0;
	xor	a, a
	ldhl	sp,	#0
	ld	(hl), a
	jp	00113$
00112$:
;C:/GB/ZGB/common/src/Scroll.c:92: type = GetTileReplacement(t, &replacement);
	ldhl	sp,	#0
	ld	c, l
	ld	b, h
	push	bc
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_GetTileReplacement
	add	sp, #4
	ldhl	sp,	#1
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:93: if(type != 255u) {
	ld	a, (hl)
	inc	a
	jp	Z,00113$
;C:/GB/ZGB/common/src/Scroll.c:94: id = SPRITE_UNIQUE_ID(x, y);
	ldhl	sp,	#10
	ld	c, (hl)
	ld	b, #0x00
	inc	hl
	inc	hl
	ld	d, (hl)
	ld	a,#0x00
	ld	e,a
	or	a, c
	ldhl	sp,	#2
	ld	(hl), a
	ld	a, d
	or	a, b
	inc	hl
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:95: for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
	xor	a, a
	ldhl	sp,	#7
	ld	(hl), a
00118$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#7
	ld	a, (hl)
	sub	a, c
	ld	a, #0x01
	jr	Z,00177$
	xor	a, a
00177$:
	ldhl	sp,	#4
	ld	(hl), a
	bit	0, (hl)
	jp	NZ, 00104$
;C:/GB/ZGB/common/src/Scroll.c:96: s = sprite_manager_sprites[sprite_manager_updatables[i + 1]];
	ldhl	sp,	#7
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
	ldhl	sp,	#5
	ld	(hl+), a
	inc	de
	ld	a, (de)
;C:/GB/ZGB/common/src/Scroll.c:97: if((s->unique_id == id) && ((UINT16)s->type == (UINT16)type)) {
	ld	(hl-), a
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0017
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, c
	jr	NZ,00119$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jr	NZ,00119$
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0011
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#1
	ld	e, (hl)
	ld	d, #0x00
	ld	a, e
	sub	a, c
	jr	NZ,00182$
	ld	a, d
	sub	a, b
	jr	Z,00104$
00182$:
;C:/GB/ZGB/common/src/Scroll.c:98: break;
00119$:
;C:/GB/ZGB/common/src/Scroll.c:95: for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
	ldhl	sp,	#7
	inc	(hl)
	jp	00118$
00104$:
;C:/GB/ZGB/common/src/Scroll.c:102: if(i == sprite_manager_updatables[0]) {
	ldhl	sp,	#4
	ld	a, (hl)
	or	a, a
	jp	Z, 00113$
;C:/GB/ZGB/common/src/Scroll.c:103: s = SpriteManagerAdd(type, x << 3, (y - 1) << 3);
	ldhl	sp,#(13 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	dec	bc
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	dec	hl
	dec	hl
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
	ldhl	sp,	#5
	ld	a, (hl)
	push	af
	inc	sp
	call	_SpriteManagerAdd
	add	sp, #5
	ld	c, e
	ld	b, d
;C:/GB/ZGB/common/src/Scroll.c:104: if(s) {
	ld	a, b
	or	a, c
	jr	Z,00113$
;C:/GB/ZGB/common/src/Scroll.c:105: s->unique_id = id;
	ld	hl, #0x0017
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	(bc), a
	inc	bc
	ld	a, (hl)
	ld	(bc), a
00113$:
;C:/GB/ZGB/common/src/Scroll.c:111: id = 0x9800 + (0x1F & (x + scroll_offset_x)) + ((0x1F & (y + scroll_offset_y)) << 5);
	ld	hl, #_scroll_offset_x
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, c
	and	a, #0x1f
	ld	b, #0x00
	ld	c, a
	ld	hl, #0x9800
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#6
	ld	(hl+), a
	ld	(hl), d
	ld	hl, #_scroll_offset_y
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, c
	and	a, #0x1f
	ld	c, a
	ld	b, #0x00
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	sla	c
	rl	b
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
;C:/GB/ZGB/common/src/Scroll.c:112: SetTile(id, replacement);
	ldhl	sp,	#0
	ld	a, (hl)
	push	af
	inc	sp
	push	bc
	call	_SetTile
	add	sp, #3
;C:/GB/ZGB/common/src/Scroll.c:126: }
	add	sp, #8
	ret
;C:/GB/ZGB/common/src/Scroll.c:148: void ScrollSetTiles(UINT8 first_tile, const struct TilesInfo* tiles) {
;	---------------------------------
; Function ScrollSetTiles
; ---------------------------------
_ScrollSetTiles::
	add	sp, #-8
;C:/GB/ZGB/common/src/Scroll.c:153: PUSH_BANK(tiles->bank);
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	push	bc
	push	af
	inc	sp
	call	_PushBank
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Scroll.c:154: n_tiles = tiles->data->num_frames;
	inc	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0002
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
	ldhl	sp,	#0
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:155: palette_entries = tiles->data->color_data;
	ld	hl, #0x0005
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
	ldhl	sp,	#1
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:157: set_bkg_data(first_tile, n_tiles, tiles->data->data);
	inc	bc
	inc	bc
	inc	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	ldhl	sp,	#2
	ld	a, (hl)
	push	af
	inc	sp
	ldhl	sp,	#13
	ld	a, (hl)
	push	af
	inc	sp
	call	_set_bkg_data
	add	sp, #4
;C:/GB/ZGB/common/src/Scroll.c:158: for(i = first_tile; i < first_tile + n_tiles; ++i) {
	ldhl	sp,	#10
	ld	a, (hl)
	ldhl	sp,	#7
	ld	(hl), a
00103$:
	ldhl	sp,	#10
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#0
	ld	a, (hl)
	ldhl	sp,	#3
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
	inc	hl
	ld	c, (hl)
	ld	b, #0x00
	dec	hl
	dec	hl
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	ld	a, b
	ld	d, a
	ld	e, (hl)
	bit	7, e
	jr	Z,00125$
	bit	7, d
	jr	NZ,00126$
	cp	a, a
	jr	00126$
00125$:
	bit	7, d
	jr	Z,00126$
	scf
00126$:
	jp	NC, 00101$
;C:/GB/ZGB/common/src/Scroll.c:159: scroll_tile_info[i] = palette_entries ? palette_entries[i] : 0;
	ld	de, #_scroll_tile_info
	ldhl	sp,	#7
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#2
	ld	a, (hl-)
	or	a, (hl)
	jr	Z,00107$
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#7
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	jr	00108$
00107$:
	ld	bc, #0x0000
00108$:
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Scroll.c:158: for(i = first_tile; i < first_tile + n_tiles; ++i) {
	ldhl	sp,	#7
	inc	(hl)
	jp	00103$
00101$:
;C:/GB/ZGB/common/src/Scroll.c:161: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:162: }
	add	sp, #8
	ret
;C:/GB/ZGB/common/src/Scroll.c:164: void InitWindow(UINT8 x, UINT8 y, struct MapInfo* map) {
;	---------------------------------
; Function InitWindow
; ---------------------------------
_InitWindow::
	add	sp, #-4
;C:/GB/ZGB/common/src/Scroll.c:165: PUSH_BANK(map->bank);
	ldhl	sp,#(9 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	push	bc
	push	af
	inc	sp
	call	_PushBank
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Scroll.c:166: set_win_tiles(x, y, map->data->width, map->data->height, map->data->data);
	inc	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#0
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	hl, #0x0003
	add	hl, bc
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
	ld	(hl), a
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	b, (hl)
	pop	hl
	push	hl
	push	hl
	ldhl	sp,	#5
	ld	a, (hl)
	push	af
	inc	sp
	push	bc
	inc	sp
	ldhl	sp,	#11
	ld	a, (hl)
	push	af
	inc	sp
	dec	hl
	ld	a, (hl)
	push	af
	inc	sp
	call	_set_win_tiles
	add	sp, #6
;C:/GB/ZGB/common/src/Scroll.c:176: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:177: }
	add	sp, #4
	ret
;C:/GB/ZGB/common/src/Scroll.c:181: void ClampScrollLimits(UINT16* x, UINT16* y) {
;	---------------------------------
; Function ClampScrollLimits
; ---------------------------------
_ClampScrollLimits::
	add	sp, #-6
;C:/GB/ZGB/common/src/Scroll.c:182: if(clamp_enabled) {
	ld	hl, #_clamp_enabled
	ld	a, (hl)
	or	a, a
	jp	Z, 00111$
;C:/GB/ZGB/common/src/Scroll.c:183: if(U_LESS_THAN(*x, 0u)) {
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	bit	7, a
	jr	Z,00102$
;C:/GB/ZGB/common/src/Scroll.c:184: *x = 0u;		
	pop	bc
	pop	hl
	push	hl
	push	bc
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
00102$:
;C:/GB/ZGB/common/src/Scroll.c:186: if(*x > (scroll_w - SCREENWIDTH)) {
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	inc	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	hl, #_scroll_w
	ld	a, (hl)
	add	a, #0x60
	ld	c, a
	inc	hl
	ld	a, (hl)
	adc	a, #0xff
	ld	b, a
	ldhl	sp,	#4
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jr	NC,00104$
;C:/GB/ZGB/common/src/Scroll.c:187: *x = (scroll_w - SCREENWIDTH);
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
00104$:
;C:/GB/ZGB/common/src/Scroll.c:189: if(U_LESS_THAN(*y, 0u)) {
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	bit	7, a
	jr	Z,00106$
;C:/GB/ZGB/common/src/Scroll.c:190: *y = 0u;		
	pop	hl
	push	hl
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
00106$:
;C:/GB/ZGB/common/src/Scroll.c:192: if(*y > (scroll_h - SCREENHEIGHT + scroll_h_border)) {
	pop	de
	push	de
	ld	a,(de)
	ldhl	sp,	#2
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	hl, #_scroll_h
	ld	a, (hl)
	add	a, #0x70
	ld	c, a
	inc	hl
	ld	a, (hl)
	adc	a, #0xff
	ld	b, a
	ld	hl, #_scroll_h_border
	ld	a, (hl)
	ld	e, a
	rla
	sbc	a, a
	ld	d, a
	ldhl	sp,	#4
	ld	(hl), e
	inc	hl
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#2
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jr	NC,00111$
;C:/GB/ZGB/common/src/Scroll.c:193: *y = (scroll_h - SCREENHEIGHT + scroll_h_border);
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
00111$:
;C:/GB/ZGB/common/src/Scroll.c:196: }
	add	sp, #6
	ret
;C:/GB/ZGB/common/src/Scroll.c:198: void ScrollSetMap(const struct MapInfo* map_data) {
;	---------------------------------
; Function ScrollSetMap
; ---------------------------------
_ScrollSetMap::
	add	sp, #-4
;C:/GB/ZGB/common/src/Scroll.c:199: PUSH_BANK(map_data->bank);
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	a,(de)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Scroll.c:200: scroll_tiles_w = map_data->data->width;
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
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	hl, #_scroll_tiles_w
	ld	(hl), a
	xor	a, a
	ld	(_scroll_tiles_w + 1), a
;C:/GB/ZGB/common/src/Scroll.c:201: scroll_tiles_h = map_data->data->height;
	ldhl	sp,#(3 - 1)
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
	ld	a, b
	ld	l, c
	ld	h, a
	ld	a, (hl)
	ld	hl, #_scroll_tiles_h
	ld	(hl), a
	xor	a, a
	ld	(_scroll_tiles_h + 1), a
;C:/GB/ZGB/common/src/Scroll.c:202: scroll_map = map_data->data->data;
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	ld	e, c
	ld	d, b
	ld	a,(de)
	ld	hl, #_scroll_map
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:203: scroll_cmap = map_data->data->attributes;
	ldhl	sp,#(3 - 1)
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
	ld	e, c
	ld	d, b
	ld	a,(de)
	ld	hl, #_scroll_cmap
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:204: scroll_x = 0;
	ld	hl, #_scroll_x
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:205: scroll_y = 0;
	ld	hl, #_scroll_y
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:206: scroll_w = scroll_tiles_w << 3;
	ld	hl, #_scroll_tiles_w
	ld	a, (hl)
	ld	hl, #_scroll_w
	ld	(hl), a
	ld	hl, #_scroll_tiles_w + 1
	ld	a, (hl)
	ld	hl, #_scroll_w + 1
	ld	(hl), a
	ld	a, #0x03+1
	jr	00111$
00110$:
	dec	hl
	sla	(hl)
	inc	hl
	rl	(hl)
00111$:
	dec	a
	jr	NZ,00110$
;C:/GB/ZGB/common/src/Scroll.c:207: scroll_h = scroll_tiles_h << 3;
	ld	hl, #_scroll_tiles_h
	ld	a, (hl)
	ld	hl, #_scroll_h
	ld	(hl), a
	ld	hl, #_scroll_tiles_h + 1
	ld	a, (hl)
	ld	hl, #_scroll_h + 1
	ld	(hl), a
	ld	a, #0x03+1
	jr	00113$
00112$:
	dec	hl
	sla	(hl)
	inc	hl
	rl	(hl)
00113$:
	dec	a
	jr	NZ,00112$
;C:/GB/ZGB/common/src/Scroll.c:208: scroll_bank = map_data->bank;
	pop	de
	push	de
	ld	a,(de)
	ld	hl, #_scroll_bank
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:209: if(scroll_target) {
	ld	hl, #_scroll_target + 1
	ld	a, (hl-)
	or	a, (hl)
	jp	Z, 00102$
;C:/GB/ZGB/common/src/Scroll.c:210: scroll_x = scroll_target->x - (SCREENWIDTH >> 1);
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, c
	add	a, #0xb0
	ld	hl, #_scroll_x
	ld	(hl), a
	ld	a, b
	adc	a, #0xff
	inc	hl
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:211: scroll_y = scroll_target->y - scroll_bottom_movement_limit; //Move the camera to its bottom limit
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_scroll_bottom_movement_limit
	ld	e, (hl)
	ld	d, #0x00
	ldhl	sp,	#2
	ld	(hl), e
	inc	hl
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ld	hl, #_scroll_y + 1
	ld	(hl-), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:212: ClampScrollLimits(&scroll_x, &scroll_y);
	ld	hl, #_scroll_y
	push	hl
	ld	hl, #_scroll_x
	push	hl
	call	_ClampScrollLimits
	add	sp, #4
00102$:
;C:/GB/ZGB/common/src/Scroll.c:214: pending_h_i = 0;
	ld	hl, #_pending_h_i
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:215: pending_w_i = 0;
	ld	hl, #_pending_w_i
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:216: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:217: }
	add	sp, #4
	ret
;C:/GB/ZGB/common/src/Scroll.c:219: void InitScroll(const struct MapInfo* map_data, const UINT8* coll_list, const UINT8* coll_list_down) {
;	---------------------------------
; Function InitScroll
; ---------------------------------
_InitScroll::
	add	sp, #-2
;C:/GB/ZGB/common/src/Scroll.c:224: PUSH_BANK(map_data->bank)
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	a,(de)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Scroll.c:225: tiles_info = map_data->data->tiles;
	pop	bc
	push	bc
	inc	bc
	ld	l, c
	ld	h, b
	ld	b, (hl)
	inc	hl
	ld	c, (hl)
	ld	a, b
	add	a, #0x06
	ld	b, a
	jr	NC,00103$
	inc	c
00103$:
	ld	l, b
	ld	h, c
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
;C:/GB/ZGB/common/src/Scroll.c:226: POP_BANK;
	push	bc
	call	_PopBank
	pop	bc
;C:/GB/ZGB/common/src/Scroll.c:228: InitScrollWithTiles(map_data, tiles_info, coll_list, coll_list_down);
	ldhl	sp,	#8
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
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_InitScrollWithTiles
	add	sp, #8
;C:/GB/ZGB/common/src/Scroll.c:229: }
	add	sp, #2
	ret
;C:/GB/ZGB/common/src/Scroll.c:231: void InitScrollWithTiles(const struct MapInfo* map_data, const struct TilesInfo* tiles_info, const UINT8* coll_list, const UINT8* coll_list_down)
;	---------------------------------
; Function InitScrollWithTiles
; ---------------------------------
_InitScrollWithTiles::
	add	sp, #-5
;C:/GB/ZGB/common/src/Scroll.c:236: ScrollSetTiles(0, tiles_info);
	ldhl	sp,	#9
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	xor	a, a
	push	af
	inc	sp
	call	_ScrollSetTiles
	add	sp, #3
;C:/GB/ZGB/common/src/Scroll.c:238: ScrollSetMap(map_data);
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_ScrollSetMap
	add	sp, #2
;C:/GB/ZGB/common/src/Scroll.c:240: for(i = 0u; i != 128; ++i) {
	ld	c, #0x00
00109$:
;C:/GB/ZGB/common/src/Scroll.c:241: scroll_collisions[i] = 0u;
	ld	a, #<(_scroll_collisions)
	add	a, c
	ld	b, a
	ld	a, #>(_scroll_collisions)
	adc	a, #0x00
	ld	l, b
	ld	h, a
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:242: scroll_collisions_down[i] = 0u;
	ld	a, #<(_scroll_collisions_down)
	add	a, c
	ld	b, a
	ld	a, #>(_scroll_collisions_down)
	adc	a, #0x00
	ld	l, b
	ld	h, a
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Scroll.c:240: for(i = 0u; i != 128; ++i) {
	inc	c
	ld	a, c
	sub	a, #0x80
	jr	NZ,00109$
;C:/GB/ZGB/common/src/Scroll.c:244: if(coll_list) {
	ldhl	sp,	#12
	ld	a, (hl-)
	or	a, (hl)
	jr	Z,00104$
;C:/GB/ZGB/common/src/Scroll.c:245: for(i = 0u; coll_list[i] != 0u; ++i) {
	ld	c, #0x00
00112$:
	ldhl	sp,#(12 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	l, c
	ld	h, #0x00
	add	hl, de
	ld	b,l
	ld	a,h
	ld	a, (hl)
	or	a, a
	jr	Z,00104$
;C:/GB/ZGB/common/src/Scroll.c:246: scroll_collisions[coll_list[i]] = 1u;
	add	a, #<(_scroll_collisions)
	ld	b, a
	ld	a, #0x00
	adc	a, #>(_scroll_collisions)
	ld	l, b
	ld	h, a
	ld	(hl), #0x01
;C:/GB/ZGB/common/src/Scroll.c:245: for(i = 0u; coll_list[i] != 0u; ++i) {
	inc	c
	jr	00112$
00104$:
;C:/GB/ZGB/common/src/Scroll.c:249: if(coll_list_down) {
	ldhl	sp,	#14
	ld	a, (hl-)
	or	a, (hl)
	jr	Z,00107$
;C:/GB/ZGB/common/src/Scroll.c:250: for(i = 0u; coll_list_down[i] != 0u; ++i) {
	ld	c, #0x00
00115$:
	ldhl	sp,#(14 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	l, c
	ld	h, #0x00
	add	hl, de
	ld	b,l
	ld	a,h
	ld	a, (hl)
	or	a, a
	jr	Z,00107$
;C:/GB/ZGB/common/src/Scroll.c:251: scroll_collisions_down[coll_list_down[i]] = 1u;
	add	a, #<(_scroll_collisions_down)
	ld	b, a
	ld	a, #0x00
	adc	a, #>(_scroll_collisions_down)
	ld	l, b
	ld	h, a
	ld	(hl), #0x01
;C:/GB/ZGB/common/src/Scroll.c:250: for(i = 0u; coll_list_down[i] != 0u; ++i) {
	inc	c
	jr	00115$
00107$:
;C:/GB/ZGB/common/src/Scroll.c:256: PUSH_BANK(map_data->bank);
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Scroll.c:257: y = scroll_y >> 3;
	ld	hl, #_scroll_y
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	ld	hl, #_scroll_y + 1
	ld	a, (hl)
	ldhl	sp,	#3
	ld	(hl), a
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
;C:/GB/ZGB/common/src/Scroll.c:258: for(i = 0u; i != (SCREEN_TILE_REFRES_H) && y != scroll_h; ++i, y ++) {
	xor	a, a
	inc	hl
	inc	hl
	ld	(hl), a
00119$:
	ldhl	sp,	#4
	ld	a, (hl)
	sub	a, #0x15
	jp	Z,00108$
	ldhl	sp,#(3 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_scroll_h
	ld	a, (hl)
	sub	a, c
	jr	NZ,00185$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jp	Z,00108$
00185$:
;C:/GB/ZGB/common/src/Scroll.c:259: ScrollUpdateRow((scroll_x >> 3) - SCREEN_PAD_LEFT,  y - SCREEN_PAD_TOP);
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0001
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#1
	ld	(hl-), a
	ld	(hl), e
	ld	hl, #_scroll_x + 1
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
	dec	bc
	pop	hl
	push	hl
	push	hl
	push	bc
	call	_ScrollUpdateRow
	add	sp, #4
;C:/GB/ZGB/common/src/Scroll.c:258: for(i = 0u; i != (SCREEN_TILE_REFRES_H) && y != scroll_h; ++i, y ++) {
	ldhl	sp,	#4
	inc	(hl)
	dec	hl
	dec	hl
	inc	(hl)
	jp	NZ,00119$
	inc	hl
	inc	(hl)
	jp	00119$
00108$:
;C:/GB/ZGB/common/src/Scroll.c:261: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:262: }
	add	sp, #5
	ret
;C:/GB/ZGB/common/src/Scroll.c:264: void ScrollUpdateRowR() {
;	---------------------------------
; Function ScrollUpdateRowR
; ---------------------------------
_ScrollUpdateRowR::
	add	sp, #-3
;C:/GB/ZGB/common/src/Scroll.c:267: for(i = 0u; i != 5 && pending_w_i != 0; ++i, -- pending_w_i)  {
	xor	a, a
	ldhl	sp,	#2
	ld	(hl), a
00104$:
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x05
	jp	Z,00106$
	ld	hl, #_pending_w_i
	ld	a, (hl)
	or	a, a
	jp	Z, 00106$
;C:/GB/ZGB/common/src/Scroll.c:271: UPDATE_TILE(pending_w_x ++, pending_w_y, pending_w_map ++,0);
	ld	hl, #_pending_w_map
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	ld	hl, #_pending_w_map
	inc	(hl)
	jr	NZ,00125$
	inc	hl
	inc	(hl)
00125$:
	ld	hl, #_pending_w_x + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	dec	hl
	inc	(hl)
	jr	NZ,00126$
	inc	hl
	inc	(hl)
00126$:
	ld	hl, #0x0000
	push	hl
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ld	hl, #_pending_w_y
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_UPDATE_TILE
	add	sp, #8
;C:/GB/ZGB/common/src/Scroll.c:267: for(i = 0u; i != 5 && pending_w_i != 0; ++i, -- pending_w_i)  {
	ldhl	sp,	#2
	inc	(hl)
	ld	hl, #_pending_w_i
	dec	(hl)
	jp	00104$
00106$:
;C:/GB/ZGB/common/src/Scroll.c:274: }
	add	sp, #3
	ret
;C:/GB/ZGB/common/src/Scroll.c:276: void ScrollUpdateRowWithDelay(INT16 x, INT16 y) {
;	---------------------------------
; Function ScrollUpdateRowWithDelay
; ---------------------------------
_ScrollUpdateRowWithDelay::
;C:/GB/ZGB/common/src/Scroll.c:277: while(pending_w_i) {
00101$:
	ld	hl, #_pending_w_i
	ld	a, (hl)
	or	a, a
	jr	Z,00103$
;C:/GB/ZGB/common/src/Scroll.c:278: ScrollUpdateRowR();
	call	_ScrollUpdateRowR
	jr	00101$
00103$:
;C:/GB/ZGB/common/src/Scroll.c:281: pending_w_x = x;
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_pending_w_x
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:282: pending_w_y = y;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_pending_w_y
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Scroll.c:283: pending_w_i = SCREEN_TILE_REFRES_W;
	ld	hl, #_pending_w_i
	ld	(hl), #0x17
;C:/GB/ZGB/common/src/Scroll.c:284: pending_w_map = scroll_map + scroll_tiles_w * y + x;
	push	bc
	ld	hl, #_scroll_tiles_w
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__mulint
	add	sp, #4
	ld	c, e
	ld	b, d
	ld	a, c
	ld	hl, #_scroll_map
	add	a, (hl)
	ld	c, a
	ld	a, b
	inc	hl
	adc	a, (hl)
	ld	b, a
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ld	hl, #_pending_w_map
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Scroll.c:289: }
	ret
;C:/GB/ZGB/common/src/Scroll.c:291: void ScrollUpdateRow(INT16 x, INT16 y) {
;	---------------------------------
; Function ScrollUpdateRow
; ---------------------------------
_ScrollUpdateRow::
	add	sp, #-5
;C:/GB/ZGB/common/src/Scroll.c:293: unsigned char* map = scroll_map + scroll_tiles_w * y + x;
	ldhl	sp,#(10 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	ld	hl, #_scroll_tiles_w
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__mulint
	add	sp, #4
	ld	c, e
	ld	b, d
	ld	a, c
	ld	hl, #_scroll_map
	add	a, (hl)
	ld	c, a
	ld	a, b
	inc	hl
	adc	a, (hl)
	ld	b, a
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
;C:/GB/ZGB/common/src/Scroll.c:299: PUSH_BANK(scroll_bank);
	push	bc
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Scroll.c:300: for(i = 0u; i != SCREEN_TILE_REFRES_W; ++i) {
	ldhl	sp,	#2
	ld	(hl), c
	inc	hl
	ld	(hl), b
	xor	a, a
	inc	hl
	ld	(hl), a
00102$:
;C:/GB/ZGB/common/src/Scroll.c:304: UPDATE_TILE(x + i, y, map ++, 0);
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	inc	hl
	inc	(hl)
	jr	NZ,00117$
	inc	hl
	inc	(hl)
00117$:
	ldhl	sp,	#4
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #0x0000
	push	hl
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_UPDATE_TILE
	add	sp, #8
;C:/GB/ZGB/common/src/Scroll.c:300: for(i = 0u; i != SCREEN_TILE_REFRES_W; ++i) {
	ldhl	sp,	#4
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x17
	jp	NZ,00102$
;C:/GB/ZGB/common/src/Scroll.c:307: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:308: }
	add	sp, #5
	ret
;C:/GB/ZGB/common/src/Scroll.c:310: void ScrollUpdateColumnR() {
;	---------------------------------
; Function ScrollUpdateColumnR
; ---------------------------------
_ScrollUpdateColumnR::
	dec	sp
;C:/GB/ZGB/common/src/Scroll.c:313: for(i = 0u; i != 5 && pending_h_i != 0; ++i, pending_h_i --) {
	xor	a, a
	ldhl	sp,	#0
	ld	(hl), a
00104$:
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, #0x05
	jp	Z,00106$
	ld	hl, #_pending_h_i
	ld	a, (hl)
	or	a, a
	jp	Z, 00106$
;C:/GB/ZGB/common/src/Scroll.c:319: UPDATE_TILE(pending_h_x, pending_h_y ++, pending_h_map, 0);
	ld	hl, #_pending_h_y + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	dec	hl
	inc	(hl)
	jr	NZ,00125$
	inc	hl
	inc	(hl)
00125$:
	ld	hl, #0x0000
	push	hl
	ld	hl, #_pending_h_map
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	ld	hl, #_pending_h_x
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_UPDATE_TILE
	add	sp, #8
;C:/GB/ZGB/common/src/Scroll.c:320: pending_h_map += scroll_tiles_w;
	ld	hl, #_pending_h_map
	ld	a, (hl)
	ld	hl, #_scroll_tiles_w
	add	a, (hl)
	ld	hl, #_pending_h_map
	ld	(hl+), a
	ld	a, (hl)
	ld	hl, #_scroll_tiles_w + 1
	adc	a, (hl)
	ld	hl, #_pending_h_map + 1
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:313: for(i = 0u; i != 5 && pending_h_i != 0; ++i, pending_h_i --) {
	ldhl	sp,	#0
	inc	(hl)
	ld	hl, #_pending_h_i
	dec	(hl)
	jp	00104$
00106$:
;C:/GB/ZGB/common/src/Scroll.c:323: }
	inc	sp
	ret
;C:/GB/ZGB/common/src/Scroll.c:325: void ScrollUpdateColumnWithDelay(INT16 x, INT16 y) {
;	---------------------------------
; Function ScrollUpdateColumnWithDelay
; ---------------------------------
_ScrollUpdateColumnWithDelay::
;C:/GB/ZGB/common/src/Scroll.c:326: while(pending_h_i) {
00101$:
	ld	hl, #_pending_h_i
	ld	a, (hl)
	or	a, a
	jr	Z,00103$
;C:/GB/ZGB/common/src/Scroll.c:327: ScrollUpdateColumnR();
	call	_ScrollUpdateColumnR
	jr	00101$
00103$:
;C:/GB/ZGB/common/src/Scroll.c:330: pending_h_x = x;
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_pending_h_x
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:331: pending_h_y = y;
	ldhl	sp,#(5 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_pending_h_y
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Scroll.c:332: pending_h_i = SCREEN_TILE_REFRES_H;
	ld	hl, #_pending_h_i
	ld	(hl), #0x15
;C:/GB/ZGB/common/src/Scroll.c:333: pending_h_map = scroll_map + scroll_tiles_w * y + x;
	push	bc
	ld	hl, #_scroll_tiles_w
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__mulint
	add	sp, #4
	ld	c, e
	ld	b, d
	ld	a, c
	ld	hl, #_scroll_map
	add	a, (hl)
	ld	c, a
	ld	a, b
	inc	hl
	adc	a, (hl)
	ld	b, a
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	a, l
	ld	d, h
	ld	hl, #_pending_h_map
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Scroll.c:338: }
	ret
;C:/GB/ZGB/common/src/Scroll.c:340: void ScrollUpdateColumn(INT16 x, INT16 y) {
;	---------------------------------
; Function ScrollUpdateColumn
; ---------------------------------
_ScrollUpdateColumn::
	add	sp, #-3
;C:/GB/ZGB/common/src/Scroll.c:342: unsigned char* map = &scroll_map[scroll_tiles_w * y + x];
	ldhl	sp,#(8 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	ld	hl, #_scroll_tiles_w
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__mulint
	add	sp, #4
	ldhl	sp,	#1
	ld	(hl), e
	inc	hl
	ld	(hl), d
	ldhl	sp,#(6 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#1
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, c
	ld	hl, #_scroll_map
	add	a, (hl)
	ld	c, a
	ld	a, b
	inc	hl
	adc	a, (hl)
	ld	b, a
	inc	sp
	inc	sp
	push	bc
;C:/GB/ZGB/common/src/Scroll.c:347: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Scroll.c:348: for(i = 0u; i != SCREEN_TILE_REFRES_H; ++i) {
	xor	a, a
	ldhl	sp,	#2
	ld	(hl), a
00102$:
;C:/GB/ZGB/common/src/Scroll.c:354: UPDATE_TILE(x, y + i, map, 0);
	ldhl	sp,	#2
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #0x0000
	push	hl
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	ldhl	sp,	#11
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_UPDATE_TILE
	add	sp, #8
;C:/GB/ZGB/common/src/Scroll.c:355: map += scroll_tiles_w;
	pop	de
	push	de
	ld	hl, #_scroll_tiles_w
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	inc	sp
	inc	sp
	push	hl
;C:/GB/ZGB/common/src/Scroll.c:348: for(i = 0u; i != SCREEN_TILE_REFRES_H; ++i) {
	ldhl	sp,	#2
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x15
	jp	NZ,00102$
;C:/GB/ZGB/common/src/Scroll.c:358: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:359: }
	add	sp, #3
	ret
;C:/GB/ZGB/common/src/Scroll.c:361: void RefreshScroll() {
;	---------------------------------
; Function RefreshScroll
; ---------------------------------
_RefreshScroll::
	add	sp, #-10
;C:/GB/ZGB/common/src/Scroll.c:362: UINT16 ny = scroll_y;
	ld	hl, #_scroll_y
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:364: if(scroll_target) {
	ld	hl, #_scroll_target + 1
	ld	a, (hl-)
	or	a, (hl)
	jp	Z, 00108$
;C:/GB/ZGB/common/src/Scroll.c:365: if(U_LESS_THAN(scroll_bottom_movement_limit, scroll_target->y - scroll_y)) {
	ld	hl, #_scroll_bottom_movement_limit
	ld	a, (hl)
	ldhl	sp,	#8
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	ld	hl, #_scroll_target
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), e
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x000a
	add	hl, de
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#4
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ld	hl, #_scroll_y + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	sub	a, c
	ld	e, a
	ld	a, d
	sbc	a, b
	inc	hl
	inc	hl
	ld	(hl-), a
	ld	(hl), e
	ldhl	sp,#(9 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	dec	hl
	dec	hl
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	inc	hl
	inc	hl
	ld	(hl-), a
	ld	(hl), e
	inc	hl
	bit	7, (hl)
	jr	Z,00104$
;C:/GB/ZGB/common/src/Scroll.c:366: ny = scroll_target->y - scroll_bottom_movement_limit;
	ldhl	sp,#(5 - 1)
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
	inc	sp
	inc	sp
	push	bc
	jp	00105$
00104$:
;C:/GB/ZGB/common/src/Scroll.c:367: } else if(U_LESS_THAN(scroll_target->y - scroll_y, scroll_top_movement_limit)) {
	ld	hl, #_scroll_top_movement_limit
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,#(7 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	sub	a, c
	ld	e, a
	ld	a, d
	sbc	a, b
	inc	hl
	inc	hl
	ld	(hl-), a
	ld	(hl), e
	inc	hl
	bit	7, (hl)
	jr	Z,00105$
;C:/GB/ZGB/common/src/Scroll.c:368: ny = scroll_target->y - scroll_top_movement_limit;
	ldhl	sp,#(5 - 1)
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
	inc	sp
	inc	sp
	push	bc
00105$:
;C:/GB/ZGB/common/src/Scroll.c:371: MoveScroll(scroll_target->x - (SCREENWIDTH >> 1), ny);
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0008
	add	hl, de
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, c
	add	a, #0xb0
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
	pop	hl
	push	hl
	push	hl
	push	bc
	call	_MoveScroll
	add	sp, #4
00108$:
;C:/GB/ZGB/common/src/Scroll.c:373: }
	add	sp, #10
	ret
;C:/GB/ZGB/common/src/Scroll.c:375: void MoveScroll(INT16 x, INT16 y) {
;	---------------------------------
; Function MoveScroll
; ---------------------------------
_MoveScroll::
	add	sp, #-10
;C:/GB/ZGB/common/src/Scroll.c:378: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Scroll.c:379: ClampScrollLimits(&x, &y);
	ldhl	sp,	#14
	ld	e, l
	ld	d, h
	ldhl	sp,	#12
	ld	c, l
	ld	b, h
	push	de
	push	bc
	call	_ClampScrollLimits
	add	sp, #4
;C:/GB/ZGB/common/src/Scroll.c:381: current_column = scroll_x >> 3;
	ld	hl, #_scroll_x
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	ld	hl, #_scroll_x + 1
	ld	a, (hl)
	ldhl	sp,	#1
	ld	(hl), a
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
;C:/GB/ZGB/common/src/Scroll.c:382: new_column     = x >> 3;
	ldhl	sp,#(13 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	sra	b
	rr	c
	sra	b
	rr	c
	sra	b
	rr	c
;C:/GB/ZGB/common/src/Scroll.c:383: current_row    = scroll_y >> 3;
	ld	hl, #_scroll_y
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	ld	hl, #_scroll_y + 1
	ld	a, (hl)
	ldhl	sp,	#3
	ld	(hl), a
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
;C:/GB/ZGB/common/src/Scroll.c:384: new_row        = y >> 3;
	ldhl	sp,	#14
	ld	a, (hl)
	ldhl	sp,	#4
	ld	(hl), a
	ldhl	sp,	#15
	ld	a, (hl)
	ldhl	sp,	#5
	ld	(hl), a
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
	inc	hl
	sra	(hl)
	dec	hl
	rr	(hl)
;C:/GB/ZGB/common/src/Scroll.c:388: ScrollUpdateColumnWithDelay(new_column - SCREEN_PAD_LEFT + SCREEN_TILE_REFRES_W - 1, new_row - SCREEN_PAD_TOP);
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0001
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ldhl	sp,	#7
	ld	(hl-), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:390: ScrollUpdateColumnWithDelay(new_column - SCREEN_PAD_LEFT, new_row - SCREEN_PAD_TOP);
	ld	de, #0x0001
	ld	a, c
	sub	a, e
	ld	e, a
	ld	a, b
	sbc	a, d
	ldhl	sp,	#9
	ld	(hl-), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:386: if(current_column != new_column) {
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, c
	jr	NZ,00147$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jp	Z,00105$
00147$:
;C:/GB/ZGB/common/src/Scroll.c:387: if(new_column > current_column) {
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, c
	inc	hl
	ld	a, (hl)
	sbc	a, b
	ld	d, (hl)
	ld	a, b
	ld	e, a
	bit	7, e
	jr	Z,00148$
	bit	7, d
	jr	NZ,00149$
	cp	a, a
	jr	00149$
00148$:
	bit	7, d
	jr	Z,00149$
	scf
00149$:
	jr	NC,00102$
;C:/GB/ZGB/common/src/Scroll.c:388: ScrollUpdateColumnWithDelay(new_column - SCREEN_PAD_LEFT + SCREEN_TILE_REFRES_W - 1, new_row - SCREEN_PAD_TOP);
	ld	hl, #0x0015
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_ScrollUpdateColumnWithDelay
	add	sp, #4
	jr	00105$
00102$:
;C:/GB/ZGB/common/src/Scroll.c:390: ScrollUpdateColumnWithDelay(new_column - SCREEN_PAD_LEFT, new_row - SCREEN_PAD_TOP);
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_ScrollUpdateColumnWithDelay
	add	sp, #4
00105$:
;C:/GB/ZGB/common/src/Scroll.c:394: if(current_row != new_row) {
	ldhl	sp,	#2
	ld	a, (hl+)
	inc	hl
	sub	a, (hl)
	jr	NZ,00150$
	dec	hl
	ld	a, (hl+)
	inc	hl
	sub	a, (hl)
	jp	Z,00110$
00150$:
;C:/GB/ZGB/common/src/Scroll.c:395: if(new_row > current_row) {
	ldhl	sp,	#2
	ld	e, l
	ld	d, h
	ldhl	sp,	#4
	ld	a, (de)
	sub	a, (hl)
	inc	hl
	inc	de
	ld	a, (de)
	sbc	a, (hl)
	ld	a, (de)
	ld	d, a
	ld	e, (hl)
	bit	7, e
	jr	Z,00151$
	bit	7, d
	jr	NZ,00152$
	cp	a, a
	jr	00152$
00151$:
	bit	7, d
	jr	Z,00152$
	scf
00152$:
	jr	NC,00107$
;C:/GB/ZGB/common/src/Scroll.c:396: ScrollUpdateRowWithDelay(new_column - SCREEN_PAD_LEFT, new_row - SCREEN_PAD_TOP + SCREEN_TILE_REFRES_H - 1);
	ldhl	sp,#(5 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0013
	add	hl, de
	ld	c, l
	ld	b, h
	push	bc
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_ScrollUpdateRowWithDelay
	add	sp, #4
	jr	00110$
00107$:
;C:/GB/ZGB/common/src/Scroll.c:398: ScrollUpdateRowWithDelay(new_column - SCREEN_PAD_LEFT, new_row - SCREEN_PAD_TOP);
	ldhl	sp,	#6
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_ScrollUpdateRowWithDelay
	add	sp, #4
00110$:
;C:/GB/ZGB/common/src/Scroll.c:402: scroll_x = x;
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_scroll_x
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:403: scroll_y = y;
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_scroll_y
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Scroll.c:405: if(pending_w_i) {
	ld	hl, #_pending_w_i
	ld	a, (hl)
	or	a, a
	jr	Z,00112$
;C:/GB/ZGB/common/src/Scroll.c:406: ScrollUpdateRowR();
	call	_ScrollUpdateRowR
00112$:
;C:/GB/ZGB/common/src/Scroll.c:408: if(pending_h_i) {
	ld	hl, #_pending_h_i
	ld	a, (hl)
	or	a, a
	jr	Z,00114$
;C:/GB/ZGB/common/src/Scroll.c:409: ScrollUpdateColumnR();
	call	_ScrollUpdateColumnR
00114$:
;C:/GB/ZGB/common/src/Scroll.c:411: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:412: }
	add	sp, #10
	ret
;C:/GB/ZGB/common/src/Scroll.c:414: UINT8* GetScrollTilePtr(UINT16 x, UINT16 y) {
;	---------------------------------
; Function GetScrollTilePtr
; ---------------------------------
_GetScrollTilePtr::
;C:/GB/ZGB/common/src/Scroll.c:418: return scroll_map + (scroll_tiles_w * y + x); //TODO: fix this mult!!
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ld	hl, #_scroll_tiles_w
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__mulint
	add	sp, #4
	ld	c, e
	ld	b, d
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, c
	ld	hl, #_scroll_map
	add	a, (hl)
	ld	c, a
	ld	a, b
	inc	hl
	adc	a, (hl)
	ld	b, a
	ld	e, c
	ld	d, b
;C:/GB/ZGB/common/src/Scroll.c:419: }
	ret
;C:/GB/ZGB/common/src/Scroll.c:421: UINT8 GetScrollTile(UINT16 x, UINT16 y) {
;	---------------------------------
; Function GetScrollTile
; ---------------------------------
_GetScrollTile::
;C:/GB/ZGB/common/src/Scroll.c:423: PUSH_BANK(scroll_bank);
	ld	hl, #_scroll_bank
	ld	a, (hl)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/Scroll.c:424: ret = *GetScrollTilePtr(x, y);
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	ldhl	sp,	#4
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	_GetScrollTilePtr
	add	sp, #4
	ld	a, (de)
	ld	e, a
;C:/GB/ZGB/common/src/Scroll.c:425: POP_BANK;
	push	de
	call	_PopBank
	pop	de
;C:/GB/ZGB/common/src/Scroll.c:426: return ret;
;C:/GB/ZGB/common/src/Scroll.c:427: }
	ret
;C:/GB/ZGB/common/src/Scroll.c:429: void GetMapSize(const struct MapInfo* map, UINT8* tiles_w, UINT8* tiles_h)
;	---------------------------------
; Function GetMapSize
; ---------------------------------
_GetMapSize::
	add	sp, #-4
;C:/GB/ZGB/common/src/Scroll.c:431: PUSH_BANK(map->bank);
	ldhl	sp,#(7 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	push	bc
	push	af
	inc	sp
	call	_PushBank
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Scroll.c:432: *tiles_w = map->data->width;
	ldhl	sp,	#8
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), e
	inc	bc
	inc	sp
	inc	sp
	push	bc
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	c, (hl)
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Scroll.c:433: *tiles_h = map->data->height;
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	inc	bc
	inc	bc
	inc	bc
	ld	a, b
	ld	l, c
	ld	h, a
	ld	c, (hl)
	ldhl	sp,	#2
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Scroll.c:434: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:435: }
	add	sp, #4
	ret
;C:/GB/ZGB/common/src/Scroll.c:437: UINT8 ScrollFindTile(const struct MapInfo* map, UINT8 tile,
;	---------------------------------
; Function ScrollFindTile
; ---------------------------------
_ScrollFindTile::
	add	sp, #-16
;C:/GB/ZGB/common/src/Scroll.c:441: UINT16 yt = 0;
	xor	a, a
	ldhl	sp,	#0
	ld	(hl+), a
;C:/GB/ZGB/common/src/Scroll.c:442: UINT8 found = 1;
	ld	(hl+), a
	ld	(hl), #0x01
;C:/GB/ZGB/common/src/Scroll.c:444: PUSH_BANK(map->bank);
	ldhl	sp,#(19 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	push	bc
	push	af
	inc	sp
	call	_PushBank
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Scroll.c:445: for(xt = start_x; xt != start_x + w; ++ xt) {
	ldhl	sp,	#21
	ld	a, (hl)
	ldhl	sp,	#3
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	inc	bc
	inc	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#12
	ld	(hl+), a
	ld	(hl), e
00110$:
	ldhl	sp,	#21
	ld	c, (hl)
	ld	b, #0x00
	inc	hl
	inc	hl
	ld	a, (hl)
	ldhl	sp,	#14
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl-), a
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
	ldhl	sp,	#12
	ld	a, (hl)
	sub	a, c
	jr	NZ,00139$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jp	Z,00104$
00139$:
;C:/GB/ZGB/common/src/Scroll.c:446: for(yt = start_y; yt != start_y + h; ++ yt) {
	ldhl	sp,	#22
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	ld	e, c
	ld	d, b
	ld	a,(de)
	inc	hl
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	inc	bc
	inc	bc
	ld	a, (bc)
	inc	hl
	ld	(hl), a
	ldhl	sp,	#0
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#14
	ld	(hl+), a
	ld	(hl), e
00107$:
	ldhl	sp,	#22
	ld	a, (hl)
	ldhl	sp,	#10
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,	#24
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
	ldhl	sp,	#14
	ld	a, (hl)
	sub	a, c
	jr	NZ,00140$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jp	Z,00111$
00140$:
;C:/GB/ZGB/common/src/Scroll.c:447: if(map->data->data[map->data->width * yt + xt] == (UINT16)tile) { //That cast over there is mandatory and gave me a lot of headaches
	ldhl	sp,	#9
	ld	c, (hl)
	ld	b, #0x00
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	__mulint
	add	sp, #4
	ld	c, e
	ld	b, d
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ldhl	sp,	#20
	ld	b, (hl)
	ld	de,#0x0000
	ld	a, b
	sub	a, c
	jr	NZ,00141$
	ld	a, e
	sub	a, d
	jp	Z,00105$
00141$:
;C:/GB/ZGB/common/src/Scroll.c:446: for(yt = start_y; yt != start_y + h; ++ yt) {
	ldhl	sp,	#14
	inc	(hl)
	jr	NZ,00142$
	inc	hl
	inc	(hl)
00142$:
	ldhl	sp,	#14
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	jp	00107$
00111$:
;C:/GB/ZGB/common/src/Scroll.c:445: for(xt = start_x; xt != start_x + w; ++ xt) {
	ldhl	sp,	#12
	inc	(hl)
	jr	NZ,00143$
	inc	hl
	inc	(hl)
00143$:
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#3
	ld	(hl+), a
	ld	(hl), e
	jp	00110$
00104$:
;C:/GB/ZGB/common/src/Scroll.c:452: found = 0;
	xor	a, a
	ldhl	sp,	#2
	ld	(hl), a
;C:/GB/ZGB/common/src/Scroll.c:454: done:
00105$:
;C:/GB/ZGB/common/src/Scroll.c:455: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/Scroll.c:456: *x = xt;
	ldhl	sp,#(26 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#3
	ld	a, (hl+)
	ld	(bc), a
	inc	bc
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/Scroll.c:457: *y = yt;
	ldhl	sp,#(28 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#0
	ld	a, (hl+)
	ld	(bc), a
	inc	bc
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/Scroll.c:459: return found;
	inc	hl
	ld	e, (hl)
;C:/GB/ZGB/common/src/Scroll.c:460: }
	add	sp, #16
	ret
	.area _CODE
	.area _CABS (ABS)
