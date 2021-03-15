#include "Banks/SetBank8.h"

#include "../res/src/window4.h"
#include "../res/src/diagnew4.h"
#include "../res/src/font.h"
#include "../res/src/tiles4.h"
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
extern INT8 is_on_boss;
extern INT8 archer_tool;

extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern INT8 show_diag;
extern INT8 showing_diag;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern struct Sprite* scrigno_coin;
extern struct Sprite* scrigno_dcoin;
extern struct Sprite* scrigno_shield;
extern struct Sprite* scrigno_up;
extern struct Sprite* platform_sprite;
extern struct Sprite* snake1;
extern struct Sprite* snake2;
extern struct Sprite* snake3;
extern struct Sprite* snake4;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];

void UpdateHUD4();
void ShowWindow4();
void ShowWindowDiag4();
struct Sprite* spawn_enemy4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy);
struct Sprite* spawn_item4(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

//Maps
const struct MapInfo* map_4[] = {
	&map4
};
//Levels
const struct MapInfo** maps4[] = {map_4};

const UINT8 collision_tiles4[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 81, 100, 101, 104, 111, 119, 0};//numero delle tile con zero finale

UINT8 * thunder_delay = 24u;

struct Sprite* spawn_enemy4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy){
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	return enem;
}

struct Sprite* spawn_item4(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
	SpriteManagerRemoveSprite(itemin);
	itemin = SpriteManagerAdd(SpriteItem, (UINT16) posx << 3, (UINT16) posy << 3);
	struct ItemInfo* datascrigno = (struct ItemInfo*)itemin->custom_data;
	datascrigno->setup = 1u;
	if(scrigno){
		datascrigno->content_type = content_type;
		datascrigno->type = 10;
	}else{
		datascrigno->type = content_type;
	}
	return itemin;
}

void ShowWindow4(){
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, &window4);
	SHOW_WIN;
	
	UpdateHUD4();
}

void ShowWindowDiag4(){
	if (showing_diag == 0){	
		HIDE_WIN;
		//WINDOW
		WX_REG = 7;
		WY_REG = 144 - 48; //40
		InitWindow(0, 0, &diagnew4);
		SHOW_WIN;
	}
	PRINT_POS(1,1);
	Printf(d1);
	PRINT_POS(1,2);
	Printf(d2);
	PRINT_POS(1,3);
	Printf(d3);
	PRINT_POS(1,4);
	Printf(d4);
	
	if (showing_diag == 0){
		showing_diag = 1;
	}
}

