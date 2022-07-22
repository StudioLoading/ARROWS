#include "Banks/SetAutoBank.h"

#include "SGB.h"
#include "Palette.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Music.h"

#include "custom_datas.h"
#include "TilesAnimations0.h"
#include "Dialogs.h"
#include "sgb_palette.h"

IMPORT_TILES(font);
IMPORT_TILES(tiles7);

IMPORT_MAP(map80);
//IMPORT_MAP(map71);
//IMPORT_MAP(mapcutscene0);

IMPORT_MAP(diagnew7);
IMPORT_MAP(window7);
IMPORT_MAP(finalborder);

DECLARE_MUSIC(bgm_level_cematery);

const UINT8 const collision_tiles7[] = {7, 8, 11, 13, 16, 17, 18, 20, 22, 25, 26,
 30, 31, 35, 40, 41, 42, 46, 51, 52, 53, 
 64, 69, 80, 81, 82, 83, 84, 85, 86, 87, 89, 90, 111, 119, 0};//numero delle tile di collisione seguito da zero finale

UINT8 bank_tiles7 = BANK(tiles7);

extern UINT16 sprites_palette[];
extern UINT8 amulet;
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
extern Sprite* archer_player;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern INT8 spawning_counter;
extern UINT8 updatecounter;
extern INT8 update_hud;
extern INT8 fx_cooldown;
extern UINT8 thunder_delay;
extern UINT16 apx;
extern UINT16 apy;
extern UINT16 apx_mirrored;
extern INT8 platform_vx;
extern INT8 platform_vy;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;
extern UINT8 quiver;

void UpdateHUD7() BANKED;
void ShowWindow7() BANKED;
void ShowWindowDiag7() BANKED;
void set_window_y7(UBYTE y);

INT8 final_border_set = 1;


