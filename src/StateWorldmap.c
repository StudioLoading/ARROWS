#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Music.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "TilesAnimations0.h"
#include "Dialogs.h"
#include "sgb_palette.h"


IMPORT_TILES(tilesmapworld);
IMPORT_TILES(font);

IMPORT_MAP(mapworld);

DECLARE_MUSIC(bgm_worldmap);

extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern UINT8 current_level;
extern UINT8 diag_found;
extern UINT8 on_worldmap;
extern UINT8 quiver;
extern INT8 visited;

const UINT8 const collision_tiles_worldmap[] = {0, 0};

UINT8 diag_found = 0u;
UINT8 counter = 0;
Sprite* siconpsg;
struct ItemInfo* dataiconpsg;

void START() {

	HIDE_WIN;
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//NR50_REG = 0x44; //Max volume 0x77
	
	SpriteManagerLoad(SpriteIconpsg);
	
	if(sgb_check()){
		set_sgb_palette01_worldmap();
		//reset_sgb_palette_statusbar();
	}
	
	switch(current_level){
		case 0u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, (UINT16) 9u, (UINT16) 81u);
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
			dataiconpsg->type=11;
			dataiconpsg->setup=1u;
		break;
		case 1u:
			siconpsg = SpriteManagerAdd(SpriteIconpsg, ((UINT16) 9u), (UINT16) 81u);	
			dataiconpsg = (struct ItemInfo*)siconpsg->custom_data;
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

	InitScroll(BANK(mapworld), &mapworld, collision_tiles_worldmap, 0);
	SHOW_BKG;
	
	on_worldmap = 1;

	PlayMusic(bgm_worldmap, 1);

	visited = -1;
}

void UPDATE(){
	counter++;
	if(counter == 10u){	
		if((quiver & 0b0000000010) == 0b0000000010){// ho stone calice
			WorldmapQuiverStone();
		}
		if((quiver & 0b0000000100) == 0b0000000100){// ho thunder horn
			WorldmapQuiverThunder();
		}
		if((quiver & 0b0000001000) == 0b0000001000){// ho ice kneckle
			WorldmapQuiverIce();
		}		
	}
	switch(current_level){ // spostamento orizzontale da un punto all' altro di 25u
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
		diag_found = Build_Next_Dialog_Banked(siconpsg);
		SetState(StateDiag);
	}
}