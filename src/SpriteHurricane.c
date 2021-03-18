#include "Banks/SetBank8.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//THUNDER
const UINT8 hurricane_idle[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 hurricane_walk[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 hurricane_hit[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 hurricane_dead[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();


void Start_SpriteHurricane() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 5;
	THIS->coll_w = 4;
	THIS->coll_h = 12;
	THIS->lim_x = 88u;
	THIS->lim_y = 152u;
	struct EnemyInfo* hdata = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, hurricane_idle, 8u);
	hdata->enemy_accel_y = 28;
	hdata->wait = 4u;
	hdata->hp = 24u;
	hdata->enemy_state = ENEMY_STATE_WAIT;
	hdata->vx = -1;
}

void Update_SpriteHurricane() {
	
	struct EnemyInfo* hdata = (struct EnemyInfo*)THIS->custom_data;
	
	if (hdata->enemy_state == ENEMY_STATE_WAIT){
		hdata->wait -= 1u;
		if (hdata->wait == 0u){
			hdata->wait = 32u;
			SetSpriteAnim(THIS, hurricane_walk, 8u);
			hdata->enemy_state = ENEMY_STATE_NORMAL;
		}
	}
	if(hdata->enemy_state == ENEMY_STATE_NORMAL){
		if(hdata->enemy_accel_y < 28) {
			hdata->enemy_accel_y += 1;
		}
		hdata->tile_e_collision = TranslateSprite(THIS, hdata->vx << delta_time, (hdata->enemy_accel_y >> 4)<< delta_time);
		if(!hdata->tile_e_collision && delta_time != 0 && hdata->enemy_accel_y < 28) { //Do another itethunderion if there is no collision
			hdata->enemy_accel_y += 2;
			hdata->tile_e_collision = TranslateSprite(THIS, hdata->vx << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
		}
		if (hdata->tile_e_collision == 21u | hdata->tile_e_collision == 22u){
			hdata->wait -= 1u;
			TranslateSprite(THIS, (hdata->vx << 1) << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
			if ( hdata->wait == 0u){
				SetSpriteAnim(THIS, hurricane_dead, 10u);
				hdata->enemy_state = ENEMY_STATE_DEAD;				
			}
		}else if (hdata->tile_e_collision == 100u | hdata->tile_e_collision == 101u){
			THIS->y++;
		}
		else if (hdata->tile_e_collision){
			THIS->x+=hdata->vx;
		}
	}
	
	if(hdata->enemy_state == ENEMY_STATE_DEAD){
		TranslateSprite(THIS, (hdata->vx << 1) << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
	}
	
	/* REVERSE DELLE FRECCE / DESTROY SE FRECCE DI TERRA */
	UINT8 hur_tile;
	struct Sprite* hspr;
	SPRITEMANAGER_ITERATE(hur_tile, hspr) {
		if(hspr->type == SpriteArrow) {
			if(CheckCollision(THIS, hspr)) {
				struct ArrowInfo* arritem = (struct ArrowInfo*)hspr->custom_data;
				if (arritem->original_type == 3u){
					hdata->wait = 2u;
					SetSpriteAnim(THIS, hurricane_dead, 10u);
					hdata->enemy_state = ENEMY_STATE_DEAD;
				}
			}
		}
	}
	
}

void Destroy_SpriteHurricane(){
	struct EnemyInfo* hdata = (struct EnemyInfo*)THIS->custom_data;
	hdata->enemy_state = ENEMY_STATE_DEAD;
}
