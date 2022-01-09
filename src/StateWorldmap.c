#include "Banks/SetBank14.h"

#include "../res/src/window.h"
#include "../res/src/font.h"
#include "../res/src/tilesmapworld.h"
#include "../res/src/mapworld.h"

#include "../res/src/archer.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "gbt_player.h"


#include "custom_datas.h"
#include "TileAnimations.h"
#include "Dialogs.h"
#include "sgb_palette.h"

extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern UINT8 current_level;
extern UINT16 sprites_palette[];

const UINT8 const collision_tiles_worldmap[] = {0, 0};
const UINT16 const bg_palette_worldmap[] = {PALETTE_FROM_HEADER(tilesmapworld)};
const struct MapInfo* const mapworld_0[] = {
	&mapworld
};
const struct MapInfo** const mapworld_levels[] = {mapworld_0};

UINT8 counter = 0;

void Start_StateWorldmap() {
		
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 7); //last param is the current bank we are in
	SetPalette(BG_PALETTE, 0, 8, bg_palette_worldmap, 14); //last param is the current bank we are in

	SPRITES_8x16;
	if(sgb_check()){
		set_sgb_palette01_4B();
		set_sgb_palette_statusbar();
	}
	SHOW_SPRITES;
	
	//CLEAN DIAGS
	memcpy(d1, "                    ", 20);
	memcpy(d2, "                    ", 20);
	memcpy(d3, "                    ", 20);
	memcpy(d4, "                    ", 20);

	const struct MapInfo** mapworlds = mapworld_levels[0];
	InitScroll(mapworlds[0], collision_tiles_worldmap, 0);
	SHOW_BKG;

}

void Update_StateWorldmap(){
	counter++;
	if(counter == 0){
		if(current_level < 3){
			SetState(StateGame);
		}else if (current_level < 5){
			SetState(StateGame3);
		}else{
			SetState(StateGame6);
		}
	}
}