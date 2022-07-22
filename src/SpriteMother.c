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

#define MOTHER_MAX_HIT_COOLDOWN 64
#define MOTHER_MAX_DIAG_COOLDOWN 60
#define MOTHER_MAX_LANDING_TIME 24
#define MOTHER_MAX_ACCEL_Y_TO_LAND_ANIMATION 36

const UINT8 anim_mother_idle[] = {4, 0, 0, 0, 3};
const UINT8 anim_mother_jump[] = {1, 4};
const UINT8 anim_mother_jump_up[] = {1, 6};
const UINT8 anim_mother_walk[] = {4, 7, 4, 6, 5, 4};
const UINT8 anim_mother_shoot[] = {3,2,1,2};


extern UINT8 amulet;
extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern INT8 show_diag;
extern INT8 showing_diag;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern Sprite* platform_sprite;
extern Sprite* enemies_0;
extern Sprite* enemies_1;
extern Sprite* enemies_2;
extern Sprite* enemies_3;
extern Sprite* scrigno_coin;
extern Sprite* scrigno_dcoin;
extern Sprite* scrigno_shield;
extern Sprite* scrigno_up;
extern Sprite* archer_player;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern INT8 spawning_counter;
extern UINT8 updatecounter;
extern INT8 update_hud;
extern INT8 jump_power;
extern INT8 fx_cooldown;
extern UINT8 thunder_delay;
extern UINT16 apx;
extern UINT16 apy;
extern UINT16 apx_mirrored;
extern INT8 platform_vx;
extern INT8 platform_vy;

extern const INT8 MAX_HP;
extern const UINT8 SHIELD_TILE;
extern const UINT8 SKULL_TILE;
extern const UINT8 EMPTY_TILE;
extern UINT8 tile_collision;
extern UINT8 quiver;
extern INT16 archer_accel_y;
extern INT8 shoot_cooldown;
extern INT8 death_cooldown;
extern INT8 hit_cooldown;
extern INT8 diag_cooldown;
extern INT8 landing_time;
extern INT8 is_on_boss;
extern INT8 is_on_secret;
extern UINT8 paused;
extern UINT8 diag_found;
extern UINT8 current_level;
extern UINT8 current_map;
extern UINT8 current_level_b;


void MoveMother();
void JumpMother();
void ShootMother();

void START() {
    archer_accel_y = 0;
    shoot_cooldown = 0;
    platform_vx = 0;
    platform_vy = 0;
	archer_data = (struct ArcherInfo*)THIS->custom_data;
	platform_vx = 0;
	platform_vy = 0;
    death_cooldown = 0;
    hit_cooldown = 0;
	if(archer_data->amulet != amulet){
		archer_data->amulet = 1u;
	}
	death_cooldown = 1;
	hit_cooldown = MOTHER_MAX_HIT_COOLDOWN;
	jump_power = 0;
	update_hud = 1;

	archer_state = STATE_NORMAL;
	landing_time = MOTHER_MAX_LANDING_TIME;
    diag_cooldown = MOTHER_MAX_DIAG_COOLDOWN;
    SetSpriteAnim(THIS, anim_mother_idle, 8u);
}

