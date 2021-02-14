
typedef enum  {
	STATE_NORMAL,
	STATE_NORMAL_PLATFORM,
	STATE_JUMPING,
	STATE_LADDER,
	STATE_HIT,
	STATE_DIAG,
	STATE_DEAD
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
	INT8 arrowdamage;
};
struct PlatformInfo {
	UINT8 type:3;
	UINT8 distance;
	UINT8 step;
	UINT16 initx;
	INT8 vx;
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
	ENEMY_STATE_WAIT
}ENEMY_STATE;

struct EnemyInfo{
	INT16 enemy_accel_y;
	ENEMY_STATE enemy_state;
	UINT8 tile_e_collision;
	INT8 vx;
	UINT8 wait;
	INT8 hp;
};

struct Dialog{
	char * d[4];
	unsigned char face[];
};
