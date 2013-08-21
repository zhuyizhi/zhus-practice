#ifndef BOARD_EVALUATOR_H_
#define BOARD_EVALUATOR_H_

#include "GameBoard.h"
#include "iostream"
#include "iomanip"
#include "map"
#include "vector"


class BoardEvaluator{
public:
	BoardEvaluator();
	int evaluate(GameBoard* ipBoard);
	void printStatus();
	void printBoard();
	double getScore();
	
private:
	std::map<int, std::vector<int>> combos();
	int comboNum[TYPE_NUM];
	int board_status[HEIGHT][WIDTH];
	bool board_isCombo[HEIGHT][WIDTH];

	inline void init(){
		memset(board_status, 0, sizeof(int)* HEIGHT * WIDTH);
		memset(board_isCombo, false, sizeof(bool) * HEIGHT * WIDTH);
	}
	int linkCellTo(int row, int col, int root, GameBoard& board);
	int evaluateIsCombo(GameBoard& board);
	int clean();	
};

#endif//BOARD_EVALUATOR_H_