#pragma once
#include "Shapes.h"
#include "GameObject.h"

class BrickWall: public GameObject
{
private:

public:
	void Initialise();
	void Update();
	void makeWall(int brickStart, int brickEnd, int R, int G, int B, int brickAmount);
};