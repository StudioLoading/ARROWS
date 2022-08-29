#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"

extern UINT8 wait_c;

const UINT8 anim_cutibex_walk[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames

void START(){
	THIS->lim_x = 200u;
	THIS->lim_y = 200u;
    THIS->mirror = V_MIRROR;//devo farlo diventare un gbr a parte che mi sa che se no salta tutto
	SetSpriteAnim(THIS, anim_cutibex_walk, 12u);
	struct EnemyInfo* cutibex_data = (struct EnemyInfo*)THIS->custom_data;
	cutibex_data->enemy_accel_y = 0u;
    cutibex_data->vx = 1;
    cutibex_data->wait = 0u;
    cutibex_data->enemy_state = ENEMY_STATE_WALKING;
}

void UPDATE(){
	struct EnemyInfo* cutibex_data = (struct EnemyInfo*)THIS->custom_data;
    if(THIS->x == ((UINT16) 15u << 3)){
        cutibex_data->enemy_accel_y = -4;
		PlayFx(CHANNEL_1, 60, 0x54, 0x8c, 0xc2, 0x1b, 0x84);//sfx jump
        THIS->x++;
    }
    if(THIS->x >= ((UINT16) 24u << 3)){
        SpriteManagerRemoveSprite(THIS);
    }
	switch(cutibex_data->enemy_state){
        case ENEMY_STATE_WALKING:
            if(THIS->anim_frame == 1 && cutwolf_data->tile_e_collision){
                PlayFx(CHANNEL_1, 60, 0x3a, 0xd2, 0x00, 0xc0, 0x85);//sfx step
            }
            if(cutibex_data->enemy_accel_y < 3){
                cutibex_data->wait++;
                if((cutibex_data->wait & 0x3) == 0){ //== 0){
                    cutibex_data->enemy_accel_y++;
                }
            }
            TranslateSprite(THIS, cutibex_data->vx << delta_time, cutibex_data->enemy_accel_y << delta_time);
        break;
    }
}

void DESTROY(){
    wait_c = 42u;
}