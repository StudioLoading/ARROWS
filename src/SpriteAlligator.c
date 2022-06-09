#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//ALLIGATOR
const UINT8 alligator_invisible[] = {1, 6}; //The first number indicates the number of frames
const UINT8 alligator_hide[] = {6, 0, 1, 0, 1, 0, 1}; //The first number indicates the number of frames
const UINT8 alligator_bite[] = {7, 5, 4, 3, 2, 2, 2, 5}; //The first number indicates the number of frames
const UINT8 alligator_hit[] = {6, 3, 6, 3, 6, 3, 6}; //The first number indicates the number of frames
const UINT8 alligator_dead[] = {1, 7}; //The first number indicates the number of frames
const UINT8 alligator_normal[] = {1, 5}; //The first number indicates the number of frames

const UINT16 boss_posx[] = {9u, 24u, 16u};
UINT8 poss = 0;
struct EnemyInfo* alligator_data ;


void START() {
	alligator_data = (struct EnemyInfo*)THIS->custom_data;
	/*THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 0;
	THIS->coll_w = 0;
	THIS->coll_h = 0;*/
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	SetSpriteAnim(THIS, alligator_hide, 16u);
	alligator_data->enemy_accel_y = 24;
	alligator_data->vx = 0;
	alligator_data->wait = 250u;
	alligator_data->hp = 3;
	alligator_data->enemy_state = ENEMY_STATE_HIDDEN;
}

void UPDATE() {
	/*
	if(alligator_data->enemy_state == ENEMY_STATE_ATTACK){	
		THIS->coll_w = 16;
		THIS->coll_h = 16;
	}
	*/
	if(alligator_data->enemy_state == ENEMY_STATE_WAIT){
		return;
	}
	
	if (alligator_data->enemy_state == ENEMY_STATE_DEAD){
		SetSpriteAnim(THIS, alligator_dead, 4u);
		TranslateSprite(THIS, 0, 1);
		alligator_data->hp = 0;
		return;
	}
	
	alligator_data->wait -= 1u;	
	if (alligator_data->wait == 100u){
		poss++;
		if (poss == 3u | (poss == 1u && alligator_data->hp == 1)) {
			poss = 0u;
			if (alligator_data->archer_posx > 60u & alligator_data->archer_posx < 224u)
			THIS->x = alligator_data->archer_posx;
		}else{
			THIS->x = boss_posx[poss] << 3;
		}
		alligator_data->enemy_state = ENEMY_STATE_INVISIBLE;
		SetSpriteAnim(THIS, alligator_invisible, 8u);
	}
	if (alligator_data->wait >= 100u & alligator_data->wait <= 120u){
		if (poss){
			TranslateSprite(THIS, -1 << delta_time, 1);
		}else{
			TranslateSprite(THIS, 1 << delta_time, 1);	
		}

	}
	if (alligator_data->wait == 230u){
		alligator_data->enemy_state = ENEMY_STATE_HIDDEN;
		SetSpriteAnim(THIS, alligator_hide, 8u);
	}else if (alligator_data->wait == 180u){
		alligator_data->enemy_state = ENEMY_STATE_ATTACK;
		SetSpriteAnim(THIS, alligator_bite, 10u);
	}else if (alligator_data->wait == 120u){
		alligator_data->enemy_state = ENEMY_STATE_NORMAL;
		SetSpriteAnim(THIS, alligator_normal, 8u);			
	}

	UINT8 scroll_a_tile;
	Sprite* iaspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_a_tile, iaspr) {
		if(CheckCollision(THIS, iaspr) && alligator_data->enemy_state != ENEMY_STATE_DEAD) {
			switch (iaspr->type){
				case SpritePlayer:
					alligator_data->wait = 24u;
				break;
				case SpriteArrow:
					if(alligator_data->enemy_state == ENEMY_STATE_NORMAL || alligator_data->enemy_state == ENEMY_STATE_ATTACK){
						struct ArrowInfo* arrowdata = (struct ArrowInfo*)iaspr->custom_data;
						if (arrowdata->original_type == 2){ //hit only with stoned arrows
							alligator_data->enemy_state = ENEMY_STATE_HIDDEN;
							alligator_data->wait = 24u;
							SetSpriteAnim(THIS, alligator_hit, 18u);
							alligator_data->hp -= 1;
							if (alligator_data->hp <= 0){
								alligator_data->hp = 0;
								alligator_data->enemy_state = ENEMY_STATE_DEAD;
								SetSpriteAnim(THIS, alligator_dead, 16u);
								THIS->x = (UINT16) 21u << 3;
								THIS->y = (UINT16) 14u << 3;
							}
							alligator_data->wait = 121u;
						}
						SpriteManagerRemoveSprite(iaspr);
					}
				break;
			}
		}
	}
	
}

void DESTROY() {
}
