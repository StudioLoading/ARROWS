#include "Banks/SetBank8.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//IBEX
const UINT8 ibex_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 ibex_walk[] = {5, 0,1,0,2,0};
const UINT8 ibex_hit[] = {2, 0, 1};
const UINT8 ibex_dead[] = {1, 0};
const UINT8 ibex_jump_up[] = {1, 4};
const UINT8 ibex_jump_down[] = {1, 3};

extern INT8 jump_i;

struct EnemyInfo* ibex_data ;

void CheckCollisionIBTile();
void IBTurn();

void Start_SpriteIbex() {
	THIS->coll_x = 2;
	THIS->coll_y = 2;
	THIS->coll_w = 12;
	THIS->coll_h = 14;
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
	SetSpriteAnim(THIS, ibex_walk, 10u);
	ibex_data = (struct EnemyInfo*)THIS->custom_data;
	ibex_data->enemy_accel_y = 24;
	ibex_data->vx = 1;
	ibex_data->wait = 0u;
	ibex_data->hp = 80;
	ibex_data->enemy_state = ENEMY_STATE_NORMAL;
}

void Update_SpriteIbex() {
	if(ibex_data->enemy_state == ENEMY_STATE_WAIT){
		return;
	}
	
	if (ibex_data->enemy_state == ENEMY_STATE_DEAD){
		if(ibex_data->tile_e_collision==0){
			ibex_data->tile_e_collision = TranslateSprite(THIS, 0, 1);	
		}
		ibex_data->hp = 0;
		return;
	}
	
	if (ibex_data->enemy_state == ENEMY_STATE_JUMPING){
		jump_i += 1;
		if(ibex_data->enemy_accel_y > 0){
			if (ibex_data->enemy_accel_y < 3){
				SetSpriteAnim(THIS, ibex_jump_down, 8u);
			}
		}
		if (jump_i == 64){
			SetSpriteAnim(THIS, ibex_walk, 8u);
			ibex_data->enemy_state = ENEMY_STATE_NORMAL;
			jump_i = 0;
			ibex_data->enemy_accel_y = 24;
		}
	}
	if (ibex_data->wait > 0u){
		ibex_data->wait -= 1u;
		if (ibex_data->wait == 0u){
			SetSpriteAnim(THIS, ibex_walk, 8u);
		}
	}else{
		if(ibex_data->enemy_accel_y < 24) {
			ibex_data->enemy_accel_y += 1;
		}
		if (ibex_data->vx > 0 & !SPRITE_GET_VMIRROR(THIS)){
			SPRITE_SET_VMIRROR(THIS);
		}
		if(ibex_data->vx < 0 & SPRITE_GET_VMIRROR(THIS)){
			SPRITE_UNSET_VMIRROR(THIS);
		}
		ibex_data->tile_e_collision = TranslateSprite(THIS, ibex_data->vx << delta_time, (ibex_data->enemy_accel_y >> 4)<< delta_time);
		if(!ibex_data->tile_e_collision && delta_time != 0 && ibex_data->enemy_accel_y < 24) { //Do another iteration if there is no collision
			ibex_data->enemy_accel_y += 2;
			ibex_data->tile_e_collision = TranslateSprite(THIS, 0, (ibex_data->enemy_accel_y >> 4) << delta_time);
		}
		
		if(ibex_data->tile_e_collision) {
			if(ibex_data->enemy_state == ENEMY_STATE_JUMPING & ibex_data->enemy_accel_y > 0) {
				ibex_data->enemy_state = ENEMY_STATE_NORMAL;
				SetSpriteAnim(THIS, ibex_walk, 8u);
			}else{
				ibex_data->enemy_accel_y = 0;	
			}
			CheckCollisionIBTile();
		}
		
		if(ibex_data->vx < 0){
			if(ibex_data->enemy_state != ENEMY_STATE_JUMPING){			
				if(THIS->x == (UINT16) 25u << 3 || (THIS->x == (UINT16) 21u << 3 & ibex_data->hp < 20)){
					ibex_data->vx = -1;
					SetSpriteAnim(THIS, ibex_walk, 8u);
					ibex_data->enemy_state = ENEMY_STATE_JUMPING;
					SetSpriteAnim(THIS, ibex_jump_up, 8u);
					ibex_data->enemy_accel_y = -24;
				}	
			}
		}
	}//fine else non wait


	UINT8 scroll_ib_tile;
	struct Sprite* ibbspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_ib_tile, ibbspr) {
		if(ibbspr->type == SpritePlayer) {
			if(CheckCollision(THIS, ibbspr)) {
				ibex_data->wait = 24u;
			}
		}
		if(ibbspr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibbspr) & ibex_data->enemy_state != ENEMY_STATE_DEAD) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ibbspr->custom_data;
				if(arrowdata->original_type == 3){
					ibex_data->wait = 28u;
					SetSpriteAnim(THIS, ibex_hit, 18u);
					ibex_data->hp -= arrowdata->arrowdamage;
					if (ibex_data->vx < 0){
						THIS->x++;
					}else{
						THIS->x--;
					}
				}
				SpriteManagerRemoveSprite(ibbspr);
				if (ibex_data->hp <= 0){
					ibex_data->enemy_state = ENEMY_STATE_DEAD;
					ibex_data->hp = 0;
					THIS->x = (UINT16) 24u << 3;
					THIS->y = (UINT16) 14u << 3;
					SetSpriteAnim(THIS, ibex_dead, 16u);
				}
			}
		}
	}
}

void CheckCollisionIBTile() {
	switch(ibex_data->tile_e_collision) {
		case 3u:
		case 16u:
			TranslateSprite(THIS, 0, 2);
		break;
		case 4u:
		case 5u:
		case 7u:
		case 18u:
		case 19u:
			IBTurn();
		break;
		case 90u:
		case 111u:
			THIS->y++;
		break;
	}
}

void IBTurn(){
	if (ibex_data->vx == 1){
		SPRITE_UNSET_VMIRROR(THIS);
		THIS->x -= 4;
		ibex_data->wait = 48u;
	}
	if (ibex_data->vx == -2){
		SPRITE_SET_VMIRROR(THIS);
		THIS->x += 4;
		ibex_data->wait = 48u;			
		
	}
	SetSpriteAnim(THIS, ibex_walk, 8u);
	if (ibex_data->vx == 1){
		ibex_data->vx = -2;
	}else{
		ibex_data->vx = 1;
	}
}

void Destroy_SpriteIbex() {
}
