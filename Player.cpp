#include "Player.h"

Player::Player(GameBoard* ib){
	this->board = ib;
}

int Player::move(int& height, int& width, const direction dir){
	int hOffset = height;
	int wOffset = width;

	switch(dir){
	case LEFT:
		--wOffset;
		break;
	case RIGHT:
		++wOffset;
		break;
	case UP:
		--hOffset;
		break;
	case DOWN:
		++hOffset;
	}

	if(!(validHeight(hOffset) && validWidth(wOffset)))
		return E_FAIL;
	int ret = board->swap(wOffset, hOffset, width, height);
	height = hOffset;
	width = wOffset;
	return ret;
}