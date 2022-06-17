#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


const UINT8 amulet_closed[] = {1, 2}; //The first number indicates the number of frames
const UINT8 amulet_water[] = {2, 2, 1}; //The first number indicates the number of frames
const UINT8 amulet_water_const[] = {1, 1}; //The first number indicates the number of frames
const UINT8 amulet_earth[] = {2, 2, 0}; //The first number indicates the number of frames
const UINT8 amulet_earth_const[] = {1, 0}; //The first number indicates the number of frames
const UINT8 amulet_blast[] = {2, 2, 3}; //The first number indicates the number of frames
const UINT8 amulet_blast_const[] = {1, 3}; //The first number indicates the number of frames
const UINT8 amulet_fire[] = {2, 2, 4};
const UINT8 amulet_fire_const[] = {1, 4};

struct AmuletInfo* data_amulet;

void START() {
	data_amulet = (struct AmuletInfo*)THIS->custom_data;
	data_amulet->type = 0;
	data_amulet->setup = 1u;
	data_amulet->counter = -1;
	data_amulet->picked = 0;
	THIS->lim_x = 255;
	THIS->lim_y = 255;
}

void UPDATE() {
	if(data_amulet->setup == 0u){ 
		switch(data_amulet->type){
			case 1:
				SetSpriteAnim(THIS, amulet_earth, 24u);
			break;
			case 2:
				SetSpriteAnim(THIS, amulet_water, 24u);
			break;
			case 3:
				SetSpriteAnim(THIS, amulet_blast, 24u);
			break;
			case 4:
				SetSpriteAnim(THIS, amulet_fire, 8u);
			break;
		}
		data_amulet->setup = 1u;
	}
	if(data_amulet->picked == 1){
		switch(data_amulet->type){
			case 1:
				SetSpriteAnim(THIS, amulet_earth_const, 4u);
			break;
			case 2:
				SetSpriteAnim(THIS, amulet_water_const, 4u);
			break;
			case 3:
				SetSpriteAnim(THIS, amulet_blast_const, 4u);
			break;
			case 4:
				SetSpriteAnim(THIS, amulet_fire_const, 4u);
			break;
		}
		data_amulet->picked = 2;
	}
}

void DESTROY() {
}