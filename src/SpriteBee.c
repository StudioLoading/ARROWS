#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "CircleMath.h"
#include "custom_datas.h"

//SNAKE
const UINT8 bee_idle[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 bee_walk[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 bee_hit[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 bee_dead[] = {1, 1}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();
extern void EDie();

UINT16 init_x;
UINT16 init_y;

void Start_SpriteBee() {	
	THIS->coll_x = 1;
	THIS->coll_y = 2;
	THIS->coll_w = 4;
	THIS->coll_h = 14;
	struct EnemyInfo* beedata = (struct EnemyInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, bee_idle, 24u);
	beedata->enemy_state = ENEMY_STATE_JUMPING;
	beedata->hp = 30;
	beedata->enemy_accel_y = 0;
	beedata->vx = 0;
	beedata->wait = 0u;
	beedata->archer_posx = 0u;
}

void Update_SpriteBee() { 
	
	struct EnemyInfo* beedata = (struct EnemyInfo*)THIS->custom_data;
	
	if(beedata->enemy_state == ENEMY_STATE_JUMPING){		
		THIS->lim_x = THIS->x;
		THIS->lim_y = THIS->y;
		beedata->enemy_state = ENEMY_STATE_NORMAL;
	}else if (beedata->enemy_state == ENEMY_STATE_NORMAL || beedata->enemy_state == ENEMY_STATE_HIT){
		UINT8 cos_position = beedata->archer_posx + 64u;
		THIS->x = THIS->lim_x + ((sine_wave[cos_position]) >> 3);
		THIS->y = THIS->lim_y + ((sine_wave[beedata->archer_posx]) >> 3);
		beedata->archer_posx += 3u;
		if(beedata->hp < 10u){
			beedata->archer_posx += 2u;
		}
	}
	if (beedata->enemy_state == ENEMY_STATE_DEAD){
		if (beedata->wait > 0){
			THIS->y--;
			beedata->wait--;
		}else{
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (beedata->enemy_state == ENEMY_STATE_HIT){
		beedata->wait -= 1u;
		if(beedata->wait == 0u){
			SetSpriteAnim(THIS, bee_idle, 24u);
			beedata->enemy_state = ENEMY_STATE_NORMAL;			
		}
	}
	
	UINT8 scroll_bee_tile;
	struct Sprite* ibeespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_bee_tile, ibeespr) {
		if(ibeespr->type == SpritePlayer) {
			if(CheckCollision(THIS, ibeespr)) {
				beedata->wait = 24u;
			}
		}
		if(ibeespr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibeespr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ibeespr->custom_data;
				beedata->wait = 24u;
				SetSpriteAnim(THIS, bee_hit, 24u); 
				beedata->hp -= arrowdata->arrowdamage;
				SpriteManagerRemoveSprite(ibeespr);
				if (beedata->hp <= 0){
					EDie();
				}else{
					beedata->enemy_state = ENEMY_STATE_HIT;
				}
			}
		}
	}
	
}

void Destroy_SpriteBee(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}