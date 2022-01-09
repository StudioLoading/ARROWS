#include "Banks/SetBank7.h"


#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/mapsecret0.h"
#include "../res/src/archer.h"
#include "../res/src/arrow.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"

#include "custom_datas.h"


extern UINT8 collision_tiles[];
extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 archer_tool;
extern INT8 load_next_s;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_secret;
extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern struct Sprite* scrigno_coin;
extern struct Sprite* scrigno_dcoin;
extern struct Sprite* scrigno_shield;
extern struct Sprite* scrigno_up;
extern INT8 update_hud;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

extern void ShowWindow();
extern void UpdateHUD();
extern struct Sprite* spawn_item(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

//Secrets
const struct MapInfo* const secret_1[] = {
	&mapsecret0
};
const struct MapInfo** const secrets[] = {secret_1};

//void ShowSWindow();


void Start_StateSecret() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 7);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 7); //last param is the current bank we are in

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	SHOW_SPRITES;
	//SCROLL
	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	const struct MapInfo** level_maps_s = secrets[0];
	UINT8 map_w, map_h;
	GetMapSize(level_maps_s[0], &map_w, &map_h);
	ScrollFindTile(level_maps_s[0], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(level_maps_s[0], collision_tiles, 0);
	SHOW_BKG;

	//INIT ARCHER
	archer_data->hp = hp;
	archer_data->ups = ups;
	archer_data->coins = coins;
	archer_data->tool = archer_tool;
	archer_state = STATE_JUMPING;	
	UpdateHUD();
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow();	
	
	scrigno_coin = 0;
	scrigno_dcoin = 0;
	scrigno_shield = 0;
	scrigno_up = 0;

	//ITEMS
	if ((current_level == 0u && current_map == 0u) || (current_level == 1u && current_map == 1u) ||
		(current_level == 4u && current_map == 1u)){
		scrigno_up = spawn_item(scrigno_up, 5u, 5u, 3, 1);
		scrigno_dcoin = spawn_item(scrigno_dcoin, 11u, 11u, 7, 1);
	}else{
		scrigno_coin = spawn_item(scrigno_coin, 5u, 5u, 1, 1);
		if(archer_data->hp == MAX_HP){
			scrigno_dcoin = spawn_item(scrigno_dcoin, 11u, 11u, 7, 1);
		}else{
			scrigno_shield = spawn_item(scrigno_shield, 11u, 11u, 2, 1);	
		}		
	}
	
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

}

void Update_StateSecret() {
	
	//HUD MANAGEMENT
	if (update_hud != 0){
		update_hud = 0;
		UpdateHUD();
	}
	
	if(load_next_s){
		switch(load_next_s){
			case -1: //torno dalla secret a game
				is_on_secret = -1;
				if(current_level < 3){
					SetState(StateGame);	
				}else if (current_level < 6){
					SetState(StateGame3);
				}				
			break;
		}
	}

}
