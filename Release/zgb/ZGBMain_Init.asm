;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (MINGW32)
;--------------------------------------------------------
	.module ZGBMain_Init
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _InitSprites
	.globl _Destroy_SpritePorcupine
	.globl _Update_SpritePorcupine
	.globl _Start_SpritePorcupine
	.globl _Destroy_SpriteScorpion
	.globl _Update_SpriteScorpion
	.globl _Start_SpriteScorpion
	.globl _Destroy_SpriteEnemy
	.globl _Update_SpriteEnemy
	.globl _Start_SpriteEnemy
	.globl _Destroy_SpriteItem
	.globl _Update_SpriteItem
	.globl _Start_SpriteItem
	.globl _Destroy_SpritePlatform
	.globl _Update_SpritePlatform
	.globl _Start_SpritePlatform
	.globl _Destroy_SpriteArrow
	.globl _Update_SpriteArrow
	.globl _Start_SpriteArrow
	.globl _Destroy_SpritePlayer
	.globl _Update_SpritePlayer
	.globl _Start_SpritePlayer
	.globl _InitStates
	.globl _Update_StateGameOver
	.globl _Start_StateGameOver
	.globl _Update_StateSecret
	.globl _Start_StateSecret
	.globl _Update_StateGame
	.globl _Start_StateGame
	.globl _spriteIdxs
	.globl _spriteDatas
	.globl _spriteDestroyFuncs
	.globl _spriteUpdateFuncs
	.globl _spriteStartFuncs
	.globl _spriteDataBanks
	.globl _spriteBanks
	.globl _updateFuncs
	.globl _startFuncs
	.globl _stateBanks
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_stateBanks::
	.ds 3
_startFuncs::
	.ds 6
_updateFuncs::
	.ds 6
_spriteBanks::
	.ds 7
_spriteDataBanks::
	.ds 7
_spriteStartFuncs::
	.ds 14
_spriteUpdateFuncs::
	.ds 14
_spriteDestroyFuncs::
	.ds 14
_spriteDatas::
	.ds 14
_spriteIdxs::
	.ds 7
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_1
;C:/GB/ZGB/common/src/ZGBMain_Init.c:22: void InitStates() {
;	---------------------------------
; Function InitStates
; ---------------------------------
_InitStates::
;C:/GB/ZGB/common/src/ZGBMain_Init.c:23: STATES
	ld	hl, #_startFuncs
	ld	(hl), #<(_Start_StateGame)
	inc	hl
	ld	(hl), #>(_Start_StateGame)
	ld	hl, #_updateFuncs
	ld	(hl), #<(_Update_StateGame)
	inc	hl
	ld	(hl), #>(_Update_StateGame)
	ld	bc, #_stateBanks+0
	ld	hl, #_bank_StateGame
	ld	a, (hl)
	ld	(bc), a
	ld	hl, #(_startFuncs + 0x0002)
	ld	(hl), #<(_Start_StateSecret)
	inc	hl
	ld	(hl), #>(_Start_StateSecret)
	ld	hl, #(_updateFuncs + 0x0002)
	ld	(hl), #<(_Update_StateSecret)
	inc	hl
	ld	(hl), #>(_Update_StateSecret)
	ld	de, #(_stateBanks + 0x0001)
	ld	hl, #_bank_StateSecret
	ld	a, (hl)
	ld	(de), a
	ld	hl, #(_startFuncs + 0x0004)
	ld	(hl), #<(_Start_StateGameOver)
	inc	hl
	ld	(hl), #>(_Start_StateGameOver)
	ld	hl, #(_updateFuncs + 0x0004)
	ld	(hl), #<(_Update_StateGameOver)
	inc	hl
	ld	(hl), #>(_Update_StateGameOver)
	inc	bc
	inc	bc
	ld	hl, #_bank_StateGameOver
	ld	a, (hl)
	ld	(bc), a
;C:/GB/ZGB/common/src/ZGBMain_Init.c:24: }
	ret
