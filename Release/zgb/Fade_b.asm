;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Fade_b
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _FadeOut_b
	.globl _FadeOutColor
	.globl _FadeOutDMG
	.globl _FadeIn_b
	.globl _FadeInCOLOR
	.globl _FadeStepColor
	.globl _UpdateColor
	.globl _FadeInDMG
	.globl _FadeDMG
	.globl _FadeInOp
	.globl _DespRight
	.globl _delay
	.globl _set_sprite_palette
	.globl _set_bkg_palette
	.globl _ZGB_Fading_SPal
	.globl _ZGB_Fading_BPal
	.globl _fade_bank
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_fade_bank::
	.ds 1
_ZGB_Fading_BPal::
	.ds 64
_ZGB_Fading_SPal::
	.ds 64
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
;C:/GB/ZGB/common/src/Fade_b.c:3: UINT8 fade_bank = 1;
	ld	hl, #_fade_bank
	ld	(hl), #0x01
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_1
;C:/GB/ZGB/common/src/Fade_b.c:12: UINT8 FadeInOp(UINT16 c, UINT16 i) {
;	---------------------------------
; Function FadeInOp
; ---------------------------------
_FadeInOp::
;C:/GB/ZGB/common/src/Fade_b.c:13: return U_LESS_THAN(c, i) ? 0: (c - i);
	ldhl	sp,#(3 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	inc	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ld	c, e
	bit	7, a
	jr	Z,00103$
	ld	de, #0x0000
	ret
00103$:
	ldhl	sp,	#2
	ld	a, (hl+)
	inc	hl
	ld	c, (hl)
	sub	a, c
	ld	e, a
	ld	d, #0x00
;C:/GB/ZGB/common/src/Fade_b.c:14: }
	ret
