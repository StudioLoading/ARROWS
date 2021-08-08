#pragma bank 11

#include "Keys.h"
#include "ZGBMain.h"
#include "string.h"
#include "Scroll.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"


extern UINT8 current_level_b;
extern UINT8 current_level;
extern UINT8 current_map;
extern UINT8 current_camera_state;
extern UINT8 current_camera_counter;
extern INT8 is_on_boss;
extern INT8 load_next_b;
extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];
extern struct ArcherInfo* archer_data;
extern UINT8 tile_collision;
extern ARCHER_STATE archer_state;

UINT8 Build_Next_Dialog_Banked(struct Sprite* archer) __banked{
	UINT8 diagf = 0u;
	//diagf contains an integer corresponding to a map to show on StateDiag!
	/*
		1	Player
		2 	Player 2
		3	Player 3
		4	Slave in cage standing
		5	Slave in cage sit down
		6	Slave chined
		10	Stage Zoo
		11	Stage Swamp
		12	Stage Hills
		13	Stage Sky
		14	Stage Forest
		15 	Stage Iced Cavern
		16	Stage Castle
		19	Door
		20	wrench
		21	key
		30 	amulet calice stone
		31 	amulet
		32 	amulet
		33 	amulet
		51	Wolf
		52	Gator
		53 	Eagle
		54	Ibex
		55 	Bear
		56 	Tusk
		57 	Boss
		58	Boss 2
		60	Sister
		99 	Suggestion
	
	*/
	switch (is_on_boss){
		case 0:
			switch(current_level_b){
				case 0u:
					memcpy(d1, "A BLACK WOLF  ", 18);
					memcpy(d2, "OWNS THE WRENCH", 18);
					memcpy(d3, "I NEED TO EXIT.", 18);
					memcpy(d4, "LET'S FIGHT!", 18);
					diagf = 19u;
				break;
				case 1u:
					memcpy(d1, "THE EXIT IS    ", 18);
					memcpy(d2, "BEYOND A GATOR ", 18);
					memcpy(d3, "I NEED HIS AMULET", 18);
					memcpy(d4, "LET'S FIGHT!", 18);
					diagf = 1u;
				break;
				case 2u:
					memcpy(d1, "AN EAGLE OWNS", 18);
					memcpy(d2, "THE KEY I", 18);
					memcpy(d3, "NEED TO EXIT.", 18);
					memcpy(d4, "LET'S FIGHT!", 18);
					diagf = 1u;
				break;
				case 3u:
					memcpy(d1, "HOW CAN I", 18);
					memcpy(d2, "DESTROY THIS GATE", 18);
					memcpy(d3, "... IBEX ?", 18);
					memcpy(d4, "                 ", 18);
					diagf = 1u;
				break;
				case 4u:
					memcpy(d1, "HELLO", 18);
					memcpy(d2, "TEDDY BEAR !", 18);
					memcpy(d3, "LET ME", 18);
					memcpy(d4, "PASS !", 18);
					diagf = 1u;
				break;
			}
		break;
		case 1:  //is_on_boss == 1
			switch(current_level_b){
				case 0u:
					memcpy(d1, "BEAST! BACK      ", 18);
					memcpy(d2, "TO YOUR CAGE!    ", 18);
					memcpy(d3, "-GRRR!           ", 18);
					memcpy(d4, "                 ", 18);
					current_camera_state = 3u;
					diagf = 51u;
				break;
				case 1u:				
					memcpy(d1, "FILTHY HUMAN !!  ", 18);
					memcpy(d2, "I'LL MAKE A      ", 18);
					memcpy(d3, "BELT OUT OF      ", 18);
					memcpy(d4, "YOUR SKIN.       ", 18);
					current_camera_state = 3u;
					diagf = 52u;
				break;
				case 2u:				
					memcpy(d1, "THE SKY IS MINE ", 18);
					memcpy(d2, "                ", 18);
					memcpy(d3, "                ", 18);
					memcpy(d4, "                ", 18);
					current_camera_state = 3u;
					diagf = 53u;
				break;
				case 3u:				
					memcpy(d1, "NOBODY HAS EVER ", 18);
					memcpy(d2, "GONE THROUGH MY ", 18);
					memcpy(d3, "THUNDERS! NOW   ", 18);
					memcpy(d4, "FACE MY HORNS!  ", 18);
					current_camera_state = 3u;
					diagf = 54u;
				break;
				case 4u:				
					memcpy(d1, "                ", 18);
					memcpy(d2, "                ", 18);
					memcpy(d3, "                ", 18);
					memcpy(d4, "                ", 18);
					current_camera_state = 3u;
					diagf = 55u;
				break;
			}	
		break;
		case 2://is_on_boss == 2 significa che l'ho sconfitto
			if(archer_state != STATE_AMULET_STONE && archer_state != STATE_AMULET_THUNDER && archer_state != STATE_AMULET_ICE && archer_state != STATE_AMULET_FIRE){
				switch(current_level_b){
					case 0u:
						memcpy(d1, "I...", 18);
						memcpy(d2, "JUST NEEDED THE", 18);
						memcpy(d3, "WRENCH TO GO", 18);
						memcpy(d4, "ON. SORRY WOLF!", 18);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "PRESS SELECT   ", 18);
						memcpy(d2, "TO THE [ SYMBOL", 18);
						memcpy(d3, "AND BREAK      ", 18);
						memcpy(d4, "THE GATE       ", 18);
						diagf = 99u;
					break;
					case 2u:
						memcpy(d1, "I...           ", 18);
						memcpy(d2, "JUST NEEDED THE", 18);
						memcpy(d3, "KEY TO GO ON   ", 18);
						memcpy(d4, "SORRY EAGLE!", 18);
						diagf = 99u;
					break;
					case 3u:
						memcpy(d1, "PRESS SELECT   ", 18);
						memcpy(d2, "TO THE # SYMBOL", 18);
						memcpy(d3, "AND BREAK      ", 18);
						memcpy(d4, "THE GATE       ", 18);
						diagf = 99u;
					break;
					case 4u:
						memcpy(d1, "I...           ", 18);
						memcpy(d2, "JUST NEEDED THE", 18);
						memcpy(d3, "WRENCH TO GO   ", 18);
						memcpy(d4, "ON. SORRY BEAR!", 18);
						diagf = 99u;
					break;
				}				
			}else{ // one of the amulet has been collided
				switch(archer_state){
					case STATE_AMULET_STONE:
						memcpy(d1, "THE STONE CALICE", 18);
						memcpy(d2, "                ", 18);
						memcpy(d3, "NOW I CAN THROW ", 18);
						memcpy(d4, "STONE ARROWS   +[", 18);
						diagf = 30u;					
					break;
					case STATE_AMULET_THUNDER:
						memcpy(d1, "THE THUNDER HORN ", 18);
						memcpy(d2, "                 ", 18);
						memcpy(d3, "NOW I CAN THROW  ", 18);
						memcpy(d4, "THUNDER ARROWS +#", 18);
						diagf = 31u;					
					break;
					case STATE_AMULET_ICE:
						memcpy(d1, "STALAGMITE NECK  ", 18);
						memcpy(d2, "        ", 18);
						memcpy(d3, "NOW I CAN THROW ", 18);
						memcpy(d4, "ICE ARROWS  + ] ", 18);
						diagf = 32u;					
					break;
					case STATE_AMULET_FIRE:
						memcpy(d1, "VULKAN PYRAMID  ", 18);
						memcpy(d2, "                  ", 18);
						memcpy(d3, "NOW I CAN THROW  ", 18);
						memcpy(d4, "FIRE ARROWS   +] ", 18);
						diagf = 33u;					
					break;
				}
			}
			break;
	}
	
	if (diagf == 0u){
		switch(current_level){
			case 0u:
				switch(current_map){
					case 0u:
						if (load_next_b == 1){//ho trovato la chiave
							memcpy(d1, "THIS KEY OPENS", 18);
							memcpy(d2, "THE BLACK WOLF", 18);
							memcpy(d3, "CAVE. LET'S GO.", 18);
							memcpy(d4, "                 ", 18);
							diagf = 99u;
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u){
							if (archer->x > (UINT16) 90u << 3 && 
								archer->x < (UINT16) 97u << 3 &&
								archer_data->tool == 0){//sto cercando di parlare col prig che ha la chiave
								if (archer_data->coins < 20u){
									memcpy(d1, "20 COINS     ", 18);
									memcpy(d2, "FOR THE KEY", 18);
									memcpy(d3, "                 ", 18);
									memcpy(d4, "                 ", 18);
									diagf = 4u;
								}else{
									memcpy(d1, "THANK YOU     ", 18);
									memcpy(d2, "HERE IS THE", 18);
									memcpy(d3, "KEY.", 18);
									memcpy(d4, ".. EH EH !", 18);
									diagf = 21u;		
								}				
							}else{//qualsiasi altro slave in piedi in gabbia							
								memcpy(d1, "WHAT'VE WE DONE! ", 18);
								memcpy(d2, "                 ", 18);
								memcpy(d3, "                 ", 18);
								memcpy(d4, "                 ", 18);
								diagf = 4u;
							}
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 30u){
							memcpy(d1, "ON THE       ", 18);
							memcpy(d2, "UPPER LEVEL", 18);
							memcpy(d3, "SOMEONE", 18);
							memcpy(d4, "IS LAUGHING", 18);
							diagf = 5u;
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
							memcpy(d1, " ...MPFH !       ", 18);
							memcpy(d2, "                 ", 18);
							memcpy(d3, "                 ", 18);
							memcpy(d4, "                 ", 18);
							diagf = 6u;
						}
						if(diagf == 0u){//ho premuto la combo dei diag senza motivo
							memcpy(d1, "I GOT TO FIND", 18);
							memcpy(d2, "THE KEY TO ENTER", 18);
							memcpy(d3, "THE BLACK WOLF", 18);
							memcpy(d4, "CAVE.", 18);
							diagf = 99u;
						}
					break;
					case 1u:
						if (tile_collision == 7u){
							if (load_next_b == 1){
								memcpy(d1, "-----------------", 18);
								memcpy(d2, "   CAVE OF THE", 18);
								memcpy(d3, "   BLACK WOLF ", 18);
								memcpy(d4, "-----------------", 18);
								diagf = 19u;
							}else{
								memcpy(d1, "CAVE OF THE", 18);
								memcpy(d2, "BLACK WOLF. I", 18);
								memcpy(d3, "NEED A KEY TO", 18);
								memcpy(d4, "OPEN THIS DOOR.", 18);
								PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
								diagf = 19u;
							}
						}else{
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
								memcpy(d1, " KEEP... FORWARD.", 18);
								memcpy(d2, "                 ", 18);
								memcpy(d3, "                 ", 18);
								memcpy(d4, "                 ", 18);
								diagf = 6u;
							}
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u){
								memcpy(d1, "THIS IS MOTHER   ", 18);
								memcpy(d2, "NATURE REVENGE !!", 18);
								memcpy(d3, "                 ", 18);
								memcpy(d4, "                 ", 18);
								diagf = 4u;
							}
							if(diagf == 0u){
								memcpy(d1, "I CAN SMELL...   ", 18);
								memcpy(d2, "CAVE ENTRANCE    ", 18);
								memcpy(d3, "CAN'T BE FAR.    ", 18);
								memcpy(d4, "                 ", 18);
								diagf = 99u;							
							}
						}
					break;
				}
			break;
			case 1u:
				switch(current_map){
					case 0u:
						memcpy(d1, "LET'S GET OUT", 18);
						memcpy(d2, "OF THIS FILTHY", 18);
						memcpy(d3, "SEWER.", 18);
						memcpy(d4, "    PHUA!", 18);
						diagf = 99u;
					break;
					case 1u:
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
							if (archer_data->tool == 0){//sto cercando di parlare col prig che WRENCH
								memcpy(d1, "I'LL NEVER     ", 18);
								memcpy(d2, "GET OUT. PLEASE", 18);
								memcpy(d3, "TAKE MY WRENCH.", 18);
								memcpy(d4, "FREE US ALL!", 18);
								diagf = 20u;		
							}else{
								memcpy(d1, "YOU CAN DO THIS. ", 18);
								memcpy(d2, "                 ", 18);
								memcpy(d3, "                 ", 18);
								memcpy(d4, "                 ", 18);
								diagf = 6u;
							}
						}
						if (tile_collision == 7u){
							if (archer_data->tool != 0){
								memcpy(d1, "----------------", 18);
								memcpy(d2, "  SWAMP OF THE", 18);
								memcpy(d3, "     ALLIGATOR ", 18);
								memcpy(d4, "----------------", 18);
								diagf = 19u;
							}else{
								memcpy(d1, "SWAMP. I NEED", 18);
								memcpy(d2, "THE WRENCH TO", 18);
								memcpy(d3, "OPEN THIS DOOR.", 18);
								memcpy(d4, "                 ", 18);
								PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
								diagf = 99u;
							}
						}
						if(diagf == 0u){
							memcpy(d1, "BLEAH !!", 18);
							memcpy(d2, "THE DEEPEST", 18);
							memcpy(d3, "THE WORST IS", 18);
							memcpy(d4, "GETTING", 18);
							diagf = 99u;
						}
					break;
				}
			break;
			case 2u:
				switch(current_map){
					case 0u:
						memcpy(d1, "I NEED DEXTERITY ", 18);
						memcpy(d2, "TO GET TO THE END", 18);
						memcpy(d3, "OF THIS FOREST.  ", 18);
						memcpy(d4, "                 ", 18);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "I'D BETTER        ", 18);
						memcpy(d2, "WATCH OUT FROM    ", 18);
						memcpy(d3, "THE BIRDS         ", 18);
						memcpy(d4, "                  ", 18);
						diagf = 99u;
					break;					
				}
			break;
			case 3u:
				switch(current_map){
					case 0u:
						memcpy(d1, "BETTER NOT     ", 18);
						memcpy(d2, "FALL. CERTAIN  ", 18);
						memcpy(d3, "DEATH FROM THIS", 18);
						memcpy(d4, "HEIGHT !       ", 18);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "AAH-AAH-AH", 18);
						memcpy(d2, "....!", 18);
						memcpy(d3, "THUN-DERS !!", 18);
						memcpy(d4, "                 ", 18);
						diagf = 99u;
					break;
				}
			break;
			case 4u:
				if (tile_collision == 7u){
					memcpy(d1, "THERE IS TOO", 18);
					memcpy(d2, "MUCH SILENCE", 18);
					memcpy(d3, "FROM HERE ON.", 18);
					memcpy(d4, "                 ", 18);
					PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
					diagf = 99u;
				}else{							
					memcpy(d1, "I HAVE TO GO  ", 18);
					memcpy(d2, "BELOW THESE   ", 18);
					memcpy(d3, "DEATHLY TREES ", 18);
					memcpy(d4, "              ", 18);
					diagf = 99u;
				}
			break;
		}
	}
	return diagf;
}