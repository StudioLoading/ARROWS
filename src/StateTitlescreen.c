#include "Banks/SetBank3.h"

#include "../res/src/tilestitlescreen.h"
#include "../res/src/maptitlescreen.h"
#include "../res/src/archer.h"
#include "../res/src/logo.h"

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

struct Sprite* sprite_logo_0;
struct Sprite* sprite_logo_1;
struct Sprite* sprite_logo_2;

UINT8 wait_titlescreen = 255U;

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

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_titlescreen, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette_titlescreen, 2);
	
	SPRITES_8x16;
	//SPRITES_32x32;
	SpriteManagerLoad(SpriteLogo);
	//scroll_target = SpriteManagerAdd(SpriteLogo, 0, 0);
	SHOW_SPRITES;
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//PlayMusic(credits_mod_Data, 11, 1);
	
	InitScroll(&maptitlescreen, collision_tiles_titlescreen, 0);	
	SHOW_BKG;
	
}

void Update_StateTitlescreen() {	
			
	switch(wait_titlescreen){
		case 255u:
			sprite_logo_0 = SpriteManagerAdd(SpriteLogo, 0, 0);
			struct LogoInfo* logo_data = (struct LogoInfo*)sprite_logo_0->custom_data;
			logo_data->frame = 0;
			logo_data->setup = 1;
		break;
		case 254u:
			sprite_logo_1 = SpriteManagerAdd(SpriteLogo, (UINT16) 4u << 3, 0);
			struct LogoInfo* logo_data_1 = (struct LogoInfo*)sprite_logo_1->custom_data;
			logo_data_1->frame = 1;
			logo_data_1->setup = 1;
		break;
		case 253u:
			sprite_logo_2 = SpriteManagerAdd(SpriteLogo,  (UINT16) 8u << 3, 0);
			struct LogoInfo* logo_data_2 = (struct LogoInfo*)sprite_logo_2->custom_data;
			logo_data_2->frame = 2;
			logo_data_2->setup = 1;
		break;
	}
	
	if(KEY_TICKED(J_START)){
		SetState(StateGame);	
	}
	
	if(wait_titlescreen > 252u){
		wait_titlescreen -= 1u;
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