;C:/GB/ZGB/common/src/Fade_b.c:16: void FadeDMG(UINT8 fadeout) {
;	---------------------------------
; Function FadeDMG
; ---------------------------------
_FadeDMG::
	add	sp, #-35
;C:/GB/ZGB/common/src/Fade_b.c:18: UINT8* pals[] = {(UINT8*)0xFF47, (UINT8*)0xFF48, (UINT8*)0xFF49};
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
	ld	(hl), #0x47
	inc	hl
	ld	(hl), #0xff
	ldhl	sp,#(21 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, #0x48
	ld	(bc), a
	inc	bc
	ld	a, #0xff
	ld	(bc), a
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0004
	add	hl, de
	ld	c, l
	ld	b, h
	ld	a, #0x49
	ld	(bc), a
	inc	bc
	ld	a, #0xff
	ld	(bc), a
;C:/GB/ZGB/common/src/Fade_b.c:20: UINT8* c = colors;
	ldhl	sp,	#2
	ld	a, l
	ld	d, h
	ldhl	sp,	#22
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#32
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/Fade_b.c:24: for(i = 0; i != 3; ++i) {
	xor	a, a
	inc	hl
	ld	(hl), a
00107$:
;C:/GB/ZGB/common/src/Fade_b.c:25: p = (UINT8)*(pals[i]);
	ldhl	sp,	#34
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ldhl	sp,	#20
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	ldhl	sp,	#30
	ld	(hl), a
;C:/GB/ZGB/common/src/Fade_b.c:26: for(j = 0; j != 8; j += 2, ++c) {
	xor	a, a
	inc	hl
	ld	(hl+), a
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
00105$:
;C:/GB/ZGB/common/src/Fade_b.c:27: *c = (DespRight(p, j)) & 0x3;
	ldhl	sp,	#31
	ld	a, (hl+)
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,	#30
	ld	e, (hl)
	ld	d, #0x00
	push	bc
	inc	hl
	inc	hl
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	de
	call	_DespRight
	add	sp, #4
	pop	bc
	ld	a, e
	and	a, #0x03
	ld	(bc), a
;C:/GB/ZGB/common/src/Fade_b.c:26: for(j = 0; j != 8; j += 2, ++c) {
	ldhl	sp,	#31
	ld	a, (hl)
	add	a, #0x02
	ld	(hl), a
	inc	bc
	ld	a, (hl)
	sub	a, #0x08
	jp	NZ,00105$
;C:/GB/ZGB/common/src/Fade_b.c:24: for(i = 0; i != 3; ++i) {
	ldhl	sp,	#32
	ld	(hl), c
	inc	hl
	ld	(hl), b
	inc	hl
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x03
	jp	NZ,00107$
;C:/GB/ZGB/common/src/Fade_b.c:31: for(i = 0; i != 4; ++i) {
	xor	a, a
	ldhl	sp,	#33
	ld	(hl), a
00111$:
;C:/GB/ZGB/common/src/Fade_b.c:32: p = fadeout ? 3 - i : i;
	ldhl	sp,	#37
	ld	a, (hl)
	or	a, a
	jr	Z,00115$
	ldhl	sp,	#33
	ld	c, (hl)
	ld	a, #0x03
	sub	a, c
	jr	00116$
00115$:
	ldhl	sp,	#33
	ld	a, (hl)
00116$:
	ldhl	sp,	#31
	ld	(hl), a
;C:/GB/ZGB/common/src/Fade_b.c:33: for(j = 0; j != 3; ++j) {
	xor	a, a
	ldhl	sp,	#34
	ld	(hl), a
00109$:
;C:/GB/ZGB/common/src/Fade_b.c:34: c = &colors[j << 2];
	ldhl	sp,	#34
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	sla	(hl)
	sla	(hl)
	ld	a, (hl)
	ldhl	sp,	#29
	ld	(hl), a
	rla
	sbc	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,#(23 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#29
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	c, l
	ld	b, h
	ldhl	sp,	#24
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Fade_b.c:35: *pals[j] = PAL_DEF(FadeInOp(c[0], p), FadeInOp(c[1], p), FadeInOp(c[2], p), FadeInOp(c[3], p));
	ldhl	sp,	#34
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ldhl	sp,	#20
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, bc
	ld	c, l
	ld	b, h
	ld	e, c
	ld	d, b
	ld	a,(de)
	ldhl	sp,	#26
	ld	(hl+), a
	inc	de
	ld	a, (de)
	ld	(hl), a
	ldhl	sp,	#31
	ld	a, (hl)
	ldhl	sp,	#28
	ld	(hl), a
	xor	a, a
	inc	hl
	ld	(hl), a
	ldhl	sp,#(25 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#28
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_FadeInOp
	add	sp, #4
	ld	a, e
	swap	a
	and	a, #0xf0
	add	a, a
	add	a, a
	ldhl	sp,	#32
	ld	(hl), a
	ldhl	sp,#(25 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	ld	a, (bc)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#28
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_FadeInOp
	add	sp, #4
	ld	a, e
	swap	a
	and	a, #0xf0
	ld	c, a
	ldhl	sp,	#32
	ld	a, (hl-)
	dec	hl
	ld	(hl+), a
	inc	hl
	ld	(hl), c
	ld	a, (hl-)
	dec	hl
	or	a, (hl)
	inc	hl
	inc	hl
	ld	(hl), a
	ldhl	sp,#(25 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0001
	add	hl, de
	inc	sp
	inc	sp
	push	hl
	pop	de
	push	de
	ld	a,(de)
	ld	c, a
	ld	b, #0x00
	ldhl	sp,	#28
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_FadeInOp
	add	sp, #4
	ld	a, e
	add	a, a
	add	a, a
	ldhl	sp,	#32
	or	a, (hl)
	ld	c, a
	ldhl	sp,#(25 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	e, a
	ld	d, #0x00
	push	bc
	ldhl	sp,	#30
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	de
	call	_FadeInOp
	add	sp, #4
	ld	a, e
	pop	bc
	or	a, c
	ld	c, a
	ldhl	sp,	#26
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
;C:/GB/ZGB/common/src/Fade_b.c:33: for(j = 0; j != 3; ++j) {
	ldhl	sp,	#34
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x03
	jp	NZ,00109$
;C:/GB/ZGB/common/src/Fade_b.c:37: delay(50);
	ld	hl, #0x0032
	push	hl
	call	_delay
	add	sp, #2
;C:/GB/ZGB/common/src/Fade_b.c:31: for(i = 0; i != 4; ++i) {
	ldhl	sp,	#33
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x04
	jp	NZ,00111$
;C:/GB/ZGB/common/src/Fade_b.c:39: }
	add	sp, #35
	ret
;C:/GB/ZGB/common/src/Fade_b.c:41: void FadeInDMG() {
;	---------------------------------
; Function FadeInDMG
; ---------------------------------
_FadeInDMG::
;C:/GB/ZGB/common/src/Fade_b.c:42: FadeDMG(0);
	xor	a, a
	push	af
	inc	sp
	call	_FadeDMG
	inc	sp
;C:/GB/ZGB/common/src/Fade_b.c:43: }
	ret
;C:/GB/ZGB/common/src/Fade_b.c:45: UWORD UpdateColor(UINT8 i, UWORD col) {
;	---------------------------------
; Function UpdateColor
; ---------------------------------
_UpdateColor::
	add	sp, #-4
;C:/GB/ZGB/common/src/Fade_b.c:47: return RGB2(PAL_RED(col) | DespRight(0x1F, 5 - i), PAL_GREEN(col) | DespRight(0x1F, 5 - i), PAL_BLUE(col) | DespRight(0x1F, 5 - i));
	ldhl	sp,	#7
	ld	a, (hl)
	and	a, #0x1f
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), #0x00
	ldhl	sp,	#6
	ld	c, (hl)
	ld	b, #0x00
	ld	a, #0x05
	sub	a, c
	ld	c, a
	ld	a, #0x00
	sbc	a, b
	ld	b, a
	push	bc
	push	bc
	ld	hl, #0x001f
	push	hl
	call	_DespRight
	add	sp, #4
	pop	bc
	ldhl	sp,	#2
	ld	a, (hl)
	or	a, e
	dec	hl
	dec	hl
	ld	(hl), a
	ldhl	sp,	#3
	ld	a, (hl)
	or	a, d
	dec	hl
	dec	hl
	ld	(hl), a
	ldhl	sp,#(8 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	srl	d
	rr	e
	ld	a, e
	and	a, #0x1f
	ldhl	sp,	#2
	ld	(hl+), a
	ld	(hl), #0x00
	push	bc
	push	bc
	ld	hl, #0x001f
	push	hl
	call	_DespRight
	add	sp, #4
	pop	bc
	ld	a, e
	ldhl	sp,	#2
	or	a, (hl)
	ld	e, a
	ld	a, d
	inc	hl
	or	a, (hl)
	ld	d, a
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	sla	e
	rl	d
	ldhl	sp,	#0
	ld	a, (hl)
	or	a, e
	inc	hl
	inc	hl
	ld	(hl-), a
	ld	a, (hl)
	or	a, d
	inc	hl
	inc	hl
	ld	(hl), a
	ldhl	sp,	#8
	ld	a, (hl)
	rrca
	rrca
	and	a, #0x3f
	ld	e, a
	ld	d, #0x00
	ld	a, e
	and	a, #0x1f
	ld	e, a
	ld	d, #0x00
	push	de
	push	bc
	ld	hl, #0x001f
	push	hl
	call	_DespRight
	add	sp, #4
	ld	c, e
	ld	b, d
	pop	de
	ld	a, c
	or	a, e
	ld	c, a
	ld	a, b
	or	a, d
	ld	b, a
	ld	b, #0x00
	sla	b
	rl	c
	sla	b
	rl	c
	ldhl	sp,	#2
	ld	a, (hl)
	or	a, b
	ld	e, a
	inc	hl
	ld	a, (hl)
	or	a, c
	ld	d, a
;C:/GB/ZGB/common/src/Fade_b.c:48: }
	add	sp, #4
	ret
;C:/GB/ZGB/common/src/Fade_b.c:50: void FadeStepColor(UINT8 i) {
;	---------------------------------
; Function FadeStepColor
; ---------------------------------
_FadeStepColor::
	add	sp, #-34
;C:/GB/ZGB/common/src/Fade_b.c:54: UWORD* col = ZGB_Fading_BPal;
	ld	bc, #_ZGB_Fading_BPal+0
;C:/GB/ZGB/common/src/Fade_b.c:55: UWORD* col_s = ZGB_Fading_SPal;
	ldhl	sp,	#32
	ld	(hl), #<(_ZGB_Fading_SPal)
	inc	hl
	ld	(hl), #>(_ZGB_Fading_SPal)
;C:/GB/ZGB/common/src/Fade_b.c:57: for(pal = 0; pal < 8; pal ++) {
	ldhl	sp,	#0
	ld	a, l
	ld	d, h
	ldhl	sp,	#16
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#8
	ld	a, l
	ld	d, h
	ldhl	sp,	#18
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#20
	ld	(hl+), a
	ld	(hl), e
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#22
	ld	(hl+), a
	ld	(hl), e
	xor	a, a
	ldhl	sp,	#28
	ld	(hl), a
;C:/GB/ZGB/common/src/Fade_b.c:58: for(c = 0; c < 4; ++c, ++col, ++col_s) {
00109$:
	xor	a, a
	ldhl	sp,	#29
	ld	(hl+), a
	ld	(hl), c
	inc	hl
	ld	(hl), b
00103$:
;C:/GB/ZGB/common/src/Fade_b.c:59: palette[c] = UpdateColor(i, *col);
	ldhl	sp,	#29
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ldhl	sp,	#24
	ld	(hl), c
	inc	hl
	ld	(hl), b
	dec	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#16
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#26
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,#(31 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	push	bc
	ldhl	sp,	#38
	ld	a, (hl)
	push	af
	inc	sp
	call	_UpdateColor
	add	sp, #3
	ld	c, e
	ld	b, d
	ldhl	sp,	#26
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Fade_b.c:60: palette_s[c] = UpdateColor(i, *col_s);
	ldhl	sp,#(25 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#18
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#26
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,#(33 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a,(de)
	ld	c, a
	inc	de
	ld	a,(de)
	ld	b, a
	push	bc
	ldhl	sp,	#38
	ld	a, (hl)
	push	af
	inc	sp
	call	_UpdateColor
	add	sp, #3
	ld	c, e
	ld	b, d
	ldhl	sp,	#26
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Fade_b.c:58: for(c = 0; c < 4; ++c, ++col, ++col_s) {
	ldhl	sp,	#29
	inc	(hl)
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#30
	ld	(hl+), a
	ld	(hl), d
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#32
	ld	(hl+), a
	ld	(hl), d
	ldhl	sp,	#29
	ld	a, (hl)
	sub	a, #0x04
	jp	C, 00103$
;C:/GB/ZGB/common/src/Fade_b.c:62: set_bkg_palette(pal, 1, palette);
	inc	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,#(21 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	bc
	push	de
	ld	a, #0x01
	push	af
	inc	sp
	ldhl	sp,	#33
	ld	a, (hl)
	push	af
	inc	sp
	call	_set_bkg_palette
	add	sp, #4
	pop	bc
;C:/GB/ZGB/common/src/Fade_b.c:63: set_sprite_palette(pal, 1, palette_s);
	ldhl	sp,#(23 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	bc
	push	de
	ld	a, #0x01
	push	af
	inc	sp
	ldhl	sp,	#33
	ld	a, (hl)
	push	af
	inc	sp
	call	_set_sprite_palette
	add	sp, #4
	pop	bc
;C:/GB/ZGB/common/src/Fade_b.c:57: for(pal = 0; pal < 8; pal ++) {
	ldhl	sp,	#28
	inc	(hl)
	ld	a, (hl)
	sub	a, #0x08
	jp	C, 00109$
;C:/GB/ZGB/common/src/Fade_b.c:65: delay(20);
	ld	hl, #0x0014
	push	hl
	call	_delay
	add	sp, #2
;C:/GB/ZGB/common/src/Fade_b.c:66: }
	add	sp, #34
	ret
;C:/GB/ZGB/common/src/Fade_b.c:68: void FadeInCOLOR() {
;	---------------------------------
; Function FadeInCOLOR
; ---------------------------------
_FadeInCOLOR::
;C:/GB/ZGB/common/src/Fade_b.c:70: for(i = 0; i != 6; i ++) {
	ld	b, #0x00
00102$:
;C:/GB/ZGB/common/src/Fade_b.c:71: FadeStepColor(i);	
	push	bc
	push	bc
	inc	sp
	call	_FadeStepColor
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Fade_b.c:70: for(i = 0; i != 6; i ++) {
	inc	b
	ld	a, b
	sub	a, #0x06
	jr	NZ,00102$
;C:/GB/ZGB/common/src/Fade_b.c:73: }
	ret
;C:/GB/ZGB/common/src/Fade_b.c:75: void FadeIn_b() {
;	---------------------------------
; Function FadeIn_b
; ---------------------------------
_FadeIn_b::
;C:/GB/ZGB/common/src/Fade_b.c:81: FadeInDMG();
;C:/GB/ZGB/common/src/Fade_b.c:82: }
	jp	_FadeInDMG
;C:/GB/ZGB/common/src/Fade_b.c:84: void FadeOutDMG() {
;	---------------------------------
; Function FadeOutDMG
; ---------------------------------
_FadeOutDMG::
;C:/GB/ZGB/common/src/Fade_b.c:85: FadeDMG(1);
	ld	a, #0x01
	push	af
	inc	sp
	call	_FadeDMG
	inc	sp
;C:/GB/ZGB/common/src/Fade_b.c:86: }
	ret
;C:/GB/ZGB/common/src/Fade_b.c:88: void FadeOutColor() {
;	---------------------------------
; Function FadeOutColor
; ---------------------------------
_FadeOutColor::
;C:/GB/ZGB/common/src/Fade_b.c:90: for(i = 5; i != 0xFF; -- i) {
	ld	b, #0x05
00102$:
;C:/GB/ZGB/common/src/Fade_b.c:91: FadeStepColor(i);	
	push	bc
	push	bc
	inc	sp
	call	_FadeStepColor
	inc	sp
	pop	bc
;C:/GB/ZGB/common/src/Fade_b.c:90: for(i = 5; i != 0xFF; -- i) {
	dec	b
	ld	a, b
	inc	a
	jr	NZ,00102$
;C:/GB/ZGB/common/src/Fade_b.c:93: }
	ret
;C:/GB/ZGB/common/src/Fade_b.c:95: void FadeOut_b() {
;	---------------------------------
; Function FadeOut_b
; ---------------------------------
_FadeOut_b::
;C:/GB/ZGB/common/src/Fade_b.c:101: FadeOutDMG();
;C:/GB/ZGB/common/src/Fade_b.c:102: }
	jp	_FadeOutDMG
	.area _CODE_1
	.area _CABS (ABS)
