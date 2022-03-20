#pragma once
#include "GameObject.h"

class Wall :public GameObject
{
private:
public:
	void Initialise(Vector2D pos, float ang);
	Rectangle2D collisionShape;
	IShape2D& GetShape();
	void Update(double gt);
};

