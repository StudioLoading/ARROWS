#include "Banks/SetBank0.h"

#include <gb/gb.h>

#include "ZGBMain.h"

IMPORT_TILES(tiles);
IMPORT_TILES(tiles4);
IMPORT_TILES(tiles6);
IMPORT_TILES(tilesanims);
IMPORT_TILES(tilesanimsmapworld);

extern UINT8 current_level;
extern UINT8 current_map;

UINT8 anim_bank = BANK(tilesanims);

void AnimSpuncioni0() BANKED{
	SWITCH_ROM(BANK(tiles));
	set_bkg_data(2u, 1u, tiles.data+32u);
	set_bkg_data(20u, 1u, tiles.data+320u);
	set_bkg_data(23u, 1u, tiles.data+368u);
	set_bkg_data(29u, 1u, tiles.data+464u);
	SWITCH_ROM(0);
}

void AnimSpuncioni1() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(2u, 1u, tilesanims.data+32u);
	set_bkg_data(20u, 1u, tilesanims.data+320u);
	set_bkg_data(23u, 1u, tilesanims.data+368u);
	set_bkg_data(29u, 1u, tilesanims.data+464u);
	SWITCH_ROM(0);
}

void AnimSliders0() BANKED{
	SWITCH_ROM(BANK(tiles));
	if(current_level < 3){
		set_bkg_data(99u, 1u, tiles.data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_bkg_data(111u, 1u, tiles.data+1776u);// + 16u * 111 tile index
		set_bkg_data(119u, 1u, tiles.data+1904u);// + 16u * 119 tile index		
	}else if (current_level > 4){
		set_bkg_data(99u, 1u, tiles.data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_bkg_data(111u, 1u, tiles.data+1776u);// + 16u * 111 tile index
		set_bkg_data(119u, 1u, tiles.data+1904u);// + 16u * 119 tile index				
	}
	SWITCH_ROM(0);
}

void AnimSliders1() BANKED{	
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(99u, 1u, tilesanims.data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
	set_bkg_data(111u, 1u, tilesanims.data+1776u);// + 16u * 111 tile index
	set_bkg_data(119u, 1u, tilesanims.data+1904u);// + 16u * 119 tile index
	SWITCH_ROM(0);
}

void AnimWaterfalls0() BANKED{ //re-assign the tile to its mapped value
	SWITCH_ROM(BANK(tiles));
	set_bkg_data(120u, 1u, tiles.data+1920u);// + 16u * 120 tile index
	set_bkg_data(123u, 1u, tiles.data+1968u);// + 16u * 123 tile index
	set_bkg_data(125u, 1u, tiles.data+2000u);// + 16u * 125 tile index
	set_bkg_data(112u, 1u, tiles.data+1792u);// + 16u * 112 tile index
	set_bkg_data(24u, 1u, tiles.data+384u);// + 16u * 24 candle
	SWITCH_ROM(0);
}

void AnimWaters0() BANKED{
	SWITCH_ROM(BANK(tiles4));
	if(current_level != 5u){
		if (current_level != 2u && current_level != 1u){ //I use 37 for water surface
			set_bkg_data(37u, 1u, tiles4.data+1216u);
		}else{
			set_bkg_data(28u, 1u, tiles4.data+1216u);// + 16u * 76 tile index
		}
	}
	SWITCH_ROM(0);
}

void AnimWaters1() BANKED{
	SWITCH_ROM(BANK(tiles4));
	if (current_level != 2u && current_level != 1u ){ //I use 37 for water surface
		set_bkg_data(37u, 1u, tiles4.data+1232u);
	}else{
		set_bkg_data(28u, 1u, tiles4.data+1232u);// + 16u * 77 tile index
	}
	SWITCH_ROM(0);
}

void AnimWaterfalls1() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(120u, 1u, tilesanims.data+1920u);///+ 16u * 120 tile index
	set_bkg_data(123u, 1u, tilesanims.data+1968u);///+ 16u * 123 tile index
	set_bkg_data(125u, 1u, tilesanims.data+2000u);///+ 16u * 125 tile index
	//AnimSliders1();
	set_bkg_data(112u, 1u, tilesanims.data+1792u);// + 16u * 112 tile index
	set_bkg_data(24u, 1u, tilesanims.data+384u);// + 16u * 24 candle
	SWITCH_ROM(0);
}

void AnimClouds0() BANKED{
	SWITCH_ROM(BANK(tiles4));
	set_bkg_data(93u, 1u, tiles4.data+1600u);///+ 16u * 100 tile index
	set_bkg_data(94u, 1u, tiles4.data+1616u);///+ 16u * 101 tile index
	set_bkg_data(100u, 1u, tiles4.data+1488u);///+ 16u * 93 tile index
	set_bkg_data(101u, 1u, tiles4.data+1504u);// + 16u * 94 tile index
	SWITCH_ROM(0);
}

void AnimClouds1() BANKED{
	SWITCH_ROM(BANK(tiles4));
	set_bkg_data(93u, 1u, tiles4.data+1488u);///+ 16u * 93 tile index
	set_bkg_data(94u, 1u, tiles4.data+1504u);///+ 16u * 94 tile index
	set_bkg_data(100u, 1u, tiles4.data+1600u);///+ 16u * 100 tile index
	set_bkg_data(101u, 1u, tiles4.data+1616u);// + 16u * 101 tile index	
	SWITCH_ROM(0);
}

void AnimSky0() BANKED{
	SWITCH_ROM(BANK(tiles));
	set_bkg_data(87u, 1u, tiles.data+1392u);///+ 87u * 100 tile index
	set_bkg_data(88u, 1u, tiles.data+1408u);///+ 88u * 101 tile index
	SWITCH_ROM(0);
}

void AnimSky1() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(87u, 1u, tilesanims.data+1392u);///+ 87u * 100 tile index
	set_bkg_data(88u, 1u, tilesanims.data+1408u);///+ 88u * 101 tile index
	SWITCH_ROM(0);
}

void AnimRain0() BANKED{
	SWITCH_ROM(BANK(tiles4));
	set_bkg_data(36u, 1u, tiles4.data+576u);
	set_bkg_data(37u, 1u, tiles4.data+592u);
	SWITCH_ROM(0);
}

void AnimRain1() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(36u, 1u, tilesanims.data+576u);
	set_bkg_data(37u, 1u, tilesanims.data+592u);
	SWITCH_ROM(0);
}


