#include "string"
using namespace std;
const int WIDTH = 6;
const int HEIGHT = 5;
const int TYPE_NUM = 7;
enum perl_type{
	NOT_INITIALIZED,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	BLACK,
	HEART
};

enum ret_status{
	S_OK,
	E_FAIL
};

class GameBoard{
public:
	inline int setCell(int height, int width, perl_type type){
		if(height < 0 || height > HEIGHT || width < 0 || width > WIDTH)
			return E_FAIL;
		board[height][width] = type;
		return S_OK;
	}

	inline int getCell(int height, int width, perl_type& type ){
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

	int read_file(string file_name);

	void printBoard();

private:
	perl_type board[HEIGHT][WIDTH];
};

class Point2D{
public:
	int x;
	int y;
	Point2D(){x = -1; y = -1;}
	Point2D(int first, int second){x = first; y = second;}
};