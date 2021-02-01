;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module main
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _MusicUpdate
	.globl _InitSprites
	.globl _InitStates
	.globl _vbl_update
	.globl _FadeOut
	.globl _FadeIn
	.globl _PopBank
	.globl _PushBank
	.globl _SpriteManagerUpdate
	.globl _SpriteManagerReset
	.globl _gbt_enable_channels
	.globl _gbt_update
	.globl _gbt_loop
	.globl _gbt_stop
	.globl _gbt_play
	.globl _display_off
	.globl _wait_vbl_done
	.globl _set_interrupts
	.globl _disable_interrupts
	.globl _enable_interrupts
	.globl _joypad
	.globl _add_TIM
	.globl _add_VBL
	.globl _default_palette
	.globl _music_mute_frames
	.globl _old_scroll_y
	.globl _old_scroll_x
	.globl _vbl_count
	.globl _last_music
	.globl _state_running
	.globl _current_state
	.globl _delta_time
	.globl _SetState
	.globl _PlayMusic
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_delta_time::
	.ds 1
_current_state::
	.ds 1
_state_running::
	.ds 1
_last_music::
	.ds 2
_vbl_count::
	.ds 1
_old_scroll_x::
	.ds 2
_old_scroll_y::
	.ds 2
_music_mute_frames::
	.ds 1
_default_palette::
	.ds 8
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
;C:/GB/ZGB/common/src/main.c:22: UINT8 state_running = 0;
	ld	hl, #_state_running
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:29: void* last_music = 0;
	ld	hl, #_last_music
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:41: UINT8 music_mute_frames = 0;
	ld	hl, #_music_mute_frames
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:92: UINT16 default_palette[] = {RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0)};
	ld	hl, #_default_palette
	ld	(hl), #0xff
	inc	hl
	ld	(hl), #0x7f
	ld	hl, #(_default_palette + 0x0002)
	ld	(hl), #0x94
	inc	hl
	ld	(hl), #0x52
	ld	hl, #(_default_palette + 0x0004)
	ld	(hl), #0x4a
	inc	hl
	ld	(hl), #0x29
	ld	hl, #(_default_palette + 0x0006)
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;C:/GB/ZGB/common/src/main.c:24: void SetState(UINT8 state) {
;	---------------------------------
; Function SetState
; ---------------------------------
_SetState::
;C:/GB/ZGB/common/src/main.c:25: state_running = 0;
	ld	hl, #_state_running
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:26: next_state = state;
	push	hl
	ldhl	sp,	#4
	ld	a, (hl)
	ld	hl, #_next_state
	ld	(hl), a
	pop	hl
;C:/GB/ZGB/common/src/main.c:27: }
	ret
