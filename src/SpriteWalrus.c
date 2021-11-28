#include "Banks/SetBank14.h"

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"

//WALRUS
/*
const UINT8 walrus_invisible[] = {1, 4}; //The first number indicates the number of frames
const UINT8 walrus_spin[] = {3, 2, 5, 4}; //The first number indicates the number of frames

*/
const UINT8 walrus_dead[] = {1, 3}; //The first number indicates the number of frames
const UINT8 walrus_normal[] = {1, 3}; //The first number indicates the number of frames
const UINT8 walrus_hidden[] = {1, 2}; //The first number indicates the number of frames
const UINT8 walrus_jump_up[] = {1, 0}; //The first number indicates the number of frames
const UINT8 walrus_jump_down[] = {1, 1}; //The first number indicates the number of frames
const UINT8 walrus_hit_up[] = {2, 0, 2}; //The first number indicates the number of frames
const UINT8 walrus_hit_down[] = {2, 1, 2}; //The first number indicates the number of frames

UINT8 tile_wal_collision = 0u;

struct EnemyInfo* walrus_data ;
struct Sprite* walrus_spin;
extern struct EnemyInfo* walrusspin_data;
extern struct ArcherInfo* archer_data;

void EnableCollision(INT8 e);

void Start_SpriteWalrus() {
	walrus_data = (struct EnemyInfo*)THIS->custom_data;
	THIS->coll_x = 2;
	THIS->coll_y = 0;
	THIS->coll_w = 12;
	THIS->coll_h = 32;
	THIS->lim_x = 255u;
	THIS->lim_y = 255u;
	walrus_data->enemy_accel_y = 24;
	walrus_data->vx = -1;
	walrus_data->wait = 60u;
	walrus_data->hp = 80;
	walrus_data->enemy_state = ENEMY_STATE_NORMAL;
	SPRITE_SET_VMIRROR(THIS);
	SetSpriteAnim(THIS, walrus_normal, 4u);
	walrus_spin = SpriteManagerAdd(SpriteWalrusspin, THIS->x, THIS->y - 24u);//(THIS->y + 50u));
}

