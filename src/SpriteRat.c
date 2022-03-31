#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//RAT
const UINT8 rat_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 rat_walk[] = {4, 0, 2, 1, 2}; //The first number indicates the number of frames
const UINT8 rat_hit[] = {2, 0, 3}; //The first number indicates the number of frames
const UINT8 rat_dead[] = {1, 2}; //The first number indicates the number of frames

extern void CheckCollisionETile() BANKED;
extern void ETurn() BANKED;
extern void EDie() BANKED;


void START() {
	/*
	THIS->mt_sprite->dx = 2;
	THIS->mt_sprite->dy = 5;
	THIS->coll_w = 8;
	THIS->coll_h = 11;
	*/
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, rat_walk, 8u);
	rdata->enemy_accel_y = 24;
	rdata->vx = 1;
	rdata->wait = 20u;
	rdata->hp = 24u;
	rdata->enemy_state = ENEMY_STATE_NORMAL;
}

void UPDATE() {
	
	struct EnemyInfo* ratdata = (struct EnemyInfo*)THIS->custom_data;
	
	ratdata->wait -= 1u;
	
	if (ratdata->enemy_state == ENEMY_STATE_DEAD){
		if (ratdata->wait == 0){
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (ratdata->enemy_state == ENEMY_STATE_HIT){		
		if (ratdata->wait == 0u){
			SetSpriteAnim(THIS, rat_walk, 12u);
			ratdata->enemy_state = ENEMY_STATE_NORMAL;
		}
	}
	else if (ratdata->wait & 1){
		if(ratdata->enemy_accel_y < 24) {
			ratdata->enemy_accel_y += 1;
		}
		ratdata->tile_e_collision = TranslateSprite(THIS, ratdata->vx << delta_time, (ratdata->enemy_accel_y >> 4)<< delta_time);
		//CheckCollisionETile();
		if(!ratdata->tile_e_collision && delta_time != 0 && ratdata->enemy_accel_y < 24) { //Do another iteration if there is no collision
			ratdata->enemy_accel_y += 2;
			ratdata->tile_e_collision = TranslateSprite(THIS, 0, (ratdata->enemy_accel_y >> 4) << delta_time);
		}
		if(ratdata->tile_e_collision) {
			if(ratdata->enemy_state == ENEMY_STATE_JUMPING && ratdata->enemy_accel_y > 0) {
				ratdata->enemy_state = ENEMY_STATE_NORMAL;
			}else{
				ratdata->enemy_accel_y = 0;	
			}
			CheckCollisionETile();
		}
	}
	
	UINT8 scroll_r_tile;
	Sprite* irspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_r_tile, irspr) {
		if(irspr->type == SpritePlayer) {
			if(CheckCollision(THIS, irspr)) {
				ratdata->wait = 24u;
			}
		}
		if(irspr->type == SpriteArrow) {
			if(CheckCollision(THIS, irspr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)irspr->custom_data;
				if (arrowdata->type == 6u){ //spine from porcupine
					return;
				}
				ratdata->wait = 16u;
				SetSpriteAnim(THIS, rat_hit, 24u); 
				ratdata->hp -= arrowdata->arrowdamage;
				if (THIS->x < irspr->x){ //se la freccia arriva dalla destra dell' enemy
					if (THIS->mirror == V_MIRROR){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					ratdata->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (ratdata->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (THIS->mirror != V_MIRROR){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					ratdata->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (ratdata->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(irspr);
				if (ratdata->hp <= 0){
					EDie();
				}
			}
		}
	}
	
}

void DESTROY(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-3u);
}
