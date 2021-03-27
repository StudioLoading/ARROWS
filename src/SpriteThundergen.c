#include "Banks/SetBank9.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

const UINT8 gen_idle[] = {1, 0};

void Start_SpriteThundergen() {
	THIS->coll_x = 2;
	THIS->coll_y = 0;
	THIS->coll_w = 12;
	THIS->coll_h = 12;
	SetSpriteAnim(THIS, gen_idle, 4u);
}

void Update_SpriteThundergen() {
	
	
	UINT8 scroll_itg_tile;
	struct Sprite* itgspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_itg_tile, itgspr) {
		if(itgspr->type == SpriteArrow) {
			if(CheckCollision(THIS, itgspr)){
				SpriteManagerRemoveSprite(itgspr);
				struct Sprite* tharrow_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
				/*NR50_REG = 0x22; //Max volume = 0x77
				PlayFx(CHANNEL_4, 3, 0x0C, 0xB1, 0x00, 0xC0);*/
				tharrow_sprite->flags = THIS->flags;
				tharrow_sprite->x = THIS->x;
				tharrow_sprite->y = THIS->y;
				struct ArrowInfo* arrow_data = (struct ArrowInfo*)tharrow_sprite->custom_data;
				arrow_data->type = 4;
				arrow_data->arrowdir = 4;
				tharrow_sprite->y += 8;
			}
		}
	}
}


void Destroy_SpriteThundergen() {
}
