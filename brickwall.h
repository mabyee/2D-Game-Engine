#pragma once
#include "GameObject.h"

class BrickWall: public GameObject
{
private:
	Rectangle2D collisionShape;
	int health;
public:
	void Initialise(Vector2D pos, float ang);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
};