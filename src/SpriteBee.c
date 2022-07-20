#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"
#include "CircleMath.h"

//BEE
const UINT8 bee_idle[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 bee_walk[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 bee_hit[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 bee_dead[] = {1, 1}; //The first number indicates the number of frames

extern void CheckCollisionETile() BANKED;
extern void ETurn() BANKED;
extern void EDie() BANKED;

void START() {	
	struct EnemyInfo* beedata = (struct EnemyInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, bee_idle, 24u);
	beedata->enemy_state = ENEMY_STATE_JUMPING;
	beedata->hp = 30;
	beedata->enemy_accel_y = 0;
	beedata->vx = 0;
	beedata->wait = 0u;
	beedata->archer_posx = 0u;
}

void UPDATE() { 
	
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
	Sprite* ibeespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_bee_tile, ibeespr) {
		if(CheckCollision(THIS, ibeespr)) {
			struct ArrowInfo* arrowdata = 0;
			switch(ibeespr->type){
				case SpritePlayer:
					beedata->wait = 24u;
				break;
				case SpriteArrow:
					arrowdata = (struct ArrowInfo*)ibeespr->custom_data;
					beedata->wait = 24u;
					SetSpriteAnim(THIS, bee_hit, 24u); 
					beedata->hp -= arrowdata->arrowdamage;
					PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);//hit sound
					SpriteManagerRemoveSprite(ibeespr);
					if (beedata->hp <= 0){
						EDie();
					}else{
						beedata->enemy_state = ENEMY_STATE_HIT;
					}
				break;
			}
		}
	}
	
}

void DESTROY(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}