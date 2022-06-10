#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Sound.h"
#include "Music.h"
#include "Scroll.h"

#include "custom_datas.h"
#include "Dialogs.h"
#include "sgb_palette.h"

void START(){
   	struct EnemyInfo* cutarcher = (struct EnemyInfo*)THIS->custom_data;
    cutarcher->vx = 0;
    cutarcher->enemy_accel_y = 24u;
}

void UPDATE(){
   	struct EnemyInfo* cutarcher = (struct EnemyInfo*)THIS->custom_data;
    TranslateSprite(THIS, (cutarcher->vx >> 4) << delta_time, (cutarcher->enemy_accel_y >> 4) << delta_time);
}

void DESTROY(){

}