#include "Banks/SetBank17.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


extern UINT8 current_level;
extern void ETurn();

const UINT8 anim_bat_normal[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 anim_bat_hit[] = {2, 0, 3}; //The first number indicates the number of frames

void Start_SpriteBat() {	
	THIS->coll_x = 2;
	THIS->coll_y = 2;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 120u;
	THIS->lim_y = 120u;
	SetSpriteAnim(THIS, anim_bat_normal, 16u);
	struct EnemyInfo* batdata = (struct EnemyInfo*)THIS->custom_data;
	batdata->enemy_state = ENEMY_STATE_NORMAL;
	batdata->wait = 0u;
	batdata->hp = 30;
	batdata->vx = -1;
	batdata->enemy_accel_y = -20;
	batdata->archer_posx = 127;
	SPRITE_SET_VMIRROR(THIS);
}

void Update_SpriteBat(){
	struct EnemyInfo* batdata = (struct EnemyInfo*)THIS->custom_data;
	batdata->wait++;
	batdata->archer_posx--;
	if(batdata->enemy_accel_y < 24) {
		batdata->enemy_accel_y += 1;
	}
	switch(batdata->enemy_state){
		case ENEMY_STATE_NORMAL:
			switch(batdata->wait){
				case 20:
				case 60:
				case 100:
				case 140:
				case 180:
				case 190:
				case 200:
				case 220:
					batdata->vx = 0;
					batdata->enemy_accel_y = -12;		
				break;
				default:
					if(SPRITE_GET_VMIRROR(THIS)){
						batdata->vx = -1;						
					}else{
						batdata->vx = 1;
					}
			}
			if(batdata->wait & 1){
				batdata->tile_e_collision = TranslateSprite(THIS, batdata->vx, (batdata->enemy_accel_y >> 3) << delta_time);
			}
			switch(batdata->tile_e_collision){
				case 81u:
				case 84u:
				case 85u:
					batdata->archer_posx = 0;
				break;
			}
			if(batdata->archer_posx == 0u){
				if (batdata->vx == 1){
					SPRITE_SET_VMIRROR(THIS);
				}
				if (batdata->vx == -1){
					SPRITE_UNSET_VMIRROR(THIS);
				}
				batdata->vx = -batdata->vx;				
			}
		break;
		case ENEMY_STATE_HIT:
			if(batdata->wait == 30u){
				batdata->wait = 0u;
				SetSpriteAnim(THIS, anim_bat_normal, 16u);
				batdata->enemy_state = ENEMY_STATE_NORMAL;				
			}
		break;
	}
	
	UINT8 scroll_tile;
	struct Sprite* ibatspr;
	SPRITEMANAGER_ITERATE(scroll_tile, ibatspr) {
		if(ibatspr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibatspr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ibatspr->custom_data;
				batdata->wait = 0u;//this time because wait++ on the update
				SetSpriteAnim(THIS, anim_bat_hit, 24u); 
				batdata->hp -= arrowdata->arrowdamage;
				batdata->enemy_state = ENEMY_STATE_HIT;
				SpriteManagerRemoveSprite(ibatspr);
				if (batdata->hp <= 0){
					SpriteManagerRemove(THIS_IDX);
				}
			}				
		}
	}
	
}

void Destroy_SpriteBat() {
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-4u);
}