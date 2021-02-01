;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module Print
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _set_win_tiles
	.globl _set_bkg_tiles
	.globl _print_target
	.globl _font_idx
	.globl _print_y
	.globl _print_x
	.globl _UIntToString
	.globl _IntToString
	.globl _Printf
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_print_x::
	.ds 1
_print_y::
	.ds 1
_font_idx::
	.ds 1
_print_target::
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
;C:/GB/ZGB/common/src/Print.c:7: UINT8 print_x = 0;
	ld	hl, #_print_x
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Print.c:8: UINT8 print_y = 0;
	ld	hl, #_print_y
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Print.c:9: UINT8 font_idx = 128;
	ld	hl, #_font_idx
	ld	(hl), #0x80
;C:/GB/ZGB/common/src/Print.c:10: UINT8 print_target = PRINT_BKG;
	ld	hl, #_print_target
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
;C:/GB/ZGB/common/src/Print.c:12: void UIntToString(UINT16 n, unsigned char* str) {
;	---------------------------------
; Function UIntToString
; ---------------------------------
_UIntToString::
	dec	sp
;C:/GB/ZGB/common/src/Print.c:13: UINT16 tmp = n;
	ldhl	sp,#(4 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
;C:/GB/ZGB/common/src/Print.c:16: if(n == 0) {
	ld	a, d
	or	a, e
	jr	NZ,00114$
;C:/GB/ZGB/common/src/Print.c:17: str[0] ='0';
	inc	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, #0x30
	ld	(bc), a
;C:/GB/ZGB/common/src/Print.c:18: str[1] = '\0';
	inc	bc
	xor	a, a
	ld	(bc), a
	jp	00110$
;C:/GB/ZGB/common/src/Print.c:20: while(tmp) {
00114$:
	ld	c, #0x00
00101$:
	ld	a, d
	or	a, e
	jr	Z,00103$
;C:/GB/ZGB/common/src/Print.c:21: tmp /= 10;
	push	bc
	ld	hl, #0x000a
	push	hl
	push	de
	call	__divuint
	add	sp, #4
	pop	bc
;C:/GB/ZGB/common/src/Print.c:22: size ++;
	inc	c
	jr	00101$
00103$:
;C:/GB/ZGB/common/src/Print.c:24: str[size] = '\0';
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	l, c
	ld	h, #0x00
	add	hl, de
	ld	b,l
	ld	a,h
	ld	(hl), #0x00
;C:/GB/ZGB/common/src/Print.c:25: size --;
	ld	a, c
	add	a, #0xff
	ldhl	sp,	#0
	ld	(hl), a
;C:/GB/ZGB/common/src/Print.c:27: while(n) {
00104$:
	ldhl	sp,	#4
	ld	a, (hl-)
	or	a, (hl)
	jp	Z, 00110$
;C:/GB/ZGB/common/src/Print.c:28: str[size] = (n % 10) + '0';
	ldhl	sp,#(6 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ldhl	sp,	#0
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	c, l
	ld	b, h
	push	bc
	ld	hl, #0x000a
	push	hl
	ldhl	sp,	#7
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__moduint
	add	sp, #4
	pop	bc
	ld	a, e
	add	a, #0x30
	ld	(bc), a
;C:/GB/ZGB/common/src/Print.c:29: n /= 10;
	ld	hl, #0x000a
	push	hl
	ldhl	sp,	#5
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	call	__divuint
	add	sp, #4
	ldhl	sp,	#3
	ld	(hl), e
	inc	hl
	ld	(hl), d
;C:/GB/ZGB/common/src/Print.c:30: size --;
	ldhl	sp,	#0
	dec	(hl)
	jp	00104$
00110$:
;C:/GB/ZGB/common/src/Print.c:33: }
	inc	sp
	ret
;C:/GB/ZGB/common/src/Print.c:35: void IntToString(INT16 n, unsigned char* str) {
;	---------------------------------
; Function IntToString
; ---------------------------------
_IntToString::
;C:/GB/ZGB/common/src/Print.c:39: if(n < 0){
	ldhl	sp,	#2
	ld	a, (hl)
	sub	a, #0x00
	inc	hl
	ld	a, (hl)
	sbc	a, #0x00
	ld	d, (hl)
	ld	a, #0x00
	ld	e, a
	bit	7, e
	jr	Z,00110$
	bit	7, d
	jr	NZ,00111$
	cp	a, a
	jr	00111$
00110$:
	bit	7, d
	jr	Z,00111$
	scf
00111$:
	jr	NC,00102$
;C:/GB/ZGB/common/src/Print.c:40: n = 0xFFFF - n + 1; //I tried -n but it doesn't work
	ldhl	sp,#(3 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	xor	a, a
	sub	a, c
	ld	c, a
	ld	a, #0x00
	sbc	a, b
	ld	b, a
	dec	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Print.c:41: str[0] = '-';
	inc	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, #0x2d
	ld	(bc), a
;C:/GB/ZGB/common/src/Print.c:42: str ++;
	inc	bc
	dec	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
00102$:
;C:/GB/ZGB/common/src/Print.c:45: UIntToString(n, str);
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
	call	_UIntToString
	add	sp, #4
;C:/GB/ZGB/common/src/Print.c:46: }
	ret
;C:/GB/ZGB/common/src/Print.c:48: void Printf(const char* txt, ...){
;	---------------------------------
; Function Printf
; ---------------------------------
_Printf::
	add	sp, #-23
;C:/GB/ZGB/common/src/Print.c:54: va_start(list, txt); 
	ldhl	sp,	#25
	ld	c, l
	ld	b, h
	inc	bc
	inc	bc
	ldhl	sp,	#11
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/Print.c:55: while(*txt) {
	ldhl	sp,	#1
	ld	a, l
	ld	d, h
	ldhl	sp,	#13
	ld	(hl+), a
	ld	(hl), d
	dec	hl
	ld	a, (hl+)
	ld	e, (hl)
	inc	hl
	ld	(hl+), a
	ld	(hl), e
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#17
	ld	(hl+), a
	ld	(hl), e
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#19
	ld	(hl+), a
	ld	(hl), e
00140$:
	ldhl	sp,#(26 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	ld	c,a
	or	a, a
	jp	Z, 00143$
;C:/GB/ZGB/common/src/Print.c:56: if(*txt == ' ') {
	ld	a, c
	sub	a, #0x20
	jr	NZ,00135$
;C:/GB/ZGB/common/src/Print.c:57: c = font_idx;
	push	hl
	ld	hl, #_font_idx
	ld	a, (hl)
	ldhl	sp,	#2
	ld	(hl), a
	pop	hl
	jp	00136$
00135$:
;C:/GB/ZGB/common/src/Print.c:58: } else if(*txt >= 'A' && *txt <= 'Z'){
	ld	a, c
	xor	a, #0x80
	sub	a, #0xc1
	jr	C,00131$
	ld	a, c
	ld	e, a
	ld	a, #0x5a
	ld	d, a
	ld	a, #0x5a
	sub	a, c
	bit	7, e
	jr	Z,00292$
	bit	7, d
	jr	NZ,00293$
	cp	a, a
	jr	00293$
00292$:
	bit	7, d
	jr	Z,00293$
	scf
00293$:
	jr	C,00131$
;C:/GB/ZGB/common/src/Print.c:59: c = font_idx +  1 + *txt - 'A';
	ld	a, c
	add	a, #0xc0
	ld	hl, #_font_idx
	ld	c, (hl)
	add	a, c
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
00131$:
;C:/GB/ZGB/common/src/Print.c:60: } else if(*txt >= 'a' && *txt <= 'z') {
	ldhl	sp,#(26 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	ld	c,a
	xor	a, #0x80
	sub	a, #0xe1
	jr	C,00127$
	ld	a, c
	ld	e, a
	ld	a, #0x7a
	ld	d, a
	ld	a, #0x7a
	sub	a, c
	bit	7, e
	jr	Z,00294$
	bit	7, d
	jr	NZ,00295$
	cp	a, a
	jr	00295$
00294$:
	bit	7, d
	jr	Z,00295$
	scf
00295$:
	jr	C,00127$
;C:/GB/ZGB/common/src/Print.c:61: c = font_idx +  1 + *txt - 'a';
	ld	a, c
	add	a, #0xa0
	ld	hl, #_font_idx
	ld	c, (hl)
	add	a, c
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
00127$:
;C:/GB/ZGB/common/src/Print.c:62: } else if(*txt >= '0' && *txt <= '9') {
	ldhl	sp,#(26 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, (de)
	ld	c,a
	xor	a, #0x80
	sub	a, #0xb0
	jr	C,00123$
	ld	a, c
	ld	e, a
	ld	a, #0x39
	ld	d, a
	ld	a, #0x39
	sub	a, c
	bit	7, e
	jr	Z,00296$
	bit	7, d
	jr	NZ,00297$
	cp	a, a
	jr	00297$
00296$:
	bit	7, d
	jr	Z,00297$
	scf
00297$:
	jr	C,00123$
;C:/GB/ZGB/common/src/Print.c:63: c = font_idx + 27 + *txt - '0';
	ld	a, c
	add	a, #0xeb
	ld	hl, #_font_idx
	ld	c, (hl)
	add	a, c
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
00123$:
;C:/GB/ZGB/common/src/Print.c:65: switch(*txt) {
	ldhl	sp,#(26 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, (bc)
	cp	a, #0x21
	jr	Z,00101$
	cp	a, #0x23
	jp	Z,00112$
	cp	a, #0x24
	jp	Z,00109$
	cp	a, #0x25
	jp	Z,00115$
	cp	a, #0x27
	jr	Z,00102$
	cp	a, #0x28
	jp	Z,00103$
	cp	a, #0x29
	jp	Z,00104$
	cp	a, #0x2d
	jp	Z,00105$
	cp	a, #0x2e
	jp	Z,00106$
	cp	a, #0x3a
	jp	Z,00107$
	cp	a, #0x3c
	jp	Z,00114$
	cp	a, #0x3f
	jp	Z,00108$
	cp	a, #0x40
	jp	Z,00113$
	cp	a, #0x5b
	jp	Z,00111$
	sub	a, #0x5d
	jp	Z,00110$
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:66: case  '!': c= font_idx + 37; break;
00101$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x25
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:67: case '\'': c= font_idx + 38; break;
00102$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x26
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:68: case  '(': c= font_idx + 39; break;
00103$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x27
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:69: case  ')': c= font_idx + 40; break;
00104$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x28
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:70: case  '-': c= font_idx + 41; break;
00105$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x29
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:71: case  '.': c= font_idx + 42; break;
00106$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x2a
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:72: case  ':': c= font_idx + 43; break;
00107$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x2b
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:73: case  '?': c= font_idx + 44; break;
00108$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x2c
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:76: case  '$': c= font_idx + 45; break;
00109$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x2d
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:77: case  ']': c= font_idx + 46; break;
00110$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x2e
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:78: case  '[': c= font_idx + 47; break;
00111$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x2f
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:79: case  '#': c= font_idx + 48; break;
00112$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x30
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:80: case  '@': c= font_idx + 49; break;
00113$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x31
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:81: case  '<': c= font_idx + 50; break;
00114$:
	ld	hl, #_font_idx
	ld	a, (hl)
	add	a, #0x32
	ldhl	sp,	#0
	ld	(hl), a
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:83: case  '%':
00115$:
;C:/GB/ZGB/common/src/Print.c:84: switch(*(txt + 1)) {
	inc	bc
	ld	a, (bc)
	cp	a, #0x64
	jr	Z,00117$
	cp	a, #0x69
	jr	Z,00117$
	cp	a, #0x73
	jp	Z,00119$
	sub	a, #0x75
	jp	Z,00118$
	jp	00136$
;C:/GB/ZGB/common/src/Print.c:86: case 'i':
00117$:
;C:/GB/ZGB/common/src/Print.c:87: IntToString(va_arg(list, INT16), tmp);
	ldhl	sp,	#13
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#21
	ld	(hl+), a
	ld	(hl), e
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	dec	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
	dec	bc
	dec	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#21
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_IntToString
	add	sp, #4
;C:/GB/ZGB/common/src/Print.c:88: Printf(tmp);
	ldhl	sp,#(16 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	call	_Printf
	add	sp, #2
;C:/GB/ZGB/common/src/Print.c:89: txt += 2;
	ldhl	sp,#(26 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#25
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Print.c:90: continue;
	jp	00140$
;C:/GB/ZGB/common/src/Print.c:92: case 'u':
00118$:
;C:/GB/ZGB/common/src/Print.c:93: UIntToString(va_arg(list, UINT16), tmp);
	ldhl	sp,	#17
	ld	a, (hl+)
	ld	e, (hl)
	ldhl	sp,	#21
	ld	(hl+), a
	ld	(hl), e
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	dec	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
	dec	bc
	dec	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ldhl	sp,	#21
	ld	a, (hl+)
	ld	h, (hl)
	ld	l, a
	push	hl
	push	bc
	call	_UIntToString
	add	sp, #4
;C:/GB/ZGB/common/src/Print.c:94: Printf(tmp);
	ldhl	sp,#(20 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	call	_Printf
	add	sp, #2
;C:/GB/ZGB/common/src/Print.c:95: txt += 2;
	ldhl	sp,#(26 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#25
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Print.c:96: continue;
	jp	00140$
;C:/GB/ZGB/common/src/Print.c:98: case 's':
00119$:
;C:/GB/ZGB/common/src/Print.c:99: Printf(va_arg(list, char*));
	ldhl	sp,#(12 - 1)
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	inc	bc
	inc	bc
	dec	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
	dec	bc
	dec	bc
	ld	l, c
	ld	h, b
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	push	bc
	call	_Printf
	add	sp, #2
;C:/GB/ZGB/common/src/Print.c:100: txt += 2;
	ldhl	sp,#(26 - 1)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	hl, #0x0002
	add	hl, de
	ld	a, l
	ld	d, h
	ldhl	sp,	#25
	ld	(hl+), a
	ld	(hl), d
;C:/GB/ZGB/common/src/Print.c:104: }
00136$:
;C:/GB/ZGB/common/src/Print.c:106: if(print_target == PRINT_BKG)
	ld	hl, #_print_target
	ld	a, (hl)
	or	a, a
	jr	NZ,00138$
;C:/GB/ZGB/common/src/Print.c:107: set_bkg_tiles(0x1F & (print_x + scroll_offset_x), 0x1F & (print_y + scroll_offset_y), 1, 1, &c);
	ldhl	sp,	#0
	ld	c, l
	ld	b, h
	ld	hl, #_print_y
	ld	a, (hl)
	ld	hl, #_scroll_offset_y
	add	a, (hl)
	and	a, #0x1f
	ld	e, a
	ld	hl, #_print_x
	ld	a, (hl)
	ld	hl, #_scroll_offset_x
	add	a, (hl)
	and	a, #0x1f
	ld	d, a
	push	bc
	ld	a, #0x01
	push	af
	inc	sp
	ld	a, #0x01
	push	af
	inc	sp
	ld	a, e
	push	af
	inc	sp
	push	de
	inc	sp
	call	_set_bkg_tiles
	add	sp, #6
	jr	00139$
00138$:
;C:/GB/ZGB/common/src/Print.c:109: set_win_tiles(print_x, print_y, 1, 1, &c);
	ldhl	sp,	#0
	ld	c, l
	ld	b, h
	push	bc
	ld	a, #0x01
	push	af
	inc	sp
	ld	a, #0x01
	push	af
	inc	sp
	ld	hl, #_print_y
	ld	a, (hl)
	push	af
	inc	sp
	ld	hl, #_print_x
	ld	a, (hl)
	push	af
	inc	sp
	call	_set_win_tiles
	add	sp, #6
00139$:
;C:/GB/ZGB/common/src/Print.c:111: print_x ++;
	ld	hl, #_print_x
	inc	(hl)
;C:/GB/ZGB/common/src/Print.c:112: txt ++;
	ldhl	sp,	#25
	inc	(hl)
	jp	NZ,00140$
	inc	hl
	inc	(hl)
	jp	00140$
00143$:
;C:/GB/ZGB/common/src/Print.c:115: }
	add	sp, #23
	ret
	.area _CODE
	.area _CABS (ABS)
