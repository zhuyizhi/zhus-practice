#ifndef MY_ENUMS_H_
#define MY_ENUMS_H_

const int WIDTH = 6;
const int HEIGHT = 5;
const int TYPE_NUM = 7;
enum perl_type{
	NOT_INITIALIZED,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	BLACK,
	HEART
};

enum ret_status{
	S_OK,
	E_FAIL
};

enum direction{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

#endif//MY_ENUMS_H_