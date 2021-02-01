#include "Banks/SetBank2.h"

#include "../res/src/window.h"
#include "../res/src/diagnew.h"
#include "../res/src/diagface.h"
#include "../res/src/font.h"
#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\map2.h"
#include "..\res\src\mapsecret0.h"
#include "../res/src/archer.h"
#include "../res/src/arrow.h"
#include "../res/src/platform.h"
#include "../res/src/item.h"
#include "../res/src/key.h"
#include "../res/src/enemy.h"
#include "../res/src/scorpion.h"
#include "../res/src/porcupine.h"


#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"

#include "custom_datas.h"


UINT16 bg_palette[] = {PALETTE_FROM_HEADER(tiles)};

UINT16 sprites_palette[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

UINT8 collision_tiles[] = {1, 2, 3, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 40, 41, 42, 46, 0};//numero delle tile con collisioni e ultimo sempre zero

UINT8 amulet = 1u;
UINT8 coins = 0u;
INT8 ups = 3;
INT8 hp = 100;
INT8 level_tool = -1;

void WriteAMULET();
void WriteCOINS();
void WriteHP();
void WriteUPS();
void WriteMap();
void WriteTOOL();
void populate_00();
void populate_01();
void ShowWindow();
void ShowWindowDiag();

//Levels
INT8 load_next = 0;
INT8 load_next_s = 0;
INT8 load_next_b = 0;
UINT8 current_level = 0;
UINT8 current_map = 0;
const struct MapInfo* level_1[] = {
	&map,
	&map2
};
const struct MapInfo** levels[] = {level_1};

const char * const level_names[] = {"THE ZOO", "THE SEWERS"};

UINT16 drop_player_x;
UINT16 drop_player_y;

STATE archer_state;

INT8 show_diag;
INT8 showing_diag = 0;
/*
const char* diags_10 = "DIAG_10";
const char* diags_11 = "DIAG_\n11";

const char** diags_1[] = {
	diags_10,
	diags_11
};
const char*** diags[] = {diags_1};
*/
void Start_StateGame() {
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpritePlatform);
	SpriteManagerLoad(SpriteItem);
	SpriteManagerLoad(SpriteKey);
	SpriteManagerLoad(SpriteEnemy);
	SpriteManagerLoad(SpriteScorpion);
	SpriteManagerLoad(SpritePorcupine);
	SpriteManagerLoad(SpriteDiagface);
	SHOW_SPRITES;

	//SCROLL
	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	
	const struct MapInfo** lvls = levels[current_level];
	UINT8 map_w, map_h;
	GetMapSize(lvls[current_map], &map_w, &map_h);
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
		ScrollFindTile(lvls[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else{ //vengo da altra map
		ScrollFindTile(lvls[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(lvls[current_map], collision_tiles, 0);
	SHOW_BKG;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	
	

	//INIT ARCHER
	struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;
	if (archer_data->ups > 0 & archer_data->ups != ups){
		ups = archer_data->ups;
	}
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 99u;
	}
	archer_data->ups =ups;
	archer_data->hp = hp;
	archer_data->coins = coins;
	
	ShowWindow();
	
	if(archer_data->tool == level_tool){
		WriteTOOL();
	}
	
	switch(current_level){
		case 0:
			switch(current_map){
				case 0:
					level_tool = 6;
					//wrench
					if(archer_data->tool == 0){
						populate_00();
						struct Sprite* key_sprite = SpriteManagerAdd(SpriteKey, 46*8, 2*8);
						struct ItemInfo* datakey = (struct ItemInfo*)key_sprite->custom_data;
						datakey->type = 1;
						datakey->setup = 1u;
					}
				break;
				case 1:
					populate_01();
				break;
				default:
					current_map = 0;
					populate_00();
				break;
			}
		break;
		default:
			current_level = 0;
			current_map = 0;
			populate_00();
		break;
	}
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
}

void ShowWindow(){
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 32;
	InitWindow(0, 0, &window);
	SHOW_WIN;
	
	WriteAMULET();
	WriteCOINS();
	WriteHP();
	WriteUPS();
	WriteMap();
	
}

void ShowWindowDiag(){
	if (showing_diag == 0){	
		HIDE_WIN;
		//WINDOW
		WX_REG = 7;
		WY_REG = 144 - 32;
		InitWindow(0, 0, &diagnew);
		SHOW_WIN;
		showing_diag = 1;
	}
	ShowDiag();
}

void ShowDiag(){
	PRINT_POS(3,1);
	//char * d[] = diags[current_level];
	Printf("DIAG_10");
}

void populate_01(){
	//PLATFORMS
	UINT8 platform_count = 1;
	UINT8 platform_positions_x[] = {9}; //10
	UINT8 platform_positions_y[] = {21}; //30
	UINT8 plc = 0;
	for(plc=0; plc < platform_count; plc++){
		struct Sprite* platform_sprite = SpriteManagerAdd(SpritePlatform, platform_positions_x[plc]*8, platform_positions_y[plc]*8);
		struct PlatformInfo* dataplatform = (struct PlatformInfo*)platform_sprite->custom_data;
		dataplatform->initx = platform_positions_x[plc]*8;	
	}
	
	//ENEMIES
	UINT8 e_count = 3;
	UINT8 e_positions_x[] = {32, 15, 17};
	UINT8 e_positions_y[] = {9, 4, 39};
	INT8 e_types[] = {0, 1, 2}; //0=snake, 1=scorpion, 2=porcupine
	for(plc=0; plc < e_count; plc++){
		switch(e_types[plc]){
			case 1: SpriteManagerAdd(SpriteScorpion, e_positions_x[plc]*8, e_positions_y[plc]*8); break;
			case 2: SpriteManagerAdd(SpritePorcupine, e_positions_x[plc]*8, e_positions_y[plc]*8); break;
			default: SpriteManagerAdd(SpriteEnemy, e_positions_x[plc]*8, e_positions_y[plc]*8);
		}
	}
}

void populate_00(){

	INT8 count = 3;
	INT8 scrigni_positions_x[] = {9, 12, 6, 17};
	INT8 scrigni_positions_y[] = {14, 23, 4, 36};
	INT8 st [] = {1, 1, 1, 3};
	INT8 c = 0;
	//ITEM SCRIGNI
	for(c=0; c < count; c++){
		struct Sprite* scrigno_sprite = SpriteManagerAdd(SpriteItem, scrigni_positions_x[c]*8, scrigni_positions_y[c]*8);
		struct ItemInfo* datascrigno = (struct ItemInfo*)scrigno_sprite->custom_data;
		datascrigno->type = 10;
		datascrigno->setup = 1u;
		datascrigno->content_type = st[c]; 
	}
	
	//HIDDEN ITEMS
	INT8 invcount = 1;
	INT8 invc = 0;
	INT8 invitems_positions_x[] = {31}; //13
	INT8 invitems_positions_y[] = {27};//11
	INT8 iit [] = {3, 1};
	for(invc=0; invc < invcount; invc++){
		struct Sprite* item_sprite = SpriteManagerAdd(SpriteItem, invitems_positions_x[invc]*8, invitems_positions_y[invc]*8);
		struct ItemInfo* dataitem = (struct ItemInfo*)item_sprite->custom_data;
		dataitem->type = iit[invc];
		dataitem->setup = 1u;
	}
	
	
}

void Update_StateGame() {
	
	struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;

	if(load_next) {
		switch(load_next){
			case 1: //stage
			case -1:
				current_map += load_next;
			break;
		}
		load_next = 0;
		SetState(StateGame);
	}
	
	if(load_next_s){
		load_next_s = 0;
		SetState(StateSecret);
	}
	
	if(load_next_b){
		switch(load_next_b){
			case 1: //vado allo StateBoss
				load_next_b = 0;
				SetState(StateBoss);
			break;
			case 2: // provengo dal boss TODO
				load_next_b = 0;
				current_level++;
				current_map = 0;
			break;
		}
	}
	
	if(archer_state == STATE_DIAG){
		if (show_diag == 2){
			show_diag = -1;
			showing_diag = 0;
			ShowWindow();
			return;
		}
		if(show_diag > 0 ){
			ShowWindowDiag();
			return;
		}
		if(show_diag < 0 ){
			ShowWindow();
			return;
		}
	}
	if(archer_state != STATE_DIAG){
		if (amulet != archer_data->amulet){
			amulet = archer_data->amulet;
			WriteAMULET();		
		}
		if (coins != archer_data->coins){
			coins = archer_data->coins;
			WriteCOINS();
		}
		if (hp != archer_data->hp){
			hp = archer_data->hp;
			WriteHP();
		}
		if (ups != archer_data->ups){
			ups = archer_data->ups;
			WriteUPS();
		}
		if(archer_data->tool == level_tool){
			WriteTOOL();
		}
	}	
	
}

void WriteAMULET(){
	PRINT_POS(13,1);
	switch (amulet){
		case 1: Printf("$"); break;
		case 2: Printf("]"); break;
		case 3: Printf("["); break;
		case 4: Printf("#"); break;
		case 5: Printf("@"); break;
		default: Printf("$"); break;
	}	
}

void WriteMap(){
	PRINT_POS(1, 3);
	Printf(level_names[current_level]);	
}

void WriteCOINS(){
	PRINT_POS(17, 1);
	if (coins > 9u){
		Printf("%d", coins);
	}else{
		Printf("0%d", coins);
	}
}

void WriteHP(){	
	PRINT_POS(7, 1);
	if (hp < 10){
		Printf("00%d", hp);
	}
	if (hp > 9 & hp < 100){
		Printf("0%d", hp);
	}
	if (hp >= 100){
		Printf("%d", hp);	
	}
}

void WriteTOOL(){
	switch(level_tool){
		case 6:
			PRINT_POS(11, 1);
			Printf("{");
		break;
		case 7:
			PRINT_POS(11, 1);
			Printf("<");
		break;
	}
}

void WriteUPS(){
	PRINT_POS(2, 1); //up
	if (ups > 9){Printf("%d", ups);}
	else{Printf("0%d", ups);}
}
