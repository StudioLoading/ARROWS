#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"


//FALCE
const UINT8 falcebase_sliding[] = {1, 0}; //The first number indicates the number of frames

void START() {
	THIS->lim_x = 80u;
	THIS->lim_y = 60u;
	SetSpriteAnim(THIS, falcebase_sliding, 8u);	
	struct FalcebaseInfo* falcebasedata = (struct FalcebaseInfo*)THIS->custom_data;
	falcebasedata->enemy_state = ENEMY_STATE_WAIT;
}

void UPDATE() {	
	struct FalcebaseInfo* falcebasedata = (struct FalcebaseInfo*)THIS->custom_data;
	Sprite* lama = falcebasedata->falcelama;
	switch(falcebasedata->enemy_state){
		case ENEMY_STATE_SLIDING:
			THIS->y = lama->y + 16u;
		break;
	}
}

void DESTROY(){
	
}