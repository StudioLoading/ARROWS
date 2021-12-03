#include "Banks/SetBank7.h"

#include "../res/src/diagnew.h"
#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/mapboss0.h"
#include "../res/src/mapboss1.h"
#include "../res/src/mapboss2.h"
#include "../res/src/mapboss3.h"
#include "../res/src/mapboss4.h"
#include "../res/src/mapboss5.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"

#include "custom_datas.h"
#include "TileAnimations.h"
#include "Dialogs.h"
#include "sgb_palette.h"


extern UINT8 collision_tiles[];
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
extern UINT8 updatecounter;
extern UINT8 current_camera_state; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
extern UINT8 current_camera_counter;
extern UINT8 diag_found;
extern INT8 load_next_d;
extern INT8 update_hud;

extern void ShowWindow();
extern void ShowWindowDiag();
extern void UpdateHUD();
extern void Build_Next_Dialog();


//Boss
UINT8 current_level_b = 0u; //0 default/wolf, 1 gator, 2 eagle, 3 ibex, 4 bear, 5 walrus

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
const struct MapInfo** const bosses[] = {boss_0, boss_1, boss_2, boss_3, boss_4, boss_5};

struct Sprite* boss;
INT8 boss_hp = 0;
struct EnemyInfo* boss_data_b;
struct Sprite* reward = 0;

const UINT8 const collision_btiles4[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 68, 69, 70, 71, 73, 74, 75, 81, 90, 100, 101, 102, 103, 104, 111, 119, 0};//numero delle tile con zero finale

const UINT8 const collision_btiles6[] = {2, 7, 10, 11, 12, 13, 14, 15, 16, 17, 20, 26, 35, 36, 37, 38, 39, 41, 43, 44, 61, 62, 64, 111, 119, 0};//numero delle tile di collisione seguito da zero finale

void WriteBBOSSHP();
void populate_boss0();
void SpawnReward();
void SpawnBoss(INT8 hp_default);

void Start_StateBoss() {

	reward = 0;
	
	if(is_on_boss <= 0){
		is_on_boss = 0;
	}
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);
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
				set_sgb_palette_statusbar();
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
				set_sgb_palette_statusbar();
			}
		break;
		case 2u:
			level_tool=6;
			SpriteManagerLoad(SpriteEagle);
			SpriteManagerLoad(SpriteKey);
			if(sgb_check()){
				set_sgb_palette01_FOREST();
				set_sgb_palette_statusbar();
			}			
		break;
		case 3u:
			level_tool=0;
			SpriteManagerLoad(SpriteIbex);
			SpriteManagerLoad(SpriteAmulet);
			SpriteManagerLoad(SpriteGate);
			if(sgb_check()){
				set_sgb_palette01_1B();
				set_sgb_palette_statusbar();
			}
		break;
		case 4u:
			level_tool=7;
			SpriteManagerLoad(SpriteBear);
			SpriteManagerLoad(SpriteKey);
			if(sgb_check()){
				set_sgb_palette01_TREES();
				set_sgb_palette_statusbar();
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
				set_sgb_palette_statusbar();
			}
		break;
	}
	
	SHOW_SPRITES;

	//SCROLL
	const struct MapInfo** level_maps_b = bosses[current_level_b];
	UINT8 map_w, map_h;
	GetMapSize(level_maps_b[0], &map_w, &map_h);
	if(current_camera_state < 3u){
		ScrollFindTile(level_maps_b[0], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
		scroll_top_movement_limit = 60;
		scroll_target = SpriteManagerAdd(SpriteCamerafocus, drop_player_x << 3, drop_player_y << 3);
	}else{
		if(is_on_boss < 2){
			ScrollFindTile(level_maps_b[0], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);	
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
			InitScroll(level_maps_b[0], collision_tiles, 0);
		break;
		case 3u:
		case 4u:
			InitScroll(level_maps_b[0], collision_btiles4, 0);
		break;
		case 5u:
			InitScroll(level_maps_b[0], collision_btiles6, 0);
		break;
	}
	
	SHOW_BKG;
	
	
	if (is_on_boss >= 2){
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
		if(is_on_boss >= 2){
			boss_data_b->enemy_state = ENEMY_STATE_DEAD;	
		}
	}
		
	
	//INIT ARCHER
	if (archer_data->ups > 0 & archer_data->ups != ups){
		ups = archer_data->ups;
	}
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 99u;
	}
	archer_data->ups =ups;
	archer_data->hp = hp;
	archer_data->coins = coins;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 0);
	ShowWindow();
	UpdateHUD();
	WriteBBOSSHP();
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

}

