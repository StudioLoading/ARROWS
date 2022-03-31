#include "Banks/SetBank6.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "Dialogs.h"

extern UINT8 diag_found;
extern void Build_Next_Dialog();

const UINT8 mother_idle[] = {1, 0}; //The first number indicates the number of frames
extern UINT8 colliding_mother;
struct EnemyInfo* mother_data;

void Start_SpriteMother(){
	SetSpriteAnim(THIS, mother_idle, 8u);
    THIS->mt_sprite->dx = 0;
    THIS->mt_sprite->dy = 0;
    THIS->coll_w = 16;
    THIS->coll_h = 16;
   	mother_data = (struct EnemyInfo*)THIS->custom_data;
    mother_data->enemy_state = ENEMY_STATE_WAIT;
    mother_data->enemy_accel_y = 24;
    mother_data->vx = 0;
}

void Update_SpriteMother(){

   	struct EnemyInfo* cutmother = (struct EnemyInfo*)THIS->custom_data;

    UINT8 smother_tile;
    Sprite* mspr;
    switch(mother_data->enemy_state){
        case ENEMY_STATE_WAIT:
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
            TranslateSprite(THIS, (cutmother->vx >> 4) << delta_time, (cutmother->enemy_accel_y >> 4) << delta_time);
        break;
    }

}

void Destroy_SpriteMother(){

}