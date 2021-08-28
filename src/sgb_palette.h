struct SGB_PACKET{
	unsigned char first_byte;
	UINT16 palette_0_color_0;
	UINT16 palette_0_color_1;
	UINT16 palette_0_color_2;
	UINT16 palette_0_color_3;
	UINT16 palette_1_color_1;
	UINT16 palette_1_color_2;
	UINT16 palette_1_color_3;
	unsigned char last_byte;
};

const struct SGB_PACKET snes_default = {(SGB_PAL_01 << 3) | 1,
RGB(255 >> 3, 232 >> 3, 207 >> 3),
RGB(223 >> 3, 144 >> 3, 79 >> 3),
RGB(175 >> 3, 40 >> 3, 32 >> 3),
RGB(48 >> 3, 24 >> 3, 80 >> 3), 
RGB(255 >> 3, 232 >> 3, 207 >> 3),
RGB(223 >> 3, 144 >> 3, 79 >> 3), 
RGB(175 >> 3, 40 >> 3, 32 >> 3),
0};

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
7207-2072-0720

 

Color Palette 3-B
7217-2172-1721

 

Color Palette 3-C
7227-2272-2722

 

Color Palette 3-D
7237-2372-3723

 

Color Palette 3-E
7247-2472-4724

 

Color Palette 3-F
7257-2572-5725

 

Color Palette 3-G
7267-2672-6726

 

Color Palette 3-H
7277-2772-7727

 

Color Palette 4-A
7287-2872-8728

 

Color Palette 4-B
7297-2972-9729

 

Color Palette 4-C
7307-3073-0730

 

Color Palette 4-D
7317-3173-1731

 

Color Palette 4-E
7327-3273-2732

 

Color Palette 4-F
7337-3373-3733

 

Color Palette 4-G
7347-3473-4734

 

Color Palette 4-H
7357-3573-5735
*/