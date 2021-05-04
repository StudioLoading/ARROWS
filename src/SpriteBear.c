#include "Banks/SetBank8.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//IBEX
const UINT8 bear_idle[] = {1, 1}; //The first number indicates the number of frames
const UINT8 bear_walk[] = {4, 0, 1, 0, 2};//{4, 0, 1, 2, 1};
const UINT8 bear_hit[] = {2, 0, 1};
const UINT8 bear_dead[] = {1, 1};
const UINT8 bear_attack[] = {3, 3, 4, 5};

struct EnemyInfo* bear_data ;

void CheckCollisionBETile();
void BETurn();
void ToNormalState();

void Start_SpriteBear() {
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
	SetSpriteAnim(THIS, bear_walk, 10u);
	bear_data = (struct EnemyInfo*)THIS->custom_data;
	bear_data->enemy_accel_y = 24;
	bear_data->vx = -1;
	bear_data->wait = 0u;
	bear_data->hp = 100;
	ToNormalState();
}

void Update_SpriteBear() {
	
	if(bear_data->enemy_state != ENEMY_STATE_NORMAL){
		
		if(bear_data->enemy_state == ENEMY_STATE_HIT){
			bear_data->wait--;
			if(bear_data->wait > 0){			
				if(bear_data->wait == 1  || bear_data->wait == 20 || bear_data->wait == 40 ){
					THIS->y = (UINT16) 29u;
				}else{
					THIS->y = (UINT16) 12u << 3;
				}
			}else{
				bear_data->wait = 0;
				THIS->y = (UINT16) 12u << 3;
				bear_data->enemy_state = ENEMY_STATE_NORMAL;
			}
		}
		
		if(bear_data->enemy_state == ENEMY_STATE_ATTACK){
			bear_data->wait -= 1u;
			switch(bear_data->wait){
				case 20u:
				case 30u:
				case 50u:		
					bear_data->tile_e_collision = TranslateSprite(THIS, bear_data->vx << delta_time, 0);
					CheckCollisionBETile();
				break;
			}
			if(bear_data->wait <= 0u){
				bear_data->wait = 0u;
				ToNormalState();
			}
		}
		/*
		if(bear_data->enemy_state == ENEMY_STATE_WAIT){
			return;
		}*/
		
		if (bear_data->enemy_state == ENEMY_STATE_DEAD){
			if(bear_data->tile_e_collision==0){
				bear_data->tile_e_collision = TranslateSprite(THIS, 0, 1);	
			}
			bear_data->hp = 0;
		}
		
		return;
	}
	
	if (bear_data->wait > 0u){
		bear_data->wait -= 1u;
		if (bear_data->wait <= 0u){
			bear_data->wait = 0u;
			ToNormalState();
		}
		return;
	}
	/*
	if(bear_data->vx){
		if (bear_data->vx > 0 & !SPRITE_GET_VMIRROR(THIS)){
			SPRITE_SET_VMIRROR(THIS);
		}
		if(bear_data->vx < 0 & SPRITE_GET_VMIRROR(THIS)){
			SPRITE_UNSET_VMIRROR(THIS);
		}		
	}
	*/
	bear_data->tile_e_collision = TranslateSprite(THIS, bear_data->vx << delta_time, 0);
	CheckCollisionBETile();
	if((THIS->x == (UINT16) 13u << 3 && bear_data->vx < 0) || (THIS->x == (UINT16) 22u << 3)){
		//|| (THIS->x == (UINT16) 28u << 3) ||
		if(bear_data->enemy_state != ENEMY_STATE_ATTACK){			
			SetSpriteAnim(THIS, bear_attack, 12u);
			bear_data->enemy_state = ENEMY_STATE_ATTACK;
			bear_data->wait = 58;
			THIS->coll_x = 4;
			THIS->coll_y = 0;
			THIS->coll_w = 24;
			THIS->coll_h = 32;
		}	
	}

	UINT8 scroll_be_tile;
	struct Sprite* bebspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_be_tile, bebspr) {
		if(bebspr->type == SpritePlayer) {
			if(CheckCollision(THIS, bebspr)) {
				bear_data->wait = 24u;
			}
		}
		if(bebspr->type == SpriteGate) {
			if(CheckCollision(THIS, bebspr)) {
				BETurn();
			}
		}
		if(bebspr->type == SpriteArrow) {
			if(CheckCollision(THIS, bebspr) & bear_data->enemy_state != ENEMY_STATE_DEAD) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)bebspr->custom_data;
				if(arrowdata->arrowdir == 4){
					bear_data->wait = 60u;
					bear_data->enemy_state = ENEMY_STATE_HIT;
					bear_data->hp -= arrowdata->arrowdamage;
					if (bear_data->vx < 0){
						THIS->x++;
					}else{
						THIS->x--;
					}
				}
				if (bear_data->hp <= 0){
					bear_data->enemy_state = ENEMY_STATE_DEAD;
					bear_data->hp = 0;
					THIS->x = (UINT16) 25u << 3;
					THIS->y = (UINT16) 12u << 3;
					SetSpriteAnim(THIS, bear_dead, 16u);
				}
				SpriteManagerRemoveSprite(bebspr);
			}
		}
	}
}

void CheckCollisionBETile() {
	switch(bear_data->tile_e_collision) {
		case 16u:
		case 17u:
		case 18u:
		case 20u:
		case 68u:
			BETurn();
		break;
	}
}

void BETurn(){
	if (bear_data->vx == 1){
		SPRITE_UNSET_VMIRROR(THIS);
		THIS->x -= 4;
		bear_data->wait = 48u;
	}
	if (bear_data->vx == -1){
		SPRITE_SET_VMIRROR(THIS);
		THIS->x += 4;
		bear_data->wait = 48u;			
		
	}
	ToNormalState();
	if (bear_data->vx == 1){
		bear_data->vx = -1;
	}else{
		bear_data->vx = 1;
	}
}

void ToNormalState(){
	bear_data->enemy_state = ENEMY_STATE_NORMAL;
	SetSpriteAnim(THIS, bear_walk, 8u);
	THIS->coll_x = 4;
	THIS->coll_y = 12;
	THIS->coll_w = 24;
	THIS->coll_h = 20;	
}

void Destroy_SpriteBear() {
}
