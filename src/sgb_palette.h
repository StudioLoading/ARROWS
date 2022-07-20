#include <gb/gb.h>

#define RGB8(r, g, b) (((UINT16)((b) >> 3) << 10) | ((UINT16)((g) >> 3) << 5) | ((UINT16)((r) >> 3) << 0))

#define SGB_COMUNEKO_LIGHTER  RGB8(180, 219, 214)
#define SGB_COMUNEKO_LIGHT    RGB8(193, 166, 224)
#define SGB_COMUNEKO_DARK     RGB8(193, 166, 224)
#define SGB_COMUNEKO_DARKER	  RGB8(0, 0, 0)

#define SGB_STATUS_LIGHT    RGB8(248, 184, 0)
#define SGB_STATUS_DARK     RGB8(0, 88, 248)
#define SGB_STATUS_DARKER 	RGB8(0, 0, 0)
#define SGB_STATUS_RED	 	RGB8(254, 0, 0)

#define SGB_PAL1A_LIGHTER 	RGB8(255, 232, 207)
#define SGB_PAL1A_LIGHT 	RGB8(223, 144, 79)
#define SGB_PAL1A_DARK		RGB8(175, 40, 32)
#define SGB_PAL1A_DARKER 	RGB8(48, 24, 80)

#define SGB_PAL1B_LIGHTER 	RGB8(223, 216, 192)
#define SGB_PAL1B_LIGHT 	RGB8(207, 176, 112)
#define SGB_PAL1B_DARK		RGB8(176, 80, 16)
#define SGB_PAL1B_DARKER 	RGB8(0, 0, 0)

#define SGB_PAL1D_LIGHTER 	RGB8(255, 248, 175)
#define SGB_PAL1D_LIGHT 	RGB8(192, 128, 79)
#define SGB_PAL1D_DARK		RGB8(255, 0, 0)
#define SGB_PAL1D_DARKER 	RGB8(80, 24, 0)

#define SGB_PAL1E_LIGHTER 	RGB8(255, 248, 175)
#define SGB_PAL1E_LIGHT 	RGB8(127, 192, 127)
#define SGB_PAL1E_DARK		RGB8(111, 136, 64)
#define SGB_PAL1E_DARKER 	RGB8(95, 56, 32)

#define SGB_PAL1G_LIGHTER 	RGB8(255, 248, 95)
#define SGB_PAL1G_LIGHT 	RGB8(127, 120, 0)
#define SGB_PAL1G_DARK		RGB8(0, 160, 239)
#define SGB_PAL1G_DARKER 	RGB8(0, 0, 80)

#define SGB_PAL1F_LIGHTER 	RGB8(223, 232, 255)
#define SGB_PAL1F_LIGHT 	RGB8(224, 136, 80)
#define SGB_PAL1F_DARK		RGB8(175, 0, 0)
#define SGB_PAL1F_DARKER 	RGB8(0, 64, 16)

#define SGB_PAL2A_LIGHTER 	RGB8(240, 200, 160)
#define SGB_PAL2A_LIGHT 	RGB8(192, 136, 79)
#define SGB_PAL2A_DARK		RGB8(47, 120, 0)
#define SGB_PAL2A_DARKER 	RGB8(0, 0, 0)

#define SGB_PAL2B_LIGHTER 	RGB8(255, 248, 255)
#define SGB_PAL2B_LIGHT 	RGB8(191, 184, 191)
#define SGB_PAL2B_DARK		RGB8(112, 112, 112)
#define SGB_PAL2B_DARKER 	RGB8(0, 0, 0)

#define SGB_PAL2E_LIGHTER 	RGB8(255, 248, 128)
#define SGB_PAL2E_LIGHT 	RGB8(144, 176, 224)
#define SGB_PAL2E_DARK		RGB8(47, 16, 96)
#define SGB_PAL2E_DARKER 	RGB8(16, 8, 16)

#define SGB_PAL2H_LIGHTER 	RGB8(255, 248, 255)
#define SGB_PAL2H_LIGHT 	RGB8(191, 184, 191)
#define SGB_PAL2H_DARK		RGB8(112, 112, 112)
#define SGB_PAL2H_DARKER 	RGB8(0, 0, 0)
 
#define SGB_PAL3C_LIGHTER 	RGB8(224, 168, 207)
#define SGB_PAL3C_LIGHT 	RGB8(255, 248, 127)
#define SGB_PAL3C_DARK		RGB8(0, 184, 255)
#define SGB_PAL3C_DARKER 	RGB8(32, 32, 95)

#define SGB_PAL4B_LIGHTER 	RGB8(240, 232, 240)
#define SGB_PAL4B_LIGHT 	RGB8(239, 160, 96)
#define SGB_PAL4B_DARK		RGB8(64, 120, 63)
#define SGB_PAL4B_DARKER 	RGB8(31, 8, 15)

