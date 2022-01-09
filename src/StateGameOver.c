#include "Banks/SetBank4.h"

#include "../res/src/diaggameover.h"
#include "../res/src/mapdiaggameover.h"
#include "../res/src/font.h"
#include "../res/src/archer.h"
#include "../res/src/windowpushstart.h"

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

const UINT8 collision_tiles_gameover[] = {1,0};
const UINT16 bg_palette_gameover[] = {PALETTE_FROM_HEADER(diaggameover)};
const UINT16 sprites_palette_gameover[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};
INT8 countdown = 10;
INT8 one_second = 0;

void ResetConfig(INT8 gameo);
void ShowContinue();

extern INT8 is_on_boss;
extern INT8 is_on_gameover;
extern UINT8 current_level;
extern UINT8 current_level_b;
extern UINT8 current_map;
extern UINT8 amulet;
extern UINT8 coins;
extern INT8 ups;
extern INT8 hp;
extern INT8 archer_tool;
extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

void Start_StateGameover() {

	SetPalette(BG_PALETTE, 0, 8, bg_palette_gameover, 4);//end with the bank of where I have the palette/tileset
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette_gameover, 4); //end with the bank of where I have the palette/tileset
	
	HIDE_WIN;
		
	SPRITES_8x16;	
	SpriteManagerLoad(SpriteCamerafocus);
	SHOW_SPRITES;
	
	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	current_map = 0u;
	countdown = 10;
	one_second = 0;
	ShowContinue();
	
	InitScroll(&mapdiaggameover, collision_tiles_gameover, 0);	
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, 9u << 3, 8u << 3);
	SHOW_BKG;
	
}

void Update_StateGameover() {
	if(countdown <= 9 && scroll_target->y < (UINT16) 30u << 3){
		scroll_target->y += 2;
	}
	one_second++;
	if (one_second >= 70){
		one_second = 0;
		ShowContinue();
	}
	if(KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
		ResetConfig(0);		
	}	
}

void ShowContinue(){
	WX_REG = 4u;
	WY_REG = 136u;
	countdown--;
	InitWindow(0, 0, &windowpushstart);
	if(countdown >= -1){
		PRINT_POS(5,0);
		if(countdown != -1){
			Printf(" CONTINUE ? 0%d    ", countdown);	
		}
	}else if (countdown == -2){
		ResetConfig(1);
	}
	SHOW_WIN;
}

void ResetConfig(INT8 gameo){		
	is_on_gameover = -1;
	hp = MAX_HP;
	ups = 3;
	coins = 0;
	archer_tool = 0;
	if(gameo > 0){
		current_level_b = 0u;
		current_level = 0u;
		is_on_boss = -1;
		SetState(StateTitlescreen);
	}else{
		if(is_on_boss > 0){
			if(current_level > 0u){
				current_level_b = current_level -1u;
			}
			SetState(StateBoss);	
		}else{
			SetState(StateWorldmap);			
		}
	}		
}
