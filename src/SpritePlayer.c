#include "Banks/SetBank7.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "gbt_player.h"

#include "custom_datas.h"



const UINT8 anim_idle[] = {1, 0}; //The first number indicates the number of frames
const UINT8 anim_jump[] = {1, 10};
const UINT8 anim_jump_up[] = {1, 11};
const UINT8 anim_up[] = {1, 0};
const UINT8 anim_dead[] = {1, 15};
const UINT8 anim_walk[] = {4, 7, 6, 5, 4};
const UINT8 anim_shield[] = {1, 3};
const UINT8 anim_hit[] = {2, 8, 9};
const UINT8 anim_shoot[] = {2,1,2};
const UINT8 anim_flying[] = {4, 12, 13 ,14 , 13};

INT8 shoot_cooldown = 0;
UINT8 jump_power = 0u;
INT8 platform_vx = 0;
UINT8 death_cooldown = 0;

struct Sprite* princess_parent = 0;


extern ARCHER_STATE archer_state;

INT16 archer_accel_y = 0;

UINT8 tile_collision;
extern INT8 load_next;
extern INT8 load_next_s;
extern INT8 load_next_b;

UINT8 aimc = 0u;
UINT8 hit_cooldown = 0u;

struct ArcherInfo* archer_data;

extern INT8 show_diag;
extern INT8 max_diag;

void Die();
void Shoot();
void Jump();
void MoveArcher();
void CheckCollisionTile();
void Hit();


void Start_SpritePlayer() {
	archer_data = (struct ArcherInfo*)THIS->custom_data;
	archer_data->amulet = 1u;
	archer_data->tool = 0;
	archer_data->ups = 0;
	archer_data->coins = 0u;
	
	
	THIS->coll_x = 5;
	THIS->coll_y = 5;
	THIS->coll_w = 6;
	THIS->coll_h = 11;
	
	archer_state = STATE_JUMPING;
	
	hit_cooldown = 36u;

}

