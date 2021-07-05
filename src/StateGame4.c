#include "Banks/SetBank8.h"

#include <stdbool.h>

#include "../res/src/window4.h"
#include "../res/src/diagnew4.h"
#include "../res/src/font.h"
#include "../res/src/tiles4.h"
#include "../res/src/map41.h"
#include "../res/src/map4.h"
#include "../res/src/map50.h"
#include "../res/src/map51.h"
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
#include "TileAnimations.h"


const UINT8 const collision_tiles4[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 68, 69, 70, 71, 73, 74, 75, 81, 90, 102, 103, 104, 111, 119, 0};//numero delle tile con zero finale


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
extern struct Sprite* platform_sprite;
extern struct Sprite* enemies_0;
extern struct Sprite* enemies_1;
extern struct Sprite* enemies_2;
extern struct Sprite* enemies_3;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];

extern UINT8 updatecounter;
extern INT8 platform_vx;
extern bool LCD_Installed;

struct Sprite* scrigno0 = 0;
struct Sprite* scrigno1 = 0;
struct ItemInfo* datascrigno0 = 0;
struct ItemInfo* datascrigno1 = 0;
//struct Sprite* enemies4[4] = {0,0,0,0};
/*struct Sprite* enemies4_0 = 0;
struct Sprite* enemies4_1 = 0;
struct Sprite* enemies4_2 = 0;
struct Sprite* enemies4_3 = 0;*/
//INT8 enlen4 = 0; //counts in-screen enemies
//INT8 itlen4 = 0;

void UpdateHUD4();
void ShowWindow4();
void ShowWindowDiag4();
void set_window_y4(UBYTE y);
void LCD_isr4();
void ENpop4();
void spawn_enemy4(UINT8 spriteType, UINT16 posx, UINT16 posy);
void spawn_item4(UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

//Maps
const struct MapInfo* const map_4[] = {
	&map41,
	&map4
};
const struct MapInfo* const map_5[] = {
	&map50, &map51
};
//Levels
const struct MapInfo** const maps4[] = {map_4, map_5};

const UINT16 bg_palette4[] = {PALETTE_FROM_HEADER(tiles4)};

UINT8 thunder_delay = 16u;


void spawn_enemy4(UINT8 spriteType, UINT16 posx, UINT16 posy){
	if(spriteType == SpritePlatform){
		platform_sprite = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
		return;
	}	
	SpriteManagerRemoveSprite(enemies_3);
	enemies_3 = enemies_2;
	enemies_2 = enemies_1;
	//enemies4_1 = enemies4_0;
	enemies_0 = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);;
	/*PRINT_POS(16, 0);
	Printf("%d", enlen4);*/
}

struct Sprite* spawn_vplatform4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy){
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)enem->custom_data;
	data_platform->type = 1;
	return enem;
}

void spawn_item4(UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
	scrigno1=SpriteManagerAdd(SpriteItem, (UINT16) posx << 3, (UINT16) posy << 3);
	datascrigno1 = (struct ItemInfo*)scrigno1->custom_data;
	datascrigno1->setup = 1u;
	if(scrigno){
		//se la vita del player è 100% e vorrei spawnare scudo, spawno dcoin !
		if(content_type == 2 && archer_data->hp == 100){
			content_type = 7;
		}
		datascrigno1->content_type = content_type;
		datascrigno1->type = 10;
	}else{
		datascrigno1->type = content_type;
	}
}

