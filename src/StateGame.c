#include "Banks/SetBank7.h"

#include "../res/src/window.h"
#include "../res/src/diagnew.h"
#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/map2.h"
#include "../res/src/mapsewer.h"
#include "../res/src/mapsewer2.h"
#include "../res/src/map3.h"
#include "../res/src/map3tree.h"
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


const UINT16 bg_palette[] = {PALETTE_FROM_HEADER(tiles)};

const UINT16 sprites_palette[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

const UINT8 collision_tiles[] = {1, 2, 3, 6, 7, 8, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 29, 35, 40, 41, 42, 46, 74, 75, 76, 77, 81, 85, 86, 100, 101, 104, 111, 119, 0};//numero delle tile con zero finale
UINT8 amulet = 0u;
UINT8 coins = 30u;
INT8 ups = 3;
INT8 hp = 100;
INT8 archer_tool = 0;
INT8 level_tool = -1;
INT8 load_next = 0;
INT8 load_next_s = 0;
INT8 load_next_b = 1;
UINT8 current_level = 0u;
UINT8 current_map = 0u;
UINT16 drop_player_x = 0u;
UINT16 drop_player_y = 0u;
INT8 show_diag = 0;
INT8 showing_diag = 0;
extern UINT8 updatecounter; //da StateCredit
struct Sprite* platform_sprite = 0;
struct Sprite* snake1 = 0;
struct Sprite* snake2 = 0 ;
struct Sprite* snake3 = 0 ;
struct Sprite* snake4 = 0 ;
struct Sprite* scrigno_coin = 0;
struct Sprite* scrigno_dcoin = 0;
struct Sprite* scrigno_shield = 0;
struct Sprite* scrigno_up = 0;
unsigned char d1[18];
unsigned char d2[18];
unsigned char d3[18];
unsigned char d4[18];

const struct MapInfo* level_1[] = {
	&map,
	&map2
};
const struct MapInfo* level_2[] = {
	&mapsewer2,
	&mapsewer
};
const struct MapInfo* level_3[] = {
	&map3,
	&map3tree
};
const struct MapInfo** levels[] = {level_1, level_2, level_3};

extern struct ArcherInfo* archer_data;
extern ARCHER_STATE archer_state;
extern INT8 is_on_boss;
extern UINT8 current_level_b;
extern UINT8 current_map_b;

void UpdateHUD();
void ShowWindow();
void ShowWindowDiag();
struct Sprite* spawn_enemy(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy);
struct Sprite* spawn_item(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno);

void Start_StateGame() {
	
	if (current_level > 2u){
		SetState(StateGame4);
	}
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpritePlatform);
	SpriteManagerLoad(SpriteItem);
	switch (current_level){
		case 0u:
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteScorpion);
			SpriteManagerLoad(SpritePorcupine);
		break;
		case 1u:
			SpriteManagerLoad(SpriteKey);
			SpriteManagerLoad(SpriteRat);
			SpriteManagerLoad(SpriteSpider);
		break;
		case 2u:
			SpriteManagerLoad(SpriteSpider);
			SpriteManagerLoad(SpriteEnemy);
			SpriteManagerLoad(SpriteBird);
		break;		
	}
	SHOW_SPRITES;

	//SCROLL
	if (current_level == 2u & current_map == 0u){
		scroll_bottom_movement_limit = 82;//customizzo altezza archer sul display
	}else{
		scroll_bottom_movement_limit = 62;//customizzo altezza archer sul display
	}

	const struct MapInfo** lvls = levels[current_level];
	UINT8 map_w;
	UINT8 map_h;
	GetMapSize(lvls[current_map], &map_w, &map_h);
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
		ScrollFindTile(lvls[current_map], 45, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}else{ //vengo da altra map
		ScrollFindTile(lvls[current_map], 9, 0, 0, map_w, map_h, &drop_player_x, &drop_player_y);
	}
	scroll_target = SpriteManagerAdd(SpritePlayer, drop_player_x << 3, drop_player_y << 3);
	InitScroll(lvls[current_map], collision_tiles, 0);
	SHOW_BKG;
	
	//INIT ARCHER
	is_on_boss = -1;
	if (archer_data->ups & archer_data->ups != ups){
		ups = archer_data->ups;
	}
	if (archer_data->tool & archer_data->tool != archer_tool){
		archer_tool = archer_data->tool;
	}
	if (ups == -1){ //cioè vengo dal gameOver
		ups = 3;
		coins = 0u;
		archer_tool = 0;
		hp = 50;
	}
	
	archer_data->ups = ups;
	archer_data->hp = hp;
	archer_data->coins = coins;
	archer_data->tool = archer_tool;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	ShowWindow();
	
	memcpy(d1, "DIALOG1", 18);
	memcpy(d2, "DIALOG2", 18);
	memcpy(d3, "DIALOG3", 18);
	memcpy(d4, "DIALOG4", 18);
	
	//INIT SPAWNING
	switch(current_level){
		case 0u:
			switch(current_map){
				case 0u:
					level_tool = 6;
					//wrench
					if(archer_data->tool == 0){
						if (!load_next_s){ 
							scrigno_coin = spawn_item(scrigno_coin, 9u, 12u, 1, 1);
							scrigno_shield = spawn_item(scrigno_shield, 9u, 22u, 2, 1);
							scrigno_dcoin = spawn_item(scrigno_dcoin, 6u, 4u, 7, 1);
							scrigno_up = spawn_item(scrigno_up, 31u, 27u, 3, 0);
						}
					}
				break;
			}
		break;
		case 1u:
			switch(current_map){
				case 1u:
					level_tool = 6;
					if (!load_next_s){ // se non vengo da secret. se no si arricchisce a caso senza freni
						scrigno_shield = spawn_item(scrigno_shield, 42u, 21u, 2, 1);
					}
				break;
			}
		break;
		case 2u:
			switch(current_map){
				case 0u:
					if (!load_next_s){ // se non vengo da secret. se no si arricchisce a caso senza freni
						scrigno_up = spawn_item(scrigno_up, 46u, 0u, 3, 1);
						scrigno_dcoin = spawn_item(scrigno_dcoin, 3u, 1u, 7, 1);
					}
				break;
			}
		break;
	}
	
	if (load_next_s){ //vengo da secret!
		load_next_s = 0;
	}
	if(archer_tool == level_tool){
		UpdateHUD();
	}

	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	
}

