#include "Banks/SetBank2.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"

const UINT8 camerafocus_normal[] = {1, 0}; //The first number indicates the number of frames

void Start_SpriteCamerafocus() {
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 0;
	THIS->coll_h = 0;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, camerafocus_normal, 8u);
}

void Update_SpriteCamerafocus() {
	
}

void Destroy_SpriteCamerafocus() {
}
