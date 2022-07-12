#include "Banks/SetAutoBank.h"

#include "SGB.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Palette.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "string.h"
#include "Print.h"
//#include "Sound.h"
#include "Fade.h"
#include "Music.h"

#include "sgb_palette.h"

IMPORT_TILES(tilescredit);
IMPORT_TILES(tilescredit2);
IMPORT_TILES(tilescredit3);
IMPORT_TILES(tilescredit4);

IMPORT_MAP(border);

IMPORT_MAP(mapcredit0);
IMPORT_MAP(mapcredits1);
IMPORT_MAP(mapcredits2);
IMPORT_MAP(mapcredits3);
IMPORT_MAP(mapcredits4);

//DECLARE_MUSIC(bgm_credits);
DECLARE_MUSIC(bgm_credits);

const UINT8 collision_tiles_credits[] = {1,0};
UINT8 updatecounter;
UINT8 credit_step;
UINT8 wait_time;
UINT8 on_worldmap;
UINT8 colliding_mother;

void START() {
	LOAD_SGB_BORDER(border);
	credit_step = 0u;
	wait_time = 0u;
	on_worldmap = 0;
	colliding_mother = 0u;
	InitScroll(BANK(mapcredit0), &mapcredit0, collision_tiles_credits, 0);	
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//NR50_REG = 0x44; //Max volume 0x77
	PlayMusic(bgm_credits, 0);

	SHOW_BKG;
	
}

void UPDATE() {
	wait_time += 1u;
	UINT8 cb = 0;
	if(KEY_TICKED(J_START)){
		SetState(StateTitlescreen);
		return;
	}else if(KEY_TICKED(J_B) || KEY_TICKED(J_A) || wait_time == 106u){
		wait_time = 0u;
		credit_step += 1u;
		if(credit_step == 5u){
			SetState(StateTitlescreen);
			return;
		}
		FadeIn();
		DISPLAY_OFF;
		if(sgb_check()){
			BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, 1, 2, 3);
		}
		switch (credit_step){
			case 1u:
				if(sgb_check()){
					set_sgb_palette01_WOLF();
				}
				InitScroll(BANK(mapcredits2), &mapcredits2, collision_tiles_credits, 0); // music of the Misty Hills
			break;
			case 2u:
				if(sgb_check()){
					set_sgb_palette01_COMUNEKO();
				}
				InitScroll(BANK(mapcredits4), &mapcredits4, collision_tiles_credits, 0); // comuneko
			break;
			case 3u:
				if(sgb_check()){
					set_sgb_palette01_2H();
				}
				InitScroll(BANK(mapcredits3), &mapcredits3, collision_tiles_credits, 0); // powered by ZGB
			break;
			case 4u:
				if(sgb_check()){
					set_sgb_palette01_1A();
				}
				InitScroll(BANK(mapcredits1), &mapcredits1, collision_tiles_credits, 0); //special thanks
			break;
		}
		DISPLAY_ON;
		FadeOut();
		return;
	}
		
}
