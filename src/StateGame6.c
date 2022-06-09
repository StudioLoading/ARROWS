#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Music.h"

#include "custom_datas.h"
#include "TilesAnimations0.h"
#include "Dialogs.h"
#include "sgb_palette.h"

IMPORT_TILES(font);
IMPORT_TILES(tiles6);

IMPORT_MAP(map60);
IMPORT_MAP(map61);
IMPORT_MAP(map70);
IMPORT_MAP(map71);
IMPORT_MAP(mapcutscene0);

IMPORT_MAP(diagnew6);
IMPORT_MAP(window6);


const UINT8 const collision_tiles6[] = {2, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 20, 26, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 61, 62, 64, 69, 80, 81, 82, 83, 84, 85, 86, 87, 111, 119, 0};//numero delle tile di collisione seguito da zero finale
const UINT8 const collision_tiles_cutscene0[] = {5, 7, 8, 10, 11, 13, 16, 17, 18, 19, 20, 29, 37, 0};

UINT8 bank_tiles6 = BANK(tiles6);

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
extern INT8 update_hud;
extern INT8 fx_cooldown;
extern UINT8 thunder_delay;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;
extern UINT8 quiver;

void UpdateHUD6() BANKED;
void ShowWindow6() BANKED;
void ShowWindowDiag6() BANKED;
void set_window_y6(UBYTE y);
void spawn_enemy6(UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED;
void spawn_item6(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno) BANKED;
Sprite* spawn_vplatform6(Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED;

Sprite* spawn_vplatform6(Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED{
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)enem->custom_data;
	data_platform->type = 1;
	return enem;
}

INT8 amulet_spawn;
void spawn_falci(UINT16 x, UINT16 y);

void START() {
	
	current_camera_state = 0u;
	current_camera_counter = 0u;
	fx_cooldown = 0;
	
	switch(current_level){
		case 0u:
		case 1u:
		case 2u:
			SetState(StateGame);
		break;
		case 3u:
		case 4u:
			SetState(StateGame3);
		break;
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
		case 5u:
			SpriteManagerLoad(SpriteStalagmite);
			SpriteManagerLoad(SpriteStalattite);
			SpriteManagerLoad(SpritePenguin);
			SpriteManagerLoad(SpriteGate);
			SpriteManagerLoad(SpriteIceplat);
			if(sgb_check()){
				set_sgb_palette01_ICE();
				set_sgb_palette_statusbar();
			}
		break;
		case 6u:
			amulet_spawn = 0;
			SpriteManagerLoad(SpriteAxethrower);
			SpriteManagerLoad(SpriteAxe);
			SpriteManagerLoad(SpriteBat);
			if(current_map == 0){
				SpriteManagerLoad(SpriteAmulet);
			}else if(current_map == 1){
				SpriteManagerLoad(SpriteFalce);
				SpriteManagerLoad(SpriteFalcebase);
				SpriteManagerLoad(SpriteCathead);
			}else{
				//SpriteManagerLoad(SpriteMother);
			}
			if(sgb_check()){
				set_sgb_palette01_CEMATERYCRYPT();
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

	const struct MapInfo* const level_6[] = { &map60, &map61 };
	const struct MapInfo* const level_7[] = { &map70, &map71 };

	const struct MapInfo** const levels67[] = {level_6, level_7};

	UINT8 level_6_banks[] = {BANK(map60), BANK(map61)};
	UINT8 level_7_banks[] = {BANK(map70), BANK(map71)};
	UINT8 * levels67_banks[] = {level_6_banks, level_7_banks};

	const struct MapInfo** maps67 = levels67[current_level-5];
	UINT8* map67banks = levels67_banks[current_level-5];
	UINT8 map_w6 = 0;
	UINT8 map_h6 = 0;
	GetMapSize((UINT8) map67banks[current_map], maps67[current_map], &map_w6, &map_h6);

	if (load_next_s == -1){ //COME FROM STATE SECRET
		ResumeMusic;
		ScrollFindTile((UINT8) map67banks[current_map], maps67[current_map], 45, 0, 0, 
			map_w6, map_h6, &drop_player_x, &drop_player_y);
	}else if(load_next || load_next_d == 0 || load_next_gameover){
		spawning_counter = 0;
		//PlayMusic(bgm_level_emptych1, 1);
		ScrollFindTile((UINT8) map67banks[current_map], maps67[current_map], 9, 0, 0, 
			map_w6, map_h6, &drop_player_x, &drop_player_y);		
	}//else COME FROM THE DIALOG STATE, I ALREADY SAVED PLAYER COORDS IN drop_player_x/y
	else{
		ResumeMusic;
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll((UINT8) map67banks[current_map], maps67[current_map], collision_tiles6, 0);
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
	ShowWindow6();
	
	//INIT ENEMIES	
	enemies_0 = 0;
	enemies_1 = 0;
	enemies_2 = 0;
	enemies_3 = 0;
	
	//INIT SPAWNING	
	if (load_next_s > -1 && load_next_d == 0){ // NON vengo da secret nè da dialogo!
		switch(current_level){
			case 5u:
				switch(current_map){
					case 1u:
						spawn_item6(scrigno_dcoin, 3u, 16u, 7, 1);//1coin 2hp 3up 7dcoin
						spawn_item6(scrigno_dcoin, 15u, 10u, 2, 0);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpritePenguin, 9u, 16u);
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

void UPDATE() {
	thunder_delay -= 1u;
	
	if(load_next_d){
		switch(load_next_d){
			case 1: //vado allo StateDiag
				if(diag_found == 0){
					diag_found = Build_Next_Dialog_Banked(scroll_target);
				}
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
			case 5u:
			case 6u:
				SetState(StateGame6);
			break;
			case 7u:
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
	
	if(load_next_gameover){
		load_next_gameover = 0;
		is_on_gameover = 1;
		SetState(StateGameover);
	}
	
	// SPAWNING
	switch(current_level){
		case 5u: // Ice Cave -> See King
			switch(current_map){
				case 0u:
					//dropping drop
					if (scroll_target->x > (UINT16) 8u << 3 && scroll_target->x < (UINT16) 28u << 3){
						if(thunder_delay == 0u){
							SpriteManagerAdd(SpriteStalagmite, (UINT16) 16u << 3, (UINT16) 7u << 3);
						}
					}
					if(scroll_target->x < (UINT16) 13u << 3 && spawning_counter == 0){
						spawn_item6(scrigno_up, 8u, 8u, 7, 1);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpriteStalattite, 4u, 5u);
						spawn_enemy6(SpritePenguin, 5u, 11u);
						spawning_counter++;
					}
					/*if(scroll_target->x < (UINT16) 24u << 3 && (spawning_counter == 0 || spawning_counter == 1)){
						spawn_enemy6(SpriteStalattite, 18u, 5u);
						spawning_counter = 2;
					}*/
					if(scroll_target->x > (UINT16) 26u << 3 && spawning_counter < 3){
						spawn_enemy6(SpriteStalattite, 27u, 5u);
						spawning_counter = 3;
					}
					if(scroll_target->x > (UINT16) 29u << 3 && spawning_counter == 3){
						spawn_enemy6(SpriteStalattite, 33u, 5u);
						spawn_enemy6(SpritePenguin, 39u, 11u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 30u << 3 && spawning_counter == 4){
						spawn_enemy6(SpriteStalattite, 34u, 5u);
						spawning_counter++;
					}						
					if(scroll_target->x > (UINT16) 49 << 3 && scroll_target->x < (UINT16) 69u << 3){
						if(thunder_delay == 0u){
							SpriteManagerAdd(SpriteStalagmite, (UINT16) 59u << 3, (UINT16) 10u << 3);
						}
					}
					if(scroll_target->x > (UINT16) 54u << 3 && spawning_counter == 5){
						Sprite* gate = SpriteManagerAdd(SpriteGate, (UINT16) 64u << 3, (UINT16) 12u << 3);
						struct EnemyInfo* gdata = (struct EnemyInfo*)gate->custom_data;
						gdata->vx = 4;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 63u << 3 && spawning_counter == 6){
						spawn_item6(scrigno_coin, 73u, 11u, 1, 1); //1coin 2hp 3up 7dcoin
						spawn_enemy6(SpritePenguin, 73u, 11u);
						spawning_counter++;				
					}
					if(scroll_target->x > (UINT16) 70u << 3 && spawning_counter == 7){
						spawn_enemy6(SpriteStalattite, 77u, 5u);
						spawn_enemy6(SpritePenguin, 83u, 11u);
						spawning_counter++;
					}		
					if(scroll_target->x > (UINT16) 70u << 3 && scroll_target->x < (UINT16) 90u << 3){
						if(thunder_delay == 0u){
							spawn_enemy6(SpriteStalagmite, 80u, 8u);
						}
					}
					if(scroll_target->x > (UINT16) 112u << 3 && spawning_counter == 8){
						spawn_item6(scrigno_dcoin, 120u, 3u, 3, 1);//1coin 2hp 3up 7dcoin
						spawn_item6(scrigno_coin, 127u, 12u, 1, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 138u << 3 && spawning_counter == 9){
						spawn_enemy6(SpritePenguin, 134u, 12u);
						spawn_item6(scrigno_up, 142u, 8u, 3, 0);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpritePenguin, 148u, 12u);
						spawning_counter++;
					}					
					if(scroll_target->x > (UINT16) 166u << 3){
						if(thunder_delay == 0u){
							SpriteManagerAdd(SpriteStalagmite, (UINT16) 174u << 3, (UINT16) 6u << 3);
						}
					}
					if(scroll_target->x > (UINT16) 155u << 3 && spawning_counter == 10){
						spawn_enemy6(SpritePenguin, 160u, 10u);
						spawn_enemy6(SpritePenguin, 164u, 14u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 168u << 3 && spawning_counter == 11){
						spawn_item6(scrigno_dcoin, 176u, 6u, 7, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
				break;
				case 1u:
					if (scroll_target->x > (UINT16) 20u << 3 && spawning_counter == 0){
						spawn_enemy6(SpriteIceplat, 33u, 15u);
						spawn_enemy6(SpriteIceplat, 38u, 13u);
						spawn_enemy6(SpritePlatform, 45u, 10u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 45u << 3 && spawning_counter == 1){
						spawn_enemy6(SpriteIceplat, 50u, 13u);
						spawn_enemy6(SpriteIceplat, 55u, 15u);
						spawn_enemy6(SpritePlatform, 61u, 14u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 70u << 3 && spawning_counter == 2){
						spawn_enemy6(SpriteStalattite, 72u, 5u);
						spawn_enemy6(SpritePenguin, 80u, 12u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 72u << 3 && spawning_counter == 3){						
						spawn_enemy6(SpriteStalattite, 77u, 5u);
						spawn_enemy6(SpritePenguin, 84u, 12u);						
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 88u << 3 && spawning_counter == 4){
						spawn_enemy6(SpriteIceplat, 98u, 14u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 98u << 3 && spawning_counter == 5){
						spawn_enemy6(SpriteIceplat, 108u, 12u);					
						spawn_enemy6(SpriteStalattite, 108u, 5u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 125u << 3 && spawning_counter == 6){
						spawn_enemy6(SpriteIceplat, 137u, 12u);					
						spawn_enemy6(SpriteIceplat, 134u, 14u);					
						spawn_item6(scrigno_shield, 134u, 10u, 2, 1);//1coin 2hp 3up 7dcoin
						//spawn_item6(scrigno_up, 129u, 5u, 2, 0);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 151u << 3 && spawning_counter == 7){
						spawn_enemy6(SpriteIceplat, 160u, 11u);					
						spawn_enemy6(SpriteIceplat, 162u, 13u);					
						//spawn_enemy6(SpriteStalattite, 155u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 170u << 3 && spawning_counter == 8){
						spawn_enemy6(SpriteIceplat, 175u, 15u);					
						spawn_enemy6(SpriteIceplat, 179u, 12u);				
						spawn_enemy6(SpriteStalattite, 171u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 190u << 3 && spawning_counter == 9){
						spawn_enemy6(SpriteIceplat, 197u, 8u);
						spawn_enemy6(SpriteIceplat, 199u, 9u);						
						spawn_item6(scrigno_shield, 194u, 5u, 2, 1);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpriteIceplat, 201u, 10u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 213u << 3 && spawning_counter == 10){
						spawn_enemy6(SpritePenguin, 221u, 12u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 222u << 3 && spawning_counter == 11){
						spawn_enemy6(SpritePenguin, 229u, 12u);
						spawn_item6(scrigno_shield, 229u, 11u, 7, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}						
					if (scroll_target->x > (UINT16) 207u << 3 && scroll_target->x < (UINT16) 222u << 3){							
						switch(thunder_delay){
							case 40u:
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) + 6u, 5u);
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) + 1u, 5u);
							break;
							case 80u:
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) + 4u, 5u);
							break;
							case 20u:
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3), 5u);
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) - 1u, 5u);
							break;
						}
					}
				break;
			}
		break;
		case 6u: // Cematery
			switch(current_map){
				case 0u:
					if(scroll_target->x > (UINT16) 6u << 3 && spawning_counter == 0){
						spawn_item6(scrigno_up, 13u, 16u, 7, 1);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpriteBat, 16u, 13u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 11u << 3 && spawning_counter == 1){
						spawn_enemy6(SpriteBat, 18u, 17u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 29u << 3 && spawning_counter == 2){
						spawn_enemy6(SpriteAxethrower, 40u, 15u);
						spawn_enemy6(SpriteBat, 36u, 14u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 44u << 3 && spawning_counter == 3){
						spawn_item6(scrigno_up, 50u, 16u, 2, 1);//1coin 2hp 3up 7dcoin
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 52u << 3 && spawning_counter == 4){
						spawn_enemy6(SpriteBat, 61u, 15u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 56u << 3 && spawning_counter == 5){
						spawn_enemy6(SpriteBat, 63u, 16u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 74u << 3 && scroll_target->x < (UINT16) 80u << 3 && amulet_spawn == 0 
						&& ((quiver & 0b00010000) == 0b00000000)){
						Sprite* reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 61u << 3, (UINT16) 25u << 3);
						struct AmuletInfo* datak = (struct AmuletInfo*)reward->custom_data;
						datak->type = 4;
						datak->setup = 0;
						amulet_spawn = 1;
					}
					if(scroll_target->x > (UINT16) 85u << 3 && spawning_counter == 6){
						spawn_enemy6(SpriteAxethrower, 92u, 21u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 89u << 3 && spawning_counter == 7){
						spawn_enemy6(SpriteAxethrower, 95u, 21u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 106u << 3 && spawning_counter == 8){
						spawn_enemy6(SpriteBat, 111u, 20u);
						spawn_enemy6(SpriteBat, 104u, 20u);
						amulet_spawn = 0;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 117u << 3 && spawning_counter == 9){
						spawn_enemy6(SpriteBat, 120u, 20u);
						amulet_spawn = 0;
						spawning_counter++;
					}
				break;
				case 1u:
					if(scroll_target->x > (UINT16) 6u << 3 && spawning_counter == 0){
						spawn_enemy6(SpriteBat, 15u, 22u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 12u << 3 && spawning_counter == 1){
						spawn_falci(19u, 25u);
						spawning_counter++;						
					}
					if(scroll_target->x > (UINT16) 20u << 3 && spawning_counter == 2){
						spawn_item6(scrigno_up, 18u, 23u, 2, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 35u << 3 && spawning_counter == 3){
						spawn_enemy6(SpriteAxethrower, 45u, 23u);
						spawn_item6(scrigno_coin, 25u, 23u, 7, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 48u << 3 && spawning_counter == 4){
						spawn_falci(59u, 25u);
						spawn_enemy6(SpriteBat, 63u, 23u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 84u << 3 && spawning_counter == 5){
						spawn_enemy6(SpriteCathead, 92u, 20u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 86u << 3 && spawning_counter == 6){
						spawn_enemy6(SpriteCathead, 94u, 20u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 88u << 3 && spawning_counter == 7){
						spawn_enemy6(SpriteCathead, 96u, 21u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 92u << 3 && spawning_counter == 8){
						spawn_enemy6(SpriteAxethrower, 107u, 23u);
						spawn_enemy6(SpriteBat, 100u, 23u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 108u << 3 && spawning_counter == 9){
						spawn_falci(120u, 25u);
						spawn_item6(scrigno_coin, 111u, 24u, 1, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 119u << 3 && spawning_counter == 10){
						spawn_enemy6(SpriteCathead, 131u, 21u);
						spawn_enemy6(SpriteCathead, 129u, 25u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 125u << 3 && spawning_counter == 11){
						spawn_item6(scrigno_coin, 136u, 30u, 7, 1);//1coin 2hp 3up 7dcoin
						spawn_item6(scrigno_coin, 141u, 30u, 7, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 141u << 3 && spawning_counter == 12){
						spawn_falci(154u, 25u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 151u << 3 && spawning_counter == 13){
						spawn_enemy6(SpriteBat, 160u, 21u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 153u << 3 && spawning_counter == 14){
						spawn_enemy6(SpriteBat, 161u, 23u);
						spawning_counter++;
					}
				break;/*
				case 2u:
					if(scroll_target->x > (UINT16) 43u << 3 && spawning_counter == 0){
						spawn_enemy6(SpriteMother, 56u, 18u);
						spawning_counter++;
					}
				break;*/
			}
		break;
	}
	
	if(thunder_delay == 0u){
		thunder_delay = 104u;
	}	
	
	//DIAG MANAGEMENT
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow6();
		return;
	}	
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag6();
			return;
		}
	}

	//HUD MANAGEMENT
	if (update_hud != 0){
		update_hud = 0;
		UpdateHUD6();
	}
}

void spawn_falci(UINT16 x, UINT16 y){
	Sprite* sfalce1 = SpriteManagerAdd(SpriteFalce, (UINT16) x << 3, (UINT16) y << 3);
	struct EnemyInfo * sfalcedata = (struct EnemyInfo*)sfalce1->custom_data;
	sfalcedata->wait = 20u;
	Sprite* sfalce2 = SpriteManagerAdd(SpriteFalce, (UINT16) (x+1u) << 3, (UINT16) y << 3);
	Sprite* sfalce3 = SpriteManagerAdd(SpriteFalce, (UINT16) (x+2u) << 3, (UINT16) y << 3);
	Sprite* falcebase = SpriteManagerAdd(SpriteFalcebase, (UINT16) x << 3, (UINT16) (y+1u) << 3);
	Sprite* falcebase2 = SpriteManagerAdd(SpriteFalcebase, (UINT16) (x+1u) << 3, (UINT16) (y+1) << 3);
	Sprite* falcebase3 = SpriteManagerAdd(SpriteFalcebase, (UINT16) (x+2u) << 3, (UINT16) (y+1) << 3);				
	struct EnemyInfo * sfalce2data = (struct EnemyInfo*)sfalce2->custom_data;
	sfalce2data->wait = 10u;
	struct FalcebaseInfo* falcebasedata = (struct FalcebaseInfo*)falcebase->custom_data;
	falcebasedata->falcelama = sfalce1;
	falcebasedata->enemy_state = ENEMY_STATE_SLIDING;
	struct FalcebaseInfo* falcebasedata2 = (struct FalcebaseInfo*)falcebase2->custom_data;
	falcebasedata2->falcelama = sfalce2;
	falcebasedata2->enemy_state = ENEMY_STATE_SLIDING;
	struct FalcebaseInfo* falcebasedata3 = (struct FalcebaseInfo*)falcebase3->custom_data;
	falcebasedata3->falcelama = sfalce3;
	falcebasedata3->enemy_state = ENEMY_STATE_SLIDING;
}

void UpdateHUD6(){
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

void ShowWindow6(){	
	set_window_y6(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, BANK(window6), &window6);
	SHOW_WIN;	
	UpdateHUD6();
}

void ShowWindowDiag6(){
	if (showing_diag == 0){
		HIDE_WIN;
		set_window_y6(144 - 32);
		WX_REG = 1;
		WY_REG = 144 - 32; //40
		InitWindow(0, 0, BANK(diagnew6), &diagnew6);
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


void set_window_y6(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}

void spawn_enemy6(UINT8 spriteType, UINT16 posx, UINT16 posy){
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

void spawn_item6(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
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
