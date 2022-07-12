#include "Banks/SetAutoBank.h"

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

IMPORT_MAP(mapcutscene0);
IMPORT_MAP(diagnew);

DECLARE_MUSIC(bgm_level_cematery);


const UINT8 const collision_tiles_cutscene0[] = {5, 7, 8, 10, 11, 13, 16, 17, 18, 19, 20, 29, 37, 0};
extern UINT8 bank_tiles6;

extern const UINT16 bg_palette6[];
extern const UINT16 sprites_palette[];
extern UINT8 amulet ;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern UINT8 diag_found;
extern INT8 is_on_cutscene;
extern UINT8 current_cutscene;
extern UINT8 quiver;

UINT8 wait_c = 0u;
struct CameraInfo* camera_data;
struct EnemyInfo* sprite_1_data;
struct EnemyInfo* sprite_2_data;
struct EnemyInfo* sprite_3_data;
struct EnemyInfo* sprite_4_data;
const UINT8 const collision_tiles_cutscene[] = {5, 7, 8, 11, 13, 16, 17, 18, 19, 29, 37, 0};
Sprite* sprite_1;
Sprite* sprite_2;
Sprite* sprite_3;
Sprite* sprite_4;
UINT16 sprite_1_finalx = 0u;
UINT16 sprite_2_finalx = 0u;
INT8 temporeggia = 0;
INT8 counter_0 = 0;
const UINT16 distance_cutscene1_sprite = 172u;

void ShowCutDiag();
void set_window_y_c(UBYTE y);
void CalculateSpritesDestinations() BANKED;

void START() {
	
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
			/*const struct MapInfo* const level_cutscene[] = { &mapcutscene0 };
			const struct MapInfo** const levels_cutscene[] = {level_cutscene};
			UINT8 level_cuscene_banks[] = {BANK(mapcutscene0)};
			UINT8 * levels_cutscenes_banks[] = {level_cuscene_banks};
			const struct MapInfo** levels_cutscenes = levels_cutscene[0];
			*/
			UINT8 cutscene0_bank = BANK(mapcutscene0);
			InitScroll(cutscene0_bank, &mapcutscene0, collision_tiles_cutscene, 0);

			SpriteManagerLoad(SpriteCutmother);
			SpriteManagerLoad(SpriteCutarcher);
			SpriteManagerLoad(SpriteCastlegate);
			scroll_target = SpriteManagerAdd(SpriteCamerafocus, (UINT16) 440u, (UINT16) 144u);
	   		camera_data = (struct CameraInfo*)scroll_target->custom_data;
			sprite_1 = SpriteManagerAdd(SpriteCutmother, (UINT16) 440u, (UINT16) 144u);
			sprite_2 = SpriteManagerAdd(SpriteCutarcher, (UINT16) 432u, (UINT16) 144u);
			sprite_1_data = (struct EnemyInfo*)sprite_1->custom_data;
			sprite_2_data = (struct EnemyInfo*)sprite_2->custom_data;
			PlayMusic(bgm_level_cematery, 1);

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

}

void UPDATE() {
	if(wait_c < 40u){
		wait_c ++;
		return;
	}
	switch(current_cutscene){
		case 1u:
			if((KEY_TICKED(J_A) || KEY_TICKED(J_B)) && wait_c == 40u){
				diag_found = Build_Next_Dialog_Banked(scroll_target);
				ShowCutDiag();
				CalculateSpritesDestinations();
				wait_c = 41u;
				sprite_3 = SpriteManagerAdd(SpriteCastlegate, (UINT16) 600u, (UINT16) 130u);
				sprite_3_data = (struct EnemyInfo*)sprite_3->custom_data;
				sprite_3_data->enemy_state = ENEMY_STATE_NORMAL;
				sprite_3->attr_add = 0b10000000;
				quiver = 0b0000000001;
			}
		break;
	}
	switch(wait_c){
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
				if(temporeggia >> 2 == 0){					
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
			set_window_y_c(144);
			HIDE_WIN;
			current_level = 7u;
			current_map = 0;
			SetState(StateWorldmap);
		break;
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
	}
}

void set_window_y_c(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u){} //SHOW_WIN; 
	else { HIDE_WIN; LYC_REG = 160u; } 
}