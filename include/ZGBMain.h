#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
_STATE(StateSecret)\
_STATE(StateBoss)\
_STATE(StateGameOver)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, archer)\
_SPRITE_DMG(SpriteArrow, arrow)\
_SPRITE_DMG(SpritePlatform, platform)\
_SPRITE_DMG(SpriteItem, item)\
_SPRITE_DMG(SpriteKey, key)\
_SPRITE_DMG(SpriteEnemy, enemy)\
_SPRITE_DMG(SpriteScorpion, scorpion)\
_SPRITE_DMG(SpritePorcupine, porcupine)\
_SPRITE_DMG(SpriteWolf, wolf)\
SPRITE_DEF_END


#include "ZGBMain_Init.h"

#endif

//_STATE(StateSewer)
//_STATE(StateBoss)