void Update_SpritePlayer() {
	
	if(archer_state == STATE_DIAG ){
		if (show_diag >= max_diag){
			archer_state = STATE_NORMAL;
		}else{		
			if(KEY_RELEASED(J_A)){
				show_diag += 1;	
			}	
		}
		return;
	}
	
	if(KEY_TICKED(J_START)){
		SetState(StateGame);
		return;
	}
	
	if (KEY_RELEASED(J_SELECT)){
		archer_data->amulet += 1u;
		archer_data->amulet %= 6u;
		if(archer_data->amulet == 0u){
			archer_data->amulet = 1u;
		}
	}
	
	switch(archer_state) {
		case STATE_DEAD:
			death_cooldown ++;
			if(death_cooldown == 6){
				SetSpriteAnim(THIS, anim_dead, 12u);	
			}
			if (death_cooldown < 12){
				TranslateSprite(THIS, 0, -2 );
			}else{
				if (death_cooldown < 160){
					TranslateSprite(THIS, 0, 1);
				}else{
					death_cooldown = 0;
					archer_data->ups -= 1;
					archer_data->hp = 100;	
					if (archer_data->ups == -1){SetState(StateGameOver);}
					else{SetState(StateGame);}	
				}
			}
			return;
		break;
		case STATE_NORMAL:
		case STATE_NORMAL_PLATFORM:
			MoveArcher();
			CheckCollisionTile();
			if(shoot_cooldown) {
				SetSpriteAnim(THIS, anim_shoot, 12u);
			} else {
				if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
					SetSpriteAnim(THIS, anim_walk, 16u);
				}else{
					if (archer_state == STATE_NORMAL_PLATFORM){SetSpriteAnim(THIS, anim_flying, 16u);}
					else{SetSpriteAnim(THIS, anim_idle, 33u);}					
				}
				if(KEY_PRESSED(J_UP)){
					aimc += 1;
					if(aimc >= 16){
						aimc=16;
					}
				}
				if(KEY_RELEASED(J_UP)){
					aimc = 0;
					return;
				}
			}
			if (KEY_PRESSED(J_DOWN)){
				SetSpriteAnim(THIS, anim_shield, 8u);
				THIS->coll_x = 8;
			}else if (THIS->coll_x != 5){
				THIS->coll_x = 5;
			}
			
			//Jump / Dialog
			if(KEY_TICKED(J_A)){
				if (KEY_PRESSED(J_UP)){		
					//if(show_diag<0){show_diag=0;}
					archer_state = STATE_DIAG;	
					return;
				}else{
					//Check jumping
					Jump();
				}
			}
			
			if(shoot_cooldown) {
				shoot_cooldown -= 1u;
			} else {
				if(KEY_TICKED(J_B) & (!KEY_PRESSED(J_DOWN) | (KEY_PRESSED(J_DOWN) & archer_state == STATE_JUMPING))) {
					Shoot();
				}
			}
			//Check falling
			if((archer_accel_y >> 3) > 1) {
				archer_state = STATE_JUMPING;
			}
			
		break;
		case STATE_JUMPING:
			if(shoot_cooldown) {
				shoot_cooldown -= 1u;
			}else{
				if(KEY_TICKED(J_B)) {
					Shoot();
				}else{
					if (archer_accel_y < 4){									
						if(KEY_PRESSED(J_A)) {
							if (jump_power < 6u){
								jump_power += 1u;
								archer_accel_y -= 2;
							}
						}else if (KEY_RELEASED(J_A)){
							jump_power += 1u;
							archer_accel_y = 0;
						}
						SetSpriteAnim(THIS, anim_jump_up, 33u);
					}else{
						jump_power = 0u;
						archer_accel_y += 1;
						SetSpriteAnim(THIS, anim_jump, 32u);
					}
				}
			}
			platform_vx = 0;
			MoveArcher();
		break;
		case STATE_HIT:
			hit_cooldown -= 1;
			MoveArcher();
			if (hit_cooldown == 0){
				platform_vx = 0;
				hit_cooldown = 24u;
				if(KEY_PRESSED(J_A)) {
					Jump();
				}
				archer_state = STATE_NORMAL;
			}
		break;
	}//end switch archer_state
	
	
	if(princess_parent == 0 && archer_state != STATE_LADDER && archer_state != STATE_HIT && archer_state != STATE_DEAD) {
		//Simple gravity physics 
		if(archer_accel_y < 24) {
			archer_accel_y += 1;
		}
		tile_collision = TranslateSprite(THIS, 0, archer_accel_y  >> 4 );
		if(!tile_collision && delta_time != 0 && archer_accel_y < 24) { //Do another iteration if there is no collision
			archer_accel_y += 2;
			tile_collision = TranslateSprite(THIS, 0, archer_accel_y >> 4);
		}
		if(tile_collision) {
			if(archer_state == STATE_JUMPING & archer_accel_y > 0) {
				archer_state = STATE_NORMAL;
				archer_accel_y = 0;
				//TODO PLAY ATTERRAGGIO EFFEXT
			}else{
				archer_accel_y = 0;	
			}
			CheckCollisionTile();
		}
	}
	if(princess_parent && archer_state == STATE_JUMPING) {
		archer_accel_y = 0;
		archer_state = STATE_NORMAL;
	}
	
	UINT8 scroll_tile;
	struct Sprite* ispr;
	//Check sprite collision platform/enemy
	SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
		if(ispr->type == SpriteItem) {
			if(CheckCollision(THIS, ispr)) {
				struct ItemInfo* dataitem = (struct ItemInfo*)ispr->custom_data;
				if (dataitem->setup == 0u){ //se e' trasparente non faccio niente
					switch(dataitem->type){
						case 1u: //coins
							archer_data->coins++;
							if (archer_data->coins == 100u){
								archer_data->coins = 0u;
								archer_data->ups += 1;	
							}
							PlayFx(CHANNEL_1, 3, 0x6d, 0x8c, 0x73, 0xff, 0xc7);
							SpriteManagerRemoveSprite(ispr);
						break;
						case 2u: //hp
							archer_data->hp = 100u;
							SpriteManagerRemoveSprite(ispr);
						break;
						case 3u: //up
							archer_data->ups += 1;
							SpriteManagerRemoveSprite(ispr);
						break;
						case 7u: //dcoin
							archer_data->coins+=10;
							if (archer_data->coins >= 100){
								archer_data->coins = archer_data->coins - 100;
								archer_data->ups += 1;	
							}
							PlayFx(CHANNEL_1, 3, 0x6d, 0x8c, 0x73, 0xff, 0xc7);
							SpriteManagerRemoveSprite(ispr);
						break;
						case 10u: //scrigno
							dataitem->collided = 1;
						break;
					}
				}
			}			
		}
		if(ispr->type == SpriteKey) {
			if(CheckCollision(THIS, ispr)) {
				struct ItemInfo* datakey = (struct ItemInfo*)ispr->custom_data;
				switch(datakey->type){
					case 1: //wrench
						archer_data->tool = 6;
						SpriteManagerRemoveSprite(ispr);	
					break;
					case 2: //key
						archer_data->tool = 7;
						SpriteManagerRemoveSprite(ispr);	
					break;
				}
			}
		}
		if(ispr->type == SpritePlatform) {
			if(CheckCollision(THIS, ispr)) {
				if (archer_accel_y > 0){//se sono in salita non collido !
					archer_accel_y = 0;
					struct PlatformInfo* datap = (struct PlatformInfo*)ispr->custom_data;
					platform_vx = datap->vx;
					if(archer_state != STATE_NORMAL & archer_state != STATE_NORMAL_PLATFORM){
						archer_state = STATE_NORMAL_PLATFORM;
						THIS->y = ispr->y - ispr->coll_h;
					}
				}
			}
		}
		if(ispr->type == SpriteEnemy || ispr->type == SpriteScorpion || ispr->type == SpritePorcupine || ispr->type == SpriteWolf) {
			if(CheckCollision(THIS, ispr) & archer_state != STATE_HIT) {
				struct EnemyInfo* dataenemy = (struct EnemyInfo*)ispr->custom_data;
				if (dataenemy->enemy_state == ENEMY_STATE_DEAD){
					return;
				}
				UINT8 being_hit = 1;
				if (KEY_PRESSED(J_DOWN) & ispr->type != SpriteWolf){ //se mi sto riparando e lo sono girato dove serve
					if (ispr->x < THIS->x){
						if (SPRITE_GET_VMIRROR(THIS)){//mi sto riparando bene	
							ispr->x -= 16;
							being_hit = 0;
						}
					}else{
						if (!SPRITE_GET_VMIRROR(THIS)){
							ispr->x += 16;
							being_hit = 0;
						}
					}					
				}
				if (being_hit & archer_state != STATE_DEAD){
					archer_data->hp -=  dataenemy->enemydamage;
					if (archer_data->hp <= 0){
						archer_data->hp = 0;
						Die();
					}
					Hit();
					if (ispr->x < THIS->x){
						platform_vx = 1;
					}else{
						platform_vx = -1;
					}	
				}
			}
		}
		if(ispr->type == SpriteArrow) {
			if(CheckCollision(THIS, ispr)) {
				struct ArrowInfo* arrowdata = (struct ArrowInfo*)ispr->custom_data;
				if (arrowdata->type == 6u){ //spine from porcupine
					if(!KEY_PRESSED(J_DOWN)){
						archer_data->hp -=  arrowdata->arrowdamage;
						if (archer_data->hp <= 0){
							archer_data->hp = 0;
							Die();
						}
						Hit();
					}
					SpriteManagerRemoveSprite(ispr);
					return;
				}
				struct ArrowInfo* datap = (struct ArrowInfo*)ispr->custom_data;
				if (datap->arrowdir != 1){return;}//guardo solo se è orizzontale
				if (archer_accel_y > 0 & THIS->y < (ispr->y-4)){//se sono in salita non collido !
					//archer_accel_y = 0;
					ispr->coll_x = 0;
					ispr->coll_y = 2;
					ispr->coll_w = 8;
					if (SPRITE_GET_VMIRROR(ispr)){
						platform_vx = -datap->vx;	
					}else{
						platform_vx = datap->vx;	
					}					
					if(archer_state != STATE_NORMAL & archer_state != STATE_NORMAL_PLATFORM){
						archer_state = STATE_NORMAL_PLATFORM;
						THIS->y = ispr->y - 12;
					}
				}
			}
		}
	}

}