void ShowWindow(){
	showing_diag = 0;
	show_diag = -1;
	HIDE_WIN;
	//WINDOW
	WX_REG = 7;
	WY_REG = 144 - 8;
	InitWindow(0, 0, &window);
	SHOW_WIN;
	
	UpdateHUD();
}

void ShowWindowDiag(){
	if (showing_diag == 0){	
		HIDE_WIN;
		//WINDOW
		WX_REG = 7;
		WY_REG = 144 - 48; //40
		InitWindow(0, 0, &diagnew);
		SHOW_WIN;
	}
	PRINT_POS(1,1);
	Printf(d1);
	PRINT_POS(1,2);
	Printf(d2);
	PRINT_POS(1,3);
	Printf(d3);
	PRINT_POS(1,4);
	Printf(d4);
	
	if (showing_diag == 0){
		showing_diag = 1;
	}
}

struct Sprite* spawn_enemy(struct Sprite* enem, UINT8 spriteType, UINT16 posx, UINT16 posy){
	SpriteManagerRemoveSprite(enem);
	enem = SpriteManagerAdd(spriteType, (UINT16) posx << 3, (UINT16) posy << 3);
	return enem;
}

struct Sprite* spawn_item(struct Sprite* itemin, UINT16 posx, UINT16 posy, INT8 content_type, INT8 scrigno){
	SpriteManagerRemoveSprite(itemin);
	itemin = SpriteManagerAdd(SpriteItem, (UINT16) posx << 3, (UINT16) posy << 3);
	struct ItemInfo* datascrigno = (struct ItemInfo*)itemin->custom_data;
	datascrigno->setup = 1u;
	if(scrigno){
		datascrigno->content_type = content_type;
		datascrigno->type = 10;
	}else{
		datascrigno->type = content_type;
	}
	return itemin;
}

