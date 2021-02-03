#include "Banks/SetBank3.h"

#include "../res/src/font.h"
#include "..\res\src\tiles2.h"
#include "..\res\src\mapsewer.h"
#include "../res/src/archer.h"
#include "../res/src/arrow.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "string.h"
#include "Print.h"

#include "custom_datas.h"

extern UINT8 collision_tiles[];
extern unsigned char wolf_face[];


/*
UINT16 bg_palette[] = {PALETTE_FROM_HEADER(tiles)};

UINT16 sprites_palette[] = {
	PALETTE_INDEX(archer, 0),
	PALETTE_INDEX(archer, 1),
	PALETTE_INDEX(archer, 2), //o PALETTE_INDEX(enemy,  2)
	PALETTE_INDEX(archer, 3),
	PALETTE_INDEX(archer, 4),
	PALETTE_INDEX(archer, 5),
	PALETTE_INDEX(archer, 6),
	PALETTE_INDEX(archer, 7),
};

UINT8 collision_tiles[] = {1, 2, 0};//numero delle tile con collisioni e ultimo sempre zero
*/

const struct MapInfo* level_sewer[] = {
	&mapsewer
};
const struct MapInfo** level2[] = {level_sewer};

void Start_StateSewer() {
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, 2);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, 2);

	SPRITES_8x16;
	SpriteManagerLoad(SpritePlayer);
	SpriteManagerLoad(SpriteArrow);
	SpriteManagerLoad(SpritePlatform);
	SHOW_SPRITES;

	scroll_bottom_movement_limit = 60;//customizzo altezza archer sul display
	scroll_target = SpriteManagerAdd(SpritePlayer, 64, 8);
	const struct MapInfo** lvls = level2[0];
	InitScroll(lvls[0], collision_tiles, 0);
	SHOW_BKG;
	
	//WINDOW
	INIT_FONT(font, PRINT_WIN);
	INIT_CONSOLE(font, 10, 2);
	
	//SOUND
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
}

void Update_StateSewer() {}