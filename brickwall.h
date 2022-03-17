#pragma once
#include "GameObject.h"

class BrickWall: public GameObject
{
private:
	Circle2D collisionShape;
public:
	void Initialise(Vector2D initialPos);
	void Update(double gt);
	void Render();
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
};