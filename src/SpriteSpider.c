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
	struct EnemyInfo* spdata = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, spider_idle, 8u);
	spdata->enemy_accel_y = 24;
	spdata->vx = 0;
	spdata->wait = 0u;
	spdata->hp = 18;
	spdata->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteSpider() {
	
	struct EnemyInfo* spdata = (struct EnemyInfo*)THIS->custom_data;
	
	if (spdata->enemy_state == ENEMY_STATE_DEAD){
		if (spdata->wait > 0u){
			THIS->y--;
			spdata->wait--;
		}else{
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (spdata->enemy_state == ENEMY_STATE_HIT){
		spdata->wait -= 1u;
		if (spdata->wait == 0u){
			spdata->enemy_state = ENEMY_STATE_NORMAL;
			SetSpriteAnim(THIS, spider_idle, 8u);
		}
		//return;
	}else{
		spdata->wait -= 1u;
		if (spdata->wait > 0u){
			//if(spdata->wait >> 2 < 2u){
				spdata->tile_e_collision = TranslateSprite(THIS, 0, spdata->vx << delta_time);	
			//}		
		}
		if (spdata->wait == 0u){
			spdata->wait = 120u;
		}
		
		CheckCollisionETile();
		
		if(spdata->tile_e_collision == 18u | spdata->tile_e_collision == 22u | spdata->tile_e_collision == 23u | spdata->tile_e_collision == 81u | spdata->tile_e_collision == 104u){
			spdata->vx = -spdata->vx;
		}
	}
	
	UINT8 scroll_s_tile;
	struct Sprite* isspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_s_tile, isspr) {
		if(isspr->type == SpritePlayer) {
			if(CheckCollision(THIS, isspr)) {
				spdata->wait = 60u;
			}
		}
		if(isspr->type == SpriteArrow) {
			if(CheckCollision(THIS, isspr)) {
				spdata->wait = 32u;
				SetSpriteAnim(THIS, spider_hit, 24u); 
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)isspr->custom_data;
				spdata->hp -= arrowdata->arrowdamage;
				spdata->tile_e_collision = TranslateSprite(THIS, 0, -2);
				SpriteManagerRemoveSprite(isspr);
				if (spdata->hp <= 0){
					spdata->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, spider_dead, 16u);
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					spdata->wait = 8u;
					THIS->lim_x = 8u;
					THIS->lim_y = 16u;
				}else{
					spdata->enemy_state = ENEMY_STATE_HIT;
				}
			}
		}
	}	
}

void Destroy_SpriteSpider(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}