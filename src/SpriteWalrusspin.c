#include "Banks/SetBank14.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//WALRUS
const UINT8 walrusspin_spin[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames
const UINT8 walrusspin_hidden[] = {1, 6}; //The first number indicates the number of frames
const UINT8 walrusspin_swim_deep[] = {6, 7, 7, 5, 5, 7, 5}; //The first number indicates the number of frames
const UINT8 walrusspin_swim_surface[] = {4, 4, 5, 4, 4}; //The first number indicates the number of frames

struct EnemyInfo* walrusspin_data ;
extern struct EnemyInfo* walrus_data;


void Start_SpriteWalrusspin() {
	walrusspin_data = (struct EnemyInfo*)THIS->custom_data;
	THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, walrusspin_hidden, 4u);
	walrusspin_data->enemy_accel_y = 24;
	walrusspin_data->vx = 0;
	walrusspin_data->wait = 250u;
	walrusspin_data->hp = 80;
	walrusspin_data->enemy_state = ENEMY_STATE_HIDDEN;
}

void Update_SpriteWalrusspin() {
	
	if(walrus_data->enemy_state == WALRUS_STATE_SPIN && walrusspin_data->enemy_state != WALRUS_STATE_SPIN){
		SetSpriteAnim(THIS, walrusspin_spin, 32u);
		walrusspin_data->enemy_state = WALRUS_STATE_SPIN;
	}
	
	if(walrus_data->enemy_state == WALRUS_STATE_JUMP_UP && walrusspin_data->enemy_state != WALRUS_STATE_JUMP_UP){
		SetSpriteAnim(THIS, walrusspin_hidden, 4u);
		walrusspin_data->enemy_state = WALRUS_STATE_JUMP_UP;
	}	
	
	if(walrus_data->enemy_state == WALRUS_STATE_JUMP_DOWN && walrusspin_data->enemy_state != WALRUS_STATE_JUMP_DOWN){
		SetSpriteAnim(THIS, walrusspin_hidden, 4u);
		walrusspin_data->enemy_state = WALRUS_STATE_JUMP_DOWN;
	}	
	
	if(walrus_data->enemy_state == WALRUS_STATE_SWIMMING && walrusspin_data->enemy_state != WALRUS_STATE_SWIMMING){
		SetSpriteAnim(THIS, walrusspin_swim_deep, 8u);
		walrusspin_data->wait = 255u;
		walrusspin_data->enemy_state = WALRUS_STATE_SWIMMING;
	}
	
	if(walrus_data->enemy_state == ENEMY_STATE_DEAD && walrusspin_data->enemy_state != ENEMY_STATE_DEAD){
		SetSpriteAnim(THIS, walrusspin_hidden, 4u);
		walrusspin_data->enemy_state = ENEMY_STATE_DEAD;
	}
	
}

void Destroy_SpriteWalrusspin() {
}
