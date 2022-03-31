#include "Banks/SetAutoBank.h"

#include <gb/gb.h>

#include "ZGBMain.h"
#include "Keys.h"
#include "Palette.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Music.h"
#include "Fade.h"

#include "custom_datas.h"
#include "sgb_palette.h"

IMPORT_TILES(tilesintro);

IMPORT_MAP(mapintro);

DECLARE_MUSIC(intro);

extern UINT16 sprites_palette_titlescreen[];
extern UINT8 current_camera_state; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
extern UINT8 current_camera_counter;


void START() {	

	current_camera_state = 0u;
	current_camera_counter = 0u;
	
	if(sgb_check()){
		set_sgb_palette01_intro();
	}
	scroll_bottom_movement_limit = 36u;
	
	SpriteManagerLoad(SpriteCamerafocus);
	SHOW_SPRITES;
	
	//SOUND
	PlayMusic(intro, 1);//file, bank, loop
	//PlayMusic(higher, 1);//file, bank, loop
	UINT8 default_collision_tiles[] = {1,0};
	InitScroll(BANK(mapintro), &mapintro, default_collision_tiles, 0);
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, (UINT16) 10u << 3, (UINT16) 4u << 3);
	
	SHOW_BKG;
	
}

void UPDATE() {	

	if(scroll_target-> y < ((UINT16) 5u << 3)){
		scroll_target-> y = (UINT16) 5u << 3;
		return;
	}
	if(scroll_target-> y > ((UINT16) 102u << 3)){
		scroll_target-> y = (UINT16) 102u << 3;
		return;
	}
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
	if(KEY_TICKED(J_SELECT)){
		SetState(StateIntro);
	}	
	if(KEY_TICKED(J_START)){
		SetState(StateWorldmap);	
	}	
}

