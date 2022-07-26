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

const UINT8 anim_cutarcher_idle[] = {5, 5,6,7,7,6};
const UINT8 anim_cutarcher_walk[] = {5, 4,3,2,3,1};

void START(){
    THIS->lim_x = 255u;
    THIS->lim_y = 255u;
   	struct EnemyInfo* cutarcher = (struct EnemyInfo*)THIS->custom_data;
    cutarcher->vx = 0;
    cutarcher->enemy_accel_y = 24u;
}

void UPDATE(){
   	struct EnemyInfo* cutarcher_data = (struct EnemyInfo*)THIS->custom_data;
    
    switch(cutarcher_data->enemy_state){
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, anim_cutarcher_idle, 8u);
        break;
        case ENEMY_STATE_WALKING:
            SetSpriteAnim(THIS, anim_cutarcher_walk, 8u);
        break;
    }
}

void DESTROY(){

}