void UPDATE(){
	switch(archer_state){
		case STATE_DIAG:
			if(diag_cooldown == 0){
				if (show_diag == -1){ //NON TOCCARE
					if(is_on_boss == -1) ResumeMusic;
					show_diag = 0;
					diag_cooldown = MOTHER_MAX_DIAG_COOLDOWN;
					archer_state = STATE_NORMAL;
				}else if(paused && KEY_TICKED(J_START)){
					if(is_on_boss == -1) ResumeMusic;
					set_sgb_palette_statusbar();
					diag_cooldown = MOTHER_MAX_DIAG_COOLDOWN;
					show_diag += 1;
					SetSpriteAnim(THIS, anim_mother_idle, 12u);
					paused = 0;
				} 
				else if(!paused){				
					if(KEY_TICKED(J_B) || KEY_TICKED(J_A) || KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)){ //show_diag < max_diag
						if(is_on_boss == -1) ResumeMusic;	
						set_sgb_palette_statusbar();
						diag_cooldown = MOTHER_MAX_DIAG_COOLDOWN;
						show_diag += 1;
						SetSpriteAnim(THIS, anim_mother_idle, 12u);
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
			SetSpriteAnim(THIS, anim_mother_idle, 8u);
			show_diag = 1;
		}	
		return;
	}
	
    switch(archer_state) {
		case STATE_ASCENDING:
			MoveMother();
			THIS->y--;
		break;
		case STATE_NORMAL:
            if(jump_power){
				jump_power = 0;
			}
			MoveMother();
            //CheckMotherCollisionTile();
			if(shoot_cooldown) {
				SetSpriteAnim(THIS, anim_mother_shoot, 12u);
			}else if(!KEY_PRESSED(J_DOWN)){
                if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT)) {
                    landing_time = MOTHER_MAX_LANDING_TIME;
                    SetSpriteAnim(THIS, anim_mother_walk, 16u);
                }else{
                    if (archer_state == STATE_NORMAL_PLATFORM){
                        //SetSpriteAnim(THIS, anim_flying, 16u);
                    }else{
                        if(landing_time < MOTHER_MAX_LANDING_TIME){
                            //SetSpriteAnim(THIS, anim_shield, 16u);
                            landing_time++;
                        }else{
                            SetSpriteAnim(THIS, anim_mother_idle, 8u);
                        }
                    }					
                }
			}
            if(KEY_TICKED(J_A)){//&& landing_time == MAX_LANDING_TIME){
				fx_cooldown = 30;
				landing_time = MOTHER_MAX_LANDING_TIME;
				PlayFx(CHANNEL_1, 50, 0x27, 0x40, 0x43, 0x68, 0x86);
				JumpMother();
			}
			if(shoot_cooldown) {
				shoot_cooldown -= 1;
			} else {
				if(KEY_TICKED(J_B) && (!KEY_PRESSED(J_DOWN) || ((KEY_PRESSED(J_DOWN) && archer_state == STATE_JUMPING)))) {
					ShootMother();
				}
			}
            //Check falling
			if((archer_accel_y >> 3) > 1 && archer_state != STATE_JUMPING && archer_state != STATE_NORMAL_PLATFORM){
				archer_state = STATE_JUMPING;
			}
        break;
		case STATE_JUMPING:
			if(shoot_cooldown) {
				shoot_cooldown -= 1;
			}
			else{
				if(KEY_TICKED(J_B)) {
					ShootMother();
				}else{
					if (archer_accel_y < 4){									
						if(KEY_PRESSED(J_A)) {
							if (jump_power < 4){
								jump_power += 1;
								archer_accel_y -= 2;
							}
						}else if (KEY_RELEASED(J_A)){
							jump_power += 1;
							archer_accel_y = 0;
						}
						SetSpriteAnim(THIS, anim_mother_jump_up, 33u);
					}else{
						jump_power = 0;
						archer_accel_y += 1;
						SetSpriteAnim(THIS, anim_mother_jump, 32u);
					}
				}
			}
			if(platform_vx > 0){
				platform_vx--;
			}else if (platform_vx < 0){
				platform_vx++;
			}
			platform_vy = 0;
			MoveMother();
		break;
    }
	if( archer_state != STATE_LADDER && archer_state != STATE_HIT && archer_state != STATE_DEAD) {
		//Simple gravity physics 
		if(archer_accel_y < 24) {
			archer_accel_y += 1;
		}
		tile_collision = TranslateSprite(THIS, 0, archer_accel_y  >> 4 );
		if(tile_collision) {
			if(archer_state == STATE_JUMPING && archer_accel_y > 0) {
				archer_state = STATE_NORMAL;
				if(archer_accel_y > MOTHER_MAX_ACCEL_Y_TO_LAND_ANIMATION){
					landing_time = 0;
				}
			}
			archer_accel_y = 0;	
			CheckMotherCollisionTile();
		}
	}
	
	if (GetScrollTile((THIS->x >> 3), (THIS->y >> 3)) == 99u){ //tile di sollevamento, è bg quindi non posso fare altrimenti
		archer_accel_y = -2;
		archer_state = STATE_ASCENDING;
	}else if (archer_state == STATE_ASCENDING){
		archer_accel_y = -12;
		archer_state = STATE_NORMAL;
	}
}

void CheckMotherCollisionTile() {
	if(archer_state != STATE_HIT){
		switch(tile_collision) {
			case 10u:
				if(current_level != 6u){
					return;
				}
			case 2u: //2 (e 10 del liv6) sono spuncioni alti, se li scranio, cado di 2-3px no ?
				THIS->y += 4u;
				//Hit(1);
			case 20u:
				if(current_level == 6u){
					//Hit(1);
					return;
				}
			case 23u:
			case 29u:
				//Hit(1);
			break;
			case 38u:
			case 39u:
				if(current_level == 5u || (current_level_b == 5u && is_on_boss > 0)){
					//Hit(1);				
				}
			break;
			case 40u: //skull of death
				//Hit(1);
			break;		
			case 64u: //skull in ice cave
				if(current_level == 5u){
					//Hit(1);
				}
			break;
			case 111u:
				if(platform_vx != 2){
					landing_time = MOTHER_MAX_LANDING_TIME;
					platform_vx = 2;
				}
			break;
			case 119u:
				if(platform_vx != -2){
					landing_time = MOTHER_MAX_LANDING_TIME;
					platform_vx = -2;
				}
			break;
		}
	}
}

void MoveMother(){
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
	if(landing_time == MOTHER_MAX_LANDING_TIME){
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

void JumpMother(){
	if(archer_state != STATE_JUMPING) {
		archer_state = STATE_JUMPING;
		archer_accel_y = -14;
		THIS->coll_w = 6;
		SetSpriteAnim(THIS, anim_mother_jump_up, 12u);
	}
}

void ShootMother(){
	SetSpriteAnim(THIS, anim_mother_shoot, 12u);
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

void DESTROY(){

}