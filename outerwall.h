#pragma once
#include "wall.h"

class outerwall :public Wall
{
private:

public:
	void Initialise(Vector2D pos, float ang);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
};