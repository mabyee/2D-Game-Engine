#pragma once
#include "GameObject.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;
public:
	void Initialise(Vector2D initialPos);
	void Update();
};