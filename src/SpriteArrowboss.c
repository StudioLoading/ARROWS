#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "Dialogs.h"

extern UINT8 internal_t;

const UINT8 arrowboss_idle[] = {1, 0}; //The first number indicates the number of frames

UINT8 scrollarrowboss_tile;
Sprite* iabspr;
INT8 arrowboss_direction = 0;

//extern void Hit(INT8 damage) BANKED;


void START(){
    THIS->lim_x = 64u;
    THIS->lim_y = 20u;
    SetSpriteAnim(THIS, arrowboss_idle, 1u);
   	struct EnemyInfo* arrowboss_data = (struct EnemyInfo*)THIS->custom_data;    
    arrowboss_data->hp = 30;
    arrowboss_data->enemy_accel_y = 0;
    if(arrowboss_direction == 1){
        arrowboss_data->enemy_accel_y = -1; //used as vy
    }else if(arrowboss_direction == 3){
        arrowboss_data->enemy_accel_y = 1;
    }
    arrowboss_direction++;
    if(arrowboss_direction == 4){        
        arrowboss_direction = 0;
    }
}

void UPDATE(){
  	struct EnemyInfo* arrowboss_data = (struct EnemyInfo*)THIS->custom_data;    
    arrowboss_data->hp--;
    if(arrowboss_data->hp == 0){
        arrowboss_data->hp = 30;
        arrowboss_data->vx += arrowboss_data->vx;
    }
    UINT8 arrowboss_tile_collision = TranslateSprite(THIS, arrowboss_data->vx << delta_time, arrowboss_data->enemy_accel_y << delta_time);
    if(arrowboss_tile_collision){
        switch(arrowboss_tile_collision){
            case 11u:// REDIRECTION DOWN
                if(arrowboss_data->vx > 0){
                    THIS->x += 4u;
                }else if(arrowboss_data->vx < 0){
                    THIS->x -= 4u;
                }
                arrowboss_data->vx = 0;
                arrowboss_data->enemy_accel_y = 1;
            break;
            case 16u: //REDIRECTION RIGHT
                THIS->y -= 4u;
                arrowboss_data->vx = 2;
                arrowboss_data->enemy_accel_y = 0;
            break;
            case 17u: //REDIRECTION LEFT
                THIS->y -= 4u;
                arrowboss_data->vx = -2;
                arrowboss_data->enemy_accel_y = 0;
            break;
            case 80u:
                if(arrowboss_data->enemy_accel_y > 0){
                    if(arrowboss_data->vx == 0){
                        SpriteManagerRemoveSprite(THIS);        
                    }else{
                        arrowboss_data->enemy_accel_y = 0;
                    }
                }
            break;
            default:
       	        SpriteManagerRemoveSprite(THIS);
            break;
        }
    }
	SPRITEMANAGER_ITERATE(scrollarrowboss_tile, iabspr) {
		if(CheckCollision(THIS, iabspr)) {
            if(iabspr->type == SpriteArrowmother){
                THIS->x += 4u;
                SpriteManagerAdd(SpritePuff, THIS->x, THIS->y - 4u);
                SpriteManagerRemoveSprite(THIS);
            }
            if(iabspr->type == SpriteArrow){
                //da qui
                struct ArrowInfo* myarrow_data = (struct ArrowInfo*) iabspr->custom_data;
                if(myarrow_data->original_type == 5 && myarrow_data->vx != 0 && myarrow_data->vy == 0 && arrowboss_data->vx == 0){
                    arrowboss_data->vx = (myarrow_data->vx+myarrow_data->vx);
                    if(iabspr->mirror == V_MIRROR){//means going left
                        arrowboss_data->vx = -arrowboss_data->vx;
                    }
                    arrowboss_data->enemy_accel_y = 0;
                }
                SpriteManagerRemoveSprite(iabspr);
            }
        }
    }
}

void DESTROY(){
}