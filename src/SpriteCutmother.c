#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"

#include "custom_datas.h"
#include "Dialogs.h"

extern UINT8 diag_found;
extern void Build_Next_Dialog() BANKED;

const UINT8 mother_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_cutmother_walk[] = {4, 0, 1, 0, 2}; //The first number indicates the number of frames
const UINT8 anim_cutmother_shoot[] = {3,4,3,4};
extern UINT8 colliding_mother;
extern INT8 is_on_cutscene;

struct EnemyInfo* mother_data;
INT8 cooldown = 0;

void ShootCutmother();

void START(){
    THIS->lim_x = 255u;
    THIS->lim_y = 255u;
	SetSpriteAnim(THIS, mother_idle, 8u);
   	mother_data = (struct EnemyInfo*)THIS->custom_data;
    mother_data->enemy_state = ENEMY_STATE_WAIT;
    mother_data->enemy_accel_y = 24;
    mother_data->vx = 0;
}

void ShootCutmother(){
    SetSpriteAnim(THIS, anim_cutmother_shoot, 8u);
	Sprite* arrow_cutsprite = SpriteManagerAdd(SpriteArrowmother, THIS->x+2u, THIS->y-2u);
    if(is_on_cutscene){
        struct EnemyInfo* arrow_cutsprite_data = (struct EnemyInfo*) arrow_cutsprite->custom_data;
        arrow_cutsprite_data->enemy_state = ARROWMOTHER_CUTSCENE;
    }
	//PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);
	//struct ArrowInfo* arrow_cutdata = (struct ArrowInfo*)arrow_cutsprite->custom_data;
    //arrow_cutdata->type = 2;
    //mother_data->enemy_state = ENEMY_STATE_WAIT;
}
void UPDATE(){

    UINT8 smother_tile;
    Sprite* mspr;
    switch(mother_data->enemy_state){
        case ENEMY_STATE_ATTACK:
            if(cooldown == 0){
                ShootCutmother();
                cooldown++;
            }else if (cooldown < 20){
                cooldown++;
            }else if (cooldown == 20){
                mother_data->enemy_state = ENEMY_STATE_WAIT;
            }
        break;
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, mother_idle, 8u);
            SPRITEMANAGER_ITERATE(smother_tile, mspr) {
                if(mspr->type == SpritePlayer) {
                    if(CheckCollision(THIS, mspr)) {
                        if(colliding_mother == 0u){
                   		    THIS->mirror = V_MIRROR; //SPRITE_SET_VMIRROR(THIS);
                            colliding_mother = 1u;
                            Build_Next_Dialog();
                        }
                    }
                }
            }
        break;
        case ENEMY_STATE_WALKING:
            SetSpriteAnim(THIS, anim_cutmother_walk, 8u);
        break;
    }

}

void DESTROY(){

}