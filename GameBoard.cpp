//#include "GameBoard.h"
#include "iostream"
#include "string"
#include "sstream"
#include "vector"
#include "BoardEvaluator.h"

GameBoard::GameBoard(const GameBoard& anotherBoard){
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			board[i][j] = anotherBoard.board[i][j];
}

int GameBoard::read_file(std::string file_name){
	std::ifstream infile;
	infile.open(file_name.c_str());
	std::string line, word;
	if(infile){
		int row_num = 0;
		while(getline(infile, line)){
			if(row_num >= HEIGHT)
				return E_FAIL;

			int start = 0, place = 0;
			std::vector<std::string> words;
			while(start < line.length() && (place = line.find_first_of(',', start)) > 0){
				words.push_back(line.substr(start, place - start));
				start = place + 1;
			}
			if(start < line.length())
				words.push_back(line.substr(start));
			if(words.size() != WIDTH)
				return E_FAIL;
			int val;
			for(int i = 0; i < WIDTH; i++){
				std::stringstream ss(words[i]);
				ss >> val;
				board[row_num][i] = (perl_type)val;
			}
			row_num++;
		}
	}
	infile.close();
	return S_OK;
}

void GameBoard::printBoard(){
	using namespace std;
	cout<<"This is what the game board looks like:"<<endl;
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
}