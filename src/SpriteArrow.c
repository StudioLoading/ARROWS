#include "Banks/SetBank1.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"

const UINT8 arrow_normal[] = {1, 0}; //The first number indicates the number of frames
const UINT8 arrow_water[] = {1, 1};
const UINT8 arrow_stone[] = {1, 2};
const UINT8 arrow_blast[] = {1, 3};
const UINT8 arrow_fire[] = {1, 4};
const UINT8 arrow_normal_d[] = {1, 5};
const UINT8 arrow_water_d[] = {1, 6};
const UINT8 arrow_stone_d[] = {1, 7};
const UINT8 arrow_blast_d[] = {1, 8}; 
const UINT8 arrow_fire_d[] = {1, 9}; 
const UINT8 arrow_normal_v[] = {1, 10};
const UINT8 arrow_water_v[] = {1, 11};
const UINT8 arrow_stone_v[] = {1, 12};
const UINT8 arrow_blast_v[] = {1, 13};
const UINT8 arrow_fire_v[] = {1, 14};
const UINT8 arrow_normal_g[] = {1, 15};
const UINT8 arrow_water_g[] = {1, 16};
const UINT8 arrow_stone_g[] = {1, 17};
const UINT8 arrow_blast_g[] = {1, 18};
const UINT8 arrow_fire_g[] = {1, 19};
const UINT8 spine[] = {1, 20};

UINT8 tile_a_collision;
UINT8 internal_t; // 1 normal 2 water 3 stone 4 blast 5 fire

void SetupArrow();
void CheckCollisionArrowTile();
void RedirectArrow();

void Start_SpriteArrow() {
	
	THIS->coll_x = 5;
	THIS->coll_y = 6;
	THIS->coll_w = 3;
	THIS->coll_h = 3;
	
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	data->type = 0;
	data->original_type = 0;
	data->arrowdir = -1;
}

void Update_SpriteArrow() {
	UINT8 scroll_a_tile;
	struct Sprite* iaspr;
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	internal_t = data->type;
	if (internal_t != 0 & data->arrowdir != -1) {
		SetupArrow();
		data->original_type = internal_t;
	}
	if(SPRITE_GET_VMIRROR(THIS)) {
		THIS->coll_x = 0;
		tile_a_collision = TranslateSprite(THIS, -data->vx << delta_time, data->vy << delta_time);
	} else {
		THIS->coll_x = 5;
		tile_a_collision = TranslateSprite(THIS, data->vx << delta_time, data->vy << delta_time);
	}
	if(tile_a_collision){
		CheckCollisionArrowTile();
	}
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
		if(iaspr->type == SpriteArrow) {
			if(CheckCollision(THIS, iaspr)) {
				struct ArrowInfo* arrow_diasprata = (struct ArrowInfo*)iaspr->custom_data;
				if (arrow_diasprata->type == 6 & data->type != 6){
					SpriteManagerRemove(THIS_IDX);
					SpriteManagerRemoveSprite(iaspr);
				}
			}
		}
	}
	
}

void SetupArrow(){
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	switch(internal_t) {
		case 1: //NORMAL
			data->arrowdamage = 7u;
			switch(data->arrowdir){
				case 1: //orizzontale
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_normal, 18u);	
				break;
				case 2: //diagonale
					data->vy = -1;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_normal_d, 18u);	
				break;
				case 3: //verticale in su
					data->vy = -2;
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
		case 2: // WATER
			data->arrowdamage = 10u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_water, 18u);	
				break;
				case 2:
					data->vy = -1;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_water_d, 18u);	
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
		case 3: //STONE
			data->arrowdamage = 15u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 1;
					SetSpriteAnim(THIS, arrow_stone, 18u);	
				break;
				case 2:
					data->vy = -1;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_stone_d, 18u);	
				break;
				case 3:
					data->vy = -1;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_stone_v, 18u);	
				break;
				case 4:
					data->vy = 1;
					data->vx = 0;
					SetSpriteAnim(THIS, arrow_stone_g, 18u);
				break;
			}						
			data->type = 0;
		break;
		case 4:// BLAST
			data->arrowdamage = 0u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 3;
					SetSpriteAnim(THIS, arrow_blast, 18u);	
				break;
				case 2:
					data->vy = -2;
					data->vx = 3;
					SetSpriteAnim(THIS, arrow_blast_d, 18u);	
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
		case 5: //FIRE
			data->arrowdamage = 30u;
			switch(data->arrowdir){
				case 1:
					data->vy = 0;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_fire, 18u);	
				break;
				case 2:
					data->vy = -1;
					data->vx = 2;
					SetSpriteAnim(THIS, arrow_fire_d, 18u);	
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
}

void CheckCollisionArrowTile() {	
	if (tile_a_collision < 18u & tile_a_collision > 9u){
		RedirectArrow();
	}else{
		SpriteManagerRemove(THIS_IDX);
	}
}

void RedirectArrow(){
	struct ArrowInfo* data = (struct ArrowInfo*)THIS->custom_data;
	switch(tile_a_collision) {
		case 10u: //da SX a GIU
			data->arrowdir = 4;
			THIS->x += 4;
			THIS->y += 4;
		break;
		case 11u: //da DX a GIU
			data->arrowdir = 4;
			THIS->x -= 2;
			THIS->y += 4;
		break;
		case 12u: //da SX a SU
			data->arrowdir = 3;
			THIS->x += 4;
		break;
		case 13u: // da DX a SU
			data->arrowdir = 3;
			THIS->x -= 4;
		break;
		case 14u: //da SU a SX
			SPRITE_SET_VMIRROR(THIS);
			data->arrowdir = 1;
			THIS->x -= 4;
		break;
		case 15u: //da SU a DX
			SPRITE_UNSET_VMIRROR(THIS);
			data->arrowdir = 1;
			THIS->x += 4;
			THIS->y += 6;
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
	}
	data->type = data->original_type;
	}

void Destroy_SpriteArrow() {
}
