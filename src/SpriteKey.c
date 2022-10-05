#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"

const UINT8 key_hidden[] = {1, 0}; //The first number indicates the number of frames
const UINT8 key_wrench[] = {1, 1}; //The first number indicates the number of frames
const UINT8 key_key[] = {1, 2}; //The first number indicates the number of frames



void START() {
	struct ItemInfo* keydata = (struct ItemInfo*)THIS->custom_data;
	keydata->item_accel_y = 0;
	keydata->type = 0;
	keydata->setup = 0;
	keydata->counter = 0;
	THIS->lim_x = 100;
	THIS->lim_y = 100;
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
	keydata->counter++;
	if(keydata->item_accel_y < 4 && ((keydata->counter & 0x3) == 0)) {
		keydata->item_accel_y += 1;
	}
	keydata->tile_i_collision = TranslateSprite(THIS, keydata->vx, keydata->item_accel_y);	
	if(keydata->tile_i_collision != 0){ //&& keydata->item_accel_y > 6){
		PlayFx(CHANNEL_1, 60, 0x6d, 0x8c, 0x73, 0xff, 0xc7);//sfx key
		keydata->item_accel_y = -2;
	}
	
}

void DESTROY() {
}
