#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "string.h"
#include "Scroll.h"
#include "Sound.h"
#include "gbt_player.h"

#include "custom_datas.h"

extern UINT8 current_map;
extern UINT8 current_level;
extern UINT8 current_camera_state;
extern UINT8 current_camera_counter;
extern UINT8 current_cutscene;

unsigned char d1[21];
unsigned char d2[21];
unsigned char d3[21];
unsigned char d4[21];

INT8 is_on_boss = -1;
extern INT8 is_on_cutscene;
struct ArcherInfo* archer_data;
struct CagedbossInfo* cagedboss_data;
UINT8 tile_collision = 0u;
ARCHER_STATE archer_state;
extern UINT8 current_cutscene;
extern UINT8 current_level_b;
extern INT8 load_next_b;
extern INT8 on_worldmap;
extern UINT8 colliding_mother;
extern UINT8 quiver;
extern UINT8 paused;
extern UINT8 wait_c;


UINT8 Build_Next_Dialog_Banked(Sprite* archer) BANKED{
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
				memcpy(d2, "      THE SKY       ", 20);
				memcpy(d3, "    IS THE LIMIT    ", 20);
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
				memcpy(d2, "    PET CEMATERY    ", 20);
				memcpy(d3, "                    ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 16u;
			break;
			case 7u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "     THE CASTLE     ", 20);
				memcpy(d3, "      OF FEAR       ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 17u;
			break;
			case 8u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "       FLYING       ", 20);
				memcpy(d3, "       ARROWS       ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 13u;
			break;
			case 9u:
				memcpy(d1, "                    ", 20);
				memcpy(d2, "       FINAL        ", 20);
				memcpy(d3, "       FIGHT        ", 20);
				memcpy(d4, "                    ", 20);
				diagf = 18u;
			break;
		}
		on_worldmap = 0;
	}
	
	if(is_on_cutscene == 1){
		switch(current_cutscene){
			case 1u:
				memcpy(d1, "  WE HAVE TO PLACE  ", 20);
				memcpy(d2, "  ALL THE AMULETS   ", 20);
				memcpy(d3, "  AROUND THE DOOR   ", 20);
				memcpy(d4, "  ENTRANCE          ", 20);
				diagf = 99u;
			break;
			case 2u:
				switch (wait_c){
					case 41:
						memcpy(d1, " MOM: SON! THIS GUY ", 20);
						memcpy(d2, " IS ABUSING THE     ", 20);
						memcpy(d3, " WILD ANIMALS !!    ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;
					case 42:
						memcpy(d1, " ???: UUH! I WOULD  ", 20);
						memcpy(d2, " CALL IT TEACHING   ", 20);
						memcpy(d3, " RESPECT TO HUMANS  ", 20);
						memcpy(d4, "  ... AGAIN!        ", 20);
						diagf = 99u;
					break;
					case 43:
						memcpy(d1, " MOM: NO! THE WORLD ", 20);
						memcpy(d2, " CAN NOT GO BACK    ", 20);
						memcpy(d3, " LIKE THAT !! WE    ", 20);
						memcpy(d4, " FIGHT AGAINST IT!  ", 20);
						diagf = 99u;
					break;
					case 44:
						memcpy(d1, " ???:                ", 20);
						memcpy(d3, " FEELING SORRY FOR   ", 20);
						memcpy(d4, " THE HUMANS WARDENS? ", 20);
						memcpy(d2, " ARE YOU REALLY      ", 20);
						diagf = 99u;
					break;
					case 45:
						memcpy(d1, "                     ", 20);
						memcpy(d2, " MOTHER!             ", 20);
						memcpy(d3, " LET S TAKE HIM DOWN ", 20);
						memcpy(d4, "                     ", 20);
						diagf = 99u;
					break;
					case 46:
						memcpy(d1, "     SKREEEETCH !!   ", 20);
						memcpy(d3, " I AM COMING FOR YOU ", 20);
						memcpy(d4, "       MASTER        ", 20);
						memcpy(d2, "                     ", 20);
						diagf = 53u;
					break;
				}
			break;
			case 3u:
				switch (wait_c){
					case 40u:
						memcpy(d1, "  ARCHER:           ", 20);
						memcpy(d2, "                    ", 20);
						memcpy(d3, "  WAIT... WHAT ?!   ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;				
					case 43u:
						memcpy(d1, "  ARCHER:           ", 20);
						memcpy(d3, "  MOTHER! HELP ME   ", 20);
						memcpy(d4, "  GET HIM !!  -      ", 20);
						memcpy(d2, "                    ", 20);
						diagf = 99u;
					break;					
					case 45:
						memcpy(d1, "  MOM:              ", 20);
						memcpy(d2, "  GO SON!           ", 20);
						memcpy(d3, "  RIDE MY ARROW AND ", 20);
						memcpy(d4, "  GET HIM !         ", 20);
						diagf = 60u;
					break;
				}
			break;
			case 4u:	
				switch (wait_c){
					case 45u:				
						memcpy(d1, " ???: WHY YOU WANT  ", 20);
						memcpy(d2, " TO BE PUNISHED ?   ", 20);
						memcpy(d3, " GET OUT OF MY WAY  ", 20);
						memcpy(d4, " OR ... !           ", 20);
						diagf = 99u;
					break;
					case 46u:				
						memcpy(d1, " ... OR WHAT ?      ", 20);
						memcpy(d2, " MOTHER IS NOT HERE ", 20);
						memcpy(d3, " NOW. IT IS JUST YOU", 20);
						memcpy(d4, " AND ME. NO MERCY ! ", 20);
						is_on_cutscene = 0;
						wait_c = 99u;
						current_camera_state = 2u;
						diagf = 1u;
					break;
				}
			break;			
			case 5u:	
				switch (wait_c){
					case 40u:				
						memcpy(d1, " ???:               ", 20);
						memcpy(d2, " ... YOU ....       ", 20);
						memcpy(d3, "    ... WHY ? ...   ", 20);
						memcpy(d4, "    AAAAAAHH !      ", 20);
						diagf = 99u;
					break;
					case 41u:				
						memcpy(d1, " ALLIGATOR:         ", 20);
						memcpy(d2, "            ....    ", 20);
						memcpy(d3, "                    ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;
				}
			break;
		}
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
		16	Stage Cematery
		17  Stage Castle
		19	Door - key ok
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
		60	Mother
		88  Cat Tomb
		90  Suggestion with error
		98  Paused
		99 	Suggestion
	
	*/

	if(paused && diagf == 0u){
		memcpy(d1, "    AMULETS OWNED   ", 20);
		if((quiver & 0b0000000010) == 0b0000000010){// ho stone calice
				memcpy(d2, "         $          ", 20);
		}
		if((quiver & 0b0000000100) == 0b0000000100 && (quiver & 0b0000000010) == 0b0000000010){// ho thunder horn
			memcpy(d2, "        $ [         ", 20);
		}
		if((quiver & 0b0000000100) == 0b0000000100 && (quiver & 0b0000000010) == 0b0000000010 && (quiver & 0b0000001000) == 0b0000001000){// ho ice kneckle
			memcpy(d2, "       $ [ #        ", 20);
		}
		if((quiver & 0b0000000100) == 0b0000000100 && (quiver & 0b0000000010) == 0b0000000010 && (quiver & 0b0000001000) == 0b0000001000  && (quiver & 0b0000010000) == 0b0000010000){// ho ice kneckle
			memcpy(d2, "      $ [ # ]       ", 20);
		}			
		memcpy(d3, " PRESS DOWN-JUMP TO ", 20);
		memcpy(d4, " GET SUGGESTIONS.   ", 20);
		diagf = 98u;
	}

	if(diagf == 0u){
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
					case 9u:
						memcpy(d1, "                    ", 20);
						memcpy(d2, "   GET OVER HERE !  ", 20);
						memcpy(d3, "                    ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 57u;
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
					case 9u:
						memcpy(d1, "                    ", 20);
						memcpy(d2, "   GET OVER HERE !  ", 20);
						memcpy(d3, "                    ", 20);
						memcpy(d4, "                    ", 20);
						current_camera_state = 3u;
						diagf = 57u;
					break;
				}	
			break;
			case 2://is_on_boss == 2 significa che lo sto combattendo			
				switch(current_level_b){
					case 0u:
						memcpy(d1, " THE WOLF IS FAST   ", 20);
						memcpy(d2, " AND STRONG.        ", 20);
						memcpy(d3, " I SHOULD AIM TO    ", 20);
						memcpy(d4, " HIS BELLY !        ", 20);
						diagf = 99u;
					break;
					case 1u:				
						memcpy(d1, " NORMAL ARROWS DO   ", 20);
						memcpy(d2, " NOT WORK. I SHOULD ", 20);
						memcpy(d3, " USE THOSE SPECIAL  ", 20);
						memcpy(d4, " ARROW CONVERTERS.  ", 20);
						diagf = 99u;
					break;
					case 2u:				
						memcpy(d1, " VERTICAL ARROWS DO ", 20);
						memcpy(d2, " NOT WORK. I SHOULD ", 20);
						memcpy(d3, " STRIKE WITH        ", 20);
						memcpy(d4, " HORIZONTALS.       ", 20);
						diagf = 99u;
					break;
					case 3u:				
						memcpy(d1, " MY ARROWS DO NOT   ", 20);
						memcpy(d2, " WORK! I SHOULD TRY ", 20);
						memcpy(d3, " WITH THOSE SPECIAL ", 20);
						memcpy(d4, " ARROW CONVERTERS.   ", 20);
						diagf = 99u;
					break;
					case 4u:
						memcpy(d1, " I SHOULD USE THE   ", 20);
						memcpy(d2, " ARROW BOUNCER TO   ", 20);
						memcpy(d3, " STRIKE FASTER.     ", 20);
						memcpy(d4, "                    ", 20);
						diagf = 99u;
					break;
					case 5u:				
						memcpy(d1, " ARROWS DO NOT WORK ", 20);
						memcpy(d2, " WHILE WALRUS IS    ", 20);
						memcpy(d3, " SPINNING. I SHOULD ", 20);
						memcpy(d4, " GET HIM JUMPING.   ", 20);
						diagf = 99u;
					break;
				}
			break;
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
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 4u){
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
						else if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 30u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 30u){
							memcpy(d1, "       ON THE       ", 20);
							memcpy(d2, "     UPPER LEVEL    ", 20);
							memcpy(d3, "       SOMEONE      ", 20);
							memcpy(d4, "     IS LAUGHING    ", 20);
							diagf = 5u;
						}
						else if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 58u){
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
								diagf = 90u;
							}
						}else{
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 58u){
								memcpy(d1, "  KEEP... FORWARD.  ", 20);
								memcpy(d2, "                    ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 6u;
							}
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 4u){
								memcpy(d1, "    THIS IS MOTHER  ", 20);
								memcpy(d2, "   NATURE REVENGE!  ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 4u;
							}
							if(diagf == 0u){
								memcpy(d1, " I SMELL SOMETHING. ", 20);
								memcpy(d2, " WOLF'S CAVE CAN'T  ", 20);
								memcpy(d3, "       BE FAR.      ", 20);
								memcpy(d4, "      LET'S GO!     ", 20);
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
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 58u){
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
								diagf = 90u;
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
						memcpy(d1, "BETTER NOT TO       ", 20);
						memcpy(d2, "FALL. CERTAIN       ", 20);
						memcpy(d3, "DEATH FROM THIS     ", 20);
						memcpy(d4, "HEIGHT !            ", 20);
						diagf = 99u;
					break;
					case 1u:
						memcpy(d1, "IF I TURN MY BACK   ", 20);
						memcpy(d2, "THE THUNDERS        ", 20);
						memcpy(d3, "JUST STOP!          ", 20);
						memcpy(d4, "                    ", 20);
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
								memcpy(d3, "  NOW I AM SCARED... ", 20);
								memcpy(d4, "        MOM ?       ", 20);
								diagf = 99u;							
							break;
						}
					break;
					case 1u:
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 88u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 88u){
							memcpy(d1, "                    ", 20);
							memcpy(d2, " THIS IS THE NICEST ", 20);
							memcpy(d3, " CAT I'VE EVER SEEN.", 20);
							memcpy(d4, "                    ", 20);
							diagf = 88u;
						}else{
							memcpy(d1, "  THE CASTLE IS AT  ", 20);
							memcpy(d2, "  THE END OF THIS   ", 20);
							memcpy(d3, "  CEMATERY.         ", 20);
							memcpy(d4, "                    ", 20);
							diagf = 99u;	
						}
					break;
					case 2u:
						switch (colliding_mother){
							case 0u:
								memcpy(d1, "  MOTHEEEEEEEEEER !!", 20);
								memcpy(d2, "                    ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 99u;
							break;
							case 1u:
								memcpy(d1, "     ... MOM!       ", 20);
								memcpy(d2, "   HOW ARE YOU ?    ", 20);
								memcpy(d3, "   I AM SO SCARED   ", 20);
								memcpy(d4, "       HERE!        ", 20);
								colliding_mother = 2u;
								diagf = 1u;
							break;
							case 2u:
								if((quiver & 0b0000010000) == 0b0000010000){// ho vulkan pyramid
									memcpy(d1, "                    ", 20);
									memcpy(d2, "   LET'S GET INTO   ", 20);
									memcpy(d3, "    THE CASTLE.     ", 20);
									memcpy(d4, "                    ", 20);
									colliding_mother = 3u;
									//current_map = 0u;
								}else{
									memcpy(d1, " GO BACK TO THE     ", 20);
									memcpy(d2, " CRYPT, I HAVE HID  ", 20);
									memcpy(d3, " DEN THE VULKAN PYRA", 20);
									memcpy(d4, " MID UNDERGROUND.   ", 20);
									colliding_mother = 4u;
								}
								diagf = 60u;
							break;
							case 3u: //ho vulkan pyramid
								colliding_mother = 7u;
								diagf = 99u;
								//colliding_mother = 5u;
								//diagf = 60u;
							break;
							case 4u: //non ho vulkan pyramid
								colliding_mother = 6u;
								
								diagf = 60u;
							break;
							case 5u:
								colliding_mother = 7u;
								diagf = 99u;
							break;
						}	
					break;
				}
			break;
			case 7u:
				switch(current_map){
					case 0u:
						switch(archer->type){
							case SpriteMother:
								if(archer->y < ((UINT16) 36 << 3)){
									memcpy(d1, "                    ", 20);
									memcpy(d2, "  THE ANSWER IS     ", 20);
									memcpy(d3, "  SO CLOSE NOW !!   ", 20);
									memcpy(d4, "                    ", 20);
									diagf = 60u;
								}else if (archer->y < ((UINT16) 65 << 3)){
									memcpy(d1, "                    ", 20);
									memcpy(d2, " WHY DO I SMELL     ", 20);
									memcpy(d3, " THE FOREST NOW ?   ", 20);
									memcpy(d4, "                    ", 20);
									diagf = 99u;
								}else if (archer->y < ((UINT16) 100 << 3)){
									memcpy(d1, " WHY DO I SMELL     ", 20);
									memcpy(d2, " LIKE ...           ", 20);
									memcpy(d3, " LIKE SOMETHING IS  ", 20);
									memcpy(d4, " BURNING ?          ", 20);
									diagf = 99u;
								}else if (archer->y < ((UINT16) 113 << 3)){
									memcpy(d1, " WHY DO I SMELL     ", 20);
									memcpy(d2, " OF THE ZOO ?       ", 20);
									memcpy(d3, " SO WEIRD  TO SMELL ", 20);
									memcpy(d4, " IT HERE AND NOW ...", 20);
									diagf = 99u;
								}else{
									memcpy(d1, " WAIT HERE MY SON.  ", 20);
									memcpy(d2, " FROM NOW ON IT IS  ", 20);
									memcpy(d3, " ON ME.             ", 20);
									memcpy(d4, " TRUST ME !         ", 20);
									diagf = 60u;
								}
							break;
							case SpriteCagedboss:
								cagedboss_data = (struct CagedbossInfo*)archer->custom_data;
								switch(cagedboss_data->state){
									case CAGEDBOSS_IDLE:
										memcpy(d1, " MY PETS HAVE BEEN  ", 20);
										memcpy(d2, " PUNISHED FOR THEIR ", 20);
										memcpy(d3, " FAILURES. WHAT DO  ", 20);
										memcpy(d4, " YOU WANT DOCTOR ?  ", 20);
										diagf = 57u;
										current_map = 1;
									break;
									case WOLF_CAGED:
									case IBEX_CAGED:
									case BEAR_CAGED:
										switch(cagedboss_data->hit){
											case 0:
												memcpy(d1, "   THANK YOU FOR    ", 20);
												memcpy(d2, "   HEALING ME ...   ", 20);
												memcpy(d3, "   NOW YOU ARE MY   ", 20);
												memcpy(d4, "   MASTER.          ", 20);
												if(cagedboss_data->state == WOLF_CAGED){
													diagf = 51u;
												}else if(cagedboss_data->state == IBEX_CAGED){
													diagf = 54u;
												}else if(cagedboss_data->state == BEAR_CAGED){
													diagf = 55u;
												}											
											break;
											case 1:
												memcpy(d1, "                    ", 20);
												memcpy(d2, "   GRRRRRRRR  !!    ", 20);
												memcpy(d3, "                    ", 20);
												memcpy(d4, "                    ", 20);
												diagf = 99u;												
											break;
										}
									break;
								}
							break;		
						}			
					break;
					case 1u://sono appena entrato nel livello 7.1					
						switch(archer->type){
								case SpritePlayer:
								memcpy(d1, "                    ", 20);
								memcpy(d2, "     MOTHEEEER !    ", 20);
								memcpy(d3, "                    ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 1u;
							break;	
						}
					break;
				}
			break;
			case 8u:
				switch(current_map){
					case 0u://triggered at the end of level 8.0
						switch(archer->type){
							case SpritePlayer:
								memcpy(d1, "  WE END THIS NOW.  ", 20);
								memcpy(d2, "                    ", 20);
								memcpy(d3, "   LAND! MY EAGLE.  ", 20);
								memcpy(d4, "                    ", 20);
								diagf = 57u;
							break;	
						}
					break;
				}
			break;
		}
	}
	
	return diagf;
}
