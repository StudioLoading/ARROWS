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
	THIS->coll_x = 1;
	THIS->coll_y = 2;
	THIS->coll_w = 7;
	THIS->coll_h = 12;
	THIS->lim_x = 80u;
	THIS->lim_y = 64u;
	SetSpriteAnim(THIS, hurricane_idle, 8u);
	struct EnemyInfo* hhdata = (struct EnemyInfo*)THIS->custom_data;	
	hhdata->enemy_accel_y = 28;
	hhdata->vx = 1;
	hhdata->wait = 4u;
	hhdata->hp = 24u;
	hhdata->enemy_state = ENEMY_STATE_WAIT;
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
		//hdata->vx << delta_time
		hdata->tile_e_collision = TranslateSprite(THIS, hdata->vx, (hdata->enemy_accel_y >> 4)<< delta_time);
		if(!hdata->tile_e_collision && delta_time != 0 && hdata->enemy_accel_y < 28) { //Do another iteration if there is no collision
			hdata->enemy_accel_y += 2;
			hdata->tile_e_collision = TranslateSprite(THIS, hdata->vx << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
		}		
		switch(hdata->tile_e_collision){
			case 2u:
			case 18u:
			case 20u:
			case 21u:
			case 22u:
			case 23u:
			case 29u:
			case 40u:
				hdata->wait -= 1u;
				TranslateSprite(THIS, - (hdata->vx << 1) << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
				if ( hdata->wait == 0u){
					SetSpriteAnim(THIS, hurricane_dead, 10u);
					hdata->enemy_state = ENEMY_STATE_DEAD;
				}
			break;
			
			case 100u:
			case 101u:
				THIS->y++;
			break;
		}
		/*else if (hdata->tile_e_collision){
			THIS->x+=hdata->vx;
		}*/
	}
	
	if(hdata->enemy_state == ENEMY_STATE_DEAD){
		//TranslateSprite(THIS, (hdata->vx << 1) << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
		SpriteManagerRemoveSprite(THIS);
	}
	
	/* REVERSE DELLE FRECCE / DESTROY SE FRECCE DI TERRA */
	UINT8 hur_tile;
	struct Sprite* hspr;
	SPRITEMANAGER_ITERATE(hur_tile, hspr) {
		if(hspr->type == SpriteArrow) {
			if(CheckCollision(THIS, hspr)) {
				struct ArrowInfo* arritem = (struct ArrowInfo*)hspr->custom_data;
				if (arritem->original_type == 2u){
					hdata->wait = 10u;
					SetSpriteAnim(THIS, hurricane_dead, 10u);
					hdata->enemy_state = ENEMY_STATE_DEAD;
				}
			}
		}
	}
	
}

void Destroy_SpriteHurricane(){
	struct EnemyInfo* hdata_dying = (struct EnemyInfo*)THIS->custom_data;
	hdata_dying->enemy_state = ENEMY_STATE_DEAD;
}