;C:/GB/ZGB/common/src/ZGBMain_Init.c:65: void InitSprites() {
;	---------------------------------
; Function InitSprites
; ---------------------------------
_InitSprites::
;C:/GB/ZGB/common/src/ZGBMain_Init.c:66: SPRITES
	ld	de, #_spriteBanks
	ld	hl, #_bank_SpritePlayer
	ld	a, (hl)
	ld	(de), a
	ld	a, (#_archer + 0)
	ld	hl, #_spriteDataBanks
	ld	(hl), a
	ld	hl, #_spriteStartFuncs
	ld	(hl), #<(_Start_SpritePlayer)
	inc	hl
	ld	(hl), #>(_Start_SpritePlayer)
	ld	hl, #_spriteUpdateFuncs
	ld	(hl), #<(_Update_SpritePlayer)
	inc	hl
	ld	(hl), #>(_Update_SpritePlayer)
	ld	hl, #_spriteDestroyFuncs
	ld	(hl), #<(_Destroy_SpritePlayer)
	inc	hl
	ld	(hl), #>(_Destroy_SpritePlayer)
	ld	hl, #(_archer + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #_spriteDatas
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	de, #(_spriteBanks + 0x0001)
	ld	hl, #_bank_SpriteArrow
	ld	a, (hl)
	ld	(de), a
	ld	bc, #_spriteDataBanks + 1
	ld	a, (#_arrow + 0)
	ld	(bc), a
	ld	hl, #(_spriteStartFuncs + 0x0002)
	ld	(hl), #<(_Start_SpriteArrow)
	inc	hl
	ld	(hl), #>(_Start_SpriteArrow)
	ld	hl, #(_spriteUpdateFuncs + 0x0002)
	ld	(hl), #<(_Update_SpriteArrow)
	inc	hl
	ld	(hl), #>(_Update_SpriteArrow)
	ld	hl, #(_spriteDestroyFuncs + 0x0002)
	ld	(hl), #<(_Destroy_SpriteArrow)
	inc	hl
	ld	(hl), #>(_Destroy_SpriteArrow)
	ld	hl, #(_arrow + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #(_spriteDatas + 0x0002)
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	de, #(_spriteBanks + 0x0002)
	ld	hl, #_bank_SpritePlatform
	ld	a, (hl)
	ld	(de), a
	ld	bc, #_spriteDataBanks + 2
	ld	a, (#_platform + 0)
	ld	(bc), a
	ld	hl, #(_spriteStartFuncs + 0x0004)
	ld	(hl), #<(_Start_SpritePlatform)
	inc	hl
	ld	(hl), #>(_Start_SpritePlatform)
	ld	hl, #(_spriteUpdateFuncs + 0x0004)
	ld	(hl), #<(_Update_SpritePlatform)
	inc	hl
	ld	(hl), #>(_Update_SpritePlatform)
	ld	hl, #(_spriteDestroyFuncs + 0x0004)
	ld	(hl), #<(_Destroy_SpritePlatform)
	inc	hl
	ld	(hl), #>(_Destroy_SpritePlatform)
	ld	hl, #(_platform + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #(_spriteDatas + 0x0004)
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	de, #(_spriteBanks + 0x0003)
	ld	hl, #_bank_SpriteItem
	ld	a, (hl)
	ld	(de), a
	ld	bc, #_spriteDataBanks + 3
	ld	a, (#_item + 0)
	ld	(bc), a
	ld	hl, #(_spriteStartFuncs + 0x0006)
	ld	(hl), #<(_Start_SpriteItem)
	inc	hl
	ld	(hl), #>(_Start_SpriteItem)
	ld	hl, #(_spriteUpdateFuncs + 0x0006)
	ld	(hl), #<(_Update_SpriteItem)
	inc	hl
	ld	(hl), #>(_Update_SpriteItem)
	ld	hl, #(_spriteDestroyFuncs + 0x0006)
	ld	(hl), #<(_Destroy_SpriteItem)
	inc	hl
	ld	(hl), #>(_Destroy_SpriteItem)
	ld	hl, #(_item + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #(_spriteDatas + 0x0006)
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	de, #(_spriteBanks + 0x0004)
	ld	hl, #_bank_SpriteEnemy
	ld	a, (hl)
	ld	(de), a
	ld	bc, #_spriteDataBanks + 4
	ld	a, (#_enemy + 0)
	ld	(bc), a
	ld	hl, #(_spriteStartFuncs + 0x0008)
	ld	(hl), #<(_Start_SpriteEnemy)
	inc	hl
	ld	(hl), #>(_Start_SpriteEnemy)
	ld	hl, #(_spriteUpdateFuncs + 0x0008)
	ld	(hl), #<(_Update_SpriteEnemy)
	inc	hl
	ld	(hl), #>(_Update_SpriteEnemy)
	ld	hl, #(_spriteDestroyFuncs + 0x0008)
	ld	(hl), #<(_Destroy_SpriteEnemy)
	inc	hl
	ld	(hl), #>(_Destroy_SpriteEnemy)
	ld	hl, #(_enemy + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #(_spriteDatas + 0x0008)
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	de, #(_spriteBanks + 0x0005)
	ld	hl, #_bank_SpriteScorpion
	ld	a, (hl)
	ld	(de), a
	ld	bc, #_spriteDataBanks + 5
	ld	a, (#_scorpion + 0)
	ld	(bc), a
	ld	hl, #(_spriteStartFuncs + 0x000a)
	ld	(hl), #<(_Start_SpriteScorpion)
	inc	hl
	ld	(hl), #>(_Start_SpriteScorpion)
	ld	hl, #(_spriteUpdateFuncs + 0x000a)
	ld	(hl), #<(_Update_SpriteScorpion)
	inc	hl
	ld	(hl), #>(_Update_SpriteScorpion)
	ld	hl, #(_spriteDestroyFuncs + 0x000a)
	ld	(hl), #<(_Destroy_SpriteScorpion)
	inc	hl
	ld	(hl), #>(_Destroy_SpriteScorpion)
	ld	hl, #(_scorpion + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #(_spriteDatas + 0x000a)
	ld	(hl), c
	inc	hl
	ld	(hl), b
	ld	de, #(_spriteBanks + 0x0006)
	ld	hl, #_bank_SpritePorcupine
	ld	a, (hl)
	ld	(de), a
	ld	bc, #_spriteDataBanks + 6
	ld	a, (#_porcupine + 0)
	ld	(bc), a
	ld	hl, #(_spriteStartFuncs + 0x000c)
	ld	(hl), #<(_Start_SpritePorcupine)
	inc	hl
	ld	(hl), #>(_Start_SpritePorcupine)
	ld	hl, #(_spriteUpdateFuncs + 0x000c)
	ld	(hl), #<(_Update_SpritePorcupine)
	inc	hl
	ld	(hl), #>(_Update_SpritePorcupine)
	ld	hl, #(_spriteDestroyFuncs + 0x000c)
	ld	(hl), #<(_Destroy_SpritePorcupine)
	inc	hl
	ld	(hl), #>(_Destroy_SpritePorcupine)
	ld	hl, #(_porcupine + 0x0001) + 0
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #(_spriteDatas + 0x000c)
	ld	(hl), c
	inc	hl
	ld	(hl), b
;C:/GB/ZGB/common/src/ZGBMain_Init.c:67: }
	ret
	.area _CODE_1
	.area _CABS (ABS)
