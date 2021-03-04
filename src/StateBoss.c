#include "Banks/SetBank7.h"

#include "../res/src/diagnew.h"
#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/mapboss0.h"
#include "../res/src/mapboss1.h"
#include "../res/src/mapboss2.h"
#include "../res/src/gate.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"
#include "custom_datas.h"

extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 collision_tiles[] ;
extern UINT8 amulet ;
extern UINT8 coins ;
extern INT8 ups ;
extern INT8 hp;
extern INT8 load_next_b;
extern INT8 level_tool;
extern UINT16 drop_player_x ;
extern UINT16 drop_player_y ;
extern ARCHER_STATE archer_state;
extern struct ArcherInfo* archer_data;
extern INT8 show_diag;
extern INT8 showing_diag;
extern INT8 is_on_boss;
extern UINT8 updatecounter;

extern void ShowWindow();
extern void ShowWindowDiag();
extern void UpdateHUD();
extern void Build_Next_Dialog();


//Boss
UINT8 current_level_b = 0u;
UINT8 current_map_b = 0u;

const struct MapInfo* boss_0[] = {
	&mapboss0
};
const struct MapInfo* boss_1[] = {
	&mapboss1
};
const struct MapInfo* boss_2[] = {
	&mapboss2
};
const struct MapInfo** bosses[] = {boss_0, boss_1, boss_2};

INT8 boss_hp = 0;
struct EnemyInfo* boss_data_b;

void WriteBBOSSHP();
void populate_boss0();

void Start_StateBoss() {

	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);
	SPRITES_8x16;
	
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	switch(current_level_b){
		case 0:
			level_tool=7;
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteWolf);
		break;
		case 1:
			level_tool=0;
			SpriteManagerLoad(SpriteAlligator);
			SpriteManagerLoad(SpriteAmulet);
			SpriteManagerLoad(SpriteGate);
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteItem);
		break;
		case 2:
			level_tool=0;
			SpriteManagerLoad(SpriteEagle);
			SpriteManagerLoad(SpriteAmulet);
			//SpriteManagerLoad(SpriteItem);
		break;
	}
	
	SHOW_SPRITES;


	//SCROLL
	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	const struct MapInfo** level_maps_b = bosses[current_level_b];
	UINT8 map_w, map_h;
	GetMapSize(level_maps_b[current_map_b], &map_w, &map_h);
	ScrollFindTile(level_maps_b[current_map_b], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x*8, drop_player_y*8);
	InitScroll(level_maps_b[current_map_b], collision_tiles, 0);
	SHOW_BKG;
	
	struct Sprite* boss = 0;
	struct Sprite* scrigno_sprite_boss = 0;
	//INIT BOSS
	switch(current_level_b){
		case 0:
			boss = SpriteManagerAdd(SpriteWolf, 24 << 3, 14 << 3); //34, 12
			boss_data_b = (struct EnemyInfo*)boss->custom_data;
			boss_hp = boss_data_b->hp;
		break;
		case 1:
			boss = SpriteManagerAdd(SpriteAlligator, 21 << 3, 14 << 3);
			boss_data_b = (struct EnemyInfo*)boss->custom_data;
			boss_hp = boss_data_b->hp;
			SpriteManagerAdd(SpriteGate, 42 << 3,  13 << 3);
			SpriteManagerAdd(SpriteGate, 43 << 3,  13 << 3);
			scrigno_sprite_boss = SpriteManagerAdd(SpriteItem, (UINT16) 32u << 3, (UINT16) 2u << 3);
			struct ItemInfo* datascrigno2 = (struct ItemInfo*)scrigno_sprite_boss->custom_data;
			datascrigno2->type = 2;
			datascrigno2->setup = 1u;
		break;
		case 2:
			boss = SpriteManagerAdd(SpriteEagle, 9 << 3, 14 << 3);
			boss_data_b = (struct EnemyInfo*)boss->custom_data;
			boss_hp = boss_data_b->hp;
			/*scrigno_sprite_boss = SpriteManagerAdd(SpriteItem, (UINT16) 6u << 3, (UINT16) 34u << 3);
			struct ItemInfo* datascrigno3 = (struct ItemInfo*)scrigno_sprite_boss->custom_data;
			datascrigno3->type = 2;
			datascrigno3->setup = 1u;*/
		break;
	}
	
	//INIT ARCHER
	if (archer_data->ups > 0 & archer_data->ups != ups){
		ups = archer_data->ups;
	}
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 99u;
	}
	archer_data->ups =ups;
	archer_data->hp = hp;
	archer_data->coins = coins;
	
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow();
	WriteBBOSSHP();
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)

	is_on_boss = 0;
	Build_Next_Dialog();
	
}

