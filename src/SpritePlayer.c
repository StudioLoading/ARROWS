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

#define ARCHER_MAX_JUMP_POWER 6

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
extern UINT8 paused;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;

#define MAX_HIT_COOLDOWN 40
#define MIN_HIT_COOLDOWN 30
#define MAX_DEATH_COOLDOWN 80
#define MAX_DIAG_COOLDOWN 60
#define MAX_LANDING_TIME 24
#define MAX_ACCEL_Y_TO_LAND_ANIMATION 36
#define MAX_SHOOT_COOLDOWN 8

//The first number indicates the number of frames
const UINT8 anim_idle[] = {4, 12, 13, 14, 13};
const UINT8 anim_jump[] = {1, 11};
const UINT8 anim_jump_up[] = {1, 6};
const UINT8 anim_dead[] = {1, 9};
const UINT8 anim_walk[] = {4, 7, 4, 6, 5, 4};
const UINT8 anim_shield[] = {1, 3};
const UINT8 anim_hit[] = {2, 8, 10};
const UINT8 anim_shoot[] = {3,2,1,2};
const UINT8 anim_flying[] = {4, 12, 13, 14, 13};

extern UINT8 J_JUMP;
extern UINT8 J_FIRE;
extern INT8 is_on_boss;
extern UINT8 diag_found;
extern UINT8 current_camera_state; //0 initial wait, 1 move to boss, 2 wait boss, 3 move to pg, 4 reload
extern UINT8 current_camera_counter;
extern struct ArcherInfo* archer_data;
extern ARCHER_STATE archer_state;
extern INT8 fx_cooldown;
extern UINT8 quiver; //little endian, rightest are the less important
extern UINT8 tile_collision;
extern UINT8 final_quiver;

INT8 jump_power = 0;
INT8 death_cooldown = 0;
INT8 hit_cooldown = 0;
INT16 archer_accel_y = 0;
INT8 shoot_cooldown = 0;
INT8 platform_vx = 0;
INT8 platform_vy = 0;
INT8 is_on_secret = -1;
INT8 is_on_gameover = -1;
INT8 diag_cooldown = MAX_DIAG_COOLDOWN;
INT8 landing_time = MAX_LANDING_TIME;
UINT8 surfing = 0u;

UINT8 scroll_tile;
Sprite* ispr;
struct ItemInfo* itemdata;
struct AmuletInfo* amuletdata;
struct PlatformInfo* platformdata;
struct EnemyInfo* dataenemy;
struct ArrowInfo* arrowdata;

void Die();
void Shoot();
void Jump();
void MoveArcher();
void CheckCollisionTile();
void CheckCollisionTileDoor();
void Hit(INT8 damage);
void Build_Next_Dialog() BANKED;
void GoToFinalFightCutscene(UINT8 arrow_type) BANKED;//StateBoss
void Next_Amulet() BANKED;

void START() {
		
	archer_data = (struct ArcherInfo*)THIS->custom_data;
	platform_vx = 0;
	platform_vy = 0;
	if(archer_data->amulet != amulet){
		archer_data->amulet = 1u;
	}
	
	if(diag_found == 21u){ //spawn key
		PauseMusic;
		Sprite* key_sprite = SpriteManagerAdd(SpriteKey, THIS->x + 16u, THIS->y);
		struct ItemInfo* datakey = (struct ItemInfo*)key_sprite->custom_data;
		datakey->type = 1;
		datakey->setup = 1u;
	}
	if(diag_found == 20u){ //spawn wrench	
		PauseMusic;		
		Sprite* wrench_sprite = SpriteManagerAdd(SpriteKey, THIS->x + 16u, THIS->y);
		struct ItemInfo* datawrench = (struct ItemInfo*)wrench_sprite->custom_data;
		datawrench->type = 2;
		datawrench->setup = 1u;
	}
	
	diag_found = 0u;
	death_cooldown = 1;
	hit_cooldown = MAX_HIT_COOLDOWN;
		
	update_hud = 1;

	if(current_level == 8u && current_map == 0){
		//archer_state = STATE_ARROWMOTHER;
	}else{
		archer_state = STATE_NORMAL;
	}
	landing_time = MAX_LANDING_TIME;
	if(current_level == 9u){
		archer_data->amulet = 1u;
	}
}

