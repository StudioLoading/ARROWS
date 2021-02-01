#pragma bank 3

void empty(void) __nonbanked {}
__addressmod empty const CODE;

const unsigned char platform_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x7f,0x80,0x60,0x7f,0x3f,0x3f,0x20,0x20,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xfe,0x01,0x06,0xfe,0xfc,0xfc,0x04,0x04
};

#include "TilesInfo.h"
const struct TilesInfoInternal platform_internal = {
	16, //width
	16, //height
	1, //num_tiles
	platform_tiles, //tiles
	0, //CGB palette
};
CODE struct TilesInfo platform = {
	3, //bank
	&platform_internal, //data
};