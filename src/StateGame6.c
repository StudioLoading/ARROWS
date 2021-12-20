#include "Banks/SetBank15.h"

#include <stdbool.h>

#include "../res/src/window6.h"
#include "../res/src/diagnew6.h"
#include "../res/src/font.h"
#include "../res/src/tiles6.h"
#include "../res/src/tilesanims.h"
#include "../res/src/map60.h"
#include "../res/src/map61.h"
#include "../res/src/archer.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"
#include "TileAnimations.h"
#include "Dialogs.h"
#include "sgb_palette.h"


const UINT8 const collision_tiles6[] = {2, 7, 10, 11, 12, 13, 14, 15, 16, 17, 20, 26, 35, 36, 37, 38, 39, 41, 43, 44, 61, 62, 64, 111, 119, 0};//numero delle tile di collisione seguito da zero finale

extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next;
extern INT8 load_next_b;
extern INT8 load_next_s;
extern INT8 load_next_d;
extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_boss;
extern INT8 is_on_secret;
extern INT8 archer_tool;
extern UINT8 current_camera_state;
extern UINT8 current_camera_counter;
extern UINT8 diag_found;

extern INT8 drop_player_x ;
extern INT8 drop_player_y ;
extern INT8 show_diag;
extern INT8 showing_diag;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern struct Sprite* platform_sprite;
extern struct Sprite* enemies_0;
extern struct Sprite* enemies_1;
extern struct Sprite* enemies_2;
extern struct Sprite* enemies_3;
extern struct Sprite* scrigno_coin;
extern struct Sprite* scrigno_dcoin;
extern struct Sprite* scrigno_shield;
extern struct Sprite* scrigno_up;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern INT8 spawning_triggered;
extern UINT8 updatecounter;
extern INT8 platform_vx;
extern bool LCD_Installed;
extern UINT8 thunder_delay;
extern INT8 update_hud;
extern INT8 spawning_counter;

//Maps
const struct MapInfo* const map_6[] = {
	&map60, &map61
};

const struct MapInfo** const maps6[] = {map_6};


void UpdateHUD6();
void ShowWindow6();
void ShowWindowDiag6();
void set_window_y6(UBYTE y);
void LCD_isr6();
void spawn_enemy6(UINT8 spriteType, UINT16 posx, UINT16 posy);
void spawn_item6(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);


