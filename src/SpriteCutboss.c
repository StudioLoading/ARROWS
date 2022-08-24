#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "CircleMath.h"

const UINT8 anim_cutboss_ready[] = {3, 0, 0, 3}; //The first number indicates the number of frames
const UINT8 anim_cutboss_oneagle[] = {1, 2}; //The first number indicates the number of frames
const UINT8 anim_cutboss_knee[] = {1, 1}; //The first number indicates the number of frames


void START(){
	SetSpriteAnim(THIS, anim_cutboss_oneagle, 1u);
	struct EnemyInfo* cutboss_data = (struct EnemyInfo*)THIS->custom_data;
	cutboss_data->enemy_accel_y = 2u;
}

void UPDATE(){
	struct EnemyInfo* cutboss_data = (struct EnemyInfo*)THIS->custom_data;
	switch(cutboss_data->enemy_state){
		case ENEMY_STATE_JUMPING:
			cutboss_data->tile_e_collision = TranslateSprite(THIS, 0u, cutboss_data->enemy_accel_y << delta_time);
			if(cutboss_data->tile_e_collision != 0){
				cutboss_data->wait = 160u;
				SetSpriteAnim(THIS, anim_cutboss_knee, 1u);
				cutboss_data->enemy_state = ENEMY_STATE_NORMAL;
			}
		break;
		case ENEMY_STATE_NORMAL:
			cutboss_data->wait--;
			if(cutboss_data->wait == 0){
				SetSpriteAnim(THIS, anim_cutboss_ready, 12u);
				cutboss_data->enemy_state = ENEMY_STATE_WAIT;
			}
		break;
		case ENEMY_STATE_GRAPPLING:
			SetSpriteAnim(THIS, anim_cutboss_oneagle, 1u);
		break;
	}

}

void DESTROY(){

}