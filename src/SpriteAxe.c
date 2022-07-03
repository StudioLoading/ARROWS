#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "custom_datas.h"


extern UINT8 current_level;

const UINT8 anim_axe_normal[] = {6, 0, 1, 2, 3, 4, 5}; //The first number indicates the number of frames

void START() {
	THIS->lim_x = 80u;
	THIS->lim_y = 80u;
	SetSpriteAnim(THIS, anim_axe_normal, 28u);
	struct EnemyInfo* axedata = (struct EnemyInfo*)THIS->custom_data;
	axedata->enemy_state = ENEMY_STATE_NORMAL;
	axedata->wait = 0u;
	axedata->hp = 24;
	axedata->vx = -3;
	axedata->enemy_accel_y = -20;
}

void UPDATE(){
	struct EnemyInfo* axedata = (struct EnemyInfo*)THIS->custom_data;
	axedata->wait++;
	axedata->hp--;
	if(axedata->hp == 0){
		PlayFx(CHANNEL_1, 60, 0x23, 0xcc, 0xf7, 0x43, 0x85);
		axedata->hp = 24;
	}
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

void DESTROY() {
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y-4u);
}