void Start_StateGame6() {
	
	is_on_boss = -1;
	thunder_delay = 80u;
	current_camera_state = 0u;
	current_camera_counter = 0u;
	spawning_triggered = 0;
	
	if (current_level < 3u){
		SetState(StateGame);
	}else if (current_level < 5u){
		SetState(StateGame3);
	}
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpriteItem);
	SpriteManagerLoad(SpritePlatform);
	SpriteManagerLoad(SpriteStalagmite);
	SpriteManagerLoad(SpriteStalattite);
	SpriteManagerLoad(SpritePenguin);
	SpriteManagerLoad(SpritePuff);
	//LOAD SPRITES OF THE MAP
	switch (current_level){
		case 5u:
			SpriteManagerLoad(SpriteGate);
			SpriteManagerLoad(SpriteIceplat);
			if(sgb_check()){
				set_sgb_palette01_ICE();
				set_sgb_palette_statusbar();
			}
		break;		
	}		
	SHOW_SPRITES;

	//SCROLL
	//if (current_level == 2u & current_map == 0u)
	scroll_bottom_movement_limit = 62;

	const struct MapInfo** lvls6 = maps6[current_level-5u];
	UINT8 map_w6;
	UINT8 map_h6;
	GetMapSize(lvls6[current_map], &map_w6, &map_h6);
	if (load_next_s == -1){ //COME FROM STATE SECRET
		ScrollFindTile(lvls6[current_map], 45, 0, 0, map_w6, map_h6, &drop_player_x, &drop_player_y);
	}else if(load_next || load_next_d == 0){
		spawning_triggered = 0;
		spawning_counter = 0;
		ScrollFindTile(lvls6[current_map], 9, 0, 0, map_w6, map_h6, &drop_player_x, &drop_player_y);		
	}//else COME FROM THE DIALOG STATE, I ALREADY SAVED PLAYER COORDS IN drop_player_x/y
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll(lvls6[current_map], collision_tiles6, 0);
	SHOW_BKG;
	
	//INIT ARCHER
	is_on_boss = -1;	
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 0u;
		archer_tool = 0;
		hp = 50;
	}	
	archer_data->hp = hp;
	archer_data->ups = ups;
	archer_data->coins = coins;
	archer_data->tool = archer_tool;
	archer_state = STATE_JUMPING;
	
	UpdateHUD6();
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow6();
	
	//SET LEVEL TOOL
	/*switch(current_level){
		case 0u:
			switch(current_map){
				case 0u:
					level_tool = 6;
				break;
			}
		break;
		case 1:
			switch(current_map){
				case 1u:
					level_tool = 7;
				break;
			}
		break;
	}*/
	
	//INIT SPAWNING
	enemies_0 = 0;
	enemies_1 = 0;
	enemies_2 = 0;
	enemies_3 = 0;
	if (load_next_s > -1 && load_next_d == 0){ // NON vengo da secret nè da dialogo!
		switch(current_level){
			case 5u:
				switch(current_map){
					case 1u:
						spawn_item6(scrigno_dcoin, 3u, 16u, 7, 1);//1coin 2hp 3up 7dcoin
						spawn_item6(scrigno_dcoin, 15u, 10u, 2, 0);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpritePenguin, 9u, 16u);
					break;
				}
			break;
		}
	}
	
	if(load_next_d){
		load_next_d = 0;
	}else if(load_next_s == -1){
		load_next_s = 0;
	}else{//copiato dallo SpritePlayer quando chiedo il tip
		diag_found = Build_Next_Dialog_Banked(scroll_target);
		if(diag_found){			
			archer_state = STATE_DIAG;
			show_diag = 1;	
		}
	}
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
	if (!LCD_Installed) { 
		CRITICAL {
			add_LCD(LCD_isr6);
			set_interrupts(VBL_IFLAG | LCD_IFLAG);
			STAT_REG |= 0x40; 
			set_window_y6(144-8);
		}
	    LCD_Installed = true; 
	}
	
}

