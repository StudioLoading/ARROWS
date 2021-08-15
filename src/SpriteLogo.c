#include "Banks/SetBank7.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

const UINT8 logo_0[] = {1, 0}; //The first number indicates the number of frames
const UINT8 logo_1[] = {1, 1}; //The first number indicates the number of frames
const UINT8 logo_2[] = {1, 2}; //The first number indicates the number of frames


void Start_SpriteLogo(){


}

void Update_SpriteLogo() {
	struct LogoInfo* logo_data = (struct LogoInfo*)THIS->custom_data;
	if(logo_data->setup){
		switch(logo_data->frame){
			case 0:
				SetSpriteAnim(THIS, logo_0, 8u);
			break;
			case 1:
				SetSpriteAnim(THIS, logo_1, 8u);
			break;
			case 2:
				SetSpriteAnim(THIS, logo_2, 8u);
			break;
		}
		logo_data->setup = 0;
	}

}

void Destroy_SpriteLogo() {

}
