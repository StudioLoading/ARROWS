#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"

IMPORT_TILES(tiles);
IMPORT_TILES(tiles4);
IMPORT_TILES(tiles6);
IMPORT_TILES(tiles7);
IMPORT_TILES(tilesanims);
IMPORT_TILES(tilesanimsmapworld);
IMPORT_TILES(tilesanimscutscene);
IMPORT_TILES(tilescredit);
IMPORT_TILES(tilesanimcredit);

extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 archer_tool;
extern INT8 level_tool;
extern INT8 is_on_boss;
extern UINT8 current_cutscene;

UINT8 bank_tiles = BANK(tiles);
UINT8 bank_tiles4 = BANK(tiles4);
UINT8 bank_tilesanims = BANK(tilesanims);
UINT8 bank_tilesanimsmapworld = BANK(tilesanimsmapworld);
UINT8 bank_tilescredit = BANK(tilescredit);
UINT8 bank_tilesanimcredit = BANK(tilesanimcredit);


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
		case 5u:
		    set_bkg_data(first_tile, nb_tiles, tilesanimscutscene.data+((16u) * first_tile));
		break;
		case 6u:
		    set_bkg_data(first_tile, nb_tiles, tiles6.data+((16u) * first_tile));
		break;
		case 7u:
		    set_bkg_data(first_tile, nb_tiles, tiles7.data+((16u) * first_tile));
		break;
		case 8u:
		    set_bkg_data(first_tile, nb_tiles, tilescredit.data+((16u) * first_tile));
		break;
		case 9u:
		    set_bkg_data(first_tile, nb_tiles, tilesanimcredit.data+((16u) * first_tile));
		break;
	}
    SWITCH_ROM(save);
}

void Anim_StudioLoading_0() BANKED{
	set_banked_bkg_data(14u, 1u, 8u, BANK(tilescredit));
	set_banked_bkg_data(15u, 1u, 8u, BANK(tilescredit));
}
void Anim_StudioLoading_1() BANKED{
	set_banked_bkg_data(14u, 1u, 9u, BANK(tilesanimcredit));
	set_banked_bkg_data(15u, 1u, 9u, BANK(tilesanimcredit));
}

void Anim_Tiles_0() BANKED{
	//spuncioni0
	if(current_level < 5u){
		set_banked_bkg_data(2u, 1u, 0u, BANK(tiles));
		set_banked_bkg_data(20u, 1u, 0u, BANK(tiles));
		set_banked_bkg_data(23u, 1u, 0u, BANK(tiles));
		set_banked_bkg_data(29u, 1u, 0u, BANK(tiles));
	}
	//sliders0
	if(current_level < 3u){
		set_banked_bkg_data(99u, 1u, 0u, BANK(tiles));// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_banked_bkg_data(111u, 1u, 0u, BANK(tiles));// + 16u * 111 tile index
		set_banked_bkg_data(119u, 1u, 0u, BANK(tiles));// + 16u * 119 tile index		
	}else if (current_level > 2u){
		set_banked_bkg_data(99u, 1u, 4u, BANK(tiles4));// + 16u * 99 tile index SLIDING UP TILES 99 100
		set_banked_bkg_data(111u, 1u, 4u, BANK(tiles4));// + 16u * 111 tile index
		set_banked_bkg_data(119u, 1u, 4u, BANK(tiles4));// + 16u * 119 tile index				
	}	
	if(current_level < 2 && is_on_boss == -1){// && archer_tool != level_tool
		//prisoner00
		set_banked_bkg_data(4u, 1u, 0u, BANK(tiles));
		//prisoner10
		set_banked_bkg_data(30u, 1u, 0u, BANK(tiles));
		//prisoner20
		set_banked_bkg_data(58u, 1u, 0u, BANK(tiles));
	}
	if(current_level < 2u || current_cutscene == 21u){
	//waterfalls0
		set_banked_bkg_data(120u, 1u, 0u, BANK(tiles));// + 16u * 120 tile index
		set_banked_bkg_data(123u, 1u, 0u, BANK(tiles));// + 16u * 123 tile index
		set_banked_bkg_data(125u, 1u, 0u, BANK(tiles));// + 16u * 125 tile index
		set_banked_bkg_data(112u, 1u, 0u, BANK(tiles));// + 16u * 112 tile index
		//candle0
		set_banked_bkg_data(24u, 1u, 0u, BANK(tiles));// + 16u * 24 candle
	}	
	//waters0
	if (current_level < 3u){ //I use 37 for water surface
		set_banked_bkg_data(38u, 1u, 0u, BANK(tiles));
		set_banked_bkg_data(39u, 1u, 0u, BANK(tiles));
	}	
	if(current_level == 2u){		
		//sky0
		set_banked_bkg_data(87u, 1u, 0u, BANK(tiles));///+ 16u * 87 tile index
		set_banked_bkg_data(88u, 1u, 0u, BANK(tiles));///+ 16u * 88 tile index
	}
	if(current_level == 3u){
		//rain0
		set_banked_bkg_data(36u, 1u, 4u, BANK(tiles4));//16u * 36u tile index
		set_banked_bkg_data(37u, 1u, 4u, BANK(tiles4));//16u * 37u tile index
		//clouds0
		set_banked_bkg_data(93u, 1u, 4u, BANK(tiles4));///+ 16u * 93 tile index
		set_banked_bkg_data(94u, 1u, 4u, BANK(tiles4));// + 16u * 94 tile index
		//clouds1
		set_banked_bkg_data(100u, 1u, 4u, BANK(tiles4));///+ 16u * 100 tile index
		set_banked_bkg_data(101u, 1u, 4u, BANK(tiles4));// + 16u * 101 tile index	
	}
	if(current_level == 6u){
		set_banked_bkg_data(88u, 1u, 6u, BANK(tiles6));
	}
	if(current_level >= 7u){
		set_banked_bkg_data(43, 1u, 7u, BANK(tiles7));
		set_banked_bkg_data(91, 1u, 7u, BANK(tiles7));
		set_banked_bkg_data(92, 1u, 7u, BANK(tiles7));
	}
}

