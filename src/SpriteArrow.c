#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "custom_datas.h"

extern INT8 platform_vx;

const UINT8 arrow_normal[] = {1, 0}; //The first number indicates the number of frames
const UINT8 arrow_water[] = {1, 1};
const UINT8 arrow_stone[] = {1, 2};
const UINT8 arrow_blast[] = {1, 3};
const UINT8 arrow_fire[] = {1, 4};
const UINT8 arrow_normal_v[] = {1, 5};
const UINT8 arrow_water_v[] = {1, 6};
const UINT8 arrow_stone_v[] = {1, 7};
const UINT8 arrow_blast_v[] = {1, 8}; 
const UINT8 arrow_fire_v[] = {1, 9}; 
const UINT8 arrow_normal_g[] = {1, 10};
const UINT8 arrow_water_g[] = {1, 11};
const UINT8 arrow_stone_g[] = {1, 12};
const UINT8 arrow_blast_g[] = {1, 13};
const UINT8 arrow_fire_g[] = {1, 14};
const UINT8 spine[] = {1, 15};
UINT8 internal_t; // 1 normal 2 water 3 stone 4 blast 5 fire

void SetupArrow();
void CheckCollisionArrowTile(UINT8 ta);

void START() {
	THIS->lim_x = 24u;
	THIS->lim_y = 24u;
	
	struct ArrowInfo* arrow_data = (struct ArrowInfo*)THIS->custom_data;
	arrow_data->type = 0;
	arrow_data->original_type = 0;
	arrow_data->arrowdir = -1;
	arrow_data->play_sound = 0;
}

void UPDATE() {
	
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	internal_t = data->type;
	if (internal_t != 0 & data->arrowdir != -1) {
		SetupArrow();
		data->original_type = internal_t;
	}
	UINT8 tile_a_collision = 0u;
	if(THIS->mirror == V_MIRROR) {
		THIS->mt_sprite->dx = 0;
		tile_a_collision = TranslateSprite(THIS, -data->vx << delta_time, data->vy << delta_time);
	} else {
		THIS->mt_sprite->dx = 5;
		tile_a_collision = TranslateSprite(THIS, data->vx << delta_time, data->vy << delta_time);
	}	
	if(tile_a_collision){
		CheckCollisionArrowTile(tile_a_collision);
	}
	
	UINT8 scroll_a_tile;
	Sprite* iaspr;
	struct EnemyInfo* stala_sprite;
	struct ItemInfo* item_data;
	SPRITEMANAGER_ITERATE(scroll_a_tile, iaspr) {
		if(CheckCollision(THIS, iaspr)) {
			switch(iaspr->type){
				case SpriteItem:
					item_data = (struct ItemInfo*)iaspr->custom_data;
					if (item_data->collided == 0u){
						SpriteManagerRemove(THIS_IDX);
					}
					item_data->collided = 1u;
				break;
				case SpriteStalagmite:
					if(CheckCollision(THIS, iaspr)) {
						stala_sprite = (struct EnemyInfo*)iaspr->custom_data;
						if(stala_sprite->enemy_state == STALAG_STATE_DROP){
							CheckCollisionArrowTile(200u);					
						}
					}
				break;
				case SpriteAxe:
					SpriteManagerRemove(THIS_IDX);
				break;
			}
		}
	}
	
}

