#include "Banks/SetAutoBank.h"

#include "BankManager.h"
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
IMPORT_TILES(diagnew);

IMPORT_MAP(mapboss0);
IMPORT_MAP(mapboss1);
IMPORT_MAP(mapboss2);
IMPORT_MAP(mapboss3);
IMPORT_MAP(mapboss4);
IMPORT_MAP(mapboss5);
IMPORT_MAP(mapboss9);

DECLARE_MUSIC(bgm_boss_defeated);

extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next_b;
extern INT8 level_tool;
extern UINT16 drop_player_x ;
extern UINT16 drop_player_y ;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern INT8 show_diag;
extern INT8 showing_diag;
extern INT8 is_on_boss;
extern INT8 is_on_gameover;
extern UINT8 updatecounter;
extern UINT8 current_camera_state; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
extern UINT8 current_camera_counter;
extern UINT8 diag_found;
extern INT8 load_next_d;
extern INT8 load_next_gameover;
extern INT8 update_hud;

extern const INT8 MAX_HP;
extern const INT8 MAX_FINALBOSS_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

extern void ShowWindow() BANKED;
extern void ShowWindowDiag() BANKED ;
extern void UpdateHUD() BANKED;

//Boss
extern UINT8 current_level_b;

const struct MapInfo* const boss_0[] = {
	&mapboss0
};
const struct MapInfo* const boss_1[] = {
	&mapboss1
};
const struct MapInfo* const boss_2[] = {
	&mapboss2
};
const struct MapInfo* const boss_3[] = {
	&mapboss3
};
const struct MapInfo* const boss_4[] = {
	&mapboss4
};
const struct MapInfo* const boss_5[] = {
	&mapboss5
};
const struct MapInfo* const boss_9[] = {
	&mapboss9
};
//const struct MapInfo** const bosses[] = {boss_0, boss_1, boss_2, boss_3, boss_4, boss_5};
const struct MapInfo* const bosses[] = {&mapboss0, &mapboss1, &mapboss2, &mapboss3, &mapboss4, &mapboss5, 0, 0, 0, &mapboss9};

 Sprite* boss;
INT8 boss_hp = 0;
struct EnemyInfo* boss_data_b;
Sprite* reward = 0;
Sprite* reward_wrench = 0;
Sprite* reward_wrench2 = 0;
Sprite* reward_key = 0;

const UINT8 const collision_btiles[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 74, 75, 76, 77, 81, 85, 86, 89, 90, 91, 92, 104, 111, 119, 0};//numero delle tile con zero finale

const UINT8 const collision_btiles4[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 68, 69, 70, 71, 73, 74, 75, 81, 90, 100, 101, 102, 103, 104, 111, 119, 0};//numero delle tile con zero finale

const UINT8 const collision_btiles6[] = {1, 2, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 20, 26, 35, 36, 37, 38, 39, 41, 43, 44, 61, 62, 64, 111, 119, 0};//numero delle tile di collisione seguito da zero finale

const UINT8 const collision_btiles7[] = {7, 8, 11, 13, 16, 17, 18, 20, 22, 25, 26, 30, 31, 35, 40, 41, 42, 46, 51, 52, 53, 64, 69, 77, 78, 79, 80, 81, 82, 89, 90, 92, 111, 119, 0};//numero delle tile di collisione seguito da zero finale

void SpawnBoss(INT8 hp_default);
void SpawnReward();
void WriteBBOSSHP();

