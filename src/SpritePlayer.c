#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Sound.h"
#include "Music.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "Dialogs.h"

extern UINT8 amulet;
extern INT8 load_next;
extern INT8 load_next_s;
extern INT8 load_next_d;
extern INT8 load_next_b;
extern INT8 load_next_gameover;
extern UINT8 current_level;
extern UINT8 current_map;
extern UINT8 current_level_b;
extern INT8 show_diag;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern UINT16 drop_player_x;
extern UINT16 drop_player_y;
extern INT8 level_tool;
extern INT8 archer_tool;
extern INT8 update_hud;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

#define MAX_HIT_COOLDOWN 24
#define MAX_DIAG_COOLDOWN 24

//const UINT8 anim_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_idle[] = {4, 12, 13, 14, 13};
const UINT8 anim_jump[] = {1, 11};
const UINT8 anim_jump_up[] = {1, 6};
const UINT8 anim_dead[] = {1, 9};
const UINT8 anim_walk[] = {4, 7, 4, 6, 5, 4};
const UINT8 anim_shield[] = {1, 3};
const UINT8 anim_hit[] = {2, 8, 10};
const UINT8 anim_shoot[] = {3,2,1,2};
const UINT8 anim_flying[] = {4, 12, 13, 14, 13};

INT8 jump_power = 0;
INT8 death_cooldown = 0;
INT8 hit_cooldown = 0;
extern UINT8 tile_collision;
INT16 archer_accel_y = 0;
INT8 shoot_cooldown = 0;
INT8 platform_vx = 0;
INT8 platform_vy = 0;
extern INT8 is_on_boss;
INT8 is_on_secret = -1;
INT8 is_on_gameover = -1;
extern UINT8 diag_found;
extern UINT8 current_camera_state; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
extern UINT8 current_camera_counter;
extern struct ArcherInfo* archer_data;
extern ARCHER_STATE archer_state;
extern INT8 fx_cooldown;
Sprite* princess_parent = 0;
extern UINT8 quiver; //little endian, rightest are the less important
INT8 diag_cooldown = MAX_DIAG_COOLDOWN;

void Die();
void Shoot();
void Jump();
void MoveArcher();
void CheckCollisionTile();
void CheckCollisionTileDoor();
void Hit(INT8 damage);
void Build_Next_Dialog();

void START() {
		
	archer_data = (struct ArcherInfo*)THIS->custom_data;
	platform_vx = 0;
	platform_vy = 0;
	if(archer_data->amulet != amulet){
		archer_data->amulet = 1u;
	}
	
	if(diag_found == 21u){ //spawn key
		Sprite* key_sprite = SpriteManagerAdd(SpriteKey, THIS->x + 16u, THIS->y);
		struct ItemInfo* datakey = (struct ItemInfo*)key_sprite->custom_data;
		datakey->type = 1;
		datakey->setup = 1u;
	}
	if(diag_found == 20u){ //spawn wrench			
		Sprite* key_sprite = SpriteManagerAdd(SpriteKey, THIS->x + 16u, THIS->y);
		struct ItemInfo* datakey = (struct ItemInfo*)key_sprite->custom_data;
		datakey->type = 2;
		datakey->setup = 1u;
	}
	
	diag_found = 0u;
	death_cooldown = 1;
	hit_cooldown = MAX_HIT_COOLDOWN;
		
	update_hud = 1;

	archer_state = STATE_NORMAL;
	
}

