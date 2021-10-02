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
	
	if(sgb_check()){
		set_sgb_palette01_2A();
	}

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_titlescreen, 2); //end with the bank of where I have the palette/tileset
	SetPalette(BG_PALETTE, 0, 8, bg_palette_titlescreen, 7);//end with the bank of where I have the palette/tileset
	
	SPRITES_8x16;	
	SpriteManagerLoad(SpriteCamerafocus);
	SpriteManagerLoad(SpriteArrowtitle);
	SHOW_SPRITES;
	
	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowPushStart();     
	
	//SOUND
	NR52_REG = 0x50; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//PlayMusic(titlescreen_mod_Data, 12, 1);//file, bank, loop	

	InitScroll(&maptitlescreen, collision_tiles_titlescreen, 0);	
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, 9u << 3, 8u << 3);
	SHOW_BKG;
	
}

void Update_StateTitlescreen() {	

	switch(loading_code){
		case 6:
			if(KEY_TICKED(J_START)){
				quiver = 0b0000011111;
				loading_code = 7;
			}else if (KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_DOWN) || KEY_TICKED(J_RIGHT) || KEY_TICKED(J_LEFT) || KEY_TICKED(J_UP)){
				loading_code = 0;
			}	
		break;
		case 5:
			if(KEY_TICKED(J_UP)){
				loading_code = 6;
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
		SetState(StateGame);	
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
		if(current_camera_state <= 4u){
			if (current_camera_counter == 120u){
				current_camera_state++;
			}
		}else{		
			switch(current_camera_counter){
				case 80u:
					SpriteManagerAdd(SpriteArrowtitle, (UINT16) 70 << 3, (UINT16) 0 << 3);
				break;
				case 160u:
					SpriteManagerAdd(SpriteArrowtitle, (UINT16) 80 << 3, (UINT16) 6 << 3);
				break;
				case 200u:
					SpriteManagerAdd(SpriteArrowtitle, (UINT16) 70 << 3, (UINT16) 6 << 3);
				break;
				case 240u:
					SpriteManagerAdd(SpriteArrowtitle, (UINT16) 75 << 3, (UINT16) 10 << 3);
				break;
			}	
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
