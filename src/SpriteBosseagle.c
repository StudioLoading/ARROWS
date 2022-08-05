#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "custom_datas.h"

#define SHOOT_MAXCOOLDOWN 50

const UINT8 anim_bosseagle_normal[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_bosseagle_attack[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 anim_bosseagle_hit[] = {2, 0, 1}; //The first number indicates the number of frames

UINT8 boss_wait = 0u;
Sprite* boss_eagle = 0;
INT8 bosseagleshoot_cooldown = 0;
INT8 fly_counter = 0;
//3 2 1 1 2 3 
//ogni 10 frame

void START() {
	THIS->lim_x = 120u;
	THIS->lim_y = 120u;
	SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
    boss_eagle = SpriteManagerAdd(SpriteCuteagle, THIS->x, (UINT16) THIS->y - 16u);
    struct EnemyInfo* boss_eagle_data = (struct EnemyInfo*) boss_eagle->custom_data;
    boss_eagle_data->enemy_state = ENEMY_STATE_SLIDING;
    boss_wait = 0u;
    bosseagleshoot_cooldown = 0;
}

void UPDATE(){
    struct EnemyInfo* boss_data = (struct EnemyInfo*) THIS->custom_data;
    switch(boss_data->enemy_state){
        case BOSS_APPROACHING:
            boss_wait++;
            UINT8 boss_wait_module = boss_wait & 0x2; 
            if(boss_wait_module == 0){
                THIS->x -= 2;
            }
            if(boss_wait == 120u){	
                SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
                boss_data->enemy_state = BOSS_MOVING;
                boss_wait = 0u;
            }
        break;
        case BOSS_MOVING:
            fly_counter++;
            switch(fly_counter){
                case 10u:
                    THIS->y += 2;
                break;
                case 20u:
                    THIS->y += 1;
                break;
                case 30u:
                    THIS->y += 1;
                break;
                case 40u:
                    THIS->y -= 1;
                break;
                case 50u:
                    THIS->y -= 1;
                break;
                case 60u:
                    THIS->y -= 2;
                    fly_counter = 0;
                break;
            }
            boss_wait++;
            if(boss_wait == 200u){
                boss_wait = 0u;
                SetSpriteAnim(THIS, anim_bosseagle_attack, 4u);
                boss_data->enemy_state = BOSS_ATTACK;
            }
        break;
        case BOSS_ATTACK:
            bosseagleshoot_cooldown++;
            if(bosseagleshoot_cooldown >= SHOOT_MAXCOOLDOWN && THIS->anim_frame == 1){
                SpriteManagerAdd(SpriteArrowboss, THIS->x + 4u, THIS->y + 12u);
                bosseagleshoot_cooldown = 0;
            }            
            boss_wait++;
            if(boss_wait == 180u){
                boss_wait = 0u;
                SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
                boss_data->enemy_state = BOSS_MOVING;
            }
        break;
    }
    boss_eagle->x = THIS->x - 8u;
    boss_eagle->y = THIS->y - 28u;
}

void DESTROY(){

}