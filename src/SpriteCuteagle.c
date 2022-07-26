#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"

//CUTEAGLE
const UINT8 cuteagle_idle[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 cuteagle_plana[] = {1, 0};

void START(){
    THIS->lim_x = 160u;
    THIS->lim_y = 160u;
 	SetSpriteAnim(THIS, cuteagle_plana, 8u);
}

void UPDATE(){
   	struct EnemyInfo* cuteagle_data = (struct EnemyInfo*)THIS->custom_data;
    switch(cuteagle_data->enemy_state){
        case ENEMY_STATE_JUMPING:
         	SetSpriteAnim(THIS, cuteagle_idle, 24u);
        break;
        case ENEMY_STATE_SLIDING:
         	SetSpriteAnim(THIS, cuteagle_idle, 8u);
            cuteagle_data->enemy_state = ENEMY_STATE_NORMAL;
        break;
    }
}

void DESTROY(){

}