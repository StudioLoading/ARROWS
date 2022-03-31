#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

const UINT8 arrowt_normal[] = {1, 0}; //The first number indicates the number of frames

void START() {
	SetSpriteAnim(THIS, arrowt_normal, 4u);	
	THIS->lim_x = 60u;
	THIS->lim_y = 60u;
}

void UPDATE() {
	THIS->x -= 4;
	THIS->y += 2;
}

void DESTROY() {

}
