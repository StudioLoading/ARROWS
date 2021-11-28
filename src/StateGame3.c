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
#include "Dialogs.h"
#include "sgb_palette.h"


const UINT8 const collision_tiles3[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 68, 69, 70, 71, 73, 74, 75, 81, 90, 102, 103, 104, 111, 119, 0};//numero delle tile con zero finale


extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next;
extern INT8 load_next_b;
extern INT8 load_next_s;
extern INT8 load_next_d;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_boss;
extern INT8 is_on_secret;
extern INT8 archer_tool;
extern UINT8 current_camera_state;
extern UINT8 current_camera_counter;
extern UINT8 diag_found;

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
extern struct Sprite* scrigno_coin;
extern struct Sprite* scrigno_dcoin;
extern struct Sprite* scrigno_shield;
extern struct Sprite* scrigno_up;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern INT8 spawning_triggered;

extern UINT8 updatecounter;
extern INT8 platform_vx;
extern bool LCD_Installed;
extern INT8 update_hud;

void UpdateHUD3();
void ShowWindow3();
void ShowWindowDiag3();
void set_window_y3(UBYTE y);
void LCD_isr3();
void spawn_enemy3(UINT8 spriteType, UINT16 posx, UINT16 posy);
void spawn_item3(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

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

const UINT16 bg_palette3[] = {PALETTE_FROM_HEADER(tiles4)};

UINT8 thunder_delay = 16u;


void spawn_enemy3(UINT8 spriteType, UINT16 posx, UINT16 posy){
	spawning_triggered++;
	if(spriteType == SpritePlatform){
		platform_sprite = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
		return;
	}	
	SpriteManagerRemoveSprite(enemies_3);
	enemies_3 = enemies_2;
	enemies_2 = enemies_1;
	if(enemies_0 == 0 || enemies_1 == 0 || enemies_2 == 0 || enemies_3 == 0){
		enemies_0 = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	}
	/*PRINT_POS(16, 0);
	Printf("%d", enlen4);*/
}

struct Sprite* spawn_vplatform4(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy){
	spawning_triggered++;
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)enem->custom_data;
	data_platform->type = 1;
	return enem;
}

