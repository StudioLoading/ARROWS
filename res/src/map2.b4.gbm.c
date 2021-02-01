#pragma bank 4

void empty(void) __nonbanked {}
__addressmod empty const CODE;

const unsigned char map2_map[] = {
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x14,0x14,0x15,0x15,0x14,
	0x15,0x14,0x00,0x31,0x31,0x31,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x1a,0x1a,
	0x1a,0x14,0x15,0x14,0x15,0x14,0x14,0x15,0x14,0x15,
	0x2b,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,
	0x31,0x31,0x1a,0x00,0x1b,0x00,0x1b,0x1a,0x1a,0x1a,
	0x1a,0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x1a,0x00,0x1a,0x1a,0x15,
	0x14,0x15,0x14,0x15,0x15,0x14,0x15,0x14,0x2c,0x31,
	0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,
	0x31,0x00,0x1b,0x00,0x1b,0x00,0x00,0x00,0x1a,0x1a,
	0x00,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x38,
	0x15,0x14,0x15,0x1a,0x00,0x1a,0x1a,0x14,0x15,0x14,
	0x15,0x14,0x14,0x15,0x14,0x15,0x2e,0x15,0x14,0x15,
	0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x1a,
	0x1a,0x3a,0x00,0x1a,0x1a,0x1a,0x00,0x00,0x1a,0x1a,
	0x1a,0x15,0x14,0x1b,0x1b,0x1a,0x1a,0x2b,0x14,0x15,
	0x14,0x1a,0x1a,0x00,0x1a,0x1a,0x1a,0x2d,0x1a,0x15,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x12,0x31,0x31,0x33,0x1f,0x1f,0x1f,0x3b,
	0x1f,0x1a,0x12,0x1f,0x00,0x00,0x00,0x00,0x1a,0x14,
	0x00,0x1b,0x1b,0x1f,0x1f,0x2c,0x15,0x14,0x00,0x1a,
	0x00,0x00,0x00,0x1a,0x1a,0x1a,0x1a,0x14,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x00,0x1a,0x00,0x1a,0x1a,0x15,0x00,0x1b,
	0x1f,0x15,0x14,0x07,0x14,0x15,0x1a,0x1a,0x00,0x1a,
	0x1a,0x1f,0x1f,0x1f,0x1f,0x15,0x15,0x14,0x09,0x00,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x1a,0x1a,0x00,0x1a,0x1a,0x14,0x00,0x1b,0x15,0x14,
	0x15,0x14,0x15,0x14,0x00,0x1a,0x1a,0x00,0x1a,0x14,
	0x15,0x14,0x15,0x14,0x14,0x15,0x1a,0x00,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x1a,
	0x1a,0x00,0x00,0x1a,0x18,0x00,0x18,0x1a,0x1a,0x1a,
	0x1a,0x1a,0x1a,0x1a,0x00,0x1f,0x15,0x15,0x14,0x15,
	0x14,0x15,0x15,0x14,0x1a,0x00,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x1f,0x1a,0x1a,0x1a,
	0x1a,0x00,0x19,0x1a,0x19,0x00,0x00,0x1f,0x1a,0x1a,
	0x1a,0x1a,0x1a,0x03,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x12,0x1a,0x1f,0x1a,0x1a,0x1f,
	0x1f,0x1f,0x1a,0x1a,0x1a,0x12,0x1a,0x1a,0x1a,0x00,
	0x02,0x02,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x1a,0x00,0x00,0x1a,0x1a,0x1a,0x00,0x00,0x1a,0x1a,
	0x1a,0x00,0x1a,0x1a,0x1a,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x1a,0x00,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x14,0x15,0x1a,0x00,
	0x1a,0x1a,0x00,0x1a,0x00,0x1a,0x1a,0x00,0x00,0x00,
	0x00,0x1a,0x1a,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x1a,0x1a,0x1a,0x1a,0x00,0x15,0x15,
	0x14,0x15,0x14,0x15,0x15,0x14,0x1f,0x1f,0x1f,0x1f,
	0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00,0x1a,
	0x1a,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x18,0x1a,0x1a,0x1a,0x00,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x1a,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x19,
	0x00,0x1a,0x1a,0x1a,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x1a,0x00,0x03,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x00,0x00,0x03,
	0x1a,0x1a,0x00,0x1a,0x1a,0x1a,0x14,0x15,0x14,0x15,
	0x00,0x1a,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,
	0x1a,0x1a,0x00,0x00,0x1a,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x00,0x00,0x1a,0x1a,0x1a,0x00,0x1a,
	0x1a,0x00,0x1a,0x00,0x15,0x14,0x15,0x14,0x1a,0x1a,
	0x32,0x31,0x31,0x31,0x31,0x31,0x31,0x33,0x00,0x00,
	0x03,0x1a,0x1a,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x00,0x00,0x00,0x00,0x1a,0x1a,0x1a,0x00,0x00,0x1a,
	0x1a,0x1a,0x14,0x15,0x14,0x15,0x1a,0x00,0x1a,0x1a,
	0x00,0x1a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x00,
	0x00,0x00,0x2b,0x14,0x15,0x14,0x15,0x14,0x00,0x00,
	0x00,0x00,0x00,0x03,0x1a,0x1a,0x00,0x00,0x00,0x1a,
	0x15,0x14,0x15,0x14,0x1a,0x1a,0x1a,0x00,0x00,0x1a,
	0x00,0x00,0x1a,0x1a,0x1a,0x00,0x00,0x00,0x03,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x00,0x1a,0x1a,0x1f,
	0x2c,0x15,0x14,0x15,0x14,0x15,0x1f,0x1f,0x00,0x1a,
	0x1a,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x14,0x15,
	0x14,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1a,
	0x1a,0x00,0x1a,0x00,0x00,0x00,0x00,0x14,0x15,0x14,
	0x15,0x14,0x15,0x00,0x1a,0x1a,0x1f,0x14,0x2a,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x1a,0x1a,0x1a,0x00,
	0x00,0x1a,0x1a,0x1a,0x1a,0x1a,0x15,0x14,0x15,0x14,
	0x00,0x00,0x00,0x00,0x00,0x1a,0x00,0x00,0x1a,0x1a,
	0x1a,0x1a,0x00,0x00,0x00,0x15,0x14,0x15,0x14,0x15,
	0x1a,0x1a,0x1a,0x1f,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x1f,0x1a,0x1a,0x1a,0x00,0x00,
	0x1a,0x1a,0x1a,0x1a,0x14,0x15,0x14,0x15,0x14,0x15,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x14,0x15,0x14,0x15,0x00,0x1a,0x00,
	0x1f,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x12,0x1f,0x1f,0x1f,0x1f,0x00,0x00,0x00,
	0x00,0x00,0x15,0x14,0x15,0x14,0x15,0x14,0x00,0x00,
	0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
	0x02,0x15,0x14,0x15,0x00,0x00,0x1a,0x1a,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,0x00,
	0x14,0x15,0x14,0x15,0x00,0x18,0x00,0x00,0x00,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x1f,0x00,0x00,0x1a,0x00,0x00,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x16,
	0x16,0x16,0x16,0x1a,0x1a,0x1a,0x1a,0x1a,0x15,0x14,
	0x15,0x14,0x00,0x19,0x00,0x00,0x00,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x03,0x03,0x00,0x1a,0x1a,0x00,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x16,0x16,0x16,
	0x16,0x1a,0x00,0x1a,0x00,0x00,0x14,0x15,0x14,0x15,
	0x1a,0x1a,0x00,0x1a,0x00,0x00,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x1a,0x00,
	0x00,0x00,0x00,0x00,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x16,0x16,0x16,0x1a,
	0x1a,0x1a,0x1a,0x00,0x15,0x14,0x15,0x14,0x1f,0x1a,
	0x1a,0x00,0x00,0x1a,0x00,0x00,0x00,0x00,0x00,0x00,
	0x1b,0x00,0x1a,0x00,0x00,0x00,0x1a,0x1a,0x1a,0x1f,
	0x1f,0x1f,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x16,0x16,0x16,0x1a,0x00,0x00,0x03,
	0x1a,0x1a,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x1a,0x1a,0x00,0x00,0x00,0x1a,0x1a,0x1a,0x1c,0x1a,
	0x00,0x00,0x1a,0x1a,0x00,0x1a,0x00,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x16,0x16,0x1a,0x1a,0x00,0x1a,0x00,0x1a,
	0x15,0x14,0x14,0x14,0x10,0x00,0x00,0x18,0x00,0x00,
	0x1a,0x00,0x00,0x00,0x00,0x00,0x1d,0x00,0x1a,0x00,
	0x00,0x00,0x1a,0x00,0x00,0x00,0x1a,0x00,0x00,0x00,
	0x1a,0x00,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x16,
	0x16,0x16,0x1a,0x1a,0x00,0x00,0x1a,0x1a,0x14,0x15,
	0x15,0x14,0x00,0x1a,0x1a,0x19,0x00,0x1a,0x1a,0x00,
	0x1a,0x1a,0x1a,0x1a,0x1e,0x00,0x1a,0x1a,0x1a,0x1a,
	0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x00,
	0x15,0x14,0x14,0x15,0x14,0x15,0x16,0x16,0x16,0x16,
	0x03,0x1a,0x00,0x00,0x00,0x00,0x15,0x14,0x14,0x15,
	0x0d,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x1a,0x1a,
	0x1a,0x00,0x1a,0x00,0x00,0x00,0x1a,0x00,0x00,0x00,
	0x00,0x00,0x1a,0x1a,0x00,0x1a,0x1a,0x00,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x16,0x1a,0x00,
	0x1a,0x00,0x00,0x00,0x14,0x15,0x15,0x14,0x1a,0x00,
	0x00,0x1a,0x00,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,
	0x1a,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
	0x02,0x02,0x02,0x02,0x02,0x02,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x16,0x16,0x1a,0x00,0x1a,0x1a,
	0x00,0x1a,0x15,0x14,0x14,0x00,0x1a,0x1a,0x00,0x00,
	0x03,0x00,0x1a,0x1a,0x00,0x00,0x00,0x00,0x00,0x1a,
	0x1a,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x16,0x16,0x16,0x18,0x1a,0x03,0x1a,0x00,0x1a,
	0x14,0x15,0x15,0x00,0x00,0x1a,0x1f,0x02,0x02,0x02,
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x16,0x16,
	0x16,0x16,0x19,0x1a,0x1a,0x1a,0x00,0x1a,0x15,0x14,
	0x14,0x00,0x18,0x00,0x14,0x15,0x14,0x15,0x14,0x15,
	0x14,0x14,0x15,0x14,0x15,0x14,0x15,0x00,0x00,0x15,
	0x14,0x14,0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x14,
	0x15,0x14,0x15,0x14,0x15,0x14,0x15,0x16,0x16,0x16,
	0x1a,0x00,0x00,0x1a,0x00,0x1a,0x14,0x15,0x16,0x1f,
	0x19,0x1a,0x1a,0x1a,0x1a,0x00,0x1a,0x1a,0x00,0x00,
	0x1b,0x1a,0x1b,0x1a,0x1a,0x00,0x1a,0x14,0x15,0x1a,
	0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1b,0x1a,0x1b,0x1a,
	0x1b,0x1a,0x1b,0x1a,0x1a,0x1a,0x1a,0x1a,0x03,0x1a,
	0x1a,0x00,0x00,0x1a,0x15,0x14,0x16,0x03,0x03,0x1f,
	0x1a,0x1a,0x00,0x00,0x00,0x00,0x00,0x1a,0x1b,0x00,
	0x1b,0x1a,0x1a,0x00,0x14,0x15,0x1a,0x00,0x00,0x1a,
	0x1a,0x1a,0x00,0x00,0x1b,0x00,0x1b,0x1a,0x1b,0x00,
	0x1b,0x1a,0x00,0x00,0x1a,0x00,0x1a,0x1a,0x00,0x1a,
	0x00,0x00,0x14,0x15,0x16,0x1c,0x1c,0x03,0x1f,0x1a,
	0x1a,0x00,0x1a,0x1a,0x1a,0x00,0x1b,0x00,0x1b,0x00,
	0x1a,0x1a,0x1a,0x1a,0x1a,0x00,0x00,0x00,0x00,0x1a,
	0x00,0x1a,0x1b,0x00,0x1b,0x00,0x1b,0x00,0x1b,0x00,
	0x00,0x00,0x00,0x00,0x00,0x1a,0x1a,0x1a,0x00,0x1a,
	0x15,0x14,0x16,0x1d,0x1d,0x00,0x03,0x1f,0x1a,0x1a,
	0x1a,0x00,0x1a,0x1a,0x1a,0x3a,0x00,0x1a,0x1a,0x00,
	0x00,0x1a,0x00,0x00,0x1a,0x1a,0x00,0x00,0x00,0x00,
	0x1a,0x3a,0x00,0x1a,0x1a,0x3a,0x00,0x00,0x00,0x1a,
	0x1a,0x1a,0x1a,0x1f,0x16,0x16,0x1a,0x1a,0x14,0x15,
	0x16,0x1d,0x1e,0x1f,0x1f,0x03,0x1f,0x1f,0x1f,0x12,
	0x1f,0x1a,0x1f,0x3b,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
	0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x12,0x1f,0x3b,
	0x1f,0x1f,0x1f,0x3b,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
	0x1f,0x16,0x16,0x16,0x00,0x00,0x15,0x14,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x25,0x25,0x14,0x15,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x44,0x44,0x15,0x14,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x44,0x44,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x44,0x44,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x44,0x44,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x44,0x44,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x28,0x28,0x16,0x16
};
#include "tiles.h"
#include "MapInfo.h"
const struct MapInfoInternal map2_internal = {
	map2_map, //map
	48, //width
	48, //height
	0, //attributes
	&tiles, //tiles info
};
CODE struct MapInfo map2 = {
	4, //bank
	&map2_internal, //data
};