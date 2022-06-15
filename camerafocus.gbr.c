#pragma bank 255

//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(camerafocus)

const palette_color_t camerafocus_palettes[4] = {
	RGB8(255, 255, 255), RGB8(170, 170, 170), RGB8(85, 85, 85), RGB8(0, 0, 0)
};

const uint8_t camerafocus_tiles[32] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const metasprite_t camerafocus_metasprite0[] = {
	METASPR_ITEM(0, 0, 0, 0), METASPR_TERM
};

const metasprite_t* const camerafocus_metasprites[1] = {
	camerafocus_metasprite0
};

#include "MetaSpriteInfo.h"
const struct MetaSpriteInfo camerafocus = {
	8, //width
	16, //height
	2, //num tiles
	camerafocus_tiles, //tiles
	1, //num palettes
	camerafocus_palettes, //CGB palette
	1, //num sprites
	camerafocus_metasprites, //metasprites
};
