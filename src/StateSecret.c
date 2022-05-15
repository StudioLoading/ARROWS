#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"

#include "custom_datas.h"
#include "Dialogs.h"
#include "sgb_palette.h"

IMPORT_TILES(font);
IMPORT_TILES(tiles);


IMPORT_MAP(mapsecret0);
IMPORT_MAP(window);

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
extern Sprite* scrigno_coin;
extern Sprite* scrigno_dcoin;
extern Sprite* scrigno_shield;
extern Sprite* scrigno_up;
extern INT8 update_hud;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

extern void ShowWindow() BANKED;
extern void UpdateHUD() BANKED;
extern Sprite* spawn_item(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno) BANKED;

const UINT8 const collision_tiles_secret[] = { 19, 20, 21, 0};//numero delle tile con zero finale

void START() {

	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	if(sgb_check()){
		set_sgb_palette01_secret();
		//set_sgb_palette_statusbar();
	}
	SHOW_SPRITES;
	//SCROLL
	scroll_bottom_movement_limit = 60u;//customizzo altezza archer sul display
	UINT8 map_w = 0;
	UINT8 map_h = 0;
	GetMapSize(BANK(mapsecret0), &mapsecret0, &map_w, &map_h);
	ScrollFindTile(BANK(mapsecret0), &mapsecret0, 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll(BANK(mapsecret0), &mapsecret0, collision_tiles_secret, 0);
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
	INIT_CONSOLE(font, 0, 4);
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
	
}

void UPDATE() {
	
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
