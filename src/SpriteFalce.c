#include "Banks/SetBank13.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//SCYTHE
const UINT8 falce_attack[] = {1, 0}; //The first number indicates the number of frames
const UINT8 falce_base[] = {1, 1}; //The first number indicates the number of frames
const UINT8 falce_idle[] = {1, 2}; //The first number indicates the number of frames

void Start_SpriteFalce() {
	THIS->coll_x = 2;
	THIS->coll_y = 1;
	THIS->coll_w = 4;
	THIS->coll_h = 11;
	THIS->lim_x = 120u;
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
		case ENEMY_STATE_SLIDING:
			SetSpriteAnim(THIS, falce_base, 8u);
			//THIS->y = //dovrei creare un nuovo custom_data con stato e Sprite* ,
			//così ho continuamente il mio creatore,
			//devo però modificare la Start perchè varrebbe per tutti
		break;
		case ENEMY_STATE_HIDDEN:
			if(falcedata->wait == 60u){
				falcedata->wait = 0u;	
				SetSpriteAnim(THIS, falce_attack, 8u);
				falcedata->enemy_state = ENEMY_STATE_ATTACK;
			}
		break;
		case ENEMY_STATE_ATTACK:
			if(falcedata->wait < 28u){
				THIS->y--;
			}else if(falcedata->wait < 84u){
				if(falcedata->wait & 1){
					THIS->y++;
				}
			}else if(falcedata->wait == 84u){
				SetSpriteAnim(THIS, falce_idle, 8u);
				THIS->y = falcedata->enemy_accel_y;
			}else if (falcedata->wait == 120u){
				falcedata->wait = 0u;
				falcedata->enemy_state = ENEMY_STATE_HIDDEN;
			}
		break;
	}
}

void Destroy_SpriteFalce(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}