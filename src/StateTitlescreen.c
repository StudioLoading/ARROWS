#include "Banks/SetAutoBank.h"

#include "..\include\ZGBMain.h"
#include "Keys.h"
#include "Palette.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Fade.h"
#include "Music.h"

#include "custom_datas.h"
#include "sgb_palette.h"

#define TEST_QUIVER 0b0000010001
#define QUIVER 0b0000000001

IMPORT_TILES(font);

IMPORT_MAP(maptitlescreen);

DECLARE_MUSIC(bgm_titlescreen);

UINT8 quiver = TEST_QUIVER;//0b0000011111;
UINT8 amulet = 0;// = 0u;
UINT8 coins = 0;// = 30u;
INT8 ups = 0;// = 1;
INT8 hp;
INT8 level_tool = -1;
INT8 archer_tool = 0;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

const UINT8 collision_tiles_titlescreen[] = {1,0};

UINT8 current_camera_state = 0u; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
UINT8 current_camera_counter = 0u;
UINT8 wait_titlescreen = 0u;
INT8 loading_code = 0;

void START() {	

	current_camera_state = 0u;
	current_camera_counter = 0u;
	wait_titlescreen = 30u;
	amulet = 0;
    coins = 30u;
	ups = 1;
	hp = MAX_HP;
	archer_tool = 0;
	level_tool = -1;
	
	if(sgb_check()){
		set_sgb_palette01_2A();
		set_sgb_palette_title();
	}

	//SpriteManagerLoad(SpriteCamerafocus);
	//SpriteManagerLoad(SpriteArrowtitle);
	SHOW_SPRITES;
	
	INIT_FONT(font, PRINT_BKG); 
	
	InitScroll(BANK(maptitlescreen), &maptitlescreen, collision_tiles_titlescreen, 0);	
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, 9u << 3, 8u << 3);
	SHOW_BKG;
	
}

void UPDATE() {	

	switch(loading_code){
		case 5:
			if(KEY_TICKED(J_UP)){
				StopMusic;
				quiver = 0b0000011111;
				PlayFx(CHANNEL_1, 30, 0x7d, 0x85, 0xf5, 0xff, 0x57);
				PlayFx(CHANNEL_1, 30, 0x7d, 0x85, 0xf5, 0xff, 0x57);
				PlayFx(CHANNEL_1, 30, 0x7d, 0x85, 0xf5, 0xff, 0x57);
				PlayFx(CHANNEL_1, 30, 0x7d, 0x85, 0xf5, 0xff, 0x57);
				loading_code = 7;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}	
		break;
		case 4:
			if(KEY_TICKED(J_LEFT)){
				loading_code = 5;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_RIGHT)){
				loading_code = 0;
			}	
		break;
		case 3:
			if(KEY_TICKED(J_DOWN)){
				loading_code = 4;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_UP) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}	
		break;
		case 2:
			if(KEY_TICKED(J_RIGHT)){
				loading_code = 3;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_UP) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}		
		break;
		case 1:
			if(KEY_TICKED(J_B)){
				loading_code = 2;
			}else if (KEY_TICKED(J_A) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_UP) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}
		break;
		case 0:
			if(KEY_TICKED(J_A)){
				loading_code = 1;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_UP) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}
		break;
	}
	
	current_camera_counter += 1u;
	switch(current_camera_counter){
		case 10u:
			SpriteManagerAdd(SpriteArrowtitle, scroll_target->x , 0);
		break;
		case 80u:
			SpriteManagerAdd(SpriteArrowtitle, scroll_target->x - 10u, 0);
		break;
		case 120u:
			SpriteManagerAdd(SpriteArrowtitle, scroll_target->x, (UINT16) 2 << 3);
		break;
		case 160u:
			SpriteManagerAdd(SpriteArrowtitle, scroll_target->x + 10u, (UINT16) 6 << 3);
		break;
		case 200u:
			SpriteManagerAdd(SpriteArrowtitle, scroll_target->x + 20u, (UINT16) 6 << 3);
		break;
		case 240u:
			SpriteManagerAdd(SpriteArrowtitle, scroll_target->x -5u, (UINT16) 10 << 3);
		break;
	}
	switch(current_camera_state){
		case 0u:
			scroll_target->x += 8u;
			if(current_camera_counter == 20u){
				//PlayMusic(bgm_titlescreen, 1);//file, loop
				PlayMusic(bgm_titlescreen, 1);
			}
			if(current_camera_counter == 62u){
				current_camera_state = 2u;
			}	
		break;
	}
	
	if(KEY_TICKED(J_SELECT)){
		StopMusic;
		SetState(StateTitlescreen);	
	}
	
	if(KEY_TICKED(J_START)){
		StopMusic;
		SetState(StateIntro);	
	}
	
	if(current_camera_state >= 2u){
		//loop wait_titlescreen up to 120
		wait_titlescreen -= 1u;
		switch (wait_titlescreen){
			case 0u:
				//PRINT(69u, 15u, "PUSH START");
				PRINT(65u, 17u, "PUSH START");	
				wait_titlescreen = 60u;
			break;
			case 30u:
				//PRINT(69u, 15u, "          ");	
				PRINT(65u, 17u, "          ");	
			break;
		}
	}
	
	
}