void Update_StateBoss() {
	
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
				SetState(StateGame);
			break;
		}
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
				if(scroll_target->y < (boss->y + (boss->coll_h >> 1))){scroll_target->y += 1;}
				if (scroll_target->y > (boss->y + (boss->coll_h >> 1))){scroll_target->y -= 1;}
				if(scroll_target->x < (boss->x + boss->coll_x)){scroll_target->x += 1;}
				if (scroll_target->x > (boss->x + boss->coll_x)){scroll_target->x -= 1;}
				if (scroll_target->x == (boss->x + boss->coll_x) && 
					scroll_target->y == (boss->y + (boss->coll_h >> 1))){
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
	if (update_hud != 0){
		update_hud = 0;
		hp = archer_data->hp;
		amulet = archer_data->amulet;
		coins = archer_data->coins;
		ups = archer_data->ups;
		UpdateHUD();
	}
	
	if (boss_hp != boss_data_b->hp && is_on_boss < 2){
		boss_hp = boss_data_b->hp;
		WriteBBOSSHP();
		if (boss_hp <= 0){
			is_on_boss = 2;
			SpawnReward();
		}
	}
	
	if(level_tool && level_tool == archer_data->tool){
		UpdateHUD();
	}
	
	//UPDATE ARCHER POSX IN BOSS CUSTOM_DATA
	boss_data_b->archer_posx = scroll_target->x;
	
	//MOVING BACKGROUND TILES	
	if (current_level_b != 3u){ // ibex has not to be animated with water
		updatecounter++;
		if (updatecounter < 60) {
			switch(updatecounter){
				case 1:
					AnimSpuncioni0();
				break;
				case 30:
					AnimSpuncioni1();
				break;
			}
			if(current_level_b > 0u && current_level_b != 5u){
				switch(updatecounter){
					case 1:
					case 30:
						AnimWaters0();
					break;
					case 15:
					case 45:
						AnimWaters1();
					break;
				}
			}
		}else{
			updatecounter = 0;
		}
	}
	
	
}

void SpawnBoss(INT8 hp_default){
		struct Sprite* gate_sprite = 0;
		struct EnemyInfo* gatedata = 0;
		switch(current_level_b){
			case 0u:
				boss = SpriteManagerAdd(SpriteWolf, (UINT16) 24u << 3, (UINT16) 12u << 3); //34, 12
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
			break;
			case 1u:
				boss = SpriteManagerAdd(SpriteAlligator, (UINT16) 29u << 3, (UINT16) 14u << 3);
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
				boss = SpriteManagerAdd(SpriteIbex, (UINT16) 24u << 3, (UINT16) 12u << 3);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
				gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 40u << 3,  (UINT16) 13u << 3);
				gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
				gatedata->vx = 3;
			break;
			case 4u:
				boss = SpriteManagerAdd(SpriteBear, (UINT16) 20u << 3, (UINT16) 12u << 3);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
			break;
			case 5u:
				boss = SpriteManagerAdd(SpriteWalrus, (UINT16) 12u << 3, (UINT16) 15u << 3);
				boss_data_b = (struct EnemyInfo*)boss->custom_data;
				boss_hp = boss_data_b->hp;
				gate_sprite = SpriteManagerAdd(SpriteGate, (UINT16) 34 << 3, (UINT16) 19 << 3);
				gatedata = (struct EnemyInfo*)gate_sprite->custom_data;
				gatedata->vx = 4;
			break;
		}
		
		if(hp_default == 0){
			boss_hp = 0;
		}
}

void SpawnReward(){
	struct ItemInfo* datak = 0;
	struct Sprite* key_s = 0;
	switch (current_level_b){
		case 0u:// wolf -> wrench
			boss->x = (UINT16) 24u << 3;
			boss->y = (UINT16) 12u << 3;
			reward = SpriteManagerAdd(SpriteKey, (UINT16) 30u << 3, (UINT16) 10u << 3);
			datak = (struct ItemInfo*)reward->custom_data;
			datak->type = 2;
			datak->setup = 1u;
		break;
		case 1u: // gator -> amulet stone
			reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 24u << 3, (UINT16) 13u << 3);
			datak = (struct ItemInfo*)reward->custom_data;
			datak->type = 1;
			datak->setup = 1;
		break;
		case 2u: // eagle -> key
			reward = SpriteManagerAdd(SpriteKey, (UINT16) 19u << 3, (UINT16) 14u << 3);
			datak = (struct ItemInfo*)reward->custom_data;
			datak->type = 1;
			datak->setup = 1u;
		break;
		case 3u: // ibex -> amulet thunder
			reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 29u << 3, (UINT16) 13u << 3);
			datak = (struct ItemInfo*)reward->custom_data;
			datak->type = 3;
			datak->setup = 1;	
		break;
		case 4u: // bear -> wrench
			reward = SpriteManagerAdd(SpriteKey, (UINT16) 30u << 3, (UINT16) 11u << 3);
			datak = (struct ItemInfo*)reward->custom_data;
			datak->type = 2;
			datak->setup = 1u;
		break;
		case 5u: // tusk -> amulet water		
			boss->x = (UINT16) 12u << 3;
			boss->y = (UINT16) 15u << 3;
			reward = SpriteManagerAdd(SpriteAmulet, (UINT16) 28u << 3, (UINT16) 13u << 3);
			datak = (struct ItemInfo*)reward->custom_data;
			datak->type = 2;
			datak->setup = 1;
		break;
	}
}

void WriteBBOSSHP(){
	//PRINT_POS(9, 0);
	//Printf("%d", is_on_boss);
	PRINT_POS(10, 0);
	if(boss_hp>0){
		if(boss_hp > 9){
			Printf("BOSS>%d", boss_hp);
		}else if (boss_hp < 10){
			Printf("BOSS>0%d", boss_hp);
		}	
	}else{
		Printf("BOSS>00");
	}
}