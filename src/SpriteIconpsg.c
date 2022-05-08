#include "Banks/SetAutoBank.h"

#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


const UINT8 icon_empty[] = {1, 0}; //The first number indicates the number of frames
const UINT8 icon_archer[] = {1, 1}; //The first number indicates the number of frames
const UINT8 icon_archer_blink[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 icon_mother[] = {1, 2}; //The first number indicates the number of frames
const UINT8 icon_mother_blink[] = {2, 0, 2}; //The first number indicates the number of frames


void START() {
	struct ItemInfo* datak = (struct ItemInfo*)THIS->custom_data;
	//datak->type = 0;
	datak->setup = 0u;
	datak->counter = -1;
	SetSpriteAnim(THIS, icon_empty, 8u);	
	THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 16;
	THIS->lim_x = 255;
	THIS->lim_y = 255;
}

void UPDATE() {
	struct ItemInfo* datak = (struct ItemInfo*)THIS->custom_data;
	if(datak->setup > 0u){ 
		switch(datak->type){
			case 1:
				SetSpriteAnim(THIS, icon_archer, 8u);
			break;
			case 2:
				SetSpriteAnim(THIS, icon_mother, 8u);
			break;
			case 11:
				SetSpriteAnim(THIS, icon_archer_blink, 16u);
			break;
			case 12:
				SetSpriteAnim(THIS, icon_mother_blink, 16u);
			break;
		}
		datak->setup = 0u;
	}
}

void Destroy_SpriteIconpsg() {
}