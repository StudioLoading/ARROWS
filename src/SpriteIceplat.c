#include "Banks/SetBank5.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

const UINT8 iceplat_normal[] = {1, 3}; //The first number indicates the number of frames
const UINT8 iceplat_melt_2[] = {1, 2}; //The first number indicates the number of frames
const UINT8 iceplat_melt_1[] = {1, 1}; //The first number indicates the number of frames
const UINT8 iceplat_melt_0[] = {1, 0}; //The first number indicates the number of frames
extern INT8 spawning_triggered;

void Start_SpriteIceplat() {
	THIS->coll_x = 2;
	THIS->coll_y = 11;
	THIS->coll_w = 12;
	THIS->coll_h = 5;
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
	SetSpriteAnim(THIS, iceplat_normal, 8u);
	struct PlatformInfo* data_platform = (struct PlatformInfo*)THIS->custom_data;
	data_platform->distance = 60u;
	data_platform->type = 0u;
	data_platform->vx = 0;
	data_platform->vy = 0;
}

void Update_SpriteIceplat() {	
	struct PlatformInfo* data_platform = (struct PlatformInfo*)THIS->custom_data;
	if(data_platform->type != 0){ //different from 0, starts melt
		data_platform->distance -= 2u;
		switch (data_platform->distance){
			case 40u: 	SetSpriteAnim(THIS, iceplat_melt_2, 4u); break;
			case 20u: 	SetSpriteAnim(THIS, iceplat_melt_1, 4u); break;
			case 10u:	SetSpriteAnim(THIS, iceplat_melt_0, 4u); break;
			case 2u:
			case 0u: 	
				data_platform->type = 1;
				SpriteManagerRemoveSprite(THIS); 
			break;		
		}
	}
}

void Destroy_SpriteIceplat() {

}
