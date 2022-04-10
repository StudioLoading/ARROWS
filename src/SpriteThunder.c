#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//THUNDER
const UINT8 thunder_idle[] = {2, 4, 6}; //The first number indicates the number of frames
const UINT8 thunder_walk[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 thunder_hit[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 thunder_dead[] = {2, 3, 5}; //The first number indicates the number of frames

extern void CheckCollisionETile() BANKED;
extern void ETurn() BANKED;


void START() {	
	THIS->lim_x = 120u;
	THIS->lim_y = 60u;
	struct EnemyInfo* tdata = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, thunder_idle, 8u);
	tdata->enemy_accel_y = 42;
	tdata->wait = 16u;
	tdata->hp = 24u;
	tdata->enemy_state = ENEMY_STATE_WAIT;
	tdata->vx = (THIS->x & 1);
}

void UPDATE() {
	
	struct EnemyInfo* tdata = (struct EnemyInfo*)THIS->custom_data;
	
	if (tdata->enemy_state == ENEMY_STATE_WAIT){
		tdata->wait -= 1u;
		if (tdata->wait == 0u){
			SetSpriteAnim(THIS, thunder_walk, 8u);
			tdata->enemy_state = ENEMY_STATE_NORMAL;
		}
		return;
	}
	if(tdata->enemy_state == ENEMY_STATE_NORMAL){
		if(tdata->enemy_accel_y < 42) {
				tdata->enemy_accel_y += 1;
		}
		tdata->tile_e_collision = TranslateSprite(THIS, tdata->vx << delta_time, (tdata->enemy_accel_y >> 4) << delta_time);
		if(!tdata->tile_e_collision && delta_time != 0 && tdata->enemy_accel_y < 42) { //Do another itethunderion if there is no collision
			tdata->enemy_accel_y += 2;
		}
		switch(tdata->tile_e_collision){
			case 2u:
			case 7u:
			case 18u:
			case 20u:
			case 21u:
			case 22u:
			case 23u:
			case 29u:
			case 40u:
			case 104u:
				tdata->wait = 16u;
				SetSpriteAnim(THIS, thunder_dead, 10u);
				tdata->enemy_state = ENEMY_STATE_DEAD;
			break;
			case 100u:
			case 101u:
			case 102u:
			case 103u:
				THIS->y++;
			break;
		}
	}
	
	if(tdata->enemy_state == ENEMY_STATE_DEAD){
		tdata->wait--;
		if(tdata->wait == 0u){
			SpriteManagerRemove(THIS_IDX);
		}
	}
	
	UINT8 thu_tile;
	Sprite* thuspr;
	SPRITEMANAGER_ITERATE(thu_tile, thuspr) {
		if(thuspr->type == SpriteArrow) {
			if(CheckCollision(THIS, thuspr)) {
				struct ArrowInfo* arritem = (struct ArrowInfo*)thuspr->custom_data;
				if (arritem->original_type == 2u){
					tdata->wait = 2u;
					SetSpriteAnim(THIS, thunder_dead, 10u);
					tdata->enemy_state = ENEMY_STATE_DEAD;
					SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
				}
			}
		}
	}	
	
}

void DESTROY(){
	struct EnemyInfo* tdata = (struct EnemyInfo*)THIS->custom_data;
	tdata->enemy_state = ENEMY_STATE_DEAD;
}
