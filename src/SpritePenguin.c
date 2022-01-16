#include "Banks/SetBank14.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "CircleMath.h"
#include "custom_datas.h"

//SNAKE
const UINT8 penguin_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 penguin_walk[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 penguin_hit[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 penguin_hit_low[] = {2, 3, 2}; //The first number indicates the number of frames
const UINT8 penguin_dead[] = {1, 2}; //The first number indicates the number of frames
const UINT8 penguin_sliding[] = {1, 3}; 

void CheckCollisionPTile(UINT8 t);
void PTurn();
void PDie();

void Start_SpritePenguin() {	
	THIS->coll_x = 4;
	THIS->coll_y = 1;
	THIS->coll_w = 4;
	THIS->coll_h = 14;
	THIS->lim_x = 64u;
	struct EnemyInfo* pendata = (struct EnemyInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, penguin_walk, 8u);
	pendata->enemy_state = ENEMY_STATE_NORMAL;
	pendata->hp = 30;
	pendata->enemy_accel_y = 24;
	pendata->vx = -1;
	pendata->wait = 60u;
	pendata->archer_posx = 0u;
}

void Update_SpritePenguin() { 
	
	struct EnemyInfo* pendata = (struct EnemyInfo*)THIS->custom_data;
	pendata->wait--;
	if(pendata->enemy_accel_y < 24) {
		pendata->enemy_accel_y += 1;
	}
	if(pendata->enemy_state == ENEMY_STATE_SLIDING){
		pendata->tile_e_collision = TranslateSprite(THIS, pendata->vx << delta_time, (pendata->enemy_accel_y >> 4)<< delta_time);
		CheckCollisionPTile(pendata->tile_e_collision);
		if (pendata->wait == 0){
			PTurn();
			pendata->wait=60u;
			SetSpriteAnim(THIS, penguin_walk, 8u);
			pendata->enemy_state = ENEMY_STATE_NORMAL;
		}
		//return;
	}
	
	if (pendata->enemy_state == ENEMY_STATE_NORMAL){
		if (pendata->wait == 10u){
			SetSpriteAnim(THIS, penguin_sliding, 8u);
			pendata->wait=100u;
			pendata->enemy_accel_y = -6u;
			pendata->enemy_state = ENEMY_STATE_SLIDING;
			return;
		}
		/*if (pendata->wait == 30){
			PTurn();
			pendata->wait=90u;
			return;
		}*/
		if(pendata->wait & 1){	
			pendata->tile_e_collision = TranslateSprite(THIS, pendata->vx << delta_time, (pendata->enemy_accel_y >> 4)<< delta_time);
			if(pendata->tile_e_collision == 0){
				pendata->tile_e_collision = TranslateSprite(THIS, pendata->vx << delta_time, (pendata->enemy_accel_y >> 4)<< delta_time);
			}
			CheckCollisionPTile(pendata->tile_e_collision);
		}
	}
	
	if(pendata->enemy_state == ENEMY_STATE_WAIT){
		if(pendata->wait == 0){
			SetSpriteAnim(THIS, penguin_walk, 8u);
			pendata->enemy_state = ENEMY_STATE_NORMAL;			
		}
	}
	
	if (pendata->enemy_state == ENEMY_STATE_DEAD){
		if (pendata->wait > 0){
			THIS->y--;
			pendata->wait--;
		}else{
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (pendata->enemy_state == ENEMY_STATE_HIT){
		if(pendata->wait == 0u){
			SetSpriteAnim(THIS, penguin_walk, 8u);
			pendata->enemy_state = ENEMY_STATE_NORMAL;			
		}
		return;
	}
	
	UINT8 scroll_penguin_tile;
	struct Sprite* ipenspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_penguin_tile, ipenspr) {
		if(ipenspr->type == SpritePlayer) {
			if(CheckCollision(THIS, ipenspr)) {
				pendata->enemy_state = ENEMY_STATE_WAIT;
				pendata->wait = 24u;
			}
		}
		if(ipenspr->type == SpriteArrow) {
			if(CheckCollision(THIS, ipenspr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ipenspr->custom_data;
				pendata->wait = 40u;
				SetSpriteAnim(THIS, penguin_hit, 24u); 
				pendata->hp -= arrowdata->arrowdamage;
				SpriteManagerRemoveSprite(ipenspr);
				if (pendata->hp <= 0){
					PDie();
				}else{
					pendata->enemy_state = ENEMY_STATE_HIT;
				}
			}
		}
		if(ipenspr->type == SpriteStalagmite || ipenspr->type == SpriteStalattite) {
			if(CheckCollision(THIS, ipenspr)) {
				if(pendata->enemy_state == ENEMY_STATE_SLIDING){
					SpriteManagerRemoveSprite(ipenspr);
				}else{
					struct EnemyInfo* stalagmite_data = (struct EnemyInfo*)ipenspr->custom_data;
					if(stalagmite_data->enemy_state != STALAG_STATE_LOW && stalagmite_data->enemy_state != STALAG_STATE_DROP){
						PTurn();
						if(ipenspr->x > THIS->x){
							THIS->x -= 6;
						}else{
							THIS->x += 6;
						}
					}					
				}
			}
		}
	}
	
}

void PTurn(){
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	edata->vx = -edata->vx;	
	if (edata->vx == 1){
		SPRITE_SET_VMIRROR(THIS);
		THIS->x += 2;
	}
	if (edata->vx == -1){
		SPRITE_UNSET_VMIRROR(THIS);
		THIS->x -= 2;			
	}
	edata->wait = 60u;
}

void CheckCollisionPTile(UINT8 t) {
	switch(t){
		case 14u:
		case 36u:
		case 37u:
		case 44u:
		case 59u:
		case 61u:
			PTurn();
		break;
		case 20u:
		case 40u://skull of death
			PDie();
		break;
	}
}

void PDie(){
	NR50_REG = 0x55; //Max volume		
	PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	edata->hp = -1;
	SetSpriteAnim(THIS, penguin_dead, 16u);
	edata->wait = 16u;
	edata->enemy_state = ENEMY_STATE_DEAD;
}

void Destroy_SpritePenguin(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}