void Update_StateGame() {

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
			case 3:
				SetState(StateGame);	
			break;
			case 4:
			case 5:
			case 6:
			case 7:
				SetState(StateGame4);
			break;
		} 
	}
	
	if(load_next_s){
		load_next_s = 0;
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
	
	
	//SPAWNING	
	switch(current_level){
		case 0:
			switch(current_map){
				case 0:
					if (scroll_target->x == (UINT16) 9u << 3 & scroll_target->y > (UINT16) 36u  << 3){
						snake1 = spawn_enemy(snake1, SpriteEnemy, 18u, 39u);
						snake2 = spawn_enemy(snake2, SpriteEnemy, 22u, 39u);
					}
				break;
				case 1:				
					if (scroll_target->x == (UINT16) 2u << 3 & scroll_target->y < (UINT16) 8u << 3){
						snake1 = spawn_enemy(snake1, SpriteEnemy, 7u, 12u);
						platform_sprite = spawn_enemy(platform_sprite, SpritePlatform, 9u, 21u);
					}
					if (scroll_target->x == (UINT16) 7u << 3 & scroll_target->y > (UINT16) 34u  << 3){
						snake3 = spawn_enemy(snake3, SpritePorcupine, 25u, 39u);
						snake2 = spawn_enemy(snake2, SpriteEnemy, 25u, 39u);
					}
					if (scroll_target->x == (UINT16) 24u << 3 & scroll_target->y == (UINT16) 21u  << 3){
						scrigno_up = spawn_item(scrigno_up, 28u, 18u, 3, 1);
					}
					if (scroll_target->x == (UINT16) 31u << 3 & scroll_target->y == (UINT16) 39u  << 3){
						snake4 = spawn_enemy(snake4, SpriteScorpion, 38u, 39u);
					}
					if (scroll_target->x == (UINT16) 36u << 3 & scroll_target->y <= (UINT16) 10u << 3 & scroll_target->y >= (UINT16) 6u << 3){
						snake1 = spawn_enemy(snake1, SpriteEnemy, 25u, 9u);
						snake2 = spawn_enemy(snake2, SpriteEnemy, 34u, 4u);
						snake3 = spawn_enemy(snake3, SpriteScorpion, 20u, 4u);
					}
				break;
			}
		break;
		case 1:
			switch(current_map){
				case 0:
					if (scroll_target->x == drop_player_x << 4){
						snake1 = spawn_enemy(snake1, SpriteSpider, 12u, 5u);
						snake2 = spawn_enemy(snake2, SpriteSpider, 14u, 6u);
						snake3 = spawn_enemy(snake3, SpriteSpider, 21u, 4u);
					}
					if (scroll_target->x == (UINT16) 18u << 3){
						scrigno_up = spawn_item(scrigno_up, 26u, 5u, 3, 1);
						platform_sprite = spawn_enemy(platform_sprite, SpritePlatform, 35u, 6u);
					}
					if (scroll_target->x == (UINT16) 43u << 3){
						snake1 = spawn_enemy(snake1, SpriteRat, 51u, 6u);
					}
					if (scroll_target->x == (UINT16) 48u << 3){
						SpriteManagerRemoveSprite(snake1);
						SpriteManagerRemoveSprite(snake2);
						SpriteManagerRemoveSprite(snake3);
						SpriteManagerRemoveSprite(snake4);
						snake2 = spawn_enemy(snake2, SpriteRat, 56u, 2u);
						snake3 = spawn_enemy(snake3, SpriteRat, 58u, 2u);
					}
					if (scroll_target->x == (UINT16) 67u << 3){
						snake4 = spawn_enemy(snake4, SpriteRat, 81u, 3u);
						SpriteManagerRemoveSprite(snake1);
						SpriteManagerRemoveSprite(snake2);
						SpriteManagerRemoveSprite(snake3);
						snake1 = spawn_enemy(snake1, SpriteRat, 83u, 3u);
						snake2 = spawn_enemy(snake2, SpriteSpider, 85u, 5u);
						scrigno_dcoin = spawn_item(scrigno_dcoin, 85u, 5u, 7, 1);
					}
					if (scroll_target->x == (UINT16) 97u << 3 | scroll_target->x == (UINT16) 101u << 3 | scroll_target->x == (UINT16) 108u << 3){
						SpriteManagerRemoveSprite(snake3);
						SpriteManagerRemoveSprite(snake4);
						snake3 = spawn_enemy(snake3, SpriteSpider, (scroll_target->x >> 3) + 2u, 3u);
						snake4 = spawn_enemy(snake4, SpriteSpider, (scroll_target->x >> 3) - 2u, 3u);
					}
				break;
				case 1:
					if (scroll_target->x == drop_player_x << 3 & scroll_target->y == (drop_player_y +1u) << 3){
						snake1 = spawn_enemy(snake1, SpriteRat, 18u, 4u);
						snake2 = spawn_enemy(snake2, SpriteRat, 14u, 4u);
					}
					if (scroll_target->x == (UINT16) 4u << 3 & scroll_target->y == (INT16) 14u  << 3){
						SpriteManagerRemoveSprite(snake1);
						SpriteManagerRemoveSprite(snake2);
						snake3 = spawn_enemy(snake3, SpriteRat, 14u, 14u);
						snake4 = spawn_enemy(snake4, SpriteSpider, 13u, 13u);
					}
					if (scroll_target->x == (UINT16) 29u << 3 & scroll_target->y == (INT16) 3u  << 3){
						scrigno_coin = spawn_item(scrigno_coin, 45u, 3u, 1, 1);
					}
					if (scroll_target->x == (UINT16) 19u << 3 & scroll_target->y == (INT16) 14u  << 3){
						snake1 = spawn_enemy(snake1, SpriteSpider, 31u, 11u);
					}
					if (scroll_target->x == (UINT16) 28u << 3 & scroll_target->y == (INT16) 14u  << 3){
						platform_sprite = spawn_enemy(platform_sprite, SpritePlatform, 34u, 14u);
						snake2 = spawn_enemy(snake2, SpriteRat, 43u, 14u);
					}
					if (scroll_target->x == (UINT16) 42u << 3 & scroll_target->y == (INT16) 28u  << 3){
						snake3 = spawn_enemy(snake3, SpriteSpider, 48u, 26u);
					}
					if (scroll_target->x == (UINT16) 53u << 3 & scroll_target->y == (INT16) 28u  << 3){
						snake4 = spawn_enemy(snake4, SpriteSpider, 64u, 21u);
						scrigno_dcoin = spawn_item(scrigno_dcoin, 67u, 23u, 7, 1);
					}
					if (scroll_target->x == (UINT16) 66u << 3 & scroll_target->y == (INT16) 10u  << 3){
						snake1 = spawn_enemy(snake1, SpriteRat, 64u, 15u);
						snake2 = spawn_enemy(snake2, SpriteRat, 60u, 15u);
						SpriteManagerRemoveSprite(snake3);
						SpriteManagerRemoveSprite(snake4);
						scrigno_up = spawn_item(scrigno_up, 62u, 15u, 3, 1);
					}
				break;
			}
		break;
		case 2:
			switch(current_map){
				case 0:
					if (scroll_target->x == (UINT16) 5u << 3){
						snake1 = spawn_enemy(snake1, SpriteSpider, 13u, 9u);
						snake2 = spawn_enemy(snake2, SpriteSpider, 19u, 9u);
					}
					if (scroll_target->x == (UINT16) 48u << 3){
						snake3 = spawn_enemy(snake3, SpriteSpider, 51u, 9u);
						snake4 = spawn_enemy(snake4, SpriteSpider, 53u, 9u);
						snake1 = spawn_enemy(snake1, SpriteEnemy, 60u, 9u);
					}
					if (scroll_target->x == (UINT16) 84u << 3){
						snake2 = spawn_enemy(snake2, SpriteBird, 90u, 3u);
					}
					if (scroll_target->x == (UINT16) 104u << 3){
						SpriteManagerRemoveSprite(snake1);
						SpriteManagerRemoveSprite(snake2);
						snake3 = spawn_enemy(snake3, SpriteEnemy, 115u, 10u);
						snake4 = spawn_enemy(snake4, SpriteBird, 92u, 3u);
					}
					if (scroll_target->x == (UINT16) 122u << 3){
						platform_sprite = spawn_enemy(platform_sprite, SpritePlatform, 131u, 10u);
						snake1 = spawn_enemy(snake1, SpriteBird, 137u, 3u);
						snake2 = spawn_enemy(snake2, SpriteBird, 117u, 3u);
					}
					if (scroll_target->x == (UINT16) 143u << 3){
						SpriteManagerRemoveSprite(snake1);
						SpriteManagerRemoveSprite(snake4);
						snake3 = spawn_enemy(snake3, SpriteBird, 149u, 3u);
					}
					if (scroll_target->x == (UINT16) 150u << 3 | scroll_target->x == (UINT16) 151u << 3){
						snake4 = spawn_enemy(snake4, SpriteBird, 140u, 3u);
						snake1 = spawn_enemy(snake1, SpriteSpider, 162u, 9u);
						snake2 = spawn_enemy(snake2, SpriteSpider, 166u, 9u);
						snake3 = spawn_enemy(snake3, SpriteEnemy, 160u, 9u);
					}
					if (scroll_target->x == (UINT16) 167u << 3){
						snake4 = spawn_enemy(snake4, SpriteBird, 172u, 3u);
						snake1 = spawn_enemy(snake1, SpriteBird, 166u, 3u);
					}
				break;
				case 1:
					if (scroll_target->x == (UINT16) 8u << 3){
						snake1 = spawn_enemy(snake1, SpriteSpider, 16u, 9u);
						snake2 = spawn_enemy(snake2, SpriteSpider, 17u, 9u);
					}
					if (scroll_target->x == (UINT16) 123u << 3){
						SpriteManagerRemoveSprite(snake1);
						SpriteManagerRemoveSprite(snake2);
						snake3 = spawn_enemy(snake3, SpriteBird, 133u, 5u);
					}
					if (scroll_target->x == (UINT16) 128u << 3){
						snake4 = spawn_enemy(snake4, SpriteBird, 118u, 5u);
						snake1 = spawn_enemy(snake1, SpriteSpider, 135u, 10u);
						snake2 = spawn_enemy(snake2, SpriteSpider, 136u, 9u);
					}
					if (scroll_target->x == (UINT16) 141u << 3){
						snake3 = spawn_enemy(snake3, SpriteBird, 131u, 5u);
					}
					if (scroll_target->x == (UINT16) 152u << 3){
						snake4 = spawn_enemy(snake4, SpriteBird, 162u, 5u);
					}
					if (scroll_target->x == (UINT16) 163u << 3){
						snake1 = spawn_enemy(snake1, SpriteBird, 173u, 5u);
						SpriteManagerRemoveSprite(snake2);
						SpriteManagerRemoveSprite(snake3);
					}
					if (scroll_target->x == (UINT16) 170u << 3){
						snake2 = spawn_enemy(snake2, SpriteBird, 179u, 5u);
						snake3 = spawn_enemy(snake3, SpriteSpider, 173u, 8u);
					}
				break;
			}
		break;
	}
	
	//MOVING BACKGROUND TILES	
	
	if (current_level == 1 & current_map == 0){
		updatecounter++;
		if (updatecounter < 21) {
			const unsigned char wv0[1] = {120};
			const unsigned char wv1[1] = {127};
			switch(updatecounter){
				case 1:	
					set_bkg_tiles(55, 9, 1, 1, wv0); set_bkg_tiles(56, 6, 1, 1, wv0); set_bkg_tiles(55, 10, 1, 1, wv0); set_bkg_tiles(56, 10, 1, 1, wv0); 
					set_bkg_tiles(55, 11, 1, 1, wv0); set_bkg_tiles(56, 11, 1, 1, wv0); set_bkg_tiles(55, 12, 1, 1, wv0); set_bkg_tiles(56, 12, 1, 1, wv0); 
					set_bkg_tiles(55, 13, 1, 1, wv0); set_bkg_tiles(56, 13, 1, 1, wv0); set_bkg_tiles(55, 14, 1, 1, wv0); set_bkg_tiles(56, 14, 1, 1, wv0); 
					set_bkg_tiles(55, 15, 1, 1, wv0); set_bkg_tiles(56, 15, 1, 1, wv0); set_bkg_tiles(55, 16, 1, 1, wv0); set_bkg_tiles(56, 16, 1, 1, wv0); 
					set_bkg_tiles(55, 17, 1, 1, wv0); set_bkg_tiles(56, 17, 1, 1, wv0); set_bkg_tiles(55, 18, 1, 1, wv0); set_bkg_tiles(56, 18, 1, 1, wv0); 
					set_bkg_tiles(55, 19, 1, 1, wv0); set_bkg_tiles(56, 19, 1, 1, wv0); set_bkg_tiles(55, 20, 1, 1, wv0); set_bkg_tiles(56, 20, 1, 1, wv0); 
					set_bkg_tiles(55, 21, 1, 1, wv0); set_bkg_tiles(56, 21, 1, 1, wv0); 
				break;
				case 10:	
					set_bkg_tiles(55, 9, 1, 1, wv1); set_bkg_tiles(56, 9, 1, 1, wv1); set_bkg_tiles(55, 10, 1, 1, wv1); set_bkg_tiles(56, 10, 1, 1, wv1); 
					set_bkg_tiles(55, 11, 1, 1, wv1); set_bkg_tiles(56, 11, 1, 1, wv1); set_bkg_tiles(55, 12, 1, 1, wv1); set_bkg_tiles(56, 12, 1, 1, wv1); 
					set_bkg_tiles(55, 13, 1, 1, wv1); set_bkg_tiles(56, 13, 1, 1, wv1); set_bkg_tiles(55, 14, 1, 1, wv1); set_bkg_tiles(56, 14, 1, 1, wv1); 
					set_bkg_tiles(55, 15, 1, 1, wv1); set_bkg_tiles(56, 15, 1, 1, wv1); set_bkg_tiles(55, 16, 1, 1, wv1); set_bkg_tiles(56, 16, 1, 1, wv1); 
					set_bkg_tiles(55, 17, 1, 1, wv1); set_bkg_tiles(56, 17, 1, 1, wv1); set_bkg_tiles(55, 18, 1, 1, wv1); set_bkg_tiles(56, 18, 1, 1, wv1); 
					set_bkg_tiles(55, 19, 1, 1, wv1); set_bkg_tiles(56, 19, 1, 1, wv1); set_bkg_tiles(55, 20, 1, 1, wv1); set_bkg_tiles(56, 20, 1, 1, wv1); 
					set_bkg_tiles(55, 21, 1, 1, wv1); set_bkg_tiles(56, 21, 1, 1, wv1); 
				break;
			}			
		}else{
			updatecounter = 0;
		}
	}
	if (current_level == 1 & current_map == 1){
		updatecounter++;
		if (updatecounter < 21) {
			const unsigned char wf0[1] = {123};
			const unsigned char wf1[1] = {124};
			const unsigned char wt0[1] = {125};
			const unsigned char wt1[1] = {126};
			const unsigned char wv0[1] = {120};
			const unsigned char wv1[1] = {127};
			switch(updatecounter){
				case 1:	
					set_bkg_tiles(32, 1, 1, 1, wf0); set_bkg_tiles(32, 2, 1, 1, wf0); set_bkg_tiles(32, 3, 1, 1, wf0);
					set_bkg_tiles(61, 24, 1, 1, wf0); set_bkg_tiles(61, 25, 1, 1, wf0); set_bkg_tiles(61, 26, 1, 1, wf0); set_bkg_tiles(61, 27, 1, 1, wf0);
					set_bkg_tiles(1, 6, 1, 1, wv0); set_bkg_tiles(2, 6, 1, 1, wv0); set_bkg_tiles(1, 7, 1, 1, wv0);
					set_bkg_tiles(2, 7, 1, 1, wv0); set_bkg_tiles(1, 8, 1, 1, wv0); set_bkg_tiles(2, 8, 1, 1, wv0);
					set_bkg_tiles(1, 9, 1, 1, wv0); set_bkg_tiles(2, 9, 1, 1, wv0); set_bkg_tiles(1,10, 1, 1, wv0);
					set_bkg_tiles(2, 10, 1, 1, wv0); set_bkg_tiles(1, 11, 1, 1, wv0); set_bkg_tiles(2, 11, 1, 1, wv0);
					set_bkg_tiles(1, 12, 1, 1, wv0); set_bkg_tiles(2, 12, 1, 1, wv0); set_bkg_tiles(1, 13, 1, 1, wv0);
					set_bkg_tiles(2, 13, 1, 1, wv0); set_bkg_tiles(1, 14, 1, 1, wv0); set_bkg_tiles(2, 14, 1, 1, wv0);
					set_bkg_tiles(31, 5, 1, 1, wt0); set_bkg_tiles(32, 4, 1, 1, wt0);
				break;
				case 10:	
					set_bkg_tiles(32, 1, 1, 1, wf1); set_bkg_tiles(32, 2, 1, 1, wf1); set_bkg_tiles(32, 3, 1, 1, wf1);
					set_bkg_tiles(61, 24, 1, 1, wf1); set_bkg_tiles(61, 25, 1, 1, wf1); set_bkg_tiles(61, 26, 1, 1, wf1); set_bkg_tiles(61, 27, 1, 1, wf1);
					set_bkg_tiles(1, 6, 1, 1, wv1); set_bkg_tiles(2, 6, 1, 1, wv1); set_bkg_tiles(1, 7, 1, 1, wv1); set_bkg_tiles(2, 7, 1, 1, wv1);
					set_bkg_tiles(1, 8, 1, 1, wv1); set_bkg_tiles(2, 8, 1, 1, wv1); set_bkg_tiles(1, 9, 1, 1, wv1); set_bkg_tiles(2, 9, 1, 1, wv1);
					set_bkg_tiles(1, 10, 1, 1, wv1); set_bkg_tiles(2, 10, 1, 1, wv1); set_bkg_tiles(1, 11, 1, 1, wv1); set_bkg_tiles(2, 11, 1, 1, wv1);
					set_bkg_tiles(1, 12, 1, 1, wv1);  set_bkg_tiles(2, 12, 1, 1, wv1); set_bkg_tiles(1, 13, 1, 1, wv1); set_bkg_tiles(2, 13, 1, 1, wv1);
					set_bkg_tiles(1, 14, 1, 1, wv1); set_bkg_tiles(2, 14, 1, 1, wv1); set_bkg_tiles(32, 4, 1, 1, wt1);
				break;
			}			
		}else{
			updatecounter = 0;
		}
	}
	
	
	if(show_diag >= 2){ // if(show_diag >= max_diag){ 
		ShowWindow();
		return;
	}
	if(archer_state == STATE_DIAG){
		if(show_diag > 0 ){
			ShowWindowDiag();
			return;
		}
	}
	else{
		if (amulet != archer_data->amulet | amulet == 0u){
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
		if(archer_tool != archer_data->tool){// & archer_tool == level_tool
			archer_tool = archer_data->tool;
			UpdateHUD();
		}
	}
	
}

void UpdateHUD(){
	//write amulet
	PRINT_POS(19,0);
	switch (archer_data->amulet){
		case 1: Printf("$"); break;
		case 2: Printf("]"); break;
		case 3: Printf("["); break;
		case 4: Printf("#"); break;
		case 5: Printf("@"); break;
		default: Printf("$"); break;
	}
	//write coins
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
	//write hp
	PRINT_POS(7, 0);
	if (archer_data->hp < 10){
		Printf("00%d", archer_data->hp);
	}
	if (archer_data->hp > 9 & archer_data->hp < 100){
		Printf("0%d", archer_data->hp);
	}
	if (archer_data->hp >= 100){
		Printf("%d", archer_data->hp);	
	}
	//write tool
	if (archer_data->tool == level_tool){
		switch(level_tool){
			case 6:
				PRINT_POS(16, 0);
				Printf("{");
			break;
			case 7:
				PRINT_POS(16, 0);
				Printf("<");
			break;
		}
	}
	//write ups
	PRINT_POS(2, 0); //up
	if (archer_data->ups > 9){Printf("%d", archer_data->ups);}
	else{Printf("0%d", archer_data->ups);}
}
