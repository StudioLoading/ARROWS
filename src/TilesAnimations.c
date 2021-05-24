#pragma bank 3

#include <gb/gb.h>

#include "../res/src/tiles.h"
#include "../res/src/tiles4.h"

extern UINT8 current_level;
extern UINT8 current_map;


void AnimWaters0() __banked{
	set_bkg_data(120u, 1u, tiles.data->data+1920u);// + 16u * 120 tile index
	set_bkg_data(123u, 1u, tiles.data->data+1968u);// + 16u * 123 tile index
	set_bkg_data(125u, 1u, tiles.data->data+2000u);// + 16u * 125 tile index
	set_bkg_data(111u, 1u, tiles.data->data+1776u);// + 16u * 111 tile index
	set_bkg_data(119u, 1u, tiles.data->data+1904u);// + 16u * 119 tile index
	set_bkg_data(99u, 1u, tiles.data->data+1584u);// + 16u * 99 tile index
	set_bkg_data(112u, 1u, tiles.data->data+1808u);// + 16u * 113 tile index
	if (current_level != 2u){
		set_bkg_data(37u, 1u, tiles4.data->data+1216u);// + 16u * 76 tile index	
	}else{
		set_bkg_data(28u, 1u, tiles4.data->data+1216u);// + 16u * 76 tile index	
	}
	
}

void AnimWaters1() __banked{
	set_bkg_data(120u, 1u, tiles.data->data+2032u);///+ 16u * 127 tile index
	set_bkg_data(123u, 1u, tiles.data->data+1984u);///+ 16u * 124 tile index
	set_bkg_data(125u, 1u, tiles.data->data+2016u);///+ 16u * 126 tile index
	set_bkg_data(111u, 1u, tiles.data->data+1648u);// + 16u * 103 tile index
	set_bkg_data(119u, 1u, tiles.data->data+1632u);// + 16u * 102 tile index
	set_bkg_data(99u, 1u, tiles.data->data+1600u);// + 16u * 100 tile index
	set_bkg_data(112u, 1u, tiles.data->data+1792u);// + 16u * 112 tile index
	if (current_level != 2u){
		set_bkg_data(37u, 1u, tiles4.data->data+1232u);// + 16u * 77 tile index
	}else{
		set_bkg_data(28u, 1u, tiles4.data->data+1232u);// + 16u * 77 tile index
	}
}

void AnimClouds0() __banked{
	set_bkg_data(93u, 1u, tiles4.data->data+1600u);///+ 16u * 100 tile index
	set_bkg_data(94u, 1u, tiles4.data->data+1616u);///+ 16u * 101 tile index
	set_bkg_data(100u, 1u, tiles4.data->data+1488u);///+ 16u * 93 tile index
	set_bkg_data(101u, 1u, tiles4.data->data+1504u);// + 16u * 94 tile index
}

void AnimClouds1() __banked{
	set_bkg_data(93u, 1u, tiles4.data->data+1488u);///+ 16u * 93 tile index
	set_bkg_data(94u, 1u, tiles4.data->data+1504u);///+ 16u * 94 tile index
	set_bkg_data(100u, 1u, tiles4.data->data+1600u);///+ 16u * 100 tile index
	set_bkg_data(101u, 1u, tiles4.data->data+1616u);// + 16u * 101 tile index	
}