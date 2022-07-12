#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"

#include "custom_datas.h"
#include "Dialogs.h"

const UINT8 anim_castlegate[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_castlewall[] = {1, 1}; //The first number indicates the number of frames

void START(){
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
   	struct EnemyInfo* castlegate_data = (struct EnemyInfo*)THIS->custom_data;
    castlegate_data->hp = 1;
}

void UPDATE(){
   	struct EnemyInfo* castlegate_data = (struct EnemyInfo*)THIS->custom_data;
    if(castlegate_data->hp == 1){
        switch(castlegate_data->enemy_state){
            case ENEMY_STATE_NORMAL:
                SetSpriteAnim(THIS, anim_castlegate, 8u);
                castlegate_data->hp = 0;
            break;
            case ENEMY_STATE_JUMPING:

            break;
            case ENEMY_STATE_DEAD:
                SetSpriteAnim(THIS, anim_castlewall, 8u);
                castlegate_data->hp = 0;
            break;
        }
    }
}

void DESTROY(){
    struct EnemyInfo* castlegate_data = (struct EnemyInfo*)THIS->custom_data;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
}
