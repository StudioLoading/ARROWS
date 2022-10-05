#include "Banks/SetAutoBank.h"

#include "SGB.h"
#include "Keys.h"
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
IMPORT_TILES(tiles7);

IMPORT_MAP(mapcutscene0);
IMPORT_MAP(mapcutscene1);
IMPORT_MAP(mapcutscene2);
IMPORT_MAP(mapboss1);
IMPORT_MAP(mapboss9);
IMPORT_MAP(diagnew);
IMPORT_MAP(mapend);
IMPORT_MAP(border);

DECLARE_MUSIC(bgm_level_cematery);
DECLARE_MUSIC(bgm_level_castle);
DECLARE_MUSIC(bgm_amulet);
DECLARE_MUSIC(bgm_titlescreen);
DECLARE_MUSIC(bgm_level_zoo);
DECLARE_MUSIC(bgm_level_sewer);
DECLARE_MUSIC(bgm_level_sky);

const UINT8 const collision_tiles_cutscene0[] = {5, 7, 8, 10, 11, 13, 16, 17, 18, 19, 20, 29, 37, 0};
extern UINT8 bank_tiles6;

extern UINT8 J_JUMP;
extern UINT8 J_FIRE;
extern const UINT16 bg_palette6[];
extern const UINT16 sprites_palette[];
extern UINT8 amulet ;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern struct EnemyInfo* mother_data;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern UINT8 diag_found;
extern INT8 is_on_cutscene;
extern UINT8 current_cutscene;
extern UINT8 quiver;
extern struct EnemyInfo* bossfighter_data;
extern FinalFightInfo finalfightdata;
extern UINT8 updatecounter;
extern INT8 final_border_set;
extern const UINT8 FIRE_QUIVER;

UINT8 wait_c = 0u;
struct CameraInfo* camera_data;
struct CagedbossInfo* sprite_finalboss_data;
struct EnemyInfo* sprite_1_data;
struct EnemyInfo* sprite_2_data;
struct EnemyInfo* sprite_3_data;
struct EnemyInfo* sprite_4_data;
const UINT8 const collision_tiles_cutscene[] = {5, 7, 8, 11, 13, 16, 17, 18, 19, 29, 37, 0};
//questo sotto deve essere uguale all' array collision_tiles7
const UINT8 const collision_tiles_cutscene7[] = {7, 8, 11, 13, 16, 17, 18, 20, 22, 25, 26, 30, 31, 35, 40, 41, 42, 46, 51, 52, 53, 64, 69, 77, 78, 79, 80, 81, 82, 89, 90, 94, 95, 111, 119, 0};//numero delle tile di collisione seguito da zero finale
const UINT8 const collision_tiles_cutscene20[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 74, 75, 76, 77, 81, 85, 86, 89, 90, 91, 92, 104, 111, 119, 0};//numero delle tile con zero finale
const UINT8 const collision_tiles_cutscene21[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 74, 75, 76, 77, 81, 85, 86, 89, 90, 91, 92, 104, 111, 119, 0};//numero delle tile con zero finale

INT8 camera_tramble_c = 0;

Sprite* sprite_1;
Sprite* sprite_2;
Sprite* sprite_3;
Sprite* sprite_4;
UINT16 camera_finalx = 0u;
UINT16 camera_finaly = 0u;
UINT16 sprite_1_finalx = 0u;
UINT16 sprite_2_finalx = 0u;
UINT16 sprite_2_finaly = 0u;
UINT16 sprite_3_finalx = 0u;
UINT16 sprite_3_finaly = 0u;
UINT16 sprite_4_finalx = 0u;
UINT16 sprite_4_finaly = 0u;
INT8 temporeggia = 0;
INT8 counter_0 = 0;
const UINT16 distance_cutscene1_sprite = 172u;
UINT8 scene_bank = 0u;

void ShowCutDiag();
void set_window_y_c(UBYTE y);
void CalculateSpritesDestinations() BANKED;


