#ifndef PLAYER_H_
#define PLAYER_H_

#include "BoardEvaluator.h"
#include "GameBoard.h"

class Player{
public:
	Player(GameBoard *ib);

protected:
	GameBoard* board;
	int move(int& height, int& width, const direction dir);
	inline bool validWidth(const int width){ return (width >= 0 && width < WIDTH); }
	inline bool validHeight(const int height){ return (height >= 0 && height < HEIGHT); }
};

#endif PLAYER_H_