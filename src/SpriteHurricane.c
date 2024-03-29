#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"

//THUNDER
const UINT8 const hurricane_idle[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 const hurricane_walk[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 const hurricane_hit[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 const hurricane_dead[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames

extern void CheckCollisionETile() BANKED;
extern void ETurn() BANKED;


void START() {
	THIS->lim_x = 120u;
	THIS->lim_y = 60u;
	SetSpriteAnim(THIS, hurricane_idle, 8u);
	struct EnemyInfo* hcdata = (struct EnemyInfo*)THIS->custom_data;
	hcdata->enemy_state = ENEMY_STATE_WAIT;
	hcdata->vx = 1;
	hcdata->hp = 48u;
	hcdata->wait = 15u;
	hcdata->enemy_accel_y = 20;
}

void UPDATE() {
	
	struct EnemyInfo* hdata = (struct EnemyInfo*)THIS->custom_data;
	
	if(hdata->hp == 0){
		hdata->enemy_state = ENEMY_STATE_DEAD;
	}
	
	switch (hdata->enemy_state){
		case ENEMY_STATE_NORMAL:
			if(hdata->enemy_accel_y < 20) {
				hdata->enemy_accel_y += 1;
			}
			hdata->wait += 1u;
			if(hdata->wait == 40u){
				hdata->wait = 0u;
			}
			if(hdata->wait < 20u){
				hdata->vx = 1;
			}else{
				hdata->vx = -1;
				
			}
			hdata->tile_e_collision = TranslateSprite(THIS, hdata->vx << delta_time,  (hdata->enemy_accel_y >> 4) << delta_time); // 1
			if(!hdata->tile_e_collision && delta_time != 0) { //Do another iteration if there is no collision
				hdata->tile_e_collision = TranslateSprite(THIS, (hdata->vx << 1) << delta_time, (hdata->enemy_accel_y >> 4) << delta_time);
			}
			if(hdata->tile_e_collision){
				hdata->hp-=1u;
			}
		break;
		case ENEMY_STATE_WAIT:
			hdata->wait -= 1u;
			if (hdata->wait == 0u){
				hdata->wait = 32u;
				SetSpriteAnim(THIS, hurricane_walk, 8u);
				hdata->enemy_state = ENEMY_STATE_NORMAL;
			}
		break;
		case ENEMY_STATE_DEAD:
			SpriteManagerRemoveSprite(THIS);
		break;
	}
	
	/* REVERSE DELLE FRECCE / DESTROY SE FRECCE DI TERRA */
	UINT8 hur_tile;
	Sprite* hspr;
	SPRITEMANAGER_ITERATE(hur_tile, hspr) {
		if(hspr->type == SpriteArrow) {
			if(CheckCollision(THIS, hspr)) {
				struct ArrowInfo* arritem = (struct ArrowInfo*)hspr->custom_data;
				if (arritem->original_type == 2u){
					hdata->wait = 10u;
					PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);//sfx hit
					SetSpriteAnim(THIS, hurricane_dead, 10u);
					hdata->enemy_state = ENEMY_STATE_DEAD;
					SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
				}
			}
		}
	}
	
}

void DESTROY() {
	struct EnemyInfo* hdata_dying = (struct EnemyInfo*)THIS->custom_data;
	hdata_dying->enemy_state = ENEMY_STATE_DEAD;
}
