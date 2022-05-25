/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"

class outerwall :public GameObject
{
private:
	Rectangle2D collisionShape;
	Circle2D detectionRadius;
	int wallSide;
public:
	void Initialise(int side);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
	void HandleDetection(GameObject& other);
	IShape2D& GetDetectionRadius();
};