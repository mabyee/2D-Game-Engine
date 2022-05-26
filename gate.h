/*
Created by Henri Puennel, W19019002.
This file is the gate which the player enters to win the game. It is unlocked once 4 computers have been accessed.
*/
#pragma once
#include "AnimatedGameObject.h"
#include "soldier.h"

class gate:public AnimatedGameObject
{
private:
	Rectangle2D collisionShape;
	Rectangle2D detectionRadius;
	int open, opening, closed;
	Soldier* pSoldier;
	double timer;
	bool hasWon;
public:
	void Initialise(Vector2D pos, Soldier* pSol);
	void Update(double gt);
	void Render() override;
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
};

