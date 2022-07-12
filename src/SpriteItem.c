#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "custom_datas.h"

const UINT8 item_hidden[] = {1, 0}; //The first number indicates the number of frames
const UINT8 item_coin[] = {1, 1}; //The first number indicates the number of frames
const UINT8 item_hp[] = {1, 3}; //The first number indicates the number of frames
const UINT8 item_up[] = {1, 2}; //The first number indicates the number of frames
const UINT8 item_scrigno[] = {1, 4}; //The first number indicates the number of frames
const UINT8 item_scrignoaperto[] = {1, 5}; //The first number indicates the number of frames
//const UINT8 item_wrench[] = {1, 6};
const UINT8 item_dcoin[] = {1, 6}; //The first number indicates the number of frames


void START() {
	
	SetSpriteAnim(THIS, item_hidden, 8u);

	struct ItemInfo* data = (struct ItemInfo*)THIS->custom_data;
	data->collided = 0;
	data->setup = 1u;
	data->counter = -1;
	data->item_accel_y = 0;
	data->type = 0;
	data->vx = 0;
	THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 8;
	THIS->lim_x = 200u;
	THIS->lim_y = 200u;
}

void UPDATE() {
	
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
		if (data->collided || data->item_accel_y || data->counter == 0){
			if (data->setup){ //inizio setup
				data->setup = 0u;
				SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
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
					case 7: //dcoin
						SetSpriteAnim(THIS, item_dcoin, 8u);
						THIS->coll_h = 16u;
					break;
				}
			} //fine setup
			
			if(data->item_accel_y < 8) {
				data->item_accel_y += 1;
			}
			data->tile_i_collision = TranslateSprite(THIS, data->vx, data->item_accel_y >> 3);	
			if(data->tile_i_collision != 0 && data->item_accel_y > 0){
				//PlayFx(CHANNEL_1, 60, 0x4b, 0xc2, 0x43, 0x68, 0x86);
				PlayFx(CHANNEL_1, 60, 0x64, 0x81, 0x43, 0x73, 0x86);
				data->item_accel_y = -6;
			}
		}
	}//fine gestione item non scrigno
	
	UINT8 scroll_i_tile;
	Sprite* iispr;
	SPRITEMANAGER_ITERATE(scroll_i_tile, iispr) {
		if(iispr->type == SpritePlatform || iispr->type == SpriteIceplat) {
			if(CheckCollision(THIS, iispr)) {
				data->item_accel_y = 0;
				struct PlatformInfo* datapl = (struct PlatformInfo*)iispr->custom_data;
				data->vx = datapl->vx;
			}
		}
	}
}

void DESTROY() {
}
