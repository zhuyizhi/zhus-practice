#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include "BoardEvaluator.h"
#include "GameBoard.h"
#include "Player.h"

class RandomPlayer: public Player{
public:
	RandomPlayer(GameBoard* ib);
	int playAndPrint();
private:

};


#endif//RANDOM_PLAYER_H_