#pragma bank 10

#include <gb/gb.h>
#include <gb/sgb.h>

#include "sgb_palette.h"

void set_sgb_palette_statusbar() __banked {	
	struct {
        UINT8 command;
        UINT16 pal1[4];
        UINT16 pal2[3];
        UINT8 padding;
    } SGB_PALETTE2_PACKET = {
        .command = (SGB_PAL_12 << 3) | 1,
        .pal1 = {SGB_PAL1D_LIGHTER, SGB_STATUS_LIGHT, SGB_STATUS_DARK, SGB_STATUS_RED},
        .pal2 = {SGB_STATUS_LIGHT, SGB_STATUS_DARK, SGB_STATUS_DARKER},
        .padding = 0 
    };
	struct {
        UINT8 command;
        UINT8 xcoo;
        UINT8 ycoo;
		UINT16 ndata;
		UINT8 style;
        UINT8 ds[10];
    } SGB_PALETTE_STATUS_PACKET = {
        .command = (SGB_ATTR_CHR << 3) | 1,
        .xcoo = 0,
        .ycoo = 17u,
        .ndata = 16u,
		.style = 0,
		.ds = {0b01011010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010}
    };
    sgb_transfer((void *)&SGB_PALETTE2_PACKET);
    sgb_transfer((void *)&SGB_PALETTE_STATUS_PACKET);
}

void set_sgb_palette(UINT16 c0, UINT16 c1, UINT16 c2, UINT16 c3) __banked {
    struct {
        UINT8 command;
        UINT16 pal0[4];
        UINT16 pal1[3];
        UINT8 padding;
    } SGB_PALETTE_PACKET = {
        .command = (SGB_PAL_01 << 3) | 1,
        .pal0 = {c0, c1, c2, c3},
        .pal1 = {0, 0, 0},
        .padding = 0 
    };
    sgb_transfer((void *)&SGB_PALETTE_PACKET);
}

void reset_sgb_palette_statusbar() __banked{	
	struct {
        UINT8 command;
        UINT8 xcoo;
        UINT8 ycoo;
		UINT16 ndata;
		UINT8 style;
        UINT8 ds[10];
    } SGB_PALETTE_STATUS_PACKET = {
        .command = (SGB_ATTR_CHR << 3) | 1,
        .xcoo = 0,
        .ycoo = 17u,
        .ndata = 16u,
		.style = 0,
		.ds = {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}
    };
    sgb_transfer((void *)&SGB_PALETTE_STATUS_PACKET);	
}

void set_sgb_palette01_WOLF() __banked{
	set_sgb_palette(SGB_PAL2H_LIGHTER, SGB_PAL2H_LIGHT, SGB_PAL2H_DARKER, SGB_PAL2H_DARK);
}
void set_sgb_palette01_TITLEINVERTED() __banked{
	set_sgb_palette(SGB_PAL2A_LIGHTER, SGB_PAL2A_DARK, SGB_PAL2A_LIGHT, SGB_PAL2A_DARKER);
}
void set_sgb_palette01_COMUNEKO() __banked{
	set_sgb_palette(SGB_COMUNEKO_LIGHTER, SGB_COMUNEKO_LIGHT, SGB_COMUNEKO_DARK, SGB_COMUNEKO_DARKER);
}
void set_sgb_palette01_AMULET_THUNDER() __banked{
	set_sgb_palette(SGB_PAL1B_LIGHTER, RGB8(255, 187, 17), RGB8(198, 132, 74), SGB_PAL1B_DARKER);
}
void set_sgb_palette01_TREES() __banked {
	set_sgb_palette(SGB_PAL1E_LIGHTER, RGB8(252, 160, 68), RGB8(168, 16, 0), RGB8(90, 57, 33));
}
void set_sgb_palette01_BEAR() __banked {
	set_sgb_palette(SGB_PAL1E_LIGHTER, RGB8(228, 92, 16), RGB8(80, 48, 0), RGB8(90, 57, 33));
}

void set_sgb_palette01_1A() __banked {
	set_sgb_palette(SGB_PAL1A_LIGHTER, SGB_PAL1A_LIGHT, SGB_PAL1A_DARK, SGB_PAL1A_DARKER);
}

void set_sgb_palette01_1B() __banked {
	set_sgb_palette(SGB_PAL1B_LIGHTER, RGB8(255, 187, 17), RGB8(100, 100, 100), SGB_PAL1B_DARKER);
}

void set_sgb_palette01_1D() __banked {
	set_sgb_palette(SGB_PAL1D_LIGHTER, SGB_PAL1D_LIGHT, SGB_PAL1D_DARK, SGB_PAL1D_DARKER);
}

void set_sgb_palette01_1E() __banked {
	set_sgb_palette(SGB_PAL1E_LIGHTER, SGB_PAL1E_LIGHT, SGB_PAL1E_DARK, SGB_PAL1E_DARKER);
}

void set_sgb_palette01_1G() __banked {
	set_sgb_palette(SGB_PAL1G_LIGHTER, SGB_PAL1G_LIGHT, SGB_PAL1G_DARK, SGB_PAL1G_DARKER);
}

void set_sgb_palette01_1F() __banked {
	set_sgb_palette(SGB_PAL1F_LIGHTER, SGB_PAL1F_LIGHT, SGB_PAL1F_DARK, SGB_PAL1F_DARKER);
}

void set_sgb_palette01_2A() __banked {
	set_sgb_palette(SGB_PAL2A_LIGHTER, SGB_PAL2A_LIGHT, SGB_PAL2A_DARK, SGB_PAL2A_DARKER);
}

void set_sgb_palette01_2B() __banked {
	set_sgb_palette(SGB_PAL2B_LIGHTER, SGB_PAL2B_LIGHT, SGB_PAL2B_DARK, SGB_PAL2B_DARKER);
}

void set_sgb_palette01_2E() __banked {
	set_sgb_palette(SGB_PAL2E_LIGHTER, SGB_PAL2E_LIGHT, SGB_PAL2E_DARK, SGB_PAL2E_DARKER);
}

void set_sgb_palette01_2H() __banked {
	set_sgb_palette(SGB_PAL2H_LIGHTER, SGB_PAL2H_LIGHT, SGB_PAL2H_DARK, SGB_PAL2H_DARKER);
}

void set_sgb_palette01_3C() __banked {
	set_sgb_palette(SGB_PAL3C_LIGHTER, SGB_PAL3C_LIGHT, SGB_PAL3C_DARK, SGB_PAL3C_DARKER);
}

void set_sgb_palette01_4B() __banked {
	set_sgb_palette(SGB_PAL4B_LIGHTER, SGB_PAL4B_LIGHT, SGB_PAL4B_DARK, SGB_PAL4B_DARKER);
}