void START() {
	if(final_border_set == 0 && current_cutscene == 19u){
		LOAD_SGB_BORDER(border);
	}
	if(wait_c == 99u){
		//worldmap
		current_level += 1;
		current_map = 0;
		if(current_level < 10u){
			is_on_cutscene = 0;
		}
		temporeggia = 0;
		wait_c = 0;
		set_window_y_c(144);
		HIDE_WIN;
		SetState(StateWorldmap);
		return;
	}
	//INIT SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0xFF; //Max volume 0x77

    SpriteManagerLoad(SpriteCamerafocus);
	
	current_cutscene++;
	is_on_cutscene = 1;

	switch (current_cutscene){
		case 1u:
			if(sgb_check()){
				set_sgb_palette01_CEMATERYCRYPT();
			}
			scene_bank = BANK(mapcutscene0);
			InitScroll(scene_bank, &mapcutscene0, collision_tiles_cutscene, 0);

			SpriteManagerLoad(SpriteCutmother);
			SpriteManagerLoad(SpriteCutarcher);
			SpriteManagerLoad(SpriteCastlegate);
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, (UINT16) 440u, (UINT16) 160u);
	   		camera_data = (struct CameraInfo*)scroll_target->custom_data;
			sprite_1 = SpriteManagerAdd(SpriteCutmother, (UINT16) 440u, (UINT16) 144u);
			sprite_2 = SpriteManagerAdd(SpriteCutarcher, (UINT16) 432u, (UINT16) 144u);
			sprite_1_data = (struct EnemyInfo*)sprite_1->custom_data;
			sprite_2_data = (struct EnemyInfo*)sprite_2->custom_data;
			PlayMusic(bgm_level_cematery, 1);

		break;
		case 2u:		
			if(sgb_check()){
				set_sgb_palette01_CASTLE();
				set_sgb_palette_statusbar();
			}			
			scene_bank = BANK(mapcutscene1);
			InitScroll(scene_bank, &mapcutscene1, collision_tiles_cutscene7, 0);
			SpriteManagerLoad(SpriteCutmother);
			SpriteManagerLoad(SpriteCutarcher);
			SpriteManagerLoad(SpriteCutfinalboss);
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, ((UINT16) 22u << 3), ((UINT16) 12u << 3));
	   		camera_data = (struct CameraInfo*)scroll_target->custom_data;
			sprite_1 = SpriteManagerAdd(SpriteCutfinalboss, ((UINT16) 36u << 3), ((UINT16) 11u << 3));
			sprite_1->mirror = V_MIRROR;
			sprite_finalboss_data = (struct CagedbossInfo*)sprite_1->custom_data;
			sprite_finalboss_data->state = CAGEDBOSS_IDLE;
			sprite_finalboss_data->setup = 1;
			sprite_2 = SpriteManagerAdd(SpriteCutmother, ((UINT16) 35u << 3), ((UINT16) 13u << 3));						
			sprite_3 = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 30u << 3), ((UINT16) 13u << 3));
			sprite_2_data = (struct EnemyInfo*)sprite_2->custom_data;
			sprite_3_data = (struct EnemyInfo*)sprite_3->custom_data;
			sprite_3_data->enemy_state = ENEMY_STATE_WAIT;
			PlayMusic(bgm_level_castle, 1);
		break;
		case 3u://eagle che prende il boss e lo porta a destra
			if(sgb_check()){
				set_sgb_palette01_CASTLE();
				set_sgb_palette_statusbar();
			}
			scene_bank = BANK(mapcutscene1);
			InitScroll(scene_bank, &mapcutscene1, collision_tiles_cutscene7, 0);
			SpriteManagerLoad(SpriteCutarcher);
			SpriteManagerLoad(SpriteArrowmother);
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, ((UINT16) 20u << 3), ((UINT16) 12u << 3));
	   		camera_data = (struct CameraInfo*)scroll_target->custom_data;
			sprite_1 = SpriteManagerAdd(SpriteCutfinalboss, ((UINT16) 36u << 3), ((UINT16) 11u << 3));
			sprite_1->mirror = V_MIRROR;
			sprite_1_data = (struct EnemyInfo*)sprite_1->custom_data;
			sprite_1_data->enemy_state = ENEMY_STATE_WAIT;
			//sprite_finalboss_data->setup = 1;
			sprite_2 = SpriteManagerAdd(SpriteCutmother, ((UINT16) 29u << 3), ((UINT16) 13u << 3));						
			sprite_3 = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 32u << 3), ((UINT16) 13u << 3));
			mother_data = (struct EnemyInfo*)sprite_2->custom_data;
			sprite_3_data = (struct EnemyInfo*)sprite_3->custom_data;
			sprite_3_data->enemy_state = ENEMY_STATE_WAIT;
			sprite_4 = SpriteManagerAdd(SpriteCuteagle, ((UINT16) 10u << 3), ((UINT16) 1u << 3) -2u);
			sprite_4_data = (struct EnemyInfo*)sprite_4->custom_data;
			sprite_4_data->enemy_state = ENEMY_STATE_NORMAL;
		break;
		case 4u://eagle che lascia boss sul final stage
			if(sgb_check()){
				set_sgb_palette01_BOSS();
				set_sgb_palette_statusbar();
			}
			scene_bank = BANK(mapboss9);
			InitScroll(scene_bank, &mapboss9, collision_tiles_cutscene7, 0);
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, ((UINT16) 3u << 3), ((UINT16) 6u << 3));
	   		camera_data = (struct CameraInfo*)scroll_target->custom_data;
			SpriteManagerLoad(SpriteCutarcher);
			SpriteManagerLoad(SpriteCuteagle);
			SpriteManagerLoad(SpriteCutboss);
			SpriteManagerLoad(SpriteArrowmother);
			sprite_2 = SpriteManagerAdd(SpriteCuteagle, ((UINT16) 13u << 3), ((UINT16) 0u << 3));
			sprite_2_data = (struct EnemyInfo*) sprite_2->custom_data;
			sprite_3 = SpriteManagerAdd(SpriteCutboss, ((UINT16) 13u << 3), ((UINT16) 3u << 3));
			sprite_3_data = (struct EnemyInfo*) sprite_3->custom_data;
		break;
		case 5u://boss dies		
			if(sgb_check()){
				set_sgb_palette01_BOSS();
				//set_sgb_palette_statusbar();
			}
			PlayMusic(bgm_titlescreen, 1);	
			scene_bank = BANK(mapboss9);
			InitScroll(scene_bank, &mapboss9, collision_tiles_cutscene7, 0);
	   		SpriteManagerLoad(SpriteCutarcher);
			SpriteManagerLoad(SpriteCutbossdead);
			SpriteManagerLoad(SpriteCutalligator);
			UINT16 x3 = bossfighter_data->enemy_accel_y;
			sprite_3 = SpriteManagerAdd(SpriteCutbossdead,  x3, ((UINT16) 15u << 3));
			sprite_3_data = (struct EnemyInfo*) sprite_3->custom_data;
			if(bossfighter_data->enemy_accel_y < ((UINT16) 15u << 3)){
				sprite_1 = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 12u << 3), ((UINT16) 17u << 3));
				sprite_1->mirror = V_MIRROR;
			}else{
				sprite_1 = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 21u << 3), ((UINT16) 17u << 3));
				sprite_3->mirror = V_MIRROR;
			}
			sprite_1_data = (struct EnemyInfo*) sprite_1->custom_data;
			sprite_1_data->enemy_state = ENEMY_STATE_WAIT;
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, sprite_1->x, ((UINT16) 22u << 3));
			camera_data = (struct CameraInfo*)scroll_target->custom_data;
			
		break;
		case 11u://wolf attacks boss
		case 12u://ibex attacks boss
		case 13u://bear attacks boss
			//ResumeMusic;	
			scene_bank = BANK(mapboss9);
			InitScroll(scene_bank, &mapboss9, collision_tiles_cutscene7, 0);
	   		SpriteManagerLoad(SpriteCutarcher);
			switch(current_cutscene){
				case 11u:
					scroll_target = SpriteManagerAdd(SpriteCutwolf,((UINT16) 6u << 3), ((UINT16) 15u << 3));
				break;
				case 12u:
					scroll_target = SpriteManagerAdd(SpriteCutibex,((UINT16) 6u << 3), ((UINT16) 15u << 3));
				break;
				case 13u:
					scroll_target = SpriteManagerAdd(SpriteCutbear,((UINT16) 6u << 3), ((UINT16) 15u << 3));
				break;
			}
			sprite_1_data = (struct EnemyInfo*) scroll_target->custom_data;
			sprite_2 = SpriteManagerAdd(SpriteCutfinalboss,((UINT16) 20u << 3), ((UINT16) 15u << 3));
			sprite_2->mirror = V_MIRROR;
			sprite_2_data = (struct EnemyInfo*) sprite_2->custom_data;
		break;
		case 20u://final cutscene @ zoo
			if(sgb_check()){
				set_sgb_palette01_ZOO();
			}
			PlayMusic(bgm_level_zoo, 1);
			scene_bank = BANK(mapcutscene2);
			InitScroll(scene_bank, &mapcutscene2, collision_tiles_cutscene20, 0);
	   		SpriteManagerLoad(SpriteCutarcher);
	   		SpriteManagerLoad(SpriteCutwolf);
	   		SpriteManagerLoad(SpriteCutmother);
			scroll_target = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 8u << 3), ((UINT16) 12u << 3));
			scroll_target->mirror = V_MIRROR;
			sprite_4_data = (struct EnemyInfo*) scroll_target->custom_data;
			sprite_4_data->enemy_state = ENEMY_STATE_WAIT;
			sprite_1 = SpriteManagerAdd(SpriteCutmother,  ((UINT16) 10u << 3), ((UINT16) 12u << 3));
			sprite_1->mirror = V_MIRROR;
			sprite_1_data = (struct EnemyInfo*) sprite_1->custom_data;
			sprite_1_data->enemy_state = ENEMY_STATE_HIDDEN;
			sprite_2 = SpriteManagerAdd(SpriteCutwolf,  ((UINT16) 3u << 3), ((UINT16) 13u << 3) - 3u);
			sprite_2->mirror = V_MIRROR;
			sprite_2_data = (struct EnemyInfo*) sprite_2->custom_data;
			sprite_2_data->enemy_state = ENEMY_STATE_WAIT;
		break;
		case 21u://final cutscene @sewer
			if(sgb_check()){
				set_sgb_palette01_SEWER();
			}
			PlayMusic(bgm_level_sewer, 1);
			scene_bank = BANK(mapboss1);
			InitScroll(scene_bank, &mapboss1, collision_tiles_cutscene21, 0);
	   		SpriteManagerLoad(SpriteCutboss);
	   		SpriteManagerLoad(SpriteCutalligator);
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, ((UINT16) 4u << 3), ((UINT16) 2u << 3));
		break;
	}
	
	SHOW_SPRITES;

	//CLEAN DIAGS
	memcpy(d1, "                    ", 20);
	memcpy(d2, "                    ", 20);
	memcpy(d3, "                    ", 20);
	memcpy(d4, "                    ", 20);

	//SCROLL
	scroll_bottom_movement_limit = 60u;//customizzo altezza archer sul display
	//const struct MapInfo** level_cuts = cutscenes[current_cutscene];

	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	//ShowWindow();	
	
	wait_c = 0u;
	//empty the windowdiag
	diag_found = Build_Next_Dialog_Banked(scroll_target);
	ShowCutDiag();

}

