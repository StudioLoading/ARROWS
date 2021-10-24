#include "Banks/SetBank9.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//STALAGMITE
const UINT8 stalat_drop[] = {1, 0}; //The first number indicates the number of frames

void CheckCollisionStalatTile(struct EnemyInfo* stalat_data);

void Start_SpriteStalattite() {
	
	THIS->coll_x = 1;
	THIS->coll_y = 4;
	THIS->coll_w = 6;
	THIS->coll_h = 4;
	THIS->lim_x = 200u;
	THIS->lim_y = 80u;
	SetSpriteAnim(THIS, stalat_drop, 4u);
	struct EnemyInfo* ldata = (struct EnemyInfo*)THIS->custom_data;	
	ldata->enemy_accel_y = 11;
	ldata->vx = 0;
	ldata->wait = 40u;
	ldata->hp = 24u;
	ldata->enemy_state = ENEMY_STATE_WAIT;
	/*	
	STALAG_STATE_WAIT,
	STALAG_STATE_DROP,
	STALAG_STATE_LOW,
	STALAG_STATE_MED,
	STALAG_STATE_HIGH	
	*/
}

void Update_SpriteStalattite() {
	
	struct EnemyInfo* ldata = (struct EnemyInfo*)THIS->custom_data;
	UINT8 scroll_sl_tile;
	struct Sprite* islspr;	
	
	switch(ldata->enemy_state){
		case ENEMY_STATE_WAIT:		
			//Check sprite collision platform/enemy
			SPRITEMANAGER_ITERATE(scroll_sl_tile, islspr) {
				if(islspr->type == SpritePlayer && ((THIS->x - islspr->x) < 60u)) {
					ldata->enemy_state = STALAG_STATE_WAIT;
				}
			}
		break;
		case STALAG_STATE_WAIT:
			ldata->wait -= 1u;
			switch(ldata->wait){
				case 40u:
				case 30u:
				case 20u:
				case 10u:
					THIS->x -= 3u;
				break;
				case 35u:
				case 25u:
				case 15u:
				case 5u:
					THIS->x += 3u;
				break;
				case 0u:
					ldata->enemy_state = STALAG_STATE_DROP;
				break;
			}
		break;
		case STALAG_STATE_DROP:
			ldata->tile_e_collision = TranslateSprite(THIS, 0, (ldata->enemy_accel_y >> 2) << delta_time);
			if(ldata->tile_e_collision) {
				CheckCollisionStalatTile(ldata);
			}
		break;
	}
	
	
}

void CheckCollisionStalatTile(struct EnemyInfo* stalat_data){
	SpriteManagerRemoveSprite(THIS);
}

void Destroy_SpriteStalattite(){
	SpriteManagerAdd(SpritePuff, THIS->x, (UINT16)THIS->y-3u);
}
