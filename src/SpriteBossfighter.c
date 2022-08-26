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
extern UINT8 wait_c;
extern INT8 boss_hp;

const UINT8 anim_boss_idle[] = {4, 0, 0, 0, 1};
const UINT8 anim_boss_walk[] = {4, 0, 2, 1, 2};
const UINT8 anim_boss_dieing[] = {8, 0, 4, 2, 4, 1, 4, 2, 4};
const UINT8 anim_boss_knee[] = {1, 5};
const UINT8 anim_boss_attack[] = {4, 0, 0, 0, 3};
const UINT8 anim_boss_hit[] = {2, 2, 4};

struct EnemyInfo* bossfighter_data;
INT8 attack_ball_cooldown = 0;
INT8 bossfighter_hit_cooldown = 0;

UINT8 scrollbossfighter_tile;
Sprite* ibfspr;

void START(){
    SetSpriteAnim(THIS, anim_boss_idle, 8u);
    THIS->x = MAX_POS_X;
	bossfighter_data= (struct EnemyInfo*)THIS->custom_data;
	bossfighter_data->enemy_state = BOSS_IDLE;    
	bossfighter_data->hp = boss_hp;
    temporeggia = 0;
    bossfighter_hit_cooldown = 0;
}

void UPDATE(){
    switch(bossfighter_data->enemy_state){
        case BOSS_IDLE:
        case ENEMY_STATE_NORMAL:
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, anim_boss_idle, 8u);
            temporeggia++;
            if((bossfighter_data->hp < 5 && temporeggia == 36) || (bossfighter_data->hp <= 7 && temporeggia == 60)){
                SetSpriteAnim(THIS, anim_boss_walk, 4u);
                if(THIS->mirror == NO_MIRROR){
                    THIS->x--;
                }else{
                    THIS->x++;
                }
                bossfighter_data->enemy_state = BOSS_MOVING;
                temporeggia = 0;
            }
        break;
        case BOSS_MOVING:
            if(THIS->x == MIN_POS_X || THIS->x == MAX_POS_X){
                bossfighter_data->vx = 0;
                if(temporeggia == 0){//turn!
                    if(THIS->mirror == NO_MIRROR){
                        THIS->mirror = V_MIRROR;
                    }else if(THIS->mirror == V_MIRROR){
                        THIS->mirror = NO_MIRROR;
                    }
                }
                temporeggia++;
            }else{
                if(THIS->x < MIN_POS_X_INTERVAL || THIS->x > MAX_POS_X_INTERVAL){
                    bossfighter_data->vx = 1;
                }else{
                    bossfighter_data->vx = 2;
                }
                if(THIS->mirror == NO_MIRROR){
                    bossfighter_data->vx = -bossfighter_data->vx;
                }
                TranslateSprite(THIS, bossfighter_data->vx << delta_time, 0);
            }
            if((bossfighter_data->hp < 5 && temporeggia == 80) || (bossfighter_data->hp <= 7 && temporeggia == 120)){
                SetSpriteAnim(THIS, anim_boss_knee, 1u);
                bossfighter_data->enemy_state = BOSS_KNEE;
                temporeggia = 0;
            }
        break;
        case BOSS_KNEE:
            temporeggia++;
            if((bossfighter_data->hp < 5 && temporeggia == 80) || (bossfighter_data->hp <= 7 && temporeggia == 120)){
                SetSpriteAnim(THIS, anim_boss_attack, 20u);
                bossfighter_data->enemy_state = BOSS_ATTACK;
                temporeggia = 0;
            }
        break;
        case BOSS_ATTACK:        
            attack_ball_cooldown++;
            if(THIS->anim_frame == 3 && attack_ball_cooldown >= MAX_ATTACK_BALL_COOLDWON && temporeggia < 180){
                Sprite* arrowboss_spr = SpriteManagerAdd(SpriteArrowboss, THIS->x + 4u, THIS->y + 12u);
                struct EnemyInfo* arrowboss_spr_data = (struct EnemyInfo*) arrowboss_spr->custom_data;
                if(THIS->mirror == NO_MIRROR){
                    arrowboss_spr_data->vx = -2;
                }else{
                    arrowboss_spr_data->vx = 2;
                }
                attack_ball_cooldown = 0;       
            }     
            temporeggia++;
            if(bossfighter_data->hp < 5 && temporeggia == 96){
                SetSpriteAnim(THIS, anim_boss_idle, 16u);
                bossfighter_data->enemy_state = BOSS_IDLE;
                temporeggia = 0;
            }else if(bossfighter_data->hp <= 7 && temporeggia == 120){
                SetSpriteAnim(THIS, anim_boss_idle, 12u);
                bossfighter_data->enemy_state = BOSS_IDLE;
                temporeggia = 0;
            }
        break;
        case BOSS_HIT:
            bossfighter_hit_cooldown++;
            if((bossfighter_data->hp <= 7 && bossfighter_hit_cooldown >= MIN_BF_HIT_COOLDOWN) || (bossfighter_data->hp < 5 && bossfighter_hit_cooldown >= MAX_BF_HIT_COOLDOWN)){
                SetSpriteAnim(THIS, anim_boss_idle, 8u);
                bossfighter_data->enemy_state = BOSS_IDLE;
                temporeggia = 0;
            }
        break;
        case BOSS_DIEING:
            if(THIS->mirror == NO_MIRROR){//going back means right
                bossfighter_data->vx = 1;
            }else{
                bossfighter_data->vx = -1;
            }
            if(THIS->x != MAX_POS_X && THIS->x != MIN_POS_X){
                temporeggia++;
                if((temporeggia & 0x3) == 0){
                    TranslateSprite(THIS, bossfighter_data->vx << delta_time, 0);
                }
            }else{
                temporeggia = 0;
                bossfighter_data->enemy_state = BOSS_DEAD;
                bossfighter_data->enemy_accel_y = THIS->x;
                wait_c = 0;
                SetState(StateCutscene);
                return;
            }
        break;
    }
	SPRITEMANAGER_ITERATE(scrollbossfighter_tile, ibfspr) {
		if(CheckCollision(THIS, ibfspr) && bossfighter_data->enemy_state != BOSS_DIEING) {
            if(ibfspr->type == SpriteArrowboss){
                struct EnemyInfo* ibfspr_data = (struct EnemyInfo*)ibfspr->custom_data;
                if((ibfspr_data->vx > 0 && THIS->mirror == NO_MIRROR) || (ibfspr_data->vx < 0 && THIS->mirror == V_MIRROR)){
                //bossfighter_data->enemy_state != BOSS_ATTACK){
                    if(bossfighter_data->enemy_state != BOSS_HIT && ibfspr_data->enemy_accel_y == 0){
                        temporeggia = 0;
                        bossfighter_hit_cooldown = 0;
                        bossfighter_data->enemy_state = BOSS_HIT;
                        SetSpriteAnim(THIS, anim_boss_hit, 24u);
                        bossfighter_data->hp--;
                        if(bossfighter_data->hp <= 0){
                            temporeggia = 0;
                            SetSpriteAnim(THIS, anim_boss_dieing, 20u);
                            bossfighter_data->enemy_state = BOSS_DIEING;
                        }
                    }else{
                        SpriteManagerRemoveSprite(ibfspr);
                    }
                }
            }
        }
    }

}

void DESTROY(){

}