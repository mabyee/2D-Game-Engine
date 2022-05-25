/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"
#include "wall.h"

class BrickWall: public Wall
{
private:
	int health;
public:
	void Initialise(Vector2D pos, float ang);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
};