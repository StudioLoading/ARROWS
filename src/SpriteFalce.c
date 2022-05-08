#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"


//SCYTHE
const UINT8 falce_attack[] = {1, 1}; //The first number indicates the number of frames
const UINT8 falce_idle[] = {1, 0}; //The first number indicates the number of frames

void START() {
	THIS->lim_x = 80u;
	THIS->lim_y = 60u;
	SetSpriteAnim(THIS, falce_idle, 8u);
	struct EnemyInfo* falcedata = (struct EnemyInfo*)THIS->custom_data;
	falcedata->wait = 0u;
	falcedata->enemy_state = ENEMY_STATE_HIDDEN;
	falcedata->enemy_accel_y = THIS->y;
}

void UPDATE() {
	struct EnemyInfo* falcedata = (struct EnemyInfo*)THIS->custom_data;
	falcedata->wait++;
	switch(falcedata->enemy_state){
		case ENEMY_STATE_HIDDEN:
			if(falcedata->wait == 60u){
				falcedata->wait = 0u;	
				SetSpriteAnim(THIS, falce_attack, 8u);
				falcedata->enemy_state = ENEMY_STATE_ATTACK;
			}
		break;
		case ENEMY_STATE_ATTACK:
			if(falcedata->wait < 14u){
				THIS->y--;				
				THIS->y--;
			}else{
				falcedata->archer_posx = 40u;
				falcedata->enemy_state = ENEMY_STATE_WAIT;
			}
		break;
		case ENEMY_STATE_WAIT:
			falcedata->archer_posx--;
			if(falcedata->archer_posx == 0){
				falcedata->wait = 14u;
				falcedata->enemy_state = ENEMY_STATE_JUMPING;
			}
		break;
		case ENEMY_STATE_JUMPING:
			if(falcedata->wait < 64u){
				if(falcedata->wait & 0b010){
					THIS->y++;
				}
			}else if(falcedata->wait == 64u){
				SetSpriteAnim(THIS, falce_idle, 8u);
				THIS->y = falcedata->enemy_accel_y;
			}else if (falcedata->wait == 84u){
				falcedata->wait = 0u;
				falcedata->enemy_state = ENEMY_STATE_HIDDEN;
			}
		break;
	}
}

void DESTROY(){
}