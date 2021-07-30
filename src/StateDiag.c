#include "Banks/SetBank8.h"

#include <stdbool.h>

#include "../res/src/font.h"
#include "../res/src/diagnew.h"

#include "../res/src/mapdiagarcher1.h"
#include "../res/src/mapdiagslave1.h"
#include "../res/src/mapdiagslave2.h"
#include "../res/src/mapdiagslave3.h"
#include "../res/src/mapdiagkey.h"
#include "../res/src/mapdiagwrench.h"
#include "../res/src/mapdiagwolf.h"
#include "../res/src/mapdiagcave.h"
#include "../res/src/mapdiaggator.h"
#include "../res/src/mapdiageagle.h"
#include "../res/src/mapdiagibex.h"
#include "../res/src/mapdiagbear.h"


#include "../res/src/mapdiagamuletstone.h"

#include "../res/src/diagarcher1.h"
#include "../res/src/diagslave1.h"
#include "../res/src/diagslave2.h"
#include "../res/src/diagslave3.h"
#include "../res/src/diagkey.h"
#include "../res/src/diagwrench.h"
#include "../res/src/diagwolf.h"
#include "../res/src/diagcave.h"
#include "../res/src/diaggator.h"
#include "../res/src/diageagle.h"
#include "../res/src/diagibex.h"
#include "../res/src/diagbear.h"

#include "../res/src/diagamuletstone.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "Dialogs.h"

extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT16 drop_player_x;
extern UINT16 drop_player_y;

extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_boss;

extern INT8 show_diag;
extern INT8 showing_diag;

extern struct Sprite* enemies_0;
extern struct Sprite* enemies_1;
extern struct Sprite* enemies_2;
extern struct Sprite* enemies_3;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];

extern UINT8 diag_found;

const UINT16 bg_paletted[] = {PALETTE_FROM_HEADER(diagarcher1)};
const UINT8 const collision_dtiles[] = {0,0};


void Start_StateDiag() {
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_paletted, 2);
	
	SPRITES_8x16;
	SHOW_SPRITES;	
	
	switch(diag_found){
		case 0u:
		case 1u:
		case 2u:
		case 3u:
			InitScroll(&mapdiagarcher1, collision_dtiles, 0);
		break;
		case 4u:
			InitScroll(&mapdiagslave1, collision_dtiles, 0);
		break;
		case 5u:
			InitScroll(&mapdiagslave2, collision_dtiles, 0);
		break;
		case 6u:
			InitScroll(&mapdiagslave3, collision_dtiles, 0);
		break;
		case 19u:
			InitScroll(&mapdiagcave, collision_dtiles, 0);
		break;
		case 20u:
			InitScroll(&mapdiagwrench, collision_dtiles, 0);
		break;
		case 21u:
			InitScroll(&mapdiagkey, collision_dtiles, 0);
		break;
		case 30u:
			InitScroll(&mapdiagamuletstone, collision_dtiles, 0);
		break;
		case 51u:
			InitScroll(&mapdiagwolf, collision_dtiles, 0);
		break;
		case 52u:
			InitScroll(&mapdiaggator, collision_dtiles, 0);
		break;
		case 53u:
			InitScroll(&mapdiageagle, collision_dtiles, 0);
		break;
		case 54u:
			InitScroll(&mapdiagibex, collision_dtiles, 0);
		break;
		case 55u:
			InitScroll(&mapdiagbear, collision_dtiles, 0);
		break;
	}
	SHOW_BKG;
	
	HIDE_WIN;

	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 3, 4);
	
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 40; //40
	InitWindow(0, 0, &diagnew);
	SHOW_WIN;
	
	PRINT_POS(1,0);
	Printf(d1);
	PRINT_POS(1,1);
	Printf(d2);
	PRINT_POS(1,2);
	Printf(d3);
	PRINT_POS(1,3);
	Printf(d4);
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
}

void Update_StateDiag() {
	
	if(KEY_PRESSED(J_B)) {
		HIDE_WIN;
		if(is_on_boss >= 0){
			SetState(StateBoss);
		}else{
			switch(current_level){
				case 0u:
				case 1u:
				case 2u:
				case 3u:
					SetState(StateGame);
				break;
				case 4u:
				case 5u:
				case 6u:
				case 7u:
					SetState(StateGame4);
				break;
			}
		}
	}

}