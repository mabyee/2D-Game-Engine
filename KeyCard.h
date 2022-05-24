/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"

class KeyCard :public GameObject
{
private:
	Circle2D collisionShape;
	Circle2D detectionRadius;

public:
	void Initialise(Vector2D pos);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};