void set_sgb_palette_title() __banked;
void set_sgb_palette_statusbar() __banked;
void set_sgb_palette01_TITLESCREEN() __banked;
void set_sgb_palette01_intro() __banked;
void set_sgb_palette01_secret() __banked;
void set_sgb_palette01_worldmap() __banked;
void set_sgb_palette01_WOLF() __banked;
void set_sgb_palette01_TITLEINVERTED() __banked;
void set_sgb_palette01_COMUNEKO() __banked;
void reset_sgb_palette_statusbar() __banked;
void set_sgb_palette01_ZOO() __banked;
void set_sgb_palette01_SEWER() __banked;
void set_sgb_palette01_GATORSWAMP() __banked;
void set_sgb_palette01_GATOR() __banked;
void set_sgb_palette01_FOREST() __banked;
void set_sgb_palette01_EAGLE() __banked;
void set_sgb_palette01_IBEX() __banked;
void set_sgb_palette01_AMULET_THUNDER() __banked;
void set_sgb_palette01_AMULET_ICE() __banked;
void set_sgb_palette01_TREES() __banked;
void set_sgb_palette01_BEAR() __banked;
void set_sgb_palette01_ICE() __banked;
void set_sgb_palette01_WALRUS() __banked;
void set_sgb_palette01_CEMATERYCRYPT() __banked;
void set_sgb_palette01_CASTLE() __banked;
void set_sgb_palette01_BOSS() __banked;

void set_sgb_palette01_1A() __banked;	
void set_sgb_palette01_1B() __banked;
void set_sgb_palette01_1D() __banked;
void set_sgb_palette01_1E() __banked;
void set_sgb_palette01_1G() __banked;
void set_sgb_palette01_1F() __banked;
void set_sgb_palette01_2A() __banked;
void set_sgb_palette01_2B() __banked;
void set_sgb_palette01_2E() __banked;
void set_sgb_palette01_2H() __banked;
void set_sgb_palette01_3C() __banked;
void set_sgb_palette01_4B() __banked;


/*
Color Palette 1-A
704 - 255 232 207
      223 144  79
      175  40  32
       48  24  80

 

Color Palette 1-B
705 - 223 216 192
      207 176 112
      176  80  16
        0   0   0

 

Color Palette 1-C
706 - 255 192 255
      239 152  80
      159  56  96
       63  56 159

 

Color Palette 1-D
707 - 255 248 175
      192 128  79
      255   0   0
       80  24   0
 

Color Palette 1-E
708 - 255 248 175
      127 192 127
      111 136  64
       95  56  32
 

Color Palette 1-F
709 - 223 232 255
      224 136  80
      175   0   0
        0  64  16
 

Color Palette 1-G
710 -   0   0  80
        0 160 239
      127 120   0
      255 248  95

 

Color Palette 1-H
711 - 255 232 224
      255 184 143
      128  64   0
       48  24   0
 

Color Palette 2-A
712 - 240 200 160
      192 136  79
       47 120   0
        0   0   0

 

Color Palette 2-B
713 - 255 248 255
      255 232  80
      255  48   0
       80   0  95
 

Color Palette 2-C
714 - 255 192 255
      239 136 143
      127  48 239
       47  40 159
 

Color Palette 2-D
715 - 255 248 160
        0 248   0
      255  48   0
        0   0  80
 

Color Palette 2-E
716 - 255 248 128
      144 176 224
       47  16  96
       16   8  16
 

Color Palette 2-F
717 - 208 248 255
      255 144  80
      160   0   0
       31   0   0
 

Color Palette 2-G
718 - 111 184  63
      224  80  64
      224 184 128
        0  24   0

 

Color Palette 2-H
719 - 255 248 255
      191 184 191
      112 112 112
        0   0   0
 

Color Palette 3-A
255 208 159
      112 192 192
      255  96  47
       48  72  96

 

Color Palette 3-B
223 216 192
      224 128  32
        0  80   0
        0  16  16

 

Color Palette 3-C
224 168 207
      255 248 127
        0 184 255
       32  32  95

 

Color Palette 3-D
 240 248 191
      224 168 127
       15 200   0
        0   0   0

 

Color Palette 3-E
255 248 191
      224 176 111
      176 120  32
       80  72 112


 

Color Palette 3-F
 127 120 207
      255 104 255
      255 208   0
       64  64  64

 

Color Palette 3-G
  96 216  80
      255 248 255
      207  48  63
       63   0   0

 

Color Palette 3-H
 224 248 160
      127 200  63
       79 136  31
       15  24   0

 

Color Palette 4-A
 240 168 111
      127 168 255
      208   0 208
        0   0 127
 

Color Palette 4-B
240 232 240
      239 160  96
       64 120  63
       31   8  15
 

Color Palette 4-C
 255 224 224
      223 160 208
      159 160 224
       15   0   0

 

Color Palette 4-D
255 248 191
      144 200 207
       79 104 127
       15  32  79	
 

Color Palette 4-E
 255 248 191
      144 200 207
       79 104 124
       15  32  79
 

Color Palette 4-F
 191 208 208
      223 128 223
      128   0 160
       63   0   0
 

Color Palette 4-G
 176 224  31
      191  32  95
       47  16   0
        0 128  96
 

Color Palette 4-H
255 248 207
      191 192  95
      128 136  64
       64  80  47
	  
	  */
