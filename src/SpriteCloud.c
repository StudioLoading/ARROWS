#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

#include "custom_datas.h"
#include "Dialogs.h"

const UINT8 animcloud_0[] = {1, 0}; //The first number indicates the number of frames
const UINT8 animcloud_1[] = {1, 1}; //The first number indicates the number of frames


void START(){
    THIS->lim_x = 48u;
    THIS->lim_y = 8u;
    SetSpriteAnim(THIS, animcloud_0, 1u);
}

void UPDATE(){

    THIS->x -= 1;

}

void DESTROY(){

}