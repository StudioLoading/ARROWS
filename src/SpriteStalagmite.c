#include "Banks/SetBank9.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//STALAGMITE
const UINT8 stalag_drop[] = {1, 5}; //The first number indicates the number of frames
const UINT8 stalag_drop_big[] = {1, 4}; //The first number indicates the number of frames
const UINT8 stalag_low[] = {1, 3}; //The first number indicates the number of frames
const UINT8 stalag_mid[] = {1, 2}; //The first number indicates the number of frames
const UINT8 stalag_hl[] = {1, 1}; //The first number indicates the number of frames
const UINT8 stalag_hh[] = {1, 0}; //The first number indicates the number of frames

void CheckCollisionStalagTile(struct EnemyInfo* stalag_data);

void Start_SpriteStalagmite() {
	
	THIS->coll_x = 1;
	THIS->coll_y = 4;
	THIS->coll_w = 6;
	THIS->coll_h = 4;
	THIS->lim_x = 240u;
	THIS->lim_y = 40u;
	SetSpriteAnim(THIS, stalag_drop_big, 4u);
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;	
	rdata->enemy_accel_y = 20;
	rdata->vx = 0;
	rdata->wait = 20u;
	rdata->hp = 24u;
	rdata->enemy_state = STALAG_STATE_WAIT;
	/*
	
	STALAG_STATE_WAIT,
	STALAG_STATE_DROP,
	STALAG_STATE_LOW,
	STALAG_STATE_MED,
	STALAG_STATE_HIGH
	
	*/
}

void Update_SpriteStalagmite() {
	
	struct EnemyInfo* rdata = (struct EnemyInfo*)THIS->custom_data;
	if(rdata->wait > 5u){
		rdata->wait -= 1u;
		return;
	}
	switch(rdata->enemy_state){
		case STALAG_STATE_WAIT:
			SetSpriteAnim(THIS, stalag_drop, 4u);
			rdata->enemy_state = STALAG_STATE_DROP;
			return;
		break;
		case STALAG_STATE_DROP:
			rdata->tile_e_collision = TranslateSprite(THIS, 0, (rdata->enemy_accel_y >> 4)<< delta_time);
			if(rdata->tile_e_collision) {
				CheckCollisionStalagTile(rdata);
			}		
		break;
		case STALAG_STATE_LOW:
		
		break;
		case STALAG_STATE_HIGH:
			//rdata->tile_e_collision = TranslateSprite(THIS, 0, 1);
		break;
	}
	
	UINT8 scroll_st_tile;
	struct Sprite* istspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_st_tile, istspr) {
		if(istspr->type == SpritePlayer || istspr->type == SpriteArrow) {
			if(CheckCollision(THIS, istspr)) {
				if(rdata->enemy_state == STALAG_STATE_DROP){
					SpriteManagerRemoveSprite(THIS);
				}else{//altrimenti capiamo che freccia è prima di romperci
					if(istspr->type == SpriteArrow){
						if(rdata->enemy_state == STALAG_STATE_HIGH){						
							//struct ArrowInfo* arrowdata = (struct ArrowInfo*)istspr->custom_data;
							//if(arrowdata->original_type == 4){
							SpriteManagerRemoveSprite(THIS);								
							//}
						}
						SpriteManagerRemoveSprite(istspr);
					}
				}
			}
		}
		if(istspr->type == SpriteStalagmite) {
			if(CheckCollision(THIS, istspr) && istspr != THIS) {
				SpriteManagerRemoveSprite(THIS);
				struct EnemyInfo* sdata = (struct EnemyInfo*)istspr->custom_data;
				switch (sdata->enemy_state){
					case STALAG_STATE_LOW:
						istspr->y -= 6u;
						SetSpriteAnim(istspr, stalag_mid, 4u);
						sdata->enemy_state = STALAG_STATE_MED;
						istspr->coll_x = 1;
						istspr->coll_y = 1;
						istspr->coll_w = 6;
						istspr->coll_h = 14;
					break;
					case STALAG_STATE_MED:
						SetSpriteAnim(istspr, stalag_hl, 4u);
						struct Sprite* upper_stalag = SpriteManagerAdd(SpriteStalagmite, istspr->x, istspr->y - 16u);
						struct EnemyInfo* supper_stalag_data = (struct EnemyInfo*)upper_stalag->custom_data;				
						upper_stalag->coll_y = 2;
						upper_stalag->coll_h = 14;
						supper_stalag_data->enemy_state = STALAG_STATE_HIGH;
						SetSpriteAnim(upper_stalag, stalag_hh, 4u);
						sdata->enemy_state = STALAG_STATE_MED;
					break;
				}
				//THIS->y += 1u;
				//fai crescere quella a terra, istspr deve crescere,
			}
		}
	}
	
}

void CheckCollisionStalagTile(struct EnemyInfo* stalag_data){
	switch(stalag_data->tile_e_collision){
		case 12u:
			SetSpriteAnim(THIS, stalag_low, 4u);
			stalag_data->enemy_state = STALAG_STATE_LOW;
			//SpriteManagerRemoveSprite(THIS); // elimino me stesso
		break;
		case 20u:
			SpriteManagerRemoveSprite(THIS);
		break;
	}
}

void Destroy_SpriteStalagmite(){
	SpriteManagerAdd(SpritePuff, THIS->x, (UINT16)THIS->y-3u);
}