void Update_SpriteWalrus() {
	
	if(walrus_data->enemy_state == WALRUS_STATE_JUMP_DOWN || walrus_data->enemy_state == WALRUS_STATE_JUMP_UP){
		if(THIS->x < (UINT16) 12u << 3){
			THIS->x = (UINT16) 12u << 3;
			walrus_data->vx = 1;
		}
		if(THIS->x > (UINT16) 29u << 3){
			THIS->x = (UINT16) 29u << 3;
			walrus_data->vx = -1;
		}	
	}
	walrus_data->wait -= 1u;
	walrus_spin->x = THIS->x;
	if(walrus_data->enemy_state == WALRUS_STATE_SWIMMING){
		walrus_spin->y = THIS->y + 16u;
	}else{
		walrus_spin->y = THIS->y;
	}
	
	if(walrus_data->enemy_state == ENEMY_STATE_DEAD){
		if(!SPRITE_GET_VMIRROR(THIS)){
			SPRITE_SET_VMIRROR(THIS);
		}
	}	
	
	if(walrus_data->enemy_state == ENEMY_STATE_NORMAL){
		if(walrus_data->wait == 0u){
			walrus_data->wait = 20 + (walrus_data->hp >> 2); //to change the height of the up jumping before spinning in the air
			//walrus_data->vx = -1;
			SetSpriteAnim(THIS, walrus_jump_up, 4u);
			walrus_data->enemy_state = WALRUS_STATE_JUMP_UP;
			walrusspin_data->enemy_state = WALRUS_STATE_JUMP_UP;			
			return;
		}
	}
	
	if(walrus_data->enemy_state == WALRUS_STATE_JUMP_UP){
		tile_wal_collision = TranslateSprite(THIS, 0, -1 << delta_time);// walrus_data->vx << delta_time
		if(tile_wal_collision){
			switch(tile_wal_collision){
				case 26:
				case 64:
					SetSpriteAnim(THIS, walrus_hidden, 4u);
					walrus_data->enemy_state = WALRUS_STATE_SWIMMING;			
				break;
				default:
					THIS->y--;
				break;
			}
		}	
		if(walrus_data->wait == 0){
			walrus_data->wait = 40;
			SetSpriteAnim(THIS, walrus_hidden, 4u);
			EnableCollision(0);
			walrus_data->enemy_state = WALRUS_STATE_SPIN;
			return;
		}
		
	}
	
	if(walrus_data->enemy_state == WALRUS_STATE_SPIN){		
		if(walrus_data->wait == 0){
			SetSpriteAnim(THIS, walrus_jump_down, 4u);			
			THIS->coll_y = 28;
			THIS->coll_h = 4;
			EnableCollision(1);
			walrus_data->vx *= -1;
			walrus_data->enemy_state = WALRUS_STATE_JUMP_DOWN;
		}		
	}
	
	if(walrus_data->enemy_state == WALRUS_STATE_JUMP_DOWN){
		tile_wal_collision = TranslateSprite(THIS, walrus_data->vx, 2 << delta_time);			
		if(tile_wal_collision){
			switch(tile_wal_collision){
				case 26:
				case 64:
					SetSpriteAnim(THIS, walrus_hidden, 4u);					
					walrus_data->wait = 255u - (walrus_data->hp << 1 - archer_data->hp << 1);
					EnableCollision(0);
					walrus_data->enemy_state = WALRUS_STATE_SWIMMING;			
				break;
				default:
					THIS->y ++;
				break;
			}
		}
	}
	
	if(walrus_data->enemy_state == WALRUS_STATE_SWIMMING){
		if(walrus_data->wait != 0u){
			tile_wal_collision = TranslateSprite(THIS, walrus_data->vx << delta_time, 0 << delta_time);				
			switch(tile_wal_collision){
				case 35u:
				case 36u:
				case 37u:
				case 43u:
				case 44u:
					walrus_data->vx = -1;
				break;
				case 62u:
					walrus_data->vx = 1;
				break;
				case 26u:
				case 64u:
					THIS->x += walrus_data->vx;
				break;
			}
		}else{ //UP!
			walrus_data->wait = 50u + ((UINT8) walrus_data->hp >> 2);
			SetSpriteAnim(THIS, walrus_jump_up, 4u);
			EnableCollision(0);
			walrus_data->enemy_state = WALRUS_STATE_JUMP_UP;
		}
	}
	
	if(walrus_data->enemy_state == WALRUS_STATE_JUMP_UP){
		walrus_data->wait -= 1u;
		UINT8 tile_wal_collision = TranslateSprite(THIS, 0, -1 << delta_time);
		if(tile_wal_collision){					
			switch(tile_wal_collision){
				case 35u:
				case 62u:
				case 26u:
				case 64u:
					THIS->y -= 1u;
				break;
			}
		}
		if(walrus_data->wait == 0u){
			walrus_data->wait = 200u;
			SetSpriteAnim(THIS, walrus_hidden, 4u);
			EnableCollision(1);
			walrus_data->enemy_state = WALRUS_STATE_SPIN;
		}
	}
	
	/*
	
	WALRUS_STATE_WALK,
	WALRUS_STATE_SPIN,
	WALRUS_STATE_JUMP_UP,
	WALRUS_STATE_JUMP_DOWN,
	WALRUS_STATE_SWIMMING,
	WALRUS_STATE_SWIMMING_UP,
	*/

	UINT8 scroll_w_tile;
	struct Sprite* iwspr;
	
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_w_tile, iwspr) {	
		if(iwspr->type == SpriteArrow) {
			if(CheckCollision(THIS, iwspr)){
				if (walrus_data->enemy_state == WALRUS_STATE_JUMP_DOWN || walrus_data->enemy_state == WALRUS_STATE_JUMP_UP
				 || walrus_data->enemy_state == WALRUS_STATE_SWIMMING) {
					struct ArrowInfo* arrowdata = (struct ArrowInfo*)iwspr->custom_data;
					switch(walrus_data->enemy_state){
						case WALRUS_STATE_JUMP_UP:
							SetSpriteAnim(THIS, walrus_hit_up, 24u);
						break;
						case WALRUS_STATE_JUMP_DOWN:
							SetSpriteAnim(THIS, walrus_hit_down, 24u);
						break;						
					} 
					if(arrowdata->arrowdamage){
						INT8 new_boss_hp = walrus_data->hp - arrowdata->arrowdamage;
						if (new_boss_hp <= 0){
							walrus_data->hp = 0;
							SetSpriteAnim(THIS, walrus_dead, 16u);
							walrus_data->enemy_state = ENEMY_STATE_DEAD;
							THIS->x = (UINT16) 21u << 3;
							THIS->y = (UINT16) 14u << 3;
						}
						walrus_data->hp = new_boss_hp;
					}
				}					
				SpriteManagerRemoveSprite(iwspr);
			}  
		}
	}
	
}

void EnableCollision(INT8 e){
	if(e != 0){		
		THIS->coll_x = 2;
		THIS->coll_y = 6;
		THIS->coll_w = 12;
		THIS->coll_h = 20;
	}else{
		THIS->coll_x = 0;
		THIS->coll_y = 15;
		THIS->coll_w = 8;
		THIS->coll_h = 1;
	}
}

void Destroy_SpriteWalrus() {
}
