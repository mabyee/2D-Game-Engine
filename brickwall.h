/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"

class BrickWall: public GameObject
{
private:
	int health;
public:
	void Initialise(Vector2D pos, float ang);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
	Rectangle2D collisionShape;
	Circle2D detectionRadius;
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
};