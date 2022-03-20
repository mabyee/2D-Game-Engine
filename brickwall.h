#pragma once
#include "wall.h"

class BrickWall: public Wall
{
private:
	int health;
public:
	void Initialise(Vector2D pos, float ang);
	void Update(double gt);
	void HandleCollision(GameObject& other);
};