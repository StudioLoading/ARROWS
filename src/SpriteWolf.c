#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"

//WOLF
const UINT8 wolf_uuu[] = {1, 5}; //The first number indicates the number of frames
const UINT8 wolf_walk[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames
const UINT8 wolf_jump[] = {1, 0}; //The first number indicates the number of frames
const UINT8 wolf_hit[] = {2, 4, 5}; //The first number indicates the number of frames
const UINT8 wolf_dead[] = {1, 5}; //The first number indicates the number of frames

INT8 jump_i = 0;
struct EnemyInfo* wolf_data ;
INT8 walk_fx_cooldown = 0;

void CheckCollisionBTile();
void BTurn();

void START() {
	wolf_data = (struct EnemyInfo*)THIS->custom_data;
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	SetSpriteAnim(THIS, wolf_uuu, 8u);
	wolf_data->enemy_accel_y = 25;
	wolf_data->vx = 1;
	wolf_data->wait = 0u;
	wolf_data->hp = 1;
	wolf_data->enemy_state = ENEMY_STATE_NORMAL;
}

void UPDATE() {
	
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
			SetSpriteAnim(THIS, wolf_walk, 13u);
			wolf_data->enemy_state = ENEMY_STATE_NORMAL;
			walk_fx_cooldown = WALK_FX_COOLDOWN-4;
			jump_i = 0;
			wolf_data->enemy_accel_y = 25;
		}
	}
	if (wolf_data->wait > 0u){
		wolf_data->wait -= 1u;
		if (wolf_data->wait == 0u){
			SetSpriteAnim(THIS, wolf_walk, 13u);
		}
	}else{
		if(wolf_data->enemy_accel_y < 25) {
			wolf_data->enemy_accel_y += 1;
		}
		if (wolf_data->vx > 0 && THIS->mirror != V_MIRROR){
			THIS->mirror = V_MIRROR;//SPRITE_SET_VMIRROR(THIS);
		}
		if(wolf_data->vx < 0 && THIS->mirror == V_MIRROR){
			THIS->mirror = NO_MIRROR;//SPRITE_UNSET_VMIRROR(THIS);
		}
		walk_fx_cooldown++;
		if(walk_fx_cooldown == WALK_FX_COOLDOWN){
			PlayFx(CHANNEL_4, 60, 0x3a, 0xd2, 0x00, 0xc0, 0x85);
			walk_fx_cooldown = 0;
		}
		wolf_data->tile_e_collision = TranslateSprite(THIS, wolf_data->vx << delta_time, (wolf_data->enemy_accel_y >> 4)<< delta_time);
		if(!wolf_data->tile_e_collision && delta_time != 0 && wolf_data->enemy_accel_y < 26) { //Do another iteration if there is no collision
			wolf_data->enemy_accel_y += 2;
			wolf_data->tile_e_collision = TranslateSprite(THIS, 0, (wolf_data->enemy_accel_y >> 4) << delta_time);
		}
		
		if(wolf_data->tile_e_collision) {
			if(wolf_data->enemy_state == ENEMY_STATE_JUMPING && wolf_data->enemy_accel_y > 0) {
				wolf_data->enemy_state = ENEMY_STATE_NORMAL;
				SetSpriteAnim(THIS, wolf_walk, 13u);
				walk_fx_cooldown = WALK_FX_COOLDOWN-4;
			}else{
				wolf_data->enemy_accel_y = 0;	
			}
			CheckCollisionBTile();
		}
		
		if((THIS->x == (UINT16) 24u << 3 && wolf_data->enemy_state != ENEMY_STATE_JUMPING && THIS->mirror == V_MIRROR) ||
			(THIS->x == (UINT16) 26u << 3 && wolf_data->enemy_state != ENEMY_STATE_JUMPING && THIS->mirror != V_MIRROR)){
			SetSpriteAnim(THIS, wolf_jump, 8u);
			PlayFx(CHANNEL_1, 60, 0x17, 0x82, 0xf1, 0x7e, 0x84);
			wolf_data->enemy_state = ENEMY_STATE_JUMPING;
			wolf_data->enemy_accel_y = -25;
		}
	}//fine else non wait
	

	UINT8 scroll_b_tile;
	Sprite* ibspr;
	
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
						SetSpriteAnim(THIS, wolf_hit, 16u);
						wolf_data->hp -= arrowdata->original_type;
						PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);//hit sound
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
		THIS->mirror = NO_MIRROR;//SPRITE_UNSET_VMIRROR(THIS);
		THIS->x -= 4;
		wolf_data->wait = 48u;
	}
	if (wolf_data->vx == -1){
		THIS->mirror = V_MIRROR;//SPRITE_SET_VMIRROR(THIS);
		THIS->x += 4;
		wolf_data->wait = 48u;			
		
	}
	SetSpriteAnim(THIS, wolf_uuu, 16u);
	wolf_data->vx = -wolf_data->vx;
}

void DESTROY() {
}