void Die(){
	archer_state = STATE_DEAD;
}

void Shoot() {
	SetSpriteAnim(THIS, anim_shoot, 16u);
	struct Sprite* arrow_sprite = SpriteManagerAdd(SpriteArrow, 0, 0);
	/*NR50_REG = 0x22; //Max volume = 0x77
	PlayFx(CHANNEL_4, 3, 0x0C, 0xB1, 0x00, 0xC0);*/
	arrow_sprite->flags = THIS->flags;
	arrow_sprite->x = THIS->x;
	arrow_sprite->x += 4;
	arrow_sprite->y = THIS->y;
	struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_sprite->custom_data;
	if (archer_data->amulet){arrow_data->type = archer_data->amulet;}
	else{arrow_data->type = 1;}
	if (KEY_PRESSED(J_DOWN)){
		arrow_data->arrowdir = 4; // verticale in giu
		arrow_sprite->y += 8;
	}else{
		if (KEY_PRESSED(J_UP)){ //diagonale
			arrow_data->arrowdir = 2;
		}else{
			if(aimc < 16){ //orizzontale
				arrow_data->arrowdir = 1;
			}	
		}
		if (aimc == 16){ // verticale in su
			arrow_data->arrowdir = 3;
			arrow_sprite->y -= 4;
		}
	}
	shoot_cooldown = 4;//8
	aimc = 0;
}