void spawn_item3(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
	spawning_triggered++;
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

void ShowWindow3(){
	set_window_y3(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, &window4);
	SHOW_WIN;
	
	UpdateHUD3();
}

void ShowWindowDiag3(){
	if (showing_diag == 0){
		HIDE_WIN;
		set_window_y3(144 - 32);
		WX_REG = 0;
		WY_REG = 144 - 32; //40
		InitWindow(0, 0, &diagnew4);
		SHOW_WIN;
		
		PRINT_POS(1,0);
		Printf(d1);
		PRINT_POS(1,1);
		Printf(d2);
		PRINT_POS(1,2);
		Printf(d3);
		PRINT_POS(1,3);
		Printf(d4);
		
		showing_diag = 1;

	}
	
}

void Start_StateGame3() {
	
	is_on_boss = -1;
	thunder_delay = 16u;
	current_camera_state = 0u;
	current_camera_counter = 0u;
	
	if (current_level < 3u){
		SetState(StateGame);
	}else if (current_level > 4u && current_level < 7u){
		SetState(StateGame6);
	}
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette3, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	SpriteManagerLoad(SpritePuff);
	//LOAD SPRITES OF THE MAP
	switch (current_level){
		case 3u:
			SpriteManagerLoad(SpriteThunder);
			SpriteManagerLoad(SpriteHurricane);
			SpriteManagerLoad(SpriteGate);
			if(sgb_check()){
				set_sgb_palette01_1B();
				set_sgb_palette_statusbar();
			}
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
			if(sgb_check()){
				set_sgb_palette01_TREES();
				set_sgb_palette_statusbar();
			}
		break;
	}		
	SHOW_SPRITES;

	//SCROLL
	//if (current_level == 2u & current_map == 0u)
	scroll_bottom_movement_limit = 62;

	const struct MapInfo** lvls4 = maps4[current_level-3u];
	UINT8 map_w4;
	UINT8 map_h4;
	GetMapSize(lvls4[current_map], &map_w4, &map_h4);
	if (load_next_s == -1){ //COME FROM STATE SECRET
		ScrollFindTile(lvls4[current_map], 45, 0, 0, map_w4, map_h4, &drop_player_x, &drop_player_y);
	}else if(load_next || load_next_d == 0){
		ScrollFindTile(lvls4[current_map], 9, 0, 0, map_w4, map_h4, &drop_player_x, &drop_player_y);		
	}//else COME FROM THE DIALOG STATE, I ALREADY SAVED PLAYER COORDS IN drop_player_x/y
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll(lvls4[current_map], collision_tiles3, 0);
	SHOW_BKG;
	
	//INIT ARCHER
	is_on_boss = -1;	
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 0u;
		archer_tool = 0;
		hp = 50;
	}	
	archer_data->hp = hp;
	archer_data->ups = ups;
	archer_data->coins = coins;
	archer_data->tool = archer_tool;
	archer_state = STATE_JUMPING;
	UpdateHUD3();	
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow3();
	
	//SET LEVEL TOOL
	/*switch(current_level){
		case 0u:
			switch(current_map){
				case 0u:
					level_tool = 6;
				break;
			}
		break;
		case 1:
			switch(current_map){
				case 1u:
					level_tool = 7;
				break;
			}
		break;
	}*/
	
	//INIT SPAWNING
	
	enemies_0 = 0;
	enemies_1 = 0;
	enemies_2 = 0;
	enemies_3 = 0;

	if (load_next_s > -1 && load_next_d == 0){ // NON vengo da secret nè da dialogo!
		switch(current_level){
			case 3u:
				switch(current_map){
					case 1u:
						spawn_item3(scrigno_up, 10u, 9u, 3, 1);
					break;
				}
			break;
			case 4u:
				switch(current_map){
					case 1u:
						spawn_item3(scrigno_shield, 9u, 2u, 2, 1);
					break;
				}
			break;
		}
	}
	
	if(load_next_d){
		load_next_d = 0;
	}	
	if(load_next_s == -1){
		load_next_s = 0;
	}
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
	if (!LCD_Installed) { 
		CRITICAL {
			add_LCD(LCD_isr3);
			set_interrupts(VBL_IFLAG | LCD_IFLAG);
			STAT_REG |= 0x40; 
			set_window_y3(144-8);
		}
	    LCD_Installed = true; 
	}
	
}

