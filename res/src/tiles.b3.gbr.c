#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char tilesCGB[] = {
	0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char tiles_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 1
	0xcf,0x20,0xc3,0x20,0x00,0xff,0xfb,0x04,
	0xf9,0x04,0x78,0x04,0x00,0xff,0xdf,0x20,
	
	//Frame 2
	0x00,0x00,0x00,0x44,0x00,0x44,0x44,0xaa,
	0x44,0xaa,0xea,0x15,0xae,0x51,0xff,0xff,
	
	//Frame 3
	0x00,0xff,0x2c,0x42,0x00,0x7e,0x00,0x3c,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 4
	0xaa,0x00,0xaa,0x00,0xaa,0x10,0xff,0x00,
	0xaa,0x10,0xaa,0x50,0xaa,0x54,0x8a,0x74,
	
	//Frame 5
	0xaa,0x54,0xaa,0x54,0xaa,0x54,0xff,0x00,
	0xaa,0x54,0xaa,0x44,0xaa,0x44,0xaa,0x44,
	
	//Frame 6
	0xff,0x00,0x7e,0x00,0x3c,0x00,0xff,0x00,
	0xff,0x00,0x00,0xff,0x00,0x00,0x00,0xff,
	
	//Frame 7
	0xc8,0xd4,0xb6,0x88,0xea,0xd4,0xbe,0x81,
	0xef,0xd7,0x2e,0x13,0x2e,0x13,0x3e,0x01,
	
	//Frame 8
	0x00,0x00,0x66,0x00,0x42,0x00,0x00,0x00,
	0x00,0x00,0x42,0x00,0x66,0x00,0x00,0x00,
	
	//Frame 9
	0x24,0x3c,0x3c,0x24,0x24,0x3c,0x3c,0x24,
	0x66,0x7e,0x42,0x7e,0x24,0x3c,0x18,0x18,
	
	//Frame 10
	0x00,0x00,0x28,0x44,0x10,0x28,0x00,0x10,
	0x00,0x00,0x14,0x22,0x08,0x14,0x00,0x08,
	
	//Frame 11
	0x00,0x00,0x28,0x44,0x10,0x28,0x00,0x10,
	0x00,0x00,0x14,0x22,0x08,0x14,0x00,0x08,
	
	//Frame 12
	0x00,0x08,0x08,0x14,0x14,0x22,0x00,0x00,
	0x00,0x10,0x10,0x28,0x28,0x44,0x00,0x00,
	
	//Frame 13
	0x00,0x08,0x08,0x14,0x14,0x22,0x00,0x00,
	0x00,0x10,0x10,0x28,0x28,0x44,0x00,0x00,
	
	//Frame 14
	0x00,0x00,0x00,0x02,0x02,0x24,0x24,0x48,
	0x42,0x84,0x20,0x42,0x00,0x20,0x00,0x00,
	
	//Frame 15
	0x00,0x00,0x00,0x40,0x40,0x24,0x24,0x12,
	0x42,0x21,0x04,0x42,0x00,0x04,0x00,0x00,
	
	//Frame 16
	0x00,0x00,0x00,0x40,0x40,0x24,0x24,0x12,
	0x42,0x21,0x04,0x42,0x00,0x04,0x00,0x00,
	
	//Frame 17
	0x00,0x00,0x00,0x02,0x02,0x24,0x24,0x48,
	0x42,0x84,0x20,0x42,0x00,0x20,0x00,0x00,
	
	//Frame 18
	0xc0,0x3e,0x68,0x14,0x28,0x14,0x28,0x14,
	0x28,0x14,0x28,0x14,0x62,0x1e,0xd1,0x2f,
	
	//Frame 19
	0xc0,0xc8,0xa2,0xb4,0xe2,0xdc,0xbe,0xa1,
	0xe7,0xdd,0x2e,0x17,0x27,0x1d,0x3e,0x01,
	
	//Frame 20
	0xe0,0x98,0xb8,0xc6,0xe0,0x98,0x80,0xe0,
	0xe0,0x98,0xd8,0xa6,0xe0,0x98,0x80,0xe0,
	
	//Frame 21
	0x59,0x22,0x04,0xdb,0x02,0x61,0x02,0x31,
	0x24,0x12,0x68,0x16,0x80,0x7a,0x20,0xc1,
	
	//Frame 22
	0x00,0x7e,0x00,0x81,0x60,0x9d,0x40,0xbd,
	0x40,0xbd,0x40,0xbd,0x7e,0x81,0x00,0xff,
	
	//Frame 23
	0xff,0xff,0x75,0x8a,0x57,0xa8,0x22,0x55,
	0x22,0x55,0x00,0x22,0x00,0x22,0x00,0x00,
	
	//Frame 24
	0x04,0x00,0x08,0x00,0x14,0x00,0x14,0x00,
	0x1c,0x00,0x08,0x00,0x18,0x00,0x18,0x00,
	
	//Frame 25
	0x18,0x00,0x18,0x00,0x18,0x00,0x24,0x00,
	0x3c,0x00,0xc3,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 26
	0x20,0x00,0x20,0x00,0xff,0x00,0x04,0x00,
	0x04,0x00,0x04,0x00,0xff,0x00,0x20,0x00,
	
	//Frame 27
	0x28,0x00,0x10,0x00,0x28,0x00,0x28,0x00,
	0x28,0x00,0x10,0x00,0x28,0x00,0x28,0x00,
	
	//Frame 28
	0xff,0x00,0xff,0x00,0xaa,0x00,0xaa,0x00,
	0xaa,0x00,0xaa,0x00,0xaa,0x00,0xaa,0x00,
	
	//Frame 29
	0x01,0x07,0x07,0x19,0x1b,0x65,0x07,0x19,
	0x01,0x07,0x07,0x19,0x1d,0x63,0x07,0x19,
	
	//Frame 30
	0xaa,0x00,0xaa,0x04,0xaa,0x04,0xff,0x00,
	0xaa,0x05,0xaa,0x15,0xaa,0x15,0xaa,0x41,
	
	//Frame 31
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x94,0x00,0x61,0x04,0x02,0x54,0x98,0x65,
	
	//Frame 32
	0x00,0x00,0x00,0x1c,0x14,0x26,0x14,0x26,
	0x14,0x26,0x2c,0x3e,0x1c,0x1c,0x00,0x00,
	
	//Frame 33
	0x00,0x00,0x7e,0x7e,0x5a,0x66,0x66,0x5a,
	0x42,0x7e,0x7e,0x24,0x3c,0x18,0x00,0x00,
	
	//Frame 34
	0x00,0x00,0x00,0x04,0x02,0x0a,0x0a,0x12,
	0x16,0x24,0x0c,0x48,0x38,0x70,0x00,0x00,
	
	//Frame 35
	0xfe,0xff,0xc1,0xff,0xdd,0xe3,0xcd,0xf3,
	0xd5,0xeb,0xa1,0xdf,0xdf,0xbf,0x7f,0xff,
	
	//Frame 36
	0xc1,0xcf,0x27,0x3f,0x1c,0x3c,0x1c,0x3e,
	0x33,0x37,0x61,0x69,0xc0,0xd0,0x80,0xf0,
	
	//Frame 37
	0x00,0x00,0xbb,0x00,0xc4,0x00,0xb0,0x00,
	0x1d,0x00,0xe2,0x00,0x7a,0x00,0x1b,0x00,
	
	//Frame 38
	0x06,0x00,0x18,0x00,0xb8,0x00,0x0c,0x00,
	0x7f,0x00,0x1f,0x00,0x03,0x00,0x00,0x00,
	
	//Frame 39
	0xe0,0x00,0x9c,0x00,0x0f,0x00,0x38,0x00,
	0xfe,0x00,0xe0,0x00,0x56,0x00,0x00,0x00,
	
	//Frame 40
	0xff,0x00,0x87,0x00,0x03,0x00,0x25,0x40,
	0x01,0x00,0x95,0x00,0x6b,0x94,0x95,0x6a,
	
	//Frame 41
	0x00,0x00,0x0c,0x0c,0xfa,0xfe,0x51,0xaf,
	0x51,0xaf,0xfa,0xfe,0x0c,0x0c,0x00,0x00,
	
	//Frame 42
	0x00,0x00,0x30,0x30,0x5f,0x7f,0x8a,0xf5,
	0x8a,0xf5,0x5f,0x7f,0x30,0x30,0x00,0x00,
	
	//Frame 43
	0x00,0x18,0x18,0x24,0x34,0x42,0x34,0x42,
	0x2c,0x42,0x2c,0x42,0x1c,0x42,0x1c,0x42,
	
	//Frame 44
	0x38,0x42,0x38,0x42,0x34,0x42,0x34,0x42,
	0x2c,0x42,0x2c,0x42,0x1c,0x42,0x1c,0x42,
	
	//Frame 45
	0x00,0x08,0x24,0x34,0x24,0x2c,0x24,0x34,
	0x66,0x6e,0x42,0x7e,0x24,0x3c,0x18,0x18,
	
	//Frame 46
	0x40,0x5c,0xa6,0x98,0x62,0x5c,0x9e,0xad,
	0x3e,0x4d,0x1e,0x2b,0x3e,0x01,0x3e,0x01,
	
	//Frame 47
	0xfe,0x66,0xff,0xe7,0xff,0xe7,0xff,0xff,
	0xff,0xc3,0xff,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 48
	0x00,0xff,0x00,0x9f,0x00,0xf9,0x00,0xff,
	0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 49
	0x77,0x00,0x54,0x22,0x6b,0x94,0x3f,0x40,
	0x5c,0x21,0xfd,0x02,0x3e,0x40,0xcd,0x22,
	
	//Frame 50
	0x00,0x01,0x00,0x07,0x00,0x1f,0x08,0x31,
	0x10,0x6f,0x07,0xf8,0x08,0xf0,0x00,0xe0,
	
	//Frame 51
	0x00,0x80,0x00,0xe0,0x00,0xf8,0x10,0x8c,
	0x08,0xf6,0xe0,0x1f,0x10,0x0f,0x00,0x07,
	
	//Frame 52
	0x00,0x70,0x1f,0xf0,0x3f,0xef,0x7f,0xc0,
	0x40,0xc0,0x80,0x80,0x00,0x00,0x00,0x00,
	
	//Frame 53
	0x08,0x00,0x18,0x00,0x3c,0x00,0x0c,0x00,
	0x0e,0x00,0x9f,0x00,0x57,0x28,0x2d,0x92,
	
	//Frame 54
	0x00,0x0e,0xf8,0x0f,0xfc,0xf7,0xfe,0x03,
	0x02,0x03,0x01,0x01,0x00,0x00,0x00,0x00,
	
	//Frame 55
	0x02,0x02,0x1e,0x64,0x3b,0x45,0x76,0x0e,
	0x6e,0x18,0x5c,0x32,0x38,0x66,0x40,0x40,
	
	//Frame 56
	0x01,0x01,0x1e,0x62,0x3f,0x45,0x7e,0x0a,
	0x74,0x1a,0x6c,0x72,0x58,0x56,0x70,0x70,
	
	//Frame 57
	0x81,0x81,0x63,0x63,0x36,0x36,0x1c,0x1c,
	0x1c,0x1c,0x34,0x34,0x66,0x66,0xc3,0xc3,
	
	//Frame 58
	0x81,0x00,0xd9,0x00,0x3a,0x00,0x1c,0x00,
	0x1c,0x00,0x1c,0x00,0x1c,0x00,0x1c,0x00,
	
	//Frame 59
	0x1c,0x00,0x14,0x00,0x34,0x00,0x24,0x00,
	0x24,0x00,0x6c,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 60
	0x00,0x00,0xff,0x00,0x00,0xff,0xff,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 61
	0x81,0x81,0xc3,0xc3,0x26,0x26,0x3c,0x3c,
	0x18,0x18,0x3c,0x3c,0xe7,0xe7,0x81,0x81,
	
	//Frame 62
	0x00,0x00,0x03,0x00,0x0f,0x00,0x1f,0x00,
	0x1d,0x00,0x3f,0x00,0x3f,0x00,0x3f,0x00,
	
	//Frame 63
	0x3f,0x00,0x3c,0x00,0x7c,0x00,0x71,0x00,
	0x73,0x00,0x72,0x00,0x64,0x00,0xea,0x00,
	
	//Frame 64
	0xe8,0x00,0x10,0x00,0x16,0x00,0x16,0x00,
	0x1f,0x00,0x3d,0x00,0x3a,0x00,0x7a,0x00,
	
	//Frame 65
	0xff,0x00,0xf7,0x00,0xfb,0x00,0xfb,0x00,
	0xfb,0x00,0xeb,0x00,0xf7,0x00,0xff,0x00,
	
	//Frame 66
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0x40,0x00,0x3f,0x00,0xa0,0x00,
	
	//Frame 67
	0xa0,0x00,0xa0,0x00,0x40,0x00,0x3c,0x00,
	0x42,0x00,0x42,0x00,0x82,0x00,0x83,0x00,
	
	//Frame 68
	0x00,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	
	//Frame 69
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0x0f,0x00,0x87,0x00,
	
	//Frame 70
	0x87,0x00,0xc7,0x00,0xa7,0x00,0xa7,0x00,
	0x87,0x00,0xc7,0x00,0xc7,0x00,0x0f,0x00,
	
	//Frame 71
	0x00,0x00,0x80,0x00,0xe0,0x00,0xf0,0x00,
	0xf8,0x00,0xfc,0x00,0xfc,0x00,0xfe,0x00,
	
	//Frame 72
	0xf6,0x00,0xf3,0x00,0xe1,0x00,0xc1,0x00,
	0xc1,0x00,0xc0,0x00,0xe0,0x00,0xf0,0x00,
	
	//Frame 73
	0xf8,0x00,0xfc,0x00,0xbc,0x00,0x9e,0x00,
	0x8c,0x00,0x88,0x00,0x80,0x00,0x00,0x00,
	
	//Frame 74
	0xff,0xff,0xff,0xff,0xcb,0xff,0xe7,0xff,
	0xd3,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,
	
	//Frame 75
	0xff,0xdf,0xff,0xb1,0xf3,0xed,0xf3,0xcf,
	0xef,0x87,0xdf,0xef,0xff,0xff,0xff,0xff,
	
	//Frame 76
	0x9f,0xbf,0x87,0xdf,0x97,0xd6,0xc3,0xf7,
	0xe3,0xfb,0x73,0x7f,0x7a,0x7b,0x3d,0x3f,
	
	//Frame 77
	0xf9,0xfd,0xe1,0xfb,0xe9,0x6b,0xc3,0xef,
	0xc7,0xdf,0xce,0xfe,0x5e,0xde,0xbc,0xfc,
	
	//Frame 78
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 79
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 80
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 81
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 82
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 83
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 84
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 85
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 86
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 87
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 88
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 89
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 90
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 91
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 92
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 93
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 94
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 95
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 96
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 97
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 98
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 99
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 100
	0x00,0x7f,0x40,0x80,0x40,0xbf,0x40,0xbb,
	0x40,0xb6,0x40,0xbf,0x7f,0x80,0x00,0xff,
	
	//Frame 101
	0x00,0xfe,0x00,0x03,0x02,0xfd,0x02,0x6d,
	0x02,0xdd,0x02,0xfd,0xfe,0x01,0x00,0xff,
	
	//Frame 102
	0x30,0x58,0x90,0x78,0x37,0xd8,0xb0,0x5e,
	0x08,0x7c,0x30,0x78,0x97,0x68,0x30,0x58,
	
	//Frame 103
	0x30,0x58,0x20,0x5c,0xa7,0x58,0x24,0x58,
	0x24,0x58,0x28,0x5c,0xbf,0x58,0x34,0x58,
	
	//Frame 104
	0x00,0x7e,0x3c,0xc3,0x42,0xbd,0x42,0xbd,
	0x42,0xbd,0x42,0xbd,0x3c,0xc3,0x00,0x7e,
	
	//Frame 105
	0x20,0x00,0x20,0x00,0xed,0x1f,0x0d,0x30,
	0x3a,0x25,0x34,0x28,0xf7,0x28,0x28,0x38,
	
	//Frame 106
	0x30,0x28,0x30,0x28,0xfa,0x25,0x0d,0x30,
	0x0d,0x1f,0x04,0x00,0xff,0x00,0x20,0x00,
	
	//Frame 107
	0x30,0x28,0x30,0x28,0xf7,0x28,0x14,0x28,
	0x34,0x28,0x34,0x28,0xf7,0x28,0x30,0x28,
	
	//Frame 108
	0x20,0x00,0x20,0x00,0x08,0xf7,0xff,0x00,
	0xf7,0xff,0x02,0x00,0xff,0x00,0x20,0x00,
	
	//Frame 109
	0x20,0x00,0x20,0x00,0x6f,0xf0,0x64,0x18,
	0xbc,0x48,0x1c,0x28,0xdf,0x28,0x28,0x38,
	
	//Frame 110
	0x60,0x08,0x58,0x28,0x3f,0xc8,0xe4,0x18,
	0xe4,0xf0,0x04,0x00,0xff,0x00,0x20,0x00,
	
	//Frame 111
	0x00,0x7f,0x7f,0x80,0x12,0xa4,0x00,0x92,
	0x12,0xa4,0x7f,0x80,0x00,0x7f,0x00,0x00,
	
	//Frame 112
	0x1f,0xe0,0x00,0xff,0x3c,0x43,0x00,0xff,
	0x03,0x60,0x00,0xff,0xf0,0x03,0x00,0xff,
	
	//Frame 113
	0xf0,0x0e,0x00,0xff,0x03,0x34,0x00,0xff,
	0x30,0x06,0x00,0xff,0x0f,0x30,0x00,0xff,
	
	//Frame 114
	0x85,0x81,0xff,0xc3,0x67,0x66,0x3f,0x3c,
	0x19,0x18,0xe7,0x66,0xf3,0xc2,0x9f,0x81,
	
	//Frame 115
	0x0b,0x00,0x44,0x00,0x37,0x00,0x8f,0x00,
	0xfd,0x00,0x3d,0x00,0x6d,0x00,0x6d,0x00,
	
	//Frame 116
	0xd0,0x00,0x22,0x00,0xec,0x00,0xf1,0x00,
	0xbf,0x00,0xbc,0x00,0xb6,0x00,0xb6,0x00,
	
	//Frame 117
	0xed,0x00,0xed,0x00,0xed,0x00,0x6d,0x00,
	0x6d,0x00,0x6d,0x00,0x60,0x0d,0x40,0x00,
	
	//Frame 118
	0xb7,0x00,0xb7,0x00,0xb7,0x00,0xb6,0x00,
	0xb6,0x00,0xb6,0x00,0x06,0xb0,0x02,0x00,
	
	//Frame 119
	0x00,0xfe,0xfe,0x01,0x48,0x25,0x00,0x49,
	0x48,0x25,0xfe,0x01,0x00,0xfe,0x00,0x00,
	
	//Frame 120
	0xab,0x00,0xbf,0x00,0xbb,0x00,0xaa,0x00,
	0xaa,0x00,0xaa,0x00,0xee,0x00,0xee,0x00,
	
	//Frame 121
	0x20,0x00,0xff,0x00,0x11,0x00,0x11,0x00,
	0x77,0x00,0xff,0x00,0xd6,0x00,0xab,0x00,
	
	//Frame 122
	0x3c,0x00,0x7e,0x00,0xe7,0x18,0xc3,0x3c,
	0x99,0x24,0xbd,0x00,0xdb,0x00,0x6e,0x00,
	
	//Frame 123
	0x18,0x00,0x34,0x00,0x3c,0x00,0x34,0x00,
	0x34,0x00,0x1c,0x00,0x3c,0x00,0x34,0x00,
	
	//Frame 124
	0x34,0x00,0x1c,0x00,0x3c,0x00,0x34,0x00,
	0x18,0x00,0x34,0x00,0x3c,0x00,0x34,0x00,
	
	//Frame 125
	0xe0,0x00,0xff,0x00,0x43,0x00,0xff,0x00,
	0x60,0x00,0xff,0x00,0x03,0x00,0xff,0x00,
	
	//Frame 126
	0x0e,0x00,0xff,0x00,0x34,0x00,0xff,0x00,
	0x06,0x00,0xff,0x00,0x30,0x00,0xff,0x00,
	
	//Frame 127
	0xaa,0x00,0xaa,0x00,0xee,0x00,0xee,0x00,
	0xab,0x00,0xbf,0x00,0xbb,0x00,0xaa,0x00
};

#include "TilesInfo.h"
const struct TilesInfoInternal tiles_internal = {
	8, //width
	8, //height
	128, //num_tiles
	tiles_tiles, //tiles
	tilesCGB, //CGB palette
};
CODE struct TilesInfo tiles = {
	3, //bank
	&tiles_internal, //data
};