void Update_StateGame6() {
	
	thunder_delay -= 1u;
	
	if(load_next_d){
		switch(load_next_d){
			case 1: //vado allo StateDiag
				diag_found = Build_Next_Dialog_Banked(scroll_target);
				load_next_d = 2;
				SetState(StateDiag);
			break;
			case 2:
				load_next_d = 0;
				if(is_on_boss == 0){
					load_next_b = 1;
				}
			break;
		}		
	}
	
	if(load_next) {
		switch(load_next){
			case 1: //stage
			case -1:
				current_map += load_next;
			break;
		}
		load_next = 0;
		switch(current_level){
			case 0:
			case 1:
			case 2:
				SetState(StateGame);	
			break;
			case 3:
			case 4:
				SetState(StateGame3);
			break;
			case 5:
			case 6:
				SetState(StateGame6);
			break;
			case 7:
			break;
		} 
	}
	
	if(load_next_s == 1){
		load_next_s = 0;
		is_on_secret = 1;
		SetState(StateSecret);
	}
	
	if(load_next_b){
		switch(load_next_b){
			case 1: //vado allo StateBoss
				if(archer_state != STATE_DIAG){
					load_next_b = 0;
					SetState(StateBoss);//StateBoss
				}
			break;
			/*case 2: // provengo dal boss, vado al next level
			break;*/
		}
	}	
	
	// SPAWNING
	// !SPRITE_GET_VMIRROR(scroll_target) && 
	//if(archer_state != STATE_HIT && platform_vx == 0u){
	switch(current_level){
		case 5u: // Ice Cave -> See King
			switch(current_map){
				case 0u:
					//dropping drop
					if (scroll_target->x > (UINT16) 8u << 3 && scroll_target->x < (UINT16) 28u << 3){
						if(thunder_delay == 0u){
							SpriteManagerAdd(SpriteStalagmite, (UINT16) 16u << 3, (UINT16) 7u << 3);
						}
					}
					if(scroll_target->x < (UINT16) 13u << 3 && spawning_counter == 0){
						spawn_item6(scrigno_up, 8u, 8u, 7, 1);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpriteStalattite, 4u, 5u);
						spawn_enemy6(SpritePenguin, 5u, 11u);
						spawning_counter++;
					}
					/*if(scroll_target->x < (UINT16) 24u << 3 && (spawning_counter == 0 || spawning_counter == 1)){
						spawn_enemy6(SpriteStalattite, 18u, 5u);
						spawning_counter = 2;
					}*/
					if(scroll_target->x > (UINT16) 26u << 3 && spawning_counter < 3){
						spawn_enemy6(SpriteStalattite, 27u, 5u);
						spawning_counter = 3;
					}
					if(scroll_target->x > (UINT16) 29u << 3 && spawning_counter == 3){
						spawn_enemy6(SpriteStalattite, 33u, 5u);
						spawn_enemy6(SpritePenguin, 39u, 11u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 30u << 3 && spawning_counter == 4){
						spawn_enemy6(SpriteStalattite, 34u, 5u);
						spawning_counter++;
					}						
					if(scroll_target->x > (UINT16) 49 << 3 && scroll_target->x < (UINT16) 69u << 3){
						if(thunder_delay == 0u){
							SpriteManagerAdd(SpriteStalagmite, (UINT16) 59u << 3, (UINT16) 10u << 3);
						}
					}
					if(scroll_target->x > (UINT16) 54u << 3 && spawning_counter == 5){
						struct Sprite* gate = SpriteManagerAdd(SpriteGate, (UINT16) 64u << 3, (UINT16) 12u << 3);
						struct EnemyInfo* gdata = (struct EnemyInfo*)gate->custom_data;
						gdata->vx = 4;
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 63u << 3 && spawning_counter == 6){
						spawn_item6(scrigno_coin, 73u, 11u, 1, 1); //1coin 2hp 3up 7dcoin
						spawn_enemy6(SpritePenguin, 73u, 11u);
						spawning_counter++;				
					}
					if(scroll_target->x > (UINT16) 70u << 3 && spawning_counter == 7){
						spawn_enemy6(SpriteStalattite, 77u, 5u);
						spawn_enemy6(SpritePenguin, 83u, 11u);
						spawning_counter++;
					}		
					if(scroll_target->x > (UINT16) 70u << 3 && scroll_target->x < (UINT16) 90u << 3){
						if(thunder_delay == 0u){
							spawn_enemy6(SpriteStalagmite, 80u, 8u);
						}
					}
					if(scroll_target->x > (UINT16) 112u << 3 && spawning_counter == 8){
						spawn_item6(scrigno_dcoin, 120u, 3u, 3, 1);//1coin 2hp 3up 7dcoin
						spawn_item6(scrigno_coin, 127u, 12u, 1, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 138u << 3 && spawning_counter == 9){
						spawn_enemy6(SpritePenguin, 134u, 12u);
						spawn_item6(scrigno_up, 142u, 8u, 3, 0);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpritePenguin, 148u, 12u);
						spawning_counter++;
					}					
					if(scroll_target->x > (UINT16) 166u << 3){
						if(thunder_delay == 0u){
							SpriteManagerAdd(SpriteStalagmite, (UINT16) 174u << 3, (UINT16) 6u << 3);
						}
					}
					if(scroll_target->x > (UINT16) 155u << 3 && spawning_counter == 10){
						spawn_enemy6(SpritePenguin, 160u, 10u);
						spawn_enemy6(SpritePenguin, 164u, 14u);
						spawning_counter++;
					}
					if(scroll_target->x > (UINT16) 168u << 3 && spawning_counter == 11){
						spawn_item6(scrigno_dcoin, 176u, 6u, 7, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
				break;
				case 1u:
					if (scroll_target->x > (UINT16) 20u << 3 && spawning_counter == 0){
						spawn_enemy6(SpriteIceplat, 33u, 15u);
						spawn_enemy6(SpriteIceplat, 38u, 13u);
						spawn_enemy6(SpritePlatform, 45u, 10u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 45u << 3 && spawning_counter == 1){
						spawn_enemy6(SpriteIceplat, 50u, 13u);
						spawn_enemy6(SpriteIceplat, 55u, 15u);
						spawn_enemy6(SpritePlatform, 61u, 14u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 70u << 3 && spawning_counter == 2){
						spawn_enemy6(SpriteStalattite, 72u, 5u);
						spawn_enemy6(SpritePenguin, 80u, 12u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 72u << 3 && spawning_counter == 3){						
						spawn_enemy6(SpriteStalattite, 77u, 5u);
						spawn_enemy6(SpritePenguin, 84u, 12u);						
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 88u << 3 && spawning_counter == 4){
						spawn_enemy6(SpriteIceplat, 98u, 14u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 98u << 3 && spawning_counter == 5){
						spawn_enemy6(SpriteIceplat, 108u, 12u);					
						spawn_enemy6(SpriteStalattite, 108u, 5u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 125u << 3 && spawning_counter == 6){
						spawn_enemy6(SpriteIceplat, 137u, 12u);					
						spawn_enemy6(SpriteIceplat, 134u, 14u);					
						spawn_item6(scrigno_shield, 134u, 10u, 2, 1);//1coin 2hp 3up 7dcoin
						//spawn_item6(scrigno_up, 129u, 5u, 2, 0);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 151u << 3 && spawning_counter == 7){
						spawn_enemy6(SpriteIceplat, 160u, 11u);					
						spawn_enemy6(SpriteIceplat, 162u, 13u);					
						//spawn_enemy6(SpriteStalattite, 155u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 170u << 3 && spawning_counter == 8){
						spawn_enemy6(SpriteIceplat, 175u, 15u);					
						spawn_enemy6(SpriteIceplat, 179u, 12u);				
						spawn_enemy6(SpriteStalattite, 171u, 4u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 190u << 3 && spawning_counter == 9){
						spawn_enemy6(SpriteIceplat, 197u, 8u);
						spawn_enemy6(SpriteIceplat, 199u, 9u);						
						spawn_item6(scrigno_shield, 194u, 5u, 2, 1);//1coin 2hp 3up 7dcoin
						spawn_enemy6(SpriteIceplat, 201u, 10u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 213u << 3 && spawning_counter == 10){
						spawn_enemy6(SpritePenguin, 221u, 12u);
						spawning_counter++;
					}
					if (scroll_target->x > (UINT16) 222u << 3 && spawning_counter == 11){
						spawn_enemy6(SpritePenguin, 229u, 12u);
						spawn_item6(scrigno_shield, 229u, 11u, 7, 1);//1coin 2hp 3up 7dcoin
						spawning_counter++;
					}						
					if (scroll_target->x > (UINT16) 207u << 3){							
						switch(thunder_delay){
							case 40u:
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) + 6u, 5u);
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) + 1u, 5u);
							break;
							case 80u:
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) + 4u, 5u);
							break;
							case 20u:
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3), 5u);
								spawn_enemy6(SpriteStalattite, (scroll_target->x >> 3) - 1u, 5u);
							break;
						}
					}
				break;
			}
		break;
	}
	
	if(thunder_delay == 0u){
		thunder_delay = 104u;
	}
	
	//MOVING BACKGROUND TILES
	updatecounter++;
	if (updatecounter < 60) {
		switch(updatecounter){
			case 20:
			case 40:
			case 59:
				AnimSliders0();
			break;
			case 10:
			case 30:
			case 50:
				AnimSliders1();
			break;
		}	
	}else{
		updatecounter = 0;
	}	
	
	//DIAG MANAGEMENT
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow6();
		return;
	}	
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag6();
			return;
		}
	}

	//HUD MANAGEMENT
	if (update_hud != 0){
		update_hud = 0;
		hp = archer_data->hp;
		amulet = archer_data->amulet;
		coins = archer_data->coins;
		ups = archer_data->ups;
		UpdateHUD6();
	}
}

