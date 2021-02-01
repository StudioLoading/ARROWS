#include "Banks/SetBank2.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

const UINT8 platform_normal[] = {1, 0}; //The first number indicates the number of frames

void Start_SpritePlatform() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 12;
	THIS->coll_w = 12;
	THIS->coll_h = 4;
	THIS->lim_x = 255;
	THIS->lim_y = 255;
	SetSpriteAnim(THIS, platform_normal, 8u);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)THIS->custom_data;
	data_platform->type = 0;
	data_platform->distance = 200;
	data_platform->step = 0;
}

void Update_SpritePlatform() {
	struct PlatformInfo* data_platform = (struct PlatformInfo*)THIS->custom_data;
	UINT8 r = 0x1;//2;
	if (data_platform->step < 30 | data_platform->step > 170){
		r=0x7;//8;
	}
	if(data_platform->step > 70 & data_platform->step < 130){
		r=0x7;//8;
	}
	if ((data_platform->step & r) == 0){
		if (data_platform->step < (data_platform->distance/2)){
			data_platform->vx = 1;
		}else{		
			data_platform->vx = -1;
		}
		TranslateSprite(THIS, data_platform->vx, 0);	
	}else{
		data_platform->vx = 0;
	}
	data_platform->step += 1;
	if (data_platform->step >= data_platform->distance){
		data_platform->step = 0;
		THIS->x = data_platform->initx;		
	}
}

void Destroy_SpritePlatform() {
}
