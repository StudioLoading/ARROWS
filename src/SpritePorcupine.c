#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//PORCUPINE
const UINT8 porcupine_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 porcupine_walk[] = {4, 0, 6, 1, 6}; //The first number indicates the number of frames
const UINT8 porcupine_hit[] = {3, 2, 3, 4}; //The first number indicates the number of frames
const UINT8 porcupine_dead[] = {1, 5}; //The first number indicates the number of frames
const UINT8 porcupine_attack[] = {4, 6, 7, 7, 7}; //The first number indicates the number of frames

extern void CheckCollisionETile();

void Start_SpritePorcupine() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 8;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, porcupine_idle, 8u);
	data->enemy_accel_y = 24;
	data->vx = 1;
	data->wait = 0u;
	data->enemydamage = 15u;
	data->hp = 30u;
	data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpritePorcupine() {
	
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
	
	if (data->enemy_state == ENEMY_STATE_ATTACK){
		if (data->wait == attack_wait){SetSpriteAnim(THIS, porcupine_attack, 8u);}
		if (data->wait == 1u){
			struct Sprite* arrow_e_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
			struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_e_sprite->custom_data;
			arrow_data->arrowdir = 1;
			arrow_data->type = 6;
			arrow_data->arrowdamage = 10u;
			arrow_e_sprite->flags = THIS->flags;
			if(SPRITE_GET_VMIRROR(THIS)){arrow_e_sprite->x = THIS->x-16;}
			else{arrow_e_sprite->x = THIS->x+10;}
			arrow_e_sprite->y = THIS->y + 2;
		}
	}
	
	if (data->wait > 0u){
		data->wait -= 1u;
		if (data->wait == 0u){
			SetSpriteAnim(THIS, porcupine_walk, 8u);
			data->enemy_state = ENEMY_STATE_NORMAL;
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
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				SpriteManagerRemoveSprite(iespr);
			}
		}
	}
	
}

void Destroy_SpritePorcupine() {
}
