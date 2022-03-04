#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	Vector2D velocity;
public:
	void Initialise(Vector2D initialPos);
	void Update();
};