#include "Banks/SetBank17.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


extern UINT8 current_level;

const UINT8 anim_axethrower_normal[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_axethrower_throw[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 anim_axethrower_hit[] = {2, 0, 1}; //The first number indicates the number of frames

void Start_SpriteAxethrower() {	
	THIS->coll_x = 4;
	THIS->coll_y = 2;
	THIS->coll_w = 8;
	THIS->coll_h = 14;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, anim_axethrower_normal, 8u);
	struct EnemyInfo* throwerdata = (struct EnemyInfo*)THIS->custom_data;
	throwerdata->wait = 16u;
	throwerdata->enemy_state = ENEMY_STATE_NORMAL;
	throwerdata->hp = 45;
}

void Update_SpriteAxethrower(){
	struct EnemyInfo* throwerdata = (struct EnemyInfo*)THIS->custom_data;
	throwerdata->wait--;
	if((throwerdata->enemy_state == ENEMY_STATE_ATTACK || throwerdata->enemy_state == ENEMY_STATE_SLIDING) && throwerdata->wait == 16u){
		SpriteManagerAdd(SpriteAxe, THIS->x + 8u, THIS->y);
	}
	if(throwerdata->wait == 0u){
		switch(throwerdata->enemy_state){
			case ENEMY_STATE_NORMAL:			
				throwerdata->wait = 24u;
				SetSpriteAnim(THIS, anim_axethrower_throw, 8u);
				throwerdata->enemy_state = ENEMY_STATE_ATTACK;
			break;			
			case ENEMY_STATE_ATTACK:			
				throwerdata->wait = 24u;
				throwerdata->enemy_state = ENEMY_STATE_SLIDING;
			break;			
			case ENEMY_STATE_SLIDING:
				throwerdata->wait = 64u;
				SetSpriteAnim(THIS, anim_axethrower_normal, 8u);
				throwerdata->enemy_state = ENEMY_STATE_NORMAL;
			break;
			case ENEMY_STATE_HIT:
				throwerdata->wait = 24u;
				SetSpriteAnim(THIS, anim_axethrower_throw, 8u);
				throwerdata->enemy_state = ENEMY_STATE_ATTACK;			
			break;
		}
	}
	
	UINT8 scroll_at_tile;
	struct Sprite* iatspr;
	SPRITEMANAGER_ITERATE(scroll_at_tile, iatspr) {
		if(iatspr->type == SpriteArrow) {
			if(CheckCollision(THIS, iatspr)) {
				if(throwerdata->enemy_state != ENEMY_STATE_HIT){
					SetSpriteAnim(THIS, anim_axethrower_hit, 20u);
					throwerdata->enemy_state = ENEMY_STATE_HIT;	
					throwerdata->wait = 20u;
					struct ArrowInfo* arrowdata = (struct ArrowInfo*)iatspr->custom_data;
					throwerdata->hp -= arrowdata->arrowdamage;
					SpriteManagerRemoveSprite(iatspr);
					if (throwerdata->hp <= 0){
						SpriteManagerRemove(THIS_IDX);
					}
				}
			}
		}
	}
}


void Destroy_SpriteAxethrower() {
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-4u);
}