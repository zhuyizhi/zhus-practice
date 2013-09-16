#include "Scorer.h"


double Scorer::simpleScore(EvaluateResult *evalute_result){
	double  score = 0;
	for(int i = 0; i < TYPE_NUM; i++)
		score += evalute_result->comboNum[i];
	return score;
}