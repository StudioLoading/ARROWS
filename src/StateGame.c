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
IMPORT_TILES(tiles);
IMPORT_TILES(tiles4);
IMPORT_TILES(tilesanims);
IMPORT_TILES(tilesanimsmapworld);

IMPORT_MAP(map);
IMPORT_MAP(map2);
IMPORT_MAP(mapsewer);
IMPORT_MAP(mapsewer2);
IMPORT_MAP(map3);
IMPORT_MAP(map3tree);

IMPORT_MAP(diagnew);
IMPORT_MAP(window);

DECLARE_MUSIC(bgm_level_zoo);
DECLARE_MUSIC(bgm_level_sewer);
DECLARE_MUSIC(bgm_level_forest);

extern struct ArcherInfo* archer_data;
extern ARCHER_STATE archer_state;
extern INT8 is_on_boss;
extern INT8 is_on_secret;
extern INT8 is_on_gameover;
extern UINT8 current_level_b;
extern UINT8 current_map_b;
extern INT8 platform_vx;
extern UINT8 current_camera_state;
extern UINT8 current_camera_counter;
extern UINT8 diag_found;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

const UINT8 const collision_tiles[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 74, 75, 76, 77, 81, 85, 86, 89, 90, 91, 92, 104, 111, 119, 0};//numero delle tile con zero finale

//initialized on StateTitlescreen
extern UINT8 amulet;
extern UINT8 coins;
extern INT8 ups;
extern INT8 hp;
extern INT8 archer_tool;
extern INT8 level_tool;
extern INT8 load_next_d;
extern INT8 load_next_b;
extern UINT8 updatecounter; //da StateCredit
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern INT8 platform_vx;

INT8 load_next = 0;
INT8 load_next_s = 0;
INT8 load_next_d = 0;
INT8 load_next_b = 0; // 0 default, 1 se voglio testare il boss stage, in coerenza col current_level_b
UINT8 current_level_b = 0u; //0 default/wolf, 1 gator, 2 eagle, 3 ibex, 4 bear, 5 walrus
INT8 load_next_gameover = 0;
UINT8 current_level = 6u; // 0u default, 1 sewer, 2 forest, 3 sky, 4 trees, 5 ice cavern, 6 cematery, 7 castle
UINT8 current_map = 2u; // 0u default
UINT8 current_cutscene = 0u;

UINT16 drop_player_x = 0u;
UINT16 drop_player_y = 0u;
INT8 show_diag = 0;
INT8 showing_diag = 0;
INT8 spawning_triggered = 0;
INT8 spawning_counter = 0;
INT8 update_hud = 0;
INT8 LCD_Installed = 0;
INT8 fx_cooldown = 0;

UINT8 paused = 0;
UINT16 apx = 0;
UINT16 apy = 0;
UINT16 apx_mirrored = 0;

Sprite* platform_sprite = 0;
Sprite* enemies_0 = 0;
Sprite* enemies_1 = 0 ;
Sprite* enemies_2 = 0 ;
Sprite* enemies_3 = 0 ;
Sprite* scrigno_coin = 0;
Sprite* scrigno_dcoin = 0;
Sprite* scrigno_shield = 0;
Sprite* scrigno_up = 0;
Sprite* archer_player = 0;

