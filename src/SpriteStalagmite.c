#include "Banks/SetBank9.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//STALAGMITE
const UINT8 stalag_drop[] = {1, 5}; //The first number indicates the number of frames
const UINT8 stalag_drop_big[] = {1, 4}; //The first number indicates the number of frames
const UINT8 stalag_walk[] = {4, 0, 5, 1, 5}; //The first number indicates the number of frames
const UINT8 stalag_hit[] = {3, 2, 3, 4}; //The first number indicates the number of frames
const UINT8 stalag_dead[] = {1, 5}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();

void CheckCollisionStalagTile(UINT8 ta);

void Start_SpriteStalagmite() {
	
	THIS->coll_x = 1;
	THIS->coll_y = 4;
	THIS->coll_w = 6;
	THIS->coll_h = 4;
	THIS->lim_x = 200u;
	THIS->lim_y = 80u;
	SetSpriteAnim(THIS, stalag_drop_big, 4u);
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;	
	rdata->enemy_accel_y = 20;
	rdata->vx = 0;
	rdata->wait = 20u;
	rdata->hp = 24u;
	rdata->enemy_state = ENEMY_STATE_WAIT;
}

void Update_SpriteStalagmite() {
	
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;
	if(rdata->wait > 5u){
		rdata->wait -= 1u;
		return;
	}
	if(rdata->enemy_state == ENEMY_STATE_WAIT){
		SetSpriteAnim(THIS, stalag_drop, 4u);
		rdata->enemy_state = ENEMY_STATE_NORMAL;
		return;
	}else if(rdata->enemy_state == ENEMY_STATE_NORMAL){
		rdata->tile_e_collision = TranslateSprite(THIS, rdata->vx << delta_time, (rdata->enemy_accel_y >> 4)<< delta_time);
		if(rdata->tile_e_collision) {
			if(rdata->enemy_accel_y > 0) {
				rdata->enemy_state = ENEMY_STATE_NORMAL;
			}else{
				rdata->enemy_accel_y = 0;	
			}
			CheckCollisionStalagTile(rdata->tile_e_collision);
		}
		
	}
	
	UINT8 scroll_st_tile;
	struct Sprite* istspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_st_tile, istspr) {
		if(istspr->type == SpritePlayer || istspr->type == SpriteArrow) {
			if(CheckCollision(THIS, istspr)) {
				CheckCollisionStalagTile(12u);
			}
		}
		if(istspr->type == SpriteStalagmite) {
			if(CheckCollision(THIS, istspr)) {
				//THIS->y += 1u;
				//fai crescere quella a terra, istspr deve crescere,
			}
		}
	}
	
}

void CheckCollisionStalagTile(UINT8 ta){
	switch(ta){
		case 12u:
			SpriteManagerRemoveSprite(THIS); // elimino me stesso
		break;
	}
}

void Destroy_SpriteStalagmite(){
	SpriteManagerAdd(SpritePuff, THIS->x, (UINT16)THIS->y-3u);
}
