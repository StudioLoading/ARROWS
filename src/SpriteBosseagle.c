#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "CircleMath.h"

#define SHOOT_MAXCOOLDOWN 36

const UINT8 anim_bosseagle_normal[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_bosseagle_attack[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 anim_bosseagle_hit[] = {2, 0, 1}; //The first number indicates the number of frames

extern Sprite* enemies_2; //moving iconpsg level 8.0

UINT8 boss_wait = 0u;
Sprite* boss_eagle = 0;
INT8 bosseagleshoot_cooldown = 0;
INT8 fly_counter = 0;
UINT16 init_posx = 0u;
UINT16 init_posy = 0u;
INT8 alternate_initposs = -1;
//3 2 1 1 2 3 
//ogni 10 frame

void START() {
    init_posx = 0u;
    init_posy = 0u;
	THIS->lim_x = 120u;
	THIS->lim_y = 120u;
	SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
    boss_eagle = SpriteManagerAdd(SpriteCuteagle, THIS->x, (UINT16) THIS->y - 16u);
    struct EnemyInfo* boss_eagle_data = (struct EnemyInfo*) boss_eagle->custom_data;
    boss_eagle_data->enemy_state = ENEMY_STATE_SLIDING;
    boss_wait = 0u;
    bosseagleshoot_cooldown = 0;
    struct EnemyInfo* bosseagle_data = (struct EnemyInfo*) THIS->custom_data;
    bosseagle_data->archer_posx = 0u;
    bosseagle_data->hp = 8;
}

void UPDATE(){
    struct EnemyInfo* boss_data = (struct EnemyInfo*) THIS->custom_data;
    switch(boss_data->enemy_state){
        case BOSS_APPROACHING_FIRST:
            if(THIS->x > ((UINT16) 18u << 3)){
                THIS->x--;
            }else{
                SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
                boss_data->enemy_state = BOSS_MOVING;
                init_posx = THIS->x;
                init_posy = THIS->y;
                boss_wait = 0u;
            }
        break;
        case BOSS_APPROACHING:
            boss_wait++;
            //UINT8 boss_wait_module = boss_wait & 0x2; 
            //if(boss_wait_module == 0){
                if(init_posx == 0u && init_posy == 0u){
                    THIS->x -= 2;
                }else{
                    if(THIS->x > init_posx){
                        THIS->x--;
                    }else if(THIS->x < init_posx){
                        THIS->x ++;
                        if(enemies_2->x > ((UINT16) 8u << 3)){
                            THIS->x ++;
                        }
                    }
                    if(THIS->y > init_posy){
                        THIS->y --;
                    }else if(THIS->y < init_posy){
                        THIS->y ++;
                        if(enemies_2->x > ((UINT16) 8u << 3)){
                            THIS->y ++;
                        }
                    }
                //}
            }
            if(boss_wait == 120u){	
                SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
                boss_data->enemy_state = BOSS_MOVING;
                if(enemies_2->x < ((UINT16) 7u << 3)){
                    init_posx = ((UINT16) 18u << 3);
                    init_posy = ((UINT16) 8u << 3);
                }else{
                    if(alternate_initposs < 0){
                        alternate_initposs = 0;
                    }
                    if(alternate_initposs == 0){
                        init_posx = ((UINT16) 17u << 3);
                        init_posy = ((UINT16) 8u << 3);
                        alternate_initposs = 1;
                    }else{
                        alternate_initposs = 0;
                        init_posx = ((UINT16) 17u << 3);
                        init_posy = ((UINT16) 14u << 3);
                    }
                }
                boss_wait = 0u;
            }
        break;
        case BOSS_MOVING:
            //FLYING
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
            if(boss_wait == 180u){
                boss_wait = 0u;
                SetSpriteAnim(THIS, anim_bosseagle_attack, 6u);
                boss_data->enemy_state = BOSS_ATTACK;
            }

            //ROUNDING
            UINT8 cos_position = boss_data->archer_posx + 64u;
		    THIS->x = THIS->lim_x + ((sine_wave[cos_position]) >> 3);
		    THIS->y = THIS->lim_y + ((sine_wave[boss_data->archer_posx]) >> 3);
		    if(enemies_2->x < ((UINT16) 8u << 3)){
                boss_data->archer_posx += 2u;
            }else{
                boss_data->archer_posx += 4u;
            }
        break;
        case BOSS_ATTACK:
            bosseagleshoot_cooldown++;
            if(bosseagleshoot_cooldown >= SHOOT_MAXCOOLDOWN && THIS->anim_frame == 1){
                Sprite* arrowboss_spr = SpriteManagerAdd(SpriteArrowboss, THIS->x + 4u, THIS->y + 12u);
                struct EnemyInfo* arrowboss_spr_data = (struct EnemyInfo*) arrowboss_spr->custom_data;
                arrowboss_spr_data->vx = -2;
                bosseagleshoot_cooldown = 0;
            }            
            boss_wait++;
            if(boss_wait == 180u){
                boss_wait = 0u;
                SetSpriteAnim(THIS, anim_bosseagle_normal, 4u);
                boss_data->archer_posx = 0u;	
                THIS->lim_x = init_posx;
                THIS->lim_y = init_posy;
                boss_data->enemy_state = BOSS_APPROACHING;// BOSS_MOVING;
            }
        break;
    }
    boss_eagle->x = THIS->x - 8u;
    boss_eagle->y = THIS->y - 28u;
}

void DESTROY(){

}