#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"

extern UINT8 wait_c;

const UINT8 anim_cutwolf_walk[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames
const UINT8 anim_cutwolf_talking[] = {1, 2}; //The first number indicates the number of frames
const UINT8 anim_cutwolf_uuu[] = {1, 5}; //The first number indicates the number of frames


void START(){
	THIS->lim_x = 200u;
	THIS->lim_y = 200u;
    THIS->mirror = V_MIRROR;//devo farlo diventare un gbr a parte che mi sa che se no salta tutto
	SetSpriteAnim(THIS, anim_cutwolf_walk, 12u);
	struct EnemyInfo* cutwolf_data = (struct EnemyInfo*)THIS->custom_data;
	cutwolf_data->enemy_accel_y = 0u;
    cutwolf_data->vx = 1;
    cutwolf_data->wait = 0u;
    cutwolf_data->enemy_state = ENEMY_STATE_WALKING;
}

void UPDATE(){
	struct EnemyInfo* cutwolf_data = (struct EnemyInfo*)THIS->custom_data;
    if(THIS->x == ((UINT16) 15u << 3)){
        cutwolf_data->enemy_accel_y = -4;
        cutwolf_data->vx++;
		PlayFx(CHANNEL_1, 60, 0x54, 0x8c, 0xc2, 0x1b, 0x84);//sfx jump
        THIS->x++;
    }
    if(THIS->x >= ((UINT16) 24u << 3)){
        SpriteManagerRemoveSprite(THIS);
    }
	switch(cutwolf_data->enemy_state){
        case ENEMY_STATE_WALKING:
            if(THIS->anim_frame == 1 && cutwolf_data->tile_e_collision != 0){
                PlayFx(CHANNEL_1, 60, 0x3a, 0xd2, 0x00, 0xc0, 0x85);//sfx step
            }
            if(cutwolf_data->enemy_accel_y < 3){
                cutwolf_data->wait++;
                if((cutwolf_data->wait & 0x3) == 0){ //== 0){
                    cutwolf_data->enemy_accel_y++;
                }
            }
            cutwolf_data->tile_e_collision = TranslateSprite(THIS, cutwolf_data->vx << delta_time, cutwolf_data->enemy_accel_y << delta_time);
        break;
        case ENEMY_STATE_WAIT:
            SetSpriteAnim(THIS, anim_cutwolf_talking, 4u);
        break;
        case ENEMY_STATE_HIDDEN:
            SetSpriteAnim(THIS, anim_cutwolf_uuu, 4u);
        break;
    }
}

void DESTROY(){
    wait_c = 42u;
}