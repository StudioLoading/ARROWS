#include "Banks/SetAutoBank.h"

#include "..\include\ZGBMain.h"
#include "Keys.h"
#include "Palette.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "Fade.h"

#include "sgb_palette.h"

IMPORT_MAP(mapdiaggameover);

IMPORT_TILES(font);

const UINT8 collision_tiles_gameover[] = {1,0};
INT8 countdown;
INT8 one_second;

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

void START() {

	HIDE_WIN;

	SpriteManagerLoad(SpriteCamerafocus);
	if(sgb_check()){
		set_sgb_palette01_2H();
	}
	SHOW_SPRITES;
	
	INIT_FONT(font, PRINT_BKG); 

	current_map = 0u;
	countdown = 10;
	one_second = 0;
	
	InitScroll( (UINT8) BANK(mapdiaggameover), &mapdiaggameover, collision_tiles_gameover, 0);	
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, 9u << 3, 8u << 3);
	SHOW_BKG;
	
}

void UPDATE() {
	if( scroll_target->y < (UINT16) 35u << 3){ //countdown <= 9 &&
		scroll_target->y += 2;
		return;
	}
	one_second++;
	if (one_second >= 90){
		one_second = 0;
		ShowContinue();
	}
	if(KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
		ResetConfig(0);		
	}	
}

void ShowContinue(){
	countdown--;
	if(countdown > -1){
		PRINT(6u, 39u, "CONTINUE? 0");
		unsigned char str[] = "0";
		UIntToString(countdown, str);
		PRINT(17u, 39u, str);
	}else if (countdown == -2){
		ResetConfig(1);
	}
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
