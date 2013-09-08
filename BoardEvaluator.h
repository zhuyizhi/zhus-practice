#ifndef BOARD_EVALUATOR_H_
#define BOARD_EVALUATOR_H_

#include "GameBoard.h"
#include "iostream"
#include "iomanip"
#include "map"
#include "vector"

struct EvaluateResult{
	int comboNum[TYPE_NUM];
	std::map<int, std::vector<int>> combos;
	EvaluateResult(){
		combos.clear();
		for(int i = 0; i < TYPE_NUM; ++i)
			comboNum[i] = 0;
	}
	void printStatus(){
		using namespace std;
		cout<<"combo numers are:"<<endl;
		for(int i = 0; i < TYPE_NUM; i++)
			cout<<setw(3)<<((perl_type)i)<<"-->"<<comboNum[i]<<" "<<endl;
		cout<<"+++++++++++++++++++++++++++"<<endl;
		
		cout<<"combos:"<<endl;
		map<int, vector<int>>::iterator ite = combos.begin();
		while(ite != combos.end()){
			cout<<ite->first<<"---> (";
			vector<int>::iterator value_ite = ite->second.begin();
			while(value_ite != ite->second.end()){
				cout<<*(value_ite++)<<",";
			}
			cout<<")"<<endl;
			ite++;
		}
		cout<<endl;
	}
};

class BoardEvaluator{
public:
	//evaluate the input board. Result is stored in comboNum and combos
	static EvaluateResult *evaluate(GameBoard* ipBoard);
	
private:
	static int linkCellTo(int row, int col, int root, GameBoard& board, int board_status[HEIGHT][WIDTH]);
	static int evaluateIsCombo(GameBoard& board, bool board_isCombo[HEIGHT][WIDTH]);
	static int connectCells(GameBoard& board, int board_status[HEIGHT][WIDTH]);
	static int adjustBoard(GameBoard& board, bool board_isCombo[HEIGHT][WIDTH]);
};

#endif//BOARD_EVALUATOR_H_