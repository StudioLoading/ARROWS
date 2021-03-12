#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char arrow_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc2,0x02,0x03,0xff,0xc2,0x02,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 1
	0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x00,
	0x00,0x00,0xaa,0x22,0x55,0xff,0xaa,0x88,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 2
	0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x0c,
	0x46,0x46,0x07,0xff,0x46,0x46,0x0c,0x0c,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 3
	0x00,0x00,0x00,0x00,0x14,0x00,0x22,0x04,
	0x12,0x20,0x08,0x02,0x95,0x08,0x52,0x85,
	0x30,0x42,0x10,0x20,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 4
	0x00,0x00,0x00,0x00,0x14,0x00,0x4c,0x00,
	0x34,0x0a,0x09,0x0f,0x82,0x07,0x54,0xff,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 5
	0x08,0x08,0x1c,0x1c,0x00,0x08,0x00,0x08,
	0x00,0x08,0x00,0x08,0x14,0x08,0x14,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 6
	0x08,0x08,0x14,0x18,0x08,0x08,0x14,0x0c,
	0x08,0x08,0x14,0x18,0x08,0x08,0x14,0x18,
	0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 7
	0x08,0x08,0x1c,0x1c,0x3e,0x3e,0x22,0x2a,
	0x00,0x08,0x00,0x08,0x14,0x1c,0x00,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 8
	0x08,0x04,0x04,0x02,0x08,0x04,0x10,0x08,
	0x0e,0x01,0x04,0x02,0x08,0x04,0x10,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 9
	0x20,0x38,0x90,0x78,0x28,0x18,0xd4,0x08,
	0x0c,0x08,0x60,0x18,0x08,0x08,0x00,0x08,
	0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 10
	0x14,0x08,0x14,0x08,0x00,0x08,0x00,0x08,
	0x00,0x08,0x00,0x08,0x1c,0x1c,0x08,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 11
	0x08,0x08,0x14,0x18,0x08,0x08,0x14,0x18,
	0x08,0x08,0x14,0x0c,0x08,0x08,0x14,0x18,
	0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 12
	0x00,0x08,0x14,0x1c,0x00,0x08,0x00,0x08,
	0x22,0x2a,0x3e,0x3e,0x1c,0x1c,0x08,0x08,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 13
	0x10,0x08,0x08,0x04,0x04,0x02,0x0e,0x01,
	0x10,0x08,0x08,0x04,0x04,0x02,0x08,0x04,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 14
	0x00,0x08,0x00,0x08,0x08,0x08,0x60,0x18,
	0x0c,0x08,0xd4,0x08,0x28,0x18,0x90,0x78,
	0x20,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 15
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x40,0x00,0x38,0x46,0x20,0x40,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

#include "TilesInfo.h"
const struct TilesInfoInternal arrow_internal = {
	8, //width
	16, //height
	16, //num_tiles
	arrow_tiles, //tiles
	0, //CGB palette
};
CODE struct TilesInfo arrow = {
	3, //bank
	&arrow_internal, //data
};