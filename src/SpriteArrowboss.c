#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "Dialogs.h"

const UINT8 arrowboss_idle[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames

UINT8 scrollarrowboss_tile;
Sprite* iabspr;
INT8 arrowboss_direction = 0;

//extern void Hit(INT8 damage) BANKED;


void START(){
    THIS->lim_x = 2u;
    THIS->lim_y = 20u;
    SetSpriteAnim(THIS, arrowboss_idle, 16u);
   	struct EnemyInfo* arrowboss_data = (struct EnemyInfo*)THIS->custom_data;    
    arrowboss_data->vx = 0;
    if(arrowboss_direction == 1){
        arrowboss_data->vx = -1; //used as vy
    }else if(arrowboss_direction == 3){
        arrowboss_data->vx = 1;
    }
    arrowboss_direction++;
    if(arrowboss_direction == 4){        
        arrowboss_direction = 0;
    }
}

void UPDATE(){
  	struct EnemyInfo* arrowboss_data = (struct EnemyInfo*)THIS->custom_data;    
    UINT8 arrowboss_tile_collision = TranslateSprite(THIS, -2 << delta_time, arrowboss_data->vx << delta_time);
    if(arrowboss_tile_collision){
	    SpriteManagerRemoveSprite(THIS);
    }
	SPRITEMANAGER_ITERATE(scrollarrowboss_tile, iabspr) {
		if(CheckCollision(THIS, iabspr)) {
            if(iabspr->type == SpriteArrowmother){
                THIS->x += 4u;
                SpriteManagerAdd(SpritePuff, THIS->x, THIS->y - 4u);
                SpriteManagerRemoveSprite(THIS);
            }
            if(iabspr->type == SpriteArrow){
                SpriteManagerRemoveSprite(iabspr);
            }
        }
    }
}

void DESTROY(){
}