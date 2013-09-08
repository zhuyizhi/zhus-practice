#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "vector"
#include "BoardEvaluator.h"
#include "RandomPlayer.h"
using namespace std;


int main(){
	GameBoard gb;
	string file_name = "E:/input-2.txt";

	gb.read_file(file_name);
	gb.printBoard();
	
	EvaluateResult *evalute_result = BoardEvaluator::evaluate(&gb);
	evalute_result->printStatus();

	RandomPlayer player(&gb);
	player.playAndPrint();
	system("pause");
}