#include "Banks/SetBank7.h"

#include <stdbool.h>

#include "../res/src/window.h"
#include "../res/src/diagnew.h"
#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/map2.h"
#include "../res/src/mapsewer.h"
#include "../res/src/mapsewer2.h"
#include "../res/src/map3.h"
#include "../res/src/map3tree.h"
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


const UINT8 const collision_tiles[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 74, 75, 76, 77, 81, 85, 86, 89, 90, 91, 92, 104, 111, 119, 0};//numero delle tile con zero finale


const UINT16 const bg_palette[] = {PALETTE_FROM_HEADER(tiles)};

const UINT16 const sprites_palette[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

UINT8 amulet = 0u;
UINT8 coins = 0u;
INT8 ups = 3;
INT8 hp = 100;
INT8 archer_tool = 0;
INT8 level_tool = -1;
INT8 load_next = 0;
INT8 load_next_s = 0;
INT8 load_next_b = 0; // 0 default, 1 se voglio testare il boss stage, in coerenza col current_level_b sullo StateBoss
UINT8 current_level = 0u; // 0u default, 1 swamp, 2 forest, 3 sky, 4 trees, 5 ice cavern
UINT8 current_map = 0u; // 0u default
UINT16 drop_player_x = 0u;
UINT16 drop_player_y = 0u;
INT8 show_diag = 0;
INT8 showing_diag = 0;
bool LCD_Installed = false;

extern UINT8 updatecounter; //da StateCredit
struct Sprite* platform_sprite = 0;
struct Sprite* enemies_0 = 0;
struct Sprite* enemies_1 = 0 ;
struct Sprite* enemies_2 = 0 ;
struct Sprite* enemies_3 = 0 ;
//struct Sprite* enemies[4] = {0,0,0,0};
//INT8 enlen = 0; //counts in-screen enemies
struct Sprite* scrigno_coin = 0;
struct Sprite* scrigno_dcoin = 0;
struct Sprite* scrigno_shield = 0;
struct Sprite* scrigno_up = 0;
unsigned char d1[18];
unsigned char d2[18];
unsigned char d3[18];
unsigned char d4[18];

const struct MapInfo* const level_1[] = {
	&map,
	&map2
};
const struct MapInfo* const level_2[] = {
	&mapsewer2,
	&mapsewer
};
const struct MapInfo* const level_3[] = {
	&map3,
	&map3tree
};
const struct MapInfo** const levels[] = {level_1, level_2, level_3};

extern struct ArcherInfo* archer_data;
extern ARCHER_STATE archer_state;
extern INT8 is_on_boss;
extern UINT8 current_level_b;
extern UINT8 current_map_b;
extern INT8 platform_vx;

void UpdateHUD();
void ShowWindow();
void ShowWindowDiag();
void set_window_y(UBYTE y);
void LCD_isr();
void spawn_enemy(UINT8 spriteType, UINT16 posx, UINT16 posy);
void spawn_item(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);



void Start_StateGame() {
	
	if (current_level > 2u){
		SetState(StateGame4);
	}
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpritePlatform);
	SpriteManagerLoad(SpriteItem);
	switch (current_level){
		case 0u:
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteScorpion);
			SpriteManagerLoad(SpritePorcupine);
		break;
		case 1u:
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteRat);
			SpriteManagerLoad(SpriteSpider);
		break;
		case 2u:
			SpriteManagerLoad(SpriteSpider);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteBird);
		break;		
	}
	SHOW_SPRITES;

	//SCROLL
	if (current_level == 2u & current_map == 0u){
		scroll_bottom_movement_limit = 82;//customizzo altezza archer sul display
	}else{
		scroll_bottom_movement_limit = 62;//customizzo altezza archer sul display
	}

	const struct MapInfo** lvls = levels[current_level];
	UINT8 map_w;
	UINT8 map_h;
	GetMapSize(lvls[current_map], &map_w, &map_h);
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
		ScrollFindTile(lvls[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else if(archer_state != STATE_DIAG){ //non vengo da dialogo
			ScrollFindTile(lvls[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else{
		load_next_s = 1; // START UGLY STORY : tracking the fact that the previous state is a Dialog, so I don't want initial spawnings !
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll(lvls[current_map], collision_tiles, 0);
	SHOW_BKG;
	
	//INIT ARCHER
	is_on_boss = -1;
	if (archer_data->ups & archer_data->ups != ups){
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
	
	archer_data->coins = coins;
	archer_data->tool = archer_tool;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow();
	
	memcpy(d1, "DIALOG1", 18);
	memcpy(d2, "DIALOG2", 18);
	memcpy(d3, "DIALOG3", 18);
	memcpy(d4, "DIALOG4", 18);
	
	//INIT SPAWNING
	switch(current_level){
		case 0u:
			switch(current_map){
				case 0u:
					level_tool = 6;
					//wrench
					if(archer_data->tool == 0){
						if (!load_next_s){ 
							spawn_item(scrigno_coin, 9u, 12u, 1, 1);
							spawn_item(scrigno_shield, 9u, 22u, 2, 1);
							spawn_item(scrigno_dcoin, 6u, 4u, 7, 1);
							spawn_item(scrigno_up, 31u, 27u, 3, 0);
						}
					}
				break;
				case 1u:
					spawn_enemy(SpriteEnemy, 7u, 12u);
					spawn_enemy(SpritePlatform, 9u, 21u);
				break;
			}
		break;
		case 1u:
			switch(current_map){
				case 0u:
					if (!load_next_s){ // se non vengo da secret. se no si arricchisce a caso senza freni
						spawn_enemy(SpriteSpider, 12u, 5u);
						spawn_enemy(SpriteSpider, 14u, 6u);
					}
				break;
				case 1u:
					level_tool = 6;
					if (!load_next_s){ // se non vengo da secret. se no si arricchisce a caso senza freni
						spawn_item(scrigno_shield, 41u, 3u, 2, 1);
						spawn_enemy(SpriteRat, 16u, 4u);
						spawn_enemy(SpriteEnemy, 17u, 4u);
					}
				break;
			}
		break;
		case 2u:
			switch(current_map){
				case 0u:
					if (!load_next_s){ // se non vengo da secret. se no si arricchisce a caso senza freni
						spawn_item(scrigno_dcoin, 3u, 1u, 7, 1);
						spawn_enemy(SpriteSpider, 13u, 9u);
						spawn_enemy(SpriteSpider, 19u, 9u);
					}
				break;
				case 1u:
					if (!load_next_s){ // se non vengo da secret. se no si arricchisce a caso senza freni
						spawn_enemy(SpriteSpider, 16u, 9u);
						spawn_enemy(SpriteSpider, 17u, 9u);
					}
				break;
			}
		break;
	}
	
	if(load_next_s) load_next_s = 0; //END UGLY STORY: for track a previous state for which I don't want the initial spawning
	
	if(archer_tool == level_tool){
		UpdateHUD();
	}

	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
	if (!LCD_Installed) { 
		CRITICAL {
			add_LCD(LCD_isr);
			set_interrupts(VBL_IFLAG | LCD_IFLAG);
			STAT_REG |= 0x40; 
			set_window_y(144-8);
		}
	    LCD_Installed = true; 
	}

	
}

void ShowWindow(){
	set_window_y(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, &window);
	SHOW_WIN;
	
	UpdateHUD();
	
}

void ShowWindowDiag(){
/*	if (showing_diag == 0){	
		HIDE_WIN;
		//WINDOW
		WX_REG = 7;
		WY_REG = 144 - 48; //40
		InitWindow(0, 0, &diagnew);
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
	*/
}

void spawn_enemy(UINT8 spriteType, UINT16 posx, UINT16 posy){
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

void spawn_item(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
	SpriteManagerRemoveSprite(itemin);
	struct Sprite* itemnew = SpriteManagerAdd(SpriteItem, (UINT16) posx << 3, (UINT16) posy << 3);
	struct ItemInfo* datascrigno = (struct ItemInfo*)itemnew->custom_data;
	datascrigno->setup = 1u;
	if(scrigno){
		//se la vita del player è 100% e vorrei spawnare scudo, spawno dcoin !
		if(content_type == 2 && archer_data->hp == 100){
			content_type = 7;
		}
		datascrigno->content_type = content_type;
		datascrigno->type = 10;
	}else{
		datascrigno->type = content_type;
	}
}

void Update_StateGame() {

	if(load_next) {
		switch(load_next){
			case 1: //stage
			case -1:
				current_map += load_next;
			break;
		}
		load_next = 0;
		switch(current_level){
			case 0:
			case 1:
			case 2:
			case 3:
				SetState(StateGame);	
			break;
			case 4:
			case 5:
			case 6:
			case 7:
				SetState(StateGame4);
			break;
		} 
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
	
	
	//SPAWNING	
	if(!SPRITE_GET_VMIRROR(scroll_target) && archer_state != STATE_HIT && platform_vx == 0u){
		switch(current_level){
			case 0:
				switch(current_map){
					case 0:
						if (scroll_target->x == (UINT16) 9u << 3 & scroll_target->y > (UINT16) 36u  << 3){
							spawn_enemy(SpriteEnemy, 18u, 39u);
							spawn_enemy(SpriteEnemy, 22u, 39u);
						}
					break;
					case 1:
						if (scroll_target->x == (UINT16) 12u << 3 && scroll_target->y > (UINT16) 37u << 3){
							spawn_enemy(SpriteEnemy, 21u, 39u);
							spawn_enemy(SpriteEnemy, 23u, 39u);
						}
						if (scroll_target->x == (UINT16) 25u << 3 && scroll_target->y == (UINT16) 39u  << 3){
							spawn_enemy(SpriteScorpion, 38u, 39u);
						}
						if (scroll_target->x == (UINT16) 37u << 3 && scroll_target->y <= (UINT16) 19u << 3 && scroll_target->y > (UINT16) 15u << 3){
							spawn_enemy(SpriteEnemy, 27u, 8u);
							spawn_enemy(SpritePorcupine, 48u, 9u);							
							spawn_enemy(SpriteScorpion, 17u, 3u);
						}
					break;
				}
			break;
			case 1:
				switch(current_map){
					case 0:
						if (scroll_target->x == (UINT16) 15u << 3){
							spawn_enemy(SpriteSpider, 21u, 4u);
							spawn_item(scrigno_up, 26u, 5u, 3, 1);
							spawn_enemy(SpritePlatform, 35u, 6u);
						}
						if (scroll_target->x == (UINT16) 48u << 3){
							spawn_enemy(SpriteRat, 58u, 6u);
							spawn_enemy(SpriteEnemy, 61u, 6u);
						}
						if (scroll_target->x == (UINT16) 80u << 3 && scroll_target->y > (UINT16) 14u << 3){
							spawn_item(scrigno_shield, 93u, 18u, 2, 1);
						}
						if (scroll_target->x == (UINT16) 67u << 3){
							spawn_enemy(SpriteRat, 81u, 3u);
							spawn_enemy(SpriteEnemy, 88u, 3u);
							spawn_enemy(SpriteSpider, 85u, 5u);
							spawn_item(scrigno_dcoin, 85u, 5u, 7, 1);
						}
						if ((scroll_target->x == (UINT16) 97u << 3 | scroll_target->x == (UINT16) 101u << 3 | scroll_target->x == (UINT16) 108u << 3) && scroll_target->y < (UINT16) 6u << 3 ){
							scroll_target->x++;
							spawn_enemy(SpriteSpider, (scroll_target->x >> 3) + 3u, 3u);
							spawn_enemy(SpriteSpider, (scroll_target->x >> 3) - 3u, 3u);
						}
						if (scroll_target->x == (UINT16) 177u << 3){
							spawn_item(scrigno_dcoin, 192u, 7u, 7, 1);
						}
						
					break;
					case 1:
						if (scroll_target->x == (UINT16) 4u << 3 && scroll_target->y >= (INT16) 12u  << 3 && scroll_target->y <= (INT16) 17u  << 3){
							spawn_enemy(SpriteRat, 14u, 14u);
							spawn_enemy(SpriteSpider, 13u, 13u);
						}
						if (scroll_target->x == (UINT16) 29u << 3 && scroll_target->y == (INT16) 3u  << 3){
							spawn_item(scrigno_dcoin, 45u, 3u, 1, 1);
						}
						if (scroll_target->x == (UINT16) 37u << 3 && scroll_target->y == (INT16) 21u  << 3){
							spawn_item(scrigno_shield, 46u, 21u, 2, 0);
						}
						if (scroll_target->x == (UINT16) 28u << 3 && scroll_target->y == (INT16) 14u << 3){
							spawn_enemy(SpritePlatform, 34u, 14u);
							spawn_enemy(SpriteRat, 45u, 14u);
							spawn_item(scrigno_up, 44u, 13u, 3, 1);
						}
						if (scroll_target->x == (UINT16) 42u << 3 && scroll_target->y == (INT16) 28u  << 3){
							spawn_enemy(SpriteSpider, 48u, 26u);
						}
						if (scroll_target->x == (UINT16) 53u << 3 && scroll_target->y == (INT16) 28u  << 3){
							spawn_enemy(SpriteSpider, 64u, 21u);
							spawn_item(scrigno_dcoin, 67u, 23u, 7, 1);
						}
						if (scroll_target->x == (UINT16) 66u << 3 && scroll_target->y == (INT16) 10u  << 3){
							spawn_enemy(SpriteRat, 64u, 15u);
							spawn_enemy(SpriteRat, 60u, 15u);
							spawn_item(scrigno_up, 62u, 15u, 3, 1);
						}
						if (scroll_target->x == (UINT16) 89u << 3 && scroll_target->y == (INT16) 27u << 3){
							spawn_item(scrigno_dcoin, 93u, 14u, 1, 1);
						}
					break;
				}
			break;
			case 2:
				switch(current_map){
					case 0:
						if (scroll_target->x == (UINT16) 37u << 3){
							spawn_item(scrigno_up, 46u, 0u, 3, 1);
						}
						if (scroll_target->x == (UINT16) 43u << 3){
							spawn_enemy(SpriteSpider, 51u, 9u);
							spawn_enemy(SpriteEnemy, 56u, 9u);
						}
						if (scroll_target->x == (UINT16) 84u << 3){
							spawn_enemy(SpriteBird, 90u, 3u);
						}
						if (scroll_target->x == (UINT16) 104u << 3){
							spawn_enemy(SpriteEnemy, 115u, 10u);
							spawn_enemy(SpriteBird, 90u, 3u);
						}
						if (scroll_target->x == (UINT16) 119u << 3){
							spawn_enemy(SpritePlatform, 131u, 10u);
							spawn_enemy(SpriteBird, 140u, 3u);
							spawn_enemy(SpriteBird, 114u, 4u);
						}
						if (scroll_target->x == (UINT16) 143u << 3){
							spawn_enemy(SpriteBird, 155u, 3u);
						}
						if (scroll_target->x == (UINT16) 150u << 3 | scroll_target->x == (UINT16) 151u << 3){
							spawn_enemy(SpriteBird, 140u, 3u);
							spawn_enemy(SpriteSpider, 162u, 9u);
							spawn_enemy(SpriteEnemy, 165u, 9u);
						}
						if (scroll_target->x == (UINT16) 167u << 3){
							spawn_enemy(SpriteBird, 178u, 3u);
							spawn_enemy(SpriteBird, 160u, 3u);
						}
						if (scroll_target->x == (UINT16) 170u << 3){
							spawn_item(scrigno_shield, 183u, 6u, 2, 1);
						}
					break;
					case 1:
						if (scroll_target->x == (UINT16) 123u << 3){
							spawn_enemy(SpriteBird, 135u, 5u);
						}
						if (scroll_target->x == (UINT16) 128u << 3){
							spawn_enemy(SpriteBird, 116u, 5u);
							spawn_enemy(SpriteSpider, 135u, 10u);
							spawn_enemy(SpriteSpider, 136u, 9u);
						}
						if (scroll_target->x == (UINT16) 141u << 3){
							spawn_enemy(SpriteBird, 130u, 5u);
						}
						if (scroll_target->x == (UINT16) 152u << 3){
							spawn_enemy(SpriteBird, 165u, 5u);
						}
						if (scroll_target->x == (UINT16) 163u << 3){
							spawn_enemy(SpriteBird, 175u, 5u);
						}
						if (scroll_target->x == (UINT16) 170u << 3){
							spawn_enemy(SpriteBird, 182u, 5u);
							spawn_enemy(SpriteSpider, 173u, 8u);
						}
					break;
				}
			break;
		}
	}
	
	//MOVING BACKGROUND TILES	
	//if (current_level == 1u || current_level == 2u){
		updatecounter++;
		if (updatecounter < 21) {
			switch(updatecounter){
				case 1:
					AnimWaters0();
				break;
				case 10:
					AnimWaters1();
				break;
			}			
		}else{
			updatecounter = 0;
		}
	//}
	
	
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
		if (amulet != archer_data->amulet | amulet == 0u){
			amulet = archer_data->amulet;
			UpdateHUD();
		}
		if (coins != archer_data->coins){
			coins = archer_data->coins;
			UpdateHUD();
		}
		if (hp != archer_data->hp && archer_data->hp >= 0){
			if(archer_data->hp < hp){
				hp--;
			}else{
				hp++;
			}
			UpdateHUD();
		}
		if (ups != archer_data->ups){
			ups = archer_data->ups;
			UpdateHUD();
		}
		if(archer_tool != archer_data->tool){// & archer_tool == level_tool
			archer_tool = archer_data->tool;
			UpdateHUD();
		}
	}
	
}

void UpdateHUD(){
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
		if (archer_data->coins > 9){
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

void LCD_isr() NONBANKED {
    if (LYC_REG == 0) {
        if (WY_REG == 0) HIDE_SPRITES; else SHOW_SPRITES; 
        LYC_REG = WY_REG;
    } else {
        HIDE_SPRITES; 
        LYC_REG = 0;
    }
}

void set_window_y(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}
