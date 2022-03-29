/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"

class BrickWall: public GameObject
{
private:
	Rectangle2D collisionShape;
	Circle2D detectionRadius;
	int health;
public:
	void Initialise(Vector2D pos, float ang);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
	void HandleDetection(GameObject& other);
	IShape2D& GetDetectionRadius();
};