#pragma bank 10

#include <gb/gb.h>
#include <gb/sgb.h>

#include "sgb_palette.h"

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


void set_sgb_palette01_1A() __banked {
	set_sgb_palette(SGB_PAL1A_LIGHTER, SGB_PAL1A_LIGHT, SGB_PAL1A_DARK, SGB_PAL1A_DARKER);
}

void set_sgb_palette01_1B() __banked {
	set_sgb_palette(SGB_PAL1B_LIGHTER, SGB_PAL1B_LIGHT, SGB_PAL1B_DARK, SGB_PAL1B_DARKER);
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

void set_sgb_palette01_2B() __banked {
	set_sgb_palette(SGB_PAL2B_LIGHTER, SGB_PAL2B_LIGHT, SGB_PAL2B_DARK, SGB_PAL2B_DARKER);
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
