#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"


const UINT8 anim_puff[] = {2, 0, 1}; //The first number indicates the number of frames

void START() {
	struct PuffInfo* puff_data = (struct PuffInfo*)THIS->custom_data;
	puff_data->puff_counter = 24;
	SetSpriteAnim(THIS, anim_puff, 8u);
	PlayFx(CHANNEL_1, 5, 0x4b, 0xc2, 0x43, 0x68, 0x86);
}

void UPDATE() {
	struct PuffInfo* puff_data = (struct PuffInfo*)THIS->custom_data;
	puff_data->puff_counter--;
	if(puff_data->puff_counter <= 0){
		SpriteManagerRemoveSprite(THIS);
	}	
}

void DESTROY(){
	
}