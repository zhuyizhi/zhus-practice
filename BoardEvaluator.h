#include "GameBoard.h"
#include "iostream"
#include "iomanip"
#include "map"
#include "vector"
using namespace std;

class BoardEvaluator{
public:
	BoardEvaluator(GameBoard ipBoard);
	int evaluate();
	inline int initStatus(){
		memset(board_status, 0, sizeof(int)* HEIGHT * WIDTH);
		return S_OK;
	}
	inline int initIsCombo(){
		memset(board_isCombo, false, sizeof(bool) * HEIGHT * WIDTH);
		return S_OK;
	}
	void printStatus();
	double getScore();
	
private:
	
	GameBoard mpBoard;
	int comboNum[TYPE_NUM];
	int board_status[HEIGHT][WIDTH];
	bool board_isCombo[HEIGHT][WIDTH];
	int linkCellTo(int row, int col, int root);
	int evaluateIsCombo();
	map<int, vector<int>> combos;
};