void Update_StateGame3() {
	
	if(load_next_d){
		switch(load_next_d){
			case 1: //vado allo StateDiag
				diag_found = Build_Next_Dialog_Banked(scroll_target);
				load_next_d = 2;
				SetState(StateDiag);
			break;
			case 2:
				load_next_d = 0;
				if(is_on_boss == 0){
					load_next_b = 1;
				}
			break;
		}		
	}
	
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
				SetState(StateGame);	
			break;
			case 3:
			case 4:
				SetState(StateGame3);
			break;
			case 5:
			case 6:
				SetState(StateGame6);
			break;
			case 7:
			break;
		} 
	}
	
	if(load_next_s == 1){
		load_next_s = 0;
		is_on_secret = 1;
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
	
	// SPAWNING
	if(!SPRITE_GET_VMIRROR(scroll_target) && archer_state != STATE_HIT && platform_vx == 0u){
		switch(current_level){
			case 3u: // Sky -> Ibex
				switch(current_map){
					case 0u:
						if (scroll_target->x > (UINT16) 93u << 3 && scroll_target->x < (UINT16) 143u << 3 ){
							if (scroll_target->x == (UINT16) 120u << 3){
								spawn_item3(scrigno_shield, 133u, 9u, 2, 1);
							}
							switch(thunder_delay){
								case 60u:
									spawn_enemy3(SpriteHurricane, (scroll_target->x >> 3) + 5u, 5u);
								break;
								case 120u:
									spawn_enemy3(SpriteHurricane, (scroll_target->x >> 3) + 4u, 6u);
								break;
								case 180u:
									spawn_enemy3(SpriteHurricane, (scroll_target->x >> 3) + 4u, 6u);
								break;
								case 0u:
									spawn_enemy3(SpriteHurricane, (scroll_target->x >> 3), 7u);
									thunder_delay = 180u;
								break;
							}
							thunder_delay -= 1u;
							//PRINT_POS(16,0);
							//Printf("%d", thunder_delay);
						}
						if (scroll_target->x == (UINT16) 120u << 3){							
							struct Sprite* gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 152u << 3, (UINT16) 10u << 3);
							struct EnemyInfo* gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
							gatedata->vx = 3;
						}
					break;
					case 1u:
						switch(thunder_delay){
							case 40u:
								spawn_enemy3(SpriteThunder, (scroll_target->x >> 3) + 2u, 4u);
							break;
							case 80u:
								spawn_enemy3(SpriteThunder, (scroll_target->x >> 3) - 2u, 4u);
							break;
							case 120u:
								spawn_enemy3(SpriteThunder, (scroll_target->x >> 3) + 1u, 4u);
							break;
							case 0u:
								spawn_enemy3(SpriteThunder, (scroll_target->x >> 3) + 5u, 4u);
								thunder_delay = 160u;
							break;
							default:
								if (scroll_target->x == (UINT16) 30u << 3){
									spawn_item3(scrigno_shield, 39u, 4u, 2, 1);
								}
								if(scroll_target->x == (UINT16) 140u << 3){
									spawn_item3(scrigno_shield, 156u, 5u, 2, 1);							
								}					
								if(scroll_target->x == (UINT16) 175u << 3){
									spawn_item3(scrigno_shield, 185u, 4u, 2, 1);
								}
							break;
						}
						thunder_delay -= 1u;					
					break;
				}
			break;
			case 4u: // Trees -> Bear
				switch(current_map){
					case 0u:
						if(scroll_target->x == (UINT16) 25u << 3 && scroll_target->y < (UINT16) 14u << 3){
							spawn_item3(scrigno_shield, 31u, 17u, 2, 1);
							//snake3 = spawn_vplatform4(snake3, SpritePlatform, 5u, 19u);
						}
						if(scroll_target->x == (UINT16) 26u << 3 && 
							scroll_target->y == (UINT16) 38u << 3 && spawning_triggered <= 1){
							enemies_0 = spawn_vplatform4(enemies_2, SpritePlatform, 37u, 43u);
							enemies_1 = spawn_vplatform4(enemies_3, SpritePlatform, 42u, 51u);
						}
						if(scroll_target->x == (UINT16) 30u << 3 && scroll_target->y > (UINT16) 60u << 3 && spawning_triggered <= 3 ){
							spawn_enemy3(SpriteRat, (scroll_target->x >> 3) -8u, (scroll_target->y >> 3) - 4u);
							spawn_enemy3(SpriteSpider, 20u, 58u);
						}
						if(scroll_target->x == (UINT16) 23u << 3 && scroll_target->y > (UINT16) 60u << 3 && spawning_triggered <= 5){
							spawn_enemy3(SpriteRat, (scroll_target->x >> 3) + 6u, (scroll_target->y >> 3) -4u);
							spawn_enemy3(SpriteRat, (scroll_target->x >> 3) - 8u, (scroll_target->y >> 3) -4u);
						}
						if(scroll_target->x == (UINT16) 11u << 3 && scroll_target->y > (UINT16) 64u << 3 && spawning_triggered <= 7){
							spawn_enemy3(SpriteSpider, 24u, 63u);
							spawn_enemy3(SpriteSpider, 20u, 64u);
						}
						if(scroll_target->x == (UINT16) 25u << 3 && scroll_target->y > (UINT16) 64u << 3 && spawning_triggered <= 8){
							spawn_enemy3(SpriteRat, 20u, 63u);
						}						
						if(scroll_target->x == (UINT16) 34u << 3 && scroll_target->y > (UINT16) 64u << 3 && spawning_triggered <= 9){
							spawn_enemy3(SpriteRat, 30u, 63u);
						}
					break;
					case 1u:
						if(scroll_target->x == (UINT16) 31u << 3 && scroll_target->y < (UINT16) 10u << 3 && spawning_triggered <= 1){
							spawn_item3(scrigno_dcoin, 34u, 2u, 7, 0);
						}
						if(scroll_target->x == (UINT16) 23u << 3 && scroll_target->y < (UINT16) 28u << 3 && scroll_target->y > (UINT16) 25u << 3 && spawning_triggered <= 2){
							spawn_enemy3(SpriteRat, 17u, 28u);
						}
						if(scroll_target->x == (UINT16) 30u << 3 && scroll_target->y < (UINT16) 28u << 3 && scroll_target->y > (UINT16) 25u << 3 && spawning_triggered <= 3){
							spawn_enemy3(SpriteRat, 30u, 28u);
							spawn_enemy3(SpriteSpider, 23u, 27u);
						}
						if(scroll_target->x == (UINT16) 34u << 3 && scroll_target->y < (UINT16) 39u << 3 && scroll_target->y > (UINT16) 36u << 3 && spawning_triggered <= 5){
							spawn_item3(scrigno_shield, 43u, 41u, 2, 1);
						}
					break;
				}
			break;
		}
	}
	
	//MOVING BACKGROUND TILES	
	updatecounter++;
	if (updatecounter < 120) {		
		if (current_level != 3u){
			switch(updatecounter){
				case 1:
				case 60:
					AnimWaters0();
					AnimSpuncioni0();
				break;
				case 30:
				case 90:
					AnimWaters1();
					AnimSpuncioni1();
				break;
			}
		}else{ //cioè liv3 sky
			switch(updatecounter){
				case 1:
					AnimClouds0();
					AnimRain0();
				break;
				case 40:
					AnimClouds1();
					AnimRain0();
				break;
				case 80:
					AnimRain1();
				break;
				case 20:
					AnimClouds0();
					AnimRain1();
				break;
				case 60:
					AnimClouds1();
					AnimRain1();
				break;
				case 100:
					AnimRain1();
				break;
			}
		
		}
	}else{
		updatecounter = 0;
	}
	
	
	//DIAG MANAGEMENT
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow3();
		return;
	}	
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag3();
			return;
		}
	}
	
	//HUD MANAGEMENT
	if (update_hud != 0){
		update_hud = 0;
		hp = archer_data->hp;
		amulet = archer_data->amulet;
		coins = archer_data->coins;
		ups = archer_data->ups;
		UpdateHUD3();
	}
	
}