void Update_StateBoss() {

	if(show_diag >= 2){ // >=max_diag
		ShowWindow();		
		WriteBBOSSHP();
		return;
	}
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag();
			return;
		}
	}else{
		if (amulet != archer_data->amulet){
			amulet = archer_data->amulet;
			UpdateHUD();
		}
		if (coins != archer_data->coins){
			coins = archer_data->coins;
			UpdateHUD();
		}
		if (hp != archer_data->hp){
			hp = archer_data->hp;
			UpdateHUD();
		}
		if (ups != archer_data->ups){
			ups = archer_data->ups;
			UpdateHUD();
		}

		if (boss_hp != boss_data_b->hp){
			boss_hp = boss_data_b->hp;
			if (boss_hp <= 0){
				boss_hp = 0;
				boss_data_b->hp = 0;
			}
			WriteBBOSSHP();		
		}
		
		if(level_tool == archer_data->tool){
			UpdateHUD();
		}
	}
	
	if(load_next_b){
		switch(load_next_b){
			case 2: //esco dal boss col tool
				is_on_boss = 0;
				SetState(StateGame);
			break;
		}
	}
	
	//UPDATE ARCHER POSX IN BOSS CUSTOM_DATA
	boss_data_b->archer_posx = scroll_target->x;
	
	/*PRINT_POS(13,2);
	Printf("%u", gate_sprite->x);*/
	
	//MOVING BACKGROUND TILES	
	if (current_level_b == 1 & current_map_b == 0){
		UINT8 idxswamp = 0u;
		updatecounter++;
		if (updatecounter < 21) {
			const unsigned char wf0[1] = {123};
			const unsigned char wf1[1] = {124};
			const unsigned char wt0[1] = {112};
			const unsigned char wt1[1] = {113};
			switch(updatecounter){
				case 1:	
					set_bkg_tiles(15u, 12u, 1, 1, wf0); set_bkg_tiles(15u, 13u, 1, 1, wf0); set_bkg_tiles(15u, 14u, 1, 1, wf0);
					set_bkg_tiles(26u, 12u, 1, 1, wf0); set_bkg_tiles(26u, 13u, 1, 1, wf0); set_bkg_tiles(26u, 14u, 1, 1, wf0);
					set_bkg_tiles(37u, 12u, 1, 1, wf0); set_bkg_tiles(37u, 13u, 1, 1, wf0); set_bkg_tiles(37u, 14u, 1, 1, wf0);
					for (idxswamp = 6u; idxswamp < 42u; idxswamp += 1u){
						set_bkg_tiles(idxswamp, 15u, 1, 1, wt0); 
					}
				break;
				case 10:	
					set_bkg_tiles(15u, 12u, 1, 1, wf1); set_bkg_tiles(15u, 13u, 1, 1, wf1); set_bkg_tiles(15u, 14u, 1, 1, wf1);
					set_bkg_tiles(26u, 12u, 1, 1, wf1); set_bkg_tiles(26u, 13u, 1, 1, wf1); set_bkg_tiles(26u, 14u, 1, 1, wf1);
					set_bkg_tiles(37u, 12u, 1, 1, wf1); set_bkg_tiles(37u, 13u, 1, 1, wf1); set_bkg_tiles(37u, 14u, 1, 1, wf1);
					for (idxswamp = 6u; idxswamp < 42u; idxswamp += 1u){
						set_bkg_tiles(idxswamp, 15u, 1, 1, wt1); 
					}
				break;
			}			
		}else{
			updatecounter = 0;
		}
	}
	
	
}

void WriteBBOSSHP(){
	PRINT_POS(10, 0);	
	if(boss_hp > 0){
		Printf("BOSS>%d", boss_hp);
	}else{
		Printf("       ");
		UpdateHUD();
	}
}