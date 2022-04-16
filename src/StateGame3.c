#include "Banks/SetAutoBank.h"

#include <stdbool.h>

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Music.h"

#include "custom_datas.h"
#include "TileAnimations.h"
#include "Dialogs.h"
#include "sgb_palette.h"

IMPORT_TILES(font);
IMPORT_TILES(tiles4);

IMPORT_MAP(map4);
IMPORT_MAP(map41);
IMPORT_MAP(map50);
IMPORT_MAP(map51);

IMPORT_MAP(diagnew4);
IMPORT_MAP(window4);

DECLARE_MUSIC(bgm_level_emptych1);

const UINT8 const collision_tiles3[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 68, 69, 70, 71, 73, 74, 75, 81, 90, 102, 103, 104, 111, 119, 0};//numero delle tile con zero finale

UINT8 thunder_delay = 16u;

extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next;
extern INT8 load_next_b;
extern INT8 load_next_s;
extern INT8 load_next_d;
extern INT8 load_next_gameover;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_boss;
extern INT8 is_on_secret;
extern INT8 is_on_gameover;
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
extern Sprite* platform_sprite;
extern Sprite* enemies_0;
extern Sprite* enemies_1;
extern Sprite* enemies_2;
extern Sprite* enemies_3;
extern Sprite* scrigno_coin;
extern Sprite* scrigno_dcoin;
extern Sprite* scrigno_shield;
extern Sprite* scrigno_up;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern INT8 spawning_counter;
extern UINT8 updatecounter;
extern INT8 platform_vx;
extern bool LCD_Installed;
extern INT8 update_hud;
extern INT8 fx_cooldown;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

void UpdateHUD3() BANKED;
void ShowWindow3() BANKED;
void ShowWindowDiag3() BANKED;
void set_window_y3(UBYTE y);
void spawn_enemy3(UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED;
void spawn_item3(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno) BANKED;
Sprite* spawn_vplatform4(Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED;

Sprite* spawn_vplatform4(Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED{
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)enem->custom_data;
	data_platform->type = 1;
	return enem;
}

void START() {
	
	current_camera_state = 0u;
	current_camera_counter = 0u;
	fx_cooldown = 0;
	
	if (current_level < 3u){
		SetState(StateGame);
	}else if (current_level > 4u && current_level < 7u){
		//SetState(StateGame6);
	}

	//INIT SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0xFF; //Max volume 0x77

	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpritePlatform);
	SpriteManagerLoad(SpriteItem);

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
			SpriteManagerLoad(SpritePuff);
			if(current_map == 0){
				SpriteManagerLoad(SpriteRat);
				SpriteManagerLoad(SpriteBee);
			}else if (current_map == 1){
				SpriteManagerLoad(SpriteRat);
				SpriteManagerLoad(SpriteSpider);
				SpriteManagerLoad(SpriteBee);
			}
			if(sgb_check()){
				set_sgb_palette01_TREES();
				set_sgb_palette_statusbar();
			}
		break;
	}		
	SHOW_SPRITES;

	//CLEAN DIAGS
	memcpy(d1, "                    ", 20);
	memcpy(d2, "                    ", 20);
	memcpy(d3, "                    ", 20);
	memcpy(d4, "                    ", 20);

	//SCROLL	
	scroll_bottom_movement_limit = 62u;	

	const struct MapInfo* const level_4[] = {
		&map41,
		&map4
	};
	const struct MapInfo* const level_5[] = {
		&map50, &map51
	};

	const struct MapInfo** const levels45[] = {level_4, level_5};

	UINT8 level_4_banks[] = {BANK(map41), BANK(map4)};
	UINT8 level_5_banks[] = {BANK(map50), BANK(map51)};
	UINT8 * levels45_banks[] = {level_4_banks, level_5_banks};

	const struct MapInfo** maps45 = levels45[current_level-3];
	UINT8* map45banks = levels45_banks[current_level-3];
	UINT8 map_w4 = 0;
	UINT8 map_h4 = 0;
	GetMapSize((UINT8) map45banks[current_map], maps45[current_map], &map_w4, &map_h4);

	if (load_next_s == -1){ //COME FROM STATE SECRET
		ResumeMusic;
		ScrollFindTile((UINT8) map45banks[current_map], maps45[current_map], 45, 0, 0, 
			map_w4, map_h4, &drop_player_x, &drop_player_y);
	}else if(load_next || load_next_d == 0 || load_next_gameover){
		spawning_counter = 0;
		//PlayMusic(bgm_level_emptych1, 1);
		ScrollFindTile((UINT8) map45banks[current_map], maps45[current_map], 9, 0, 0, 
			map_w4, map_h4, &drop_player_x, &drop_player_y);		
	}//else COME FROM THE DIALOG STATE, I ALREADY SAVED PLAYER COORDS IN drop_player_x/y
	else{
		ResumeMusic;
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll((UINT8) map45banks[current_map], maps45[current_map], collision_tiles3, 0);
	SHOW_BKG;
	
	//INIT ARCHER
	is_on_boss = -1;
	archer_data->hp = hp;
	archer_data->ups = ups;
	archer_data->coins = coins;
	archer_data->tool = archer_tool;
	archer_state = STATE_JUMPING;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 0, 4);
	ShowWindow3();

	//INIT ENEMIES	
	enemies_0 = 0;
	enemies_1 = 0;
	enemies_2 = 0;
	enemies_3 = 0;
	
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
	
	if(load_next_s == -1){
		load_next_s = 0;
	}else if (load_next_d == 0){//copiato dallo SpritePlayer quando chiedo il tip
		diag_found = Build_Next_Dialog_Banked(scroll_target);
		if(diag_found){
			//archer_state = STATE_DIAG;
			//show_diag = 1;	
		}
	}
	load_next_d = 0;	

}