void UPDATE() {

	if (is_on_boss == 0 && current_camera_state != 3u){
		return;
	}
	switch(archer_state){
		case STATE_AMULET_STONE:
		case STATE_AMULET_ICE:
		case STATE_AMULET_THUNDER:
		case STATE_AMULET_FIRE:
			death_cooldown--;
			if(death_cooldown <= -100){				
				Build_Next_Dialog();
			}
			return;
		break;
		case STATE_DIAG:
			if(diag_cooldown == 0){
				if (show_diag == -1){ //NON TOCCARE
					show_diag = 0;
					diag_cooldown = MAX_DIAG_COOLDOWN;
					archer_state = STATE_NORMAL;
				}else if (KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)){ //show_diag < max_diag
					diag_cooldown = MAX_DIAG_COOLDOWN;
					show_diag += 1;
					SetSpriteAnim(THIS, anim_idle, 12u);
				}
			}else{
				diag_cooldown--;
			}
			return;
		break;
	}
	
	if(KEY_TICKED(J_START) && is_on_boss < 0){
		//se sono sullo stato del boss non fare un bel niente !!!!!!
		//non si mette in pausa al mostro!
		SetState(StateGame);
		return;
	}
	
	if (KEY_RELEASED(J_SELECT)){
		UINT8 or_ = 0u;
		while(or_ == 0u){			
			archer_data->amulet += 1u;
			archer_data->amulet %= 6u;
			if(archer_data->amulet == 0u){
				archer_data->amulet = 1u;
			}
			or_ = quiver >> (archer_data->amulet - 1u); // del risultato di questa operazione devo prendere solo il bit meno significativo, più a dx
			or_ = or_ & 1u;
		}
		update_hud = 1;
	}
	
	switch(archer_state) {
		case STATE_ASCENDING:
			MoveArcher();
			THIS->y--;
		break;
		case STATE_DEAD:
			if(death_cooldown > 0){
				death_cooldown ++;				
			}
			if(death_cooldown == 6){
				SetSpriteAnim(THIS, anim_dead, 12u);
				archer_data->ups -= 1;
			}
			if (death_cooldown < 12){
				TranslateSprite(THIS, 0, -2 );
			}else if (death_cooldown != 0){
				if (death_cooldown < 80){
					tile_collision = TranslateSprite(THIS, 0, 1);
				}else if (death_cooldown == 80){
					death_cooldown = 0;
					archer_data->hp = MAX_HP;
					update_hud = 1;
					if (archer_data->ups <= -1){
						load_next_gameover = 1;
					}else{
						if (is_on_boss > 0){
							current_camera_state = 3u;
							SetState(StateBoss);							
						}else{ //non vado alla worldmap perchè è una rottura per il giocatore				
							if(current_level < 3){
								SetState(StateGame);
							}else if (current_level < 5){
								//SetState(StateGame3);
							}else{
								//SetState(StateGame6);
							}
						}
					}
					return;
				}
			}
			return;
		break;
		case STATE_NORMAL:
		case STATE_NORMAL_PLATFORM:
			if(jump_power){
				jump_power = 0;
			}
			MoveArcher();			
			CheckCollisionTile();
			if(shoot_cooldown) {
				SetSpriteAnim(THIS, anim_shoot, 12u);
			} else if(!KEY_PRESSED(J_DOWN)){
				if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT)) {
					SetSpriteAnim(THIS, anim_walk, 16u);
				}else{
					if (archer_state == STATE_NORMAL_PLATFORM){SetSpriteAnim(THIS, anim_flying, 16u);}
					else{SetSpriteAnim(THIS, anim_idle, 12u);}					
				}
			}
			if (KEY_PRESSED(J_DOWN)){
				if(KEY_PRESSED(J_A) && archer_state == STATE_NORMAL && is_on_secret == -1){// && is_on_boss != 1
					SetSpriteAnim(THIS, anim_shield, 8u);
					Build_Next_Dialog();
					return;
				}else if (!KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
					SetSpriteAnim(THIS, anim_shield, 8u);
					if (archer_state == STATE_NORMAL_PLATFORM){
						//THIS->coll_x = 3;
						//THIS->mt_sprite->dy = 9;
						//THIS->coll_w = 10;
						//THIS->coll_h = 6;	
					}
				}
			}else if (THIS->mt_sprite->dx != 5){
				THIS->mt_sprite->dx = 5;
				if (archer_state == STATE_NORMAL_PLATFORM){
					THIS->coll_h = 12;
					THIS->mt_sprite->dy = 3;
					THIS->coll_w = 6;
				}
			}
			//Jump
			if(KEY_TICKED(J_A)){
				fx_cooldown = 30;
				PlayFx(CHANNEL_1, 30, 0x27, 0x40, 0x43, 0x68, 0x86);
				Jump();
			}
			if(shoot_cooldown) {
				shoot_cooldown -= 1;
			} else {
				if(KEY_TICKED(J_B) && (!KEY_PRESSED(J_DOWN) || ((KEY_PRESSED(J_DOWN) && archer_state == STATE_JUMPING)))) {
					Shoot();
				}
			}
			//Check falling
			if((archer_accel_y >> 3) > 1 && archer_state != STATE_DIAG) {
				archer_state = STATE_JUMPING;
			}
			if(is_on_boss == 3 && current_camera_state < 5u){
				current_camera_state = 5u; //valore che uso io completamente custom per il dialogo once a boss sconfitto
				Build_Next_Dialog();
				return;				
			}			
		break;
		case STATE_JUMPING:
			if(shoot_cooldown) {
				shoot_cooldown -= 1;
			}
			else{
				if(KEY_TICKED(J_B)) {
					Shoot();
				}else{
					if (archer_accel_y < 4){									
						if(KEY_PRESSED(J_A)) {
							if (jump_power < 6){
								jump_power += 1;
								archer_accel_y -= 2;
							}
						}else if (KEY_RELEASED(J_A)){
							jump_power += 1;
							archer_accel_y = 0;
						}
						SetSpriteAnim(THIS, anim_jump_up, 33u);
					}else{
						jump_power = 0;
						archer_accel_y += 1;
						SetSpriteAnim(THIS, anim_jump, 32u);
					}
				}
			}
			if(platform_vx > 0){
				platform_vx--;
			}else if (platform_vx < 0){
				platform_vx++;
			}
			platform_vy = 0;
			MoveArcher();
		break;
		case STATE_HIT:
			hit_cooldown -= 1;
			if(KEY_PRESSED(J_A) && hit_cooldown < 8) {
				Jump();
			}
			MoveArcher();
			if (hit_cooldown <= 0){
				jump_power = 0;
				archer_accel_y += 10;
				MoveArcher();
				platform_vx = 0;
				platform_vy = 0;
				hit_cooldown = MAX_HIT_COOLDOWN;
				archer_state = STATE_NORMAL;
			}
			return;
		break;
	}//end switch archer_state	
	
	if(princess_parent == 0 && archer_state != STATE_LADDER && archer_state != STATE_HIT && archer_state != STATE_DEAD) {
		//Simple gravity physics 
		if(archer_accel_y < 24) {
			archer_accel_y += 1;
		}
		tile_collision = TranslateSprite(THIS, 0, archer_accel_y  >> 4 );
		if(KEY_TICKED(J_UP)){
			CheckCollisionTileDoor();
		}
		/*if(tile_collision == 0 && delta_time != 0 && archer_accel_y < 24) { //Do another iteration if there is no collision
			archer_accel_y += 1;
			tile_collision = TranslateSprite(THIS, 0, archer_accel_y >> 4);
		}*/
		if(tile_collision) {
			if(archer_state == STATE_JUMPING && archer_accel_y > 0) {
				archer_state = STATE_NORMAL;
			}
			archer_accel_y = 0;	
			CheckCollisionTile();
		}
	}
	if(princess_parent && archer_state == STATE_JUMPING) {
		archer_accel_y = 0;
		archer_state = STATE_NORMAL;
	}
	
	if (GetScrollTile((THIS->x >> 3) +1, (THIS->y >> 3)) == 99u){ //tile di sollevamento, è bg quindi non posso fare altrimenti
		archer_accel_y = -2;
		archer_state = STATE_ASCENDING;
	}else if (archer_state == STATE_ASCENDING){
		archer_accel_y = -12;
		archer_state = STATE_NORMAL;
	}
	
	UINT8 scroll_tile;
	Sprite* ispr;
	SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
		if(ispr->type == SpriteAmulet) {
			if(CheckCollision(THIS, ispr)) {
				struct ItemInfo* dataamulet = (struct ItemInfo*)ispr->custom_data;
				if(dataamulet->counter == -1){
					dataamulet->counter = 60;
					dataamulet->setup = 0;
					ispr->y -= 20u;
					archer_data->hp = MAX_HP;
					death_cooldown = 127;
					THIS->x = ispr->x-3u;
					THIS->y = ispr->y+12u;
					switch(dataamulet->type){
						case 1:
							archer_state = STATE_AMULET_STONE;
							quiver = quiver | 0b0000000010; 
						break;
						case 2:
							archer_state = STATE_AMULET_ICE;
							quiver = quiver | 0b0000001000;
						break;
						case 3:
							archer_state = STATE_AMULET_THUNDER;
							quiver = quiver | 0b0000000100;
						break;
						case 4:
							quiver = quiver | 0b0000010000;
							archer_state = STATE_AMULET_FIRE;
						break;
					}
					SetSpriteAnim(THIS, anim_jump, 8u);
					update_hud = 1;
					if(is_on_boss >= 0){
						is_on_boss = 3;
					}else{
						Build_Next_Dialog();
					}					
				}
			}
		}
		if(ispr->type == SpriteItem) {
			if(CheckCollision(THIS, ispr)) {
				struct ItemInfo* dataitem = (struct ItemInfo*)ispr->custom_data;
				if (dataitem->setup == 0u){ //se e' trasparente non faccio niente
					switch(dataitem->type){
						case 1u: //coins
							archer_data->coins += 1u;
							fx_cooldown = 30;
							PlayFx(CHANNEL_1, 30, 0x6d, 0x8c, 0x73, 0xff, 0xc7);	
							SpriteManagerRemoveSprite(ispr);
						break;
						case 2u: //hp
							archer_data->hp = MAX_HP;
							fx_cooldown = 30;
							PlayFx(CHANNEL_1, 30, 0x54, 0x80, 0x74, 0x83, 0x86);
							SpriteManagerRemoveSprite(ispr);
						break;
						case 3u: //up
							archer_data->ups += 1;
							SpriteManagerRemoveSprite(ispr);
						break;
						case 7u: //dcoin
							archer_data->coins += 10u;
							if (archer_data->coins >= 100u){
								archer_data->coins = archer_data->coins - 100u;
								archer_data->ups += 1;	
							}else{
								fx_cooldown = 30;
								PlayFx(CHANNEL_1, 30, 0x6d, 0x8c, 0x73, 0xff, 0xc7);	
							}
							SpriteManagerRemoveSprite(ispr);
						break;
					}
					update_hud = 1;
				}
			}			
		}
		if(ispr->type == SpriteKey) {
			if(CheckCollision(THIS, ispr)) {
				//archer_tool = 0;
				struct ItemInfo* datakey = (struct ItemInfo*)ispr->custom_data;
				switch(datakey->type){
					case 1: //key				
						SetSpriteAnim(THIS, anim_idle, 12u);	
						if (current_level == 0u && current_map == 0u){
							if( archer_data->coins < 20u){
								return;
							}
							archer_data->coins -= 20u;
						}
						archer_data->tool = 6;
						update_hud = 1;
						SpriteManagerRemoveSprite(ispr);
						return;
					break;
					case 2: //wrench
						SetSpriteAnim(THIS, anim_idle, 12u);
						archer_data->tool = 7;
						update_hud = 1;
						SpriteManagerRemoveSprite(ispr);
						return;
					break;
				}
			}
		}
		if(ispr->type == SpritePlatform || ispr->type == SpriteIceplat) {
			if(CheckCollision(THIS, ispr)) {//&& (ispr->y - THIS->y) > 10
				struct PlatformInfo* datap = (struct PlatformInfo*)ispr->custom_data;
				if (archer_accel_y > 0){//se sono in salita non collido !
					archer_accel_y = 0;
					if(archer_state != STATE_NORMAL_PLATFORM){
						archer_state = STATE_NORMAL_PLATFORM;
						THIS->y = ispr->y - ispr->coll_h;
						if(ispr->type == SpriteIceplat){
							datap->type = 1u;
						}
					}
				}
				platform_vx = datap->vx;
				platform_vy = datap->vy;
				//THIS->y = ispr->y-3;				
			}
		}
		if(ispr->type == SpriteIceplat){
			if(CheckCollision(THIS, ispr) && archer_state != STATE_NORMAL_PLATFORM) {
				struct PlatformInfo* datap = (struct PlatformInfo*)ispr->custom_data;
				datap->type = 1u;
				THIS->y -= ispr->coll_h;
				archer_state = STATE_NORMAL_PLATFORM;
			}
		}
		/* || ispr->type == SpritePorcupine || ispr->type == SpriteEagle || ispr->type == SpriteThunder 
			|| ispr->type == SpriteIbex || ispr->type == SpriteStalattite || ispr->type == SpriteStalagmite 
			|| ispr->type == SpriteBear || ispr->type == SpriteWalrus || ispr->type == SpriteWalrusspin 
			|| ispr->type == SpriteBee	|| ispr->type == SpritePenguin || ispr->type == SpriteAxe 
			|| ispr->type == SpriteBat || ispr->type == SpriteFalce || ispr->type == SpriteCathead*/
		if(ispr->type == SpriteEnemy || ispr->type == SpriteScorpion
			|| ispr->type == SpriteRat || ispr->type == SpriteWolf || ispr->type == SpriteSpider
			|| ispr->type == SpriteAlligator 
			|| ispr->type == SpriteBird ) {
			if(CheckCollision(THIS, ispr) && archer_state != STATE_HIT) {
				struct EnemyInfo* dataenemy = (struct EnemyInfo*)ispr->custom_data;
				if(dataenemy->enemy_state == ENEMY_STATE_INVISIBLE ||
					dataenemy->enemy_state == ENEMY_STATE_HIDDEN){
					return;
				}
				switch(is_on_boss){
					case 0:
						if(ispr->type == SpriteEagle && dataenemy->enemy_state != ENEMY_STATE_ATTACK){
							return;
						}
					break;
					case 1:
						if(dataenemy->enemy_state == ENEMY_STATE_DEAD){
							if (ispr->x > THIS->x){
								THIS->x -= 1;
							}else{
								THIS->x += 1;
							}
							if(KEY_TICKED(J_A)){
								if (KEY_PRESSED(J_UP)){		
									Build_Next_Dialog();	
								}
							}						
							return;
						}
					break;
				}
				if (dataenemy->enemy_state == ENEMY_STATE_DEAD){
					return;
				}
				UINT8 being_hit = 1u;
				if (KEY_PRESSED(J_DOWN)){
					/*&& ispr->type != SpriteWalrus && ispr->type != SpriteWalrusspin
						&& ispr->type != SpriteEagle && ispr->type != SpriteIbex && ispr->type != SpriteBear && ispr->type != SpriteSpider*/
					if(ispr->type != SpriteWolf && ispr->type != SpriteAlligator){
						if (ispr->x < THIS->x){
							if (THIS->mirror == V_MIRROR){//mi sto riparando bene
								TranslateSprite(ispr, -16u << delta_time, -2u << delta_time);
								being_hit = 0u;
							}
						}else{
							if (THIS->mirror != V_MIRROR){
								TranslateSprite(ispr, 16u << delta_time, -2u << delta_time);
								being_hit = 0u;
							}
						}					
					}
				}
				if (being_hit == 1u && archer_state != STATE_DEAD){
					INT8 enemydamage = 1;
					switch(ispr->type){
						case SpriteWolf:
						case SpriteAlligator:
						/*case SpriteIbex:
						case SpriteBear:
						case SpriteWalrus:*/
							enemydamage = 2;
							TranslateSprite(THIS, 0, -1);
						break;
					}
					if (ispr->x < THIS->x){
						platform_vx = 1;
					}else{
						platform_vx = -1;
					}
					if(dataenemy->vx){
						platform_vx = dataenemy->vx;
					}
					Hit(enemydamage);
				}
			}
		}
		/*if(ispr->type == SpriteHurricane) {
			if(CheckCollision(THIS, ispr) && archer_state != STATE_HIT) {	
				if (archer_state == STATE_JUMPING | archer_state == STATE_ASCENDING){
					TranslateSprite(THIS, -2u, -2u);
				}else{
					TranslateSprite(THIS, -2u, -1u);
				}
			}
		}*/
		
		if(ispr->type == SpriteArrow) {
			if(CheckCollision(THIS, ispr)) {
				struct ArrowInfo* datap = (struct ArrowInfo*)ispr->custom_data;
				if (datap->arrowdir != 1){return;}//guardo solo se è orizzontale
				if (archer_accel_y > 0 && THIS->y < (ispr->y-4)){//se sono in salita non collido !
					//ispr->mt_sprite->dx = 0;
					//ispr->mt_sprite->dy = 2;
					//ispr->coll_w = 8;
					if (ispr->mirror == V_MIRROR){
						platform_vx = 0-datap->vx;	
					}else{
						platform_vx = datap->vx;	
					}					
					if(archer_state != STATE_NORMAL && archer_state != STATE_NORMAL_PLATFORM){
						archer_state = STATE_NORMAL_PLATFORM;
						THIS->y = ispr->y - 12;
					}
				}
			}
		}
		if(ispr->type == SpriteGate) {
			if(CheckCollision(THIS, ispr)) {
				THIS->x--;
			}
		}
	}

}

