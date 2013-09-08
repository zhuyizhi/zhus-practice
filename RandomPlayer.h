#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include "BoardEvaluator.h"
#include "GameBoard.h"

class RandomPlayer{
public:
	RandomPlayer(GameBoard* ib);
	int playAndPrint();
private:
	GameBoard* board;
	int move(int& height, int& width, const direction dir);
	inline bool validWidth(const int width){ return (width >= 0 && width < WIDTH); }
	inline bool validHeight(const int height){ return (height >= 0 && height < HEIGHT); }

	double simpleScore(EvaluateResult *evalute_result){
		double  score = 0;
		for(int i = 0; i < TYPE_NUM; i++)
			score += evalute_result->comboNum[i];
		return score;
	}
};


#endif//RANDOM_PLAYER_H_