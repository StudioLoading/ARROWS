#include "Banks/SetBank19.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "Dialogs.h"


void Start_SpriteCutarcher(){
    THIS->mt_sprite->dx = 4;
    THIS->mt_sprite->dy = 2;
    THIS->coll_h = 14;
    THIS->coll_w = 6;
   	struct EnemyInfo* cutarcher = (struct EnemyInfo*)THIS->custom_data;
    cutarcher->vx = 0;
    cutarcher->enemy_accel_y = 24u;
}

void Update_SpriteCutarcher(){
   	struct EnemyInfo* cutarcher = (struct EnemyInfo*)THIS->custom_data;
    TranslateSprite(THIS, (cutarcher->vx >> 4) << delta_time, (cutarcher->enemy_accel_y >> 4) << delta_time);
}

void Destroy_SpriteCutarcher(){

}