#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "custom_datas.h"

extern UINT8 current_level;

const UINT8 anim_bat_normal[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 anim_bat_hit[] = {2, 0, 3}; //The first number indicates the number of frames
const INT8 V_MAX = 2;

void START() {
	THIS->lim_x = 120u;
	THIS->lim_y = 120u;
	SetSpriteAnim(THIS, anim_bat_normal, 16u);
	struct EnemyInfo* batdata = (struct EnemyInfo*)THIS->custom_data;
	batdata->enemy_state = ENEMY_STATE_NORMAL;
	batdata->wait = 0u;
	batdata->hp = 30;
	batdata->vx = -V_MAX;
	batdata->enemy_accel_y = -20;
	batdata->archer_posx = 127;
	THIS->mirror = V_MIRROR;
}

void UPDATE(){
	struct EnemyInfo* batdata = (struct EnemyInfo*)THIS->custom_data;
	batdata->wait++;
	batdata->archer_posx--;
	if(batdata->enemy_accel_y < 24) {
		batdata->enemy_accel_y += 1;
	}
	switch(batdata->enemy_state){
		case ENEMY_STATE_WAIT:
			if(batdata->wait == 36){
				batdata->wait = 0;
				batdata->enemy_state = ENEMY_STATE_NORMAL;
			}
		break;
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
					if(THIS->mirror == V_MIRROR){
						batdata->vx = -V_MAX;						
					}else{
						batdata->vx = V_MAX;
					}
			}
			if(batdata->wait & 1){
				batdata->tile_e_collision = TranslateSprite(THIS, batdata->vx, (batdata->enemy_accel_y >> 3) << delta_time);
			}
			if(batdata->enemy_state != ENEMY_STATE_WAIT){
				switch(batdata->tile_e_collision){
					case 81u:
					case 84u:
					case 85u:
						batdata->archer_posx = 0;
						batdata->enemy_state = ENEMY_STATE_WAIT;
						batdata->wait=0;
					break;
				}
			}
			if(batdata->archer_posx == 0u){
				if (batdata->vx == V_MAX){
					THIS->mirror = V_MIRROR;//SPRITE_SET_VMIRROR(THIS);
				}
				if (batdata->vx == -V_MAX){
					THIS->mirror = NO_MIRROR; //SPRITE_UNSET_VMIRROR(THIS);
				}
				batdata->vx = -batdata->vx;	
				batdata->archer_posx = 127u;			
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
	Sprite* ibatspr;
	SPRITEMANAGER_ITERATE(scroll_tile, ibatspr) {
		if(CheckCollision(THIS, ibatspr)) {
			if(ibatspr->type == SpriteArrow) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ibatspr->custom_data;
				batdata->wait = 0u;//this time because wait++ on the update
				SetSpriteAnim(THIS, anim_bat_hit, 24u); 
				batdata->hp -= arrowdata->arrowdamage;
				batdata->enemy_state = ENEMY_STATE_HIT;
				batdata->wait=0;
				PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);//hit sound
				SpriteManagerRemoveSprite(ibatspr);
				if (batdata->hp <= 0){
					SpriteManagerRemove(THIS_IDX);
				}
				if(ibatspr->x < THIS->x && THIS->mirror == NO_MIRROR){
					batdata->archer_posx = 0;
					batdata->enemy_state = ENEMY_STATE_WAIT;
				}				
				if(ibatspr->x > THIS->x && THIS->mirror == V_MIRROR){
					batdata->archer_posx = 0;
					batdata->enemy_state = ENEMY_STATE_WAIT;
				}
			}				
		}
	}
	
}

void DESTROY() {
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-4u);
}