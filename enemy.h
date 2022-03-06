#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
public:
	void Initialise(Vector2D initialPos, Vector2D velocity);
	void Update(double gt);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};