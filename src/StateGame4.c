#include "Banks/SetBank8.h"

#include "../res/src/window4.h"
#include "../res/src/diagnew4.h"
#include "../res/src/font.h"
#include "../res/src/tiles4.h"
#include "../res/src/map41.h"
#include "../res/src/map4.h"
#include "../res/src/map50.h"
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


const UINT8 collision_tiles4[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 68, 69, 70, 71, 73, 74, 75, 81, 90, 100, 101, 104, 111, 119, 0};//numero delle tile con zero finale


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
extern UINT8 updatecounter;


void UpdateHUD4();
void ShowWindow4();
void ShowWindowDiag4();
struct Sprite* spawn_enemy4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy);
struct Sprite* spawn_item4(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

//Maps
const struct MapInfo* map_4[] = {
	&map41,
	&map4
};
const struct MapInfo* map_5[] = {
	&map50//, &map51
};
//Levels
const struct MapInfo** maps4[] = {map_4, map_5};


const UINT16 bg_palette4[] = {PALETTE_FROM_HEADER(tiles4)};

UINT8 thunder_delay = 16u;

struct Sprite* spawn_enemy4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy){
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	return enem;
}

struct Sprite* spawn_vplatform4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy){
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)enem->custom_data;
	data_platform->type = 1;
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
	SetPalette(BG_PALETTE, 0, 8, bg_palette4, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	switch (current_level){
		case 3u:
			SpriteManagerLoad(SpriteThunder);
			SpriteManagerLoad(SpriteHurricane);
			if(current_map == 0){
				snake1 = spawn_enemy4(snake1, SpriteHurricane, 1u, 0u);	
				snake2 = spawn_enemy4(snake2, SpriteHurricane, 2u, 0u);	
				snake3 = spawn_enemy4(snake3, SpriteHurricane, 3u, 0u);	
				snake4 = spawn_enemy4(snake4, SpriteHurricane, 10u, 0u);		
			}
			if(current_map == 1){
				snake1 = spawn_enemy4(snake1, SpriteThunder, 1u, 0u);	
				snake2 = spawn_enemy4(snake2, SpriteThunder, 2u, 0u);	
				snake3 = spawn_enemy4(snake3, SpriteThunder, 3u, 0u);	
				snake4 = spawn_enemy4(snake4, SpriteThunder, 10u, 0u);						
			}
		case 4u:
			SpriteManagerLoad(SpritePlatform);
			SpriteManagerLoad(SpriteRat);
			SpriteManagerLoad(SpriteSpider);
			if(current_map == 0){
				snake1 = spawn_enemy4(snake1, SpriteRat, 3u, 5u);	
				snake2 = spawn_enemy4(snake2, SpriteRat, 6u, 5u);	
				snake3 = spawn_enemy4(snake3, SpriteSpider, 7u, 5u);	
				snake4 = spawn_enemy4(snake4, SpriteRat, 14u,5u);		
			}
		break;
		case 5u:
		break;		
	}		
	SHOW_SPRITES;
	
	//SCROLL
	scroll_bottom_movement_limit = 62;//customizzo altezza archer sul display
	const struct MapInfo** level_maps4 = maps4[current_level-3u]; //current_level-3
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
	if (scroll_target->x > (UINT16) 18u << 3){
		struct EnemyInfo* datasnake1 = (struct EnemyInfo*)snake1->custom_data;
		struct EnemyInfo* datasnake2 = (struct EnemyInfo*)snake2->custom_data;
		struct EnemyInfo* datasnake3 = (struct EnemyInfo*)snake3->custom_data;
		struct EnemyInfo* datasnake4 = (struct EnemyInfo*)snake4->custom_data;
		switch(current_level){
			case 3u:
				switch(current_map){
					case 0u:
						if (scroll_target->x > (UINT16) 93u << 3){							
							if (scroll_target->x == (UINT16) 120u << 3){
								scrigno_shield = spawn_item4(scrigno_shield, 133u, 9u, 2, 1);
							}
							if (scroll_target->x >> 2 & 1){
								if (datasnake1->enemy_state == ENEMY_STATE_DEAD){
									snake1 = spawn_enemy4(snake1, SpriteHurricane, (scroll_target->x >> 3) + 4u, 3u);	
								}
								if (datasnake2->enemy_state == ENEMY_STATE_DEAD){
									snake2 = spawn_enemy4(snake2, SpriteHurricane, (scroll_target->x >> 3) + 5u, 4u);
								}
								if (datasnake3->enemy_state == ENEMY_STATE_DEAD){
									snake3 = spawn_enemy4(snake3, SpriteHurricane, (scroll_target->x >> 3) + 3u, 5u);
								}
							}
							thunder_delay--;
							if (thunder_delay == 0u){		
								if (datasnake4->enemy_state == ENEMY_STATE_DEAD){				
									snake4 = spawn_enemy4(snake4, SpriteThunder, (scroll_target->x >> 3), 0u);
									thunder_delay = 20u;
								}
							}
							
						}
					break;
					case 1u:
						if (scroll_target->x == (UINT16) 5u << 3 & scrigno_up == 0){
							scrigno_up = spawn_item4(scrigno_up, 5u, 4u, 3, 1);
						}
						if (scroll_target->x == (UINT16) 33u << 3 & scrigno_shield == 0){
							scrigno_shield = spawn_item4(scrigno_shield, 39u, 4u, 2, 1);
						}						
						if (scroll_target->x > (UINT16) 12u << 3){
							if (scroll_target->x >> 2 & 1){
								if (datasnake1->enemy_state == ENEMY_STATE_DEAD){
									snake1 = spawn_enemy4(snake1, SpriteThunder, (scroll_target->x >> 3) + 4u, 1u);	
								}
								if (datasnake2->enemy_state == ENEMY_STATE_DEAD){
									snake2 = spawn_enemy4(snake2, SpriteThunder, (scroll_target->x >> 3) - 4u, 2u);
								}
								if (datasnake3->enemy_state == ENEMY_STATE_DEAD){
									snake3 = spawn_enemy4(snake3, SpriteThunder, (scroll_target->x >> 3) - 1u, 0u);
								}
							}
							if (scroll_target->x > (UINT16) 140u << 3){
								thunder_delay--;
								if (thunder_delay == 0u){		
									if (datasnake4->enemy_state == ENEMY_STATE_DEAD){				
										snake4 = spawn_enemy4(snake4, SpriteThunder, (scroll_target->x >> 3), 0u);
										thunder_delay = 20u;
									}
								}
							}
						}
						if(scroll_target->x == (UINT16) 140u << 3){
							scrigno_dcoin = spawn_item4(scrigno_dcoin, 156u, 5u, 3, 1);							
						}					
						if(scroll_target->x == (UINT16) 180u << 3){
							scrigno_shield = spawn_item4(scrigno_shield, 186u, 4u, 2, 1);
						}						
					break;
				}
			break;
			case 4u:
				switch(current_map){
					case 0u:
						if(scroll_target->x == (UINT16) 25u << 3 && scroll_target->y < (UINT16) 14u << 3){
							scrigno_shield = spawn_item4(scrigno_shield, 31u, 17u, 2, 1);
							snake3 = spawn_vplatform4(snake3, SpritePlatform, 5u, 19u);
						}
						if(scroll_target->x == (UINT16) 33u << 3 && scroll_target->y == (UINT16) 36u << 3 ){
							snake2 = spawn_vplatform4(snake2, SpritePlatform, 37u, 43u);
							snake1 = spawn_vplatform4(snake1, SpritePlatform, 42u, 51u);
						}
						if(scroll_target->x == (UINT16) 30u << 3 && scroll_target->y == (UINT16) 60u << 3 ){
							snake3 = spawn_enemy4(snake3, SpriteRat, (scroll_target->x >> 3) -8u, (scroll_target->y >> 3) - 4u);
							snake4 = spawn_enemy4(snake4, SpriteSpider, (UINT16) 20u, (UINT16) 58u);
						}
						if(scroll_target->x == (UINT16) 23u << 3 && scroll_target->y == (UINT16) 60u << 3 ){
							snake1 = spawn_enemy4(snake1, SpriteRat, (scroll_target->x >> 3) + 6u, (scroll_target->y >> 3) -4u);
							snake2 = spawn_enemy4(snake2, SpriteRat, (scroll_target->x >> 3) - 8u, (scroll_target->y >> 3) -4u);
						}
					break;
				}
			break;
		}
	}
	
	
	//MOVING BACKGROUND TILES
	UINT16 idx_flash = 0u;
	UINT16 min_flash_x = 0u;
	UINT16 max_flash_x = 32u;
	const unsigned char sx_b[1] = {93};
	const unsigned char sx_c[1] = {100};
	const unsigned char dx_b[1] = {94};
	const unsigned char dx_c[1] = {101};
	if (current_level == 3){
		updatecounter++;
		if (updatecounter < 120) {
			switch(updatecounter){
				case 1:
				case 16:
				case 48:
					for (idx_flash = min_flash_x; idx_flash < max_flash_x; idx_flash++){
						set_bkg_tiles(idx_flash	, 3u, 1, 1, sx_b);
						set_bkg_tiles(idx_flash, 4u, 1, 1, dx_c);
						idx_flash++;
						set_bkg_tiles(idx_flash, 3u, 1, 1, dx_b);
						set_bkg_tiles(idx_flash	, 4u, 1, 1, sx_c);
					}
				break;
				case 4:
				case 24:
				case 42:
					for (idx_flash = min_flash_x; idx_flash < max_flash_x; idx_flash++){
						set_bkg_tiles(idx_flash	, 3u, 1, 1, sx_c);
						set_bkg_tiles(idx_flash, 4u, 1, 1, dx_b);
						idx_flash++;
						set_bkg_tiles(idx_flash, 3u, 1, 1, dx_c);
						set_bkg_tiles(idx_flash	, 4u, 1, 1, sx_b);
					}
				break;
			}
		}else{
			updatecounter = 0;
		}
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
	PRINT_POS(19,0);
	switch (archer_data->amulet){
		case 1: Printf("$"); break;
		case 2: Printf("["); break;
		case 3: Printf("]"); break;
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
