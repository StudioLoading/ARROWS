#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"

extern UINT8 current_camera_state;
extern INT8 walk_fx_cooldown;
extern struct ArcherInfo* archer_data;

//BEAR
const UINT8 bear_idle[] = {1, 2}; //The first number indicates the number of frames
const UINT8 bear_walk[] = {4, 0, 1, 2, 3};
const UINT8 bear_hit[] = {2, 0, 1};
const UINT8 bear_dead[] = {1, 2};
const UINT8 bear_attack[] = {4, 5, 4, 5, 5};

struct EnemyInfo* bear_data ;

void CheckCollisionBETile();
void BETurn();
void ToNormalState();

void START() {
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, bear_idle, 4u);
	bear_data = (struct EnemyInfo*)THIS->custom_data;
	bear_data->enemy_accel_y = 24;
	bear_data->vx = -1;
	bear_data->wait = 0u;
	bear_data->hp = 6;
	if(current_camera_state == 3u){
		ToNormalState();		
	}
}

void UPDATE() {
	
	if(bear_data->enemy_state != ENEMY_STATE_NORMAL){		
		if(bear_data->enemy_state == ENEMY_STATE_ATTACK){
			bear_data->wait -= 1u;
			switch(bear_data->wait){
				case 20u:
				case 30u:
				case 50u:
					PlayFx(CHANNEL_4, 60, 0x01, 0xf9, 0x32, 0xc0, 0x00);		
					bear_data->tile_e_collision = TranslateSprite(THIS, bear_data->vx << delta_time, 1 << delta_time);
					CheckCollisionBETile();
				break;
			}
			if(bear_data->wait <= 0u){
				bear_data->wait = 0u;
				ToNormalState();
			}
		}else{
			if(bear_data->enemy_state == ENEMY_STATE_HIT){
				bear_data->wait--;
				/*if(bear_data->wait > 0){			
					if(bear_data->wait == 1  || bear_data->wait == 20 || bear_data->wait == 40 ){
						THIS->y = (UINT16) 29u << 3;
					}else{
						THIS->y = (UINT16) 12u << 3;
					}
				}else{*/
				if(bear_data->wait <= 0){
					bear_data->wait = 0;
					//THIS->y = (UINT16) 12u << 3;
					bear_data->enemy_state = ENEMY_STATE_NORMAL;
				}
			}
			
			if(bear_data->enemy_state == ENEMY_STATE_WAIT){
				return;
			}			
			if (bear_data->enemy_state == ENEMY_STATE_DEAD){
				if(bear_data->tile_e_collision==0){
					bear_data->tile_e_collision = TranslateSprite(THIS, 0, 1);	
				}
				bear_data->hp = 0;
			}			
			return;			
		}		
	}else{	
		if (bear_data->wait > 0u){
			bear_data->wait -= 1u;
			if (bear_data->wait <= 0u){
				bear_data->wait = 0u;
				ToNormalState();
			}
			return;
		}		
	}
	
	if(bear_data->enemy_state == ENEMY_STATE_NORMAL){
		walk_fx_cooldown++;
		if(walk_fx_cooldown == WALK_FX_COOLDOWN){
			PlayFx(CHANNEL_4, 60, 0x3a, 0xd2, 0x00, 0xc0, 0x85);
			walk_fx_cooldown = 0;
		}		
		bear_data->tile_e_collision = TranslateSprite(THIS, bear_data->vx << delta_time, 0 << delta_time);
		if(bear_data->tile_e_collision){
			CheckCollisionBETile();
			TranslateSprite(THIS, 0, 1 << delta_time);
		}
	}
	if((THIS->x == (UINT16) 13u << 3 && bear_data->vx < 0) || (THIS->x == (UINT16) 22u << 3)){
		if(bear_data->enemy_state != ENEMY_STATE_ATTACK){			
			SetSpriteAnim(THIS, bear_attack, 12u);
			PlayFx(CHANNEL_4, 60, 0x01, 0xf9, 0x32, 0xc0, 0x00);
			bear_data->enemy_state = ENEMY_STATE_ATTACK;
			bear_data->wait = 58;
		}	
	}

	UINT8 scroll_be_tile;
	Sprite* bebspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_be_tile, bebspr) {
		if(CheckCollision(THIS, bebspr) && archer_data->hp > 0) {
			switch(bebspr->type){
				case SpritePlayer:
					bear_data->wait = 24u;
				break;
				case SpriteArrow:
					if(bear_data->enemy_state != ENEMY_STATE_DEAD) {
						struct ArrowInfo* arrowdata = (struct ArrowInfo*)bebspr->custom_data;
						if(arrowdata->original_type != 2u){
							return;
						}
						if(arrowdata->arrowdir == 4 || (bear_data->enemy_state == ENEMY_STATE_ATTACK)){
							bear_data->wait = 60u;
							bear_data->enemy_state = ENEMY_STATE_HIT;
							bear_data->hp -= 1;
							if (bear_data->vx < 0){
								THIS->x++;
							}else{
								THIS->x--;
							}
							SpriteManagerRemoveSprite(bebspr);
						}
						if (bear_data->hp <= 0){
							bear_data->enemy_state = ENEMY_STATE_DEAD;
							bear_data->hp = 0;
							THIS->x = (UINT16) 25u << 3;
							THIS->y = (UINT16) 12u << 3;
							SetSpriteAnim(THIS, bear_dead, 16u);
						}
					}
				break;

			}
		}
	}
}

void CheckCollisionBETile() {
	switch(bear_data->tile_e_collision) {
		case 16u:
		case 17u:
		case 18u:
		case 20u:
		case 68u:
			BETurn();
		break;
	}
}

void BETurn(){
	if (bear_data->vx == 1){
		THIS->mirror = NO_MIRROR;//SPRITE_UNSET_VMIRROR(THIS);
		THIS->x -= 4;
		bear_data->wait = 48u;
	}
	if (bear_data->vx == -1){
		THIS->mirror = V_MIRROR; //SPRITE_SET_VMIRROR(THIS);
		THIS->x += 4;
		bear_data->wait = 48u;			
		
	}
	ToNormalState();
	if (bear_data->vx == 1){
		bear_data->vx = -1;
	}else{
		bear_data->vx = 1;
	}
}

void ToNormalState(){
	walk_fx_cooldown = WALK_FX_COOLDOWN-4;
	bear_data->enemy_state = ENEMY_STATE_NORMAL;
	SetSpriteAnim(THIS, bear_walk, 13u);	
}

void DESTROY() {
}