void START(){

	reward = 0;

	if(is_on_boss <= 0){
		is_on_boss = 0;
	}

	SPRITES_8x16;

	SpriteManagerLoad(SpriteCamerafocus);
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	switch(current_level_b){
		case 0u:
			level_tool=7;
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteWolf);
			if(sgb_check()){
				set_sgb_palette01_2H();
			}
		break;
		case 1u:
			level_tool=0;
			SpriteManagerLoad(SpriteAlligator);
			SpriteManagerLoad(SpriteAmulet);
			SpriteManagerLoad(SpriteGate);
			SpriteManagerLoad(SpriteItem);
			if(sgb_check()){
				set_sgb_palette01_GATORSWAMP();
			}
		break;
		case 2u:
			level_tool=6;
			SpriteManagerLoad(SpriteEagle);
			SpriteManagerLoad(SpriteFeather);
			SpriteManagerLoad(SpriteKey);
			if(sgb_check()){
				set_sgb_palette01_FOREST();
			}
		break;
		case 3u:
			level_tool=0;
			SpriteManagerLoad(SpriteIbex);
			SpriteManagerLoad(SpriteAmulet);
			SpriteManagerLoad(SpriteGate);
			if(sgb_check()){
				set_sgb_palette01_1B();
			}
		break;
		case 4u:
			level_tool=7;
			SpriteManagerLoad(SpriteBear);
			SpriteManagerLoad(SpriteKey);
			if(sgb_check()){
				set_sgb_palette01_TREES();
			}
		break;
		case 5u:
			level_tool=0;
			SpriteManagerLoad(SpriteWalrus);
			SpriteManagerLoad(SpriteWalrusspin);
			SpriteManagerLoad(SpriteGate);
			SpriteManagerLoad(SpriteAmulet);
			if(sgb_check()){
				set_sgb_palette01_WALRUS();
			}
		break;
		case 9u:
			level_tool=0;
			SpriteManagerLoad(SpriteBossfighter);
			SpriteManagerLoad(SpriteAlligator);
			if(sgb_check()){
				set_sgb_palette01_CASTLE();
			}
		break;
	}
	if(sgb_check()){
		set_sgb_palette_statusbar();
	}
	SHOW_SPRITES;

	//SCROLL
	const struct MapInfo* level_maps_b = bosses[current_level_b];
	UINT8 boss_banks[] = {BANK(mapboss0), BANK(mapboss1), BANK(mapboss2),BANK(mapboss3), BANK(mapboss4), BANK(mapboss5), 0, 0, 0, BANK(mapboss9)};
	UINT8 map_w = 0;
	UINT8 map_h = 0;
	GetMapSize(boss_banks[current_level_b], level_maps_b, &map_w, &map_h);
	if(current_camera_state < 3u){
		ScrollFindTile((UINT8) boss_banks[current_level_b], level_maps_b, 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
		scroll_top_movement_limit = 60;
		scroll_target = SpriteManagerAdd(SpriteCamerafocus, drop_player_x << 3, drop_player_y << 3);
	}else{
		if(is_on_boss <= 2){
			is_on_boss = 2;
			ScrollFindTile((UINT8) boss_banks[current_level_b], level_maps_b, 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
		}
		scroll_top_movement_limit = 30;
		scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
		scroll_bottom_movement_limit = 80;//customizzo altezza archer sul display
		archer_state = STATE_JUMPING;
	}
	diag_found = Build_Next_Dialog_Banked(scroll_target);
	switch (current_level_b){
		case 0u:
		case 1u:
		case 2u:
			InitScroll((UINT8) boss_banks[current_level_b], level_maps_b, collision_btiles, 0);
		break;
		case 3u:
		case 4u:
			InitScroll((UINT8) boss_banks[current_level_b], level_maps_b, collision_btiles4, 0);
		break;
		case 5u:
			InitScroll((UINT8) boss_banks[current_level_b], level_maps_b, collision_btiles6, 0);
		break;
		case 9u:
			InitScroll((UINT8) boss_banks[current_level_b], level_maps_b, collision_btiles7, 0);
		break;
	}

	SHOW_BKG;

	if (is_on_boss > 2){
		if(is_on_boss == 4){//lo setto a 4 solo quando si muore dopo aver sconfitto il boss ma prima di essere usciti, come dei coglioni
			SpawnReward();
		}
		SpawnBoss(0);
		archer_state = STATE_JUMPING;
	}else{
		SpawnBoss(-1);
	}

	//INTRO
	if (current_camera_state < 3u){
		boss_data_b->enemy_state = ENEMY_STATE_WAIT;
		return;
	}else{
		boss_data_b->enemy_state = ENEMY_STATE_NORMAL;
		if(is_on_boss > 2){
			boss_data_b->enemy_state = ENEMY_STATE_DEAD;
		}
	}

	//INIT ARCHER
	archer_data->ups = ups;
	archer_data->hp = hp;
	archer_data->coins = coins;

	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 0);
	ShowWindow();
	WriteBBOSSHP();

}

