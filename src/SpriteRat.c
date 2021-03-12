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


void Start_SpriteRat() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 5;
	THIS->coll_w = 8;
	THIS->coll_h = 11;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, rat_idle, 8u);
	rdata->enemy_accel_y = 24;
	rdata->vx = 1;
	rdata->wait = 0u;
	rdata->hp = 24u;
	rdata->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteRat() {
	
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;
	
	if (rdata->enemy_state == ENEMY_STATE_DEAD){
		if (rdata->wait > 0u){
			THIS->y--;
			rdata->wait--;
		}else{
			THIS->y++;	
			THIS->y++;
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (rdata->wait > 0u){
		rdata->wait -= 1u;
		if (rdata->wait == 0u){
			SetSpriteAnim(THIS, rat_walk, 8u);
		}
	}else{
		if(rdata->enemy_accel_y < 24) {
				rdata->enemy_accel_y += 1;
		}
		rdata->tile_e_collision = TranslateSprite(THIS, rdata->vx << delta_time, (rdata->enemy_accel_y >> 4)<< delta_time);
		//CheckCollisionETile();
		if(!rdata->tile_e_collision && delta_time != 0 && rdata->enemy_accel_y < 24) { //Do another iteration if there is no collision
			rdata->enemy_accel_y += 2;
			rdata->tile_e_collision = TranslateSprite(THIS, 0, (rdata->enemy_accel_y >> 4) << delta_time);
		}
		if(rdata->tile_e_collision) {
			if(rdata->enemy_state == ENEMY_STATE_JUMPING & rdata->enemy_accel_y > 0) {
				rdata->enemy_state = ENEMY_STATE_NORMAL;
			}else{
				rdata->enemy_accel_y = 0;	
			}
			CheckCollisionETile();
		}
	}//fine else non wait
	
	UINT8 scroll_e_tile;
	struct Sprite* iespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
		if(iespr->type == SpritePlayer) {
			if(CheckCollision(THIS, iespr)) {
				rdata->wait = 24u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				rdata->wait = 24u;
				SetSpriteAnim(THIS, rat_hit, 24u); 
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
				rdata->hp -= arrowdata->arrowdamage;
				if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					rdata->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (rdata->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					rdata->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (rdata->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(iespr);
				if (rdata->hp <= 0){
					rdata->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, rat_dead, 16u);
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					rdata->wait = 8u;
					THIS->lim_x = 8u;
					THIS->lim_y = 16u;
				}
			}
		}
	}
	
}

void Destroy_SpriteRat(){}
