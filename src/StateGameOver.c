#include "Banks/SetBank6.h"

#include "..\res\src\tiles.h"
#include "..\res\src\mapgameover.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"


void Start_StateGameOver() {
	InitScroll(&mapgameover, 0, 0);
	SHOW_BKG;
}

void Update_StateGameOver() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(StateGame);
	}
}