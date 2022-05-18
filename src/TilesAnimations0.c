#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"

IMPORT_TILES(tiles);
IMPORT_TILES(tiles4);
IMPORT_TILES(tilesanims);
IMPORT_TILES(tilesanimsmapworld);

extern UINT8 current_level;
extern UINT8 current_map;

UINT8 bank_tiles = BANK(tiles);
UINT8 bank_tiles4 = BANK(tiles4);
UINT8 bank_tilesanims = BANK(tilesanims);
UINT8 bank_tilesanimsmapworld = BANK(tilesanimsmapworld);


void set_banked_bkg_data(UINT8 first_tile, UINT8 nb_tiles, UINT8 tiles_used, UINT8 bank) NONBANKED {
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);
	switch(tiles_used){
		case 0u:
    		set_bkg_data(first_tile, nb_tiles, tiles.data+((16u) * first_tile));
		break;
		case 1u:
		    set_bkg_data(first_tile, nb_tiles, tilesanims.data+((16u) * first_tile));
		break;
		case 2u:
		    set_bkg_data(first_tile, nb_tiles, tilesanimsmapworld.data+((16u) * first_tile));
		break;
		case 4u:
		    set_bkg_data(first_tile, nb_tiles, tiles4.data+((16u) * first_tile));
		break;
	}
    SWITCH_ROM(save);
}

void Anim_Tiles_0() BANKED{
	//spuncioni0
	set_banked_bkg_data(2u, 1u, 0, BANK(tiles));
	set_banked_bkg_data(20u, 1u, 0, BANK(tiles));
	set_banked_bkg_data(23u, 1u, 0, BANK(tiles));
	set_banked_bkg_data(29u, 1u, 0, BANK(tiles));
	//sliders0
	if(current_level < 3){
		set_banked_bkg_data(99u, 1u, 0, BANK(tiles));// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_banked_bkg_data(111u, 1u, 0, BANK(tiles));// + 16u * 111 tile index
		set_banked_bkg_data(119u, 1u, 0, BANK(tiles));// + 16u * 119 tile index		
	}else if (current_level > 4){
		set_banked_bkg_data(99u, 1u, 0, BANK(tiles));// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_banked_bkg_data(111u, 1u, 0, BANK(tiles));// + 16u * 111 tile index
		set_banked_bkg_data(119u, 1u, 0, BANK(tiles));// + 16u * 119 tile index				
	}	
	//prisoner00
	set_banked_bkg_data(4u, 1u, 0, BANK(tiles));
	//prisoner10
	set_banked_bkg_data(30u, 1u, 0, BANK(tiles));
	//prisoner20
	set_banked_bkg_data(58u, 1u, 0, BANK(tiles));
	//waterfalls0
	set_banked_bkg_data(120u, 1u, 0, BANK(tiles));// + 16u * 120 tile index
	set_banked_bkg_data(123u, 1u, 0, BANK(tiles));// + 16u * 123 tile index
	set_banked_bkg_data(125u, 1u, 0, BANK(tiles));// + 16u * 125 tile index
	set_banked_bkg_data(112u, 1u, 0, BANK(tiles));// + 16u * 112 tile index
	set_banked_bkg_data(24u, 1u, 0, BANK(tiles));// + 16u * 24 candle
	//sky0
	set_banked_bkg_data(87u, 1u, 0, BANK(tiles));///+ 87u * 100 tile index
	set_banked_bkg_data(88u, 1u, 0, BANK(tiles));///+ 88u * 101 tile index
}

void Anim_Tiles_1() BANKED{
	//spuncioni1
	set_banked_bkg_data(2u, 1u, 1, BANK(tilesanims));
	set_banked_bkg_data(20u, 1u, 1, BANK(tilesanims));
	set_banked_bkg_data(23u, 1u, 1, BANK(tilesanims));
	set_banked_bkg_data(29u, 1u, 1, BANK(tilesanims));
	//sliders1
	set_banked_bkg_data(99u, 1u, 1, BANK(tilesanims));// + 16u * 99 tile index SLIDING UP TILES 99 100
	set_banked_bkg_data(111u, 1u, 1, BANK(tilesanims));// + 16u * 111 tile index
	set_banked_bkg_data(119u, 1u, 1, BANK(tilesanims));// + 16u * 119 tile index
	//prisoner01
	set_banked_bkg_data(4u, 1u, 1, BANK(tilesanims));
	//prisoner11
	set_banked_bkg_data(30u, 1u, 1, BANK(tilesanims));
	//prisoner21
	set_banked_bkg_data(58u, 1u, 1, BANK(tilesanims));
	//waterfalls1
	set_banked_bkg_data(120u, 1u, 1, BANK(tilesanims));///+ 16u * 120 tile index
	set_banked_bkg_data(123u, 1u, 1, BANK(tilesanims));///+ 16u * 123 tile index
	set_banked_bkg_data(125u, 1u, 1, BANK(tilesanims));///+ 16u * 125 tile index
	set_banked_bkg_data(112u, 1u, 1, BANK(tilesanims));// + 16u * 112 tile index
	set_banked_bkg_data(24u, 1u, 1, BANK(tilesanims));// + 16u * 24 candle
	//waters1
	if (current_level != 2u && current_level != 1u ){ //I use 37 for water surface
		set_banked_bkg_data(37u, 1u, 4, BANK(tiles4));
	}else{
		set_banked_bkg_data(28u, 1u, 4, BANK(tiles4));// + 16u * 77 tile index
	}	
	//sky1
	set_banked_bkg_data(87u, 1u, 1, BANK(tilesanims));///+ 16u * 87u tile index
	set_banked_bkg_data(88u, 1u, 1, BANK(tilesanims));///+ 16u * 88u tile index
	if(current_level == 3u){
		//rain1
		set_banked_bkg_data(36u, 1u, 1, BANK(tilesanims));//16u * 36u tile index
		set_banked_bkg_data(37u, 1u, 1, BANK(tilesanims));//16u * 37u tile index
		//clouds1
		set_banked_bkg_data(93u, 1u, 4, BANK(tiles4));///+ 16u * 93 tile index
		set_banked_bkg_data(94u, 1u, 4, BANK(tiles4));///+ 16u * 94 tile index
		set_banked_bkg_data(100u, 1u, 4, BANK(tiles4));///+ 16u * 100 tile index
		set_banked_bkg_data(101u, 1u, 4, BANK(tiles4));// + 16u * 101 tile index	
	}
}

void WorldmapQuiverStone() BANKED{
	set_banked_bkg_data(44u, 1u, 2, BANK(tilesanimsmapworld));// 16 * 1
}
void WorldmapQuiverThunder() BANKED{
	set_banked_bkg_data(45u, 1u, 2, BANK(tilesanimsmapworld));// 16 * 3
}
void WorldmapQuiverIce() BANKED{
	set_banked_bkg_data(56u, 1u, 2, BANK(tilesanimsmapworld));// 16 * 6
}
void WorldmapQuiverFire() BANKED{
	set_banked_bkg_data(47u, 1u, 2, BANK(tilesanimsmapworld));// 16 * 10
}