#include "Banks/SetBank6.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


const UINT8 amulet_closed[] = {1, 0}; //The first number indicates the number of frames
const UINT8 amulet_water[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 amulet_earth[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 amulet_blast[] = {2, 0, 3}; //The first number indicates the number of frames
const UINT8 amulet_fire[] = {2, 0, 4};

struct ItemInfo* datak;

void Start_SpriteAmulet() {
	datak = (struct ItemInfo*)THIS->custom_data;
	datak->type = 0;
	datak->setup = 1u;
	datak->counter = -1;
	SetSpriteAnim(THIS, amulet_closed, 8u);
	
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 16;
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;

}

void Update_SpriteAmulet() {
	if(datak->setup){ // !
		/*THIS->coll_x = 0;
		THIS->coll_y = 0;
		THIS->coll_w = 0;
		THIS->coll_h = 0;*/
		switch(datak->type){
			/*case 0:
				SetSpriteAnim(THIS, amulet_normal, 8u);
			break;*/
			case 1:
				SetSpriteAnim(THIS, amulet_earth, 16u);
			break;
			case 2:
				SetSpriteAnim(THIS, amulet_water, 16u);
			break;
			case 3:
				SetSpriteAnim(THIS, amulet_blast, 16u);
			break;
			case 4:
				SetSpriteAnim(THIS, amulet_fire, 16u);
			break;
		}
		datak->setup = 1;
	}else if (datak->counter > 0){
		datak->counter--;
		//TranslateSprite(THIS, 0, 1);
		if (datak->counter==0){
			//SpriteManagerRemoveSprite(THIS);
		}
	}
}

void Destroy_SpriteAmulet() {
}