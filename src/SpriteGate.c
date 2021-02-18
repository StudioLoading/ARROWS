#include "Banks/SetBank6.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"


const UINT8 anim_gate[] = {1, 0}; //The first number indicates the number of frames

void Start_SpriteGate() {
	
	SetSpriteAnim(THIS, anim_gate, 8u);	
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 16;
}

void Update_SpriteGate() {
}


void Destroy_SpriteGate() {
}