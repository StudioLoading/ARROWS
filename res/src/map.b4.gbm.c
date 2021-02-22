#pragma bank 4

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char map_map[] = {
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,0x00,0x00,
	0x00,0x26,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x31,0x31,0x31,0x31,0x31,0x31,
	0x00,0x26,0x27,0x00,0x00,0x26,0x27,0x00,0x00,0x00,
	0x26,0x27,0x00,0x00,0x1b,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x26,0x27,0x00,0x00,0x00,0x00,0x26,0x27,
	0x16,0x16,0x1b,0x00,0x00,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x31,0x1c,0x1c,0x31,0x31,0x31,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1b,0x00,0x26,0x27,0x00,0x00,0x26,0x27,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,
	0x1b,0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x00,0x1e,0x1e,0x31,0x31,0x31,0x00,0x00,0x00,0x00,
	0x00,0x26,0x27,0x00,0x26,0x27,0x00,0x26,0x27,0x00,
	0x1b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,0x1b,0x00,
	0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x1f,0x06,
	0x06,0x1f,0x31,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1b,0x00,
	0x00,0x03,0x02,0x02,0x03,0x02,0x02,0x02,0x02,0x03,
	0x02,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x1f,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x00,0x26,0x27,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1f,0x35,0x1f,0x1f,0x1b,0x00,0x00,0x00,
	0x16,0x16,0x00,0x16,0x16,0x16,0x16,0x00,0x16,0x00,
	0x00,0x00,0x00,0x00,0x04,0x00,0x16,0x16,0x16,0x00,
	0x00,0x00,0x00,0x1b,0x00,0x00,0x00,0x00,0x16,0x16,
	0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x00,0x00,
	0x16,0x16,0x16,0x16,0x1b,0x00,0x00,0x00,0x00,0x1b,
	0x00,0x1b,0x00,0x00,0x1b,0x00,0x1b,0x02,0x03,0x00,
	0x1f,0x1f,0x05,0x1f,0x16,0x16,0x16,0x00,0x1f,0x1f,
	0x00,0x1b,0x00,0x00,0x1f,0x1f,0x16,0x16,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1b,0x00,0x00,0x00,0x00,0x1b,0x00,0x1b,
	0x00,0x00,0x1b,0x00,0x1b,0x16,0x00,0x00,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x00,0x16,0x16,0x09,0x1b,
	0x00,0x1f,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x1b,0x00,0x03,0x00,0x00,0x1b,0x00,0x1b,0x00,0x00,
	0x1b,0x00,0x1b,0x00,0x00,0x00,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x00,0x16,0x16,0x00,0x1b,0x00,0x03,
	0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x26,0x27,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1b,0x00,
	0x1b,0x03,0x00,0x1b,0x00,0x1b,0x00,0x00,0x1b,0x00,
	0x1b,0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x00,0x00,0x1b,0x00,0x1b,0x00,0x00,0x00,0x00,
	0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x26,0x27,0x00,0x00,0x00,0x00,0x1b,0x00,0x1b,0x00,
	0x03,0x1b,0x00,0x1b,0x00,0x00,0x1b,0x00,0x1b,0x00,
	0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,
	0x00,0x1b,0x00,0x1b,0x1f,0x00,0x00,0x31,0x31,0x31,
	0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x00,0x00,0x00,
	0x00,0x1f,0x00,0x00,0x1b,0x00,0x1b,0x00,0x00,0x1b,
	0x1c,0x1b,0x00,0x00,0x1b,0x00,0x1b,0x00,0x00,0x00,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x1c,
	0x1c,0x1b,0x03,0x00,0x00,0x31,0x31,0x31,0x00,0x00,
	0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
	0x00,0x00,0x1c,0x1c,0x1c,0x00,0x00,0x1c,0x04,0x1c,
	0x03,0x03,0x1c,0x1c,0x1c,0x00,0x00,0x00,0x00,0x00,
	0x1b,0x00,0x16,0x16,0x16,0x00,0x00,0x04,0x04,0x1c,
	0x00,0x00,0x00,0x31,0x31,0x31,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x1e,0x1e,0x1e,0x1f,0x00,0x1e,0x05,0x1e,0x00,0x00,
	0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x1b,0x00,
	0x16,0x16,0x16,0x1f,0x1f,0x05,0x05,0x1e,0x1f,0x1f,
	0x1f,0x1f,0x31,0x1f,0x1f,0x1f,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,
	0x06,0x12,0x1f,0x06,0x06,0x06,0x1f,0x1f,0x05,0x05,
	0x05,0x1f,0x00,0x00,0x00,0x00,0x1b,0x00,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x00,0x00,0x00,0x00,0x1c,0x00,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x1f,
	0x00,0x00,0x1e,0x00,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
	0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x02,0x02,
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x31,
	0x31,0x31,0x00,0x00,0x31,0x31,0x31,0x00,0x00,0x00,
	0x31,0x31,0x31,0x00,0x00,0x00,0x00,0x00,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x00,0x00,0x16,0x16,0x16,0x16,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x31,
	0x31,0x00,0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x1f,0x00,0x31,0x31,0x31,0x00,
	0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,
	0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x1f,0x1f,
	0x1f,0x1f,0x1f,0x1f,0x00,0x35,0x1f,0x1f,0x1f,0x00,
	0x1f,0x1f,0x12,0x1f,0x1f,0x31,0x1f,0x35,0x1f,0x00,
	0x00,0x00,0x16,0x16,0x16,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,0x16,
	0x16,0x16,0x16,0x00,0x00,0x00,0x03,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x02,0x02,0x00,
	0x16,0x16,0x16,0x1f,0x00,0x00,0x1f,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x1f,0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x16,0x16,
	0x16,0x03,0x00,0x00,0x03,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x03,
	0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x31,
	0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x16,0x16,
	0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x02,0x02,0x00,
	0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x2d,0x16,0x16,0x16,0x16,0x1a,0x1a,0x1a,
	0x1a,0x1a,0x1a,0x1a,0x1a,0x2b,0x16,0x16,0x00,0x00,
	0x00,0x00,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,
	0x31,0x31,0x31,0x31,0x00,0x00,0x00,0x00,0x00,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x31,0x31,0x31,
	0x31,0x31,0x31,0x31,0x00,0x00,0x00,0x00,0x00,0x03,
	0x00,0x00,0x1f,0x2c,0x16,0x16,0x16,0x16,0x00,0x00,
	0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,
	0x1a,0x1a,0x00,0x00,0x00,0x00,0x1f,0x16,0x16,0x16,
	0x16,0x16,0x16,0x00,0x00,0x1a,0x1a,0x1a,0x1a,0x1a,
	0x1a,0x1a,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
	0x16,0x29,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1f,0x03,0x16,0x16,0x16,0x16,0x16,
	0x16,0x00,0x00,0x1f,0x1f,0x35,0x1f,0x1f,0x1f,0x00,
	0x00,0x00,0x19,0x00,0x02,0x02,0x02,0x02,0x16,0x16,
	0x16,0x16,0x31,0x31,0x31,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x03,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x02,
	0x02,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x00,
	0x03,0x00,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x1a,0x1a,0x1a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x02,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,0x00,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x03,0x00,0x00,0x00,0x03,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x00,0x03,0x00,0x00,0x00,0x00,0x16,0x16,0x16,0x16,
	0x16,0x16,0x15,0x15,0x00,0x00,0x1f,0x1f,0x02,0x02,
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
	0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x00,
	0x00,0x00,0x00,0x00,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x00,0x00,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x31,0x31,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x31,0x31,0x31,
	0x31,0x31,0x31,0x31,0x31,0x31,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x15,
	0x00,0x00,0x00,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x00,0x1a,0x1a,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x31,0x31,0x31,0x31,0x31,0x31,
	0x31,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x15,0x1f,0x00,
	0x00,0x00,0x00,0x00,0x15,0x15,0x15,0x1a,0x1a,0x1a,
	0x00,0x1a,0x1a,0x1a,0x15,0x15,0x15,0x15,0x15,0x31,
	0x31,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x15,0x15,0x15,0x1f,0x00,0x00,
	0x00,0x00,0x00,0x00,0x1b,0x00,0x3e,0x41,0x44,0x47,
	0x1a,0x1a,0x1b,0x00,0x1b,0x00,0x1a,0x1a,0x1a,0x1a,
	0x00,0x00,0x1a,0x1a,0x1a,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x00,
	0x00,0x00,0x15,0x15,0x15,0x15,0x1f,0x00,0x00,0x00,
	0x00,0x1f,0x1c,0x00,0x3f,0x42,0x45,0x48,0x00,0x1a,
	0x00,0x3a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,
	0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,
	0x00,0x1f,0x1f,0x15,0x15,0x15,0x15,0x27,0x27,0x27,
	0x15,0x15,0x15,0x15,0x15,0x1f,0x1f,0x1f,0x1f,0x12,
	0x1e,0x1f,0x40,0x43,0x46,0x49,0x1f,0x1f,0x1f,0x3b,
	0x1f,0x1f,0x1f,0x35,0x1f,0x1f,0x1f,0x12,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,
	0x15,0x15,0x15,0x15,0x15,0x44,0x44,0x44,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x15,0x15,
	0x15,0x15,0x15,0x44,0x44,0x44,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x27,0x27,0x27,0x27,0x27,0x27,
	0x27,0x27,0x27,0x27,0x27,0x15,0x15,0x15,0x15,0x15,
	0x15,0x44,0x44,0x44,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,
	0x44,0x44,0x44,0x15,0x15,0x15,0x15,0x15,0x15,0x44,
	0x44,0x44,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,
	0x44,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x44,0x44,0x44,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x44,0x44,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x1a,
	0x1a,0x1a,0x2b,0x1a,0x1a,0x44,0x44,0x44,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x44,0x44,0x44,0x44,
	0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x1a,0x1a,0x1a,
	0x2c,0x1a,0x1a,0x44,0x44,0x44,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x28,0x28,0x28,0x28,0x28,0x28,
	0x28,0x28,0x28,0x28,0x28,0x15,0x15,0x15,0x2e,0x15,
	0x15,0x28,0x28,0x28,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15
};
#include "tiles.h"
#include "MapInfo.h"
const struct MapInfoInternal map_internal = {
	map_map, //map
	48, //width
	56, //height
	0, //attributes
	&tiles, //tiles info
};
CODE struct MapInfo map = {
	4, //bank
	&map_internal, //data
};