void Jump() {
	if(archer_state != STATE_JUMPING) {
		NR50_REG = 0x22; //Max volume		
		//PlayFx(CHANNEL_1, 60, 0x46, 0xC2, 0x43, 0x68, 0x86);
		archer_state = STATE_JUMPING;
		archer_accel_y = -14;
		princess_parent = 0;
		SetSpriteAnim(THIS, anim_jump_up, 12u);
	}
}

void MoveArcher() {
	
	if(KEY_PRESSED(J_LEFT)) {
		if(KEY_PRESSED(J_DOWN)){
			
		}else{
			if (SPRITE_GET_VMIRROR(THIS)){
				tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
			}
		}
		SPRITE_SET_VMIRROR(THIS);
	}
	else if(KEY_PRESSED(J_RIGHT)) {
		if(!SPRITE_GET_VMIRROR(THIS) & !KEY_PRESSED(J_DOWN)){
			tile_collision = TranslateSprite(THIS, 1 << delta_time, 0);
		}
		SPRITE_UNSET_VMIRROR(THIS);
	}
	tile_collision = TranslateSprite(THIS, platform_vx << delta_time, 0);
}

void CheckCollisionTile() {
	if(tile_collision){
		platform_vx = 0;
	}
	switch(tile_collision) {
		case 2u:
			if (archer_state != STATE_HIT){
				archer_data->hp -=  5;
				if (archer_data->hp <= 0){
					archer_data->hp = 0;
					archer_state = STATE_DEAD;
				}
				Hit();
			}
		break;
		case 7u: //fine level - goto boss!
			if(archer_data->tool){
				archer_data->tool = 0; //tool consumato
				load_next_b = 1;
			}			
		break;
		case 8u: //fine boss!
			if(archer_data->tool){
				archer_data->tool = 0; //tool consumato
				load_next_b = 2;
			}			
		break;
		case 19u: //exit secret room
			load_next_s = -1;
		break;
		case 40u: //instant death
			archer_data->hp = 0;
			Die();
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
		/*case 28u:
			SET_BIT(stage_completion, current_stage);
			SetState(StateStageSelect);
		break;*/
	}
}

void Hit() {
	if (archer_state != STATE_DEAD){
		archer_state = STATE_HIT;	
		platform_vx = 1;
		THIS->y -= 6;
		SetSpriteAnim(THIS, anim_hit, 32u);
		NR50_REG = 0x55; //Max volume
		PlayFx(CHANNEL_1, 2, 0x4c, 0x81, 0x43, 0x73, 0x86);
	}
}


void Destroy_SpritePlayer() {
	
}
