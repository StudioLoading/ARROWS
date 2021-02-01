;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module SpriteManager
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _SetBank
	.globl _PopBank
	.globl _PushBank
	.globl _RefreshScroll
	.globl _DrawSprite
	.globl _InitSprite
	.globl _ClearOAMs
	.globl _SwapOAMs
	.globl _LoadSprite
	.globl _VectorRemovePos
	.globl _VectorAdd
	.globl _THIS
	.globl _THIS_IDX
	.globl _cachedSprite
	.globl _sprite_manager_removal_check
	.globl _sprite_manager_updatables
	.globl _sprite_manager_sprites_pool
	.globl _sprite_manager_sprites_poolSTACK
	.globl _sprite_manager_sprites
	.globl _sprite_manager_sprites_mem
	.globl _SpriteManagerReset
	.globl _SpriteManagerLoad
	.globl _SpriteManagerAdd
	.globl _SpriteManagerRemove
	.globl _SpriteManagerRemoveSprite
	.globl _SpriteManagerFlushRemove
	.globl _SpriteManagerUpdate
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_sprite_manager_sprites_mem::
	.ds 660
_sprite_manager_sprites::
	.ds 40
_sprite_manager_sprites_poolSTACK::
	.ds 20
_sprite_manager_sprites_pool::
	.ds 2
_sprite_manager_updatables::
	.ds 21
_sprite_manager_removal_check::
	.ds 1
_cachedSprite::
	.ds 2
_THIS_IDX::
	.ds 1
_THIS::
	.ds 2
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
;C:/GB/ZGB/common/src/SpriteManager.c:11: DECLARE_STACK(sprite_manager_sprites_pool, N_SPRITE_MANAGER_SPRITES);
	ld	hl, #_sprite_manager_sprites_pool
	ld	(hl), #<((_sprite_manager_sprites_poolSTACK - 0x0001))
	inc	hl
	ld	(hl), #>((_sprite_manager_sprites_poolSTACK - 0x0001))
