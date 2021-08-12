#include "Banks/SetBank2.h"

#include "../res/src/tilescredit.h"
#include "../res/src/mapcredit0.h"
#include "../res/src/mapcredits1.h"
#include "../res/src/mapcredits2.h"
#include "../res/src/mapcredits3.h"
#include "../res/src/mapcredits4.h"
#include "../res/src/archer.h"

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

UINT8 wait_credit = 250u;
const UINT8 collision_tiles_credits[] = {1,0};
const UINT16 bg_palette_credits[] = {PALETTE_FROM_HEADER(tilescredit)};
UINT8 updatecounter = 20u;
extern UINT8* credits_mod_Data[];
UINT8 credit_step = 0u;

const UINT16 sprites_palette_credits[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

void Start_StateCredit() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_credits, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette_credits, 2);
	SPRITES_8x16;
	SHOW_SPRITES;
	InitScroll(&mapcredit0, collision_tiles_credits, 0);	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	PlayMusic(credits_mod_Data, 11, 1);
	
	SHOW_BKG;
	
}

void Update_StateCredit() {
	
	if(credit_step == 0u){
		updatecounter++;
		if (updatecounter < 20u) {
			switch(updatecounter){
				case 1u:
					set_bkg_data(14u, 1u, tilescredit.data->data+352u);// 16 * 22 tile index
					set_bkg_data(15u, 1u, tilescredit.data->data+368u);// 16 * 22 tile index
				break;
				case 10u:
					set_bkg_data(14u, 1u, tilescredit.data->data+224u);// restore tile
					set_bkg_data(15u, 1u, tilescredit.data->data+240u);// restore tile
				break;
			}
		}else{
			updatecounter = 0;
		}
		
	}
	
	if(KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_START) || wait_credit == 0u){
		updatecounter = 0u;
		wait_credit = 250u;
		credit_step += 1u;
		FadeIn();
		DISPLAY_OFF;
		BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, 1, 2, 3);
		switch (credit_step){
			case 1u:
				InitScroll(&mapcredits2, collision_tiles_credits, 0);
			break;
			case 2u:
				InitScroll(&mapcredits4, collision_tiles_credits, 0);
			break;
			case 3u:
				InitScroll(&mapcredits3, collision_tiles_credits, 0);
			break;
			case 4u:
				InitScroll(&mapcredits1, collision_tiles_credits, 0);
			break;
			default:
				DISPLAY_ON;
				FadeOut();
				SetState(StateGame); // TitleScreen !
			break;
		}
		DISPLAY_ON;
		FadeOut();
		return;
	}
	
	wait_credit--;
	
}
