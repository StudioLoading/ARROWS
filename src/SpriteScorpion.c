#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//SCORPION
const UINT8 scorpion_idle[] = {1, 5}; //The first number indicates the number of frames
const UINT8 scorpion_walk[] = {4, 0, 5, 1, 5}; //The first number indicates the number of frames
const UINT8 scorpion_hit[] = {3, 2, 3, 4}; //The first number indicates the number of frames
const UINT8 scorpion_dead[] = {1, 0}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();


void Start_SpriteScorpion() {
	
	THIS->coll_x = 2;
	THIS->coll_y = 5;
	THIS->coll_w = 8;
	THIS->coll_h = 11;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct EnemyInfo* spider_data = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, scorpion_walk, 8u);
	spider_data->enemy_accel_y = 24;
	spider_data->vx = 1;
	spider_data->wait = 0u;
	spider_data->hp = 60;
	spider_data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteScorpion() {
	
	struct EnemyInfo* spider_data = (struct EnemyInfo*)THIS->custom_data;
	
	spider_data->wait--;
	
	if(spider_data->enemy_state == ENEMY_STATE_HIT){
		if(spider_data->wait == 0u){
			SetSpriteAnim(THIS, scorpion_walk, 8u);				
			spider_data->wait = 60u;
			spider_data = ENEMY_STATE_NORMAL;
		}
	}
	
	if (spider_data->enemy_state == ENEMY_STATE_DEAD){
		if (spider_data->wait == 0u){
			//THIS->y--;
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if(spider_data->enemy_accel_y < 24) {
			spider_data->enemy_accel_y += 1;
	}
	if(spider_data->wait & 1){
		if(spider_data->enemy_state != ENEMY_STATE_HIT && spider_data->enemy_state != ENEMY_STATE_DEAD){
			spider_data->tile_e_collision = TranslateSprite(THIS, spider_data->vx << delta_time, (spider_data->enemy_accel_y >> 4)<< delta_time);
			//CheckCollisionETile();
			if(!spider_data->tile_e_collision && delta_time != 0 && spider_data->enemy_accel_y < 24) { //Do another iteration if there is no collision
				spider_data->enemy_accel_y += 2;
				spider_data->tile_e_collision = TranslateSprite(THIS, 0, (spider_data->enemy_accel_y >> 4) << delta_time);
			}
			if(spider_data->tile_e_collision) {
				if(spider_data->enemy_state == ENEMY_STATE_JUMPING & spider_data->enemy_accel_y > 0) {
					spider_data->enemy_state = ENEMY_STATE_NORMAL;
				}else{
					spider_data->enemy_accel_y = 0;	
				}
				CheckCollisionETile();
			}
		}
	}
		
	UINT8 scroll_e_tile;
	struct Sprite* iespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
		if(iespr->type == SpritePlayer) {
			if(CheckCollision(THIS, iespr)) {
				spider_data->wait = 24u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				struct ArrowInfo* arrowspider_data = (struct ArrowInfo*)iespr->custom_data;
				spider_data->hp -= arrowspider_data->arrowdamage;
				if (THIS->x < iespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					spider_data->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (spider_data->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					spider_data->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (spider_data->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(iespr);
				if (spider_data->hp <= 0){
					spider_data->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, scorpion_dead, 16u);
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					spider_data->wait = 8u;
					THIS->lim_x = 8u;
					THIS->lim_y = 16u;
				}else{					
					spider_data->wait = 24u;
					SetSpriteAnim(THIS, scorpion_hit, 24u); 
					spider_data->enemy_state = ENEMY_STATE_HIT;
				}
			}
		}
	}
	
}



void Destroy_SpriteScorpion() {
	struct EnemyInfo* spider_data = (struct EnemyInfo*)THIS->custom_data;
	spider_data->enemy_state = ENEMY_STATE_DEAD;
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y);
}
