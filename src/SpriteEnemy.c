#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//SNAKE
const UINT8 enemy_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 enemy_walk[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 enemy_hit[] = {3, 2, 3, 4}; //The first number indicates the number of frames
const UINT8 enemy_dead[] = {1, 5}; //The first number indicates the number of frames

void CheckCollisionETile();
void ETurn();

void Start_SpriteEnemy() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 0;
	THIS->coll_w = 12;
	THIS->coll_h = 16;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, enemy_idle, 8u);
	data->enemy_accel_y = 24;
	data->vx = 1;
	data->wait = 0u;
	data->enemydamage = 5u;
	data->hp = 45u;
	data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteEnemy() {
	
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	
	if (data->enemy_state == ENEMY_STATE_DEAD){
		if (data->wait > 0){
			THIS->y--;
			data->wait--;
		}else{
			THIS->y++;	
			THIS->y++;
		}		
		return;
	}
	
	if (data->wait > 0u){
		data->wait -= 1u;
		if (data->wait == 0u){
			SetSpriteAnim(THIS, enemy_walk, 8u);
		}
	}else{
		if(data->enemy_accel_y < 24) {
				data->enemy_accel_y += 1;
		}
		data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, (data->enemy_accel_y >> 4)<< delta_time);
		//CheckCollisionETile();
		if(!data->tile_e_collision && delta_time != 0 && data->enemy_accel_y < 24) { //Do another iteration if there is no collision
			data->enemy_accel_y += 2;
			data->tile_e_collision = TranslateSprite(THIS, 0, (data->enemy_accel_y >> 4) << delta_time);
		}
		if(data->tile_e_collision) {
			if(data->enemy_state == ENEMY_STATE_JUMPING & data->enemy_accel_y > 0) {
				data->enemy_state = ENEMY_STATE_NORMAL;
			}else{
				data->enemy_accel_y = 0;	
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
				data->wait = 24u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
				if (arrowdata->type == 6u){ //spine from porcupine
					return;
				}
				data->wait = 24u;
				SetSpriteAnim(THIS, enemy_hit, 24u); 
				data->hp -= arrowdata->arrowdamage;
				if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					data->tile_e_collision = TranslateSprite(THIS, -4 << delta_time, (data->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					data->tile_e_collision = TranslateSprite(THIS, 4 << delta_time, (data->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(iespr);
				if (data->hp <= 0){
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					data->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, enemy_dead, 16u);
					data->wait = 8u;
					THIS->lim_x = 8u;
					THIS->lim_y = 16u;
				}
			}
		}
	}
	
}


void CheckCollisionETile() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	switch(data->tile_e_collision) {
		case 4u:
		case 5u:
		case 6u:
		case 7u:
		case 18u:
		case 19u:
			ETurn();
		break;
	}
}

void ETurn(){
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	if (data->vx == 1){
		SPRITE_SET_VMIRROR(THIS);
		THIS->x -= 4;
		data->wait = 48u;
	}
	if (data->vx == -1){
		SPRITE_UNSET_VMIRROR(THIS);
		THIS->x += 4;
		data->wait = 48u;			
	}
	data->vx = -data->vx;
	if(THIS->type == SpritePorcupine){
		data->enemy_state = ENEMY_STATE_ATTACK;
		data->wait = attack_wait;
	}
	
}

void Destroy_SpriteEnemy() {
}
