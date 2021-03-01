#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//RAT
const UINT8 spider_idle[] = {8, 0,1,2,3,4,3,2,1}; //The first number indicates the number of frames
const UINT8 spider_hit[] = {3, 5, 5, 0}; //The first number indicates the number of frames
const UINT8 spider_dead[] = {1, 5}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();


void Start_SpriteSpider() {
	
	THIS->coll_x = 1;
	THIS->coll_y = 1;
	THIS->coll_w = 6;
	THIS->coll_h = 13;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, spider_idle, 8u);
	data->enemy_accel_y = 24;
	data->vx = 0;
	data->wait = 0u;
	data->hp = 40;
	data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteSpider() {
	
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	
	if (data->enemy_state == ENEMY_STATE_DEAD){
		if (data->wait > 0u){
			THIS->y--;
			data->wait--;
		}else{
			THIS->y++;	
			THIS->y++;
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (data->enemy_state == ENEMY_STATE_HIT){
		data->wait -= 1u;
		if (data->wait == 0u){
			data->enemy_state = ENEMY_STATE_NORMAL;
			SetSpriteAnim(THIS, spider_idle, 8u);
		}
		return;
	}
	
	data->wait -= 1u;
	if (data->wait > 0u){
		if(data->wait >> 2 < 2u){
			data->tile_e_collision = TranslateSprite(THIS, 0, data->vx << delta_time);	
		}		
	}
	if (data->wait == 0u){
		data->wait = 120u;
	}
	
	CheckCollisionETile();
	
	if(data->tile_e_collision == 18u | data->tile_e_collision == 22u | data->tile_e_collision == 52u | data->tile_e_collision == 100u | data->tile_e_collision == 101u){
		data->vx = -data->vx;
	}
	
	UINT8 scroll_e_tile;
	struct Sprite* iespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_e_tile, iespr) {
		if(iespr->type == SpritePlayer) {
			if(CheckCollision(THIS, iespr)) {
				data->wait = 60u;
			}
		}
		if(iespr->type == SpriteArrow) {
			if(CheckCollision(THIS, iespr)) {
				data->wait = 32u;
				SetSpriteAnim(THIS, spider_hit, 24u); 
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)iespr->custom_data;
				data->hp -= arrowdata->arrowdamage;
				data->tile_e_collision = TranslateSprite(THIS, 0, -2);
				SpriteManagerRemoveSprite(iespr);
				if (data->hp <= 0){
					data->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, spider_dead, 16u);
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					data->wait = 8u;
					THIS->lim_x = 8u;
					THIS->lim_y = 16u;
				}else{
					data->enemy_state = ENEMY_STATE_HIT;
				}
			}
		}
	}	
}



void Destroy_SpriteSpider() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	data->enemy_state = ENEMY_STATE_DEAD;
}
