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

#define MAX_ATTACK_BALL_COOLDWON 16
#define MAX_BF_HIT_COOLDOWN 48
#define MIN_BF_HIT_COOLDOWN 40
#define MAX_POS_X 23 << 3
#define MIN_POS_X 5 << 3
#define MIN_POS_X_INTERVAL 9 << 3
#define MAX_POS_X_INTERVAL 19 << 3

extern INT8 temporeggia;

const UINT8 anim_cutbossdead_idle[] = {2, 0, 1};
const UINT8 anim_cutbossdead_falling[] = {6, 2, 2, 2, 3, 3, 3};
const UINT8 anim_cutbossdead_invisible[] = {1, 1};


void START(){
    SetSpriteAnim(THIS, anim_cutbossdead_idle, 24u);
   	struct EnemyInfo* cutbossdead_data= (struct EnemyInfo*)THIS->custom_data;
    cutbossdead_data->enemy_state = BOSS_IDLE;
    temporeggia = 0;
}

void UPDATE(){
   	struct EnemyInfo* cutbossdead_data = (struct EnemyInfo*)THIS->custom_data;
    switch(cutbossdead_data->enemy_state){
        case BOSS_IDLE:
            temporeggia++;
            if(temporeggia >= 120){
                temporeggia = 0;
                SetSpriteAnim(THIS, anim_cutbossdead_falling, 4u);
                cutbossdead_data->enemy_state = BOSS_DIEING;
            }
        break;
        case BOSS_DIEING:
            temporeggia++;
            if((temporeggia & 0x4) == 0){
                THIS->y++;
                if(THIS->y >= ((UINT16) 23u << 3)){                    
                    SetSpriteAnim(THIS, anim_cutbossdead_invisible, 1u);
                    cutbossdead_data->enemy_state = ENEMY_STATE_HIDDEN;
                }
            }
        break;
    }
}

void DESTROY(){

}
