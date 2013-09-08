#include "iostream"

#include "RandomPlayer.h"


RandomPlayer::RandomPlayer(GameBoard* ib){
	this->board = ib;
}

int RandomPlayer::move(int& height, int& width, const direction dir){
	int hOffset = height;
	int wOffset = width;

	switch(dir){
	case LEFT:
		--wOffset;
		break;
	case RIGHT:
		++wOffset;
		break;
	case UP:
		--hOffset;
		break;
	case DOWN:
		++hOffset;
	}

	if(!(validHeight(hOffset) && validWidth(wOffset)))
		return E_FAIL;
	int ret = board->swap(wOffset, hOffset, width, height);
	height = hOffset;
	width = wOffset;
	return ret;
}

int RandomPlayer::playAndPrint(){
	srand(static_cast<unsigned>(time(0)));
	int width = rand() % WIDTH;
	int height = rand() % HEIGHT;
	
	int max_step = 50;
	int step = 0;
	double max_score = -1;
	int max_at_step = -1;
	std::vector<direction> steps;

	while(step < max_step){
		direction dir = static_cast<direction>(rand() % 4);
		int status = move(height, width, dir);
		if(status == S_OK){// it's possible that the randomly choosed direction is invalid.
			steps.push_back(dir);
			EvaluateResult *evaluate_result = BoardEvaluator::evaluate(board);
			double score = simpleScore(evaluate_result);
			if(score > max_score){
				max_score = score;
				max_at_step = step; 
			}
			step++;
		}

	}

	std::cout<<"best combo number = "<<max_score<<std::endl
		<<"Starts at orb ("<<width<<","<<height<<")"<<std::endl
		<<"Path is :"<<std::endl;

	std::vector<direction>::iterator ite = steps.begin();
	while(ite != steps.end()){
		std::cout<<*ite<<std::endl;
		ite++;
	}
	
	std::cout<<"+++++++++++++++++++++++++++++++"<<std::endl;

	this->board->printBoard();
	return S_OK;
}
