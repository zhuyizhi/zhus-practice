#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include "string"
#include "fstream"

#include "Enums.h"

class GameBoard{
public:
	
	explicit GameBoard(const GameBoard&);
	GameBoard& operator=(const GameBoard&);
	inline int setCell(int height, int width, perl_type type){
		if(height < 0 || height > HEIGHT || width < 0 || width > WIDTH)
			return E_FAIL;
		board[height][width] = type;
		return S_OK;
	}
	inline int getCell(int height, int width, perl_type& type ) const {
		if(height < 0 || height > HEIGHT || width < 0 || width > WIDTH)
			return E_FAIL;
		type = board[height][width];
		return S_OK;
	}

	inline void clear_board(){
		for(int i = 0; i < HEIGHT; i++)
			for(int j = 0; j < WIDTH; j++)
				board[i][j] = NOT_INITIALIZED;
	}

	int read_file(std::string file_name);

	inline int swap(int w1, int h1, int w2, int h2){
		perl_type t1 = board[h1][w1];
		board[h1][w1] = board[h2][w2];
		board[h2][w2] = t1;

		return S_OK;
	}

	void printBoard();

private:
	perl_type board[HEIGHT][WIDTH];
};
#endif//GAME_BOARD_H_