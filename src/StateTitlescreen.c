#include "Banks/SetBank7.h"

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

const UINT8 collision_tiles_titlescreen[] = {1,0};
const UINT16 bg_palette_titlescreen[] = {PALETTE_FROM_HEADER(tilestitlescreen)};

UINT8 wait_titlescreen = 255U;

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

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_titlescreen, 2); //end with the bank of where I have the palette/tileset
	SetPalette(BG_PALETTE, 0, 8, bg_palette_titlescreen, 7);//end with the bank of where I have the palette/tileset
	
	SPRITES_8x16;
	SHOW_SPRITES;
	
	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowPushStart();
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//PlayMusic(credits_mod_Data, 11, 1);
	
	InitScroll(&maptitlescreen, collision_tiles_titlescreen, 0);	
	SHOW_BKG;
	
}

void Update_StateTitlescreen() {	
			
	if(KEY_TICKED(J_START)){
		SetState(StateGame);	
	}
	
	if(wait_titlescreen > 252u){
		wait_titlescreen -= 1u;
	}else{
		if (wait_titlescreen > 60u){
			wait_titlescreen = 50u;
		}
		//loop wait_titlescreen up to 120
		wait_titlescreen -= 1u;
		if (wait_titlescreen == 0u){
			wait_titlescreen = 60u;
			return;
		}
		if(wait_titlescreen == 30u){
			HIDE_WIN;
		}else if(wait_titlescreen == 59u){
			SHOW_WIN;
		}	
		
	}
	/*
		FadeIn();
		DISPLAY_OFF;
		BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, 1, 2, 3);
		switch (credit_step){
			case 1u:
				InitScroll(&mapcredits2, collision_tiles_titlescreen, 0);
			break;
			case 2u:
				InitScroll(&mapcredits4, collision_tiles_titlescreen, 0);
			break;
			case 3u:
				InitScroll(&mapcredits3, collision_tiles_titlescreen, 0);
			break;
			case 4u:
				InitScroll(&mapcredits1, collision_tiles_titlescreen, 0);
			break;
		}
		DISPLAY_ON;
		FadeOut();
		return;
	}*/
	
}

void ShowPushStart(){
	WX_REG = 4u;
	WY_REG = 136u;
	InitWindow(0, 0, &windowpushstart);
	PRINT_POS(0,0);
	Printf("      PUSH START     ");
	SHOW_WIN;
}
