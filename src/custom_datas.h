typedef enum  {
	STATE_NORMAL,
	STATE_NORMAL_PLATFORM,
	STATE_JUMPING,
	STATE_LADDER,
	STATE_HIT,
	STATE_DIAG,
	STATE_ASCENDING,
	STATE_DEAD,
	STATE_AMULET_STONE,
	STATE_AMULET_THUNDER,
	STATE_AMULET_ICE,
	STATE_AMULET_FIRE,
	STATE_ARROWMOTHER
}ARCHER_STATE;


struct ArcherInfo {
	UINT8 amulet;
	UINT8 coins;
	INT8 hp;
	INT8 ups;
	INT8 tool;
};

struct ArrowInfo {
	UINT8 type:4;
	UINT8 original_type:4;
	UINT8 vx:4;
	INT8 vy;
	INT8 arrowdir;
	INT8 arrowdamage; //set to 100 not to pop it on destroy!
	INT8 play_sound;
};
struct PlatformInfo {
	UINT8 type:3;
	UINT8 distance;
	UINT8 step;
	UINT16 initx;
	INT8 vx;
	INT8 vy;
};
struct AmuletInfo{
	INT8 type;
	UINT8 setup;
	INT8 counter;
	INT8 picked;
	UINT8 nothing_2;
};
struct ItemInfo{
	UINT8 collided;
	INT8 type; //1=coin, 2=hp, 3=up, 4=amulet?
	INT8 item_accel_y;
	UINT8 tile_i_collision;
	UINT8 setup;
	INT8 content_type;//1=coin, 2=hp, 3=up, 4=amulet?
	INT8 counter;
	INT8 vx;
};
typedef enum  {
	ENEMY_STATE_NORMAL,
	ENEMY_STATE_JUMPING,
	ENEMY_STATE_HIT,
	ENEMY_STATE_DEAD,
	ENEMY_STATE_ATTACK,
	ENEMY_STATE_HIDDEN,
	ENEMY_STATE_INVISIBLE,
	ENEMY_STATE_WAIT,
	ENEMY_STATE_SLIDING,
	ENEMY_STATE_WALKING,
	ENEMY_STATE_KNEE,
	STALAG_STATE_WAIT,
	STALAG_STATE_DROP,
	STALAG_STATE_LOW,
	STALAG_STATE_MED,
	STALAG_STATE_HIGH,
	WALRUS_STATE_WALK,
	WALRUS_STATE_SPIN,
	WALRUS_STATE_JUMP_UP,
	WALRUS_STATE_JUMP_DOWN,
	WALRUS_STATE_SWIMMING,
	WALRUS_STATE_SWIMMING_UP,
	MOTHER_FOLLOWING,
	ARROWMOTHER_CUTSCENE,
	ARROWMOTHER_NORMAL,
	BOSS_APPROACHING_FIRST,
	BOSS_APPROACHING,
	BOSS_ATTACK,
	BOSS_HIT,
	BOSS_CHASING,
	BOSS_MOVING
}ENEMY_STATE;

struct EnemyInfo{
	INT16 enemy_accel_y;
	ENEMY_STATE enemy_state;
	UINT8 tile_e_collision;
	INT8 vx; //type for the SpriteGate
	UINT8 wait;
	INT8 hp;
	UINT8 archer_posx;
};

struct LogoInfo{
	INT8 setup; // =1 means animation needs to be set according to frame, =0 animation frame not set yet
	INT8 frame; //0 to 5
};

struct PuffInfo{
	INT8 puff_counter;
};

struct FalcebaseInfo{
	Sprite * falcelama;
	ENEMY_STATE enemy_state;
};

struct CameraInfo{
	UINT8 step;
	UINT8 wait;
	UINT16 final_x;
	UINT16 final_y;
};

typedef enum  {
	WOLF_CAGED,
	WOLF_FREE,
	IBEX_CAGED,
	IBEX_FREE,
	BEAR_CAGED,
	BEAR_FREE,
	BOSS_IDLE
}CAGEDBOSS_STATE;


struct CagedbossInfo{
	INT8 setup;
	CAGEDBOSS_STATE state;
	UINT8 hit; 
	UINT8 wait;
};