#include "Banks/SetBank2.h"

#include "../res/src/tilescredit.h"
#include "../res/src/mapcredit0.h"
#include "../res/src/archer.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "gbt_player.h"

UINT8 wait_credit = 160u;
const UINT8 collision_tiles_credits[] = {1,0};
const UINT16 bg_palette_credits[] = {PALETTE_FROM_HEADER(tilescredit)};
UINT8 updatecounter = 20u;

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
	SHOW_BKG;
	
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
}

void Update_StateCredit() {
	if(wait_credit){
		wait_credit--;
	}else{
		updatecounter = 0u;
		SetState(StateGame);
	}
	
	const unsigned char h_0[1] = {14};
	const unsigned char h_1[1] = {22};
	const unsigned char v_0[1] = {15};
	const unsigned char v_1[1] = {23};
	updatecounter++;
	if (updatecounter < 20u) {
		switch(updatecounter){
			case 1:
				set_bkg_tiles(5u, 7u, 1, 1, h_0); set_bkg_tiles(6u, 7u, 1, 1, h_0); set_bkg_tiles(7u, 7u, 1, 1, h_0);
				set_bkg_tiles(8u, 7u, 1, 1, h_0); set_bkg_tiles(9u, 7u, 1, 1, h_0); set_bkg_tiles(10u, 7u, 1, 1, h_0);
				set_bkg_tiles(11u, 7u, 1, 1, h_0); set_bkg_tiles(12u, 7u, 1, 1, h_0); set_bkg_tiles(13u, 7u, 1, 1, h_0);
				set_bkg_tiles(13u, 7u, 1, 1, h_0); set_bkg_tiles(14u, 7u, 1, 1, h_0);
				set_bkg_tiles(5u, 10u, 1, 1, h_1); set_bkg_tiles(6u, 10u, 1, 1, h_1); set_bkg_tiles(7u, 10u, 1, 1, h_1);
				set_bkg_tiles(8u, 10u, 1, 1, h_1); set_bkg_tiles(9u, 10u, 1, 1, h_1); set_bkg_tiles(10u, 10u, 1, 1, h_1);
				set_bkg_tiles(11u, 10u, 1, 1, h_1); set_bkg_tiles(12u, 10u, 1, 1, h_1); set_bkg_tiles(13u, 10u, 1, 1, h_1);
				set_bkg_tiles(13u, 10u, 1, 1, h_1); set_bkg_tiles(14u, 10u, 1, 1, h_1);
				set_bkg_tiles(4u, 8u, 1, 1, v_1); set_bkg_tiles(4u, 9u, 1, 1, v_1);
				set_bkg_tiles(15u, 8u, 1, 1, v_0); set_bkg_tiles(15u, 9u, 1, 1, v_0);
			break;
			case 10:
				set_bkg_tiles(5u, 7u, 1, 1, h_1); set_bkg_tiles(6u, 7u, 1, 1, h_1); set_bkg_tiles(7u, 7u, 1, 1, h_1);
				set_bkg_tiles(8u, 7u, 1, 1, h_1); set_bkg_tiles(9u, 7u, 1, 1, h_1); set_bkg_tiles(10u, 7u, 1, 1, h_1);
				set_bkg_tiles(11u, 7u, 1, 1, h_1); set_bkg_tiles(12u, 7u, 1, 1, h_1); set_bkg_tiles(13u, 7u, 1, 1, h_1);
				set_bkg_tiles(13u, 7u, 1, 1, h_1); set_bkg_tiles(14u, 7u, 1, 1, h_1);
				set_bkg_tiles(5u, 10u, 1, 1, h_0); set_bkg_tiles(6u, 10u, 1, 1, h_0); set_bkg_tiles(7u, 10u, 1, 1, h_0);
				set_bkg_tiles(8u, 10u, 1, 1, h_0); set_bkg_tiles(9u, 10u, 1, 1, h_0); set_bkg_tiles(10u, 10u, 1, 1, h_0);
				set_bkg_tiles(11u, 10u, 1, 1, h_0); set_bkg_tiles(12u, 10u, 1, 1, h_0); set_bkg_tiles(13u, 10u, 1, 1, h_0);
				set_bkg_tiles(13u, 10u, 1, 1, h_0); set_bkg_tiles(14u, 10u, 1, 1, h_0);
				set_bkg_tiles(4u, 8u, 1, 1, v_0); set_bkg_tiles(4u, 9u, 1, 1, v_0);
				set_bkg_tiles(15u, 8u, 1, 1, v_1); set_bkg_tiles(15u, 9u, 1, 1, v_1);
			break;
		}
	}else{
		updatecounter = 0;
	}
}
