#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Sound.h"
#include "Music.h"
#include "Scroll.h"

#include "custom_datas.h"
#include "Dialogs.h"
#include "sgb_palette.h"

extern INT8 temporeggia;

const UINT8 anim_cutarcher_idle[] = {5, 5,6,7,7,6};
const UINT8 anim_cutarcher_walk[] = {5, 4,3,2,3,1};

void START(){
    THIS->lim_x = 255u;
    THIS->lim_y = 255u;
   	struct EnemyInfo* cutarcher_data = (struct EnemyInfo*)THIS->custom_data;
    cutarcher_data->vx = 4;
    cutarcher_data->enemy_accel_y = 24u;
    cutarcher_data->tile_e_collision = 0u;
    temporeggia = 0;
}

void UPDATE(){
    UINT8 cutarcher_tile;
    Sprite* cutarcherspr;

   	struct EnemyInfo* cutarcher_data = (struct EnemyInfo*)THIS->custom_data;
    
    switch(cutarcher_data->enemy_state){
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, anim_cutarcher_idle, 8u);
            cutarcher_data->enemy_state = ENEMY_STATE_NORMAL;
        break;
        case ENEMY_STATE_WALKING:
            SetSpriteAnim(THIS, anim_cutarcher_walk, 8u);
            cutarcher_data->enemy_state = ENEMY_STATE_NORMAL;
        break;
        case ENEMY_STATE_JUMPING:
        case ENEMY_STATE_SLIDING:
            //TranslateSprite(THIS, cutarcher_data->vx << delta_time, 0);
            //THIS->y = cutarcher_data->enemy_accel_y; 
        break;
    }

    SPRITEMANAGER_ITERATE(cutarcher_tile, cutarcherspr) {
        if(CheckCollision(THIS, cutarcherspr)) {
            if(cutarcherspr->type == SpriteArrowmother) {
                cutarcher_data->enemy_state = ENEMY_STATE_SLIDING;
                cutarcher_data->tile_e_collision = 1u;
                cutarcher_data->vx = 2;
                THIS->y = cutarcherspr->y - 9u;
                THIS->x = cutarcherspr->x + 4u;
            }
        }
    }
}

void DESTROY(){

}