;C:/GB/ZGB/common/src/SpriteManager.c:14: DECLARE_VECTOR(sprite_manager_updatables, N_SPRITE_MANAGER_SPRITES);
	ld	hl, #_sprite_manager_updatables
	ld	(hl), #0x00
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;C:/GB/ZGB/common/src/SpriteManager.c:18: void SpriteManagerReset() {
;	---------------------------------
; Function SpriteManagerReset
; ---------------------------------
_SpriteManagerReset::
	add	sp, #-3
;C:/GB/ZGB/common/src/SpriteManager.c:22: for(i = 0u; i != sprite_manager_updatables[0]; ++ i) {
	xor	a, a
	ldhl	sp,	#2
	ld	(hl), a
00104$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, c
	jp	Z,00101$
;C:/GB/ZGB/common/src/SpriteManager.c:23: THIS = sprite_manager_sprites[sprite_manager_updatables[i + 1]];
	ldhl	sp,	#2
	ld	a, (hl)
	inc	a
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
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
	ld	hl, #_THIS
	ld	(hl+), a
	inc	de
	ld	a, (de)
;C:/GB/ZGB/common/src/SpriteManager.c:24: PUSH_BANK(spriteBanks[THIS->type]);
	ld	(hl-), a
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0011
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	add	a, #<(_spriteBanks)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_spriteBanks)
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/SpriteManager.c:25: spriteDestroyFuncs[THIS->type]();
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0011
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_spriteDestroyFuncs
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	call	___sdcc_call_hl
;C:/GB/ZGB/common/src/SpriteManager.c:26: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/SpriteManager.c:22: for(i = 0u; i != sprite_manager_updatables[0]; ++ i) {
	ldhl	sp,	#2
	inc	(hl)
	jp	00104$
00101$:
;C:/GB/ZGB/common/src/SpriteManager.c:30: StackClear(sprite_manager_sprites_pool);
	ld	hl, #_sprite_manager_sprites_pool
	ld	(hl), #<((_sprite_manager_sprites_poolSTACK - 0x0001))
	inc	hl
	ld	(hl), #>((_sprite_manager_sprites_poolSTACK - 0x0001))
;C:/GB/ZGB/common/src/SpriteManager.c:31: for(i = 0; i != N_SPRITE_MANAGER_SPRITES; ++i) {
	xor	a, a
	ldhl	sp,	#2
	ld	(hl), a
00106$:
;C:/GB/ZGB/common/src/SpriteManager.c:32: sprite_manager_sprites[i] = (struct Sprite*)&sprite_manager_sprites_mem[sizeof(struct Sprite) * (UINT16)i];
	ldhl	sp,	#2
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_sprite_manager_sprites
	add	hl, bc
	inc	sp
	inc	sp
	push	hl
	ldhl	sp,	#2
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	hl, #_sprite_manager_sprites_mem
	add	hl, bc
	ld	c, l
	ld	a, h
	ld	b, a
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/SpriteManager.c:33: StackPush(sprite_manager_sprites_pool, i);		
	ld	hl, #_sprite_manager_sprites_pool
	inc	(hl)
	jr	NZ,00139$
	inc	hl
	inc	(hl)
00139$:
	ld	hl, #_sprite_manager_sprites_pool + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#2
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:31: for(i = 0; i != N_SPRITE_MANAGER_SPRITES; ++i) {
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x14
	jp	NZ,00106$
;C:/GB/ZGB/common/src/SpriteManager.c:35: ClearOAMs();
	call	_ClearOAMs
;C:/GB/ZGB/common/src/SpriteManager.c:38: sprite_manager_updatables[0] = 0;
	ld	hl, #_sprite_manager_updatables
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/SpriteManager.c:39: sprite_manager_removal_check = 0;
	ld	hl, #_sprite_manager_removal_check
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/SpriteManager.c:40: }
	add	sp, #3
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:42: void SpriteManagerLoad(UINT8 sprite_type) {
;	---------------------------------
; Function SpriteManagerLoad
; ---------------------------------
_SpriteManagerLoad::
	add	sp, #-2
;C:/GB/ZGB/common/src/SpriteManager.c:43: PUSH_BANK(spriteDataBanks[sprite_type])
	ld	bc, #_spriteDataBanks+0
	ldhl	sp,	#4
	ld	l, (hl)
	ld	h, #0x00
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/SpriteManager.c:44: spriteIdxs[sprite_type] = LoadSprite(spriteDatas[sprite_type]);
	ld	de, #_spriteIdxs
	ldhl	sp,	#4
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	inc	sp
	inc	sp
	push	hl
	ldhl	sp,	#4
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_spriteDatas
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	call	_LoadSprite
	add	sp, #2
	ld	c, e
	pop	hl
	push	hl
	ld	(hl), c
;C:/GB/ZGB/common/src/SpriteManager.c:45: POP_BANK
	call	_PopBank
;C:/GB/ZGB/common/src/SpriteManager.c:46: }
	add	sp, #2
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:49: struct Sprite* SpriteManagerAdd(UINT8 sprite_type, UINT16 x, UINT16 y) {
;	---------------------------------
; Function SpriteManagerAdd
; ---------------------------------
_SpriteManagerAdd::
	add	sp, #-7
;C:/GB/ZGB/common/src/SpriteManager.c:54: sprite_idx = StackPop(sprite_manager_sprites_pool);
	ld	hl, #_sprite_manager_sprites_pool + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	ldhl	sp,	#6
	ld	(hl), a
	ld	hl, #_sprite_manager_sprites_pool + 1
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	dec	de
	dec	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/SpriteManager.c:55: sprite = sprite_manager_sprites[sprite_idx];
	ldhl	sp,	#6
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
;C:/GB/ZGB/common/src/SpriteManager.c:56: sprite->type = sprite_type;
	pop	de
	push	de
	ld	hl, #0x0011
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), d
	pop	bc
	pop	de
	push	de
	push	bc
	ldhl	sp,	#9
	ld	a, (hl)
	ld	(de), a
;C:/GB/ZGB/common/src/SpriteManager.c:57: sprite->marked_for_removal = 0;
	pop	de
	push	de
	ld	hl, #0x0012
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:58: sprite->lim_x = 32u;
	pop	de
	push	de
	ld	hl, #0x0013
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, #0x20
	ld	(bc), a
	inc	bc
	ld	a, #0x00
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:59: sprite->lim_y = 32u;
	pop	de
	push	de
	ld	hl, #0x0015
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, #0x20
	ld	(bc), a
	inc	bc
	ld	a, #0x00
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:60: sprite->flags = 0;
	pop	de
	push	de
	ld	hl, #0x000c
	add	hl, de
	ld	c, l
	ld	b, h
	xor	a, a
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:62: VectorAdd(sprite_manager_updatables, sprite_idx);
	ldhl	sp,	#6
	ld	a, (hl)
	push	af
	inc	sp
	ld	hl, #_sprite_manager_updatables
	push	hl
	call	_VectorAdd
	add	sp, #3
;C:/GB/ZGB/common/src/SpriteManager.c:64: PUSH_BANK(spriteDataBanks[sprite->type]);
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	add	a, #<(_spriteDataBanks)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_spriteDataBanks)
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/SpriteManager.c:65: InitSprite(sprite, spriteDatas[sprite_type]->height == 8 ? 0 : spriteDatas[sprite_type]->width >> 3, spriteIdxs[sprite_type]);
	ld	bc, #_spriteIdxs+0
	ldhl	sp,	#9
	ld	l, (hl)
	ld	h, #0x00
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	ldhl	sp,	#4
	ld	(hl), a
	ldhl	sp,	#9
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_spriteDatas
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0001
	add	hl, bc
	ld	a, l
	ld	d, h
	ldhl	sp,	#5
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	sub	a, #0x08
	jr	NZ,00103$
	ld	d, #0x00
	ld	b, #0x00
	jr	00104$
00103$:
	ld	a, (bc)
	swap	a
	rlca
	and	a, #0x1f
	ld	d, a
	ld	b, #0x00
00104$:
	ldhl	sp,	#4
	ld	a, (hl)
	push	af
	inc	sp
	push	de
	inc	sp
	pop	bc
	pop	hl
	push	hl
	push	bc
	push	hl
	call	_InitSprite
	add	sp, #4
;C:/GB/ZGB/common/src/SpriteManager.c:66: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/SpriteManager.c:67: sprite->x = x;
	pop	de
	push	de
	ld	hl, #0x0008
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#10
	ld	a, (hl+)
	ld	(bc), a
	inc	bc
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:68: sprite->y = y;
	pop	de
	push	de
	ld	hl, #0x000a
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#12
	ld	a, (hl+)
	ld	(bc), a
	inc	bc
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:71: cachedSprite = THIS;
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_cachedSprite
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/SpriteManager.c:72: spriteIdxTmp = THIS_IDX;
	push	hl
	ld	hl, #_THIS_IDX
	ld	a, (hl)
	ldhl	sp,	#8
	ld	(hl), a
	pop	hl
;C:/GB/ZGB/common/src/SpriteManager.c:73: THIS = sprite;
	ldhl	sp,	#0
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_THIS
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/SpriteManager.c:74: THIS_IDX = sprite_manager_updatables[0] - 1;
	ld	a, (#_sprite_manager_updatables + 0)
	add	a, #0xff
	ld	hl, #_THIS_IDX
	ld	(hl), a
;C:/GB/ZGB/common/src/SpriteManager.c:75: PUSH_BANK(spriteBanks[sprite->type]);
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	add	a, #<(_spriteBanks)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_spriteBanks)
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/SpriteManager.c:76: spriteStartFuncs[sprite->type]();
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_spriteStartFuncs
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	call	___sdcc_call_hl
;C:/GB/ZGB/common/src/SpriteManager.c:77: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/SpriteManager.c:79: THIS = cachedSprite;
	ld	hl, #_cachedSprite
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_THIS
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/SpriteManager.c:80: THIS_IDX = spriteIdxTmp;
	push	hl
	ldhl	sp,	#8
	ld	a, (hl)
	ld	hl, #_THIS_IDX
	ld	(hl), a
	pop	hl
;C:/GB/ZGB/common/src/SpriteManager.c:81: return sprite;
	pop	de
	push	de
;C:/GB/ZGB/common/src/SpriteManager.c:82: }
	add	sp, #7
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:84: void SpriteManagerRemove(int idx) {
;	---------------------------------
; Function SpriteManagerRemove
; ---------------------------------
_SpriteManagerRemove::
;C:/GB/ZGB/common/src/SpriteManager.c:85: sprite_manager_removal_check = 1;
	ld	hl, #_sprite_manager_removal_check
	ld	(hl), #0x01
;C:/GB/ZGB/common/src/SpriteManager.c:86: sprite_manager_sprites[sprite_manager_updatables[idx + 1]]->marked_for_removal = 1;
	ldhl	sp,	#2
	ld	a, (hl)
	inc	a
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
	ld	hl, #_sprite_manager_updatables
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
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
	ld	hl, #0x0012
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	(hl), #0x01
;C:/GB/ZGB/common/src/SpriteManager.c:87: }
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:89: void SpriteManagerRemoveSprite(struct Sprite* sprite) {
;	---------------------------------
; Function SpriteManagerRemoveSprite
; ---------------------------------
_SpriteManagerRemoveSprite::
	add	sp, #-2
;C:/GB/ZGB/common/src/SpriteManager.c:92: for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
	xor	a, a
	ldhl	sp,	#0
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
00105$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ldhl	sp,	#1
	ld	a, (hl)
	sub	a, c
	jp	Z,00107$
;C:/GB/ZGB/common/src/SpriteManager.c:93: s = sprite_manager_sprites[sprite_manager_updatables[i + 1]];
	ldhl	sp,	#1
	ld	a, (hl)
	inc	a
	ld	c, a
	rla
	sbc	a, a
	ld	b, a
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
;C:/GB/ZGB/common/src/SpriteManager.c:94: if(s == sprite) {
	ldhl	sp,	#4
	ld	a, (hl)
	sub	a, c
	jr	NZ,00106$
	inc	hl
	ld	a, (hl)
	sub	a, b
	jr	NZ,00106$
;C:/GB/ZGB/common/src/SpriteManager.c:95: SpriteManagerRemove(i);
	ldhl	sp,	#0
	ld	c, (hl)
	ld	b, #0x00
	push	bc
	call	_SpriteManagerRemove
	add	sp, #2
;C:/GB/ZGB/common/src/SpriteManager.c:96: break;
	jr	00107$
00106$:
;C:/GB/ZGB/common/src/SpriteManager.c:92: for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
	ldhl	sp,	#1
	inc	(hl)
	ld	a, (hl-)
	ld	(hl), a
	jp	00105$
00107$:
;C:/GB/ZGB/common/src/SpriteManager.c:99: }
	add	sp, #2
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:101: void SpriteManagerFlushRemove() {
;	---------------------------------
; Function SpriteManagerFlushRemove
; ---------------------------------
_SpriteManagerFlushRemove::
	add	sp, #-2
;C:/GB/ZGB/common/src/SpriteManager.c:103: for(THIS_IDX = sprite_manager_updatables[0] - 1u; (UINT8)(THIS_IDX + 1u) != 0u; THIS_IDX --) {
	ld	a, (#_sprite_manager_updatables + 0)
	add	a, #0xff
	ld	hl, #_THIS_IDX
	ld	(hl), a
00105$:
	ld	hl, #_THIS_IDX
	ld	c, (hl)
	inc	c
	ld	a, c
	or	a, a
	jp	Z, 00103$
;C:/GB/ZGB/common/src/SpriteManager.c:104: THIS = sprite_manager_sprites[sprite_manager_updatables[THIS_IDX + 1u]];
	ld	e, c
	ld	d, #0x00
	ld	hl, #_sprite_manager_updatables
	add	hl, de
	inc	sp
	inc	sp
	push	hl
	pop	de
	push	de
	ld	a,(de)
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
	ld	hl, #_THIS
	ld	(hl+), a
	inc	de
	ld	a, (de)
;C:/GB/ZGB/common/src/SpriteManager.c:105: if(THIS->marked_for_removal) {
	ld	(hl-), a
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0012
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	a, (bc)
	or	a, a
	jp	Z, 00106$
;C:/GB/ZGB/common/src/SpriteManager.c:106: StackPush(sprite_manager_sprites_pool, sprite_manager_updatables[THIS_IDX + 1u]);
	ld	hl, #_sprite_manager_sprites_pool
	inc	(hl)
	jr	NZ,00126$
	inc	hl
	inc	(hl)
00126$:
	ld	hl, #_sprite_manager_sprites_pool + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	pop	de
	push	de
	ld	a,(de)
	ld	(bc), a
;C:/GB/ZGB/common/src/SpriteManager.c:107: VectorRemovePos(sprite_manager_updatables, THIS_IDX);
	ld	hl, #_THIS_IDX
	ld	a, (hl)
	push	af
	inc	sp
	ld	hl, #_sprite_manager_updatables
	push	hl
	call	_VectorRemovePos
	add	sp, #3
;C:/GB/ZGB/common/src/SpriteManager.c:109: PUSH_BANK(spriteBanks[THIS->type]);
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
	add	a, #<(_spriteBanks)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_spriteBanks)
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/SpriteManager.c:110: spriteDestroyFuncs[THIS->type]();
	ld	hl, #_THIS + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #0x0011
	add	hl, bc
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_spriteDestroyFuncs
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	call	___sdcc_call_hl
;C:/GB/ZGB/common/src/SpriteManager.c:111: POP_BANK;
	call	_PopBank
00106$:
;C:/GB/ZGB/common/src/SpriteManager.c:103: for(THIS_IDX = sprite_manager_updatables[0] - 1u; (UINT8)(THIS_IDX + 1u) != 0u; THIS_IDX --) {
	ld	hl, #_THIS_IDX
	dec	(hl)
	jp	00105$
00103$:
;C:/GB/ZGB/common/src/SpriteManager.c:114: sprite_manager_removal_check = 0;
	ld	hl, #_sprite_manager_removal_check
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/SpriteManager.c:115: }
	add	sp, #2
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:117: void SetBank(UINT8 bank)
;	---------------------------------
; Function SetBank
; ---------------------------------
_SetBank::
;C:/GB/ZGB/common/src/SpriteManager.c:127: __endasm;
	ldhl	sp, #2
	ld	a, (hl)
	ld	(#__current_bank), a
	ld	(#0x2000), a
;C:/GB/ZGB/common/src/SpriteManager.c:128: }
	ret
;C:/GB/ZGB/common/src/SpriteManager.c:135: void SpriteManagerUpdate() {
;	---------------------------------
; Function SpriteManagerUpdate
; ---------------------------------
_SpriteManagerUpdate::
	add	sp, #-2
;C:/GB/ZGB/common/src/SpriteManager.c:136: SPRITEMANAGER_ITERATE(THIS_IDX, THIS) {
	ld	hl, #_THIS_IDX
	ld	(hl), #0x00
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
	ld	hl, #_THIS
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
00109$:
	ld	hl, #_sprite_manager_updatables + 0
	ld	c, (hl)
	ld	hl, #_THIS_IDX
	ld	a, (hl)
	sub	a, c
	jp	Z,00105$
;C:/GB/ZGB/common/src/SpriteManager.c:137: if(!THIS->marked_for_removal) {
	ld	hl, #_THIS
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	ld	(hl), e
	pop	de
	push	de
	ld	hl, #0x0012
	add	hl, de
	ld	c,l
	ld	a,h
	ld	c, (hl)
	ld	a, c
	or	a, a
	jp	NZ, 00110$
;C:/GB/ZGB/common/src/SpriteManager.c:139: SetBank(spriteBanks[THIS->type]);
	pop	de
	push	de
	ld	hl, #0x0011
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, (bc)
	add	a, #<(_spriteBanks)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_spriteBanks)
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_SetBank
	inc	sp
;C:/GB/ZGB/common/src/SpriteManager.c:141: spriteUpdateFuncs[THIS->type]();
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
	ld	c, a
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_spriteUpdateFuncs
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	call	___sdcc_call_hl
;C:/GB/ZGB/common/src/SpriteManager.c:143: if(THIS == scroll_target)
	ld	hl, #_THIS
	ld	a, (hl)
	ld	hl, #_scroll_target
	sub	a, (hl)
	jr	NZ,00102$
	ld	hl, #_THIS + 1
	ld	a, (hl)
	ld	hl, #_scroll_target + 1
	sub	a, (hl)
	jr	NZ,00102$
;C:/GB/ZGB/common/src/SpriteManager.c:144: RefreshScroll();
	call	_RefreshScroll
00102$:
;C:/GB/ZGB/common/src/SpriteManager.c:146: DrawSprite(); //this needs to be done using the sprite bank because the animation array is stored there
	call	_DrawSprite
00110$:
;C:/GB/ZGB/common/src/SpriteManager.c:136: SPRITEMANAGER_ITERATE(THIS_IDX, THIS) {
	ld	hl, #_THIS_IDX
	inc	(hl)
	ld	a, (hl)
	inc	a
	add	a, #<(_sprite_manager_updatables)
	ld	c, a
	ld	a, #0x00
	adc	a, #>(_sprite_manager_updatables)
	ld	l, c
	ld	h, a
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
	ld	hl, #_THIS
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	jp	00109$
00105$:
;C:/GB/ZGB/common/src/SpriteManager.c:150: SwapOAMs();
	call	_SwapOAMs
;C:/GB/ZGB/common/src/SpriteManager.c:152: if(sprite_manager_removal_check) {
	ld	hl, #_sprite_manager_removal_check
	ld	a, (hl)
	or	a, a
	jr	Z,00111$
;C:/GB/ZGB/common/src/SpriteManager.c:153: SpriteManagerFlushRemove();
	call	_SpriteManagerFlushRemove
00111$:
;C:/GB/ZGB/common/src/SpriteManager.c:155: }
	add	sp, #2
	ret
	.area _CODE
	.area _CABS (ABS)
