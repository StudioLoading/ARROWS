#include "Banks/SetAutoBank.h"

#include "SGB.h"
#include "Palette.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Palette.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "string.h"
#include "Print.h"
#include "Fade.h"
#include "Music.h"

#include "custom_datas.h"
#include "TilesAnimations0.h"
#include "sgb_palette.h"

IMPORT_TILES(tilescredit);
IMPORT_TILES(font);

IMPORT_MAP(mapcreditfinal);

//DECLARE_MUSIC(bgm_boss_defeated);

extern UINT8 J_JUMP;
extern UINT8 J_FIRE;
extern UINT8 thunder_delay;
extern INT8 temporeggia;
extern UINT8 updatecounter;
extern UINT8 current_map;
extern UINT8 current_level;
extern UINT8 current_cutscene;

const UINT8 collision_tiles_credits_final[] = {1,0};

UINT8 credit_step_final;
UINT8 wait_time_final;
UINT8 on_worldmap_final;
struct CameraInfo* camerainfo_data = 0;

void START() {
	credit_step_final = 0u;
	wait_time_final = 0u;
	on_worldmap_final = 0;
	thunder_delay = 0;
	InitScroll(BANK(mapcreditfinal), &mapcreditfinal, collision_tiles_credits_final, 0);
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, ((INT16) 10u << 3), ((UINT16) 7u << 3));
	camerainfo_data = (struct CameraInfo*) scroll_target->custom_data;
	camerainfo_data->final_y = ((UINT16) 25u << 3);	
	temporeggia = 0;
	updatecounter = 0u;
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	//NR50_REG = 0x44; //Max volume 0x77
	//PlayMusic(bgm_boss_defeated, 1);

	INIT_FONT(font, PRINT_BKG);
	SHOW_BKG;
	
}

void UPDATE() {
	wait_time_final += 1u;
	UINT8 cb = 0;

	//START ANIMATION
	switch(thunder_delay){
		case 20u:
			Anim_StudioLoading_1();
		break;		
		case 40u:
			Anim_StudioLoading_0();
			thunder_delay = 0;
		break;
	}
	thunder_delay++;
	//END ANIMATION

	temporeggia++;
	if(credit_step_final == 4u){
		temporeggia = -100;
		if(scroll_target->y < camerainfo_data->final_y){
			scroll_target->y++;
		}else{
			credit_step_final = 5u;
		}
	}
	if(credit_step_final == 7u){
		temporeggia = -100;
		if(scroll_target->y < camerainfo_data->final_y){
			scroll_target->y++;
		}else{
			credit_step_final = 8u;
		}
	}
	if(credit_step_final == 11u){
		temporeggia = -100;
		if(scroll_target->y < camerainfo_data->final_y){
			scroll_target->y++;
		}else{
			credit_step_final = 12u;
		}
	}
	switch(temporeggia){
		case 120:
			switch(credit_step_final){
				case 0u:
					PRINT(3u, 1u, "FLYING ARROWS");
					PRINT(3u, 2u, "IS A PRODUCT");
					PRINT(3u, 3u, "DESIGNED BY");
					credit_step_final = 1u;
				break;
				case 1u:
					PRINT(3u, 1u, "              ");
					PRINT(3u, 2u, "              ");
					PRINT(3u, 3u, "GRAPHICS BY   ");
					credit_step_final = 3u;
				break;
				case 3u:
					PRINT(3u, 1u, "              ");
					PRINT(3u, 2u, "              ");
					PRINT(3u, 3u, "PRODUCED BY   ");
					credit_step_final = 4u;
				break;
				case 5u:
					PRINT(3u, 21u, "SPECIAL THANKS");
					PRINT(3u, 22u, "              ");
					PRINT(3u, 23u, "TO SPECIAL    ");
					PRINT(3u, 24u, "              ");
					PRINT(3u, 25u, "KICKSTARTER    ");
					PRINT(3u, 26u, "              ");
					PRINT(3u, 27u, "BACKERS:      ");
					credit_step_final = 6u;
				break;
				case 6u:
					camerainfo_data->final_y = ((UINT16) 41u << 3);
					credit_step_final = 7u;
				break;
				case 8u:
					PRINT(2u, 32u, "                 ");
					PRINT(2u, 33u, "                 ");
					PRINT(2u, 34u, "                 ");
					PRINT(2u, 35u, "                 ");
					PRINT(2u, 36u, "HEXADIGITAL      ");
					PRINT(2u, 37u, "                 ");
					PRINT(2u, 38u, "HAYDEN CRIST     ");
					PRINT(2u, 39u, "                  ");
					PRINT(2u, 40u, "ELIZABETH GORMAN  ");
					PRINT(2u, 41u, "                  ");
					PRINT(2u, 42u, "SI PITTMAN          ");
					credit_step_final = 9u;
				break;
				case 9u:
					PRINT(2u, 36u, "AWESOME JACKET    ");
					PRINT(2u, 37u, "   DUDE KS        ");
					PRINT(2u, 38u, "                 ");
					PRINT(2u, 39u, "RICHARD DAVEY    ");
					PRINT(2u, 40u, "                 ");
					PRINT(2u, 41u, "CAYLEN LEPPY  ");
					PRINT(2u, 42u, "  WILLIAMS    ");
					credit_step_final = 10u;
				break;
				case 10u:
					camerainfo_data->final_y = ((UINT16) 51u << 3);
					credit_step_final = 11u;
				break;
				case 12u:
					PRINT(2u, 49u, "MEANWHILE         ");
					PRINT(2u, 50u, "                 ");
					PRINT(2u, 51u, "IN THE SEWERS ...");
					credit_step_final = 13u;
				break;
				case 13u:
					current_level = 11u;
					current_map = 0u;
					current_cutscene = 20u;
					SetState(StateWorldmap);
				break;
			}
			temporeggia = -100;
		break;
	}


}
