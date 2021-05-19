#pragma bank 3

#include <gb/gb.h>

#include "../res/src/tiles.h"


void AnimWaterfall0() __banked{
	set_bkg_data(120u, 1u, tiles.data->data+1920u);// + 16u * 120 tile index
}
void AnimWaterfall1() __banked{
	set_bkg_data(120u, 1u, tiles.data->data+2032u);///+ 16u * 127 tile index
}


void AnimMinifall0() __banked{
	set_bkg_data(123u, 1u, tiles.data->data+1968u);// + 16u * 123 tile index
}
void AnimMinifall1() __banked{
	set_bkg_data(123u, 1u, tiles.data->data+1984u);///+ 16u * 124 tile index
}


void AnimWaterHlight0() __banked{
	set_bkg_data(125u, 1u, tiles.data->data+2000u);// + 16u * 125 tile index
}
void AnimWaterHlight1() __banked{
	set_bkg_data(125u, 1u, tiles.data->data+2016u);///+ 16u * 126 tile index
}


void AnimSlideRight0() __banked{
	set_bkg_data(111u, 1u, tiles.data->data+1776u);// + 16u * 111 tile index
}
void AnimSlideRight1() __banked{
	set_bkg_data(111u, 1u, tiles.data->data+1648u);// + 16u * 103 tile index
}
void AnimSlideLeft0() __banked{
	set_bkg_data(119u, 1u, tiles.data->data+1904u);// + 16u * 119 tile index
}
void AnimSlideLeft1() __banked{
	set_bkg_data(119u, 1u, tiles.data->data+1632u);// + 16u * 102 tile index
}
void AnimSlideUp0() __banked{
	set_bkg_data(99u, 1u, tiles.data->data+1584u);// + 16u * 99 tile index
}
void AnimSlideUp1() __banked{
	set_bkg_data(99u, 1u, tiles.data->data+1600u);// + 16u * 100 tile index
}