void UpdateHUD() BANKED;
void ShowWindow() BANKED;
void ShowWindowDiag() BANKED;
void set_window_y(UBYTE y);
void spawn_enemy(UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED;
void spawn_item(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno) BANKED;


void START() {
	
	current_camera_state = 0u;
	current_camera_counter = 0u;
	fx_cooldown = 0;

	switch(current_level){
		case 3u:
		case 4u:
			SetState(StateGame3);
		break;
		case 5u:
		case 6u:
			SetState(StateGame6);
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
	SpriteManagerLoad(SpritePuff);
	SpriteManagerLoad(SpriteCamerafocus);
	//LOAD THE SPRITES FOR THE MAP and plays the bgm	
	switch (current_level){
		case 0u:
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteScorpion);
			if(sgb_check()){
				set_sgb_palette01_ZOO();
				set_sgb_palette_statusbar();
			}
			PlayMusic(bgm_level_zoo, 1);
		break;
		case 1u:
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteRat);
			SpriteManagerLoad(SpriteSpider);
			SpriteManagerLoad(SpriteGate);
			if(sgb_check()){
				set_sgb_palette01_SEWER();
				set_sgb_palette_statusbar();
			}
			PlayMusic(bgm_level_sewer, 1);
		break;
		case 2u:
			SpriteManagerLoad(SpriteSpider);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteBird);
			if(sgb_check()){
				set_sgb_palette01_FOREST();
				set_sgb_palette_statusbar();
			}			
			PlayMusic(bgm_level_forest, 1);
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
	if (current_level == 2u && current_map == 0u){
		scroll_bottom_movement_limit = 82u;
	}
	
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

	UINT8 level_1_banks[] = {BANK(map), BANK(map2)};
	UINT8 level_2_banks[] = {BANK(mapsewer2), BANK(mapsewer)};
	UINT8 level_3_banks[] = {BANK(map3), BANK(map3tree)};
	UINT8 * levels_banks[] = {level_1_banks, level_2_banks, level_3_banks};

	const struct MapInfo** maps = levels[current_level];
	UINT8* mapbanks = levels_banks[current_level];
	UINT8 map_w = 0;
	UINT8 map_h = 0;
	GetMapSize((UINT8) mapbanks[current_map], maps[current_map], &map_w, &map_h);
	if (load_next_s == -1){ //COME FROM STATE SECRET
		ResumeMusic;
		ScrollFindTile((UINT8) mapbanks[current_map], maps[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else if(load_next || load_next_d == 0 || load_next_gameover){
		spawning_counter = 0;
		//PlayMusic(bgm_level_emptych1, 1);
		ScrollFindTile((UINT8) mapbanks[current_map], maps[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);		
	}//else COME FROM THE DIALOG STATE, I ALREADY SAVED PLAYER COORDS IN drop_player_x/y
	else{
		ResumeMusic;
	}
	archer_player = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, archer_player->x , archer_player->y);
	InitScroll((UINT8) mapbanks[current_map], maps[current_map], collision_tiles, 0);
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
	ShowWindow();
	
	//SET LEVEL TOOL
	switch(current_level){
		case 0u:
			level_tool = 6;
		break;
		case 1u:
			switch(current_map){
				case 1u:
					level_tool = 7;
				break;
			}
		break;
	}
	
	//INIT ENEMIES	
	enemies_0 = 0;
	enemies_1 = 0;
	enemies_2 = 0;
	enemies_3 = 0;

	if(load_next_s == -1){
		load_next_s = 0;
	}else if (load_next_d == 0){//copiato dallo SpritePlayer quando chiedo il tip
		diag_found = Build_Next_Dialog_Banked(archer_player);
		if(diag_found){
			//archer_state = STATE_DIAG;
			//show_diag = 1;	
		}
	}
	load_next_d = 0;	

}

void ShowWindow() BANKED{
	set_window_y(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, BANK(window), &window);
	SHOW_WIN;
	
	UpdateHUD();
	
}

void ShowWindowDiag() BANKED{
	if (showing_diag == 0){
		reset_sgb_palette_statusbar();
		HIDE_WIN;
		set_window_y(144 - 32);
		WX_REG = 0;
		WY_REG = 144 - 32; //40
		InitWindow(0, 0, BANK(diagnew), &diagnew);
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

void spawn_enemy(UINT8 spriteType, UINT16 posx, UINT16 posy) BANKED{
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

void spawn_item(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno) BANKED{
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
	//camerafocus shifting management
	if(archer_player && archer_state != STATE_HIT && archer_state != STATE_DEAD){
		if(archer_player->x < 32u){
			scroll_target->x = 32u;
		}else{
			apx = archer_player->x + 24;
			apy = archer_player->y - 8;
			apx_mirrored = archer_player->x - 24;
			scroll_target->y = apy;
			INT8 dx = platform_vx;
			if(archer_player->mirror == V_MIRROR){
				if(scroll_target->x > apx_mirrored){
					dx -= 1;
				}
				if(scroll_target->x < apx_mirrored){
					dx += 1;
				}
			}else{
				if(scroll_target->x < apx){
					dx += 1;
				}
				if(scroll_target->x > apx){
					dx -= 1;
				}
			}
			scroll_target->x += dx;
		}
	}

	if(load_next_d){
		switch(load_next_d){
			case 1: //vado allo StateDiag
				diag_found = Build_Next_Dialog_Banked(archer_player);
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
				SetState(StateGame6);
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

	//SPAWNING
	switch(current_level){
		case 0u:
			switch(current_map){
				case 0u:
					if(spawning_counter == 0){
						spawn_item(scrigno_up, 1u, 9u, 3, 0);
						spawning_counter++;
					}
				break;
				case 1u:
					if (scroll_target->x >= (UINT16) 6u << 3 && spawning_counter == 0){
						spawn_enemy(SpriteEnemy, 13u, 7u);
						spawning_counter++;
					}
					if (scroll_target->x >= (UINT16) 10u << 3 && spawning_counter == 1){
						spawn_enemy(SpriteEnemy, 22u, 7u);
						spawn_enemy(SpriteEnemy, 26u, 7u);
						spawning_counter++;
					}
					if (scroll_target->x >= (UINT16) 30u << 3 && spawning_counter == 2){
						spawn_enemy(SpritePlatform, 39u, 8u);
						spawning_counter++;
					}
					if (scroll_target->x >= (UINT16) 47u << 3 && spawning_counter == 3){
						spawn_enemy(SpriteScorpion, 56u, 8u);
						spawn_enemy(SpriteEnemy, 51u, 8u);
						spawning_counter++;
					}
					if (scroll_target->x >= (UINT16) 77u << 3 && spawning_counter == 4){
						spawn_enemy(SpriteEnemy, 85u, 7u);
						spawning_counter++;
					}
					if (scroll_target->x >= (UINT16) 95u << 3 && spawning_counter == 5){
						spawn_enemy(SpriteScorpion, 107u, 8u);
						spawning_counter++;
					}
					if (scroll_target->x >= (UINT16) 146u << 3 && spawning_counter == 6){
						spawn_enemy(SpriteEnemy, 155u, 8u);
						spawning_counter++;
					}
				break;
			}
		break;
		case 1u:
			switch(current_map){
				case 0u:
					if (scroll_target->x > (UINT16) 5u << 3 && spawning_counter == 0){
						spawn_enemy(SpriteSpider, 12u, 5u);
						spawn_enemy(SpriteSpider, 14u, 6u);
						spawning_counter++;
					}						
					if (scroll_target->x > (UINT16) 13u << 3 && spawning_counter == 1){
						spawn_enemy(SpriteSpider, 21u, 4u);
						spawn_item(scrigno_up, 25u, 5u, 3, 1);
						spawn_enemy(SpritePlatform, 35u, 6u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 48u << 3 && spawning_counter == 2){
						spawn_enemy(SpriteRat, 58u, 6u);
						spawn_enemy(SpriteEnemy, 61u, 6u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 67u << 3 && spawning_counter == 3){
						if( scroll_target->y < (UINT16) 14u << 3 ){
							spawn_enemy(SpriteRat, 81u, 3u);
							spawn_enemy(SpriteEnemy, 88u, 3u);
							spawn_enemy(SpriteSpider, 85u, 5u);
							spawn_item(scrigno_dcoin, 85u, 5u, 7, 1);
						}
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 88u << 3 && spawning_counter == 4){
						if(scroll_target->y > (UINT16) 14u << 3){
							spawn_item(scrigno_shield, 93u, 18u, 2, 1);
						}
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 97u << 3 && spawning_counter == 5){
						if(scroll_target->y < (UINT16) 7u << 3 ){
							spawn_enemy(SpriteSpider, 101u, 3u);
							spawn_enemy(SpriteSpider, 105u, 3u);
							spawn_enemy(SpriteSpider, 111u, 3u);
						}
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 180u << 3 && spawning_counter == 6){
						spawn_item(scrigno_dcoin, 192u, 7u, 7, 1);
						Sprite* gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 193u << 3, (UINT16) 18u << 3);
						struct EnemyInfo* gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
						gatedata->vx = 2;
						Sprite* gate_sprite2 = SpriteManagerAdd(SpriteGate, (UINT16) 192u << 3, (UINT16) 18u << 3);
						struct EnemyInfo* gatedata2 = (struct EnemyInfo*)gate_sprite2->custom_data;
						gatedata2->vx = 2;
						spawning_counter++;
					}	
				break;
				case 1u:
					if (scroll_target->x > (UINT16) 9u << 3 && spawning_counter == 0){
						spawn_enemy(SpriteRat, 16u, 4u);
						spawn_enemy(SpriteEnemy, 17u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 29u << 3 && spawning_counter == 1){
						spawn_item(scrigno_dcoin, 36u, 3u, 1, 1);
						spawn_enemy(SpriteRat, 42u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 38u << 3 && spawning_counter == 2){
						spawn_enemy(SpriteSpider, 50u, 7u);
						spawn_enemy(SpriteRat, 34u, 6u);
						spawn_enemy(SpriteEnemy, 52u, 6u);
						spawn_item(scrigno_shield, 41u, 3u, 2, 1);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 51u << 3 && spawning_counter == 3){
						spawn_enemy(SpritePlatform, 63u, 8u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 89u << 3 && spawning_counter == 4){
						spawn_enemy(SpriteSpider, 94u, 5u);
						spawn_enemy(SpriteRat, 100u, 6u);
						spawn_enemy(SpriteEnemy, 102u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 136u << 3 && spawning_counter == 5){
						spawn_enemy(SpriteSpider, 149u, 5u);
						spawn_enemy(SpriteSpider, 150u, 5u);
						spawn_enemy(SpriteRat, 143u, 13u);
						spawn_enemy(SpriteEnemy, 142u, 14u);
						spawn_enemy(SpriteEnemy, 141u, 14u);
						spawning_counter++;
					}					
				break;
			}
		break;
		case 2u:
			switch(current_map){
				case 0u:
					if (scroll_target->x > (UINT16) 7u << 3 && spawning_counter == 0){
						spawn_item(scrigno_dcoin, 3u, 1u, 7, 1);
						spawn_enemy(SpriteSpider, 13u, 9u);
						spawn_enemy(SpriteSpider, 19u, 9u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 37u << 3 && spawning_counter == 1){
						spawn_item(scrigno_up, 46u, 0u, 3, 1);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 43u << 3 && spawning_counter == 2){
						spawn_enemy(SpriteSpider, 51u, 9u);
						spawn_enemy(SpriteEnemy, 56u, 9u);
						spawn_enemy(SpriteEnemy, 66u, 9u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 84u << 3 && spawning_counter == 3){
						spawn_enemy(SpriteBird, 90u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 104u << 3 && spawning_counter == 4){
						spawn_enemy(SpriteEnemy, 115u, 10u);
						spawn_enemy(SpriteBird, 90u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 119u << 3 && spawning_counter == 5){
						spawn_enemy(SpritePlatform, 131u, 10u);
						spawn_enemy(SpriteBird, 140u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 143u << 3 && spawning_counter == 6){
						spawn_enemy(SpriteBird, 155u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 150u << 3 && spawning_counter == 7){
						spawn_enemy(SpriteEnemy, 165u, 9u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 151u << 3 && spawning_counter == 8){
						spawn_enemy(SpriteBird, 140u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 163u << 3 && spawning_counter == 9){
						spawn_enemy(SpriteBird, 160u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 167u << 3 && spawning_counter == 10){
						spawn_enemy(SpriteBird, 178u, 3u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 170u << 3 && spawning_counter == 11){
						spawn_item(scrigno_shield, 183u, 6u, 2, 1);
						spawning_counter++;
					}
				break;
				case 1:
					if (scroll_target->x > (UINT16) 8u << 3 && spawning_counter == 0){
						spawn_enemy(SpriteSpider, 16u, 9u);
						spawn_enemy(SpriteSpider, 17u, 9u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 123u << 3 && spawning_counter == 1){
						spawn_enemy(SpriteBird, 135u, 5u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 128u << 3 && spawning_counter == 2){
						spawn_enemy(SpriteBird, 116u, 5u);
						spawn_enemy(SpriteSpider, 135u, 10u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 141u << 3 && spawning_counter == 3){
						spawn_enemy(SpriteBird, 130u, 5u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 152u << 3 && spawning_counter == 4){
						spawn_enemy(SpriteBird, 165u, 5u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 163u << 3 && spawning_counter == 5){
						spawn_enemy(SpriteBird, 175u, 5u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 168u << 3 && spawning_counter == 6){
						spawn_enemy(SpriteBird, 182u, 5u);
						spawning_counter++;
					}		
				break;
			}
		break;
	}
	
	//MOVING BACKGROUND TILES	
	updatecounter++;
	if (updatecounter < 20) {
		switch(updatecounter){
			case 1:
				Anim_Tiles_0();
			break;
			case 10:
				Anim_Tiles_1();
			break;
		}			
	}else{
		updatecounter = 0;
	}	
	
	//DIAG MANAGEMENT
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
	
	//HUD MANAGEMENT
	if (update_hud){
		update_hud = 0;
		UpdateHUD();
	}
	
}

void UpdateHUD() BANKED{
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
	if(hp<0)hp=0;
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

void set_window_y(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) {SHOW_WIN;} else { HIDE_WIN; LYC_REG = 160u; } 
}
