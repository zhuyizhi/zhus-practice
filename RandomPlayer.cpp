#include "iostream"

#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(BoardEvaluator* ieva, GameBoard* ib){
	this->board = ib;
	this->eva = ieva;
}

int RandomPlayer::move(const int height, const int width, const direction dir){
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

	return board->swap(wOffset, hOffset, width, height);
}

int RandomPlayer::playAndPrint(){
	int w = 2;
	int h = 2;
	direction dir = RIGHT;
	cout<<"(" << w <<","<< h <<") is moving " << dir << endl;
	move(0, 1, DOWN);
	board->printBoard();
	cout<<"for compare"<<endl;
	this->eva->printBoard();
	this->eva->evaluate();
	cout<<"now the score is:"<< this->eva->getScore() <<endl;
	

	return S_OK;
}