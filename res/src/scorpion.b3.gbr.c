#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char scorpion_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x18,0x18,0x3c,0x3c,
	0x22,0x26,0x60,0x62,0x40,0x40,0xc4,0xc4,
	0x88,0x88,0x91,0x91,0xba,0xba,0xf6,0xfe,
	0x7e,0xfe,0x3c,0x7c,0x24,0x3c,0x48,0x48,
	
	//Frame 1
	0x00,0x00,0x00,0x00,0x0c,0x0c,0x1e,0x1e,
	0x31,0x33,0x60,0x61,0x40,0x40,0xc8,0xc8,
	0x8c,0x8c,0x92,0x92,0xbb,0xbb,0xf6,0xfe,
	0x7e,0xfe,0x3c,0x7c,0x24,0x3c,0x12,0x12,
	
	//Frame 2
	0x00,0x00,0x00,0x00,0x0c,0x0c,0x1e,0x1e,
	0x31,0x3b,0x64,0x61,0x40,0x4a,0xc8,0xc8,
	0x8c,0x8c,0x92,0x92,0xbb,0xbb,0xf6,0xfe,
	0x7e,0xfe,0x3c,0x7c,0x24,0x3c,0x24,0x24,
	
	//Frame 3
	0x00,0x00,0x00,0x00,0x0c,0x0c,0x0e,0x1f,
	0x31,0x3b,0x60,0x61,0x40,0x4a,0xc8,0xd9,
	0x8c,0x8c,0x92,0x92,0xbb,0xbb,0xf6,0xfe,
	0x7e,0xfe,0x3c,0x7c,0x24,0x3c,0x24,0x24,
	
	//Frame 4
	0x00,0x00,0x00,0x00,0x0c,0x0c,0x0c,0x1e,
	0x31,0x33,0x60,0x61,0x40,0x52,0xc8,0xc8,
	0x8c,0x8c,0x92,0x92,0xbb,0xbb,0xf6,0xfe,
	0x7e,0xfe,0x3c,0x7c,0x24,0x3c,0x24,0x24,
	
	//Frame 5
	0x24,0x24,0x24,0x3c,0x3c,0x7c,0x7e,0xfe,
	0xf6,0xfe,0xbb,0xbb,0x92,0x92,0x8c,0x8c,
	0xc8,0xc8,0x40,0x40,0x60,0x61,0x31,0x33,
	0x1e,0x1e,0x0c,0x0c,0x00,0x00,0x00,0x00,
	
	//Frame 6
	0x00,0x00,0x00,0x00,0x0c,0x0c,0x1e,0x1e,
	0x31,0x33,0x60,0x61,0x40,0x40,0xc8,0xc8,
	0x8c,0x8c,0x92,0x92,0xbb,0xbb,0xf6,0xfe,
	0x7e,0xfe,0x3c,0x7c,0x24,0x3c,0x24,0x24
};

#include "TilesInfo.h"
const struct TilesInfoInternal scorpion_internal = {
	8, //width
	16, //height
	7, //num_tiles
	scorpion_tiles, //tiles
	0, //CGB palette
};
CODE struct TilesInfo scorpion = {
	3, //bank
	&scorpion_internal, //data
};