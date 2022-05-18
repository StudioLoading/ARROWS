#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"

IMPORT_TILES(tiles4);
IMPORT_TILES(tilesanims);

extern UINT8 current_level;
extern UINT8 current_map;

extern UINT8 bank_tilesanims;
extern UINT8 bank_tiles4;


void set_banked_bkg_data_1(UINT8 first_tile, UINT8 nb_tiles, const UINT8 *data, UINT8 bank) NONBANKED {
    uint8_t save = _current_bank;
    SWITCH_ROM(bank);   
    set_bkg_data(first_tile, nb_tiles, data);
    SWITCH_ROM(save);
}

void Anim_Tiles_1(){
	//spuncioni1
	set_banked_bkg_data_1(2u, 1u, tilesanims.data+32u, bank_tilesanims);
	set_banked_bkg_data_1(20u, 1u, tilesanims.data+320u, bank_tilesanims);
	set_banked_bkg_data_1(23u, 1u, tilesanims.data+368u, bank_tilesanims);
	set_banked_bkg_data_1(29u, 1u, tilesanims.data+464u, bank_tilesanims);
	//sliders1
	set_banked_bkg_data_1(99u, 1u, tilesanims.data+1584u, bank_tilesanims);// + 16u * 99 tile index SLIDING UP TILES 99 100
	set_banked_bkg_data_1(111u, 1u, tilesanims.data+1776u, bank_tilesanims);// + 16u * 111 tile index
	set_banked_bkg_data_1(119u, 1u, tilesanims.data+1904u, bank_tilesanims);// + 16u * 119 tile index
	//prisoner01
	set_banked_bkg_data_1(4u, 1u, tilesanims.data+64u, bank_tilesanims);
	//prisoner11
	set_banked_bkg_data_1(30u, 1u, tilesanims.data+480u, bank_tilesanims);
	//prisoner21
	set_banked_bkg_data_1(58u, 1u, tilesanims.data+928u, bank_tilesanims);
	//waterfalls1
	set_banked_bkg_data_1(120u, 1u, tilesanims.data+1920u, bank_tilesanims);///+ 16u * 120 tile index
	set_banked_bkg_data_1(123u, 1u, tilesanims.data+1968u, bank_tilesanims);///+ 16u * 123 tile index
	set_banked_bkg_data_1(125u, 1u, tilesanims.data+2000u, bank_tilesanims);///+ 16u * 125 tile index
	set_banked_bkg_data_1(112u, 1u, tilesanims.data+1792u, bank_tilesanims);// + 16u * 112 tile index
	set_banked_bkg_data_1(24u, 1u, tilesanims.data+384u, bank_tilesanims);// + 16u * 24 candle
	//sky1
	set_banked_bkg_data_1(87u, 1u, tilesanims.data+1392u, bank_tilesanims);///+ 87u * 100 tile index
	set_banked_bkg_data_1(88u, 1u, tilesanims.data+1408u, bank_tilesanims);///+ 88u * 101 tile index
	//rain1
	set_banked_bkg_data_1(36u, 1u, tilesanims.data+576u, bank_tilesanims);
	set_banked_bkg_data_1(37u, 1u, tilesanims.data+592u, bank_tilesanims);

	Anim_Tiles_2();

}


void Anim_Tiles_2(){
	//waters1
	if (current_level != 2u && current_level != 1u ){ //I use 37 for water surface
		set_banked_bkg_data_1(37u, 1u, tiles4.data+1232u, bank_tiles4);
	}else{
		set_banked_bkg_data_1(28u, 1u, tiles4.data+1232u, bank_tiles4);// + 16u * 77 tile index
	}
	//clouds1
	set_banked_bkg_data_1(93u, 1u, tiles4.data+1488u, bank_tiles4);///+ 16u * 93 tile index
	set_banked_bkg_data_1(94u, 1u, tiles4.data+1504u, bank_tiles4);///+ 16u * 94 tile index
	set_banked_bkg_data_1(100u, 1u, tiles4.data+1600u, bank_tiles4);///+ 16u * 100 tile index
	set_banked_bkg_data_1(101u, 1u, tiles4.data+1616u, bank_tiles4);// + 16u * 101 tile index	
	
}