void ShowWindow4(){
	set_window_y4(144 - 8);
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
	
	is_on_boss = -1;
	thunder_delay = 16u;
	
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
		break;
		case 4u:
			SpriteManagerLoad(SpritePlatform);
			if(current_map == 0){
				SpriteManagerLoad(SpriteRat);
				SpriteManagerLoad(SpriteSpider);
			}else if (current_map == 1){
				SpriteManagerLoad(SpriteRat);
				SpriteManagerLoad(SpriteSpider);
				SpriteManagerLoad(SpriteBird);
			}
		break;
		case 5u:
		break;		
	}		
	SHOW_SPRITES;
	
	//SCROLL
	scroll_bottom_movement_limit = 62;//customizzo altezza archer sul display
	const struct MapInfo** const level_maps4 = maps4[current_level-3u]; //current_level-3

	UINT8 map_w, map_h;
	GetMapSize(level_maps4[current_map], &map_w, &map_h);	
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
		ScrollFindTile(level_maps4[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else if(archer_state != STATE_DIAG){ //non vengo da dialogo
		ScrollFindTile(level_maps4[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else{
		load_next_s = 1; // START UGLY STORY : tracking the fact that the previous state is a Dialog, so I don't want initial spawnings !
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll(level_maps4[current_map], collision_tiles4, 0);
	SHOW_BKG;
	
	
	//INIT ARCHER
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
	archer_data->ups = ups;
	if(archer_data->hp != 100){
		archer_data->hp = hp;	
	}else{
		hp = 100;
	}
	archer_data->hp = hp;
	archer_data->coins = coins;
	
	//INIT ENEMY
	switch(current_level){
		case 3:
			switch(current_map){
				case 1u:
					spawn_item4(10u, 9u, 3, 1);
				break;
			}
		break;
	}

	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow4();
	
	memcpy(d1, "DIALOG1", 18);
	memcpy(d2, "DIALOG2", 18);
	memcpy(d3, "DIALOG3", 18);
	memcpy(d4, "DIALOG4", 18);

	if(load_next_s) load_next_s = 0; //END UGLY STORY: for track a previous state for which I don't want the initial spawning

	if(archer_tool == level_tool){
		UpdateHUD4();
	}

	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
	if (!LCD_Installed) { 
		CRITICAL {
			add_LCD(LCD_isr4);
			set_interrupts(VBL_IFLAG | LCD_IFLAG);
			STAT_REG |= 0x40; 
			set_window_y4(144-8);
		}
	    LCD_Installed = TRUE; 
	}

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
	
	if(load_next_b == 1){
		if(archer_state != STATE_DIAG){
			load_next_b = 0;
			SetState(StateBoss);//StateBoss
		}
	}
	
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow4();
		return;
	}
	
	// SPAWNING
	if(!SPRITE_GET_VMIRROR(scroll_target) && archer_state != STATE_HIT && platform_vx == 0u){
		switch(current_level){
			case 3u: // liv. 4 Sky -> Ibex
				switch(current_map){
					case 0u:
						if (scroll_target->x > (UINT16) 93u << 3){
							if (scroll_target->x == (UINT16) 120u << 3){
								spawn_item4(133u, 9u, 2, 1);
							}
							switch(thunder_delay){
								case 60u:
									spawn_enemy4(SpriteHurricane, (scroll_target->x >> 3) + 5u, 5u);
								break;
								case 120u:
									spawn_enemy4(SpriteHurricane, (scroll_target->x >> 3) + 4u, 6u);
								break;
								case 180u:
									spawn_enemy4(SpriteHurricane, (scroll_target->x >> 3) + 4u, 6u);
								break;
								case 0u:
									spawn_enemy4(SpriteHurricane, (scroll_target->x >> 3), 7u);
									thunder_delay = 180u;
								break;
							}
							thunder_delay -= 1u;
							//PRINT_POS(16,0);
							//Printf("%d", thunder_delay);
						}
					break;
					case 1u:
						switch(thunder_delay){
							case 40u:
								spawn_enemy4(SpriteThunder, (scroll_target->x >> 3) + 2u, 4u);
							break;
							case 80u:
								spawn_enemy4(SpriteThunder, (scroll_target->x >> 3) - 2u, 4u);
							break;
							case 120u:
								spawn_enemy4(SpriteThunder, (scroll_target->x >> 3) + 1u, 4u);
							break;
							case 0u:
								spawn_enemy4(SpriteThunder, (scroll_target->x >> 3) + 5u, 4u);
								thunder_delay = 160u;
							break;
							default:
								if (scroll_target->x == (UINT16) 30u << 3){
									spawn_item4(39u, 4u, 2, 1);
								}
								if(scroll_target->x == (UINT16) 140u << 3){
									spawn_item4(156u, 5u, 3, 1);							
								}					
								if(scroll_target->x == (UINT16) 175u << 3){
									spawn_item4(185u, 4u, 2, 1);
								}
							break;
						}
						thunder_delay -= 1u;					
					break;
				}
			break;
			case 4u: // liv. 5 Trees -> Bear
				switch(current_map){
					case 0u:
						if(scroll_target->x == (UINT16) 25u << 3 && scroll_target->y < (UINT16) 14u << 3){
							spawn_item4(31u, 17u, 2, 1);
							//snake3 = spawn_vplatform4(snake3, SpritePlatform, 5u, 19u);
						}
						if((scroll_target->x == (UINT16) 25u << 3 || scroll_target->x == (UINT16) 26u << 3) && 
							scroll_target->y == (UINT16) 38u << 3 ){
							enemies_0 = spawn_vplatform4(enemies_2, SpritePlatform, 37u, 43u);
							enemies_1 = spawn_vplatform4(enemies_3, SpritePlatform, 42u, 51u);
						}
						if(scroll_target->x == (UINT16) 30u << 3 && scroll_target->y == (UINT16) 60u << 3 ){
							spawn_enemy4(SpriteRat, (scroll_target->x >> 3) -8u, (scroll_target->y >> 3) - 4u);
							spawn_enemy4(SpriteSpider, 20u, 58u);
						}
						if(scroll_target->x == (UINT16) 23u << 3 && scroll_target->y == (UINT16) 60u << 3 ){
							spawn_enemy4(SpriteRat, (scroll_target->x >> 3) + 6u, (scroll_target->y >> 3) -4u);
							spawn_enemy4(SpriteRat, (scroll_target->x >> 3) - 8u, (scroll_target->y >> 3) -4u);
						}
						if(scroll_target->x == (UINT16) 11u << 3 && scroll_target->y == (UINT16) 64u << 3 ){
							spawn_enemy4(SpriteSpider, 24u, 63u);
							spawn_enemy4(SpriteSpider, 20u, 64u);
						}
						if(scroll_target->x == (UINT16) 25u << 3 && scroll_target->y == (UINT16) 64u << 3 ){
							spawn_enemy4(SpriteRat, 20u, 63u);
						}
						
						if(scroll_target->x == (UINT16) 34u << 3 && scroll_target->y == (UINT16) 64u << 3 ){
							spawn_enemy4(SpriteRat, 30u, 63u);
						}
					break;
					case 1u:
						if(scroll_target->x == (UINT16) 31u << 3 && scroll_target->y < (UINT16) 7u << 3){
							spawn_item4(34u, 2u, 3, 1);
						}
						if(scroll_target->x == (UINT16) 23u << 3 && 
							scroll_target->y < (UINT16) 28u << 3 && scroll_target->y > (UINT16) 25u << 3){
							spawn_enemy4(SpriteRat, 17u, 28u);
						}
						if(scroll_target->x == (UINT16) 30u << 3 && 
							scroll_target->y < (UINT16) 28u << 3 && scroll_target->y > (UINT16) 25u << 3){
							spawn_enemy4(SpriteRat, 30u, 28u);
							spawn_enemy4(SpriteSpider, 23u, 27u);
						}
						if(scroll_target->x == (UINT16) 34u << 3 && 
							scroll_target->y < (UINT16) 39u << 3 && scroll_target->y > (UINT16) 36u << 3){
							spawn_item4(43u, 41u, 2, 1);
						}
					break;
				}
			break;
		}
	}
	
	//MOVING BACKGROUND TILES
	if (current_level == 3u){
		updatecounter++;
		if (updatecounter < 120) {
			switch(updatecounter){
				case 1:
				case 16:
				case 48:
					AnimClouds0();
				break;
				case 4:
				case 24:
				case 42:
					AnimClouds1();
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
		if (hp != archer_data->hp && archer_data->hp >= 0){
			if(archer_data->hp < hp){
				hp--;
			}else{
				hp++;
			}
			//hp = archer_data->hp;
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
		case 3: Printf("#"); break;
		case 4: Printf("]"); break;
		case 5: Printf("@"); break;
		default: Printf("$"); break;
	}
	//write coins
	if (is_on_boss < 0){
		if (archer_data->coins == 100u){
			archer_data->coins = 0u;
			coins = 0u;
			archer_data->ups += 1;	
		}
		PRINT_POS(12, 0);
		if (archer_data->coins > 9u){
			Printf("%d", archer_data->coins);
		}else{
			Printf("0%d", archer_data->coins);
		}
	}
	//write hp
	PRINT_POS(7, 0);
	if (hp < 10){ // archer_data->hp < 10 &&
		Printf("00");
		PRINT_POS(9, 0);
		Printf("%d", hp);
	}else if (hp >= 100){ // archer_data->hp >= 100 &&
		Printf("%d", hp);	
	}else if (hp > 9){ // archer_data->hp > 9 && archer_data->hp < 100 && 
		Printf("0%d", hp);
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

void LCD_isr4() NONBANKED {
    if (LYC_REG == 0) {
        if (WY_REG == 0) HIDE_SPRITES; else SHOW_SPRITES; 
        LYC_REG = WY_REG;
    } else {
        HIDE_SPRITES; 
        LYC_REG = 0;
    }
}

void set_window_y4(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}