void UPDATE() {

	if(load_next_d){
		switch(load_next_d){
			case 1: //go to StateDiag
				diag_found = Build_Next_Dialog_Banked(scroll_target);
				load_next_d = 2;
				SetState(StateDiag);
			break;
			case 2:
				load_next_d = 0;
			break;
		}
	}

	if(load_next_b){
		switch(load_next_b){
			case 2: //esco dal boss col tool
				is_on_boss = -1;
				SetState(StateWorldmap);
			break;
		}
	}

	if(load_next_gameover){
		load_next_gameover = 0;
		is_on_gameover = 1;
		SetState(StateGameover);
	}

	// INTRO START
	if (current_camera_state < 3u){
		switch(current_camera_state){//0 initial wait, 1 move to boss, 2 go to Diag,
			case 0u:
				current_camera_counter += 1u;
				if(current_camera_counter == 60u){
					current_camera_counter = 0u;
					current_camera_state += 1u;
				}
			break;
			case 1u:
				if(scroll_target->y < boss->y){scroll_target->y += 1;}
				if(scroll_target->y > boss->y){scroll_target->y -= 1;}
				if(scroll_target->x < boss->x){scroll_target->x += 1;}
				if(scroll_target->x > boss->x){scroll_target->x -= 1;}
				if(scroll_target->x == boss->x && scroll_target->y == boss->y){
					is_on_boss = 1;
					current_camera_state += 1u;
				}
			break;
			case 2u:
				current_camera_counter += 1u;
				if(current_camera_counter == 40u){
					diag_found = Build_Next_Dialog_Banked(scroll_target);
					current_camera_state += 1u;
					current_camera_counter = 0u;
					SetState(StateDiag);
				}
			break;
		}
		/*PRINT_POS(10, 0);
		Printf("%d", current_camera_counter);
		PRINT_POS(13, 0);
		Printf("%d", current_camera_state);	*/
	}
	//INTRO END

	//DIAG MANAGEMENT
	if(show_diag >= 2){ // if(show_diag >= max_diag){
		ShowWindow();
		return;
	}
	if(archer_state == STATE_DIAG){
		if(show_diag >= 2){ // if(show_diag >= max_diag){
			ShowWindow();
			return;
		}
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

	if (boss_hp != boss_data_b->hp && is_on_boss < 3){
		boss_hp = boss_data_b->hp;
		WriteBBOSSHP();
		if (boss_hp <= 0){
			is_on_boss = 3;
			SpawnReward();
		}
	}
	/*
	if(level_tool && level_tool == archer_data->tool){
		UpdateHUD();
	}
	*/
	//UPDATE ARCHER POSX IN BOSS CUSTOM_DATA
	boss_data_b->archer_posx = scroll_target->x;

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

}

void SpawnBoss(INT8 hp_default){
		Sprite* gate_sprite = 0;
		struct EnemyInfo* gatedata = 0;
		switch(current_level_b){
			case 0u:
				boss = SpriteManagerAdd(SpriteWolf, (UINT16) 24u << 3, (UINT16) 15u << 3); //34, 12
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
			break;
			case 1u:
				boss = SpriteManagerAdd(SpriteAlligator, (UINT16) 29u << 3, ((UINT16) 16u << 3) - 4u);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
				gate_sprite = SpriteManagerAdd(SpriteGate, 42 << 3,  13 << 3);
				gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
				gatedata->vx = 2;
			break;
			case 2u:
				boss = SpriteManagerAdd(SpriteEagle, (UINT16) 28u << 3, (UINT16) 14u << 3);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
			break;
			case 3u:
				boss = SpriteManagerAdd(SpriteIbex, (UINT16) 24u << 3, ((UINT16) 14u << 3) - 4u);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
				gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 40u << 3,  (UINT16) 13u << 3);
				gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
				gatedata->vx = 3;
			break;
			case 4u:
				boss = SpriteManagerAdd(SpriteBear, (UINT16) 20u << 3, ((UINT16) 13u << 3) +4u);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
			break;
			case 5u:
				boss = SpriteManagerAdd(SpriteWalrus, (UINT16) 13u << 3, (UINT16) 15u << 3);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
				gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 34 << 3, (UINT16) 19 << 3);
				gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
				gatedata->vx = 4;
			break;
			case 9u:
				boss = SpriteManagerAdd(SpriteBossfighter, (UINT16) 22u << 3, ((UINT16) 15u << 3) + 3u);
				SpriteManagerAdd(SpriteAlligator, (UINT16) 21u << 3 , ((UINT16) 26u << 3) + 2u);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
			break;
		}

		if(hp_default == 0){
			boss_hp = 0;
		}
}

