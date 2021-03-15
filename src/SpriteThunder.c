#include "Banks/SetBank8.h"
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

extern void CheckCollisionETile();
extern void ETurn();


void Start_SpriteThunder() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 5;
	THIS->coll_w = 4;
	THIS->coll_h = 11;
	THIS->lim_x = 152u;
	THIS->lim_y = 152u;
	struct EnemyInfo* tdata = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, thunder_idle, 8u);
	tdata->enemy_accel_y = 40;
	tdata->wait = 20u;
	tdata->hp = 24u;
	tdata->enemy_state = ENEMY_STATE_WAIT;
	tdata->vx = (THIS->x & 1);
}

void Update_SpriteThunder() {
	
	struct EnemyInfo* tdata = (struct EnemyInfo*)THIS->custom_data;
	
	if (tdata->enemy_state == ENEMY_STATE_WAIT){
		tdata->wait -= 1u;
		if (tdata->wait == 0u){
			SetSpriteAnim(THIS, thunder_walk, 8u);
			tdata->enemy_state = ENEMY_STATE_NORMAL;
		}
	}
	if(tdata->enemy_state == ENEMY_STATE_NORMAL){
		if(tdata->enemy_accel_y < 40) {
				tdata->enemy_accel_y += 1;
		}
		tdata->tile_e_collision = TranslateSprite(THIS, tdata->vx << delta_time, (tdata->enemy_accel_y >> 4)<< delta_time);
		if(!tdata->tile_e_collision && delta_time != 0 && tdata->enemy_accel_y < 40) { //Do another itethunderion if there is no collision
			tdata->enemy_accel_y += 2;
			tdata->tile_e_collision = TranslateSprite(THIS, 0, (tdata->enemy_accel_y >> 4) << delta_time);
		}
		if (tdata->tile_e_collision == 21u){
			tdata->wait = 16u;
			SetSpriteAnim(THIS, thunder_dead, 10u);
			tdata->enemy_state = ENEMY_STATE_DEAD;
		}else if (tdata->tile_e_collision == 100u | tdata->tile_e_collision == 101u){
			THIS->y++;
		}
	}
	
	if(tdata->enemy_state == ENEMY_STATE_DEAD){
		tdata->wait--;
		if(tdata->wait == 0u){
			SpriteManagerRemove(THIS_IDX);
		}
	}
	
	/*
	
	UINT8 scroll_e_tile;
	struct Sprite* iespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
		if(iespr->type == SpritePlayer) {
			if(CheckCollision(THIS, iespr)) {
				tdata->wait = 24u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				tdata->wait = 24u;
				SetSpriteAnim(THIS, thunder_hit, 24u); 
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
				tdata->hp -= arrowdata->arrowdamage;
				if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					tdata->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (tdata->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					tdata->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (tdata->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(iespr);
				if (tdata->hp <= 0){
					tdata->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, thunder_dead, 16u);
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					tdata->wait = 8u;
					THIS->lim_x = 8u;
					THIS->lim_y = 16u;
				}
			}
		}
	}
	*/
	
}

void Destroy_SpriteThunder(){}
