#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "vector"
#include "BoardEvaluator.h"
using namespace std;


int main(){
	GameBoard gb;
	string file_name = "E:/input-3.txt";

	gb.read_file(file_name);
	gb.printBoard();
	
	BoardEvaluator be(gb);
	be.initStatus();
	be.initIsCombo();
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	be.evaluate();
	be.printStatus();
	cout<<"score is "<<be.getScore()<<endl;
	system("pause");
}