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
extern INT8 on_worldmap;

UINT8 Build_Next_Dialog_Banked(struct Sprite* archer) __banked{
	UINT8 diagf = 0u;	
	memcpy(d1, "                    ", 20);
	memcpy(d2, "                    ", 20);
	memcpy(d3, "                    ", 20);
	memcpy(d4, "                    ", 20);
	if(on_worldmap == 1){
		switch(current_level){
			case 0u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "       THE ZOO      ", 20);
				memcpy(d3, "                    ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 10u;
			break;
			case 1u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "  THROUGH THE SEWER ", 20);
				memcpy(d3, "                    ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 11u;
			break;
			case 2u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "  RUN TO THE HILLS  ", 20);
				memcpy(d3, "                    ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 12u;
			break;
			case 3u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "       THE SKY      ", 20);
				memcpy(d3, "     IS THE LIMIT   ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 13u;
			break;
			case 4u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "     WELCOME TO     ", 20);
				memcpy(d3, "     THE JUNGLE     ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 14u;
			break;
			case 5u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "      ICE COLD      ", 20);
				memcpy(d3, "                    ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 15u;
			break;
			case 6u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "    PET SEMATARY    ", 20);
				memcpy(d3, "                    ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 16u;
			break;
		}
		on_worldmap = 0;
	}
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
	if(diagf == 0U){
		switch (is_on_boss){
			case 0:
				switch(current_level_b){
					case 0u:
						memcpy(d1, "    A BLACK WOLF    ", 20);
						memcpy(d2, "  OWNS THE WRENCH   ", 20);
						memcpy(d3, "  I NEED TO EXIT.   ", 20);
						memcpy(d4, "    LET'S FIGHT!    ", 20);
						diagf = 19u;
					break;
					case 1u:
						memcpy(d1, "    THE EXIT IS     ", 20);
						memcpy(d2, "   BEYOND A GATOR   ", 20);
						memcpy(d3, " I NEED HIS AMULET  ", 20);
						memcpy(d4, "    LET'S FIGHT!    ", 20);
						diagf = 1u;
					break;
					case 2u:
						memcpy(d1, "    AN EAGLE OWNS   ", 20);
						memcpy(d2, "      THE KEY I     ", 20);
						memcpy(d3, "    NEED TO EXIT.   ", 20);
						memcpy(d4, "     LET'S FIGHT!   ", 20);
						diagf = 1u;
					break;
					case 3u:
						memcpy(d1, "    THE EXIT IS     ", 20);
						memcpy(d2, "   BEYOND A IBEX    ", 20);
						memcpy(d3, " I NEED HIS AMULET  ", 20);
						memcpy(d4, "    LET'S FIGHT!    ", 20);
						diagf = 1u;
					break;
					case 4u:
						memcpy(d1, "       HELLO        ", 20);
						memcpy(d2, "     TEDDY BEAR !   ", 20);
						memcpy(d3, "                    ", 20);
						memcpy(d4, "     LET ME PASS!   ", 20);
						diagf = 1u;
					break;
					case 5u:
						memcpy(d1, "    THE EXIT IS     ", 20);
						memcpy(d2, "  BEYOND A WALRUS.  ", 20);
						memcpy(d3, " I NEED HIS AMULET  ", 20);
						memcpy(d4, "    LET'S FIGHT!    ", 20);
						diagf = 1u;
					break;
				}
			break;
			case 1:  //is_on_boss == 1
				switch(current_level_b){
					case 0u:
						memcpy(d1, "   BEAST! BACK      ", 20);
						memcpy(d2, "   TO YOUR CAGE!    ", 20);
						memcpy(d3, "   -GRRR!           ", 20);
						memcpy(d4, "                    ", 20);
						current_camera_state = 3u;
						diagf = 51u;
					break;
					case 1u:				
						memcpy(d1, "   FILTHY HUMAN !!  ", 20);
						memcpy(d2, "   I'LL MAKE A      ", 20);
						memcpy(d3, "   BELT OUT OF      ", 20);
						memcpy(d4, "   YOUR SKIN.       ", 20);
						current_camera_state = 3u;
						diagf = 52u;
					break;
					case 2u:				
						memcpy(d1, " AS LONG AS I FLY   ", 20);
						memcpy(d2, " THE SKY IS MINE!   ", 20);
						memcpy(d3, "HOPE YOU DON'T MIND ", 20);
						memcpy(d4, "IN MY CLAWS YOU DIE!", 20);
						current_camera_state = 3u;
						diagf = 53u;
					break;
					case 3u:				
						memcpy(d1, "  NOBODY HAS EVER   ", 20);
						memcpy(d2, "  GONE THROUGH MY   ", 20);
						memcpy(d3, "  THUNDERS! NOW     ", 20);
						memcpy(d4, "  FACE MY HORNS!    ", 20);
						current_camera_state = 3u;
						diagf = 54u;
					break;
					case 4u:
						memcpy(d1, "        GRRR!       ", 20);
						memcpy(d2, "                    ", 20);
						memcpy(d3, "    ROOOOOOOAAAR!   ", 20);
						memcpy(d4, "                    ", 20);
						current_camera_state = 3u;
						diagf = 55u;
					break;
					case 5u:				
						memcpy(d1, " YOUR ARROWS WON'T  ", 20);
						memcpy(d2, " BEAT MY HEADBUTTS! ", 20);
						memcpy(d3, " IS THE ICE NECKLES ", 20);
						memcpy(d4, " PRETTY OR ISN'T IT?", 20);
						current_camera_state = 3u;
						diagf = 56u;
					break;
				}	
			break;
			case 2://is_on_boss == 2 significa che l'ho sconfitto
			case 3: // final tip on boss destroyed
				if(archer_state != STATE_AMULET_STONE && archer_state != STATE_AMULET_THUNDER && archer_state != STATE_AMULET_ICE && archer_state != STATE_AMULET_FIRE){
					switch(current_level_b){
						case 0u:
							memcpy(d1, "        I...        ", 20);
							memcpy(d2, "  JUST NEEDED THE   ", 20);
							memcpy(d3, "  WRENCH TO GO ON   ", 20);
							memcpy(d4, "   SORRY BLACKIE!   ", 20);
							diagf = 99u;
						break;
						case 1u:
							memcpy(d1, "     PRESS SELECT   ", 20);
							memcpy(d2, "   TO THE [ SYMBOL  ", 20);
							memcpy(d3, " AND BREAK THE GATE ", 20);
							memcpy(d4, "                    ", 20);
							diagf = 99u;
						break;
						case 2u:
							memcpy(d1, "         I...       ", 20);
							memcpy(d2, "   JUST NEEDED THE  ", 20);
							memcpy(d3, "     KEY TO GO ON   ", 20);
							memcpy(d4, "     SORRY EAGLE!   ", 20);
							diagf = 99u;
						break;
						case 3u:
							memcpy(d1, "     PRESS SELECT   ", 20);
							memcpy(d2, "   TO THE # SYMBOL  ", 20);
							memcpy(d3, " AND BREAK THE GATE ", 20);
							memcpy(d4, "                    ", 20);
							diagf = 99u;
						break;
						case 4u:
							memcpy(d1, " I...               ", 20);
							memcpy(d2, " JUST NEEDED THE    ", 20);
							memcpy(d3, " WRENCH TO GO       ", 20);
							memcpy(d4, " ON. SORRY BEAR!    ", 20);
							diagf = 99u;
						break;
						case 5u:
							memcpy(d1, "     PRESS SELECT   ", 20);
							memcpy(d2, "   TO THE ] SYMBOL  ", 20);
							memcpy(d3, " AND BREAK THE GATE ", 20);
							memcpy(d4, "                    ", 20);
							diagf = 99u;
						break;
					}				
				}else{ // one of the amulet has been collided
					switch(archer_state){
						case STATE_AMULET_STONE:
							memcpy(d1, "  THE STONE CALICE  ", 20);
							memcpy(d2, "                   ", 20);
							memcpy(d3, "  NOW I CAN THROW   ", 20);
							memcpy(d4, "  STONE ARROWS   +[ ", 20);
							diagf = 30u;					
						break;
						case STATE_AMULET_THUNDER:
							memcpy(d1, "  THE THUNDER HORN  ", 20);
							memcpy(d2, "                    ", 20);
							memcpy(d3, "  NOW I CAN THROW   ", 20);
							memcpy(d4, "  THUNDER ARROWS +# ", 20);
							diagf = 31u;					
						break;
						case STATE_AMULET_ICE:
							memcpy(d1, "  STALAGMITE NECK   ", 20);
							memcpy(d2, "                    ", 20);
							memcpy(d3, "  NOW I CAN THROW   ", 20);
							memcpy(d4, "  ICE ARROWS     +] ", 20);
							diagf = 32u;					
						break;
					}
				}
				break;
		}
	}
	
	if(diagf == 0u){
		switch(current_level){
			case 0u:
				switch(current_map){
					case 0u:
						if (load_next_b == 1){//ho trovato la chiave
							memcpy(d1, "   THIS KEY OPENS   ", 20);
							memcpy(d2, "   THE BLACK WOLF   ", 20);
							memcpy(d3, "   CAVE. LET'S GO.  ", 20);
							memcpy(d4, "                    ", 20);
							diagf = 99u;
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u){
							if (archer->x > (UINT16) 90u << 3 && 
								archer->x < (UINT16) 97u << 3 &&
								archer_data->tool == 0){//sto cercando di parlare col prig che ha la chiave
								if (archer_data->coins < 20u){
									memcpy(d1, "      20 COINS      ", 20);
									memcpy(d2, "     FOR THE KEY    ", 20);
									memcpy(d3, "                    ", 20);
									memcpy(d4, "                    ", 20);
									diagf = 4u;
								}else{
									memcpy(d1, "     THANK YOU      ", 20);
									memcpy(d2, "    HERE IS THE     ", 20);
									memcpy(d3, "       KEY.         ", 20);
									memcpy(d4, "    .. EH EH !      ", 20);
									diagf = 21u;		
								}				
							}else{										
								memcpy(d1, "     WHAT HAVE      ", 20);
								memcpy(d2, "      WE DONE!      ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 4u;								
							}
						}
						else if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 30u){
							memcpy(d1, "       ON THE       ", 20);
							memcpy(d2, "     UPPER LEVEL    ", 20);
							memcpy(d3, "       SOMEONE      ", 20);
							memcpy(d4, "     IS LAUGHING    ", 20);
							diagf = 5u;
						}
						else if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
							memcpy(d1, "                    ", 20);
							memcpy(d2, "      ...MPFH !     ", 20);
							memcpy(d3, "                    ", 20);
							memcpy(d4, "                    ", 20);
							diagf = 6u;
						}
						else if(diagf == 0u){//ho premuto la combo dei diag senza motivo
							if(archer_data->tool == 0){
								memcpy(d1, " I'VE GOT TO FIND   ", 20);
								memcpy(d2, " THE KEY TO ENTER   ", 20);
								memcpy(d3, " THE BLACK WOLF     ", 20);
								memcpy(d4, " CAVE.              ", 20);
							}else{
								memcpy(d1, " I'VE GOT TO FIND   ", 20);
								memcpy(d2, " THE BLACK WOLF     ", 20);
								memcpy(d3, " CAVE.              ", 20);
								memcpy(d4, "                    ", 20);								
							}
							diagf = 99u;
						}
					break;
					case 1u:
						if (tile_collision == 7u){
							if (load_next_b == 1){
								memcpy(d1, "--------------------", 20);
								memcpy(d2, "      CAVE OF THE   ", 20);
								memcpy(d3, "      BLACK WOLF    ", 20);
								memcpy(d4, "--------------------", 20);
								diagf = 19u;
							}else{
								memcpy(d1, "    CAVE OF THE     ", 20);
								memcpy(d2, "    BLACK WOLF. I   ", 20);
								memcpy(d3, "    NEED A KEY TO   ", 20);
								memcpy(d4, "   OPEN THIS DOOR.  ", 20);
								PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
								diagf = 19u;
							}
						}else{
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
								memcpy(d1, "  KEEP... FORWARD.  ", 20);
								memcpy(d2, "                    ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 6u;
							}
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u){
								memcpy(d1, "    THIS IS MOTHER  ", 20);
								memcpy(d2, "   NATURE REVENGE!  ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 4u;
							}
							if(diagf == 0u){
								memcpy(d1, " I CAN SMELL...     ", 20);
								memcpy(d2, " CAVE ENTRANCE      ", 20);
								memcpy(d3, " CAN'T BE FAR.      ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 99u;							
							}
						}
					break;
				}
			break;
			case 1u:
				switch(current_map){
					case 0u:
						memcpy(d1, "LET'S GET OUT       ", 20);
						memcpy(d2, "OF THIS FILTHY      ", 20);
						memcpy(d3, "SEWER.              ", 20);
						memcpy(d4, "              PHUA! ", 20);
						diagf = 99u;
					break;
					case 1u:
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u){
							if (archer_data->tool == 0){//sto cercando di parlare col prig che WRENCH
								memcpy(d1, "     I'LL NEVER     ", 20);
								memcpy(d2, "   GET OUT. PLEASE  ", 20);
								memcpy(d3, "   TAKE MY WRENCH.  ", 20);
								memcpy(d4, "    FREE US ALL!    ", 20);
								diagf = 20u;		
							}else{
								memcpy(d1, "  YOU CAN DO THIS.  ", 20);
								memcpy(d2, "                    ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 6u;
							}
						}
						if (tile_collision == 7u){
							if (archer_data->tool != 0){
								memcpy(d1, "--------------------", 20);
								memcpy(d2, "     SWAMP OF THE   ", 20);
								memcpy(d3, "      ALLIGATOR     ", 20);
								memcpy(d4, "--------------------", 20);
								diagf = 19u;
							}else{
								memcpy(d1, "SWAMP. I NEED       ", 20);
								memcpy(d2, "THE WRENCH TO       ", 20);
								memcpy(d3, "OPEN THIS DOOR.     ", 20);
								memcpy(d4, "                    ", 20);
								PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
								diagf = 99u;
							}
						}
						if(diagf == 0u){
							memcpy(d1, "BLEAH !!            ", 20);
							memcpy(d2, "THE DEEPEST         ", 20);
							memcpy(d3, "THE WORST IS        ", 20);
							memcpy(d4, "GETTING             ", 20);
							diagf = 99u;
						}
					break;
				}
			break;
			case 2u:
				switch(current_map){
					case 0u:
						memcpy(d1, "I NEED DEXTERITY    ", 20);
						memcpy(d2, "TO GET TO THE END   ", 20);
						memcpy(d3, "OF THIS FOREST.     ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "I'D BETTER          ", 20);
						memcpy(d2, "WATCH OUT FROM      ", 20);
						memcpy(d3, "THE BIRDS           ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;					
				}
			break;
			case 3u:
				switch(current_map){
					case 0u:
						memcpy(d1, "BETTER NOT          ", 20);
						memcpy(d2, "FALL. CERTAIN       ", 20);
						memcpy(d3, "DEATH FROM THIS     ", 20);
						memcpy(d4, "HEIGHT !            ", 20);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "AAH-AAH             ", 20);
						memcpy(d2, "AH-AH-AH!           ", 20);
						memcpy(d3, "THUN-               ", 20);
						memcpy(d4, "DERS !!             ", 20);
						diagf = 99u;
					break;
				}
			break;
			case 4u:
				if (tile_collision == 7u){
					memcpy(d1, "THERE IS TOO        ", 20);
					memcpy(d2, "MUCH SILENCE        ", 20);
					memcpy(d3, "FROM HERE ON.       ", 20);
					memcpy(d4, "                    ", 20);
					PlayFx(CHANNEL_1, 3, 0x0D, 0x01, 0x43, 0x73, 0x86);
					diagf = 99u;
				}else{							
					memcpy(d1, "I HAVE TO GO        ", 20);
					memcpy(d2, "BELOW THESE         ", 20);
					memcpy(d3, "DEATHLY TREES       ", 20);
					memcpy(d4, "                    ", 20);
					diagf = 99u;
				}
			break;
			case 5u:
				switch(current_map){
					case 0u:
						memcpy(d1, "I AM FREEZING!      ", 20);
						memcpy(d2, "STALATTITE MAKES    ", 20);
						memcpy(d3, "STALAGMITE GROW. CAN", 20);
						memcpy(d4, "I USE THESE DROPS ? ", 20);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "THIS CAVE IS COLLAP ", 20);
						memcpy(d2, "SING! I CAN SEE  A  ", 20);
						memcpy(d3, "LAKE STRAIGHT AHEAD.", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;
				}
			break;
			case 6u:
				switch(current_map){
					case 0u:
						switch(archer_state){
							case STATE_AMULET_FIRE:
								memcpy(d1, "  VULKAN PYRAMID    ", 20);
								memcpy(d2, "                    ", 20);
								memcpy(d3, "  NOW I CAN THROW   ", 20);
								memcpy(d4, "  FIRE ARROWS    +@ ", 20);
								diagf = 33u;					
							break;
							default:
								memcpy(d1, "   OPENED CASKETS   ", 20);
								memcpy(d2, "   CLOSED CASKETS   ", 20);
								memcpy(d3, "  NOW I AM SCARED.  ", 20);
								memcpy(d4, "        MOM ?       ", 20);
								diagf = 99u;							
							break;
						}
					break;
				}
			break;
		}
	}
	
	return diagf;
}
