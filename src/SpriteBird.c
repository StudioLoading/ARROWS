#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//BIRD
const UINT8 bird_walk[] = {2, 1, 3}; //The first number indicates the number of frames
const UINT8 bird_hit[] = {2, 3, 2}; //The first number indicates the number of frames
const UINT8 bird_dead[] = {1, 0}; //The first number indicates the number of frames
const UINT8 bird_attack[] = {1, 0}; //The first number indicates the number of frames
const UINT8 bird_up[] = {1, 4}; //The first number indicates the number of frames

const UINT8 bird_time_attack = 76u;
const UINT8 bird_time_normal = 81u;

extern void CheckCollisionETile();
extern void ETurn();
extern void EDie();


void Start_SpriteBird() {
	
	THIS->coll_x = 0;
	THIS->coll_y = 7;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 255u;
	THIS->lim_y = 128u;
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;	
	SetSpriteAnim(THIS, bird_walk, 8u);
	data->enemy_accel_y = 0;
	data->vx = 1;
	data->wait = bird_time_normal;
	data->hp = 5;
	data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteBird() {
	
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	
	if (data->enemy_state == ENEMY_STATE_DEAD){
		if (data->wait > 0){
			THIS->y--;
			data->wait--;
		}else{
			SpriteManagerRemoveSprite(THIS);
			THIS->y++;	
			THIS->y++;
		}		
		return;
	}
	
	if (data->enemy_state == ENEMY_STATE_HIT){
		data->wait--;
		if(data->wait){
			return;
		}
	}
	
	if (data->enemy_state == ENEMY_STATE_ATTACK){
		data->wait--;
		if(data->wait == (bird_time_attack-1)){
			data->enemy_accel_y = 2;
		}else if (data->wait == 50u){
			data->enemy_accel_y = 0;
			SetSpriteAnim(THIS, bird_walk, 8u);
		}else if(data->wait == 25u){
			SetSpriteAnim(THIS, bird_up, 8u);
			data->enemy_accel_y = -2;
		}
		if (data->wait == 0u){
			data->enemy_accel_y = 0;
			data->wait = bird_time_normal;
			SetSpriteAnim(THIS, bird_walk, 8u);
			data->enemy_state = ENEMY_STATE_NORMAL;
			return;
		}
	}
	
	if (data->enemy_state == ENEMY_STATE_NORMAL){
		data->wait--;
		if(data->wait == 0u){
			SetSpriteAnim(THIS, bird_attack, 8u);
			data->wait = bird_time_attack;
			data->enemy_state = ENEMY_STATE_ATTACK;
			return;
		}
	}
	
	if(data->enemy_state == ENEMY_STATE_NORMAL){
		//THIS->x += data->vx;
		data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, data->enemy_accel_y << delta_time);
		if(data->tile_e_collision == 40u){//skull of death
			EDie();
		}
		//THIS->y += data->enemy_accel_y;	
	}else{		
		if(data->wait << 2){
			data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, data->enemy_accel_y << delta_time);
			if(data->tile_e_collision == 40u){//skull of death
				EDie();
			}
			//THIS->x += data->vx;
			//THIS->y += data->enemy_accel_y;
		}
	}
	
	UINT8 scroll_bi_tile;
	struct Sprite* ibispr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_bi_tile, ibispr) {
		if(ibispr->type == SpritePlayer) {
			if(data->enemy_state == ENEMY_STATE_NORMAL){ //  & data->wait == 40u
				if(THIS->x > ibispr->x & data->vx == 1 & ((THIS->x - ibispr->x) > 24u) ){
					data->vx = -1;
					SPRITE_SET_VMIRROR(THIS);
				}else if (THIS->x < ibispr->x & data->vx == -1 & ((ibispr->x - THIS->x) > 24u)){
					data->vx = 1;
					SPRITE_UNSET_VMIRROR(THIS);
				}
				if ((ibispr->x - THIS->x) == 33u | ((THIS->x - ibispr->x) == 33u)){
					SetSpriteAnim(THIS, bird_attack, 8u);
					data->wait = bird_time_attack;
					data->enemy_state = ENEMY_STATE_ATTACK;					
				}
			}
			
		}
		if(ibispr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibispr)) {
				SpriteManagerRemoveSprite(ibispr);
				struct ArrowInfo* arrowbidata = (struct ArrowInfo*)ibispr->custom_data;
				data->enemy_state = ENEMY_STATE_HIT;
				data->wait = 30u;
				SetSpriteAnim(THIS, bird_hit, 24u); 
				data->hp -= arrowbidata->arrowdamage;
				if (data->hp <= 0){
					data->wait = 8u;
					data->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, bird_dead, 16u);
					NR50_REG = 0x55; //Max volume		
					PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
				}
			}
		}
	}
	
}

void Destroy_SpriteBird() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	data->enemy_state = ENEMY_STATE_DEAD;
}
