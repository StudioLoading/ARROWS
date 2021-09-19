#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char enemy_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x0c,0x0c,0x1e,0x1a,0x0f,0x0f,
	0x1a,0x1a,0x00,0x98,0x98,0x98,0x10,0x9c,
	0x8e,0x8e,0x6d,0xff,0x33,0x7f,0x2a,0x2a,
	
	//Frame 1
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x18,0x3c,0x34,0x1e,0x1e,
	0x34,0x34,0x00,0x70,0x70,0x70,0x20,0x78,
	0x4c,0x4c,0x5a,0x7e,0x26,0x7e,0x14,0x14,
	
	//Frame 2
	0x00,0x00,0x00,0x00,0x00,0x0a,0x04,0x00,
	0x00,0x0a,0x0c,0x0c,0x1e,0x1a,0x0f,0x0f,
	0x1a,0x1a,0x00,0x98,0x98,0x98,0x10,0x9c,
	0x8e,0x8e,0x6d,0xff,0x33,0x7f,0x2a,0x2a,
	
	//Frame 3
	0x00,0x00,0x00,0x11,0x00,0x0a,0x00,0x00,
	0x00,0x0a,0x0c,0x1d,0x1f,0x1b,0x0e,0x0e,
	0x1c,0x1c,0x02,0x9a,0x98,0x98,0x10,0x9c,
	0x8e,0x8e,0x6d,0xff,0x33,0x7f,0x2a,0x2a,
	
	//Frame 4
	0x00,0x00,0x00,0x11,0x00,0x00,0x00,0x00,
	0x00,0x00,0x0c,0x1d,0x1e,0x1a,0x0f,0x0f,
	0x1a,0x9a,0x00,0x98,0x98,0x98,0x10,0x9c,
	0x8e,0x8e,0x6d,0xff,0x33,0x7f,0x2a,0x2a,
	
	//Frame 5
	0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,
	0x0e,0x0e,0x0f,0x0b,0x1e,0x1e,0x0c,0x0c,
	0x18,0x18,0x00,0x98,0x98,0x98,0x10,0x9c,
	0x8e,0x8e,0x6d,0xff,0x33,0x7f,0x2a,0x2a
};

#include "TilesInfo.h"
const struct TilesInfoInternal enemy_internal = {
	8, //width
	16, //height
	6, //num_tiles
	enemy_tiles, //tiles
	0, //CGB palette
};
CODE struct TilesInfo enemy = {
	3, //bank
	&enemy_internal, //data
};