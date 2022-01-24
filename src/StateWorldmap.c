#include "Banks/SetBank14.h"

#include "../res/src/font.h"
#include "../res/src/tilesmapworld.h"
#include "../res/src/mapworld.h"

#include "../res/src/iconpsg.h"
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
struct Sprite* siconpsg;
struct ItemInfo* dataiconpsg;

void Start_StateWorldmap() {

	HIDE_WIN;
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 7); //last param is the current bank we are in
	SetPalette(BG_PALETTE, 0, 8, bg_palette_worldmap, 14); //last param is the current bank we are in
	SpriteManagerLoad(SpriteIconpsg);
	
	if(sgb_check()){
		set_sgb_palette01_worldmap();
		//reset_sgb_palette_statusbar();
	}
	
	
	SPRITES_8x16;
	
	switch(current_level){
		case 0u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, (UINT16) 9u, (UINT16) 81u);
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=11;
			dataiconpsg->setup=1u;
		break;
		case 1u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, ((UINT16) 9u), (UINT16) 81u);	dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=1;
			dataiconpsg->setup=1u;
		break;
		case 2u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, ((UINT16) 9u) + 23u, (UINT16) 81u);		
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=1;
			dataiconpsg->setup=1u;
		break;
		case 3u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, ((UINT16) 9u) + 46u, (UINT16) 81u);		
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=1;
			dataiconpsg->setup=1u;
		break;
		case 4u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, ((UINT16) 9u) + 69u, (UINT16) 81u);		
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=1;
			dataiconpsg->setup=1u;
		break;
		case 5u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, (UINT16) 48u, (UINT16) 120u);
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=1;
			dataiconpsg->setup=1u;
		break;
		case 6u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, (UINT16) 73u, (UINT16) 120u);
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=1;
			dataiconpsg->setup=1u;
		break;
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
	switch(current_level){ // spostamento orizzontale da un punto all' altro di 25u
		//case 0u: ho appena iniziato , non faccio niente
		case 1u:
			if(counter > 80u && siconpsg->x < 32u && (counter & 1)){
				siconpsg->x++;
			}
		break;
		case 2u:
			if(counter > 80u && siconpsg->x < 57u && (counter & 1)){
				siconpsg->x++;
			}
		break;
		case 3u:
			if (counter == 10u) {
				WorldmapQuiverStone();
			}
			if(counter > 80u && siconpsg->x < 82u && (counter & 1)){
				siconpsg->x++;
			}
		break;
		case 4u:
			if(counter > 80u && siconpsg->x > 48u && (counter & 1)){
				siconpsg->x-=2;
			}
			if(counter > 80u && siconpsg->y < 120u && (counter & 1)){
				siconpsg->y += 2;
			}
		break;
		case 5u:
			if(counter > 80u && siconpsg->x < 73u && (counter & 1)){
				siconpsg->x++;
			}
		break;
		case 6u:
			if(counter > 80u && siconpsg->x < 98u && (counter & 1)){
				siconpsg->x++;
			}
		break;
	}
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