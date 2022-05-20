/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
class Score
{
private:
	
	int currentScore;
public:
	void Initialise();
	void AddScore(int newScore);
	int GetScore();
	void ResetScore();
	Score();
	~Score();
	
};