void Anim_Tiles_1() BANKED{
	
	//spuncioni1
	if(current_level < 5u){
		set_banked_bkg_data(2u, 1u, 1u, BANK(tilesanims));
		set_banked_bkg_data(20u, 1u, 1u, BANK(tilesanims));
		set_banked_bkg_data(23u, 1u, 1u, BANK(tilesanims));
		set_banked_bkg_data(29u, 1u, 1u, BANK(tilesanims));
	}
	//sliders1
	set_banked_bkg_data(99u, 1u, 1u, BANK(tilesanims));// + 16u * 99 tile index SLIDING UP TILES 99 100
	set_banked_bkg_data(111u, 1u, 1u, BANK(tilesanims));// + 16u * 111 tile index
	set_banked_bkg_data(119u, 1u, 1u, BANK(tilesanims));// + 16u * 119 tile index
	if(current_level < 2 && archer_tool != level_tool && is_on_boss == -1){
		//prisoner01
		set_banked_bkg_data(4u, 1u, 1u, BANK(tilesanims));
		//prisoner11
		set_banked_bkg_data(30u, 1u, 1u, BANK(tilesanims));
		//prisoner21
		set_banked_bkg_data(58u, 1u, 1u, BANK(tilesanims));
	}
	if(current_level < 2u || current_cutscene == 21u){
		//waterfalls1
		set_banked_bkg_data(120u, 1u, 1u, BANK(tilesanims));///+ 16u * 120 tile index
		set_banked_bkg_data(123u, 1u, 1u, BANK(tilesanims));///+ 16u * 123 tile index
		set_banked_bkg_data(125u, 1u, 1u, BANK(tilesanims));///+ 16u * 125 tile index
		set_banked_bkg_data(112u, 1u, 1u, BANK(tilesanims));// + 16u * 112 tile index
		//candle1
		set_banked_bkg_data(24u, 1u, 1u, BANK(tilesanims));// + 16u * 24 candle
	}
	//waters1
	if (current_level < 3u ){ //I use 37 for water surface
		set_banked_bkg_data(38u, 1u, 1u, BANK(tilesanims));
		set_banked_bkg_data(39u, 1u, 1u, BANK(tilesanims));
	}	
	if(current_level == 2u){
		//sky1
		set_banked_bkg_data(87u, 1u, 1u, BANK(tilesanims));///+ 16u * 87u tile index
		set_banked_bkg_data(88u, 1u, 1u, BANK(tilesanims));///+ 16u * 88u tile index
	}
	if(current_level == 3u){
		//rain1
		set_banked_bkg_data(36u, 1u, 1u, BANK(tilesanims));//16u * 36u tile index
		set_banked_bkg_data(37u, 1u, 1u, BANK(tilesanims));//16u * 37u tile index
		//clouds1
		set_banked_bkg_data(93u, 1u, 1u, BANK(tilesanims));///+ 16u * 93 tile index
		set_banked_bkg_data(94u, 1u, 1u, BANK(tilesanims));///+ 16u * 94 tile index
		//clouds1
		set_banked_bkg_data(100u, 1u, 1u, BANK(tilesanims));///+ 16u * 100 tile index
		set_banked_bkg_data(101u, 1u, 1u, BANK(tilesanims));// + 16u * 101 tile index	
	}
	if(current_level == 6u){
		set_banked_bkg_data(88u, 1u, 1u, BANK(tilesanims));
	}
	if(current_level >= 7u){
		set_banked_bkg_data(43u, 1u, 1u, BANK(tilesanims));
		set_banked_bkg_data(91, 1u, 1u, BANK(tilesanims));
		set_banked_bkg_data(92, 1u, 1u, BANK(tilesanims));
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

void CutsceneAmulet0() BANKED{
	set_banked_bkg_data(30u, 1u, 5, BANK(tilesanimscutscene));// 16 * 10
}
void CutsceneAmulet1() BANKED{
	set_banked_bkg_data(31u, 1u, 5, BANK(tilesanimscutscene));// 16 * 10
}
void CutsceneAmulet2() BANKED{
	set_banked_bkg_data(38u, 1u, 5, BANK(tilesanimscutscene));
}
void CutsceneAmulet3() BANKED{
	set_banked_bkg_data(39u, 1u, 5, BANK(tilesanimscutscene));
}
void WorldmapFinalFight() BANKED{//116 117 + 118 119
	set_banked_bkg_data(116u, 1u, 2, BANK(tilesanimsmapworld));
	set_banked_bkg_data(117u, 1u, 2, BANK(tilesanimsmapworld));
	set_banked_bkg_data(118u, 1u, 2, BANK(tilesanimsmapworld));
	set_banked_bkg_data(119u, 1u, 2, BANK(tilesanimsmapworld));
}