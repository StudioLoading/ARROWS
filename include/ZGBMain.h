#ifndef ZGBMAIN_H
#define ZGBMAIN_H


#define STATES \
_STATE(StateCredit)\
_STATE(StateTitlescreen)\
_STATE(StateIntro)\
_STATE(StateWorldmap)\
_STATE(StateGame)\
_STATE(StateGame3)\
_STATE(StateGame6)\
_STATE(StateSecret)\
_STATE(StateBoss)\
_STATE(StateDiag)\
_STATE(StateGameover)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, archer)\
_SPRITE_DMG(SpriteArrow, arrow)\
_SPRITE_DMG(SpriteArrowtitle, arrowtitle)\
_SPRITE_DMG(SpritePlatform, platform)\
_SPRITE_DMG(SpriteItem, item)\
_SPRITE_DMG(SpriteKey, key)\
_SPRITE_DMG(SpriteAmulet, amulets)\
_SPRITE_DMG(SpriteEnemy, enemy)\
_SPRITE_DMG(SpriteScorpion, scorpion)\
_SPRITE_DMG(SpritePorcupine, porcupine)\
_SPRITE_DMG(SpriteThunder, thunder)\
_SPRITE_DMG(SpriteHurricane, hurricane)\
_SPRITE_DMG(SpriteWolf, wolf_new)\
_SPRITE_DMG(SpriteRat, rat)\
_SPRITE_DMG(SpriteSpider, spider)\
_SPRITE_DMG(SpriteStalagmite, stalagmite)\
_SPRITE_DMG(SpriteStalattite, stalattite)\
_SPRITE_DMG(SpriteAlligator, alligator)\
_SPRITE_DMG(SpriteBird, bird)\
_SPRITE_DMG(SpriteGate, gate)\
_SPRITE_DMG(SpriteEagle, eagle)\
_SPRITE_DMG(SpriteIbex, ibex)\
_SPRITE_DMG(SpriteBear, bear)\
_SPRITE_DMG(SpriteCamerafocus, camerafocus)\
_SPRITE_DMG(SpritePuff, puff)\
_SPRITE_DMG(SpriteIceplat, iceplat)\
_SPRITE_DMG(SpriteWalrus, walrus)\
_SPRITE_DMG(SpriteWalrusspin, walrusspin)\
_SPRITE_DMG(SpriteBee, bee)\
_SPRITE_DMG(SpritePenguin, penguin)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif

