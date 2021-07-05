#include "Banks/SetBank8.h"

#include <stdbool.h>

#include "../res/src/font.h"
#include "../res/src/diagnew.h"
#include "../res/src/mapdiagarcher.h"
#include "../res/src/diagarcher.h"

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

const UINT16 bg_paletted[] = {PALETTE_FROM_HEADER(diagarcher)};
const UINT8 const collision_dtiles[] = {0,0};

const struct MapInfo* const diagplayer[] = {
	&mapdiagarcher
};

const struct MapInfo** const diagmaps[] = {0, diagplayer};

void Start_StateDiag() {
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_paletted, 2);
	
	SPRITES_8x16;
	SHOW_SPRITES;	
	
	UINT8 n = Build_Next_Dialog_Banked(0);
	const struct MapInfo** diag_maps = diagmaps[n];
	InitScroll(&mapdiagarcher, collision_dtiles, 0);
	SHOW_BKG;
	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 48; //40
	InitWindow(0, 0, &diagnew);
	SHOW_WIN;
	
	PRINT_POS(1,1);
	Printf(d1);
	PRINT_POS(1,2);
	Printf(d2);
	PRINT_POS(1,3);
	Printf(d3);
	PRINT_POS(1,4);
	Printf(d4);
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
}

void Update_StateDiag() {
	
	if(KEY_PRESSED(J_B)) {
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