#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//CUTALLIGATOR
const UINT8 anim_cutalligator_invisible[] = {2, 0, 1}; //The first number indicates the number of frames

extern UINT8 wait_c;

struct EnemyInfo* cutalligator_data;

void START() {
    THIS->lim_x = 80u;
    THIS->lim_y = 80u;
    cutalligator_data = (struct EnemyInfo*) THIS->custom_data;
    cutalligator_data->enemy_state = ENEMY_STATE_HIDDEN;
    cutalligator_data->wait = 0u;
	SetSpriteAnim(THIS, anim_cutalligator_invisible, 24u);
}

void UPDATE(){
    if(cutalligator_data->enemy_state == ENEMY_STATE_WALKING){
        cutalligator_data->wait++;
        if((cutalligator_data->wait & 0x2) == 0){
            THIS->x += cutalligator_data->vx;
        }
    }
}

void DESTROY(){
    wait_c = 44u;
}