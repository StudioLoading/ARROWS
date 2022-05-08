#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"


//CATHEAD
const UINT8 cathead_idle[] = {2, 0, 1}; //The first number indicates the number of frames

void START() {	
	struct EnemyInfo* catheaddata = (struct EnemyInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, cathead_idle, 16u);
	catheaddata->enemy_state = ENEMY_STATE_ATTACK;
	catheaddata->hp = 10;
	catheaddata->enemy_accel_y = 0;
	catheaddata->vx = 0;
	catheaddata->wait = 0u;
	catheaddata->archer_posx = 0u;
}

void UPDATE() { 
	struct EnemyInfo* catheaddata = (struct EnemyInfo*)THIS->custom_data;
	if(catheaddata->enemy_state == ENEMY_STATE_HIT){
		catheaddata->wait--;
		if(catheaddata->wait == 0u){
			catheaddata->enemy_state = ENEMY_STATE_ATTACK;
		}
		return;
	}
	catheaddata->wait++;//up to 255
	if(catheaddata->wait & 0b100){		
		THIS->x-=2;
	}
	if(catheaddata->wait & 1){
		if(catheaddata->wait < 64u){
			THIS->y++;
		}else if(catheaddata->wait > 80u && catheaddata->wait < 128u){
			THIS->y--;
		}else if(catheaddata->wait > 140u && catheaddata->wait < 192u){
			THIS->y++;
		}else if(catheaddata->wait > 200u && catheaddata->wait < 255u){
			THIS->y--;
		}
	}
	
	UINT8 scathead_tile;
	Sprite* icatheadsprite;
	SPRITEMANAGER_ITERATE(scathead_tile, icatheadsprite) {
		if(icatheadsprite->type == SpriteArrow) {
			if(CheckCollision(THIS, icatheadsprite)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)icatheadsprite->custom_data;
				catheaddata->wait = 48u;
				catheaddata->hp -= arrowdata->arrowdamage;
				catheaddata->enemy_state = ENEMY_STATE_HIT;
				SpriteManagerRemoveSprite(icatheadsprite);
				if (catheaddata->hp <= 0){
					SpriteManagerRemove(THIS_IDX);
				}
			}				
		}
	}
	
}

void DESTROY(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-4u);
}