void Start_StateGame4() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	switch (current_level){
		case 3u:
			SpriteManagerLoad(SpriteThunder);
		case 4u:
		break;
		case 5u:
		break;		
	}
	SHOW_SPRITES;
	
	//SCROLL
	scroll_bottom_movement_limit = 62;//customizzo altezza archer sul display
	const struct MapInfo** level_maps4 = maps4[0]; //current_level-3
	UINT8 map_w, map_h;
	GetMapSize(level_maps4[current_map], &map_w, &map_h);
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
		ScrollFindTile(level_maps4[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else{ //vengo da altra map
		ScrollFindTile(level_maps4[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(level_maps4[current_map], collision_tiles4, 0);
	SHOW_BKG;
	
	
	//INIT ARCHER
	is_on_boss = -1;
	if (archer_data->ups > 0 & archer_data->ups != ups){
		 ups = archer_data->ups;
	}
	if (archer_data->tool & archer_data->tool != archer_tool){
		archer_tool = archer_data->tool;
	}
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 0u;
		archer_tool = 0;
		hp = 50;
	}
	archer_data->ups =ups;
	archer_data->hp = hp;
	archer_data->coins = coins;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow4();
	
	memcpy(d1, "DIALOG1", 18);
	memcpy(d2, "DIALOG2", 18);
	memcpy(d3, "DIALOG3", 18);
	memcpy(d4, "DIALOG4", 18);
	
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
	}
	if(archer_tool == level_tool){
		UpdateHUD4();
	}

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
			//case 2: // provengo dal boss, vado al next level
			//break;
		}
	}
	
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow4();
		return;
	}
	
	// SPAWNING
	switch(current_level){
		case 3u:
			switch(current_map){
				case 0u:
					if (scroll_target->x == (UINT16) 5u << 3 & scrigno_up == 0){
						scrigno_up = spawn_item4(scrigno_up, 5u, 4u, 3, 1);
					}
					if (scroll_target->x == (UINT16) 16u << 3 & scrigno_dcoin == 0){
						scrigno_dcoin = spawn_item4(scrigno_dcoin, 23u, 4u, 3, 1);
					}
					if (scroll_target->x > (UINT16) 20u << 3 & scroll_target->x < (UINT16) 65u << 3){
						if (scroll_target->x == (UINT16) 20u << 3 | scroll_target->x == (UINT16) 23u << 3 | scroll_target->x == (UINT16) 29u << 3 | 
						scroll_target->x == (UINT16) 31u << 3 | scroll_target->x == (UINT16) 34u << 3 | scroll_target->x == (UINT16) 40u << 3 | 
						scroll_target->x == (UINT16) 45u << 3 | scroll_target->x == (UINT16) 50u << 3 | 
						scroll_target->x == (UINT16) 53u << 3 | scroll_target->x == (UINT16) 56u << 3 | 
						scroll_target->x == (UINT16) 62u << 3){
							snake1 = spawn_enemy4(snake1, SpriteThunder, (scroll_target->x >> 3) + 4u, 0u);
							snake2 = spawn_enemy4(snake2, SpriteThunder, (scroll_target->x >> 3) - 4u, 0u);
							snake3 = spawn_enemy4(snake3, SpriteThunder, (scroll_target->x >> 3) - 4u, 0u);
						}
						*thunder_delay--;
						if (*thunder_delay == 0u){						
							snake4 = spawn_enemy4(snake4, SpriteThunder, (scroll_target->x >> 3), 0u);
							*thunder_delay = 24u;
						}
					}
				break;
			}
		break;			
	}
	
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag4();
			return;
		}
	}
	else{	
		if (amulet != archer_data->amulet){
			amulet = archer_data->amulet;
			UpdateHUD4();
		}
		if (coins != archer_data->coins){
			coins = archer_data->coins;
			UpdateHUD4();
		}
		if (hp != archer_data->hp){
			hp = archer_data->hp;
			UpdateHUD4();
		}
		if (ups != archer_data->ups){
			ups = archer_data->ups;
			UpdateHUD4();
		}	
		if(archer_data->tool == level_tool){
			UpdateHUD4();
		}
	}
	
}

void UpdateHUD4(){
	//write amulet
	PRINT_POS(18,0);
	switch (archer_data->amulet){
		case 1: Printf("$"); break;
		case 2: Printf("]"); break;
		case 3: Printf("["); break;
		case 4: Printf("#"); break;
		case 5: Printf("@"); break;
		default: Printf("$"); break;
	}
	//write coins
	if (archer_data->coins == 100u){
		archer_data->coins = 0u;
		coins = 0u;
		archer_data->ups += 1;	
	}
	PRINT_POS(12, 0);
	if (archer_data->coins > 9){
		Printf("%d", archer_data->coins);
	}else{
		Printf("0%d", archer_data->coins);
	}
	//write hp
	PRINT_POS(7, 0);
	if (archer_data->hp < 10){
		Printf("00%d", archer_data->hp);
	}
	if (archer_data->hp > 9 & archer_data->hp < 100){
		Printf("0%d", archer_data->hp);
	}
	if (archer_data->hp >= 100){
		Printf("%d", archer_data->hp);	
	}
	//write tool
	if (archer_data->tool == level_tool){
		switch(level_tool){
			case 6:
				PRINT_POS(16, 0);
				Printf("{");
			break;
			case 7:
				PRINT_POS(16, 0);
				Printf("<");
			break;
		}
	}
	//write ups
	PRINT_POS(2, 0); //up
	if (archer_data->ups > 9){Printf("%d", archer_data->ups);}
	else{Printf("0%d", archer_data->ups);}
}