void AnimPrisoner00() BANKED{
	SWITCH_ROM(BANK(tiles));
	set_bkg_data(4u, 1u, tiles.data+64u);
	SWITCH_ROM(0);
}
void AnimPrisoner01() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(4u, 1u, tilesanims.data+64u);
	SWITCH_ROM(0);
}
void AnimPrisoner10() BANKED{
	SWITCH_ROM(BANK(tiles));
	set_bkg_data(30u, 1u, tiles.data+480u);
	SWITCH_ROM(0);
}
void AnimPrisoner11() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(30u, 1u, tilesanims.data+480u);
	SWITCH_ROM(0);
}
void AnimPrisoner20() BANKED{
	SWITCH_ROM(BANK(tiles));
	set_bkg_data(58u, 1u, tiles.data+928u);
	SWITCH_ROM(0);
}
void AnimPrisoner21() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(58u, 1u, tilesanims.data+928u);
	SWITCH_ROM(0);
}

void WorldmapQuiverStone() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(44u, 1u, tilesanims.data+16u);// 16 * 1
	SWITCH_ROM(0);
}
void WorldmapQuiverThunder() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(45u, 1u, tilesanims.data+48u);// 16 * 3
	SWITCH_ROM(0);
}
void WorldmapQuiverIce() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(56u, 1u, tilesanims.data+96u);// 16 * 6
	SWITCH_ROM(0);
}
void WorldmapQuiverFire() BANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(47u, 1u, tilesanims.data+160u);// 16 * 10
	SWITCH_ROM(0);
}