#include "Banks/SetBank15.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//SCYTHE
const UINT8 falce_attack[] = {1, 0}; //The first number indicates the number of frames
const UINT8 falce_idle[] = {1, 1}; //The first number indicates the number of frames

void Start_SpriteFalce() {
	THIS->mt_sprite->dx = 2;
	THIS->mt_sprite->dy = 1;
	THIS->coll_w = 4;
	THIS->coll_h = 11;
	THIS->lim_x = 80u;
	THIS->lim_y = 60u;
	SetSpriteAnim(THIS, falce_idle, 8u);
	struct EnemyInfo* falcedata = (struct EnemyInfo*)THIS->custom_data;
	falcedata->wait = 0u;
	falcedata->enemy_state = ENEMY_STATE_HIDDEN;
	falcedata->enemy_accel_y = THIS->y;
}

void Update_SpriteFalce() {
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

void Destroy_SpriteFalce(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}