;C:/GB/ZGB/common/src/main.c:30: void PlayMusic(const unsigned char* music[], unsigned char bank, unsigned char loop) {
;	---------------------------------
; Function PlayMusic
; ---------------------------------
_PlayMusic::
;C:/GB/ZGB/common/src/main.c:31: if(music != last_music) {
	pop	bc
	pop	de
	push	de
	push	bc
	ld	hl, #_last_music + 1
	dec	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, c
	sub	a, e
	jr	NZ,00110$
	ld	a, b
	sub	a, d
	ret	Z
00110$:
;C:/GB/ZGB/common/src/main.c:32: last_music = music;
	pop	bc
	pop	de
	push	de
	push	bc
	dec	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/main.c:33: gbt_play(music, bank, 7);
	ld	a, #0x07
	push	af
	inc	sp
	ldhl	sp,	#5
	ld	a, (hl)
	push	af
	inc	sp
	push	de
	call	_gbt_play
	add	sp, #4
;C:/GB/ZGB/common/src/main.c:34: gbt_loop(loop);
	ldhl	sp,	#5
	ld	a, (hl)
	push	af
	inc	sp
	call	_gbt_loop
	inc	sp
;C:/GB/ZGB/common/src/main.c:35: REFRESH_BANK;
	ld	de, #0x2000
	ld	hl, #__current_bank
	ld	a, (hl)
	ld	(de), a
;C:/GB/ZGB/common/src/main.c:37: }
	ret
;C:/GB/ZGB/common/src/main.c:42: void vbl_update() {
;	---------------------------------
; Function vbl_update
; ---------------------------------
_vbl_update::
;C:/GB/ZGB/common/src/main.c:43: vbl_count ++;
	ld	hl, #_vbl_count
	inc	(hl)
;C:/GB/ZGB/common/src/main.c:47: if(old_scroll_x < scroll_x)
	ld	de, #_old_scroll_x
	ld	hl, #_scroll_x
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
	jr	Z,00147$
	bit	7, d
	jr	NZ,00148$
	cp	a, a
	jr	00148$
00147$:
	bit	7, d
	jr	Z,00148$
	scf
00148$:
	jr	NC,00104$
;C:/GB/ZGB/common/src/main.c:48: old_scroll_x += (scroll_x - old_scroll_x + 1) >> 1;
	ld	hl, #_scroll_x
	ld	a, (hl)
	ld	hl, #_old_scroll_x
	sub	a, (hl)
	ld	c, a
	ld	hl, #_scroll_x + 1
	ld	a, (hl)
	ld	hl, #_old_scroll_x + 1
	sbc	a, (hl)
	ld	b, a
	inc	bc
	sra	b
	rr	c
	dec	hl
	ld	a, (hl)
	add	a, c
	ld	(hl+), a
	ld	a, (hl)
	adc	a, b
	ld	(hl), a
	jp	00105$
00104$:
;C:/GB/ZGB/common/src/main.c:49: else if(old_scroll_x > scroll_x)
	ld	de, #_scroll_x
	ld	hl, #_old_scroll_x
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
	jr	Z,00149$
	bit	7, d
	jr	NZ,00150$
	cp	a, a
	jr	00150$
00149$:
	bit	7, d
	jr	Z,00150$
	scf
00150$:
	jr	NC,00105$
;C:/GB/ZGB/common/src/main.c:50: old_scroll_x -= (old_scroll_x - scroll_x + 1) >> 1;
	ld	hl, #_old_scroll_x
	ld	a, (hl)
	ld	hl, #_scroll_x
	sub	a, (hl)
	ld	c, a
	ld	hl, #_old_scroll_x + 1
	ld	a, (hl)
	ld	hl, #_scroll_x + 1
	sbc	a, (hl)
	ld	b, a
	inc	bc
	sra	b
	rr	c
	ld	hl, #_old_scroll_x
	ld	a, (hl)
	sub	a, c
	ld	(hl+), a
	ld	a, (hl)
	sbc	a, b
	ld	(hl), a
00105$:
;C:/GB/ZGB/common/src/main.c:51: SCX_REG = old_scroll_x + (scroll_offset_x << 3);
	ld	hl, #_old_scroll_x
	ld	c, (hl)
	ld	hl, #_scroll_offset_x
	ld	a, (hl)
	add	a, a
	add	a, a
	add	a, a
	add	a, c
	ldh	(_SCX_REG+0),a
;C:/GB/ZGB/common/src/main.c:53: if(old_scroll_y < scroll_y)
	ld	de, #_old_scroll_y
	ld	hl, #_scroll_y
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
	jr	NC,00109$
;C:/GB/ZGB/common/src/main.c:54: old_scroll_y += (scroll_y - old_scroll_y + 1) >> 1;
	ld	hl, #_scroll_y
	ld	a, (hl)
	ld	hl, #_old_scroll_y
	sub	a, (hl)
	ld	c, a
	ld	hl, #_scroll_y + 1
	ld	a, (hl)
	ld	hl, #_old_scroll_y + 1
	sbc	a, (hl)
	ld	b, a
	inc	bc
	sra	b
	rr	c
	dec	hl
	ld	a, (hl)
	add	a, c
	ld	(hl+), a
	ld	a, (hl)
	adc	a, b
	ld	(hl), a
	jp	00110$
00109$:
;C:/GB/ZGB/common/src/main.c:55: else if(old_scroll_y > scroll_y)
	ld	de, #_scroll_y
	ld	hl, #_old_scroll_y
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
	jr	Z,00153$
	bit	7, d
	jr	NZ,00154$
	cp	a, a
	jr	00154$
00153$:
	bit	7, d
	jr	Z,00154$
	scf
00154$:
	jr	NC,00110$
;C:/GB/ZGB/common/src/main.c:56: old_scroll_y -= (old_scroll_y - scroll_y + 1) >> 1;
	ld	hl, #_old_scroll_y
	ld	a, (hl)
	ld	hl, #_scroll_y
	sub	a, (hl)
	ld	c, a
	ld	hl, #_old_scroll_y + 1
	ld	a, (hl)
	ld	hl, #_scroll_y + 1
	sbc	a, (hl)
	ld	b, a
	inc	bc
	sra	b
	rr	c
	ld	hl, #_old_scroll_y
	ld	a, (hl)
	sub	a, c
	ld	(hl+), a
	ld	a, (hl)
	sbc	a, b
	ld	(hl), a
00110$:
;C:/GB/ZGB/common/src/main.c:57: SCY_REG = old_scroll_y + (scroll_offset_y << 3);
	ld	hl, #_old_scroll_y
	ld	c, (hl)
	ld	hl, #_scroll_offset_y
	ld	a, (hl)
	add	a, a
	add	a, a
	add	a, a
	add	a, c
	ldh	(_SCY_REG+0),a
;C:/GB/ZGB/common/src/main.c:59: if(music_mute_frames != 0) {
	ld	hl, #_music_mute_frames
	ld	a, (hl)
	or	a, a
	ret	Z
;C:/GB/ZGB/common/src/main.c:60: music_mute_frames --;
	dec	(hl)
;C:/GB/ZGB/common/src/main.c:61: if(music_mute_frames == 0) {
	ld	a, (hl)
	or	a, a
	ret	NZ
;C:/GB/ZGB/common/src/main.c:62: gbt_enable_channels(0xF);
	ld	a, #0x0f
	push	af
	inc	sp
	call	_gbt_enable_channels
	inc	sp
;C:/GB/ZGB/common/src/main.c:65: }
	ret
;C:/GB/ZGB/common/src/main.c:70: void MusicUpdate() {
;	---------------------------------
; Function MusicUpdate
; ---------------------------------
_MusicUpdate::
;C:/GB/ZGB/common/src/main.c:71: gbt_update();
	call	_gbt_update
;C:/GB/ZGB/common/src/main.c:72: REFRESH_BANK;
	ld	de, #0x2000
	ld	hl, #__current_bank
	ld	a, (hl)
	ld	(de), a
;C:/GB/ZGB/common/src/main.c:73: }
	ret
;C:/GB/ZGB/common/src/main.c:93: void main() {
;	---------------------------------
; Function main
; ---------------------------------
_main::
;C:/GB/ZGB/common/src/main.c:98: PUSH_BANK(1);
	ld	a, #0x01
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/main.c:99: InitStates();
	call	_InitStates
;C:/GB/ZGB/common/src/main.c:100: InitSprites();
	call	_InitSprites
;C:/GB/ZGB/common/src/main.c:101: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/main.c:103: disable_interrupts();
	call	_disable_interrupts
;C:/GB/ZGB/common/src/main.c:104: add_VBL(vbl_update);
	ld	hl, #_vbl_update
	push	hl
	call	_add_VBL
	add	sp, #2
;C:/GB/ZGB/common/src/main.c:105: add_TIM(MusicUpdate);
	ld	hl, #_MusicUpdate
	push	hl
	call	_add_TIM
	add	sp, #2
;C:/GB/ZGB/common/src/main.c:109: TMA_REG = 0xBCU;
	ld	a, #0xbc
	ldh	(_TMA_REG+0),a
;C:/GB/ZGB/common/src/main.c:111: TAC_REG = 0x04U;
	ld	a, #0x04
	ldh	(_TAC_REG+0),a
;C:/GB/ZGB/common/src/main.c:113: set_interrupts(VBL_IFLAG | TIM_IFLAG);
	ld	a, #0x05
	push	af
	inc	sp
	call	_set_interrupts
	inc	sp
;C:/GB/ZGB/common/src/main.c:114: enable_interrupts();
	call	_enable_interrupts
;C:/GB/ZGB/common/src/main.c:117: while (state_running) {
00103$:
	ld	hl, #_state_running
	ld	a, (hl)
	or	a, a
	jp	Z, 00105$
;C:/GB/ZGB/common/src/main.c:118: if(!vbl_count)
	ld	hl, #_vbl_count
	ld	a, (hl)
	or	a, a
	jr	NZ,00102$
;C:/GB/ZGB/common/src/main.c:119: wait_vbl_done();
	call	_wait_vbl_done
00102$:
;C:/GB/ZGB/common/src/main.c:120: delta_time = vbl_count == 1u ? 0u : 1u;
	ld	hl, #_vbl_count
	ld	a, (hl)
	dec	a
	jr	NZ,00113$
	ld	bc, #0x0000
	jr	00114$
00113$:
	ld	bc, #0x0001
00114$:
	ld	hl, #_delta_time
	ld	(hl), c
;C:/GB/ZGB/common/src/main.c:121: vbl_count = 0;
	ld	hl, #_vbl_count
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:123: UPDATE_KEYS();
	push	hl
	ld	hl, #_keys
	ld	a, (hl)
	ld	hl, #_previous_keys
	ld	(hl), a
	pop	hl
	call	_joypad
	ld	hl, #_keys
	ld	(hl), e
;C:/GB/ZGB/common/src/main.c:125: SpriteManagerUpdate();
	call	_SpriteManagerUpdate
;C:/GB/ZGB/common/src/main.c:126: PUSH_BANK(stateBanks[current_state]);
	ld	a, #<(_stateBanks)
	ld	hl, #_current_state
	add	a, (hl)
	ld	c, a
	ld	a, #>(_stateBanks)
	adc	a, #0x00
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/main.c:127: updateFuncs[current_state]();
	ld	hl, #_current_state
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_updateFuncs
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	call	___sdcc_call_hl
;C:/GB/ZGB/common/src/main.c:128: POP_BANK;
	call	_PopBank
	jp	00103$
00105$:
;C:/GB/ZGB/common/src/main.c:131: FadeIn();
	call	_FadeIn
;C:/GB/ZGB/common/src/main.c:132: DISPLAY_OFF
	call	_display_off
;C:/GB/ZGB/common/src/main.c:134: gbt_stop();
	call	_gbt_stop
;C:/GB/ZGB/common/src/main.c:135: last_music = 0;
	ld	hl, #_last_music
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:137: last_sprite_loaded = 0;
	ld	hl, #_last_sprite_loaded
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:138: SpriteManagerReset();
	call	_SpriteManagerReset
;C:/GB/ZGB/common/src/main.c:139: state_running = 1;
	ld	hl, #_state_running
	ld	(hl), #0x01
;C:/GB/ZGB/common/src/main.c:140: current_state = next_state;
	push	hl
	ld	hl, #_next_state
	ld	a, (hl)
	ld	hl, #_current_state
	ld	(hl), a
	pop	hl
;C:/GB/ZGB/common/src/main.c:141: scroll_target = 0;
	ld	hl, #_scroll_target
	ld	(hl), #0x00
	inc	hl
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/main.c:149: BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, 1, 2, 3);
	ld	a, #0xe4
	ldh	(_OBP1_REG+0),a
	ld	a, #0xe4
	ldh	(_OBP0_REG+0),a
	ld	a, #0xe4
	ldh	(_BGP_REG+0),a
;C:/GB/ZGB/common/src/main.c:151: PUSH_BANK(stateBanks[current_state]);
	ld	a, #<(_stateBanks)
	ld	hl, #_current_state
	add	a, (hl)
	ld	c, a
	ld	a, #>(_stateBanks)
	adc	a, #0x00
	ld	b, a
	ld	a, (bc)
	push	af
	inc	sp
	call	_PushBank
	inc	sp
;C:/GB/ZGB/common/src/main.c:152: (startFuncs[current_state])();
	ld	hl, #_current_state
	ld	c, (hl)
	ld	b, #0x00
	sla	c
	rl	b
	ld	hl, #_startFuncs
	add	hl, bc
	ld	c,l
	ld	b,h
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	l, c
	ld	h, b
	call	___sdcc_call_hl
;C:/GB/ZGB/common/src/main.c:153: POP_BANK;
	call	_PopBank
;C:/GB/ZGB/common/src/main.c:154: old_scroll_x = scroll_x;
	ld	hl, #_scroll_x
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_old_scroll_x
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/main.c:155: old_scroll_y = scroll_y;
	ld	hl, #_scroll_y
	ld	a, (hl+)
	ld	e, (hl)
	ld	hl, #_old_scroll_y
	ld	(hl+), a
	ld	(hl), e
;C:/GB/ZGB/common/src/main.c:157: if(state_running) {
	ld	hl, #_state_running
	ld	a, (hl)
	or	a, a
	jp	Z, 00103$
;C:/GB/ZGB/common/src/main.c:158: DISPLAY_ON;
	ldh	a, (_LCDC_REG+0)
	or	a, #0x80
	ldh	(_LCDC_REG+0),a
;C:/GB/ZGB/common/src/main.c:159: FadeOut();
	call	_FadeOut
	jp	00103$
;C:/GB/ZGB/common/src/main.c:164: }
	ret
	.area _CODE
	.area _CABS (ABS)
