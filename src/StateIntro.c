#include "Banks/SetBank13.h"

#include "../res/src/tilesintro.h"
#include "../res/src/mapintro.h"
#include "../res/src/archer.h"
#include "../res/src/font.h"

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


const UINT16 bg_palette_intro[] = {PALETTE_FROM_HEADER(tilesintro)};
const UINT8 collision_tiles_intro[] = {1,0};

extern UINT8* intro_mod_Data[]; 
extern UINT8 current_camera_state; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
extern UINT8 current_camera_counter;


const UINT16 sprites_palette_intro[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

void Start_StateIntro() {	
	
	current_camera_state = 0u;
	current_camera_counter = 0u;
	
	if(sgb_check()){
		set_sgb_palette01_2A();
	}

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_titlescreen, 2); //end with the bank of where I have the palette/tileset
	SetPalette(BG_PALETTE, 0, 8, bg_palette_intro, 14);//end with the bank of where I have the palette/tileset	
	SPRITES_8x16;	
	SpriteManagerLoad(SpriteCamerafocus);
	SHOW_SPRITES;

	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	HIDE_WIN;
	
	//SOUND
	NR52_REG = 0x50; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//PlayMusic(intro_mod_Data, 12, 1);//file, bank, loop	

	InitScroll(&mapintro, collision_tiles_intro, 14);//map pointer, collision array, tile bank
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, (UINT16) 10u << 3, (UINT16) 12u << 3);	
	SHOW_BKG;
	
}

void Update_StateIntro() {	

	if(scroll_target-> y < ((UINT16) 195u << 3) && scroll_target-> y > ((UINT16) 5u << 3)){
		current_camera_counter++;	
		switch(current_camera_counter){
			case 0u:
			case 20u:
			case 40u:
			case 60u:
			case 80u:
			case 100u:
			case 120u:
			case 140u:
			case 160u:
			case 180u:
			case 200u:
			case 220u:
			case 240u:
				scroll_target->y += 2;
			break;
		}	
		if(KEY_PRESSED(J_A)){
			scroll_target->y++;
		}
		if(KEY_PRESSED(J_DOWN)){
			scroll_target->y++;
		}
		if(KEY_PRESSED(J_B)){
			scroll_target->y--;			
		}
		if(KEY_PRESSED(J_UP)){
			scroll_target->y--;
		}
	}
	if(KEY_TICKED(J_SELECT)){
		SetState(StateIntro);
	}
	
	if(KEY_TICKED(J_START)){
		SetState(StateGame);	
	}

	
}

