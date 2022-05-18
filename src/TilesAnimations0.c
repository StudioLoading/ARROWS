#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"

IMPORT_TILES(tiles);
IMPORT_TILES(tilesanims);
IMPORT_TILES(tilesanimsmapworld);

extern UINT8 current_level;
extern UINT8 current_map;

extern UINT8 bank_tiles;
extern UINT8 bank_tilesanimsmapworld;

void Anim_Tiles_0() NONBANKED{
	UINT8 save = _current_bank;
	SWITCH_ROM(bank_tiles);
	//spuncioni0
	set_bkg_data(2u, 1u, tiles.data+32u);
	set_bkg_data(20u, 1u, tiles.data+320u);
	set_bkg_data(23u, 1u, tiles.data+368u);
	set_bkg_data(29u, 1u, tiles.data+464u);
	//sliders0
	if(current_level < 3){
		set_bkg_data(99u, 1u, tiles.data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_bkg_data(111u, 1u, tiles.data+1776u);// + 16u * 111 tile index
		set_bkg_data(119u, 1u, tiles.data+1904u);// + 16u * 119 tile index		
	}else if (current_level > 4){
		set_bkg_data(99u, 1u, tiles.data+1584u);// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_bkg_data(111u, 1u, tiles.data+1776u);// + 16u * 111 tile index
		set_bkg_data(119u, 1u, tiles.data+1904u);// + 16u * 119 tile index				
	}
	//waterfalls0
	set_bkg_data(120u, 1u, tiles.data+1920u);// + 16u * 120 tile index
	set_bkg_data(123u, 1u, tiles.data+1968u);// + 16u * 123 tile index
	set_bkg_data(125u, 1u, tiles.data+2000u);// + 16u * 125 tile index
	set_bkg_data(112u, 1u, tiles.data+1792u);// + 16u * 112 tile index
	set_bkg_data(24u, 1u, tiles.data+384u);// + 16u * 24 candle
	//sky0
	set_bkg_data(87u, 1u, tiles.data+1392u);///+ 87u * 100 tile index
	set_bkg_data(88u, 1u, tiles.data+1408u);///+ 88u * 101 tile index
	//prisoner00
	set_bkg_data(4u, 1u, tiles.data+64u);
	//prisoner10
	set_bkg_data(30u, 1u, tiles.data+480u);
	//prisoner20
	set_bkg_data(58u, 1u, tiles.data+928u);

	SWITCH_ROM(save);

}

void WorldmapQuiverStone() NONBANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(44u, 1u, tilesanims.data+16u);// 16 * 1
	SWITCH_ROM(0);
}
void WorldmapQuiverThunder() NONBANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(45u, 1u, tilesanims.data+48u);// 16 * 3
	SWITCH_ROM(0);
}
void WorldmapQuiverIce() NONBANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(56u, 1u, tilesanims.data+96u);// 16 * 6
	SWITCH_ROM(0);
}
void WorldmapQuiverFire() NONBANKED{
	SWITCH_ROM(BANK(tilesanims));
	set_bkg_data(47u, 1u, tilesanims.data+160u);// 16 * 10
	SWITCH_ROM(0);
}