void Die(){
	StopMusic;
	fx_cooldown = 60;
	PlayFx(CHANNEL_1, 60, 0x7c, 0x80, 0x74, 0x83, 0x86);
	archer_state = STATE_DEAD;
	hit_cooldown = 0;
	platform_vx = 0;
	platform_vy = 0;
}

void Shoot() {
	SetSpriteAnim(THIS, anim_shoot, 12u);
	Sprite* arrow_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
	fx_cooldown = 20;
	//PlayFx(CHANNEL_4, 20, 0x0C, 0xB1, 0x00, 0xC0);
	PlayFx(CHANNEL_1, 20, 0x7D, 0x40, 0xF2, 0x20, 0x70);
	arrow_sprite->mirror = THIS->mirror;//flags
	arrow_sprite->x = THIS->x;
	if(arrow_sprite->mirror != V_MIRROR){
		arrow_sprite->x += 4;
	}
	arrow_sprite->y = THIS->y+4;
	struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_sprite->custom_data;
	if (archer_data->amulet){arrow_data->type = archer_data->amulet;}
	else{arrow_data->type = 1;}
	if (KEY_PRESSED(J_DOWN)){
		arrow_data->arrowdir = 4; // verticale in giu
		arrow_sprite->y += 8;
	}else{
		if (KEY_PRESSED(J_UP)){ //verticale in su
			arrow_data->arrowdir = 3;
			arrow_sprite->y -= 3;
		}else{
			arrow_data->arrowdir = 1;
		}
	}
	shoot_cooldown = 8;
}