void UPDATE() {
	if(wait_c < 40u){
		wait_c ++;
		return;
	}
	switch(current_cutscene){
		case 1u://mother meeting
			switch(wait_c){
				case 40u: // (KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)) &&
					diag_found = Build_Next_Dialog_Banked(scroll_target);
					ShowCutDiag();
					CalculateSpritesDestinations();
					wait_c = 41u;
					sprite_3 = SpriteManagerAdd(SpriteCastlegate, (UINT16) 600u, (UINT16) 130u);
					sprite_3_data = (struct EnemyInfo*)sprite_3->custom_data;
					sprite_3_data->enemy_state = ENEMY_STATE_NORMAL;
					quiver = FIRE_QUIVER;
				break;
				case 41u:
					switch(temporeggia){
						case 0:
							/*if(sprite_2->y != sprite_1->y){
								sprite_2->y = sprite_1->y;
							}*/
							if(sprite_1->x != sprite_1_finalx){			
								TranslateSprite(sprite_1, 1 << delta_time, 0);
							}
							if(sprite_2->x != sprite_2_finalx){
								TranslateSprite(sprite_2, 1 << delta_time, 0);
							}
							if(scroll_target->x != sprite_1->x){
								scroll_target->x = sprite_1->x;
							}
							temporeggia = 1;
							if(sprite_1->x == sprite_1_finalx && sprite_2->x == sprite_2_finalx){
								wait_c = 42u;
							}
						break;
						case 1:
							temporeggia = 0;
						break;
					}
				break;
				case 42u: //sprite arrivati a destinazione finale
					PauseMusic;
					sprite_1_data->enemy_state = ENEMY_STATE_WAIT;
					sprite_2_data->enemy_state = ENEMY_STATE_WAIT;
					if(temporeggia < 60){
						temporeggia++;
					}else{
						temporeggia = 0;
						//metti amuleto, azzera temporeggia
						switch(counter_0){
							case 0:
								CutsceneAmulet0();
								PlayFx(CHANNEL_1, 60, 0x23, 0x93, 0xf7, 0x48, 0x81);
							break;
							case 1:
								CutsceneAmulet1();
								PlayFx(CHANNEL_1, 60, 0x23, 0x93, 0xf7, 0x48, 0x81);
							break;
							case 2:
								CutsceneAmulet2();
								PlayFx(CHANNEL_1, 60, 0x23, 0x93, 0xf7, 0x48, 0x81);
							break;
							case 3:
								CutsceneAmulet3();
								PlayFx(CHANNEL_1, 60, 0x23, 0x93, 0xf7, 0x48, 0x81);
							break;
							case 4:
								wait_c = 43u;
							break;
						}
						counter_0++;
					}
				break;
				case 43u:
					//solleva il portone
					if(temporeggia < 42){
						if(temporeggia & 1){
							sprite_3->y += 1;
						}else{
							sprite_3->y -= 2;
						}
						if(temporeggia & 1 == 0){					
							PlayFx(CHANNEL_1, 60, 0x73, 0x09, 0xf2, 0x1e, 0x86);
						}
						temporeggia++;
					}else{
						wait_c = 44u;
						sprite_1_data->enemy_state = ENEMY_STATE_WALKING;
						sprite_2_data->enemy_state = ENEMY_STATE_WALKING;
						sprite_1->attr_add = 0b10000000;
						sprite_2->attr_add = 0b10000000;
						sprite_1_finalx = sprite_1->x + 32u;
						sprite_2_finalx = sprite_2->x + 54u;
					}
				break;
				case 44u:
					ResumeMusic;
					if(sprite_1->x != sprite_1_finalx){			
						TranslateSprite(sprite_1, 1 << delta_time, 0);
					}
					if(sprite_2->x != sprite_2_finalx){
						TranslateSprite(sprite_2, 1 << delta_time, 0);
					}
					if(sprite_1->x == sprite_1_finalx && sprite_2->x == sprite_2_finalx){
						wait_c = 99u;
					}
				break;
				case 99u:
					//worldmap
					wait_c = 0;
					set_window_y_c(144);
					HIDE_WIN;
					current_level = 7u;
					current_map = 0;
					SetState(StateWorldmap);
				break;
			}
		break;
		case 2u://tower talk
			switch(wait_c){
				case 40u:
					CalculateSpritesDestinations();
					wait_c = 41u;
				break;
				case 41u:
					if(camera_finalx > scroll_target->x){
						TranslateSprite(scroll_target, 1 << delta_time, 0);
					}else{
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						ShowCutDiag();
						wait_c = 42u;
						temporeggia = 0;
					}
				break;
				case 42u:
					if(temporeggia < 120){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)){
							temporeggia = 0;
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							ShowCutDiag();
							wait_c = 43u;
						}
					}
				break;
				case 43u:
					if(temporeggia < 120){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)){
							temporeggia = 0;
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							ShowCutDiag();
							wait_c = 44u;
						}
					}
				break;
				case 44u:
					if(temporeggia < 120){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)){
							temporeggia = 0;
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							ShowCutDiag();
							wait_c = 45u;
						}
					}
				break;
				case 45u:
					if(temporeggia < 120){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)){
							temporeggia = 0;
							wait_c = 46u;
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							SetState(StateDiag);
						}
					}
				break;
			}
		break;
		case 3u://eagle che porta via boss		
			switch(wait_c){
				case 40u:
					CalculateSpritesDestinations();
					diag_found = Build_Next_Dialog_Banked(scroll_target);
					ShowCutDiag();
					wait_c = 41u;
				break;
				case 41u:
					if(sprite_4->x < sprite_4_finalx){
						TranslateSprite(sprite_4, 2 << delta_time, 0);
					}
					if(sprite_4->y < sprite_4_finaly){
						TranslateSprite(sprite_4, 0, 1 << delta_time);
					}
					if(camera_finalx > scroll_target->x){
						TranslateSprite(scroll_target, 1 << delta_time, 0);
					}else{		
						CalculateSpritesDestinations();
						sprite_4_data->enemy_state = ENEMY_STATE_JUMPING;
						//sprite_4_data->
						sprite_1_data->enemy_state = ENEMY_STATE_GRAPPLING;
						wait_c = 42u;
						temporeggia = 0;
					}
				break;
				case 42u:
					sprite_1->x = sprite_4->x;
					sprite_1->y = sprite_4->y + 22u;
					if(sprite_4->y > sprite_4_finaly && sprite_4->y < 800u){
						if(temporeggia == 3){
							TranslateSprite(sprite_4, 0, -1 << delta_time);
							temporeggia = 0;
						}else{
							temporeggia++;
						}
					}else if (sprite_4->x < sprite_4_finalx){
						if(sprite_4_data->enemy_state != ENEMY_STATE_SLIDING){
							sprite_4_data->enemy_state = ENEMY_STATE_SLIDING;
						}
						if(temporeggia == 0){
							temporeggia = 1;
						}else{
							temporeggia = 0;
						}
						TranslateSprite(sprite_4, 2 << delta_time, -temporeggia << delta_time);
					}else{
						wait_c = 43u;
					}
				break;
				case 43u:
					temporeggia = 0;
					diag_found = Build_Next_Dialog_Banked(scroll_target);
					ShowCutDiag();
					wait_c = 44u;
				break;
				case 44u:
					if(temporeggia < 60){
						temporeggia++;
					}else{
						temporeggia = 0;
						mother_data->enemy_state = ENEMY_STATE_ATTACK;
						//sprite_3_data->enemy_accel_y = -12;
						//sprite_3_data->enemy_state = ENEMY_STATE_JUMPING;
						wait_c = 45u;
					}
				break;
				case 45u:
					if(temporeggia < 60){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)){
							temporeggia = 0;
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							wait_c = 99u;
							SetState(StateDiag);
						}	
					}
				break;
				case 99u:
					//worldmap
					set_window_y_c(144);
					HIDE_WIN;
					current_level = 8u;
					is_on_cutscene = 0;
					current_map = 0;
					SetState(StateWorldmap);
				break;
			}
		break;
		case 4u://eagle che lascia boss cadere
			switch(wait_c){
				case 40u:
					CalculateSpritesDestinations();
					//diag_found = Build_Next_Dialog_Banked(scroll_target);
					//ShowCutDiag();
					wait_c = 41u;
				break;
				case 41u:
					if(sprite_2->x < sprite_2_finalx || sprite_2->y < sprite_2_finaly){
						if(sprite_2->x < sprite_2_finalx){
							TranslateSprite(sprite_2, 1 << delta_time, 0);
						}
						if(sprite_2->y < sprite_2_finaly){
							TranslateSprite(sprite_2, 0, 1 << delta_time);
						}
						if(sprite_3->x != sprite_2->x){
							sprite_3->x = sprite_2->x;
							wait_c = 41u;
						} 
						if(sprite_3->y != (sprite_2->y + 28u)){
							sprite_3->y = sprite_2->y + 28u;
							wait_c = 41u;
						}
						if(scroll_target->x != (sprite_3->x - 32u)){
							scroll_target->x = sprite_3->x - 32u;
							wait_c = 41u;
						}
						if(scroll_target->y != (sprite_3->y - 16u)){
							scroll_target->y = (sprite_3->y - 16u);
							wait_c = 41u;
						}			
					}else{
						CalculateSpritesDestinations();
						wait_c = 42u;
					}	
				break;
				case 42u:
					if(sprite_3_data->enemy_state == ENEMY_STATE_NORMAL){
						camera_tramble_c++;
						switch(camera_tramble_c){
							case 6:
								camera_tramble_c = 0;
							break;
							case 1:
							case 2:
								scroll_target->y = ((UINT16) 12u << 3);
								PlayFx(CHANNEL_1, 60, 0x42, 0x04, 0xfc, 0x28, 0x82);
							break;
							case 4:
							case 5:
								scroll_target->y = ((UINT16) 16u << 3);
								//PlayFx(CHANNEL_1, 60, 0x23, 0x01, 0xf7, 0x28, 0x82);
							break;
						}
					}else{
						if(scroll_target->x != (sprite_3->x - 32u)){
							scroll_target->x = sprite_3->x - 32u;
						}
						if(scroll_target->y != (sprite_3->y - 16u)){
							scroll_target->y = (sprite_3->y - 16u);
						}
					}
					if(sprite_2->x < sprite_2_finalx || sprite_2->y > sprite_2_finaly){//eagle flyies away
						if(sprite_2->x < sprite_2_finalx){
							TranslateSprite(sprite_2, 1 << delta_time, 0);
						}
						if(sprite_2->y > sprite_2_finaly){
							TranslateSprite(sprite_2, 0, -1 << delta_time);
						}
					}else{
						scroll_target->y = (sprite_3->y - 16u);
						CalculateSpritesDestinations();
						sprite_1 = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 5u << 3), ((UINT16) 13u << 3) + 4u);
						sprite_1_data = (struct EnemyInfo*) sprite_1->custom_data;
						wait_c = 43u;
					}
				break;
				case 43u://archer and arrowmother to sprite_1_finalx
					if(sprite_3_data->enemy_state == ENEMY_STATE_NORMAL){
						camera_tramble_c++;
						switch(camera_tramble_c){
							case 6:
								camera_tramble_c = 0;
							break;
							case 1:
							case 2:
								scroll_target->y = ((UINT16) 12u << 3);
							break;
							case 4:
							case 5:
								scroll_target->y = ((UINT16) 16u << 3);
							break;
						}
					}
					if(sprite_1->x < sprite_1_finalx){
						TranslateSprite(sprite_1, 1 << delta_time, 0);
					}else{
						CalculateSpritesDestinations();
						sprite_1_data->enemy_state = ENEMY_STATE_JUMPING;
						TranslateSprite(sprite_1, 0, -6 << delta_time);
						wait_c = 44u;
					}
					sprite_4->x = sprite_1->x;
				break;
				case 44u:
					TranslateSprite(sprite_4, 2 << delta_time, 0);
					sprite_1_data->tile_e_collision = TranslateSprite(sprite_1, 0, 1 << delta_time);
					if(sprite_1_data->tile_e_collision == 80u){
						sprite_1_data->enemy_state = ENEMY_STATE_KNEE;
						sprite_1_data->wait = 40u;
						temporeggia = 0;
						CalculateSpritesDestinations();
						wait_c = 45u;
					}
				break;
				case 45u:
					TranslateSprite(sprite_4, 2 << delta_time, 0);
					if(temporeggia < 50){
						temporeggia++;
					}
					if(temporeggia == 50 && (KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE))){
						temporeggia = 0;
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						PlayMusic(bgm_level_castle, 1);
						ShowCutDiag();
						wait_c = 46u;
					}
				break;
				case 46u:
					if(temporeggia < 50){
						temporeggia++;
					}
					if(temporeggia == 50 && (KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE))){
						temporeggia = 0;
						finalfightdata.to_be_loaded = 0u;
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						SetState(StateDiag);
					}
				break;
			}
		break;
		case 5u://boss muore
			switch(wait_c){
				case 40u:
					diag_found = Build_Next_Dialog_Banked(scroll_target);
					ShowCutDiag();
					wait_c = 41u;
				break;
				case 41u:					
					if(sprite_3_data->enemy_state == ENEMY_STATE_HIDDEN){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						ShowCutDiag();
						wait_c = 42u;
					}
				break;
				case 42u:
					if(sprite_1->mirror == NO_MIRROR){
						sprite_4 = SpriteManagerAdd(SpriteCutalligator, (UINT16) sprite_1->x - 16u, ((UINT16) 26u << 3));
					}else{
						sprite_4 = SpriteManagerAdd(SpriteCutalligator, (UINT16) sprite_1->x + 16u, ((UINT16) 26u << 3));						
					}
					sprite_4_data = (struct EnemyInfo*) sprite_4->custom_data;
					sprite_4_data->enemy_state = ENEMY_STATE_WALKING;
					if(sprite_1->mirror == NO_MIRROR){
						sprite_4_data->vx = 1;
					}else{
						sprite_4_data->vx = -1;
					}
					wait_c = 43u;
					temporeggia = 0;
					//PlayMusic(bgm_amulet, 1);
				break;
				case 43u:
					//temporeggia++;
				break;
				case 44u://wait_c = 44u is done on the DESTROY of Cutalligator
					//go to cutscene at the zoo
					/*wait_c = 0;
					set_window_y_c(144);
					HIDE_WIN;*/
					current_level = 9u;
					current_map = 0;
					wait_c = 99u;
					SetState(StateCutscene);
					/*
					current_map = 0;
					wait_c = 0u;
					SetState(StateWorldmap);*/
				break;
			}
		break;
		case 11u: //wolf hits boss
		case 12u: //ibex hits boss
		case 13u: //bear hits boss
			switch(wait_c){
				case 40u: // (KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)) &&
					diag_found = Build_Next_Dialog_Banked(scroll_target);
					ShowCutDiag();
					wait_c = 41u;
				break;
				case 42u:
					if(KEY_TICKED(J_JUMP) || KEY_TICKED(J_FIRE)){	
						temporeggia = 0;
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						is_on_cutscene = 0;
						//wait_c = 99u;
						SetState(StateDiag);
					}	
				break;
			}
		break;
		case 20u://final cutscene @ zoo
			switch(wait_c){
				case 40u:
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 41u;
					}
				break;
				case 41u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						wait_c = 42u;
					}
				break;
				case 42u:					
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 43u;
					}
				break;
				case 43u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						wait_c = 44u;
					}
				break;
				case 44u:					
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 45u;
					}
				break;
				case 45u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						wait_c = 46u;
					}
				break;
				case 46u:					
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 47u;
					}
				break;
				case 47u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						wait_c = 48u;
					}
				break;
				case 48u:					
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 49u;
					}
				break;
				case 49u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						wait_c = 50u;
					}
				break;
				case 50u:		
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 51u;
					}
				break;
				case 51u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						wait_c = 52u;
					}
				break;
				case 52u:					
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						sprite_2_data->enemy_state = ENEMY_STATE_HIDDEN;						
						wait_c = 53u;
					}
				break;
				case 53u:					
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						HIDE_WIN;
						SetState(StateCreditfinal);
					}
				break;
			}
		break;
		case 21u://final cutscene @sewer
			switch(wait_c){
				case 40u:
					CalculateSpritesDestinations();
					wait_c = 41u;
				break;
				case 41u:
					if(scroll_target->y < camera_finaly){			
						TranslateSprite(scroll_target, 0, 1 << delta_time);
					}else{
						wait_c = 42u;
					}
				break;
				case 42u:
					sprite_1 = SpriteManagerAdd(SpriteCutalligator, ((UINT16) 4u << 3), ((UINT16) 15u << 3));
					sprite_1->mirror = V_MIRROR;
					sprite_2 = SpriteManagerAdd(SpriteCutboss, ((UINT16) 7u << 3), ((UINT16) 13u << 3));
					sprite_1_data = (struct EnemyInfo*) sprite_1->custom_data;
					sprite_1_data->enemy_state = ENEMY_STATE_WAIT;
					sprite_2_data = (struct EnemyInfo*) sprite_2->custom_data;
					sprite_2_data->enemy_state = ENEMY_STATE_HIT;
					wait_c = 43u;
				break;
				case 43u:
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
						diag_found = Build_Next_Dialog_Banked(scroll_target);
						temporeggia = 0;
						ShowCutDiag();
						wait_c = 44u;
					}
				break;
				case 44u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							temporeggia = 0;
							ShowCutDiag();
							wait_c = 45u;
						}
					}
				break;
				case 45u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							temporeggia = 0;
							ShowCutDiag();
							wait_c = 46u;
						}
					}
				break;
				case 46u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							temporeggia = 0;
							ShowCutDiag();
							wait_c = 47u;
						}
					}
				break;
				case 47u:
					if(temporeggia < 40){
						temporeggia++;
					}else{
						if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP)){
							diag_found = Build_Next_Dialog_Banked(scroll_target);
							SetState(StateDiag);
						}
						//wait_c = 0;
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

}

