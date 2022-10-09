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
UINT8 next_credit_step = 0u;
struct CameraInfo* camerainfo_data = 0;

void START() {
	next_credit_step = 0u;
	credit_step_final = 0u;
	wait_time_final = 0u;
	on_worldmap_final = 0;
	thunder_delay = 0;
	InitScroll(BANK(mapcreditfinal), &mapcreditfinal, collision_tiles_credits_final, 0);
	scroll_target = SpriteManagerAdd(SpriteCamerafocus, ((INT16) 10u << 3), ((UINT16) 7u << 3));
	camerainfo_data = (struct CameraInfo*) scroll_target->custom_data;
	camerainfo_data->final_y = ((UINT16) 29u << 3);	
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

	if(temporeggia <= 30){
		temporeggia++;
	}else{
		if(KEY_RELEASED(J_A) || KEY_RELEASED(J_B)){
			temporeggia = 0;
			credit_step_final += 1u;
			next_credit_step = 1u;
		}
	}
	if(next_credit_step == 1u){
		next_credit_step = 0u;
		switch(credit_step_final){
			case 1u:
				PRINT(3u, 1u, "FLYING ARROWS");
				PRINT(3u, 2u, "IS A PRODUCT");
				PRINT(3u, 3u, "DESIGNED BY");
			break;
			case 2u:
				PRINT(3u, 1u, "              ");
				PRINT(3u, 2u, "              ");
				PRINT(3u, 3u, "GRAPHICS BY   ");
			break;
			case 3u:
				PRINT(3u, 1u, "              ");
				PRINT(3u, 2u, "              ");
				PRINT(3u, 3u, "PRODUCED BY   ");
			break;
			case 5u:
				PRINT(3u, 21u, "SPECIAL THANKS");
				PRINT(3u, 22u, "              ");
				PRINT(3u, 23u, "TO SPECIAL    ");
				PRINT(3u, 24u, "              ");
				PRINT(3u, 25u, "KICKSTARTER    ");
				PRINT(3u, 26u, "              ");
				PRINT(3u, 27u, "BACKERS:      ");
			break;
			case 6u:
				PRINT(2u, 21u, "HEXADIGITAL      ");
				PRINT(2u, 22u, "                 ");
				PRINT(2u, 23u, "HAYDEN CRIST     ");
				PRINT(2u, 24u, "                  ");
				PRINT(2u, 25u, "ELIZABETH GORMAN  ");
				PRINT(2u, 26u, "                  ");
				PRINT(2u, 27u, "SI PITTMAN          ");
			break;
			case 7u:
				PRINT(2u, 21u, "AWESOME JACKET   ");
				PRINT(2u, 22u, "   DUDE KS       ");
				PRINT(2u, 23u, "                 ");
				PRINT(2u, 24u, "RICHARD DAVEY    ");
				PRINT(2u, 25u, "                 ");
				PRINT(2u, 26u, "CAYLEN LEPPY     ");
				PRINT(2u, 27u, "  WILLIAMS       ");
			break;
			case 8u:
				PRINT(2u, 21u, "                 ");
				PRINT(2u, 22u, "                 ");
				PRINT(2u, 23u, "MEANWHILE        ");
				PRINT(2u, 24u, "                 ");
				PRINT(2u, 25u, "IN THE SEWERS ...");
				PRINT(2u, 26u, "                 ");
				PRINT(2u, 27u, "                 ");
				PRINT(2u, 28u, "                 ");
				PRINT(2u, 29u, "                 ");
			break;
			case 9u:			
				current_level = 11u;
				current_map = 0u;
				current_cutscene = 20u;
				SetState(StateWorldmap);
			break;
		}
	}
	if(credit_step_final == 4u){
		if(scroll_target->y < camerainfo_data->final_y){
			temporeggia = 0;
			scroll_target->y += 2;
		}
	}

}