void Jump() {
	if(archer_state != STATE_JUMPING) {
		archer_state = STATE_JUMPING;
		archer_accel_y = -14;
		princess_parent = 0;
		THIS->coll_w = 6;
		SetSpriteAnim(THIS, anim_jump_up, 12u);
	}
}

void MoveArcher() {
	if(archer_state == STATE_HIT){
		if(THIS->mirror == V_MIRROR){
			platform_vx=1;
		}else{
			platform_vx=-1;
		}			
	}
	if(platform_vx || platform_vy){
		tile_collision = TranslateSprite(THIS, platform_vx << delta_time, platform_vy << delta_time);
	}
	if(KEY_PRESSED(J_LEFT)) {
		if(KEY_PRESSED(J_DOWN) && archer_state != STATE_JUMPING){
			
		}else{
			if (THIS->mirror == V_MIRROR){
				tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
			}
		}
		THIS->mirror = V_MIRROR;//SPRITE_SET_VMIRROR(THIS);
	}
	else if(KEY_PRESSED(J_RIGHT)) {
		if(KEY_PRESSED(J_DOWN) && archer_state != STATE_JUMPING){
			
		}else{
			if(THIS->mirror != V_MIRROR){
				tile_collision = TranslateSprite(THIS, 1 << delta_time, 0);
			}
		}
		THIS->mirror = NO_MIRROR;//SPRITE_UNSET_VMIRROR(THIS);
	}
}

