#pragma bank 4

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char mapsecret0_map[] = {
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x15,0x14,
	0x15,0x14,0x09,0x00,0x00,0x00,0x00,0x00,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x14,
	0x14,0x14,0x14,0x15,0x14,0x14,0x00,0x00,0x00,0x00,
	0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x14,0x14,0x14,0x14,0x15,0x14,0x15,0x14,
	0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x14,0x14,0x15,
	0x14,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x14,0x15,0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x15,0x14,0x15,0x14,0x00,0x00,
	0x00,0x00,0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x14,0x15,
	0x15,0x14,0x15,0x14,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x15,0x15,0x14,0x15,0x14,0x15,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2b,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x14,0x15,0x14,0x15,
	0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x2c,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x15,0x14,0x15,0x14,0x15,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x15,0x15,0x13,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x14,0x15,0x14,0x15,0x14,0x00,
	0x00,0x00,0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x02,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14
};
#include "tiles.h"
#include "MapInfo.h"
const struct MapInfoInternal mapsecret0_internal = {
	mapsecret0_map, //map
	24, //width
	24, //height
	0, //attributes
	&tiles, //tiles info
};
CODE struct MapInfo mapsecret0 = {
	4, //bank
	&mapsecret0_internal, //data
};