void SetupArrow(){
	struct ArrowInfo* arrow_data = (struct ArrowInfo*)THIS->custom_data;
	switch(internal_t) {
		case 1: //NORMAL
			arrow_data->arrowdamage = 8u;
			switch(arrow_data->arrowdir){
				case 1: //orizzontale
					arrow_data->vy = 0;
					arrow_data->vx = 2;
					SetSpriteAnim(THIS, arrow_normal, 18u);
				break;
				case 3: //verticale in su
					arrow_data->vy = -1;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_normal_v, 18u);	
				break;
				case 4: //verticale in giu
					arrow_data->vy = 2;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_normal_g, 18u);	
				break;
			}
			arrow_data->type = 0;
		break;
		case 2: //STONE
			arrow_data->arrowdamage = 16u;
			switch(arrow_data->arrowdir){
				case 1:
					arrow_data->vy = 0;
					arrow_data->vx = 1;
					SetSpriteAnim(THIS, arrow_stone, 18u);	
				break;
				case 3:
					arrow_data->vy = -1;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_stone_v, 18u);	
				break;
				case 4:
					arrow_data->vy = 2;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_stone_g, 18u);
				break;
			}						
			arrow_data->type = 0;
		break;
		case 3: // BLAST
			arrow_data->arrowdamage =20u;
			switch(arrow_data->arrowdir){
				case 1:
					arrow_data->vy = 0;
					arrow_data->vx = 3;
					SetSpriteAnim(THIS, arrow_blast, 18u);	
				break;
				case 3:
					arrow_data->vy = -3;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_blast_v, 18u);	
				break;
				case 4:
					arrow_data->vy = 3;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_blast_g, 18u);	
				break;
			}
			arrow_data->type = 0;
		break;
		case 4:// ICE
			arrow_data->arrowdamage = 10u;
			switch(arrow_data->arrowdir){
				case 1:
					arrow_data->vy = 0;
					arrow_data->vx = 2;
					SetSpriteAnim(THIS, arrow_water, 18u);	
				break;
				case 3:
					arrow_data->vy = -2;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_water_v, 18u);	
				break;
				case 4:
					arrow_data->vy = 2;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_water_g, 18u);	
				break;
			}						
			arrow_data->type = 0;
		break;
		case 5: //FIRE
			arrow_data->arrowdamage = 30u;
			switch(arrow_data->arrowdir){
				case 1:
					arrow_data->vy = 0;
					arrow_data->vx = 2;
					SetSpriteAnim(THIS, arrow_fire, 18u);	
				break;
				case 3:
					arrow_data->vy = -2;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_fire_v, 18u);	
				break;
				case 4:
					arrow_data->vy = 2;
					arrow_data->vx = 0;
					SetSpriteAnim(THIS, arrow_fire_g, 18u);	
				break;
			}						
			arrow_data->type = 0;
		break;
		case 6:
			switch(arrow_data->arrowdir){
				case 1:
					arrow_data->vy = 0;
					arrow_data->vx = 2;
					SetSpriteAnim(THIS, spine, 18u);	
				break;
			}
			//data->type = 0;
		break;
	}
	//RELATIVE MOVEMENT ON X AXIS!
	if(platform_vx){
		if(platform_vx > 0 && THIS->mirror != V_MIRROR){
			arrow_data->vx += platform_vx;
		}else if (platform_vx < 0 && THIS->mirror == V_MIRROR){
			arrow_data->vx -= platform_vx;
		}		
	}
}

void CheckCollisionArrowTile(UINT8 ta) {
	struct ArrowInfo* arrow_data = (struct ArrowInfo*)THIS->custom_data;
	arrow_data->play_sound = 1;
	switch(ta) {
		case 11u: // GIU
			arrow_data->arrowdir = 4;
			if(THIS->mirror == V_MIRROR){
				THIS->x -= 2;
			}else{
				THIS->x += 2;
			}			
			THIS->y += 4;
		break;
		case 13u: // a SU
			arrow_data->arrowdir = 3;
			if(THIS->mirror == V_MIRROR){
				THIS->x -= 4;
			}else{
				THIS->x += 4;
			}
		break;
		case 16u:// a DX
			THIS->mirror = NO_MIRROR; //SPRITE_UNSET_VMIRROR(THIS);
			arrow_data->arrowdir = 1;
			THIS->x += 4;
			THIS->y -= 4;
		break;
		case 17u: //da GIU a SX
			THIS->mirror = V_MIRROR; //SPRITE_SET_VMIRROR(THIS);
			arrow_data->arrowdir = 1;
			THIS->x -= 4;
			THIS->y -= 4;
		break;
		case 89u: //STONE generator da DX a GIU
			arrow_data->arrowdir = 4;
			if(THIS->mirror == V_MIRROR){
				THIS->x -= 4;
			}else{
				THIS->x += 4;
			}			
			THIS->y += 4;
			arrow_data->original_type = 2; //questo dovrebbe triggerare il Setup al prossimo frame
		break;
		case 90u: //thunder generator da DX a GIU
			arrow_data->arrowdir = 4;
			if(THIS->mirror == V_MIRROR){
				THIS->x -= 4;
			}else{
				THIS->x += 4;
			}		
			THIS->y += 4;
			arrow_data->original_type = 3; //questo dovrebbe triggerare il Setup al prossimo frame
		break;
		case 200u://numero per indicare la goccia che cade da stalattite
			arrow_data->original_type = 4; //questo dovrebbe triggerare il Setup al prossimo frame
		break;
		default:
			arrow_data->arrowdamage = 100;
			arrow_data->play_sound = 0;
			SpriteManagerRemove(THIS_IDX);
			return;
		break;
	}
	arrow_data->type = arrow_data->original_type;
	if(arrow_data->play_sound == 1){
		PlayFx(CHANNEL_1, 50, 0x2e, 0x81, 0xc2, 0x73, 0x86);
	}
}

void DESTROY() {
}