void CheckCollisionTileDoor(){
	//UINT8 getScrolledTile = GetScrollTile((THIS->x >> 3) +1u, ((THIS->y+3) >> 3) +2u);
	tile_collision = GetScrollTile((THIS->x >> 3) +1u, ((THIS->y+3) >> 3) +2u);
	//switch(getScrolledTile){//tile_collision
	switch(tile_collision){//tile_collision
		case 7u: //fine level - goto boss!
			current_camera_state = 0u; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
			current_camera_counter = 0u;
			switch(current_level){
				case 0u: //wolf
				case 1u: //gator
					if(archer_data->tool){
						current_level_b = current_level;
						is_on_boss = 0;
					}
				break;
				case 2u: // eagle
				case 3u: // ibex
				case 4u: // bear 
				case 5u: // walrus
					current_level_b = current_level;
					is_on_boss = 0;
				break;
			}
			Build_Next_Dialog();
		break;
		case 8u: //fine boss!
			if(current_level_b == 0u || current_level_b == 2u || current_level_b == 4u){
				if(archer_data->tool != level_tool){
					return;
				}
			}
			is_on_boss = -1;
			archer_tool = 0;
			archer_data->tool = 0; //tool consumato
			load_next_b = 0;
			current_level += 1u;
			current_map = 0;
			SetState(StateWorldmap);
		break;
		case 19u: //exit secret room
			load_next_s = -1;			
		break;
		case 41u: //next map
			load_next = 1;
		break;
		case 42u: //previous map
			load_next = -1;
		break;
		case 46u: //secret room
			load_next_s = 1;
		break;
	}
}

