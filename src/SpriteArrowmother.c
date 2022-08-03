#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "Dialogs.h"

const UINT8 arrowmother_idle[] = {1, 0}; //The first number indicates the number of frames

extern INT16 archer_accel_y;

void START(){
    THIS->lim_x = 128u;
    THIS->lim_y = 128u;
    SetSpriteAnim(THIS, arrowmother_idle, 1u);
}

void UPDATE(){
	struct EnemyInfo* arrowmother_data = (struct EnemyInfo*) THIS->custom_data;
    UINT8 some_keys = 1;
    switch(arrowmother_data->enemy_state){
        case ARROWMOTHER_CUTSCENE:
            TranslateSprite(THIS, 2 << delta_time, 0);
        break;
        case ARROWMOTHER_NORMAL:
            if(KEY_PRESSED(J_UP) && archer_accel_y > -2){
                THIS->lim_y = -1u;
                some_keys = 0;
            }else if(KEY_PRESSED(J_DOWN)){
                THIS->lim_y = 1u;
                some_keys = 0;
            }
            if(KEY_PRESSED(J_RIGHT)){
				THIS->mirror = NO_MIRROR;
                THIS->lim_x = 1u;
                some_keys = 0;
            }else if(KEY_PRESSED(J_LEFT)){
				THIS->mirror = V_MIRROR;
                THIS->lim_x = -1u;
                some_keys = 0;
            }
            if(some_keys){
                THIS->lim_x = 0;
                THIS->lim_y = 0;
            }else{
                TranslateSprite(THIS, THIS->lim_x << delta_time, THIS->lim_y << delta_time);
            }
        break;
    }
}

void DESTROY(){

}