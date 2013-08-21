#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include "BoardEvaluator.h"
#include "GameBoard.h"

class RandomPlayer{
public:
	RandomPlayer(BoardEvaluator* ieva, GameBoard* ib);
	int playAndPrint();
private:
	BoardEvaluator* eva;
	GameBoard* board;
	int move(const int height, const int width, const direction dir);
	inline bool validWidth(const int width){ return (width >= 0 && width < WIDTH); }
	inline bool validHeight(const int height){ return (height >= 0 && height < HEIGHT); }
};


#endif//RANDOM_PLAYER_H_