void UpdateHUD3(){
	hp = archer_data->hp;
	amulet = archer_data->amulet;
	coins = archer_data->coins;
	ups = archer_data->ups;
	archer_tool = archer_data->tool;
	//write amulet
	PRINT_POS(18,0);
	switch (archer_data->amulet){
		//case 1: Printf("$"); break;
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
	if(hp < 0){
		Printf("XX");
	}else if (hp < 10){ // archer_data->hp < 10 &&
		Printf("0");
		PRINT_POS(8, 0);
		Printf("%d", hp);
	}else if (hp >= 100){ // archer_data->hp >= 100 &&
		Printf("99");	
	}else if (hp > 9){ // archer_data->hp > 9 && archer_data->hp < 100 && 
		Printf("%d", hp);
	}
	//write tool
	if (archer_data->tool == level_tool){
		switch(level_tool){
			case 6: //key
				PRINT_POS(16, 0);
				Printf("{");
			break;
			case 7: //wrench
				PRINT_POS(16, 0);
				Printf("<");
			break;
		}
	}
	//write ups
	PRINT_POS(2, 0); //up
	if (archer_data->ups > 9){Printf("%d", archer_data->ups);}
	else if (archer_data->ups >= 0){Printf("0%d", archer_data->ups);}
}

void LCD_isr3() NONBANKED {
    if (LYC_REG == 0) {
        if (WY_REG == 0) HIDE_SPRITES; else SHOW_SPRITES; 
        LYC_REG = WY_REG;
    } else {
        HIDE_SPRITES; 
        LYC_REG = 0;
    }
}

void set_window_y3(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}
