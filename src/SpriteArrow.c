#include "Banks/SetBank6.h"
#include "main.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

extern INT8 platform_vx;

/*struct Arrows{
	UINT8 ids[5];
    INT8 falen;
};*/

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

struct Sprite * ids[4] = {0,0,0,0};
INT8 falen = 0; //counts in-screen arrows 

void SetupArrow();
void CheckCollisionArrowTile(UINT8 ta);
void FApush();
void FApop();

void Start_SpriteArrow() {
	
	THIS->coll_x = 5;
	THIS->coll_y = 6;
	THIS->coll_w = 3;
	THIS->coll_h = 3;
	THIS->lim_x = 120u;
	THIS->lim_y = 120u;
	
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	data->type = 0;
	data->original_type = 0;
	data->arrowdir = -1;
	//data->counter = 0;

	FApush();
}

void FApush(){
	if (falen <= 4 && falen > 0){
		ids[falen-1] = THIS;
	}else{
		FApop();
		ids[0] = THIS;
	}
	falen++;
}

void FApop(){
	if (falen){
		falen--;
		SpriteManagerRemoveSprite(ids[falen-1]);
	}
	ids[3] = ids[2];
	ids[2] = ids[1];
	ids[1] = ids[0];
}

void Update_SpriteArrow() {
	
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	internal_t = data->type;
	if (internal_t != 0 & data->arrowdir != -1) {
		SetupArrow();
		data->original_type = internal_t;
	}
	UINT8 tile_a_collision = 0u;
	if(SPRITE_GET_VMIRROR(THIS)) {
		THIS->coll_x = 0;
		tile_a_collision = TranslateSprite(THIS, -data->vx << delta_time, data->vy << delta_time);
	} else {
		THIS->coll_x = 5;
		tile_a_collision = TranslateSprite(THIS, data->vx << delta_time, data->vy << delta_time);
	}	
	if(tile_a_collision){
		CheckCollisionArrowTile(tile_a_collision);
	}
	
	UINT8 scroll_a_tile;
	struct Sprite* iaspr;
	SPRITEMANAGER_ITERATE(scroll_a_tile, iaspr) {
		if(iaspr->type == SpriteItem) {
			if(CheckCollision(THIS, iaspr)) {
				struct ItemInfo* item_data = (struct ItemInfo*)iaspr->custom_data;
				if (item_data->collided == 0u){
					SpriteManagerRemove(THIS_IDX);
				}
				item_data->collided = 1u;
			}
		}
		/*if(iaspr->type == SpriteArrow) {
			if(CheckCollision(THIS, iaspr)) {
				struct ArrowInfo* arrow_diasprata = (struct ArrowInfo*)iaspr->custom_data;
				if (arrow_diasprata->type == 6 & data->type != 6){
					SpriteManagerRemove(THIS_IDX);
					SpriteManagerRemoveSprite(iaspr);
				}
			}
		}*/
		if(iaspr->type == SpriteStalagmite){
			if(CheckCollision(THIS, iaspr)) {
				struct EnemyInfo* stala_sprite = (struct EnemyInfo*)iaspr->custom_data;
				if(stala_sprite->enemy_state == STALAG_STATE_DROP){
					CheckCollisionArrowTile(200u);					
				}
			}
		}
	}
	
}

void SetupArrow(){
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	switch(internal_t) {
		case 1: //NORMAL
			data->arrowdamage = 8u;
			switch(data->arrowdir){
				case 1: //orizzontale
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_normal, 18u);
				break;
				case 3: //verticale in su
					data->vy = -1;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_normal_v, 18u);	
				break;
				case 4: //verticale in giu
					data->vy = 2;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_normal_g, 18u);	
				break;
			}
			data->type = 0;
		break;
		case 2: //STONE
			data->arrowdamage = 16u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 1;
					SetSpriteAnim(THIS, arrow_stone, 18u);	
				break;
				case 3:
					data->vy = -1;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_stone_v, 18u);	
				break;
				case 4:
					data->vy = 2;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_stone_g, 18u);
				break;
			}						
			data->type = 0;
		break;
		case 3: // BLAST
			data->arrowdamage =20u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 3;
					SetSpriteAnim(THIS, arrow_blast, 18u);	
				break;
				case 3:
					data->vy = -3;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_blast_v, 18u);	
				break;
				case 4:
					data->vy = 3;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_blast_g, 18u);	
				break;
			}						
			data->type = 0;
		break;
		case 4:// ICE
			data->arrowdamage = 10u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_water, 18u);	
				break;
				case 3:
					data->vy = -2;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_water_v, 18u);	
				break;
				case 4:
					data->vy = 2;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_water_g, 18u);	
				break;
			}						
			data->type = 0;
		break;
		case 5: //FIRE
			data->arrowdamage = 30u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_fire, 18u);	
				break;
				case 3:
					data->vy = -2;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_fire_v, 18u);	
				break;
				case 4:
					data->vy = 2;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_fire_g, 18u);	
				break;
			}						
			data->type = 0;
		break;
		case 6:
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, spine, 18u);	
				break;
			}
			//data->type = 0;
		break;
	}
	//RELATIVE MOVEMENT ON X AXIS!
	if(platform_vx){
		if(platform_vx > 0 && !SPRITE_GET_VMIRROR(THIS)){
			data->vx += platform_vx;
		}else if (platform_vx < 0 && SPRITE_GET_VMIRROR(THIS)){
			data->vx -= platform_vx;
		}		
	}
}

void CheckCollisionArrowTile(UINT8 ta) {	
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	switch(ta) {
		case 11u: //da DX a GIU
			data->arrowdir = 4;
			if(SPRITE_GET_VMIRROR(THIS)){
				THIS->x -= 2;
			}else{
				THIS->x += 2;
			}			
			THIS->y += 4;
		break;
		case 13u: // da DX a SU
			data->arrowdir = 3;
			if(SPRITE_GET_VMIRROR(THIS)){
				THIS->x -= 4;
			}else{
				THIS->x += 4;
			}
		break;
		case 16u://da GIU a DX
			SPRITE_UNSET_VMIRROR(THIS);
			data->arrowdir = 1;
			THIS->x += 4;
			THIS->y -= 4;
		break;
		case 17u: //da GIU a SX
			SPRITE_SET_VMIRROR(THIS);
			data->arrowdir = 1;
			THIS->x -= 4;
			THIS->y -= 4;
		break;
		case 89u: //STONE generator da DX a GIU
			data->arrowdir = 4;
			if(SPRITE_GET_VMIRROR(THIS)){
				THIS->x -= 4;
			}else{
				THIS->x += 4;
			}			
			THIS->y += 4;
			data->original_type = 2; //questo dovrebbe triggerare il Setup al prossimo frame
		break;
		case 90u: //thunder generator da DX a GIU
			data->arrowdir = 4;
			if(SPRITE_GET_VMIRROR(THIS)){
				THIS->x -= 4;
			}else{
				THIS->x += 4;
			}		
			THIS->y += 4;
			data->original_type = 3; //questo dovrebbe triggerare il Setup al prossimo frame
		break;
		case 200u://numero per indicare la goccia che cade da stalattite
			data->original_type = 4; //questo dovrebbe triggerare il Setup al prossimo frame
		break;
		default:
			data->arrowdamage = 100;
			SpriteManagerRemoveSprite(THIS);
			return;
		break;
	}
	data->type = data->original_type;
}

void Destroy_SpriteArrow() {
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	if(data->arrowdamage != 100){
		FApop();
	}else if (falen){
		falen--;
	}
}
