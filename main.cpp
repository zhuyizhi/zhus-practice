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
	
	BoardEvaluator be(gb);
	be.initStatus();
	be.initIsCombo();
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	be.evaluate();
	be.printStatus();
	be.evaluate();
	cout<<"score is "<<be.getScore()<<endl;
	
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	RandomPlayer pr(&be, &gb);
	pr.playAndPrint();
	

	system("pause");
}