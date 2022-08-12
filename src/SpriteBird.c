#include "Banks/SetAutoBank.h"

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

extern void CheckCollisionETile() BANKED;
extern void ETurn() BANKED;
extern void EDie() BANKED;


void START() {
	
	THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 7;
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

void UPDATE() {
	
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	
	switch(data->enemy_state){
		case ENEMY_STATE_DEAD:
			if (data->wait > 0){
				THIS->y--;
				data->wait--;
			}else{
				SpriteManagerRemoveSprite(THIS);
				SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
				THIS->y++;	
				THIS->y++;
			}		
		break;
		case ENEMY_STATE_HIT:
			data->wait--;
			if(data->wait){
				return;
			}
		break;
		case ENEMY_STATE_ATTACK:
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
		break;
		case ENEMY_STATE_NORMAL:
			data->wait--;
			if(data->wait == 0u){
				SetSpriteAnim(THIS, bird_attack, 8u);
				data->wait = bird_time_attack;
				data->enemy_state = ENEMY_STATE_ATTACK;
				return;
			}
			//THIS->x += data->vx;
			data->tile_e_collision = TranslateSprite(THIS, data->vx << delta_time, data->enemy_accel_y << delta_time);
			if(data->tile_e_collision == 40u){//skull of death
				EDie();
			}
			if(data->tile_e_collision == 77u){//boss chasing
				SpriteManagerRemoveSprite(THIS);
			}
		break;
		//THIS->y += data->enemy_accel_y;	
	}
	if(data->enemy_state != ENEMY_STATE_NORMAL){
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
	Sprite* ibispr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_bi_tile, ibispr) {
		if(ibispr->type == SpritePlayer) {
			if(data->enemy_state == ENEMY_STATE_NORMAL){ //  & data->wait == 40u
				if(THIS->x > ibispr->x & data->vx == 1 & ((THIS->x - ibispr->x) > 24u) ){
					data->vx = -1;
					THIS->mirror = V_MIRROR; //SPRITE_SET_VMIRROR(THIS);
				}else if (THIS->x < ibispr->x & data->vx == -1 & ((ibispr->x - THIS->x) > 24u)){
					data->vx = 1;
					THIS->mirror = NO_MIRROR; //SPRITE_UNSET_VMIRROR(THIS);
				}
				if ((ibispr->x - THIS->x) == 33u || ((THIS->x - ibispr->x) == 33u)){
					SetSpriteAnim(THIS, bird_attack, 8u);
					data->wait = bird_time_attack;
					data->enemy_state = ENEMY_STATE_ATTACK;					
				}
			}
			
		}
		if(CheckCollision(THIS, ibispr)) {
			if(ibispr->type == SpriteArrowmother) {
				SpriteManagerRemoveSprite(THIS);
			}else if(ibispr->type == SpriteArrow) {
				SpriteManagerRemoveSprite(ibispr);
				struct ArrowInfo* arrowbidata = (struct ArrowInfo*)ibispr->custom_data;
				data->enemy_state = ENEMY_STATE_HIT;
				data->wait = 30u;
				SetSpriteAnim(THIS, bird_hit, 24u); 
				PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);//hit sound
				data->hp -= arrowbidata->arrowdamage;
				if (data->hp <= 0){
					data->wait = 8u;
					data->enemy_state = ENEMY_STATE_DEAD;
					SetSpriteAnim(THIS, bird_dead, 16u);
				}
			}
		}
	}
	
}

void DESTROY() {
	struct EnemyInfo* data = (struct EnemyInfo*)THIS->custom_data;
	data->enemy_state = ENEMY_STATE_DEAD;
}
