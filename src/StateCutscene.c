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
UINT8 wait_c = 0u;
struct CameraInfo* camera_data;
struct CameraInfo* sprite_1_data;
struct CameraInfo* sprite_2_data;
const UINT8 const collision_tiles_cutscene[] = {5, 7, 8, 10, 11, 13, 16, 17, 18, 19, 20, 29, 37, 0};
Sprite* sprite_1;
Sprite* sprite_2;
UINT16 sprite_1_finalx = 0u;
UINT16 sprite_2_finalx = 0u;

void ShowCutDiag();
void set_window_y_c(UBYTE y);
void CalculateSpritesDestinations() BANKED;

void START() {
	
	//INIT SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0xFF; //Max volume 0x77

    SpriteManagerLoad(SpriteCamerafocus);
    SpriteManagerLoad(SpriteMother);
	SpriteManagerLoad(SpriteCutarcher);
	
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

			scroll_target = SpriteManagerAdd(SpriteCamerafocus, 100u, 150u);
	   		camera_data = (struct CameraInfo*)scroll_target->custom_data;
			sprite_1 = SpriteManagerAdd(SpriteMother, 100u, 142u);
			sprite_1->mirror = V_MIRROR;
			sprite_2 = SpriteManagerAdd(SpriteCutarcher, 80u, 138u);
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
			if(KEY_TICKED(J_A) || KEY_TICKED(J_B)){
				diag_found = Build_Next_Dialog_Banked(scroll_target);
				ShowCutDiag();
				CalculateSpritesDestinations();
				wait_c = 41u;
			}
		break;
	}
	if(wait_c == 41u){
		if(sprite_1->x != sprite_1_finalx){			
			TranslateSprite(sprite_1, 1 << delta_time, 0);
		}
		if(sprite_2->x != sprite_2_finalx){
			TranslateSprite(sprite_2, 1 << delta_time, 0);
		}
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
			sprite_1_finalx = sprite_1->x + 100u;
			sprite_2_finalx = sprite_2->x + 100u;
			struct EnemyInfo* sprite_1_data = (struct EnemyInfo*)sprite_1->custom_data;
			sprite_1_data->enemy_state = ENEMY_STATE_WALKING;
			sprite_1_data->vx = 1;
			struct EnemyInfo* sprite_2_data = (struct EnemyInfo*)sprite_2->custom_data;
			sprite_2_data->enemy_state = ENEMY_STATE_WALKING;
			sprite_2_data->vx = 1;
		break;
	}
}

void set_window_y_c(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}