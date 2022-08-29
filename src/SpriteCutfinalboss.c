#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "Dialogs.h"

extern void Build_Next_Dialog() BANKED;

const UINT8 cutfinalboss_idle[] = {5, 0, 0, 0, 0, 1}; //The first number indicates the number of frames
const UINT8 cutfinalboss_hit[] = {2, 3, 4}; //The first number indicates the number of frames
const UINT8 cutfinalboss_grappling[] = {1, 2};
extern UINT8 colliding_mother;
struct EnemyInfo* cutfinalboss_data;

void START(){
    THIS->lim_x = 255u;
    THIS->lim_y = 255u;
	SetSpriteAnim(THIS, cutfinalboss_idle, 8u);
   	cutfinalboss_data = (struct EnemyInfo*)THIS->custom_data;
    cutfinalboss_data->enemy_state = ENEMY_STATE_WAIT;
    cutfinalboss_data->enemy_accel_y = 24;
    cutfinalboss_data->vx = 0;
    cutfinalboss_data->wait = 0u;
}

void UPDATE(){
    UINT8 scutfinalboss_tile;
    Sprite* cfbspr;
    switch(cutfinalboss_data->enemy_state){
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, cutfinalboss_idle, 8u);
            SPRITEMANAGER_ITERATE(scutfinalboss_tile, cfbspr) {
                if(CheckCollision(THIS, cfbspr)) {
                    if(cfbspr->type == SpritePlayer) {
                        if(colliding_mother == 0u){
                   		    THIS->mirror = V_MIRROR; //SPRITE_SET_VMIRROR(THIS);
                            colliding_mother = 1u;
                            Build_Next_Dialog();
                        }
                    }
                    if(cfbspr->type == SpriteCutwolf || cfbspr->type == SpriteCutibex || cfbspr->type == SpriteCutbear){
                        cutfinalboss_data->wait = 0u;
                        cutfinalboss_data->enemy_state = ENEMY_STATE_HIT;
                    }
                }
            }
        break;
        case ENEMY_STATE_WALKING:
            SetSpriteAnim(THIS, cutfinalboss_idle, 8u);
        break;
        case ENEMY_STATE_GRAPPLING:
            SetSpriteAnim(THIS, cutfinalboss_grappling, 1u);
        break;
        case ENEMY_STATE_HIT:
            SetSpriteAnim(THIS, cutfinalboss_hit, 24u);
            if(THIS->anim_frame == 0){
                PlayFx(CHANNEL_1, 60, 0x44, 0x82, 0xf3, 0x45, 0x85);//sfx hit
            }
            cutfinalboss_data->wait++;
            if(cutfinalboss_data->wait == 120u){
                cutfinalboss_data->wait = 0u;
                cutfinalboss_data->enemy_state = ENEMY_STATE_WAIT;
            }
        break;
    }
}

void DESTROY(){

}