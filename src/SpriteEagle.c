#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//BIRD
const UINT8 eagle_idle[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 eagle_walk[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 eagle_hit[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 eagle_dead[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames
const UINT8 eagle_attack[] = {1, 3}; //The first number indicates the number of frames
const UINT8 eagle_up[] = {4, 0, 1, 2, 1}; //The first number indicates the number of frames

const UINT8 eagle_time_attack = 76u;
const UINT8 eagle_time_normal = 81u;

extern void CheckCollisionETile();
extern void ETurn();

void START() {
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, eagle_idle, 14u);
	data->enemy_accel_y = 0;
	data->vx = 1;
	data->wait = eagle_time_normal;
	data->hp = 3;
	data->enemy_state = ENEMY_STATE_NORMAL;
}

void UPDATE() {
	
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	
	if (data->enemy_state == ENEMY_STATE_DEAD || data->enemy_state == ENEMY_STATE_WAIT){
		return;
	}
	
	if (THIS->x == 0 & data->vx == -1){
		data->vx = 1;
	}
	
	if(THIS->y < 8 << 3){
		//data->enemy_accel_y = -32u;
		THIS->y++;
		return;
	}
	if (data->enemy_state == ENEMY_STATE_HIT){
		data->wait--;
		THIS->y--;
		if(data->wait){
			return;
		}else{
			data->enemy_accel_y = 0;
			data->wait = eagle_time_normal;
			SetSpriteAnim(THIS, eagle_walk, 14u);
			data->enemy_state = ENEMY_STATE_NORMAL;
			return;
		}
	}
	
	if (data->enemy_state == ENEMY_STATE_ATTACK){
		data->wait--;
		if(data->wait == (eagle_time_attack-1)){
			data->enemy_accel_y = 2;
		}else if (data->wait == 50u){
			data->enemy_accel_y = 0;
			SetSpriteAnim(THIS, eagle_walk, 14u);
		}else if(data->wait == 25u){
			SetSpriteAnim(THIS, eagle_up, 24u);
			data->enemy_accel_y = -2;
		}
		if (data->wait == 0u){
			data->enemy_accel_y = 0;
			data->wait = eagle_time_normal;
			SetSpriteAnim(THIS, eagle_walk, 14u);
			data->enemy_state = ENEMY_STATE_NORMAL;
			return;
		}
	}
	
	if (data->enemy_state == ENEMY_STATE_NORMAL){
		data->wait--;
		if(data->wait == 0u){
			SetSpriteAnim(THIS, eagle_attack, 14u);
			data->wait = eagle_time_attack;
			data->enemy_state = ENEMY_STATE_ATTACK;
			return;
		}
	}
	
	if(data->enemy_state == ENEMY_STATE_NORMAL){
		if(data->wait << 2){
			THIS->x += data->vx;
		}
		THIS->y += data->enemy_accel_y;	
	}else{		
		if(data->wait << 2){
			THIS->x += data->vx;
			THIS->y += data->enemy_accel_y;	
		}
	}
	
	UINT8 scroll_bi_tile;
	Sprite* ibispr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_bi_tile, ibispr) {
		if(ibispr->type == SpritePlayer) {
			if(data->enemy_state == ENEMY_STATE_NORMAL){ //  & data->wait == 40u
				if(THIS->x > ibispr->x){
					THIS->mirror = V_MIRROR; //SPRITE_SET_VMIRROR(THIS);
					if (data->vx == 1 & ((THIS->x - ibispr->x) > 24u) ){
						data->vx = -1;
					}
				}else if (THIS->x < ibispr->x){
					THIS->mirror = NO_MIRROR;//SPRITE_UNSET_VMIRROR(THIS);
					if (data->vx == -1 & ((ibispr->x - THIS->x) > 24u)){
						data->vx = 1;	
					}
				}
				if ((ibispr->x - THIS->x) == 33u | ((THIS->x - ibispr->x) == 33u)){
					SetSpriteAnim(THIS, eagle_attack, 14u);
					data->wait = eagle_time_attack;
					data->enemy_state = ENEMY_STATE_ATTACK;
				}
			}			
		}
		if(ibispr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibispr)) {
				struct ArrowInfo* arrowbidata = (struct ArrowInfo*)ibispr->custom_data;
				if(data->enemy_state != ENEMY_STATE_HIT && arrowbidata->arrowdir == 1){ //sensibile solo alle orizzontali
					data->enemy_state = ENEMY_STATE_HIT;
					data->wait = 32u;
					SetSpriteAnim(THIS, eagle_hit, 24u);
					SpriteManagerAdd(SpriteFeather, (UINT16) ibispr->x, (UINT16) ibispr->y);
					data->hp -= arrowbidata->original_type;
					if (data->hp <= 0){
						data->enemy_state = ENEMY_STATE_DEAD;
						data->hp = 0;
						THIS->x = (UINT16) 23u << 3;
						THIS->y = (UINT16) 13u << 3;
						data->vx=0;
						data->enemy_accel_y = 0;
						SetSpriteAnim(THIS, eagle_dead, 14u);
						PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
					}
					SpriteManagerRemoveSprite(ibispr);
				}
			}
		}
	}
	
}

void DESTROY() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	data->enemy_state = ENEMY_STATE_DEAD;
}