void UPDATE() {

	if (is_on_boss == 0 && current_camera_state != 3u){
		return;
	}
	switch(archer_state){//for STATES AMULET AND DIAG
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
					if(is_on_boss == -1) ResumeMusic;
					show_diag = 0;
					diag_cooldown = MAX_DIAG_COOLDOWN;
					archer_state = STATE_NORMAL;
				}else if(paused && KEY_TICKED(J_START)){
					if(is_on_boss == -1) ResumeMusic;
					set_sgb_palette_statusbar();
					diag_cooldown = MAX_DIAG_COOLDOWN;
					show_diag += 1;
					SetSpriteAnim(THIS, anim_idle, 12u);
					archer_state = STATE_NORMAL;
					paused = 0;
				} 
				else if(!paused){				
					if(KEY_TICKED(J_FIRE) || KEY_TICKED(J_JUMP) || KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)){ //show_diag < max_diag
						if(is_on_boss == -1) ResumeMusic;	
						set_sgb_palette_statusbar();
						diag_cooldown = MAX_DIAG_COOLDOWN;
						show_diag += 1;
						SetSpriteAnim(THIS, anim_idle, 12u);
					}
				}
			}else{
				diag_cooldown--;
			}
			return;
		break;
	}
	
	if(KEY_TICKED(J_START) && KEY_PRESSED(J_DOWN)){
		SetState(StateGame);
		return;
	}

	if(KEY_TICKED(J_START) && is_on_boss < 0 && is_on_secret == -1 && archer_state == STATE_NORMAL){
		if(paused == 0u){
			paused = 1u;
			diag_found = Build_Next_Dialog_Banked(THIS);// expected 98
			archer_state = STATE_DIAG;
			SetSpriteAnim(THIS, anim_idle, 12u);
			show_diag = 1;
		}	
		return;
	}
	
	if (KEY_RELEASED(J_SELECT)){
		Next_Amulet();
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
				if (death_cooldown < MAX_DEATH_COOLDOWN){
					tile_collision = TranslateSprite(THIS, 0, 1);
				}else if (death_cooldown == MAX_DEATH_COOLDOWN){
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
							if(current_level < 3u){
								SetState(StateGame);
							}else if (current_level < 5u){
								SetState(StateGame3);
							}else if (current_level <= 6u){
								SetState(StateGame6);
							}else if (current_level == 7u){
								//current_map = 2;
								SetState(StateGame7);
							}else if (current_level == 8u){
								SetState(StateGame7);
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
					landing_time = MAX_LANDING_TIME;
					SetSpriteAnim(THIS, anim_walk, 16u);
				}else{
					if (archer_state == STATE_NORMAL_PLATFORM){SetSpriteAnim(THIS, anim_flying, 16u);}
					else{
						if(landing_time < MAX_LANDING_TIME){
							SetSpriteAnim(THIS, anim_shield, 16u);
							landing_time++;
						}else{
							SetSpriteAnim(THIS, anim_idle, 12u);
						}
					}					
				}
			}
			if (KEY_PRESSED(J_DOWN)){
				if(KEY_PRESSED(J_JUMP) && archer_state == STATE_NORMAL && is_on_secret == -1){// && is_on_boss != 1
					SetSpriteAnim(THIS, anim_shield, 8u);
					Build_Next_Dialog();
					return;
				}else if (!KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
					SetSpriteAnim(THIS, anim_shield, 8u);
				}
			}
			//Jump
			if(KEY_TICKED(J_JUMP)){//&& landing_time == MAX_LANDING_TIME){
				fx_cooldown = 30;
				landing_time = MAX_LANDING_TIME;
				PlayFx(CHANNEL_1, 50, 0x27, 0x40, 0x43, 0x68, 0x86);
				Jump();
			}
			if(shoot_cooldown) {
				shoot_cooldown -= 1;
			} else {
				if(KEY_TICKED(J_FIRE) && (!KEY_PRESSED(J_DOWN) || ((KEY_PRESSED(J_DOWN) && archer_state == STATE_JUMPING)))) {
					Shoot();
				}
			}
			//Check falling
			if((archer_accel_y >> 3) > 1 && archer_state != STATE_JUMPING && archer_state != STATE_NORMAL_PLATFORM){
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
				if(KEY_TICKED(J_FIRE)) {
					Shoot();
				}else{
					if (archer_accel_y < 4){									
						if(KEY_PRESSED(J_JUMP)) {
							if (jump_power < ARCHER_MAX_JUMP_POWER){
								jump_power += 1;
								archer_accel_y -= 2;
							}
						}else if (KEY_RELEASED(J_JUMP)){
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
			if(KEY_PRESSED(J_JUMP) && hit_cooldown < MIN_HIT_COOLDOWN) {
				platform_vx = 0;
				platform_vy = 0;
				hit_cooldown = MAX_HIT_COOLDOWN;
				Jump();
			}else{
				//MoveArcher();
				if (hit_cooldown < 1){
					jump_power = 0;
					archer_accel_y += 10;
					MoveArcher();
					platform_vx = 0;
					platform_vy = 0;
					hit_cooldown = MAX_HIT_COOLDOWN;
					archer_state = STATE_NORMAL;
				}
			}
			return;
		break;
		case STATE_ARROWMOTHER:
			//Jump
			if(jump_power){
				jump_power = 0;
			}
			if(shoot_cooldown) {
				SetSpriteAnim(THIS, anim_shoot, 12u);
			}else{
				SetSpriteAnim(THIS, anim_idle, 12u);
			}
			if(KEY_PRESSED(J_LEFT)) {
				THIS->mirror = V_MIRROR;
			}
			if(KEY_PRESSED(J_RIGHT)) {
				THIS->mirror = NO_MIRROR;
			}
			THIS->x = THIS->lim_x;
			THIS->y = THIS->lim_y;
			if(KEY_TICKED(J_JUMP)){//&& landing_time == MAX_LANDING_TIME){
				fx_cooldown = 30;
				landing_time = MAX_LANDING_TIME;
				PlayFx(CHANNEL_1, 50, 0x27, 0x40, 0x43, 0x68, 0x86);
				Jump();
			}
			if(shoot_cooldown) {
				shoot_cooldown -= 1;
			} else {
				if(KEY_TICKED(J_FIRE) && (!KEY_PRESSED(J_DOWN) || ((KEY_PRESSED(J_DOWN) && archer_state == STATE_JUMPING)))) {
					Shoot();
				}
			}
		break;
	}//end switch archer_state	
	
	if( archer_state != STATE_LADDER && archer_state != STATE_HIT && archer_state != STATE_DEAD && archer_state != STATE_ARROWMOTHER) {
		//Simple gravity physics 
		if(archer_accel_y < 24) {
			archer_accel_y += 1;
		}
		tile_collision = TranslateSprite(THIS, 0, archer_accel_y  >> 4 );
		if(KEY_TICKED(J_UP)){
			CheckCollisionTileDoor();
		}
		if(tile_collision) {
			if(archer_state == STATE_JUMPING && archer_accel_y > 0) {
				archer_state = STATE_NORMAL;
				if(archer_accel_y > MAX_ACCEL_Y_TO_LAND_ANIMATION){
					landing_time = 0;
				}
			}
			archer_accel_y = 0;	
			CheckCollisionTile();
		}
	}
	
	if (GetScrollTile((THIS->x >> 3), (THIS->y >> 3)) == 99u || GetScrollTile((THIS->x >> 3) + 1u, (THIS->y >> 3) + 1u) == 99u){ //tile di sollevamento, è bg quindi non posso fare altrimenti
		archer_accel_y = -2;
		archer_state = STATE_ASCENDING;
	}else if (archer_state == STATE_ASCENDING){
		archer_accel_y = -12;
		archer_state = STATE_NORMAL;
	}
	
	SPRITEMANAGER_ITERATE(scroll_tile, ispr) {
		if(CheckCollision(THIS, ispr)) {
			switch(ispr->type){
				case SpriteAmulet:
					amuletdata = (struct AmuletInfo*)ispr->custom_data;
					ispr->y -= 24u;
					archer_data->hp = MAX_HP;
					death_cooldown = 127;
					THIS->x = ispr->x;
					THIS->y = ispr->y+20u;
					amuletdata->picked = 1;
					switch(amuletdata->type){
						case 1:
							archer_state = STATE_AMULET_STONE;
							quiver |= 0b0000000010; 
						break;
						case 2:
							archer_state = STATE_AMULET_ICE;
							quiver |= 0b0000001000;
						break;
						case 3:
							archer_state = STATE_AMULET_THUNDER;
							quiver |= 0b0000000100;
						break;
						case 4:
							quiver |= 0b0000010000;
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
				break;
				case SpriteItem:
					itemdata = (struct ItemInfo*)ispr->custom_data;
					if (itemdata->setup == 0u){ //se e' trasparente non faccio niente
						fx_cooldown = 30;
						if(itemdata->type == itemdata->content_type){
							PlayFx(CHANNEL_1, 50, 0x6d, 0x8c, 0x73, 0xff, 0xc7);//sfx item
						}
						switch(itemdata->type){
							case 1u: //coins
								archer_data->coins += 1u;
								SpriteManagerRemoveSprite(ispr);
							break;
							case 2u: //hp
								archer_data->hp = MAX_HP;
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
								}
								SpriteManagerRemoveSprite(ispr);
							break;
						}
						update_hud = 1;
					}
				break;
				case SpriteKey:
					ResumeMusic;
					itemdata = (struct ItemInfo*)ispr->custom_data;
					switch(itemdata->type){
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
				break;
				case SpritePlatform:
				case SpriteIceplat:
					platformdata = (struct PlatformInfo*)ispr->custom_data;
					if (archer_accel_y > 0){//se sono in salita non collido !
						archer_accel_y = 0;
						if(archer_state != STATE_NORMAL_PLATFORM){
							archer_state = STATE_NORMAL_PLATFORM;
							THIS->y = ispr->y - 5;
							if(ispr->type == SpriteIceplat){
								platformdata->type = 1u;
								THIS->y = ispr->y-14;
							}
						}
					}
					platform_vx = platformdata->vx;
					platform_vy = platformdata->vy;
				break;				
				case SpriteEnemy:
				case SpriteScorpion:
				case SpriteSpider:
				case SpriteEagle:
				case SpriteRat: 
				case SpriteWolf:
				case SpriteThunder:
				case SpriteAlligator:
				case SpriteIbex:
				case SpriteBee:
				case SpriteBird:
				case SpriteBear:
				case SpritePenguin:
				case SpriteStalattite:
				case SpriteStalagmite:
				case SpriteWalrus:
				case SpriteWalrusspin:
				case SpriteAxe:
				case SpriteBat:
				case SpriteFalce:
				case SpriteCathead:
					if (archer_data->hp <= 0){
						update_hud = 1;
						Die();
						return;
					}
					if(archer_state == STATE_HIT || hit_cooldown < MAX_HIT_COOLDOWN) {
						return;
					}
					dataenemy = (struct EnemyInfo*)ispr->custom_data;
					if(dataenemy->enemy_state == ENEMY_STATE_INVISIBLE || dataenemy->enemy_state == ENEMY_STATE_HIDDEN){
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
								if(KEY_TICKED(J_JUMP)){
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
						if(ispr->type != SpriteSpider && ispr->type != SpriteWolf 
							&& ispr->type != SpriteAlligator && ispr->type != SpriteEagle 
							&& ispr->type != SpriteIbex && ispr->type != SpriteWalrus 
							&& ispr->type != SpriteWalrusspin
							&& ispr->type != SpriteBear && ispr->type != SpriteArrowboss){
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
							case SpriteIbex:
							case SpriteBear:
							case SpriteWalrus:
							case SpriteWalrusspin:
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
					}else{
						PlayFx(CHANNEL_1, 50, 0x2c, 0x81, 0x43, 0x73, 0x86);	
						if(THIS->mirror != V_MIRROR){
							SpriteManagerAdd(SpritePuff, THIS->x + 8, ispr->y -2u);
						}else{
							SpriteManagerAdd(SpritePuff, THIS->x - 8, ispr->y -2u);
						}
					}
				break;
				case SpriteArrowboss:
					dataenemy = (struct EnemyInfo*)ispr->custom_data;
					if(KEY_PRESSED(J_DOWN)){
						if(dataenemy->vx != 0){
							SpriteManagerAdd(SpritePuff, ispr->x, ispr->y);
							dataenemy->vx = 0;
						}
						dataenemy->enemy_accel_y = -3;
						return;					
					}else if(dataenemy->vx != 0){
						return;
					}else{
						SpriteManagerRemoveSprite(ispr);
					}
				case SpriteBossfighter:
					dataenemy = (struct EnemyInfo*)ispr->custom_data;
					if(dataenemy->enemy_state == BOSS_DIEING && dataenemy->enemy_state == BOSS_DEAD){
						return;
					}
				case SpriteBosseagle:
				case SpriteCuteagle:
					if (archer_data->hp <= 0){
						update_hud = 1;
						Die();
						return;
					}
					if(archer_state != STATE_HIT && hit_cooldown == MAX_HIT_COOLDOWN) {
 						Hit(1);
					}
				break;
				case SpriteHurricane:
					if (archer_state != STATE_HIT) {	
						if (archer_state == STATE_JUMPING || archer_state == STATE_ASCENDING){
							TranslateSprite(THIS, -2u, -2u);
						}else{
							TranslateSprite(THIS, -2u, -1u);
						}
					}
				break;
				case SpriteArrow:					
					arrowdata = (struct ArrowInfo*)ispr->custom_data;					
					surfing = 40u;
					if (arrowdata->arrowdir != 1 || current_level == 8u){return;}//guardo solo se è orizzontale
					if (archer_accel_y > 0 && THIS->y < (ispr->y-4)){//se sono in salita non collido !
						if (ispr->mirror == V_MIRROR){
							platform_vx = 0-arrowdata->vx;	
						}else{
							platform_vx = arrowdata->vx;	
						}
						archer_accel_y = 0;
						if(archer_state != STATE_NORMAL_PLATFORM){
							archer_state = STATE_NORMAL_PLATFORM;
							THIS->y = ispr->y - 12;
						}
					}
				break;
				case SpriteGate:
					THIS->x--;
				break;				
				case SpriteArrowmother:
					if(archer_accel_y > -2 && archer_state != STATE_HIT){//archer_state != STATE_JUMPING && 
						archer_state = STATE_ARROWMOTHER;
						THIS->lim_y = ispr->y - 11u;
					}
					THIS->lim_x = ispr->x + 4u;
				break;
			}//fine switch ispr->type
		}// fine check collision
		else{
			if(surfing > 0u){
				surfing--;
				if(surfing == 0u){
					platform_vx = 0;
				}
			}
		}
	}//fine SPRITEMANAGER_ITERATE
}

void Next_Amulet() BANKED{
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
	//PlayFx(CHANNEL_1, 60, 0x2d, 0x41, 0xc8, 0xf0, 0xc7);
	arrow_sprite->mirror = THIS->mirror;//flags
	arrow_sprite->x = THIS->x;
	if(arrow_sprite->mirror != V_MIRROR){
		arrow_sprite->x += 4;
	}
	arrow_sprite->y = THIS->y+4;
	struct ArrowInfo* arrow_data = (struct ArrowInfo*)arrow_sprite->custom_data;
	if (archer_data->amulet){arrow_data->type = archer_data->amulet;}
	else{arrow_data->type = 1;}
	if (KEY_PRESSED(J_DOWN) && current_level != 8u){
		arrow_data->arrowdir = 4; // verticale in giu
		arrow_sprite->y += 8;
	}else{
		if (KEY_PRESSED(J_UP) && current_level != 8u){ //verticale in su
			arrow_data->arrowdir = 3;
			arrow_sprite->y -= 3;
		}else{
			arrow_data->arrowdir = 1;
		}
	}
	shoot_cooldown = MAX_SHOOT_COOLDOWN;
	if(current_level_b == 9u){
		switch(archer_data->amulet){
			case 2: //STONE
				quiver &= 0b1111111101;
				final_quiver &= 0b1111111101;
				GoToFinalFightCutscene(archer_data->amulet);
			break;
			case 3: //BLAST
				quiver &= 0b1111111011;
				final_quiver &= 0b1111111011;
				GoToFinalFightCutscene(archer_data->amulet);
			break;
			case 4: //ICE
				quiver &= 0b1111110111;
				final_quiver &= 0b1111110111;
				GoToFinalFightCutscene(archer_data->amulet);
			break;
		}
	}
}

void Jump() {
	if(archer_state != STATE_JUMPING) {
		archer_state = STATE_JUMPING;
		archer_accel_y = -14;
		THIS->coll_w = 6;
		SetSpriteAnim(THIS, anim_jump_up, 12u);
	}
}

void MoveArcher() {
	/*if(archer_state == STATE_HIT){
		if(THIS->mirror == V_MIRROR){
			platform_vx=1;
		}else{
			platform_vx=-1;
		}			
	}*/
	if(platform_vx != 0 || platform_vy != 0){
		tile_collision = TranslateSprite(THIS, platform_vx << delta_time, platform_vy << delta_time);
	}
	if(landing_time == MAX_LANDING_TIME){
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
}

void CheckCollisionTileDoor(){
	tile_collision = GetScrollTile((THIS->x >> 3) +1u, ((THIS->y+3) >> 3) +2u);
	switch(tile_collision){//tile_collision
		case 7u: //EXIT fine level - goto boss!
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
					landing_time = MAX_LANDING_TIME;
					platform_vx = 2;
				}
			break;
			case 119u:
				if(platform_vx != -2){
					landing_time = MAX_LANDING_TIME;
					platform_vx = -2;
				}
			break;
		}
	}
}

void Hit(INT8 damage) {
	landing_time = MAX_LANDING_TIME;
	if (//hit_cooldown < MAX_HIT_COOLDOWN - && 
		((archer_state != STATE_DEAD && archer_state != STATE_HIT) 
		||
		(archer_state == STATE_JUMPING && jump_power < ARCHER_MAX_JUMP_POWER))){
		archer_state = STATE_HIT;
		archer_data->hp -=  damage;
		if (archer_data->hp <= 0){
			update_hud = 1;
			Die();
			return;
		}
		fx_cooldown = 30;
		PlayFx(CHANNEL_1, 60, 0x4c, 0x81, 0x43, 0x73, 0x86);
		update_hud = 1;
		TranslateSprite(THIS, 0, -2 << delta_time);
		SetSpriteAnim(THIS, anim_hit, 24u);
	}
}

void Build_Next_Dialog() BANKED{
	diag_found = Build_Next_Dialog_Banked(THIS);
	if(diag_found){
		if(diag_found < 89u){ 
			drop_player_x = THIS->x >> 3;
			drop_player_y = THIS->y >> 3;
			load_next_d = 1;
		}else{//means no state changing
			// 99u just simple diag message to show from StateGame			
			// 98u means paused
			// 90u suggestion with error sound
			if(diag_found == 90u){
				PlayFx(CHANNEL_1, 60, 0x70a, 0x80, 0xf4, 0x73, 0x86);
			}
			archer_state = STATE_DIAG;
			SetSpriteAnim(THIS, anim_idle, 12u);
			show_diag = 1;	
		}		
	}
}

void DESTROY() {
	
}