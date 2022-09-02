#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Keys.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Music.h"

#include "custom_datas.h"

#define CURSOR_UP_Y     5
#define CURSOR_DOWN_Y   8

const UINT8 anim_cursor_normal[] = {1, 1}; //The first number indicates the number of frames
const UINT8 anim_cursor_blink[] = {2, 0, 1}; //The first number indicates the number of frames

UINT8 cursor_move_cmd = 0u;
UINT8 cursor_moving = 0u;
INT8 cursor_vy = 0;

void START(){
    SetSpriteAnim(THIS, anim_cursor_normal, 4u);
}

void UPDATE(){

    if(KEY_TICKED(J_SELECT)){
        cursor_move_cmd = 1u;
        cursor_moving = 1u;
    }
    if(cursor_move_cmd == 1u){
        cursor_move_cmd = 0u;
        if(THIS->y == ((UINT16) CURSOR_UP_Y << 3 )){
            cursor_vy = 1;
        }
        if(THIS->y == ((UINT16) CURSOR_DOWN_Y << 3)){
            cursor_vy = -1;
        }
        cursor_moving = 1u;
    }
    if(cursor_moving == 1u){
        TranslateSprite(THIS, 0 << delta_time, cursor_vy << delta_time);
        if(cursor_vy == -1){ // going up
            if(THIS->y == ((UINT16) CURSOR_UP_Y << 3)){
                cursor_vy = 0;
                cursor_moving = 0u;
            }
        }else if(cursor_vy == 1){ // going down
            if(THIS->y == ((UINT16) CURSOR_DOWN_Y << 3)){
                cursor_vy = 0;
                cursor_moving = 0u;
            }
        }
    }
}

void DESTROY(){

}