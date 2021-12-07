#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "CircleMath.h"
#include "custom_datas.h"

//SNAKE
const UINT8 bee_idle[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 bee_walk[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 bee_hit[] = {2, 0, 1}; //The first number indicates the number of frames
const UINT8 bee_dead[] = {1, 1}; //The first number indicates the number of frames

extern void CheckCollisionETile();
extern void ETurn();
extern void EDie();

UINT16 init_x;
UINT16 init_y;

void Start_SpriteBee() {	
	THIS->coll_x = 1;
	THIS->coll_y = 2;
	THIS->coll_w = 4;
	THIS->coll_h = 14;
	THIS->lim_x = THIS->x;
	THIS->lim_y = THIS->y;
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	SetSpriteAnim(THIS, bee_idle, 24u);
	edata->enemy_state = ENEMY_STATE_NORMAL;
	edata->hp = 30;
	edata->enemy_accel_y = 0;
	edata->vx = 0;
	edata->wait = 0u;
	edata->archer_posx = 0u;
}

void Update_SpriteBee() { 
	
	struct EnemyInfo* edata = (struct EnemyInfo*)THIS->custom_data;
	
	UINT8 cos_position = edata->archer_posx + 64u;
	THIS->x = THIS->lim_x + ((sine_wave[cos_position]) >> 3);
	THIS->y = THIS->lim_y + ((sine_wave[edata->archer_posx]) >> 3);
	edata->archer_posx += 3u;
	if(edata->hp < 10u){
		edata->archer_posx += 2u;
	}
	
	if (edata->enemy_state == ENEMY_STATE_DEAD){
		if (edata->wait > 0){
			THIS->y--;
			edata->wait--;
		}else{
			SpriteManagerRemoveSprite(THIS);
		}		
		return;
	}
	
	if (edata->enemy_state == ENEMY_STATE_HIT){
		edata->wait -= 1u;
		if(edata->wait == 0u){
			SetSpriteAnim(THIS, bee_idle, 24u);
			edata->enemy_state = ENEMY_STATE_NORMAL;			
		}
	}
	
	UINT8 scroll_bee_tile;
	struct Sprite* ibeespr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_bee_tile, ibeespr) {
		if(ibeespr->type == SpritePlayer) {
			if(CheckCollision(THIS, ibeespr)) {
				edata->wait = 24u;
			}
		}
		if(ibeespr->type == SpriteArrow) {
			if(CheckCollision(THIS, ibeespr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ibeespr->custom_data;
				edata->wait = 24u;
				SetSpriteAnim(THIS, bee_hit, 24u); 
				edata->hp -= arrowdata->arrowdamage;
				if (THIS->x < ibeespr->x){ //se la freccia arriva dalla destra dell' enemy
					if (SPRITE_GET_VMIRROR(THIS)){ // se sto andando a sinistra, l'ho preso da dietro! turn!
						ETurn();
					}
					edata->tile_e_collision = TranslateSprite(THIS, -2 << delta_time, (edata->enemy_accel_y >> 4));
				}else{ //se la freccia arriva da sinistra dell' enemy
					if (!SPRITE_GET_VMIRROR(THIS)){ // se sto andando a destra, l'ho preso da dietro! turn!
						ETurn();
					}
					edata->tile_e_collision = TranslateSprite(THIS, 2 << delta_time, (edata->enemy_accel_y >> 4));
				}
				SpriteManagerRemoveSprite(ibeespr);
				if (edata->hp <= 0){
					EDie();
				}else{
					edata->enemy_state = ENEMY_STATE_HIT;
				}
			}
		}
	}
	
}

void Destroy_SpriteBee(){
	SpriteManagerAdd(SpritePuff, THIS->x, THIS->y+8u);
}