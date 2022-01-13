#include "Banks/SetBank14.h"
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


void Start_SpriteIconpsg() {
	struct ItemInfo* datak = (struct ItemInfo*)THIS->custom_data;
	//datak->type = 0;
	datak->setup = 0u;
	datak->counter = -1;
	SetSpriteAnim(THIS, icon_empty, 8u);	
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 16;
	THIS->lim_x = 255;
	THIS->lim_y = 255;
}

void Update_SpriteIconpsg() {
	struct ItemInfo* datak = (struct ItemInfo*)THIS->custom_data;
	if(datak->setup > 0u){ 
		switch(datak->type){
			case 1:
				SetSpriteAnim(THIS, icon_archer, 16u);
			break;
			case 2:
				SetSpriteAnim(THIS, icon_mother, 16u);
			break;
			case 11:
				SetSpriteAnim(THIS, icon_archer_blink, 24u);
			break;
			case 12:
				SetSpriteAnim(THIS, icon_mother_blink, 24u);
			break;
		}
		datak->setup = 0u;
	}
}

void Destroy_SpriteIconpsg() {
}