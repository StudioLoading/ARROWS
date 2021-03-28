#include "Banks/SetBank6.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


extern UINT8 current_level;

const UINT8 anim_gate[] = {2, 0, 1}; //The first number indicates the number of frames

void Start_SpriteGate() {
	
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 16;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, anim_gate, 16u);
	struct EnemyInfo* gatedata = (struct EnemyInfo*)THIS->custom_data;
	
}

void Update_SpriteGate() {
	
	UINT8 scroll_gate_tile;
	struct Sprite* gatespr;

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


void Destroy_SpriteGate() {
}