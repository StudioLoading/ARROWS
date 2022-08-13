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

const UINT8 anim_boss_idle[] = {4, 0, 0, 0, 1};

struct EnemyInfo* bossfighter_data;

void START(){
    SetSpriteAnim(THIS, anim_boss_idle, 8u);
	bossfighter_data= (struct EnemyInfo*)THIS->custom_data;
	bossfighter_data->enemy_state = ENEMY_STATE_WAIT;
	bossfighter_data->hp = 7;
}

void UPDATE(){
    switch(bossfighter_data->enemy_state){
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, anim_boss_idle, 8u);
        break;
    }

}

void DESTROY(){

}