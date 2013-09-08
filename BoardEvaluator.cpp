#include "BoardEvaluator.h"

using namespace std;

EvaluateResult *BoardEvaluator::evaluate(GameBoard* ipBoard){
	int iteRound = -1;
	bool haveCombo;
	GameBoard lBoard(*ipBoard);
	EvaluateResult *evaluate_result = new EvaluateResult();

	//while has combo, do elimination
	do{
		haveCombo = false;
		iteRound++;
		int board_status[HEIGHT][WIDTH];
		bool board_isCombo[HEIGHT][WIDTH];
		memset(board_status, 0, sizeof(int)* HEIGHT * WIDTH);
		memset(board_isCombo, false, sizeof(bool) * HEIGHT * WIDTH);

		//1. init board status. Set orb's neighbor to orb's unique id if they
		//have same color. Result stored in board_status.
		connectCells(lBoard, board_status);

		//2. init isCombo. If an orb is part of a combo, then set corresponding cell
		//in board_isCombo true.
		evaluateIsCombo(lBoard, board_isCombo);

		//3. construct combos and comboNum using board_status and board_isCombo.
		//combos stores orb id for each combo. comboNum stores combo number for each color.
		map<int, vector<int>> tempMap;
		int round_base = iteRound * WIDTH * HEIGHT;
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				if(board_isCombo[i][j]){
					haveCombo = true;
					int root = board_status[i][j] + round_base;
					int current = i * WIDTH + j + 1 + round_base;
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
			int row = (root - 1 - round_base) / WIDTH;
			int col = (root - 1 - round_base) % WIDTH;
			perl_type type;
			lBoard.getCell(row, col, type);
			evaluate_result->comboNum[static_cast<int>(type)]++;
			evaluate_result->combos.insert(*ite);
			ite++;
		}

		

		// 4. adjust the board by setting eliminated orbs on lBoard to NOT_INITIALIZED.
		adjustBoard(lBoard, board_isCombo);
	}while(haveCombo);


	return evaluate_result;
}

int BoardEvaluator::evaluateIsCombo(GameBoard& board, bool board_isCombo[HEIGHT][WIDTH]){
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

int BoardEvaluator::linkCellTo(int row, int col, int root, GameBoard& board, int board_status[HEIGHT][WIDTH]){
	perl_type current;
	board.getCell(row, col, current);//currently don't check return value
	if(current == NOT_INITIALIZED)
		return S_OK;
	board_status[row][col] = root;
	perl_type other = NOT_INITIALIZED;
	if(row > 0){
		board.getCell(row - 1,col, other);
		if(current == other && board_status[row - 1][col] != root)
			linkCellTo(row - 1, col, root, board, board_status);
	}
	if(row + 1 < HEIGHT){
		board.getCell(row + 1,col, other);
		if(current == other && board_status[row + 1][col] != root)
			linkCellTo(row + 1, col, root, board, board_status);
	}
	if(col > 0){
		board.getCell(row,col - 1, other);
		if(current == other && board_status[row][col - 1] != root)
			linkCellTo(row, col - 1, root, board, board_status);
	}

	if(col + 1 < WIDTH){
		board.getCell(row,col + 1, other);
		if(current == other && board_status[row][col + 1] != root)
			linkCellTo(row, col + 1, root, board, board_status);
	}

	return S_OK;
}

int BoardEvaluator::connectCells(GameBoard& board, int board_status[HEIGHT][WIDTH]){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			if(board_status[i][j] == NOT_INITIALIZED){
				int element_id = i * WIDTH + j + 1;//unique element id;
				linkCellTo(i, j,  element_id, board, board_status);
			}
		}
	}
	return S_OK;
}

int BoardEvaluator::adjustBoard(GameBoard& board, bool board_isCombo[HEIGHT][WIDTH]){
	for(int j = 0; j < WIDTH; j++){
		for(int i = HEIGHT -1, newHeight = i; i >= 0; i--){
			if(!board_isCombo[i][j]){
				if(i != newHeight){
					perl_type cType;
					board.getCell(i, j, cType);
					board.setCell(newHeight, j, cType);
					board.setCell(i, j, NOT_INITIALIZED);
				}
				newHeight--;
			}else{
				board.setCell(i, j, NOT_INITIALIZED);
			}
		}
	}

	return S_OK;
}