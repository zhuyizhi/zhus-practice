#include "BoardEvaluator.h"

using namespace std;

BoardEvaluator::BoardEvaluator(){
	memset(comboNum, 0, sizeof(int) * TYPE_NUM);
}

int BoardEvaluator::evaluate(GameBoard* ipBoard){
	int iteRound = -1;
	bool haveCombo;
	GameBoard lBoard(*ipBoard);
	memset(comboNum, 0, sizeof(int) * TYPE_NUM);
	combos.clear();
	do{
		haveCombo = false;
		iteRound++;
		init();
		//1. init board status.
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				if(board_status[i][j] == NOT_INITIALIZED){
					linkCellTo(i, j,  i * WIDTH + j + 1, lBoard);
				}
			}
		}
		//2. init isCombo
		evaluateIsCombo(lBoard);
		//3. init combos and comboNum
		map<int, vector<int>> tempMap;
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				if(board_isCombo[i][j]){
					haveCombo = true;
					int root = board_status[i][j] + iteRound * WIDTH * HEIGHT;
					int current = i * WIDTH + j + 1 + iteRound * WIDTH * HEIGHT;
					if(tempMap.find(root) == tempMap.end()){
						vector<int> vec;
						tempMap.insert(make_pair(root, vec));
					}
					map<int, vector<int>>::iterator ite = tempMap.find(root);
					ite->second.push_back(current);				
				}
			}
		}

		map<int, vector<int>>::iterator ite = tempMap.begin();
		while(ite != tempMap.end()){
			int root = ite->first;
			int row = (root - 1 - iteRound * WIDTH * HEIGHT) / WIDTH;
			int col = (root - 1 - iteRound * WIDTH * HEIGHT) % WIDTH;
			perl_type type;
			lBoard.getCell(row, col, type);
			this->comboNum[(int)type]++;
			combos.insert(*ite);
			ite++;
		}

		

		// 4. adjust the board
		for(int j = 0; j < WIDTH; j++){
			for(int i = HEIGHT -1, newHeight = i; i >= 0; i--){
				if(!board_isCombo[i][j]){
					if(i != newHeight){
						perl_type cType;
						lBoard.getCell(i, j, cType);
						lBoard.setCell(newHeight, j, cType);
						lBoard.setCell(i, j, NOT_INITIALIZED);
					}

					newHeight--;
				}else{
					lBoard.setCell(i, j, NOT_INITIALIZED);
				}
			}
		}

	}while(haveCombo);


	return S_OK;
}

int BoardEvaluator::evaluateIsCombo(GameBoard& board){
	//2.1, horizontally search
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH - 2; j++){
			perl_type current = NOT_INITIALIZED;
			board.getCell(i, j, current);
			if(current == NOT_INITIALIZED)
				continue;
			perl_type other = NOT_INITIALIZED;
			board.getCell(i, j + 1, other);
			perl_type third = NOT_INITIALIZED;
			board.getCell(i, j + 2, third);
			if(current == other && current == third){
				board_isCombo[i][j] = board_isCombo[i][j + 1] = board_isCombo[i][j + 2] = true;
			}
		}
	}
	//2.2, vertically search
	for(int i = 0; i < HEIGHT - 2; i++){
		for(int j = 0; j < WIDTH; j++){
			perl_type current = NOT_INITIALIZED;
			board.getCell(i, j, current);
			if(current == NOT_INITIALIZED)
				continue;
			perl_type other = NOT_INITIALIZED;
			board.getCell(i + 1, j, other);
			perl_type third = NOT_INITIALIZED;
			board.getCell(i + 2, j, third);
			if(current == other && current == third){
				board_isCombo[i][j] = board_isCombo[i + 1][j] = board_isCombo[i + 2][j] = true;
			}
		}
	}
	return S_OK;
}

int BoardEvaluator::linkCellTo(int row, int col, int root, GameBoard& board){
	perl_type current;
	board.getCell(row, col, current);//currently don't check return value
	if(current == NOT_INITIALIZED)
		return S_OK;
	board_status[row][col] = root;
	perl_type other = NOT_INITIALIZED;
	if(row > 0){
		board.getCell(row - 1,col, other);
		if(current == other && board_status[row - 1][col] != root)
			linkCellTo(row - 1, col, root);
	}
	if(row + 1 < HEIGHT){
		board.getCell(row + 1,col, other);
		if(current == other && board_status[row + 1][col] != root)
			linkCellTo(row + 1, col, root);
	}
	if(col > 0){
		board.getCell(row,col - 1, other);
		if(current == other && board_status[row][col - 1] != root)
			linkCellTo(row, col - 1, root);
	}

	if(col + 1 < WIDTH){
		board.getCell(row,col + 1, other);
		if(current == other && board_status[row][col + 1] != root)
			linkCellTo(row, col + 1, root);
	}

	return S_OK;
}

void BoardEvaluator::printStatus(){
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				cout<<board_isCombo[i][j]<<" ";
			}
			cout<<endl;
		}

		cout<<"+++++++++++++++++++++++++++"<<endl;
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				cout<<setw(3)<<board_status[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"+++++++++++++++++++++++++++"<<endl;
		for(int i = 0; i < TYPE_NUM; i++)
			cout<<((perl_type)i)<<"-->"<<comboNum[i]<<" ";
		cout<<endl;
	}

double BoardEvaluator::getScore(){
	double score = 0;
	map<int, vector<int>>::iterator ite = combos.begin();
	while(ite != combos.end()){
		score += 1 + (ite->second.size() - 3) * 0.25;
		ite++;
	}
	return score;
}

void BoardEvaluator::printBoard(){
	this->mpBoard.printBoard();
}