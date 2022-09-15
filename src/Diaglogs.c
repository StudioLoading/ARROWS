#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "string.h"
#include "Scroll.h"

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
extern UINT8 current_level_b;
extern INT8 load_next_b;
extern INT8 on_worldmap;
extern UINT8 colliding_mother;
extern UINT8 quiver;
extern UINT8 paused;
extern UINT8 wait_c;
extern INT8 boss_hp;

UINT8 Build_Next_Dialog_Banked(Sprite* archer) BANKED;
void copy_strings_to_dn(char* s1, char* s2, char* s3, char* s4);


void copy_strings_to_dn(char* s1, char* s2, char* s3, char* s4){
	memcpy(d1, s1, 20);
	memcpy(d2, s2, 20);
	memcpy(d3, s3, 20);
	memcpy(d4, s4, 20);
}

UINT8 Build_Next_Dialog_Banked(Sprite* archer) BANKED{
	UINT8 diagf = 0u;
	copy_strings_to_dn("                    ","                    ","                    ","                    ");
	if(on_worldmap == 1){
		switch(current_level){
			case 0u:
				copy_strings_to_dn("                    ","       THE ZOO      ","                    ","                    ");
				diagf = 10u;
			break;
			case 1u:
				copy_strings_to_dn("                    ","  THROUGH THE SEWER ","                    ","                    ");
				diagf = 11u;
			break;
			case 2u:
				copy_strings_to_dn("                    ","  RUN TO THE HILLS  ","                    ","                    ");
				diagf = 12u;
			break;
			case 3u:
				copy_strings_to_dn("                    ","      THE SKY       ","    IS THE LIMIT    ","                    ");
				diagf = 13u;
			break;
			case 4u:
				copy_strings_to_dn("                    ","     WELCOME TO     ","     THE JUNGLE     ","                    ");
				diagf = 14u;
			break;
			case 5u:
				copy_strings_to_dn("                    ","      ICE COLD      ","     THE JUNGLE     ","                    ");
				diagf = 15u;
			break;
			case 6u:
				copy_strings_to_dn("                    ","    PET CEMATERY    ","                    ","                    ");
				diagf = 16u;
			break;
			case 7u:
				copy_strings_to_dn("                    ","     THE CASTLE     ","      OF FEAR       ","                    ");
				diagf = 17u;
			break;
			case 8u:
				copy_strings_to_dn("                    ","       FLYING       ","       ARROWS       ","                    ");
				diagf = 13u;
			break;
			case 9u:
				copy_strings_to_dn("                    ","       FINAL        ","       FIGHT        ","                    ");
				diagf = 18u;
			break;
			case 10u:
				copy_strings_to_dn("                    ","       THE ZOO      ","                    ","                    ");
				diagf = 60u;
			break;
			case 11u:
				copy_strings_to_dn("                    ","      THE SEWER     ","                    ","                    ");
				diagf = 11u;
			break;
		}
		on_worldmap = 0;
	}
	
	if(is_on_cutscene == 1){
		copy_strings_to_dn("                    ","                    ","                    ","                    ");
		diagf = 99u;
		switch(current_cutscene){
			case 1u:
				copy_strings_to_dn("  WE HAVE TO PLACE  ","  ALL THE AMULETS   ","  AROUND THE DOOR   ","  ENTRANCE          ");
				diagf = 99u;
			break;
			case 2u:
				switch (wait_c){
					case 41:
						copy_strings_to_dn(" MOM: SON! THIS GUY "," IS ABUSING THE     "," WILD ANIMALS !!    ","                    ");
						diagf = 99u;
					break;
					case 42:
						copy_strings_to_dn(" ???: UUH! I WOULD  "," CALL IT TEACHING   "," RESPECT TO HUMANS  ","  ... AGAIN!        ");
						diagf = 99u;
					break;
					case 43:
						copy_strings_to_dn(" MOM: NO! THE WORLD "," CAN NOT GO BACK    "," LIKE THAT !! WE    "," FIGHT AGAINST IT!  ");
						diagf = 99u;
					break;
					case 44:
						copy_strings_to_dn(" ???:                "," FEELING SORRY FOR   "," THE HUMANS WARDENS? "," ARE YOU REALLY      ");
						diagf = 99u;
					break;
					case 45:
						copy_strings_to_dn("                     "," MOTHER!             "," LET S TAKE HIM DOWN ","                     ");
						diagf = 99u;
					break;
					case 46:
						copy_strings_to_dn("     SKREEEETCH !!   "," I AM COMING FOR YOU ","       MASTER        ","                     ");
						diagf = 53u;
					break;
				}
			break;
			case 3u:
				switch (wait_c){
					case 40u:
						copy_strings_to_dn("  ARCHER:           ","                    ","  WAIT... WHAT ?!   ","                    ");
						diagf = 99u;
					break;				
					case 43u:
						copy_strings_to_dn("  ARCHER:           ","  MOTHER! HELP ME   ","  GET HIM !!  -      ","                    ");
						diagf = 99u;
					break;					
					case 45:
						copy_strings_to_dn("  MOM:              ","  GO SON!           ","  RIDE MY ARROW AND ","  GET HIM !         ");
						diagf = 60u;
					break;
				}
			break;
			case 4u:	
				switch (wait_c){
					case 45u:				
						copy_strings_to_dn(" ???: WHY YOU WANT  "," TO BE PUNISHED ?   "," GET OUT OF MY WAY  "," OR ... !           ");
						diagf = 99u;
					break;
					case 46u:				
						copy_strings_to_dn(" ... OR WHAT ?      "," MOTHER IS NOT HERE "," NOW. IT IS JUST YOU"," AND ME. NO MERCY ! ");
						is_on_cutscene = 0;
						//wait_c = 99u;
						current_camera_state = 2u;
						diagf = 1u;
					break;
				}
			break;			
			case 5u:	
				switch (wait_c){
					case 40u: 
						copy_strings_to_dn(" ???:               "," ... YOU ....       ","    ... WHY ? ...   ","    AAAAAAHH !      ");
						diagf = 99u;
					break;
					case 41u:		
						copy_strings_to_dn(" ALLIGATOR:         ","            ....    ","                    ","                    ");
						diagf = 99u;
					break;
				}
			break;
			case 11u:	
				switch (wait_c){
					case 40u:
						copy_strings_to_dn(" WOLF:              ","       NO MORE      ","     HUMAN ZOO!     ","                    ");
						diagf = 99u;
					break;
					case 42u:
						copy_strings_to_dn("                    ","      THANK YOU      ","        MOTHER      ","                    ");
						diagf = 1u;
					break;
				}
			break;
			case 12u:	
				switch (wait_c){
					case 40u:
						copy_strings_to_dn(" IBEX:              ","    NOW IT IS YOUR  ","   TURN TO FACE MY  ","         HORN !!    ");
						diagf = 99u;
					break;
					case 42u:
						copy_strings_to_dn("                    ","      THANK YOU      ","        MOTHER      ","                    ");
						diagf = 1u;
					break;
				}
			break;
			case 13u:	
				switch (wait_c){
					case 40u:
						copy_strings_to_dn(" BEAR:              ","      LEAVE MY      ","    MASTER ALONE    ","         !!         ");
						diagf = 99u;
					break;
					case 42u:
						copy_strings_to_dn("                    ","      THANK YOU      ","        MOTHER      ","                    ");
						diagf = 1u;
					break;
				}
			break;
			case 20u:	
				switch (wait_c){
					case 40u:
						copy_strings_to_dn(" MOM: GREAT JOB SON! "," FOUR OF THE STRONG  "," EST WILD ANIMALS    "," ARE NOW FREE.        ");
						diagf = 99u;
					break;
					case 42u:
						copy_strings_to_dn(" BLACKIE: THANK YOU  "," DOCTOR AND SON. WHY  "," HAVE YOU DONE THAT ?","                     ");
						diagf = 99u;
					break;
					case 44u:
						copy_strings_to_dn(" BLACKIE:            "," WHY DID YOU GET IN "," ALL OF THIS?        ","                     ");
						diagf = 99u;
					break;
					case 46u:
						copy_strings_to_dn(" MOM: LISTEN TO ME.  "," THE MASTER AND       "," SLAVE RELATIONSHIP  "," IS OVER.            ");
						diagf = 99u;
					break;
					case 48u:
						copy_strings_to_dn(" MOM: ANIMALS NOW    "," HAVE A CONSCIENCE   "," AND ARE FREE TO SET "," THE RELATIONSHIP   ");
						diagf = 99u;
					break;
					case 50u:
						copy_strings_to_dn(" MOM: THEY PREFERE.  ","                     ","                     ","                     ");
						diagf = 99u;
					break;
					case 52u:
						copy_strings_to_dn(" BLACKIE: UUUUUUHH ! "," NO MORE PRISONS !!  "," NO MORE ZOO-ES !!   ","                     ");
						diagf = 99u;
					break;
				}
			break;			
			case 21u:	
				switch (wait_c){
					case 43u:
						copy_strings_to_dn(" ???:                "," THANK YOU MY FRIEND "," WHY MY BEASTS       "," BETRAYED ME ?       ");
						diagf = 99u;
					break;
					case 44u:
						copy_strings_to_dn(" GATOR: I SMELLED    "," THEY FEARED MORE    "," THAT DOCTOR THAN    "," YOU.                ");
						diagf = 99u;
					break;
					case 45u:
						copy_strings_to_dn(" ???: IT'S TIME THEN "," ... IT IS TIME FOR  "," THEM TO WAKE UP     "," ...                 ");
						diagf = 99u;
					break;
					case 46u:
						copy_strings_to_dn(" ???: SOME TIME AGO  "," THEY WERE CALLED    "," LIZARDS. THE MOON   "," CHANGED THEM INTO...");
						diagf = 99u;
					break;
					case 47u:
						copy_strings_to_dn("                     ","     MY DRAGONS !    ","                     ","           (THE END) ");
						diagf = 57u;
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
						copy_strings_to_dn("    A BLACK WOLF    ","  OWNS THE WRENCH   ","  I NEED TO EXIT.   ","    LET'S FIGHT!    ");
						diagf = 19u;
					break;
					case 1u:		
						copy_strings_to_dn("    THE EXIT IS     ","   BEYOND A GATOR   "," I NEED HIS AMULET  ","    LET'S FIGHT!    ");
						diagf = 1u;
					break;
					case 2u:		
						copy_strings_to_dn("    AN EAGLE OWNS   ","      THE KEY I     ","    NEED TO EXIT.   ","     LET'S FIGHT!   ");
						diagf = 1u;
					break;
					case 3u:		
						copy_strings_to_dn("    THE EXIT IS     ","   BEYOND A IBEX    "," I NEED HIS AMULET  ","    LET'S FIGHT!    ");
						diagf = 1u;
					break;
					case 4u:		
						copy_strings_to_dn("       HELLO        ","     TEDDY BEAR !   ","                    ","     LET ME PASS!   ");
						diagf = 1u;
					break;
					case 5u:		
						copy_strings_to_dn("    THE EXIT IS     ","  BEYOND A WALRUS.  "," I NEED HIS AMULET  ","    LET'S FIGHT!    ");
						diagf = 1u;
					break;
					case 9u:		
						copy_strings_to_dn("        UH,         "," FEEL FREE TO TAKE  "," A LOOK UNDER THIS  ","      PLATFORM ...  ");
						diagf = 57u;
					break;
				}
			break;
			case 1:  //is_on_boss == 1
				switch(current_level_b){
					case 0u:		
						copy_strings_to_dn("   BEAST! BACK      ","   TO YOUR CAGE!    ","   -GRRR!           ","                    ");
						current_camera_state = 3u;
						diagf = 51u;
					break;
					case 1u:				
						copy_strings_to_dn("   FILTHY HUMAN !!  ","   I'LL MAKE A      ","   BELT OUT OF      ","   YOUR SKIN.       ");
						current_camera_state = 3u;
						diagf = 52u;
					break;
					case 2u:				
						copy_strings_to_dn(" AS LONG AS I FLY   "," THE SKY IS MINE!   ","HOPE YOU DON'T MIND ","IN MY CLAWS YOU DIE!");
						current_camera_state = 3u;
						diagf = 53u;
					break;
					case 3u:		
						copy_strings_to_dn("  NOBODY HAS EVER   ","  GONE THROUGH MY   ","  THUNDERS! NOW     ","  FACE MY HORNS!    ");
						current_camera_state = 3u;
						diagf = 54u;
					break;
					case 4u:		
						copy_strings_to_dn("        GRRR!       ","                    ","    ROOOOOOOAAAR!   ","                    ");
						current_camera_state = 3u;
						diagf = 55u;
					break;
					case 5u:		
						copy_strings_to_dn(" YOUR ARROWS WON'T  "," BEAT MY HEADBUTTS! "," IS THE ICE NECKLES "," PRETTY OR ISN'T IT?");
						current_camera_state = 3u;
						diagf = 56u;
					break;
					case 9u:		
						copy_strings_to_dn("                    ","   GET OVER HERE !  ","                    ","                    ");
						current_camera_state = 3u;
						diagf = 57u;
					break;
				}	
			break;
			case 2: //is_on_boss == 2 significa che lo sto combattendo			
				switch(current_level_b){
					case 0u:		
						copy_strings_to_dn(" THE WOLF IS FAST   "," AND STRONG.        "," I SHOULD AIM TO    "," HIS BELLY !        ");
						diagf = 99u;
					break;
					case 1u:		
						copy_strings_to_dn(" NORMAL ARROWS DO   "," NOT WORK. I SHOULD "," USE THOSE SPECIAL  "," ARROW CONVERTERS.  ");
						diagf = 99u;
					break;
					case 2u:		
						copy_strings_to_dn(" VERTICAL ARROWS DO "," NOT WORK. I SHOULD "," STRIKE WITH        "," HORIZONTALS.       ");
						diagf = 99u;
					break;
					case 3u:		
						copy_strings_to_dn(" MY ARROWS DO NOT   "," WORK! I SHOULD TRY "," WITH THOSE SPECIAL "," ARROW CONVERTERS.   ");
						diagf = 99u;
					break;
					case 4u:		
						copy_strings_to_dn(" I SHOULD USE THE   "," ARROW BOUNCER TO   "," STRIKE FASTER.     ","                    ");
						diagf = 99u;
					break;
					case 5u:		
						copy_strings_to_dn(" ARROWS DO NOT WORK "," WHILE WALRUS IS    "," SPINNING. I SHOULD "," GET HIM JUMPING.   ");
						diagf = 99u;
					break;
					case 9u: //finalfight, archer->lim_y has the type of arrow shoot
						if(boss_hp < 2){
							copy_strings_to_dn("  I CAN BEAT THIS   ","      GUY ONLY      ","    WITH FLAMING    ","       ARROWS    +@ ");
							diagf = 99u;
						}else{
							switch(archer_data->amulet){
								case 2u: //STONE WOLF		
									copy_strings_to_dn("                    ","    GGGRRRRRR !!    ","                    ","                    ");
									diagf = 51u;
								break;
								case 3u: //BLAST IBEX		
									copy_strings_to_dn("                    ","    GGGRRRRRR !!    ","                    ","                    ");
									diagf = 54u;
								break;
								case 4u: //ICE BEAR	
									copy_strings_to_dn("                    ","    GGGRRRRRR !!    ","                    ","                    ");
									diagf = 55u;
								break;
							}
						}
					break;
				}
			break;
			case 3: // final tip on boss destroyed
				if(archer_state != STATE_AMULET_STONE && archer_state != STATE_AMULET_THUNDER && archer_state != STATE_AMULET_ICE && archer_state != STATE_AMULET_FIRE){
					switch(current_level_b){
						case 0u:
							copy_strings_to_dn("        I...        ","  JUST NEEDED THE   ","  WRENCH TO GO ON   ","   SORRY BLACKIE!   ");
							diagf = 99u;
						break;
						case 1u:
							copy_strings_to_dn("     PRESS SELECT   ","   TO THE [ SYMBOL  "," AND BREAK THE GATE ","                    ");
							diagf = 99u;
						break;
						case 2u:
							copy_strings_to_dn("         I...       ","   JUST NEEDED THE  ","     KEY TO GO ON   ","     SORRY EAGLE!   ");
							diagf = 99u;
						break;
						case 3u:
							copy_strings_to_dn("     PRESS SELECT   ","   TO THE # SYMBOL  "," AND BREAK THE GATE ","                    ");
							diagf = 99u;
						break;
						case 4u:
							copy_strings_to_dn(" I...               "," JUST NEEDED THE    "," WRENCH TO GO       "," ON. SORRY BEAR!    ");
							diagf = 99u;
						break;
						case 5u:
							copy_strings_to_dn("     PRESS SELECT   ","   TO THE ] SYMBOL  "," AND BREAK THE GATE ","                    ");
							diagf = 99u;
						break;
					}				
				}else{ // one of the amulet has been collided
					switch(archer_state){
						case STATE_AMULET_STONE:
							copy_strings_to_dn("  THE STONE CALICE  ","                   ","  NOW I CAN THROW   ","  STONE ARROWS   +[ ");
							diagf = 30u;					
						break;
						case STATE_AMULET_THUNDER:
							copy_strings_to_dn("  THE THUNDER HORN  ","                    ","  NOW I CAN THROW   ","  THUNDER ARROWS +# ");
							diagf = 31u;					
						break;
						case STATE_AMULET_ICE:
							copy_strings_to_dn("  STALAGMITE NECK   ","                    ","  NOW I CAN THROW   ","  ICE ARROWS     +] ");
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
							copy_strings_to_dn("   THIS KEY OPENS   ","   THE BLACK WOLF   ","   CAVE. LET'S GO.  ","                    ");
							diagf = 99u;
						}
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 4u){
							if (archer->x > (UINT16) 90u << 3 && 
								archer->x < (UINT16) 97u << 3 &&
								archer_data->tool == 0){//sto cercando di parlare col prig che ha la chiave
								if (archer_data->coins < 20u){
									copy_strings_to_dn("      20 COINS      ","     FOR THE KEY    ","                    ","                    ");
									diagf = 4u;
								}else{
									copy_strings_to_dn("     THANK YOU      ","    HERE IS THE     ","       KEY.         ","    .. EH EH !      ");
									diagf = 21u;		
								}				
							}else{		
								copy_strings_to_dn("     WHAT HAVE      ","      WE DONE!      ","                    ","                    ");
								diagf = 4u;								
							}
						}
						else if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 30u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 30u){
							copy_strings_to_dn("       ON THE       ","     UPPER LEVEL    ","       SOMEONE      ","     IS LAUGHING    ");
							diagf = 5u;
						}
						else if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 58u){
							copy_strings_to_dn("                    ","      ...MPFH !     ","                    ","                    ");
							diagf = 6u;
						}
						else if(diagf == 0u){//ho premuto la combo dei diag senza motivo
							if(archer_data->tool == 0){
								copy_strings_to_dn(" I'VE GOT TO FIND   "," THE KEY TO ENTER   "," THE BLACK WOLF     "," CAVE.              ");
							}else{
								copy_strings_to_dn(" I'VE GOT TO FIND   "," THE BLACK WOLF     "," CAVE.              ","                    ");
							}
							diagf = 99u;
						}
					break;
					case 1u:
						if (tile_collision == 7u){
							if (load_next_b == 1){
								copy_strings_to_dn("--------------------","      CAVE OF THE   ","      BLACK WOLF    ","--------------------");
								diagf = 19u;
							}else{
								copy_strings_to_dn("    CAVE OF THE     ","    BLACK WOLF. I   ","    NEED A KEY TO   ","   OPEN THIS DOOR.  ");
								diagf = 90u;
							}
						}else{
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 58u){
								copy_strings_to_dn("  KEEP... FORWARD.  ","                    ","                    ","                    ");
								diagf = 6u;
							}
							if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 4u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 4u){
								copy_strings_to_dn("    THIS IS MOTHER  ","   NATURE REVENGE!  ","                    ","                    ");
								diagf = 4u;
							}
							if(diagf == 0u){
								copy_strings_to_dn(" I SMELL SOMETHING. "," WOLF'S CAVE CAN'T  ","       BE FAR.      ","      LET'S GO!     ");
								diagf = 99u;							
							}
						}
					break;
				}
			break;
			case 1u:
				switch(current_map){
					case 0u:
						copy_strings_to_dn(" LET'S GET OUT       "," OF THIS FILTHY      "," SEWER.              ","              PHUA! ");
						diagf = 99u;
					break;
					case 1u:
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 58u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 58u){
							if (archer_data->tool == 0){//sto cercando di parlare col prig che WRENCH
								copy_strings_to_dn("     I'LL NEVER     ","   GET OUT. PLEASE  ","   TAKE MY WRENCH.  ","    FREE US ALL!    ");
								diagf = 20u;		
							}else{
								copy_strings_to_dn("  YOU CAN DO THIS.  ","                    ","                    ","                    ");
								diagf = 6u;
							}
						}
						if (tile_collision == 7u){
							if (archer_data->tool != 0){
								copy_strings_to_dn("--------------------","     SWAMP OF THE   ","      ALLIGATOR     ","--------------------");
								diagf = 19u;
							}else{
								copy_strings_to_dn(" SWAMP. I NEED       "," THE WRENCH TO       "," OPEN THIS DOOR.     ","                    ");
								diagf = 90u;
							}
						}
						if(diagf == 0u){
							copy_strings_to_dn(" BLEAH !!            "," THE DEEPEST         "," THE WORST IS        ", " GETTING             ");
							diagf = 99u;
						}
					break;
				}
			break;
			case 2u:
				switch(current_map){
					case 0u:
						copy_strings_to_dn(" I NEED DEXTERITY    "," TO GET TO THE END   "," OF THIS FOREST.     ","                    ");
						diagf = 99u;
					break;
					case 1u:
						copy_strings_to_dn(" I'D BETTER          "," WATCH OUT FROM      "," THE BIRDS           ","                    ");
						diagf = 99u;
					break;					
				}
			break;
			case 3u:
				switch(current_map){
					case 0u:
						copy_strings_to_dn(" BETTER NOT TO       "," FALL. CERTAIN       "," DEATH FROM THIS     "," HEIGHT !            ");
						diagf = 99u;
					break;
					case 1u:
						copy_strings_to_dn(" IF I TURN MY BACK   "," THE THUNDERS        "," JUST STOP!          ","                    ");
						diagf = 99u;
					break;
				}
			break;
			case 4u:
				if (tile_collision == 7u){
					copy_strings_to_dn(" THERE IS TOO        "," MUCH SILENCE        "," FROM HERE ON.       ","                    ");
					diagf = 99u;
				}else{		
					copy_strings_to_dn(" I HAVE TO GO        "," BELOW THESE         "," DEATHLY TREES       ","                    ");
					diagf = 99u;
				}
			break;
			case 5u:
				switch(current_map){
					case 0u:
						copy_strings_to_dn(" I AM FREEZING!      "," STALATTITE MAKES    "," STALAGMITE GROW. CAN"," I USE THESE DROPS ? ");
						diagf = 99u;
					break;
					case 1u:
						copy_strings_to_dn("THIS CAVE IS COLLAP ","SING! I CAN SEE  A  ","LAKE STRAIGHT AHEAD.","                    ");
						diagf = 99u;
					break;
				}
			break;
			case 6u:
				switch(current_map){
					case 0u:
						switch(archer_state){
							case STATE_AMULET_FIRE:
								copy_strings_to_dn("  VULKAN PYRAMID    ","                    ","  NOW I CAN THROW   ","  FIRE ARROWS    +@ ");
								diagf = 33u;					
							break;
							default:
								copy_strings_to_dn("   OPENED CASKETS   ","   CLOSED CASKETS   ","  NOW I AM SCARED... ","        MOM ?       ");
								diagf = 99u;							
							break;
						}
					break;
					case 1u:
						if(GetScrollTile((archer->x >> 3) +1, (archer->y >> 3)) == 88u || GetScrollTile((archer->x >> 3), (archer->y >> 3)) == 88u){
							copy_strings_to_dn("                    "," THIS IS THE NICEST "," CAT I'VE EVER SEEN.","                    ");
							diagf = 88u;
						}else{
							copy_strings_to_dn("  THE CASTLE IS AT  ","  THE END OF THIS   ","  CEMATERY.         ","                    ");
							diagf = 99u;	
						}
					break;
					case 2u:
						switch (colliding_mother){
							case 0u:
								copy_strings_to_dn("  MOTHEEEEEEEEEER !!","                    ","                    ","                    ");
								diagf = 99u;
							break;
							case 1u:
								copy_strings_to_dn("     ... MOM!       ","   HOW ARE YOU ?    ","   I AM SO SCARED   ","       HERE!        ");
								colliding_mother = 2u;
								diagf = 1u;
							break;
							case 2u:
								if((quiver & 0b0000010000) == 0b0000010000){// ho vulkan pyramid
									copy_strings_to_dn("                    ","   LET'S GET INTO   ","    THE CASTLE.     ","                    ");
									colliding_mother = 3u;
									//current_map = 0u;
								}else{
									copy_strings_to_dn(" GO BACK TO THE     "," CRYPT, I HAVE HID  "," DEN THE VULKAN PYRA"," MID UNDERGROUND.   ");
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
									copy_strings_to_dn("                    ","  THE ANSWER IS     ","  SO CLOSE NOW !!   ","                    ");
									diagf = 60u;
								}else if (archer->y < ((UINT16) 65 << 3)){
									copy_strings_to_dn("                    "," WHY DO I SMELL     "," THE FOREST NOW ?   ","                    ");
									diagf = 99u;
								}else if (archer->y < ((UINT16) 100 << 3)){
									copy_strings_to_dn(" WHY DO I SMELL     "," LIKE ...           "," LIKE SOMETHING IS  "," BURNING ?          ");
									diagf = 99u;
								}else if (archer->y < ((UINT16) 113 << 3)){
									copy_strings_to_dn(" WHY DO I SMELL     "," OF THE ZOO ?       "," SO WEIRD  TO SMELL "," IT HERE AND NOW ...");
									diagf = 99u;
								}else{
									copy_strings_to_dn(" WAIT HERE MY SON.  "," FROM NOW ON IT IS  "," ON ME.             "," TRUST ME !         ");
									diagf = 60u;
								}
							break;
							case SpriteCagedboss:
								cagedboss_data = (struct CagedbossInfo*)archer->custom_data;
								switch(cagedboss_data->state){
									case CAGEDBOSS_IDLE:
										copy_strings_to_dn(" MY PETS HAVE BEEN  "," PUNISHED FOR THEIR "," FAILURES. WHAT DO  "," YOU WANT DOCTOR ?  ");
										diagf = 57u;
										current_map = 1;
									break;
									case WOLF_CAGED:
									case IBEX_CAGED:
									case BEAR_CAGED:
										switch(cagedboss_data->hit){
											case 0:
												copy_strings_to_dn("   THANK YOU FOR    ","   HEALING ME ...   ","   NOW YOU ARE MY   ","   MASTER.          ");
												if(cagedboss_data->state == WOLF_CAGED){
													diagf = 51u;
												}else if(cagedboss_data->state == IBEX_CAGED){
													diagf = 54u;
												}else if(cagedboss_data->state == BEAR_CAGED){
													diagf = 55u;
												}											
											break;
											case 1:
												copy_strings_to_dn("                    ","   GRRRRRRRR  !!    ","                    ","                    ");
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
								copy_strings_to_dn("                    ","     MOTHEEEER !    ","                    ","                    ");
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
								copy_strings_to_dn("  WE END THIS NOW.  ","                    ","   LAND! MY EAGLE.  ","                    ");
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
