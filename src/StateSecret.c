#include "Banks/SetBank2.h"

#include "../res/src/window.h"
#include "../res/src/font.h"
#include "..\res\src\tiles.h"
#include "..\res\src\mapsecret0.h"
#include "../res/src/archer.h"
#include "../res/src/arrow.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"

#include "custom_datas.h"


extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 collision_tiles[] ;
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next_s;
extern INT8 level_tool;
extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern STATE archer_state;


extern void WriteAMULET();
extern void WriteCOINS();
extern void WriteHP();
extern void WriteUPS();
extern void WriteMap();
extern void WriteTOOL();


//Secrets
UINT8 current_level_s = 0;
UINT8 current_map_s = 0;
const struct MapInfo* secret_1[] = {
	&mapsecret0
};
const struct MapInfo** secrets[] = {secret_1};


void populate_secret0();
void ShowSWindow();


void Start_StateSecret() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	SHOW_SPRITES;
	//SCROLL
	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	const struct MapInfo** level_maps_s = secrets[current_level_s];
	UINT8 map_w, map_h;
	GetMapSize(level_maps_s[current_map_s], &map_w, &map_h);
	ScrollFindTile(level_maps_s[current_map_s], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(level_maps_s[current_map_s], collision_tiles, 0);
	SHOW_BKG;

	//INIT ARCHER
	struct ArcherInfo* archer_data_s = (struct ArcherInfo*)scroll_target->custom_data;
	if (archer_data_s->ups > 0 & archer_data_s->ups != ups){
		 ups = archer_data_s->ups;
	}
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 99u;
	}
	archer_data_s->ups =ups;
	archer_data_s->hp = hp;
	archer_data_s->coins = coins;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowSWindow();
	
	//ITEMS
	switch(current_level_s){
		case 0:
			switch(current_map_s){
				case 0:
					populate_secret0();
				break;
			}
		break;
	}
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

}


void ShowSWindow(){
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

void populate_secret0(){
	INT8 invcount = 3;
	INT8 invc = 0;
	INT8 invitems_positions_x[] = {6,7,8};
	INT8 invitems_positions_y[] = {14,14,14};
	INT8 iit [] = {7, 7, 7};
	for(invc=0; invc < invcount; invc++){
		struct Sprite* item_sprite = SpriteManagerAdd(SpriteItem, invitems_positions_x[invc]*8, invitems_positions_y[invc]*8);
		struct ItemInfo* dataitem = (struct ItemInfo*)item_sprite->custom_data;
		dataitem->type = iit[invc];
		dataitem->collided = 1u;
		dataitem->setup = 1u;
	}
}

void Update_StateSecret() {
	
	struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;

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
	
	if(load_next_s){
		switch(load_next_s){
			case 1: //entro in secret
				current_map_s += load_next_s;
				WriteMap();
				load_next_s = 0;
				SetState(StateSecret);
			break;
			case -1: //torno dalla secret a game
				//load_next_s = 0;
				SetState(StateGame);
			break;
		}
	}

}
