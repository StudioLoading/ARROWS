#include "Banks/SetBank7.h"

#include "../res/src/window.h"
#include "../res/src/diagnew.h"
#include "../res/src/font.h"
#include "..\res\src\tiles.h"
#include "..\res\src\mapboss0.h"
#include "..\res\src\mapboss1.h"
#include "../res/src/archer.h"
#include "../res/src/arrow.h"
#include "../res/src/wolf.h"
#include "../res/src/key.h"
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
extern INT8 load_next_b;
extern INT8 level_tool;
extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern INT8 show_diag;
extern INT8 showing_diag;
extern INT8 max_diag;
extern INT8 is_on_boss;

extern void ShowWindow();
extern void ShowWindowDiag();
extern void WriteAMULET();
extern void WriteCOINS();
extern void WriteHP();
extern void WriteUPS();
extern void WriteTOOL();
extern void Build_Next_Dialog();




//Boss
UINT8 current_level_b = 0u;
UINT8 current_map_b = 0u;
const struct MapInfo* boss_0[] = {
	&mapboss0
};
const struct MapInfo* boss_1[] = {
	&mapboss1
};
const struct MapInfo** bosses[] = {boss_0, boss_1};

INT8 boss_hp = 0;
struct EnemyInfo* boss_data_b;
const char * const level_b_names[] = {"THE CAVE", "THE SWAMP"};

void WriteBBOSSHP();
void populate_boss0();
void WriteBMap();

void Start_StateBoss() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);
	SPRITES_8x16;
	
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteKey);
	switch(current_level_b){
		case 0:
			level_tool=7;
			SpriteManagerLoad(SpriteWolf);
		break;
		case 1:
			//SpriteManagerLoad(SpriteWolf);
		break;
	}
	
	SHOW_SPRITES;


	//SCROLL
	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	const struct MapInfo** level_maps_b = bosses[current_level_b];
	UINT8 map_w, map_h;
	GetMapSize(level_maps_b[current_map_b], &map_w, &map_h);
	ScrollFindTile(level_maps_b[current_map_b], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(level_maps_b[current_map_b], collision_tiles, 0);
	SHOW_BKG;
	
	//INIT BOSS
	struct Sprite* boss = SpriteManagerAdd(SpriteWolf, 24*8, 14*8); //34, 12
	boss_data_b = (struct EnemyInfo*)boss->custom_data;
	boss_hp = boss_data_b->hp;
	
	
	//INIT ARCHER
	//struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;
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
	
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow();
	WriteBBOSSHP();
	WriteBMap();
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

	is_on_boss = 0;
	Build_Next_Dialog();
	
}

void Update_StateBoss() {

	if(show_diag >= max_diag){
		ShowWindow();		
		WriteBBOSSHP();
		WriteBMap();
		return;
	}
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag();
			return;
		}
	}else{
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

		if (boss_hp != boss_data_b->hp){
			boss_hp = boss_data_b->hp;
			if (boss_hp <= 0){
				boss_hp = 0;
				boss_data_b->hp = 0;
			}
			WriteBBOSSHP();		
		}
		
		if(level_tool == archer_data->tool){
			WriteTOOL();
		}
	}
	
	if(load_next_b){
		switch(load_next_b){
			case 2: //esco dal boss col tool
				is_on_boss = 0;
				SetState(StateGame);
			break;
		}
	}
	
}

void WriteBMap(){
	PRINT_POS(1, 3);
	Printf(level_b_names[current_level_b]);	
}

void WriteBBOSSHP(){	
	PRINT_POS(12, 3);
	Printf("WOLF>%d", boss_hp);
}