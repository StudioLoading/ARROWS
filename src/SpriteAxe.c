#include "Banks/SetBank16.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


extern UINT8 current_level;

const UINT8 anim_axe_normal[] = {6, 0, 1, 2, 3, 4, 5}; //The first number indicates the number of frames

void Start_SpriteAxe() {	
	THIS->coll_x = 2;
	THIS->coll_y = 2;
	THIS->coll_w = 4;
	THIS->coll_h = 4;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, anim_axe_normal, 28u);
	struct EnemyInfo* axedata = (struct EnemyInfo*)THIS->custom_data;
	axedata->enemy_state = ENEMY_STATE_NORMAL;
	axedata->wait = 0u;
	axedata->hp = 45;
	axedata->vx = -3;
	axedata->enemy_accel_y = -20;
}

void Update_SpriteAxe(){
	struct EnemyInfo* axedata = (struct EnemyInfo*)THIS->custom_data;
	axedata->wait++;
	if(axedata->enemy_accel_y < 24) {
		axedata->enemy_accel_y += 1;
	}
	if(axedata->wait & 1){
		axedata->tile_e_collision = TranslateSprite(THIS, 0, (axedata->enemy_accel_y >> 3) << delta_time);	
	}else{
		axedata->tile_e_collision = TranslateSprite(THIS, axedata->vx, (axedata->enemy_accel_y >> 3) << delta_time);	
	}
	if(axedata->tile_e_collision){
		SpriteManagerRemove(THIS_IDX);
	}
	
}

void Destroy_SpriteAxe() {
	//SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-4u);
}