void ShowWindow3() BANKED{
	set_window_y3(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, BANK(window4), &window4);
	SHOW_WIN;

	UpdateHUD3();
}

void ShowWindowDiag3() BANKED{
	if (showing_diag == 0){
		HIDE_WIN;
		set_window_y3(144 - 32);
		WX_REG = 0;
		WY_REG = 144 - 32; //40
		InitWindow(0, 0, BANK(diagnew4), &diagnew4);
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

void spawn_enemy3(UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED{
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
}

void spawn_item3(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno) BANKED{
	SpriteManagerRemoveSprite(itemin);
	Sprite* itemnew = SpriteManagerAdd(SpriteItem, (UINT16) posx << 3, (UINT16) posy << 3);
	struct ItemInfo* datascrigno = (struct ItemInfo*)itemnew->custom_data;
	datascrigno->setup = 1u;
	if(scrigno){
		//se la vita del player è 100% e vorrei spawnare scudo, spawno dcoin !
		if(content_type == 2 && archer_data->hp == MAX_HP){
			content_type = 7;
		}
		datascrigno->content_type = content_type;
		datascrigno->type = 10;
	}else{
		datascrigno->type = content_type;
	}
}

void UPDATE() {
	
	if(load_next_d){
		switch(load_next_d){
			case 1: //vado allo StateDiag
				diag_found = Build_Next_Dialog_Banked(scroll_target);
				PauseMusic;
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
				PauseMusic;
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
				//SetState(StateGame6);
			break;
			case 7:
			break;
		} 
	}
	
	if(load_next_s == 1){
		load_next_s = 0;
		is_on_secret = 1;
		PauseMusic;
		SetState(StateSecret);
	}
	
	if(load_next_b){
		switch(load_next_b){
			case 1: //vado allo StateBoss
				if(archer_state != STATE_DIAG){
					load_next_b = 0;
					SetState(StateBoss);
				}
			break;
			/*case 2: // provengo dal boss, vado al next level
			break;*/
		}
	}	
	
	if(load_next_gameover){
		load_next_gameover = 0;
		is_on_gameover = 1;
		SetState(StateGameover);
	}
	
	if(fx_cooldown > 1){
		fx_cooldown--;
		//NR12_REG = 0xF0;
		//NR22_REG = 0x20;
		//NR32_REG = 0x20;
		//NR42_REG = 0x20;
	}else if (fx_cooldown == 1){
		UNMUTE_ALL_CHANNELS;
		fx_cooldown--;
	}

	// SPAWNING
	switch(current_level){
		case 3u: // Sky -> Ibex
			switch(current_map){
				case 0u:
					if (scroll_target->x > (UINT16) 93u << 3 && scroll_target->x < (UINT16) 143u << 3 ){
						if (scroll_target->x == (UINT16) 120u << 3){
							scroll_target->x++;
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
					}
					if (scroll_target->x == (UINT16) 135u << 3){						
						scroll_target->x++;
						Sprite* gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 152u << 3, (UINT16) 10u << 3);
						struct EnemyInfo* gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
						gatedata->vx = 3;						
						Sprite* gate_sprite2 = SpriteManagerAdd(SpriteGate, (UINT16) 151u << 3, (UINT16) 10u << 3);
						struct EnemyInfo* gatedata2 = (struct EnemyInfo*)gate_sprite2->custom_data;
						gatedata2->vx = 3;
					}
				break;
				case 1u:
					if(scroll_target->mirror != V_MIRROR && archer_state != STATE_HIT){
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
									scroll_target->x++;
									spawn_item3(scrigno_shield, 39u, 4u, 2, 1);
								}
								if(scroll_target->x == (UINT16) 140u << 3){
									scroll_target->x++;
									spawn_item3(scrigno_shield, 156u, 5u, 2, 1);							
								}					
								if(scroll_target->x == (UINT16) 175u << 3){
									scroll_target->x++;
									spawn_item3(scrigno_shield, 185u, 4u, 2, 1);
								}
							break;
						}
					thunder_delay -= 1u;
					}						
				break;
			}
		break;
		case 4u: // Trees -> Bear
			switch(current_map){
				case 0u:
					if(scroll_target->x > (UINT16) 25u << 3 && scroll_target->y < (UINT16) 14u << 3 && spawning_counter == 0){
						spawn_item3(scrigno_shield, 31u, 17u, 2, 1);
						spawn_enemy3(SpriteBee, 33u, 13u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 42u << 3 && scroll_target->y < (UINT16) 14u << 3 && spawning_counter == 1){
						spawn_enemy3(SpriteRat, 36u, 15u);
						spawn_enemy3(SpriteBee, 37u, 18u);
						spawning_counter++;
					}
					if(scroll_target->x < (UINT16) 16u << 3 && scroll_target->y < (UINT16) 22u << 3 && scroll_target->y > (UINT16) 13u << 3 && spawning_counter == 2){
						spawn_item3(scrigno_up, 9u, 25u, 3, 1);
						spawn_enemy3(SpriteBee, 8u, 26u);
						spawning_counter++;
					}
					if(scroll_target->x < (UINT16) 12u << 3 && scroll_target->y < (UINT16) 36u << 3 && scroll_target->y > (UINT16) 27u << 3 && spawning_counter == 3){
						spawn_item3(scrigno_dcoin, 13u, 38u, 7, 1);
						spawn_enemy3(SpriteBee, 8u, 39u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 15u << 3 && scroll_target->x < (UINT16) 22u << 3 
						&& scroll_target->y > (UINT16) 36u << 3 && scroll_target->y < (UINT16) 42u << 3 && spawning_counter == 4){
						spawn_item3(scrigno_dcoin, 42u, 38u, 7, 1);
						spawn_enemy3(SpriteBee, 40u, 42u);
						spawn_enemy3(SpriteRat, 26u, 38u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 1u << 3 && scroll_target->y > (UINT16) 55u << 3 && scroll_target->y < (UINT16) 62u << 3 && spawning_counter == 5){
						spawn_enemy3(SpriteRat, 22u, 57u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 8u << 3 && scroll_target->y > (UINT16) 60u << 3 && spawning_counter == 6){
						spawn_enemy3(SpriteBee, 18u, 62u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 21u << 3 && scroll_target->y > (UINT16) 60u << 3 && spawning_counter == 7){
						spawn_enemy3(SpriteRat, 30u, 63u);						
						spawn_item3(scrigno_dcoin, 25u, 63u, 7, 1);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 23u << 3 && scroll_target->y > (UINT16) 60u << 3 && spawning_counter == 8){
						spawn_enemy3(SpriteRat, 20u, 63u);
						spawning_counter++;
					}
				break;
				case 1u:
					if(scroll_target->y > (UINT16) 10u << 3 && spawning_counter == 0){
						spawn_enemy3(SpriteSpider, 31u, 13u);
						spawn_enemy3(SpriteBee, 34u, 13u);
						if(scroll_target->x > (UINT16) 20u << 3){
							spawn_item3(scrigno_dcoin, 34u, 2u, 7, 0);
						}
						spawning_counter++;
					}
					if(scroll_target->y > (UINT16) 20u << 3 && spawning_counter == 1){
						spawn_enemy3(SpriteRat, 16u, 15u);
						spawn_enemy3(SpriteSpider, 18u, 15u);
						spawning_counter++;
					}
					if(scroll_target->y < (UINT16) 33u << 3 && spawning_counter == 2){
						spawn_enemy3(SpriteRat, 30u, 28u);
						spawn_enemy3(SpriteSpider, 23u, 27u);
						spawning_counter++;
					}
					if(scroll_target->y > (UINT16) 34u << 3 && spawning_counter == 3){
						spawn_enemy3(SpriteBee, 39u, 38u);
						spawn_item3(scrigno_shield, 43u, 41u, 2, 1);
						spawning_counter++;
					}
				break;
			}
		break;
	}

	//MOVING BACKGROUND TILES	
	updatecounter++;
	if (updatecounter < 120) {		
		if (current_level != 3u){
			switch(updatecounter){
				case 1:
				case 20:
					AnimSliders0();
				break;
				case 40:
					AnimSliders1();
				break;
				case 60:
					AnimWaters0();
					AnimSpuncioni0();
					AnimSliders1();
				break;
				case 80:
					AnimSliders0();
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
					AnimSliders1();
				break;
				case 20:
					AnimClouds0();
					AnimRain1();
				break;
				case 40:
					AnimClouds1();
					AnimRain0();
				break;
				case 60:
					AnimClouds1();
					AnimRain1();
					AnimSliders0();
				break;
				case 80:
					AnimRain0();
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
		UpdateHUD3();
	}
	
}

void UpdateHUD3() BANKED{
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
	if(hp<=0)hp=0;
	INT8 i;
	for(i = 0; i != hp; ++i) {
		set_win_tiles(5 + i, 0, 1, 1, &SHIELD_TILE);
	}
	for(; i != MAX_HP; ++i) {
		set_win_tiles(5 + i, 0, 1, 1, &EMPTY_TILE);
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

void set_window_y3(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}
