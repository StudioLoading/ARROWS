#include "Banks/SetBank13.h"

#include "../res/src/diaggameover.h"
#include "../res/src/mapdiaggameover.h"
#include "../res/src/font.h"
#include "../res/src/windowpushstart.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Fade.h"

const UINT16 bg_palette_gameover[] = {PALETTE_FROM_HEADER(diaggameover)};
INT8 countdown = 10;
INT8 one_second = 0;

void ResetConfig();
void ShowContinue();
void ShowCounter();

extern INT8 is_on_boss;
extern UINT8 current_level_b;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 archer_tool;
extern INT8 level_tool;
extern INT8 load_next_b;

void Start_StateGameOver() {

	SetPalette(BG_PALETTE, 0, 8, bg_palette_gameover, 13);//end with the bank of where I have the palette/tileset

	HIDE_WIN;
	InitScroll(&mapdiaggameover, 0, 0);
	SHOW_BKG;
	
	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowContinue();
	
	ResetConfig();
	
}

void Update_StateGameOver() {
	one_second++;
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(StateGame);
	}else if (one_second >= 70){
		one_second = 0;
		ShowContinue();
	}
}

void ShowContinue(){
	WX_REG = 4u;
	WY_REG = 136u;
	countdown--;
	InitWindow(0, 0, &windowpushstart);
	ShowCounter();
	SHOW_WIN;
}

void ShowCounter(){
	if(countdown >= -1){
		PRINT_POS(0,0);
		if(countdown != -1){
			Printf("      CONTINUE ? 0%d     ", countdown);	
		}
	}else if (countdown == -2){
		GameOver();
		SetState(StateTitlescreen);
	}
}

void GameOver(){
	load_next_b = 0;
	is_on_boss = -1;
	current_level = 0u;
	current_map = 0u;
	current_level_b = current_level -1u;
	archer_tool = 0;
	level_tool= -1;
	countdown = 10;
	one_second = 0;
	
}

void ResetConfig(){
	load_next_b = 0;
	is_on_boss = -1;
	current_map = 0u;
	current_level_b = current_level -1u;
	archer_tool = 0;
	level_tool= -1;
	countdown = 10;
	one_second = 0;
}