void SpawnReward(){//and move boss to position
	struct ItemInfo* datak_wrench = 0;
	struct ItemInfo* datak_wrench2 = 0;
	struct ItemInfo* datak_key = 0;
	struct AmuletInfo* data_amulet = 0;
	Sprite* key_s = 0;
	PlayMusic(bgm_boss_defeated, 1);
	switch (current_level_b){
		case 0u:// wolf -> wrench
			boss->x = (UINT16) 24u << 3;
			boss->y = (UINT16) 12u << 3;
			reward_wrench = SpriteManagerAdd(SpriteKey, (UINT16) 30u << 3, (UINT16) 10u << 3);
			datak_wrench = (struct ItemInfo*)reward_wrench->custom_data;
			datak_wrench->type = 2;
			datak_wrench->setup = 1u;
		break;
		case 1u: // gator -> amulet stone
			reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 22u << 3, (UINT16) 13u << 3);
			data_amulet = (struct AmuletInfo*)reward->custom_data;
			data_amulet->setup = 0u;
			data_amulet->type = 1;
		break;
		case 2u: // eagle -> key
			reward_key = SpriteManagerAdd(SpriteKey, (UINT16) 19u << 3, (UINT16) 14u << 3);
			datak_key = (struct ItemInfo*)reward_key->custom_data;
			datak_key->type = 1;
			datak_key->setup = 1u;
		break;
		case 3u: // ibex -> amulet thunder
			boss->x = (UINT16) 24u << 3;
			boss->y = (UINT16) 14u << 3;
			boss->mirror = V_MIRROR;
			reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 29u << 3, (UINT16) 13u << 3);
			data_amulet = (struct AmuletInfo*)reward->custom_data;
			data_amulet->type = 3;
			data_amulet->setup = 0;
		break;
		case 4u: // bear -> wrench
			reward_wrench2 = SpriteManagerAdd(SpriteKey, (UINT16) 30u << 3, (UINT16) 12u << 3);
			datak_wrench2 = (struct ItemInfo*)reward_wrench2->custom_data;
			datak_wrench2->type = 2;
			datak_wrench2->setup = 1u;
			boss->x = (UINT16) 24u << 3;
			boss->y = (UINT16) 13u << 3;
		break;
		case 5u: // tusk -> amulet water
			boss->x = (UINT16) 12u << 3;
			boss->y = (UINT16) 15u << 3;
			reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 28u << 3, (UINT16) 13u << 3);
			data_amulet = (struct AmuletInfo*)reward->custom_data;
			data_amulet->type = 2;
			data_amulet->setup = 0;
		break;
	}
}

void WriteBBOSSHP(){
	if(boss_hp<=0)boss_hp=0;
	INT8 i;
	for(i = 0; i != boss_hp; ++i) {
		set_win_tiles(11 + i, 0, 1, 1, &SKULL_TILE);
	}
	if(current_level_b < 9u){
		for(; i != MAX_HP; ++i) {
			set_win_tiles(11 + i, 0, 1, 1, &EMPTY_TILE);
		}
	}else{
		for(; i != MAX_FINALBOSS_HP; ++i) {
			set_win_tiles(11 + i, 0, 1, 1, &EMPTY_TILE);
		}

	}
}