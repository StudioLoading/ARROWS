#include "Banks/SetBank6.h"

#include "../res/src/tilestitlescreen.h"
#include "../res/src/maptitlescreen.h"
#include "../res/src/archer.h"
#include "../res/src/font.h"
#include "../res/src/windowpushstart.h"


#include <gb/gb.h>

#include "ZGBMain.h"
#include "Keys.h"
#include "Palette.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Fade.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "sgb_palette.h"

extern UINT8* titlescreen_mod_Data[];
extern UINT8 quiver;// = 0b0000000001;
extern UINT8 current_camera_counter;

extern UINT8 amulet;
extern UINT8 coins;
extern INT8 ups;
extern INT8 hp;
extern INT8 archer_tool;
extern INT8 level_tool;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

const UINT8 collision_tiles_titlescreen[] = {1,0};
const UINT16 bg_palette_titlescreen[] = {PALETTE_FROM_HEADER(tilestitlescreen)};

UINT8 current_camera_state = 0u; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
UINT8 wait_titlescreen = 0u;
INT8 loading_code = 0;

void ShowPushStart();

const UINT16 sprites_palette_titlescreen[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

void Start_StateTitlescreen() {	
	
	current_camera_state = 0u;
	current_camera_counter = 0u;
	
	amulet = 0;
    coins = 30u;
	ups = 0;
	hp = MAX_HP;
	archer_tool = 0;
	level_tool = -1;
	
	if(sgb_check()){
		set_sgb_palette01_2A();
		set_sgb_palette_title();
	}

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_titlescreen, 6); //end with the bank of where I have the palette/tileset
	SetPalette(BG_PALETTE, 0, 8, bg_palette_titlescreen, 6);//end with the bank of where I have the palette/tileset
	
	SPRITES_8x16;	
	SpriteManagerLoad(SpriteCamerafocus);
	SpriteManagerLoad(SpriteArrowtitle);
	SHOW_SPRITES;
	
	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowPushStart();     
	
	//SOUND
	NR50_REG = 0x30;
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//PlayMusic(titlescreen_mod_Data, 12, 1);//file, bank, loop	

	InitScroll(&maptitlescreen, collision_tiles_titlescreen, 0);	
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, 9u << 3, 8u << 3);
	SHOW_BKG;
	
}

void Update_StateTitlescreen() {	

	switch(loading_code){
		case 5:
			if(KEY_TICKED(J_UP)){
				quiver = 0b0000011111;
				NR50_REG = 0x77;
				PlayFx(CHANNEL_1, 60, 0x46, 0xC2, 0x43, 0x68, 0x86);
				PlayFx(CHANNEL_1, 60, 0x46, 0xC2, 0x43, 0x68, 0x86);
				PlayFx(CHANNEL_1, 60, 0x46, 0xC2, 0x43, 0x68, 0x86);
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
			if(KEY_TICKED(J_A)){
				loading_code = 2;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_UP) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}
		break;
		case 0:
			if(KEY_TICKED(J_B)){
				loading_code = 1;
			}else if (KEY_TICKED(J_A) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_UP) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT)){
				loading_code = 0;
			}
		break;
	}
	
	switch(current_camera_state){
		case 0u:
			current_camera_counter += 1u;
			scroll_target->x += 8;
			if(current_camera_counter == 62u){
				current_camera_state = 2u;
			}	
		break;
	}
	
	if(KEY_TICKED(J_SELECT)){
		SetState(StateTitlescreen);	
	}
	
	if(KEY_TICKED(J_START)){
		SetState(StateIntro);	
	}
	
	if(current_camera_state >= 2u){
		//loop wait_titlescreen up to 120
		wait_titlescreen -= 1u;
		switch (wait_titlescreen){
			case 0u:
			case 60u:
			case 120u:
			case 180u:
				SHOW_WIN;
			break;
			case 30u:
			case 90u:
			case 160u:
			case 210u:
				HIDE_WIN;
			break;
		}
		current_camera_counter += 1u;
		switch(current_camera_counter){
			case 20u:
				SpriteManagerAdd(SpriteArrowtitle, (UINT16) 82 << 3, (UINT16) 0 << 3);
			break;
			case 80u:
				SpriteManagerAdd(SpriteArrowtitle, (UINT16) 68 << 3, (UINT16) 0 << 3);
			break;
			case 160u:
				SpriteManagerAdd(SpriteArrowtitle, (UINT16) 80 << 3, (UINT16) 6 << 3);
			break;
			case 200u:
				SpriteManagerAdd(SpriteArrowtitle, (UINT16) 70 << 3, (UINT16) 6 << 3);
			break;
			case 240u:
				SpriteManagerAdd(SpriteArrowtitle, (UINT16) 72 << 3, (UINT16) 10 << 3);
			break;
		}
	}
	
}

void ShowPushStart(){
	WX_REG = 4u;
	WY_REG = 136u;
	InitWindow(0, 0, &windowpushstart);
	PRINT_POS(0,0);
	Printf("      PUSH START     ");
	SHOW_WIN;
}
