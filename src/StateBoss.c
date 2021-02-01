#include "Banks/SetBank4.h"

#include "../res/src/window.h"
#include "../res/src/diag.h"
#include "../res/src/font.h"
#include "..\res\src\tiles.h"
#include "..\res\src\mapboss0.h"
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

void WriteBAMULET();
void WriteBCOINS();
void WriteBHP();
void WriteBUPS();
void WriteBMap();
void WriteBTOOL();

extern INT8 level_tool;
extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern STATE archer_state;
extern INT8 show_diag;

extern UINT8 amulet;
extern UINT8 coins;
extern INT8 ups ;
extern INT8 hp;
extern INT8 level_tool;
extern char * level_names[];
extern UINT8 current_level;

//Secrets
UINT8 current_level_b = 0u;
UINT8 current_map_b = 0u;
extern INT8 load_next_b;

const struct MapInfo* boss_0[] = {
	&mapboss0
};
const struct MapInfo** bosses[] = {boss_0};

INT8 boss_hp;
struct EnemyInfo* boss_data_b;

void WriteBBOSSHP();
void populate_boss0();
void ShowBWindow();

void Start_StateBoss() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);
	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteWolf);
	SpriteManagerLoad(SpriteKey);
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
	struct Sprite* boss = SpriteManagerAdd(SpriteWolf, 34*8, 12*8);
	boss_data_b = (struct EnemyInfo*)boss->custom_data;
	boss_hp = boss_data_b->hp;
	
	
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
	
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowBWindow();
	
	switch(current_level_b){
		case 0:
			switch(current_map_b){
				case 0:
						level_tool=7;
				break;
			}
		break;
	}
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

}

void ShowBWindow(){
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 32;
	InitWindow(0, 0, &window);
	SHOW_WIN;
	
	WriteBAMULET();
	WriteBCOINS();
	WriteBHP();
	WriteBUPS();
	//WriteBMap();
	WriteBBOSSHP();
	
}

void Update_StateBoss() {

	struct ArcherInfo* archer_data = (struct ArcherInfo*)scroll_target->custom_data;

	if (amulet != archer_data->amulet){
		amulet = archer_data->amulet;
		WriteBAMULET();		
	}
	if (coins != archer_data->coins){
		coins = archer_data->coins;
		WriteBCOINS();
	}
	if (hp != archer_data->hp){
		hp = archer_data->hp;
		WriteBHP();
	}
	if (ups != archer_data->ups){
		ups = archer_data->ups;
		WriteBUPS();
	}

	if (boss_hp != boss_data_b->hp){
		boss_hp = boss_data_b->hp;
		WriteBBOSSHP();		
	}
	
	if(level_tool == archer_data->tool){
		WriteBTOOL();
	}
	
	
	
	if(load_next_b){
		switch(load_next_b){
			case 2: //esco dal boss col tool
				SetState(StateGame);
			break;
		}
	}
	
}


void WriteBAMULET(){
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

void WriteBMap(){
	PRINT_POS(1, 3);
	Printf(level_names[current_level]);	
}

void WriteBCOINS(){
	PRINT_POS(17, 1);
	if (coins > 9u){
		Printf("%d", coins);
	}else{
		Printf("0%d", coins);
	}
}

void WriteBHP(){	
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

void WriteBTOOL(){
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

void WriteBUPS(){
	PRINT_POS(2, 1); //up
	if (ups > 9){Printf("%d", ups);}
	else{Printf("0%d", ups);}
}


void WriteBBOSSHP(){	
	PRINT_POS(12, 3);
	Printf("WOLF>%d", boss_hp);
}