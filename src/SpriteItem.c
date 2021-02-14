#include "Banks/SetBank6.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

const UINT8 item_hidden[] = {1, 0}; //The first number indicates the number of frames
const UINT8 item_coin[] = {1, 1}; //The first number indicates the number of frames
const UINT8 item_hp[] = {1, 3}; //The first number indicates the number of frames
const UINT8 item_up[] = {1, 2}; //The first number indicates the number of frames
const UINT8 item_scrigno[] = {1, 4}; //The first number indicates the number of frames
const UINT8 item_scrignoaperto[] = {1, 5}; //The first number indicates the number of frames
const UINT8 item_wrench[] = {1, 6};
const UINT8 item_dcoin[] = {1, 7}; //The first number indicates the number of frames


void Start_SpriteItem() {
	
	SetSpriteAnim(THIS, item_hidden, 8u);

	struct ItemInfo* data = (struct ItemInfo*)THIS->custom_data;
	data->collided = 0;
	data->setup = 1u;
	data->counter = -1;
	data->item_accel_y = 0;
	data->type = 0;
	data->vx = 0;
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 255;
	THIS->lim_y = 255;
}

void Update_SpriteItem() {
	
	struct ItemInfo* data = (struct ItemInfo*)THIS->custom_data;
	if (data->type == 10){ //gestione scrigno dedicata
			if (data->setup){
				SetSpriteAnim(THIS, item_scrigno, 8u);
				data->setup = 0;
				data->item_accel_y = 24;
			}else{				
				if(data->item_accel_y < 24) {
					data->item_accel_y += 1;
				}
				if(!data->tile_i_collision && delta_time != 0 && data->item_accel_y < 36) { //Do another iteration if there is no collision
					data->item_accel_y += 2;
					data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
				}		
				data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
				if(data->tile_i_collision) {
					data->item_accel_y = 0;	
				}				
				if (data->counter == -1 & data->collided & data->type != data->content_type){
					SetSpriteAnim(THIS, item_scrignoaperto, 8u);
					data->counter = 24;
				}		
				if(data->counter > 0){
					data->counter -= 1;
				}				
				if (data->counter == 0){
					THIS->y -= 20;
					data->type = data->content_type;
					data->setup = 1u;
					data->item_accel_y = 24;
					return;
				}
			}
	}else{ //inizio gestione non scrigno
		if (data->collided | data->item_accel_y | data->counter == 0){
			if (data->setup){ //inizio setup
				data->setup = 0u;
				switch(data->type){
					case 1: //coin
						SetSpriteAnim(THIS, item_coin, 8u);
					break;
					case 2: //hp
						SetSpriteAnim(THIS, item_hp, 8u);
					break;
					case 3: //up
						SetSpriteAnim(THIS, item_up, 8u);
					break;
					case 6: //wrench
						SetSpriteAnim(THIS, item_wrench, 8u);
					break;
					case 7: //dcoin
						SetSpriteAnim(THIS, item_dcoin, 8u);
						THIS->coll_y = 8;
					break;
				}
			} //fine setup
			
			if(data->item_accel_y < 24) {
				data->item_accel_y += 1;
			}
			data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
			if(!data->tile_i_collision && delta_time != 0 && data->item_accel_y < 24) { //Do another iteration if there is no collision
				data->item_accel_y += 2;
				data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 4);
			}
			
		}
	}//fine gestione item non scrigno
	
	UINT8 scroll_i_tile;
	struct Sprite* iispr;
	SPRITEMANAGER_ITERATE(scroll_i_tile, iispr) {
		if(iispr->type == SpritePlatform) {
			if(CheckCollision(THIS, iispr)) {
				data->item_accel_y = 0;
				struct PlatformInfo* datapl = (struct PlatformInfo*)iispr->custom_data;
				data->vx = datapl->vx;
			}
		}
	}
}

void Destroy_SpriteItem() {
}
