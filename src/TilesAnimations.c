#pragma bank 3

#include <gb/gb.h>

#include "../res/src/tiles.h"
#include "../res/src/tiles4.h"
#include "../res/src/tiles6.h"
#include "../res/src/tilesanims.h"
#include "../res/src/tilesanimsmapworld.h"

extern UINT8 current_level;
extern UINT8 current_map;

void AnimSliders0() __banked{
	if(current_level < 3){
		set_bkg_data(99u, 1u, tiles.data->data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_bkg_data(111u, 1u, tiles.data->data+1776u);// + 16u * 111 tile index
		set_bkg_data(119u, 1u, tiles.data->data+1904u);// + 16u * 119 tile index		
	}else if (current_level > 4){
		set_bkg_data(99u, 1u, tiles.data->data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_bkg_data(111u, 1u, tiles.data->data+1776u);// + 16u * 111 tile index
		set_bkg_data(119u, 1u, tiles.data->data+1904u);// + 16u * 119 tile index				
	}
}

void AnimSliders1() __banked{	
	set_bkg_data(99u, 1u, tilesanims.data->data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
	set_bkg_data(111u, 1u, tilesanims.data->data+1776u);// + 16u * 111 tile index
	set_bkg_data(119u, 1u, tilesanims.data->data+1904u);// + 16u * 119 tile index
}

void AnimWaters0() __banked{ //re-assign the tile to its mapped value
	set_bkg_data(120u, 1u, tiles.data->data+1920u);// + 16u * 120 tile index
	set_bkg_data(123u, 1u, tiles.data->data+1968u);// + 16u * 123 tile index
	set_bkg_data(125u, 1u, tiles.data->data+2000u);// + 16u * 125 tile index
	AnimSliders0();
	set_bkg_data(112u, 1u, tiles.data->data+1792u);// + 16u * 112 tile index
	if(current_level != 5u){
		if (current_level != 2u && current_level != 1u){ //I use 37 for water surface
			set_bkg_data(37u, 1u, tiles4.data->data+1216u);
		}else{
			set_bkg_data(28u, 1u, tiles4.data->data+1216u);// + 16u * 76 tile index
		}
	}
	set_bkg_data(24u, 1u, tiles.data->data+384u);// + 16u * 24 candle
	
}

void AnimWaters1() __banked{
	set_bkg_data(120u, 1u, tilesanims.data->data+1920u);///+ 16u * 120 tile index
	set_bkg_data(123u, 1u, tilesanims.data->data+1968u);///+ 16u * 123 tile index
	set_bkg_data(125u, 1u, tilesanims.data->data+2000u);///+ 16u * 125 tile index
	AnimSliders1();
	set_bkg_data(112u, 1u, tilesanims.data->data+1792u);// + 16u * 112 tile index
	
	if (current_level != 2u && current_level != 1u ){ //I use 37 for water surface
		set_bkg_data(37u, 1u, tiles4.data->data+1232u);
	}else{
		set_bkg_data(28u, 1u, tiles4.data->data+1232u);// + 16u * 77 tile index
	}
	set_bkg_data(24u, 1u, tilesanims.data->data+384u);// + 16u * 24 candle

}

void AnimClouds0() __banked{
	set_bkg_data(93u, 1u, tiles4.data->data+1600u);///+ 16u * 100 tile index
	set_bkg_data(94u, 1u, tiles4.data->data+1616u);///+ 16u * 101 tile index
	set_bkg_data(100u, 1u, tiles4.data->data+1488u);///+ 16u * 93 tile index
	set_bkg_data(101u, 1u, tiles4.data->data+1504u);// + 16u * 94 tile index
}

void AnimClouds1() __banked{
	set_bkg_data(93u, 1u, tiles4.data->data+1488u);///+ 16u * 93 tile index
	set_bkg_data(94u, 1u, tiles4.data->data+1504u);///+ 16u * 94 tile index
	set_bkg_data(100u, 1u, tiles4.data->data+1600u);///+ 16u * 100 tile index
	set_bkg_data(101u, 1u, tiles4.data->data+1616u);// + 16u * 101 tile index	
}

void AnimSky0() __banked{
	set_bkg_data(87u, 1u, tiles.data->data+1392u);///+ 87u * 100 tile index
	set_bkg_data(88u, 1u, tiles.data->data+1408u);///+ 88u * 101 tile index
}

void AnimSky1() __banked{
	set_bkg_data(87u, 1u, tilesanims.data->data+1392u);///+ 87u * 100 tile index
	set_bkg_data(88u, 1u, tilesanims.data->data+1408u);///+ 88u * 101 tile index
}

void AnimRain0() __banked{
	set_bkg_data(36u, 1u, tiles4.data->data+576u);
	set_bkg_data(37u, 1u, tiles4.data->data+592u);
}

void AnimRain1() __banked{
	set_bkg_data(36u, 1u, tilesanims.data->data+576u);
	set_bkg_data(37u, 1u, tilesanims.data->data+592u);
}

void AnimSpuncioni0() __banked{
	set_bkg_data(2u, 1u, tiles4.data->data+32u);
	set_bkg_data(20u, 1u, tiles4.data->data+320u);
	set_bkg_data(23u, 1u, tiles4.data->data+368u);
	set_bkg_data(29u, 1u, tiles4.data->data+464u);
}

void AnimSpuncioni1() __banked{
	set_bkg_data(2u, 1u, tilesanims.data->data+32u);
	set_bkg_data(20u, 1u, tilesanims.data->data+320u);
	set_bkg_data(23u, 1u, tilesanims.data->data+368u);
	set_bkg_data(29u, 1u, tilesanims.data->data+464u);
}

void AnimPrisoner00() __banked{
	set_bkg_data(4u, 1u, tiles.data->data+64u);
}
void AnimPrisoner01() __banked{
	set_bkg_data(4u, 1u, tilesanims.data->data+64u);
}
void AnimPrisoner10() __banked{
	set_bkg_data(30u, 1u, tiles.data->data+480u);
}
void AnimPrisoner11() __banked{
	set_bkg_data(30u, 1u, tilesanims.data->data+480u);
}
void AnimPrisoner20() __banked{
	set_bkg_data(58u, 1u, tiles.data->data+928u);
}
void AnimPrisoner21() __banked{
	set_bkg_data(58u, 1u, tilesanims.data->data+928u);
}

void WorldmapQuiverStone() __banked{
	set_bkg_data(53u, 1u, tilesanims.data->data+16u);// 16 * 1
}