#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"

//SNAKE
const UINT8 enemy_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 enemy_walk[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 enemy_hit[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 attack_wait = 32u;

void CheckCollisionETile() BANKED;
void ETurn() BANKED;
void EDie() BANKED;

void START() {
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, enemy_idle, 8u);
	edata->enemy_state = ENEMY_STATE_NORMAL;
	edata->hp = 25;
	edata->enemy_accel_y = 24;
	edata->vx = -1;
	edata->wait = 0u;
	THIS->mirror = V_MIRROR;
}

void UPDATE() {
	
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	
	if (edata->enemy_state == ENEMY_STATE_DEAD){				
		return;
	}
	
	if (edata->wait > 0u){
		edata->wait -= 1u;
		if (edata->wait == 0u){
			SetSpriteAnim(THIS, enemy_walk, 8u);
		}
	}else{
		if(edata->enemy_accel_y < 24) {
			edata->enemy_accel_y += 1;
		}
		edata->tile_e_collision = TranslateSprite(THIS, edata->vx << delta_time, (edata->enemy_accel_y >> 4)<< delta_time);
		//CheckCollisionETile();
		if(!edata->tile_e_collision && delta_time != 0 && edata->enemy_accel_y < 24) { //Do another iteration if there is no collision
			edata->enemy_accel_y += 2;
			edata->tile_e_collision = TranslateSprite(THIS, 0, (edata->enemy_accel_y >> 4) << delta_time);
		}
		if(edata->tile_e_collision) {
			if(edata->enemy_state == ENEMY_STATE_JUMPING && edata->enemy_accel_y > 0) {
				edata->enemy_state = ENEMY_STATE_NORMAL;
			}else{
				edata->enemy_accel_y = 0;	
			}
			CheckCollisionETile();
		}
	}//fine else non wait
	
	UINT8 scroll_e_tile;
	Sprite* iespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
		if(iespr->type == SpritePlayer) {
			if(CheckCollision(THIS, iespr)) {
				edata->wait = 24u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
				if (arrowdata->type == 6u){ //spine from porcupine
					return;
				}
				edata->wait = 16u;
				SetSpriteAnim(THIS, enemy_hit, 24u);
				edata->hp -= arrowdata->arrowdamage;
				PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);//hit sound
				if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (THIS->mirror == V_MIRROR){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					edata->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (edata->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (THIS->mirror != V_MIRROR){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					edata->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (edata->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(iespr);
				if (edata->hp <= 0){
					EDie();
				}
			}
		}
	}
	
}

void EDie() BANKED{
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	edata->hp = -1;
	edata->wait = 16u;
	THIS->coll_h = 0;
	THIS->coll_w = 0;
	edata->enemy_state = ENEMY_STATE_DEAD;
	SpriteManagerRemoveSprite(THIS);
}

void CheckCollisionETile() BANKED{
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	switch(edata->tile_e_collision) {
		case 3u:
		case 4u:
		case 5u:
		case 7u:
		case 11u:
		case 13u:
		case 16u:
		case 17u:
		case 18u:
		case 20u:
		case 22u:
		case 29u:
		case 69u:
		case 70u:
		case 73u:
		case 74u:
		case 75u:
		case 81u:
			ETurn();
		break;
		case 2u://spuncioni alti
		case 23u://spuncioni bassi
		case 40u://skull of death
			EDie();
		break;
	}
}

void ETurn() BANKED{
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	if (edata->vx == 1){
		THIS->mirror = V_MIRROR;//SPRITE_SET_VMIRROR(THIS);
		THIS->x -= 4;
		edata->wait = 48u;
	}
	if (edata->vx == -1){
		THIS->mirror = NO_MIRROR; // SPRITE_UNSET_VMIRROR(THIS);
		THIS->x += 4;
		edata->wait = 48u;			
	}
	edata->vx = -edata->vx;
	/*if(THIS->type == SpritePorcupine){
		edata->enemy_state = ENEMY_STATE_ATTACK;
		edata->wait = attack_wait;
	}*/
	
}

void DESTROY(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-2u);
}