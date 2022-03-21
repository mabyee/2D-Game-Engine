#include "score.h"

Score::Score()
{

}

Score::~Score()
{

}

void Score::Initialise()
{
	currentScore = 0;
}

void Score::AddScore(int newScore)
{
	currentScore = currentScore + newScore;
}

int Score::GetScore()
{
	return currentScore;
}

void Score::ResetScore()
{
	currentScore = 0;
}