#include "Banks/SetAutoBank.h"

//#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


extern UINT8 current_level;

const UINT8 anim_gate[] = {2, 0, 1}; //The first number indicates the number of frames

void START() {	
	THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 16;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, anim_gate, 16u);	
}

void UPDATE() {
	
	UINT8 scroll_gate_tile;
	Sprite* gatespr;

	SPRITEMANAGER_ITERATE(scroll_gate_tile, gatespr) {
		if(gatespr->type == SpriteArrow){
			if(CheckCollision(THIS, gatespr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)gatespr->custom_data;
				struct EnemyInfo* gdata = (struct EnemyInfo*)THIS->custom_data;
				if (arrowdata->original_type == gdata->vx){ // uso il campo vx dell' EnemyInfo per capire con che freccia è rompibile.
					SpriteManagerRemoveSprite(THIS);
				}
			}
		}
	}
}


void DESTROY() {
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}