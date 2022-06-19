#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"

//FEATHER
const UINT8 feather_anim[] = {1, 0}; //The first number indicates the number of frames


void START() {	
	SetSpriteAnim(THIS, feather_anim, 8u);
   	struct ItemInfo* feather_data = (struct ItemInfo*)THIS->custom_data;
    feather_data->item_accel_y = 1;
    feather_data->vx = 1;

}

void UPDATE() { 
	struct ItemInfo* feather_data = (struct ItemInfo*)THIS->custom_data;
	feather_data->collided++;
    switch(feather_data->collided){
        case 10u:
            feather_data->item_accel_y = 0;
        break;
        case 20:
            feather_data->item_accel_y = 1;
        break;
        case 24:
            feather_data->item_accel_y = 2;
        break;
        case 32:
            feather_data->item_accel_y = 1;
        break;
        case 42u:
            feather_data->item_accel_y = 0;
            feather_data->vx *= -1;
            if(THIS->mirror == V_MIRROR){
                THIS->mirror = NO_MIRROR;
            }else{
                THIS->mirror = V_MIRROR;
            }
            feather_data->collided = 0u;
        break;
    }
    THIS->x += feather_data->vx;
    if((feather_data->collided & 0b00000001) == 0b00000001){
        THIS->y += feather_data->item_accel_y;
    }
}

void DESTROY(){
}