#include "Banks/SetBank3.h"
#include "main.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "custom_datas.h"


//FACES
const UINT8 archer_face[] = {1, 0}; //The first number indicates the number of frames
const UINT8 slave_face[] = {1, 1}; //The first number indicates the number of frames

struct FaceInfo* face_data ;

void Start_SpriteDiagface() {
	face_data = (struct FaceInfo*)THIS->custom_data;
}

void Update_SpriteDiagface() {
	if (face_data->face_setup){
		switch(face_data->face_type){
			case 0:
				SetSpriteAnim(THIS, archer_face, 8u);
			break;
			case 1:
				SetSpriteAnim(THIS, slave_face, 8u);
			break;
		}
		face_data->face_setup = 0;
	}
}

void Destroy_SpriteDiagface() {
}
