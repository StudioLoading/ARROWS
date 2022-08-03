#include "Banks/SetAutoBank.h"

#include "Keys.h";
#include "ZGBMain.h";
#include "Scroll.h";
#include "SpriteManager.h";
#include "Palette.h";
#include "string.h";
#include "Print.h";
#include "Sound.h";
#include "Music.h";

#include "custom_datas.h";
#include "Dialogs.h";
#include "sgb_palette.h";


IMPORT_TILES(font);
IMPORT_TILES(tiles);

IMPORT_MAP(maplevel0zoo);
IMPORT_MAP(maplevel1sewer);
IMPORT_MAP(maplevel2forest);
IMPORT_MAP(maplevel3sky);
IMPORT_MAP(maplevel4jungle);
IMPORT_MAP(maplevel5icecave);
IMPORT_MAP(maplevel6cematery);
IMPORT_MAP(maplevel7castle);

IMPORT_MAP(mapdiagarcher);
IMPORT_MAP(mapdiagslave1);
IMPORT_MAP(mapdiagslave2);
IMPORT_MAP(mapdiagslave3);
IMPORT_MAP(mapdiagkey);
IMPORT_MAP(mapdiagwrench);
IMPORT_MAP(mapdiagwolf);
IMPORT_MAP(mapdiagcave);
IMPORT_MAP(mapdiaggator);
IMPORT_MAP(mapdiageagle);
IMPORT_MAP(mapdiagibex);
IMPORT_MAP(mapdiagbear);
IMPORT_MAP(mapdiagwalrus);
IMPORT_MAP(mapdiagmother);
IMPORT_MAP(mapdiagfinalboss);

IMPORT_MAP(mapdiagamuletstone);
IMPORT_MAP(mapdiagamuletthunder);
IMPORT_MAP(mapdiagamuletice);
IMPORT_MAP(mapdiagamuletfire);

IMPORT_MAP(diagslave1);
IMPORT_MAP(diagslave2);
IMPORT_MAP(diagslave3);
IMPORT_MAP(diagkey);
IMPORT_MAP(diagwrench);
IMPORT_MAP(diagwolf);
IMPORT_MAP(diagcave);
IMPORT_MAP(diaggator);
IMPORT_MAP(diageagle);
IMPORT_MAP(diagibex);
IMPORT_MAP(diagbear);
IMPORT_MAP(diagwalrus);

IMPORT_MAP(diagamuletstone);
IMPORT_MAP(diagamuletthunder);
IMPORT_MAP(diagamuletice);
IMPORT_MAP(diagamuletfire);

IMPORT_MAP(mapdiagtomb);


extern UINT16 bg_palette[];
extern UINT16 sprites_palette[];
extern UINT8 amulet ;
extern UINT16 drop_player_x;
extern UINT16 drop_player_y;

extern INT8 level_tool;
extern UINT8 current_level;
extern UINT8 current_map;
extern INT8 is_on_boss;

extern INT8 show_diag;
extern INT8 showing_diag;

extern unsigned char d1[];
extern unsigned char d2[];
extern unsigned char d3[];
extern unsigned char d4[];

extern UINT8 diag_found;
extern UINT8 colliding_mother;

extern INT8 is_on_cutscene;

//const UINT16 const bg_palette_diag[] = {PALETTE_FROM_HEADER(tiles)};
const UINT8 const collision_dtiles[] = {0,0};


