#include "Banks/SetBank3.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//WOLF
const UINT8 wolf_idle[] = {1, 5}; //The first number indicates the number of frames
const UINT8 wolf_uuu[] = {1, 5}; //The first number indicates the number of frames
const UINT8 wolf_walk[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames
const UINT8 wolf_hit[] = {1, 5}; //The first number indicates the number of frames
const UINT8 wolf_dead[] = {1, 5}; //The first number indicates the number of frames

INT8 jump_i = 0;
struct EnemyInfo* wolf_data ;

void CheckCollisionBTile();
void BTurn();

void Start_SpriteWolf() {
	wolf_data = (struct EnemyInfo*)THIS->custom_data;
	THIS->coll_x = 4;
	THIS->coll_y = 5+16;
	THIS->coll_w = 8+16;
	THIS->coll_h = 11;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	SetSpriteAnim(THIS, wolf_uuu, 8u);
	wolf_data->enemy_accel_y = 24;
	wolf_data->vx = 1;
	wolf_data->wait = 0u;
	wolf_data->hp = 50;
	wolf_data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteWolf() {
	
	if(wolf_data->enemy_state == ENEMY_STATE_WAIT){
		return;
	}
	
	if (wolf_data->enemy_state == ENEMY_STATE_DEAD){
		if(wolf_data->tile_e_collision==0){
			wolf_data->tile_e_collision = TranslateSprite(THIS, 0, 1);	
		}
		if(wolf_data->hp){
			wolf_data->hp = 0;			
		}
		return;
	}
	if (wolf_data->enemy_state == ENEMY_STATE_JUMPING){
		jump_i += 1;
		if (jump_i == 44){
			SetSpriteAnim(THIS, wolf_walk, 12u);
			wolf_data->enemy_state = ENEMY_STATE_NORMAL;
			jump_i = 0;
			wolf_data->enemy_accel_y = 20;
		}
	}
	if (wolf_data->wait > 0u){
		wolf_data->wait -= 1u;
		if (wolf_data->wait == 0u){
			SetSpriteAnim(THIS, wolf_walk, 12u);
		}
	}else{
		if(wolf_data->enemy_accel_y < 24) {
			wolf_data->enemy_accel_y += 1;
		}
		if (wolf_data->vx > 0 & !SPRITE_GET_VMIRROR(THIS)){
			SPRITE_SET_VMIRROR(THIS);
		}
		if(wolf_data->vx < 0 & SPRITE_GET_VMIRROR(THIS)){
			SPRITE_UNSET_VMIRROR(THIS);
		}
		wolf_data->tile_e_collision = TranslateSprite(THIS, wolf_data->vx << delta_time, (wolf_data->enemy_accel_y >> 4)<< delta_time);
		if(!wolf_data->tile_e_collision && delta_time != 0 && wolf_data->enemy_accel_y < 24) { //Do another iteration if there is no collision
			wolf_data->enemy_accel_y += 2;
			wolf_data->tile_e_collision = TranslateSprite(THIS, 0, (wolf_data->enemy_accel_y >> 4) << delta_time);
		}
		
		if(wolf_data->tile_e_collision) {
			if(wolf_data->enemy_state == ENEMY_STATE_JUMPING & wolf_data->enemy_accel_y > 0) {
				wolf_data->enemy_state = ENEMY_STATE_NORMAL;
				SetSpriteAnim(THIS, wolf_walk, 12u);
			}else{
				wolf_data->enemy_accel_y = 0;	
			}
			CheckCollisionBTile();
		}
		
		if(THIS->x == 25*8 & wolf_data->enemy_state != ENEMY_STATE_JUMPING){
			SetSpriteAnim(THIS, wolf_idle, 8u);
			wolf_data->enemy_state = ENEMY_STATE_JUMPING;
			wolf_data->enemy_accel_y = -24;
		}
	}//fine else non wait
	

	UINT8 scroll_b_tile;
	struct Sprite* ibspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_b_tile, ibspr) {
		if(ibspr->type == SpritePlayer) {
			if(CheckCollision(THIS, ibspr)) {
				wolf_data->wait = 24u;
			}
		}
		if(ibspr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibspr) && wolf_data->enemy_state != ENEMY_STATE_DEAD) {
				if(wolf_data->enemy_state == ENEMY_STATE_JUMPING){ 
					struct ArrowInfo* arrowdata = (struct ArrowInfo*)ibspr->custom_data;
					if (arrowdata->arrowdir != 1){ //hit solo se freccia non orizzontale
						wolf_data->wait = 28u;
						SetSpriteAnim(THIS, wolf_hit, 18u);
						if(arrowdata->arrowdamage){
							wolf_data->hp -= arrowdata->arrowdamage;
						}
					}
				}
				SpriteManagerRemoveSprite(ibspr);
				if (wolf_data->hp <= 0 && wolf_data->enemy_state != ENEMY_STATE_DEAD){
					wolf_data->hp = 0;
					SetSpriteAnim(THIS, wolf_dead, 16u);
					wolf_data->enemy_state = ENEMY_STATE_DEAD;
				}
			}
		}
	}
	
}

void CheckCollisionBTile() {
	switch(wolf_data->tile_e_collision) {
		case 3u:
			TranslateSprite(THIS, 0, 2);
		break;
		case 4u:
		case 5u:
		case 7u:
		case 18u:
		case 19u:
			BTurn();
		break;
	}
}

void BTurn(){
	if (wolf_data->vx == 1){
		SPRITE_UNSET_VMIRROR(THIS);
		THIS->x -= 4;
		wolf_data->wait = 48u;
	}
	if (wolf_data->vx == -1){
		SPRITE_SET_VMIRROR(THIS);
		THIS->x += 4;
		wolf_data->wait = 48u;			
		
	}
	SetSpriteAnim(THIS, wolf_uuu, 16u);
	wolf_data->vx = -wolf_data->vx;
}

void Destroy_SpriteWolf() {
}
