#include "Banks/SetBank8.h"

#include "../res/src/window.h"
#include "../res/src/diagnew.h"
#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/map4.h"
#include "../res/src/archer.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"


extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 collision_tiles[] ;
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next;
extern INT8 load_next_b;
extern INT8 load_next_s;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 show_diag;

extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern struct Sprite* scrigno_coin;
extern struct Sprite* scrigno_dcoin;
extern struct Sprite* scrigno_shield;
extern struct Sprite* scrigno_up;

extern void ShowWindow();
extern void ShowWindowDiag();
extern void UpdateHUD();
extern struct Sprite* spawn_item(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

//Maps
const struct MapInfo* map_4[] = {
	&map4
};
//Levels
const struct MapInfo** maps4[] = {map_4};

void Start_StateGame4() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	SHOW_SPRITES;
	//SCROLL
	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	const struct MapInfo** level_maps_s = maps4[0];
	UINT8 map_w, map_h;
	GetMapSize(level_maps_s[0], &map_w, &map_h);
	ScrollFindTile(level_maps_s[0], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(level_maps_s[0], collision_tiles, 0);
	SHOW_BKG;

	//INIT ARCHER
	if (archer_data->ups > 0 & archer_data->ups != ups){
		 ups = archer_data->ups;
	}
	archer_data->ups =ups;
	archer_data->hp = hp;
	archer_data->coins = coins;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow();
	
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

}


void Update_StateGame4() {
	
	if(load_next) {
		switch(load_next){
			case 1: //stage
			case -1:
				current_map += load_next;
			break;
		}
		load_next = 0;
		SetState(StateGame4);
	}
	
	if(load_next_s){
		load_next_s = 0;
		SetState(StateSecret);
	}
	
	if(load_next_b){
		switch(load_next_b){
			case 1: //vado allo StateBoss
				if(archer_state != STATE_DIAG){
					load_next_b = 0;
					SetState(StateBoss);//StateBoss
				}
			break;
			/*case 2: // provengo dal boss, vado al next level
			break;*/
		}
	}
	
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow();
		return;
	}
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag();
			return;
		}
	}
	else{	
		if (amulet != archer_data->amulet){
			amulet = archer_data->amulet;
			UpdateHUD();
		}
		if (coins != archer_data->coins){
			coins = archer_data->coins;
			UpdateHUD();
		}
		if (hp != archer_data->hp){
			hp = archer_data->hp;
			UpdateHUD();
		}
		if (ups != archer_data->ups){
			ups = archer_data->ups;
			UpdateHUD();
		}	
		if(archer_data->tool == level_tool){
			UpdateHUD();
		}
	}
}