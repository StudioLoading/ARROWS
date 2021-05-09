#pragma bank 11

#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "string.h"
#include "Scroll.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"


extern UINT8 current_level_b;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_boss;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern struct ArcherInfo* archer_data;
extern UINT8 tile_collision;

INT8 Build_Next_Dialog_Banked(struct Sprite* archer) __banked{
	INT8 diag_found = 1;
	switch (is_on_boss){
		case 0:
			switch(current_level_b){
				case 0u:
					memcpy(d1, "THE BLACK WOLF", 18);
					memcpy(d2, "OWNS THE WRENCH", 18);
					memcpy(d3, "I NEED TO EXIT.", 18);
					memcpy(d4, "LET'S FIGHT!", 18);
					diag_found = 0;
				break;
				case 1u:
					memcpy(d1, "HOW CAN I", 18);
					memcpy(d2, "DESTROY THIS", 18);
					memcpy(d3, "GATE? WHAT?", 18);
					memcpy(d4, "AN ALLIGATOR!!", 18);
					diag_found = 0;
				break;
				case 2u:
					memcpy(d1, "THE EAGLE OWNS", 18);
					memcpy(d2, "THE KEY I", 18);
					memcpy(d3, "NEED TO EXIT.", 18);
					memcpy(d4, "LET'S FIGHT!", 18);
					diag_found = 0;
				break;
				case 3u:
					memcpy(d1, "HOW CAN I", 18);
					memcpy(d2, "DESTROY THIS GATE", 18);
					memcpy(d3, "... IBEX ?", 18);
					memcpy(d4, "", 18);
					diag_found = 0;
				break;
			}	
		break;
		case 1:  //is_on_boss == 1 significa che ho toccato il boss che dovrebbe essere in WAIT
			switch(current_level_b){
				case 0u:
					memcpy(d1, "BEAST! BACK", 18);
					memcpy(d2, "TO YOUR CAGE!", 18);
					memcpy(d3, "-GRRR!", 18);
					memcpy(d4, "", 18);
					diag_found = 0;
				break;
			}	
		break;
		case 2://is_on_boss == 2 significa che l'ho sconfitto
			switch(current_level_b){
				case 0u:
					memcpy(d1, "I...", 18);
					memcpy(d2, "JUST NEEDED THE", 18);
					memcpy(d3, "WRENCH TO GO", 18);
					memcpy(d4, "ON. SORRY WOLF!", 18);
					diag_found = 0;
				break;
				case 1u:
					memcpy(d1, "FINALLY YOU", 18);
					memcpy(d2, "GAVE ME WHAT I", 18);
					memcpy(d3, "NEEDED. THE", 18);
					memcpy(d4, "STONE AMULET!", 18);
					diag_found = 0;
				break;
				case 2u:
					memcpy(d1, "I...", 18);
					memcpy(d2, "JUST NEEDED THE", 18);
					memcpy(d3, "WRENCH TO GO", 18);
					memcpy(d4, "ON. SORRY EAGLE!", 18);
					diag_found = 0;
				break;
				case 3u:
					memcpy(d1, "FINALLY YOU", 18);
					memcpy(d2, "GAVE ME WHAT I", 18);
					memcpy(d3, "NEEDED. THE", 18);
					memcpy(d4, "THUNDER AMULET!", 18);
					diag_found = 0;
				break;
				case 4u:
					memcpy(d1, "I...", 18);
					memcpy(d2, "JUST NEEDED THE", 18);
					memcpy(d3, "WRENCH TO GO", 18);
					memcpy(d4, "ON. SORRY BEAR!", 18);
					diag_found = 0;
				break;
			}	
		break;
	}
	
	if (diag_found){
		switch(current_level){
			case 0:
				switch(current_map){
					case 0:
						if (archer_data->tool == 6){//ho trovato la chiave
							memcpy(d1, "THIS KEY OPENS", 18);
							memcpy(d2, "THE BLACK WOLF", 18);
							memcpy(d3, "CAVE. LET'S GO.", 18);
							memcpy(d4, "", 18);
							diag_found = 0;
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u){
							if (archer->x > (UINT16) 43u << 3 & archer_data->tool == 0){//sto cercando di parlare col prig che ha la chiave
								if (archer_data->coins < 20u){
									memcpy(d1, "SLAVE: 20 COINS", 18);
									memcpy(d2, "FOR THE KEY", 18);
									memcpy(d3, "", 18);
									memcpy(d4, "", 18);
									diag_found = 0;
								}else{
									archer_data->coins -= 20u;
									memcpy(d1, "SLAVE: THANK YOU", 18);
									memcpy(d2, "HERE IS THE", 18);
									memcpy(d3, "KEY.", 18);
									memcpy(d4, ".. EH EH !", 18);								
									struct Sprite* key_sprite = SpriteManagerAdd(SpriteKey, archer->x + 16u, archer->y);
									struct ItemInfo* datakey = (struct ItemInfo*)key_sprite->custom_data;
									datakey->type = 1;
									datakey->setup = 1u;
									diag_found = 0;		
								}				
							}else{//qualsiasi altro slave							
								memcpy(d1, "SLAVE: WHAT'VE", 18);
								memcpy(d2, "WE DONE !?", 18);
								memcpy(d3, "SIGH!", 18);
								memcpy(d4, "", 18);
								diag_found = 0;
							}
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 30u){
							memcpy(d1, "SLAVE: ON THE", 18);
							memcpy(d2, "UPPER RIGHT", 18);
							memcpy(d3, "CORNER SOMEONE", 18);
							memcpy(d4, "IS LAUGHING", 18);
							diag_found = 0;
						}
						if(diag_found){//ho premuto la combo dei diag senza motivo
							memcpy(d1, "I GOT TO FIND", 18);
							memcpy(d2, "THE KEY TO ENTER", 18);
							memcpy(d3, "THE BLACK WOLF", 18);
							memcpy(d4, "CAVE.", 18);
							diag_found = 0;
						}
					break;
					case 1:
						if (tile_collision == 7u){
							if (archer_data->tool){
								memcpy(d1, "-----------------", 18);
								memcpy(d2, "   CAVE OF THE", 18);
								memcpy(d3, "   BLACK WOLF ", 18);
								memcpy(d4, "-----------------", 18);
								diag_found = 0;
							}else{
								memcpy(d1, "CAVE OF THE", 18);
								memcpy(d2, "BLACK WOLF. I", 18);
								memcpy(d3, "NEED A KEY TO", 18);
								memcpy(d4, "OPEN THIS DOOR.", 18);
								PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
								diag_found = 0;
							}
						}else{
							memcpy(d1, "I CAN SMELL...", 18);
							memcpy(d2, "WOLF' CAVE", 18);
							memcpy(d3, "CAN'T BE FAR.", 18);
							memcpy(d4, "", 18);
							diag_found = 0;							
						}
					break;
				}
			break;
			case 1:
				switch(current_map){
					case 0:
						memcpy(d1, "LET'S GET OUT", 18);
						memcpy(d2, "OF THIS FILTHY", 18);
						memcpy(d3, "SEWER.", 18);
						memcpy(d4, "-- SNIFF!", 18);
						diag_found = 0;
					break;
					case 1:
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
							if (archer_data->tool == 0){//sto cercando di parlare col prig che WRENCH
								memcpy(d1, "SLAVE: I'LL NEVER", 18);
								memcpy(d2, "GET OUT. PLEASE", 18);
								memcpy(d3, "TAKE MY WRENCH.", 18);
								memcpy(d4, "FREE US ALL!", 18);								
								struct Sprite* key_sprite = SpriteManagerAdd(SpriteKey, archer->x + 16u, archer->y);
								struct ItemInfo* datakey = (struct ItemInfo*)key_sprite->custom_data;
								datakey->type = 1;
								datakey->setup = 1u;
								diag_found = 0;		
							}
						}
						if (tile_collision == 7u){
							if (archer_data->tool){
								memcpy(d1, "----------------", 18);
								memcpy(d2, "  SWAMP OF THE", 18);
								memcpy(d3, "     ALLIGATOR ", 18);
								memcpy(d4, "----------------", 18);
								diag_found = 0;
							}else{
								memcpy(d1, "SWAMP. I NEED", 18);
								memcpy(d2, "THE WRENCH TO", 18);
								memcpy(d3, "OPEN THIS DOOR.", 18);
								memcpy(d4, "", 18);
								PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
								diag_found = 0;
							}
						}
						if(diag_found){
							if (archer_data->tool){
								memcpy(d1, "THE ONLY WAY", 18);
								memcpy(d2, "IS UP !!", 18);
								memcpy(d3, "", 18);
								memcpy(d4, "", 18);									
							}else{							
								memcpy(d1, "BLEAH !!", 18);
								memcpy(d2, "THE DEEPEST", 18);
								memcpy(d3, "THE WORST IS", 18);
								memcpy(d4, "GETTING", 18);
							}
							diag_found = 0;
						}
					break;
				}
			break;
			case 3:
				switch(current_map){
					case 0:
						memcpy(d1, "BETTER NOT TO", 18);
						memcpy(d2, "FALL. CERTAIN", 18);
						memcpy(d3, "DEATH ON THIS", 18);
						memcpy(d4, "HEIGHT !", 18);
						diag_found = 0;
					break;
					case 1:
						memcpy(d1, "AAH-AAH-AH", 18);
						memcpy(d2, "....!", 18);
						memcpy(d3, "THUN-DERS !!", 18);
						memcpy(d4, "", 18);
						diag_found = 0;
					break;
				}
			break;
			case 4:
				if (tile_collision == 7u){
					memcpy(d1, "THERE IS TOO", 18);
					memcpy(d2, "MUCH SILENCE", 18);
					memcpy(d3, "FROM HERE ON.", 18);
					memcpy(d4, "", 18);
					PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
					diag_found = 0;
				}else{							
					memcpy(d1, "I HAVE TO GO", 18);
					memcpy(d2, "BACK ON THE", 18);
					memcpy(d3, "PATH TO THE", 18);
					memcpy(d4, "CASTLE !", 18);
					diag_found = 0;
				}
			break;
		}
	}
	return diag_found;
}