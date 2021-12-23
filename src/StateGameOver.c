#include "Banks/SetBank7.h"

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

void ResetConfig(INT8 gameo);
void ShowContinue();
void ShowCounter();

extern INT8 is_on_boss;
extern INT8 is_on_gameover;
extern UINT8 current_level_b;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 archer_tool;
extern INT8 level_tool;
extern INT8 load_next_b;

void Start_StateGameOver() {

	SetPalette(BG_PALETTE, 0, 8, bg_palette_gameover, 7);//end with the bank of where I have the palette/tileset

	HIDE_WIN;
	InitScroll(&mapdiaggameover, 0, 0);
	SHOW_BKG;
	
	//WINDOW	
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	is_on_gameover = 1;
	ResetConfig(0);
	ShowContinue();
	
}

void Update_StateGameOver() {
	one_second++;
	if (one_second >= 70){
		one_second = 0;
		ShowContinue();
	}
	if(KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
		if(is_on_boss > 0){
			SetState(StateBoss);
		}else{
			SetState(StateGame);
		}
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
		PRINT_POS(1,0);
		Printf("%d %d", current_level, current_map);
		PRINT_POS(5,0);
		if(countdown != -1){
			Printf(" CONTINUE ? 0%d    ", countdown);	
		}
	}else if (countdown == -2){
		ResetConfig(1);
		SetState(StateTitlescreen);
	}
}

void ResetConfig(INT8 gameo){
	load_next_b = 0;
	current_map = 0u;
	if(gameo > 0){
		current_level = 0u;
		is_on_boss = -1;
	}
	if(is_on_boss > 0){
		current_level_b = 0u;
		if(current_level > 0u){
			current_level_b = current_level -1u;
		}
	}
	archer_tool = 0;
	level_tool= -1;
	countdown = 10;
	one_second = 0;
}