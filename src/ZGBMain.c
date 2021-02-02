#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateGame;


UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {

	if(current_state == StateGame) {
		*tile = 0;
		switch(*tile_ptr) {
			case 84u:
				*tile = 74u;
			break;
			default:
				*tile = *tile_ptr;
			break;
		}
		/*if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
			*tile = 0;
			return 255 - (UINT16)*tile_ptr;
		}*/

	}

	return 255u;
}