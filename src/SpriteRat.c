#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//RAT
const UINT8 rat_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 rat_walk[] = {4, 0, 5, 1, 5}; //The first number indicates the number of frames
const UINT8 rat_hit[] = {3, 2, 3, 4}; //The first number indicates the number of frames
const UINT8 rat_dead[] = {1, 5}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();
extern void EDie();


void Start_SpriteRat() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 5;
	THIS->coll_w = 8;
	THIS->coll_h = 11;
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

void Update_SpriteRat() {
	
	struct EnemyInfo* scorpiondata = (struct EnemyInfo*)THIS->custom_data;
	
	scorpiondata->wait -= 1u;
	
	if (scorpiondata->enemy_state == ENEMY_STATE_DEAD){
		if (scorpiondata->wait == 0){
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (scorpiondata->enemy_state == ENEMY_STATE_HIT){		
		if (scorpiondata->wait == 0u){
			SetSpriteAnim(THIS, rat_walk, 12u);
			scorpiondata->enemy_state = ENEMY_STATE_NORMAL;
		}
	}
	else if (scorpiondata->wait & 1){
		if(scorpiondata->enemy_accel_y < 24) {
			scorpiondata->enemy_accel_y += 1;
		}
		scorpiondata->tile_e_collision = TranslateSprite(THIS, scorpiondata->vx << delta_time, (scorpiondata->enemy_accel_y >> 4)<< delta_time);
		//CheckCollisionETile();
		if(!scorpiondata->tile_e_collision && delta_time != 0 && scorpiondata->enemy_accel_y < 24) { //Do another iteration if there is no collision
			scorpiondata->enemy_accel_y += 2;
			scorpiondata->tile_e_collision = TranslateSprite(THIS, 0, (scorpiondata->enemy_accel_y >> 4) << delta_time);
		}
		if(scorpiondata->tile_e_collision) {
			if(scorpiondata->enemy_state == ENEMY_STATE_JUMPING & scorpiondata->enemy_accel_y > 0) {
				scorpiondata->enemy_state = ENEMY_STATE_NORMAL;
			}else{
				scorpiondata->enemy_accel_y = 0;	
			}
			CheckCollisionETile();
		}
	}
	
	UINT8 scroll_e_tile;
	struct Sprite* iespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
		if(iespr->type == SpritePlayer) {
			if(CheckCollision(THIS, iespr)) {
				scorpiondata->wait = 24u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
				if (arrowdata->type == 6u){ //spine from porcupine
					return;
				}
				if(scorpiondata->enemy_state != ENEMY_STATE_HIT){
					scorpiondata->wait = 24u;
					scorpiondata->enemy_state = ENEMY_STATE_HIT;
					SetSpriteAnim(THIS, rat_hit, 24u); 
				}
				scorpiondata->hp -= arrowdata->arrowdamage;
				if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					scorpiondata->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (scorpiondata->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					scorpiondata->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (scorpiondata->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(iespr);
				if (scorpiondata->hp <= 0){
					EDie();
				}
			}
		}
	}
	
}

void Destroy_SpriteRat(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}
