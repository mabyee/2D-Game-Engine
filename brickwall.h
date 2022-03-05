#pragma once
#include "GameObject.h"

class BrickWall: public GameObject
{
private:
	Rectangle2D rectangleTest;
	int colour;
	Vector2D bottomCorner;
	Vector2D topCorner;
public:
	void Initialise(Vector2D initialPos);
	void Update(double gt);
	void MakeWall();
};