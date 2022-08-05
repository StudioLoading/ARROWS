#ifndef ZGBMAIN_H
#define ZGBMAIN_H
#define PauseMusic hUGE_paused = 1; hUGE_mute(HT_CH_MUTE);
#define UNMUTE_ALL_CHANNELS hUGE_mute(HT_CH_PLAY)
#define ResumeMusic hUGE_paused = 0; UNMUTE_ALL_CHANNELS  

#define WALK_FX_COOLDOWN 32
/*
*/

#define STATES \
_STATE(StateCredit)\
_STATE(StateTitlescreen)\
_STATE(StateIntro)\
_STATE(StateWorldmap)\
_STATE(StateDiag)\
_STATE(StateGame)\
_STATE(StateGame3)\
_STATE(StateGame6)\
_STATE(StateSecret)\
_STATE(StateBoss)\
_STATE(StateGameover)\
_STATE(StateCutscene)\
_STATE(StateGame7)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpriteIconpsg, iconpsg)\
_SPRITE_DMG(SpriteCamerafocus, camerafocus)\
_SPRITE_DMG(SpriteArrowtitle, arrowtitle)\
_SPRITE_DMG(SpritePlayer, archer)\
_SPRITE_DMG(SpriteArrow, arrow)\
_SPRITE_DMG(SpritePlatform, platform)\
_SPRITE_DMG(SpritePuff, puff)\
_SPRITE_DMG(SpriteIceplat, iceplat)\
_SPRITE_DMG(SpriteItem, item)\
_SPRITE_DMG(SpriteKey, key)\
_SPRITE_DMG(SpriteEnemy, enemy)\
_SPRITE_DMG(SpriteScorpion, scorpion)\
_SPRITE_DMG(SpriteRat, rat)\
_SPRITE_DMG(SpriteSpider, spider)\
_SPRITE_DMG(SpriteBird, bird)\
_SPRITE_DMG(SpriteGate, gate)\
_SPRITE_DMG(SpriteStalagmite, stalagmite)\
_SPRITE_DMG(SpriteStalattite, stalattite)\
_SPRITE_DMG(SpriteAmulet, amuleto)\
_SPRITE_DMG(SpriteWolf, wolf)\
_SPRITE_DMG(SpriteAlligator, alligator)\
_SPRITE_DMG(SpriteEagle, eagle)\
_SPRITE_DMG(SpriteFeather, feather)\
_SPRITE_DMG(SpriteThunder, thunder)\
_SPRITE_DMG(SpriteHurricane, hurricane)\
_SPRITE_DMG(SpriteIbex, ibex)\
_SPRITE_DMG(SpriteBee, bee)\
_SPRITE_DMG(SpriteBear, bear)\
_SPRITE_DMG(SpritePenguin, penguin)\
_SPRITE_DMG(SpriteWalrus, walrus)\
_SPRITE_DMG(SpriteWalrusspin, walrusspin)\
_SPRITE_DMG(SpriteAxethrower, axethrower)\
_SPRITE_DMG(SpriteAxe, axe)\
_SPRITE_DMG(SpriteBat, bat)\
_SPRITE_DMG(SpriteFalce, falce)\
_SPRITE_DMG(SpriteFalcebase, falcebase)\
_SPRITE_DMG(SpriteCathead, cathead)\
_SPRITE_DMG(SpriteCutmother, cutmother)\
_SPRITE_DMG(SpriteCutarcher, cutarcher)\
_SPRITE_DMG(SpriteCastlegate, castlegate)\
_SPRITE_DMG(SpriteCagedboss, cagedboss)\
_SPRITE_DMG(SpriteMother, mother)\
_SPRITE_DMG(SpriteCutfinalboss, cutfinalboss)\
_SPRITE_DMG(SpriteCuteagle, cuteagle)\
_SPRITE_DMG(SpriteArrowmother, arrowmother)\
_SPRITE_DMG(SpriteBosseagle, bosseagle)\
_SPRITE_DMG(SpriteArrowboss, arrowboss)\
_SPRITE_DMG(SpriteCloud, cloud)\
SPRITE_DEF_END


/*
_SPRITE_DMG(SpritePorcupine, porcupine)\
*/
#include "ZGBMain_Init.h"

#endif

