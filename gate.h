/*
Created by Henri Puennel, W19019002.
This file...
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

