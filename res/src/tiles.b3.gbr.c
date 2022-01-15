#pragma bank 3

void empty(void) __nonbanked;
__addressmod empty const CODE;

const unsigned char tilesCGB[] = {
	0x00,0x03,0x02,0x00,0x02,0x02,0x07,0x00,0x00,0x01,0x02,0x02,0x03,0x00,0x07,0x04,0x00,0x00,0x07,0x00,0x02,0x01,0x02,0x02,0x00,0x00,0x06,0x02,0x02,0x02,0x02,0x00,0x03,0x06,0x05,0x07,0x02,0x01,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x02,0x00,0x06,0x06,0x00,0x00,0x00,0x01,0x00,0x01,0x07,0x07,0x02,0x00,0x00,0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x04,0x04,0x02,0x03,0x03,0x03,0x03,0x03,0x04,0x04,0x04,0x04,0x06,0x06,0x00,0x06,0x06,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x06,0x07,0x07,0x00,0x07,0x07,0x07,0x07,0x06,0x06,0x00,0x07,0x06,0x06,0x06,0x06,0x00
};

const unsigned char tiles_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 1
	0x20,0xff,0x20,0xef,0x20,0xe3,0xff,0xff,
	0x04,0xff,0x04,0xfd,0x04,0x7c,0xff,0xff,
	
	//Frame 2
	0x40,0x40,0x40,0x40,0xe4,0xa4,0xe4,0xa4,
	0xee,0xaa,0xff,0x11,0xff,0x11,0xff,0xff,
	
	//Frame 3
	0xff,0xff,0x6e,0x42,0x7e,0x7e,0x3c,0x3c,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 4
	0xaa,0x00,0xaa,0x00,0xba,0x10,0xff,0x00,
	0xba,0x10,0xfa,0x50,0xfe,0x54,0xfe,0x74,
	
	//Frame 5
	0xfe,0x54,0xfe,0x54,0xfe,0x54,0xff,0x00,
	0xfe,0x54,0xee,0x44,0xee,0x44,0xee,0x44,
	
	//Frame 6
	0xff,0xff,0x7b,0x43,0xff,0xff,0x3a,0xbf,
	0xbf,0x3e,0xdf,0x14,0xd7,0x1e,0xf3,0x2a,
	
	//Frame 7
	0xc8,0xd4,0xb6,0x88,0xea,0xd4,0xbe,0x81,
	0xef,0xd7,0x2e,0x13,0x2e,0x13,0x3e,0x01,
	
	//Frame 8
	0x00,0x00,0x66,0x66,0x42,0x42,0x00,0x00,
	0x00,0x00,0x42,0x42,0x66,0x66,0x00,0x00,
	
	//Frame 9
	0x24,0x3c,0x3c,0x24,0x24,0x3c,0x3c,0x24,
	0x66,0x7e,0x42,0x7e,0x24,0x3c,0x18,0x18,
	
	//Frame 10
	0x31,0x00,0x4a,0x00,0x8c,0x00,0x52,0x00,
	0xa0,0x00,0x13,0x00,0x4c,0x00,0xa2,0x00,
	
	//Frame 11
	0x00,0x00,0x6c,0x6c,0x38,0x38,0x10,0x10,
	0x00,0x00,0x36,0x36,0x1c,0x1c,0x08,0x08,
	
	//Frame 12
	0xff,0xff,0x20,0xff,0x20,0xff,0xff,0xff,
	0x04,0xff,0x04,0xfd,0x04,0x7c,0xff,0xff,
	
	//Frame 13
	0x08,0x08,0x1c,0x1c,0x36,0x36,0x00,0x00,
	0x10,0x10,0x38,0x38,0x6c,0x6c,0x00,0x00,
	
	//Frame 14
	0xf9,0xe1,0x7b,0x43,0x7e,0x72,0xbf,0x3a,
	0xbf,0x3e,0xd7,0x14,0xdf,0x16,0xfb,0x22,
	
	//Frame 15
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	
	//Frame 16
	0x00,0x00,0x40,0x40,0x64,0x64,0x36,0x36,
	0x63,0x63,0x46,0x46,0x04,0x04,0x00,0x00,
	
	//Frame 17
	0x00,0x00,0x02,0x02,0x26,0x26,0x6c,0x6c,
	0xc6,0xc6,0x62,0x62,0x20,0x20,0x00,0x00,
	
	//Frame 18
	0xff,0xff,0x5e,0x62,0x7e,0x7e,0x3c,0x24,
	0x3c,0x34,0x7e,0x7e,0x7e,0x42,0xff,0xff,
	
	//Frame 19
	0xc0,0xc8,0xa2,0xb4,0xe2,0xdc,0xbe,0xa1,
	0xe7,0xdd,0x2e,0x17,0x27,0x1d,0x3e,0x01,
	
	//Frame 20
	0xf0,0x90,0xfc,0x8c,0xf0,0x90,0xe0,0xe0,
	0xf8,0x98,0xfe,0x86,0xf8,0x98,0xe0,0xe0,
	
	//Frame 21
	0xdb,0xdf,0x61,0x63,0x31,0x33,0x12,0x36,
	0x16,0x7e,0x72,0xf2,0xe1,0xc3,0x7f,0x22,
	
	//Frame 22
	0x7e,0x7e,0x81,0x81,0xe1,0x9d,0xc1,0xbd,
	0xc1,0xbd,0xc1,0xbd,0xff,0x81,0xff,0xff,
	
	//Frame 23
	0xff,0xff,0xff,0x88,0xff,0x88,0x77,0x55,
	0x27,0x25,0x22,0x22,0x02,0x02,0x00,0x00,
	
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
	0x07,0x07,0x1f,0x19,0x7f,0x61,0x1f,0x19,
	0x07,0x07,0x0f,0x09,0x3f,0x31,0x0f,0x09,
	
	//Frame 30
	0xaa,0x00,0xae,0x04,0xae,0x04,0xff,0x00,
	0xaf,0x05,0xbf,0x15,0xbf,0x15,0xeb,0x41,
	
	//Frame 31
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x02,0x50,0x98,0x65,
	
	//Frame 32
	0x00,0x00,0x1c,0x00,0x36,0x04,0x36,0x04,
	0x36,0x04,0x3e,0x2a,0x1c,0x1c,0x00,0x00,
	
	//Frame 33
	0x00,0x00,0x7e,0x7e,0x42,0x66,0x42,0x5a,
	0x42,0x7e,0x24,0x24,0x18,0x18,0x00,0x00,
	
	//Frame 34
	0x00,0x00,0x04,0x00,0x0a,0x02,0x12,0x02,
	0x24,0x04,0x48,0x08,0x70,0x70,0x00,0x00,
	
	//Frame 35
	0xd3,0x1a,0xd7,0x1e,0xdf,0x14,0xbf,0x3e,
	0xbf,0x3a,0xff,0xff,0x7b,0x43,0xff,0xff,
	
	//Frame 36
	0x10,0x00,0x10,0x00,0x30,0x00,0x3a,0x00,
	0x7f,0x00,0x7f,0x00,0x7f,0x00,0x7e,0x00,
	
	//Frame 37
	0x7e,0x00,0x36,0x00,0xef,0x00,0x78,0x00,
	0xcc,0x00,0x00,0x00,0x03,0x00,0x20,0x00,
	
	//Frame 38
	0x06,0x00,0x18,0x00,0xb8,0x00,0x0c,0x00,
	0x7f,0x00,0x1f,0x00,0x03,0x00,0x00,0x00,
	
	//Frame 39
	0xe0,0x00,0x9c,0x00,0x0f,0x00,0x38,0x00,
	0xfe,0x00,0xe0,0x00,0x56,0x00,0x00,0x00,
	
	//Frame 40
	0x00,0x00,0x78,0x78,0xfc,0xfc,0xfe,0x9a,
	0xfe,0xfe,0x7e,0xea,0x00,0x00,0x00,0x00,
	
	//Frame 41
	0xff,0x00,0xff,0x0c,0xfb,0xfe,0x51,0xaf,
	0x51,0xaf,0xfb,0xfe,0xff,0x0c,0xff,0x00,
	
	//Frame 42
	0xff,0x00,0xff,0x30,0xdf,0x7f,0x8a,0xf5,
	0x8a,0xf5,0xdf,0x7f,0xff,0x30,0xff,0x00,
	
	//Frame 43
	0x18,0x7e,0x3c,0xff,0x7e,0xff,0x7e,0xff,
	0x7e,0xff,0x7e,0xff,0x7e,0xff,0x7e,0xff,
	
	//Frame 44
	0x7e,0xff,0x7e,0xff,0x7e,0xff,0x7e,0xff,
	0x7e,0xff,0x7e,0xff,0x7e,0xff,0x7e,0xff,
	
	//Frame 45
	0x00,0x08,0x24,0x34,0x24,0x2c,0x24,0x34,
	0x66,0x6e,0x42,0x7e,0x24,0x3c,0x18,0x18,
	
	//Frame 46
	0x40,0x5c,0xa6,0x98,0x62,0x5c,0x9e,0xad,
	0x3e,0x4d,0x1e,0x2b,0x3e,0x01,0x3e,0x01,
	
	//Frame 47
	0x00,0xff,0x0d,0xf0,0x35,0xc0,0x34,0x80,
	0x62,0x80,0x62,0x10,0xc1,0x30,0xc1,0x30,
	
	//Frame 48
	0x00,0xff,0x00,0xff,0x40,0x3f,0x20,0x1f,
	0x08,0x17,0x4c,0x13,0x2e,0x11,0x17,0x08,
	
	//Frame 49
	0xdf,0xff,0xdf,0x20,0x00,0xff,0xfb,0x04,
	0xff,0xaa,0xff,0x5b,0xff,0xdf,0xff,0xdf,
	
	//Frame 50
	0x1e,0x00,0xff,0x00,0x33,0x00,0xff,0x00,
	0x42,0x00,0xff,0x00,0x54,0x00,0xff,0x00,
	
	//Frame 51
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	
	//Frame 52
	0x31,0x00,0x4a,0x00,0x8c,0x00,0x52,0x00,
	0xa0,0x00,0x13,0x00,0x4c,0x00,0xa2,0x00,
	
	//Frame 53
	0x08,0x00,0x18,0x00,0x3c,0x00,0x0c,0x00,
	0x0e,0x00,0x9f,0x00,0x57,0x28,0x2d,0x92,
	
	//Frame 54
	0xc8,0x30,0x20,0x5c,0x58,0xa4,0xa0,0x4c,
	0x68,0x86,0xb0,0x0e,0x66,0x11,0xcc,0x23,
	
	//Frame 55
	0x02,0x02,0x04,0x64,0x01,0x45,0x06,0x0e,
	0x08,0x18,0x10,0x32,0x20,0x66,0x40,0x40,
	
	//Frame 56
	0x01,0x01,0x02,0x62,0x05,0x45,0x0a,0x0a,
	0x10,0x18,0x60,0x72,0x50,0x56,0x70,0x70,
	
	//Frame 57
	0xaa,0x00,0xaa,0x00,0xba,0x10,0xff,0x00,
	0xba,0x10,0xfa,0x50,0xfe,0x54,0xfe,0x74,
	
	//Frame 58
	0x00,0x81,0x00,0xd9,0x00,0x3a,0x00,0x1c,
	0x00,0x1c,0x00,0x1c,0x00,0x1c,0x00,0x1c,
	
	//Frame 59
	0x00,0x1c,0x00,0x14,0x00,0x34,0x00,0x24,
	0x00,0x24,0x00,0x6c,0x00,0x00,0x00,0x00,
	
	//Frame 60
	0x81,0x06,0x41,0x02,0x20,0x01,0x10,0x00,
	0x0c,0x00,0x03,0x00,0x01,0x00,0x00,0x00,
	
	//Frame 61
	0x80,0x60,0xa0,0x50,0x50,0xac,0x34,0x42,
	0x82,0x3d,0x51,0x0e,0x0c,0x03,0x02,0x01,
	
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
	0xfd,0xe5,0x7f,0x45,0x7f,0x75,0xbf,0x3d,
	0xbf,0x3f,0xd5,0x15,0xdf,0x15,0xff,0x27,
	
	//Frame 75
	0xf9,0xe1,0xfb,0xa3,0xfe,0xb2,0xff,0xba,
	0xbf,0xbe,0xf7,0xf4,0xff,0xb6,0xfb,0xa2,
	
	//Frame 76
	0xff,0xff,0xfb,0x83,0xff,0xbf,0xff,0xba,
	0xbf,0xbe,0xf7,0xf4,0xff,0xb6,0xfb,0xa2,
	
	//Frame 77
	0xff,0xff,0x7b,0x41,0xff,0xfd,0xbf,0x3d,
	0xbf,0x3d,0xd7,0x15,0xdd,0x15,0xff,0x27,
	
	//Frame 78
	0x00,0xaa,0x00,0x55,0x00,0x00,0x00,0xaa,
	0x00,0x00,0x00,0x22,0x00,0x00,0x00,0x00,
	
	//Frame 79
	0x02,0x01,0x0c,0x03,0x51,0x0e,0x82,0x3d,
	0x34,0x42,0x50,0xac,0xa0,0x50,0x80,0x60,
	
	//Frame 80
	0xc0,0x00,0xb0,0x00,0xca,0x00,0xcd,0x20,
	0x66,0x00,0x3f,0x00,0x0d,0x02,0x07,0x00,
	
	//Frame 81
	0xf7,0xbf,0x5b,0xff,0x35,0x7f,0x60,0x1f,
	0xac,0x00,0x13,0x00,0x4c,0x00,0xa2,0x00,
	
	//Frame 82
	0x00,0x80,0x00,0xc0,0x80,0x40,0xc0,0x20,
	0x20,0x18,0xa8,0x04,0x64,0x82,0x6a,0x91,
	
	//Frame 83
	0xdb,0x00,0x83,0x00,0xd7,0x00,0xbd,0x00,
	0x99,0x00,0xd3,0x00,0xbd,0x00,0xed,0x00,
	
	//Frame 84
	0x13,0x04,0x63,0x80,0xb1,0x02,0x12,0x24,
	0x36,0x48,0x72,0x80,0xc1,0x02,0x22,0x10,
	
	//Frame 85
	0xb9,0xa1,0xfb,0xe3,0xfe,0xf2,0xbf,0xba,
	0xbf,0xbe,0xff,0xbf,0xdf,0x90,0xff,0xff,
	
	//Frame 86
	0xfd,0xe5,0x7f,0x45,0x7f,0x75,0xbf,0x3d,
	0xbf,0x3d,0xff,0xfd,0xdf,0x11,0xff,0xff,
	
	//Frame 87
	0x80,0x7f,0x00,0xfd,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0xff,0x00,0xff,0x02,0xfd,
	
	//Frame 88
	0x00,0xef,0x00,0xff,0x00,0xff,0x00,0xfd,
	0x00,0x78,0x00,0xfd,0x00,0xff,0x00,0xff,
	
	//Frame 89
	0x40,0x50,0x91,0xa9,0x2a,0x56,0x28,0x54,
	0x28,0x54,0x79,0x45,0x92,0xae,0x00,0x18,
	
	//Frame 90
	0xfb,0xff,0xd1,0xd9,0xa3,0xb3,0x81,0xbf,
	0x89,0x8d,0xd3,0xdb,0xa3,0xb3,0xcf,0xef,
	
	//Frame 91
	0x25,0xff,0x25,0xef,0x25,0xe7,0xff,0xff,
	0x05,0xff,0x07,0xfd,0x07,0x7d,0xff,0xff,
	
	//Frame 92
	0xa0,0xff,0xa0,0xef,0xa0,0xe3,0xff,0xff,
	0xa4,0xff,0xa4,0xfd,0xa4,0xfc,0xff,0xff,
	
	//Frame 93
	0x88,0x00,0xb2,0x00,0x96,0x00,0xa1,0x00,
	0xb1,0x00,0x93,0x00,0x91,0x00,0xa1,0x00,
	
	//Frame 94
	0x4d,0x02,0x47,0x00,0x4b,0x04,0x8b,0x00,
	0x07,0x00,0x87,0x00,0x99,0x02,0x07,0x00,
	
	//Frame 95
	0x00,0xff,0x00,0x1f,0x00,0x07,0x00,0x0b,
	0x02,0x81,0x00,0x25,0x12,0x09,0x48,0x37,
	
	//Frame 96
	0x60,0x1f,0xd4,0x2b,0x00,0x7f,0x00,0xff,
	0xa0,0x5f,0x00,0xff,0x00,0xff,0x00,0xff,
	
	//Frame 97
	0x00,0xff,0x00,0xf8,0x00,0xe0,0x00,0xc1,
	0x00,0x84,0x00,0x80,0x00,0x11,0x00,0x00,
	
	//Frame 98
	0x00,0x02,0x00,0x01,0x00,0x95,0x00,0x8b,
	0x20,0xd5,0x10,0xea,0x00,0xff,0x00,0xff,
	
	//Frame 99
	0xc6,0x82,0xfe,0x92,0xee,0xaa,0xc6,0x82,
	0xfe,0x92,0xee,0xaa,0xc6,0x82,0x7c,0x7c,
	
	//Frame 100
	0xfe,0x92,0xee,0xaa,0xc6,0x82,0x7c,0x7c,
	0xc6,0x82,0xfe,0x92,0xee,0xaa,0xc6,0x82,
	
	//Frame 101
	0x81,0x81,0x63,0x63,0x34,0x34,0x18,0x18,
	0x1c,0x1c,0x36,0x36,0x61,0x61,0xc0,0xc0,
	
	//Frame 102
	0xef,0xef,0xff,0x10,0xd6,0x52,0x94,0x94,
	0xd6,0x52,0xff,0x10,0xef,0xef,0x00,0x00,
	
	//Frame 103
	0xf7,0xf7,0xff,0x08,0x6b,0x4a,0x29,0x29,
	0x6b,0x4a,0xff,0x08,0xf7,0xf7,0x00,0x00,
	
	//Frame 104
	0xfe,0xfe,0xe7,0xe7,0xfd,0x99,0x7c,0xbd,
	0x40,0xbd,0x64,0x99,0x7e,0x81,0x7e,0xff,
	
	//Frame 105
	0x00,0x00,0x00,0x00,0x1f,0x00,0x30,0x00,
	0x27,0x00,0x2c,0x00,0x2c,0x00,0x28,0x00,
	
	//Frame 106
	0x28,0x00,0x28,0x00,0x27,0x00,0x30,0x00,
	0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 107
	0x28,0x00,0x28,0x00,0x28,0x00,0x28,0x00,
	0x28,0x00,0x28,0x00,0x28,0x00,0x28,0x00,
	
	//Frame 108
	0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
	0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 109
	0x00,0x00,0x00,0x00,0xf0,0x00,0x18,0x00,
	0xc8,0x00,0x28,0x00,0x28,0x00,0x28,0x00,
	
	//Frame 110
	0x28,0x00,0x68,0x00,0xc8,0x00,0x18,0x00,
	0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 111
	0x7f,0x7f,0xff,0x80,0xb6,0xa4,0x92,0x92,
	0xb6,0xa4,0xff,0x80,0x7f,0x7f,0x00,0x00,
	
	//Frame 112
	0x00,0x00,0x00,0x00,0x00,0xff,0x3c,0x43,
	0x00,0xff,0x03,0x60,0x00,0xff,0xf0,0x03,
	
	//Frame 113
	0x00,0x00,0x00,0x00,0x00,0xff,0x03,0x34,
	0x00,0xff,0x30,0x06,0x00,0xff,0x0f,0x30,
	
	//Frame 114
	0x00,0x00,0x00,0x00,0x82,0x82,0xff,0xff,
	0x82,0x82,0x00,0x00,0x00,0x00,0x00,0x00,
	
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
	0xfe,0xfe,0xff,0x01,0x6d,0x25,0x49,0x49,
	0x6d,0x25,0xff,0x01,0xfe,0xfe,0x00,0x00,
	
	//Frame 120
	0x54,0x00,0x40,0x00,0x44,0x00,0x55,0x00,
	0x55,0x00,0x55,0x00,0x11,0x00,0x11,0x00,
	
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
	0x00,0x00,0x00,0x00,0xbc,0x00,0x00,0x00,
	0x9f,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,
	
	//Frame 126
	0x00,0x00,0x00,0x00,0xcb,0x00,0x00,0x00,
	0xf9,0x00,0x00,0x00,0xcf,0x00,0x00,0x00,
	
	//Frame 127
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
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