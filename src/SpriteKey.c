#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

const UINT8 key_hidden[] = {1, 0}; //The first number indicates the number of frames
const UINT8 key_wrench[] = {1, 1}; //The first number indicates the number of frames
const UINT8 key_key[] = {1, 2}; //The first number indicates the number of frames



void START() {
	struct ItemInfo* keydata = (struct ItemInfo*)THIS->custom_data;
	keydata->item_accel_y = 0;
	keydata->type = 0;
	keydata->setup = 0;
	THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 200;
	THIS->lim_y = 200;
}

void UPDATE() {
	
	struct ItemInfo* keydata = (struct ItemInfo*)THIS->custom_data;
	if(keydata->setup){
		switch(keydata->type){
			case 1: //key
				SetSpriteAnim(THIS, key_key, 8u);
			break;
			case 2: //wrench
				SetSpriteAnim(THIS, key_wrench, 8u);
			break;
		}
		keydata->setup = 0;
	}
	if(keydata->item_accel_y < 8) {
		keydata->item_accel_y += 1;
	}
	keydata->tile_i_collision = TranslateSprite(THIS, keydata->vx, keydata->item_accel_y >> 2);	
	if(keydata->tile_i_collision != 0 && keydata->item_accel_y > 6){
		keydata->item_accel_y = -4;
	}
	
}

void DESTROY() {
}
