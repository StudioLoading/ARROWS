#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char enemyCGB[] = {
	0x00,0x00,0x00,0x00
};

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
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x0c,0x00,0x1e,0x04,0x0f,0x00,
	0x1a,0x00,0x98,0x00,0x98,0x00,0x9c,0x00,
	0x8e,0x00,0xff,0x00,0x7f,0x00,0x2a,0x00,
	
	//Frame 3
	0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,
	0x0e,0x0e,0x0f,0x0b,0x1e,0x1e,0x0c,0x0c,
	0x18,0x18,0x00,0x98,0x98,0x98,0x10,0x9c,
	0x8e,0x8e,0x6d,0xff,0x33,0x7f,0x2a,0x2a
};

#include "TilesInfo.h"
const struct TilesInfoInternal enemy_internal = {
	8, //width
	16, //height
	4, //num_tiles
	enemy_tiles, //tiles
	enemyCGB, //CGB palette
};
CODE struct TilesInfo enemy = {
	3, //bank
	&enemy_internal, //data
};