void ShowCutDiag(){
	HIDE_WIN;
	set_window_y_c(144 - 32);
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
}

void CalculateSpritesDestinations() BANKED{
	switch(current_cutscene){
		case 1u:
			sprite_1_finalx = sprite_1->x + distance_cutscene1_sprite;
			sprite_2_finalx = sprite_2->x + distance_cutscene1_sprite;
			sprite_1_data->enemy_state = ENEMY_STATE_WALKING;
			sprite_1_data->vx = 1;
			sprite_2_data->enemy_state = ENEMY_STATE_WALKING;
			sprite_2_data->vx = 1;
		break;
		case 2u:
			camera_finalx = ((UINT16) 34u << 3);
			sprite_1_data->enemy_state = ENEMY_STATE_WAIT;
		break;
		case 3u:
			switch(wait_c){
				case 40u:
					camera_finalx = ((UINT16) 36u << 3);
					sprite_4_finalx = sprite_1->x;
					sprite_4_finaly = sprite_1->y - 24u;
				break;
				case 41u:
					camera_finalx = ((UINT16) 60u << 3);
					sprite_4_finalx = ((UINT16) 58u << 3);
					sprite_4_finaly = ((UINT16) 5u << 3);
				break;
			}
		break;
		case 4u:
			switch(wait_c){
				case 40u:
					sprite_2_finalx = ((UINT16) 19u << 3); //eagle
					sprite_2_finaly = ((UINT16) 6u << 3);
				break;
				case 41u:
					sprite_2_data->enemy_state = ENEMY_STATE_JUMPING;
					camera_tramble_c = 0;
					sprite_3_data->enemy_state = ENEMY_STATE_JUMPING;
					sprite_2_finalx = ((UINT16) 28u << 3); //eagle
					sprite_2_finaly = ((UINT16) 0u << 3);
				break;
				case 42:
					sprite_1 = SpriteManagerAdd(SpriteCutarcher, ((UINT16) 1u << 3), ((UINT16) 14u << 3));
					sprite_1_data = (struct EnemyInfo*) sprite_1->custom_data;
					sprite_4 = SpriteManagerAdd(SpriteArrowmother, sprite_1->x - 8u, sprite_1->y + 6u);
					sprite_4_data->enemy_state = ENEMY_STATE_WAIT;
					sprite_1_finalx = ((UINT16) 9u << 3);
				break;
				case 43:
					sprite_4_finalx = ((UINT16) 30u << 3);
				break;
			}
		break;
		case 21u:
			switch(wait_c){
				case 40u:
					camera_finaly = ((UINT16) 14u << 3);
				break;
			}
		break;
	}
}

void set_window_y_c(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u){} //SHOW_WIN; 
	else { HIDE_WIN; LYC_REG = 160u; } 
}