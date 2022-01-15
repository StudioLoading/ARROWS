#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char window_map[] = {
	0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x20,0x00,0x00,0x00,0x00,0x08,0x00,0x72,0x00
};
#include "tiles.h"
#include "MapInfo.h"
const struct MapInfoInternal window_internal = {
	window_map, //map
	20, //width
	1, //height
	0, //attributes
	&tiles, //tiles info
};
CODE struct MapInfo window = {
	3, //bank
	&window_internal, //data
};