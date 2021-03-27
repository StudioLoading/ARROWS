#include "Banks/SetBank3.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

const UINT8 key_hidden[] = {1, 0}; //The first number indicates the number of frames
const UINT8 key_wrench[] = {1, 1}; //The first number indicates the number of frames
const UINT8 key_key[] = {1, 2}; //The first number indicates the number of frames



void Start_SpriteKey() {

	struct ItemInfo* keydata = (struct ItemInfo*)THIS->custom_data;
	keydata->item_accel_y = 0;
	keydata->type = 0;
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 200;
	THIS->lim_y = 200;
}

void Update_SpriteKey() {
	
	struct ItemInfo* keydata = (struct ItemInfo*)THIS->custom_data;
	if(keydata->setup){
		keydata->vx = 0;
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
	if(keydata->item_accel_y < 24) {
		keydata->item_accel_y += 1;
	}
	keydata->tile_i_collision = TranslateSprite(THIS, keydata->vx, keydata->item_accel_y >> 4);
	if(!keydata->tile_i_collision && delta_time != 0 && keydata->item_accel_y < 24) { //Do another iteration if there is no collision
		keydata->item_accel_y += 2;
		keydata->tile_i_collision = TranslateSprite(THIS, keydata->vx, keydata->item_accel_y >> 4);
	}
	
}

void Destroy_SpriteKey() {
}
