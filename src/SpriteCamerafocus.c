#include "Banks/SetAutoBank.h"

#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"

const UINT8 camerafocus_normal[] = {1, 0}; //The first number indicates the number of frames

extern UINT8 current_camera_counter;

void START() {
	THIS->mt_sprite->dx = 0;
	THIS->mt_sprite->dy = 0;
	THIS->coll_w = 0;
	THIS->coll_h = 0;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	SetSpriteAnim(THIS, camerafocus_normal, 8u);
}

void UPDATE() {
	
}

void DESTROY() {
}