void CheckCollisionTile() {
	if(archer_state != STATE_HIT){
		switch(tile_collision) {
			case 10u:
				if(current_level != 6u){
					return;
				}
			case 2u: //2 (e 10 del liv6) sono spuncioni alti, se li scranio, cado di 2-3px no ?
				THIS->y += 4u;
				Hit(1);
			case 20u:
				if(current_level == 6u){
					Hit(1);
					return;
				}
			case 23u:
			case 29u:
				Hit(1);
			break;
			case 38u:
			case 39u:
				if(current_level == 5u || (current_level_b == 5u && is_on_boss > 0)){
					Hit(1);				
				}
			break;
			case 40u: //skull of death
				Hit(1);
			break;		
			case 64u: //skull in ice cave
				if(current_level == 5u){
					Hit(1);
				}
			break;
			case 111u:
				if(platform_vx != 2){
					platform_vx = 2;
				}
			break;
			case 119u:
				if(platform_vx != -2){
					platform_vx = -2;
				}
			break;
		}
	}
}

void Hit(INT8 damage) {
	if (archer_state != STATE_DEAD && archer_state != STATE_HIT){
		archer_state = STATE_HIT;
		archer_data->hp -=  damage;
		if (archer_data->hp <= 0){
			//archer_data->hp = 0;
			update_hud = 1;
			Die();
			return;
		}
		fx_cooldown = 30;
		PlayFx(CHANNEL_1, 30, 0x4c, 0x81, 0x43, 0x73, 0x86);
		update_hud = 1;
		/*platform_vx = 1;
		if (THIS->mirror == V_MIRROR){
			platform_vx = -1;
		}*/
		TranslateSprite(THIS, 0, -2 << delta_time);
		SetSpriteAnim(THIS, anim_hit, 24u);
	}
}

void Build_Next_Dialog(){
	diag_found = Build_Next_Dialog_Banked(THIS);
	if(diag_found){
		if(diag_found != 99u){ // 99u means no state changing, just simple diag message to show from StateGame			
			drop_player_x = THIS->x >> 3;
			drop_player_y = THIS->y >> 3;
			load_next_d = 1;
		}else{
			archer_state = STATE_DIAG;
			SetSpriteAnim(THIS, anim_idle, 12u);
			show_diag = 1;	
		}		
	}
}

void DESTROY() {
	
}