void UpdateHUD6(){
	hp = archer_data->hp;
	amulet = archer_data->amulet;
	coins = archer_data->coins;
	ups = archer_data->ups;
	archer_tool = archer_data->tool;
	//write amulet
	PRINT_POS(18,0);
	switch (archer_data->amulet){
		//case 1: Printf("$"); break;
		case 2: Printf("["); break;
		case 3: Printf("#"); break;
		case 4: Printf("]"); break;
		case 5: Printf("@"); break;
		default: Printf("$"); break;
	}
	//write coins
	if (is_on_boss < 0){	
		if (archer_data->coins == 100u){
			archer_data->coins = 0u;
			coins = 0u;
			archer_data->ups += 1;	
		}
		PRINT_POS(12, 0);
		if (archer_data->coins > 9){
			Printf("%d", archer_data->coins);
		}else{
			Printf("0%d", archer_data->coins);
		}	
	}
	//write hp
	PRINT_POS(7, 0);
	if(hp < 0){
		Printf("XX");
	}else if (hp < 10){ // archer_data->hp < 10 &&
		Printf("0");
		PRINT_POS(8, 0);
		Printf("%d", hp);
	}else if (hp >= 100){ // archer_data->hp >= 100 &&
		Printf("99");	
	}else if (hp > 9){ // archer_data->hp > 9 && archer_data->hp < 100 && 
		Printf("%d", hp);
	}
	//write tool
	if (archer_data->tool == level_tool){
		switch(level_tool){
			case 6: //key
				PRINT_POS(16, 0);
				Printf("{");
			break;
			case 7: //wrench
				PRINT_POS(16, 0);
				Printf("<");
			break;
		}
	}
	//write ups
	PRINT_POS(2, 0); //up
	if (archer_data->ups > 9){Printf("%d", archer_data->ups);}
	else if (archer_data->ups >= 0){Printf("0%d", archer_data->ups);}
}

