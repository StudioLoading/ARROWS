#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"

#include "custom_datas.h"
#include "Dialogs.h"
#include "sgb_palette.h"


extern UINT8 diag_found;
extern INT8 load_next_d;
extern UINT16 drop_player_x;
extern UINT16 drop_player_y;
extern Sprite* archer_player;
extern struct ArcherInfo* archer_data;
extern ARCHER_STATE archer_state;
extern INT8 show_diag;

//CAGED BOSSES
const UINT8 wolf_caged[] = {1, 0}; //The first number indicates the number of frames
const UINT8 ibex_caged[] = {1, 1}; //The first number indicates the number of frames
const UINT8 bear_caged[] = {1, 2}; //The first number indicates the number of frames
const UINT8 boss_idle[] = {4, 3,3,3,4}; //The first number indicates the number of frames

UINT8 final_quiver = 0b00011111;

void START() {    
	THIS->lim_x = 255u;
	THIS->lim_y = 244u;
	struct CagedbossInfo* caged_data = (struct CagedbossInfo*)THIS->custom_data;
	caged_data->wait = 0u;
}

void UPDATE() { 
	struct CagedbossInfo* caged_data = (struct CagedbossInfo*)THIS->custom_data;
    if(caged_data->setup == 1){
        switch(caged_data->state){
            case WOLF_CAGED:
                SetSpriteAnim(THIS, wolf_caged, 8u);
            break;
            case IBEX_CAGED:
                SetSpriteAnim(THIS, ibex_caged, 8u);
            break;
            case BEAR_CAGED:
                SetSpriteAnim(THIS, bear_caged, 8u);
            break;
            case CAGEDBOSS_IDLE:
                SetSpriteAnim(THIS, boss_idle, 12u);
            break;
        }
        caged_data->setup = 0;
    }
    
	UINT8 scroll_caged_tile;
	Sprite* icbspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_caged_tile, icbspr) {
		if(CheckCollision(THIS, icbspr)) {
            drop_player_x = archer_player->x >> 3;
            drop_player_y = archer_player->y >> 3;
			switch(icbspr->type){
				case SpriteMother:
					caged_data->setup = 0;
                    caged_data->hit = 0;
                    diag_found = Build_Next_Dialog_Banked(THIS);
                    load_next_d = 4;
                    switch(caged_data->state){
                        case WOLF_CAGED:
                            final_quiver |= 0b00000010;
                        break;
                        case IBEX_CAGED:
                            final_quiver |= 0b00000100;
                        break;
                        case BEAR_CAGED:
                            final_quiver |= 0b00001000;
                        break;
                    }
                    SetState(StateDiag);
				break;
				case SpriteArrow:
					caged_data->setup = 0;
                    caged_data->hit = 1;
                    diag_found = Build_Next_Dialog_Banked(THIS);
                    archer_state = STATE_DIAG;
                    show_diag = 1;
                    //load_next_d = 4;
                    //SetState(StateDiag);
                break;
            }
        }
    }
}

void DESTROY(){

}