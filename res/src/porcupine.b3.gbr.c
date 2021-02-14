#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char porcupine_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x54,
	0x2a,0x2a,0x54,0x5e,0xaa,0xad,0x50,0x7e,
	0xa4,0xfc,0x48,0x70,0x10,0x60,0x50,0x50,
	
	//Frame 1
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,
	0x0a,0x0a,0x54,0x56,0x28,0x2f,0x52,0x7d,
	0xa4,0xfe,0x48,0x70,0x10,0x60,0x28,0x28,
	
	//Frame 2
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0a,0x04,0x00,0x54,0x5e,
	0x2a,0x2a,0x54,0x5e,0xaa,0xad,0x50,0x7e,
	0xa4,0xfc,0x48,0x70,0x10,0x60,0x50,0x50,
	
	//Frame 3
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x11,0x00,0x0a,0x00,0x00,0x54,0x5e,
	0x2a,0x3b,0x54,0x5e,0xaa,0xad,0x50,0x7e,
	0xa4,0xfc,0x48,0x70,0x10,0x60,0x50,0x50,
	
	//Frame 4
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x11,0x00,0x00,0x00,0x00,0x54,0x54,
	0x2a,0x3b,0x54,0x5e,0xaa,0xad,0x50,0x7e,
	0xa4,0xfc,0x48,0x70,0x10,0x60,0x50,0x50,
	
	//Frame 5
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,
	0x15,0x15,0xaa,0xaa,0x55,0x55,0xae,0xfe,
	0x47,0x7b,0x90,0xec,0x38,0xc8,0xc0,0xc0,
	
	//Frame 6
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x54,
	0x2a,0x2a,0x54,0x5e,0xaa,0xad,0x50,0x7e,
	0xa4,0xfc,0x48,0x70,0x10,0x60,0x20,0x20
};

#include "TilesInfo.h"
const struct TilesInfoInternal porcupine_internal = {
	8, //width
	16, //height
	7, //num_tiles
	porcupine_tiles, //tiles
	0, //CGB palette
};
CODE struct TilesInfo porcupine = {
	3, //bank
	&porcupine_internal, //data
};