void START() {

	reset_sgb_palette_statusbar();

	HIDE_WIN;
	//PlayMusic(loop0, 1);
	
	switch(diag_found){
		case 0u:
		case 1u:
		case 2u:
		case 3u:
			if(sgb_check()){
				set_sgb_palette01_TITLEINVERTED();
			}
			InitScroll(BANK(mapdiagarcher), &mapdiagarcher, collision_dtiles, 0);
		break;
		case 4u:
			if(sgb_check()){
				set_sgb_palette01_EAGLE();
			}
			InitScroll(BANK(mapdiagslave1), &mapdiagslave1, collision_dtiles, 0);
		break;
		case 5u:
			if(sgb_check()){
				set_sgb_palette01_TITLEINVERTED();
			}
			InitScroll(BANK(mapdiagslave2), &mapdiagslave2, collision_dtiles, 0);
		break;
		case 6u:
			if(sgb_check()){
				set_sgb_palette01_1D();
			}
			InitScroll(BANK(mapdiagslave3), &mapdiagslave3, collision_dtiles, 0);
		break;
		case 10u:
			if(sgb_check()){
				set_sgb_palette01_TITLEINVERTED();
			}
			InitScroll(BANK(maplevel0zoo), &maplevel0zoo, collision_dtiles, 0);
		break;
		case 11u:
			if(sgb_check()){
				set_sgb_palette01_SEWER();
			}
			InitScroll(BANK(maplevel1sewer), &maplevel1sewer, collision_dtiles, 0);
		break;
		case 12u:
			if(sgb_check()){
				set_sgb_palette01_FOREST();
			}
			InitScroll(BANK(maplevel2forest), &maplevel2forest, collision_dtiles, 0);
		break;
		case 13u:
			if(sgb_check()){
				set_sgb_palette01_1B();
			}
			InitScroll(BANK(maplevel3sky), &maplevel3sky, collision_dtiles, 0);
		break;
		case 14u:
			if(sgb_check()){
				set_sgb_palette01_TREES();
			}
			InitScroll(BANK(maplevel4jungle), &maplevel4jungle, collision_dtiles, 0);
		break;
		case 15u:
			if(sgb_check()){
				set_sgb_palette01_ICE();
			}
			InitScroll(BANK(maplevel5icecave), &maplevel5icecave, collision_dtiles, 0);
		break;
		case 16u:
			if(sgb_check()){
				set_sgb_palette01_CEMATERYCRYPT();
			}
			InitScroll(BANK(maplevel6cematery), &maplevel6cematery, collision_dtiles, 0);
		break;
		case 17u:
			if(sgb_check()){
				set_sgb_palette01_CASTLE();
			}
			InitScroll(BANK(maplevel7castle), &maplevel7castle, collision_dtiles, 0);
		break;
		case 19u:
			if(sgb_check()){
				set_sgb_palette01_2E();
			}
			InitScroll(BANK(mapdiagcave), &mapdiagcave, collision_dtiles, 0);
		break;
		case 20u:
			if(sgb_check()){
				set_sgb_palette01_2H();
			}
			InitScroll(BANK(mapdiagwrench), &mapdiagwrench, collision_dtiles, 0);
		break;
		case 21u:
			if(sgb_check()){
				set_sgb_palette01_2H();
			}
			InitScroll(BANK(mapdiagkey), &mapdiagkey, collision_dtiles, 0);
		break;
		case 30u:
			if(sgb_check()){
				set_sgb_palette01_2H();
			}
			InitScroll(BANK(mapdiagamuletstone), &mapdiagamuletstone, collision_dtiles, 0);
		break;
		case 31u:
			if(sgb_check()){
				set_sgb_palette01_AMULET_THUNDER();
			}
			InitScroll(BANK(mapdiagamuletthunder), &mapdiagamuletthunder, collision_dtiles, 0);
		break;
		case 32u:
			if(sgb_check()){
				set_sgb_palette01_AMULET_ICE();
			}
			InitScroll(BANK(mapdiagamuletice), &mapdiagamuletice, collision_dtiles, 0);
		break;
		case 33u:
			if(sgb_check()){
				set_sgb_palette01_1B();
			}
			InitScroll(BANK(mapdiagamuletfire), &mapdiagamuletfire, collision_dtiles, 0);
		break;
		case 51u:
			if(sgb_check()){
				set_sgb_palette01_WOLF();
			}			
			InitScroll(BANK(mapdiagwolf), &mapdiagwolf, collision_dtiles, 0);
		break;
		case 52u:
			if(sgb_check()){
				set_sgb_palette01_GATOR();
			}
			InitScroll(BANK(mapdiaggator), &mapdiaggator, collision_dtiles, 0);
		break;
		case 53u:
			if(sgb_check()){
				set_sgb_palette01_EAGLE();
			}			
			InitScroll(BANK(mapdiageagle), &mapdiageagle, collision_dtiles, 0);
		break;
		case 54u:
			if(sgb_check()){
				set_sgb_palette01_IBEX();
			}		
			InitScroll(BANK(mapdiagibex), &mapdiagibex, collision_dtiles, 0);
		break;
		case 55u:
			if(sgb_check()){
				set_sgb_palette01_BEAR();
			}
			InitScroll(BANK(mapdiagbear), &mapdiagbear, collision_dtiles, 0);
		break;
		case 56u:
			if(sgb_check()){
				set_sgb_palette01_WALRUS();
			}
			InitScroll(BANK(mapdiagwalrus), &mapdiagwalrus, collision_dtiles, 0);
		break;
		case 57u:
			if(sgb_check()){
				set_sgb_palette01_BOSS();
			}
			InitScroll(BANK(mapdiagfinalboss), &mapdiagfinalboss, collision_dtiles, 0);
		break;
		case 60u:
			if(sgb_check()){
				set_sgb_palette01_TITLEINVERTED();
			}
			InitScroll(BANK(mapdiagmother), &mapdiagmother, collision_dtiles, 0);
		break;
		case 88u:
			if(sgb_check()){
				set_sgb_palette01_CASTLE();
			}
			InitScroll(BANK(mapdiagtomb), &mapdiagtomb, collision_dtiles, 0);
		break;
	}
	SHOW_BKG;
		
	INIT_FONT(font, PRINT_BKG); 

	PRINT(0u, 13u, d1);
	PRINT(0u, 14u, d2);
	PRINT(0u, 15u, d3);
	PRINT(0u, 16u, d4);
	
}

void UPDATE() {
	
	if(KEY_PRESSED(J_B) || KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
		HIDE_WIN;
		if(is_on_boss >= 0){
			SetState(StateBoss);
		}else if (colliding_mother != 0u && colliding_mother != 6u){
			//0u means just the tip
			//6u means mother told us to go back
			//7u means cutscene!
			diag_found = Build_Next_Dialog_Banked(0);
			switch(colliding_mother){
					//triggera la cutscene di madre e figlio che vanno al portale
				case 7u:
					is_on_cutscene = 1;
					SetState(StateCutscene);
				break;
				case 1u:
				case 2u:
				case 3u:
				case 4u:
				case 5u:
					SetState(StateDiag);
				break;
			}
		}else if(is_on_cutscene){
			SetState(StateCutscene);
		}else{
			colliding_mother = 0u;
			switch(current_level){
				case 0u:
				case 1u:
				case 2u:
					SetState(StateGame);
				break;
				case 3u:
				case 4u:
					SetState(StateGame3);
				break;
				case 5u:
				case 6u:
					SetState(StateGame6);
				break;
				case 7u:
				case 8u:
					SetState(StateGame7);
				break;
			}
		}
	}

}