void ShowWindow6(){
	set_window_y6(144 - 8);
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, &window6);
	SHOW_WIN;
	
	UpdateHUD6();
}

void ShowWindowDiag6(){
	if (showing_diag == 0){
		HIDE_WIN;
		set_window_y6(144 - 32);
		WX_REG = 0;
		WY_REG = 144 - 32; //40
		InitWindow(0, 0, &diagnew6);
		SHOW_WIN;
		
		PRINT_POS(1,0);
		Printf(d1);
		PRINT_POS(1,1);
		Printf(d2);
		PRINT_POS(1,2);
		Printf(d3);
		PRINT_POS(1,3);
		Printf(d4);
		
		showing_diag = 1;
	}	
}

void LCD_isr6() NONBANKED {
    if (LYC_REG == 0) {
        if (WY_REG == 0) HIDE_SPRITES; else SHOW_SPRITES; 
        LYC_REG = WY_REG;
    } else {
        HIDE_SPRITES; 
        LYC_REG = 0;
    }
}

void set_window_y6(UBYTE y) {
    WX_REG = 7u;
    LYC_REG = WY_REG = y;
    if (y < 144u) SHOW_WIN; else { HIDE_WIN; LYC_REG = 160u; } 
}

void spawn_enemy6(UINT8 spriteType, UINT16 posx, UINT16 posy){
	spawning_triggered+=1;
	if(spriteType == SpritePlatform){
		platform_sprite = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
		return;
	}
	SpriteManagerRemoveSprite(enemies_3);
	enemies_3 = enemies_2;
	enemies_2 = enemies_1;
	if(enemies_0 == 0 || enemies_1 == 0 || enemies_2 == 0 || enemies_3 == 0){
		enemies_0 = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	}
}

void spawn_item6(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
	spawning_triggered++;
	SpriteManagerRemoveSprite(itemin);
	struct Sprite* itemnew = SpriteManagerAdd(SpriteItem, (UINT16) posx << 3, (UINT16) posy << 3);
	struct ItemInfo* datascrigno = (struct ItemInfo*)itemnew->custom_data;
	datascrigno->setup = 1u;
	if(scrigno){
		//se la vita del player è 100% e vorrei spawnare scudo, spawno dcoin !
		if(content_type == 2 && archer_data->hp == 100){
			content_type = 7;
		}
		datascrigno->content_type = content_type;
		datascrigno->type = 10;
	}else{
		datascrigno->type = content_type;
	}
}
