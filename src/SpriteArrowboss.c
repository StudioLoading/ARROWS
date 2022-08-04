#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "Dialogs.h"

const UINT8 arrowboss_idle[] = {4, 0, 1, 2, 3}; //The first number indicates the number of frames

UINT8 scrollarrowboss_tile;
Sprite* iabspr;

//extern void Hit(INT8 damage) BANKED;


void START(){
    THIS->lim_x = 20u;
    THIS->lim_y = 20u;
    SetSpriteAnim(THIS, arrowboss_idle, 16u);
}

void UPDATE(){
    UINT8 arrowboss_tile_collision = TranslateSprite(THIS, -2 << delta_time, 0);
    if(arrowboss_tile_collision){
	    SpriteManagerRemoveSprite(THIS);
    }
	SPRITEMANAGER_ITERATE(scrollarrowboss_tile, iabspr) {
		if(CheckCollision(THIS, iabspr)) {
            if(iabspr->type == SpriteArrowmother){
                SpriteManagerRemoveSprite(THIS);
            }
            if(iabspr->type == SpritePlayer){
                //SpriteManagerRemoveSprite(THIS);
                //Hit(1);
            }
            if(iabspr->type != SpriteBosseagle && iabspr->type != SpriteCuteagle && iabspr->type != SpriteArrowboss){
			    SpriteManagerRemoveSprite(THIS);
            }
        }
    }
}

void DESTROY(){
    SpriteManagerAdd(SpritePuff, THIS->x, THIS->y - 4u);
}