void START() {
	if(final_border_set){
		LOAD_SGB_BORDER(finalborder);
		final_border_set = 0;
	}
	
	current_camera_state = 0u;
	current_camera_counter = 0u;
	fx_cooldown = 0;
	
	//INIT SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0xFF; //Max volume 0x77


	//LOAD SPRITES OF THE MAP
	switch (current_level){
		case 7u:
			if(sgb_check()){
				set_sgb_palette01_CASTLE();
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

	const struct MapInfo* const level_7[] = { &map80, &map80};
	//const struct MapInfo* const level_8[] = {};

	const struct MapInfo** const levels78[] = {level_7};//, level_8};

	UINT8 level_7_banks[] = {BANK(map80), BANK(map80)};
	//UINT8 level_8_banks[] = {};
	UINT8 * levels78_banks[] = {level_7_banks};//, level_8_banks};

	const struct MapInfo** maps78 = levels78[current_level-7];
	UINT8* map78banks = levels78_banks[current_level-7];
	UINT8 map_w7 = 0;
	UINT8 map_h7 = 0;
	GetMapSize((UINT8) map78banks[current_map], maps78[current_map], &map_w7, &map_h7);

	if (load_next_s == -1){ //COME FROM STATE SECRET
		ResumeMusic;
		ScrollFindTile((UINT8) map78banks[current_map], maps78[current_map], 45, 0, 0, 
			map_w7, map_h7, &drop_player_x, &drop_player_y);
	}else if(load_next || load_next_d == 0 || load_next_gameover){
		spawning_counter = 0;
		switch(current_level){
			case 7u:
				PlayMusic(bgm_level_cematery, 1);
			break;
            case 8u:
            break;
		}		
		ScrollFindTile((UINT8) map78banks[current_map], maps78[current_map], 9, 0, 0, 
			map_w7, map_h7, &drop_player_x, &drop_player_y);		
	}//else COME FROM THE DIALOG STATE, I ALREADY SAVED PLAYER COORDS IN drop_player_x/y
	else{
		ResumeMusic;
	}
	if(current_level == 7u && current_map == 0){
		archer_player = SpriteManagerAdd(SpriteMother, drop_player_x << 3, drop_player_y << 3);
	}else{
		archer_player = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	}
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, archer_player->x , archer_player->y);
	InitScroll((UINT8) map78banks[current_map], maps78[current_map], collision_tiles7, 0);
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
	ShowWindow7();
	
	//INIT ENEMIES	
	enemies_0 = 0;
	enemies_1 = 0;
	enemies_2 = 0;
	enemies_3 = 0;
	
	//INIT SPAWNING	
	if (load_next_s > -1 && load_next_d == 0){ // NON vengo da secret nè da dialogo!
		switch(current_level){
			case 7u:
				switch(current_map){
					case 0u:
						quiver = 0b00000001;
						//spawn_item6(scrigno_dcoin, 3u, 16u, 7, 1);//1coin 2hp 3up 7dcoin
						//spawn_item6(scrigno_dcoin, 15u, 10u, 2, 0);//1coin 2hp 3up 7dcoin
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

void UPDATE(){
	//camerafocus shifting management
	if(archer_player && archer_state != STATE_HIT && archer_state != STATE_DEAD){
		if(archer_player->x < 32u){
			scroll_target->x = 32u;
		}else{
			apx = archer_player->x + 24;
			apy = archer_player->y - 8;
			if(archer_state == STATE_ASCENDING){
				apy -= 4;
				apy += platform_vy;
			}
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
	
	thunder_delay -= 1u;
	
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
			case 7u:
				SetState(StateGame7);
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
		case 7u: // Castle
			switch(current_map){
				case 0u:
					if(spawning_counter == 0 && archer_player->y < (UINT16) 856u){
						enemies_0 = SpriteManagerAdd(SpriteCagedboss, (UINT16) 4 << 3, (UINT16) 103 << 3);
						enemies_0->attr_add = 0b10000000;
						struct CagedbossInfo* wolfcaged_data = (struct CagedbossInfo*)enemies_0->custom_data;
						wolfcaged_data->state = WOLF_CAGED;
						wolfcaged_data->setup = 1;
						spawning_counter = 1;
					}
					if(spawning_counter == 1 && archer_player->y < (UINT16) 560u){
						enemies_1 = SpriteManagerAdd(SpriteCagedboss, (UINT16) 26 << 3, (UINT16) 64 << 3);
						enemies_1->attr_add = 0b10000000;
						enemies_1->mirror = V_MIRROR;
						struct CagedbossInfo* ibexcaged_data = (struct CagedbossInfo*)enemies_1->custom_data;
						ibexcaged_data->state = IBEX_CAGED;
						ibexcaged_data->setup = 1;
						spawning_counter = 2;
					}
					if(spawning_counter == 2 && archer_player->y < (UINT16) 400u){
						enemies_2 = SpriteManagerAdd(SpriteCagedboss, (UINT16) 22 << 3, (UINT16) 40 << 3);
						enemies_2->attr_add = 0b10000000;
						struct CagedbossInfo* ibexcaged_data = (struct CagedbossInfo*)enemies_2->custom_data;
						ibexcaged_data->state = BEAR_CAGED;
						ibexcaged_data->setup = 1;
						spawning_counter = 3;
					}
					if(spawning_counter == 3 && archer_player->y < (UINT16) 160u){
						enemies_3 = SpriteManagerAdd(SpriteCagedboss, (UINT16) 13 << 3, (UINT16) 11 << 3);
						//enemies_1->attr_add = 0b10000000;
						struct CagedbossInfo* finalboss_data = (struct CagedbossInfo*)enemies_3->custom_data;
						finalboss_data->state = BOSS_IDLE;
						finalboss_data->setup = 1;
						spawning_counter = 4;
					}
					if(spawning_counter == 4 && archer_player->y < (UINT16) 112u){
						diag_found = Build_Next_Dialog_Banked(enemies_3);
						SetState(StateDiag);
					}
	            break;
	        }
        break;
    }
	
	if(thunder_delay == 0u){
		thunder_delay = 120u;
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
		ShowWindow7();
		return;
	}	
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag7();
			return;
		}
	}

	//HUD MANAGEMENT
	if (update_hud != 0){
		update_hud = 0;
		UpdateHUD7();
	}
}

void UpdateHUD7() BANKED{
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

void ShowWindow7() BANKED{	
	set_window_y7(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, BANK(window7), &window7);
	SHOW_WIN;	
	UpdateHUD7();
}

void ShowWindowDiag7() BANKED{
	if (showing_diag == 0){
		HIDE_WIN;
		set_window_y7(144 - 32);
		WX_REG = 1;
		WY_REG = 144 - 32; //40
		InitWindow(0, 0, BANK(diagnew7), &diagnew7);
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

void set_window_y7(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}

void spawn_enemy7(UINT8 spriteType, UINT16 posx, UINT16 posy){
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

void spawn_item7(Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
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
