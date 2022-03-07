#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Enemy : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	int health;
public:
	void Initialise(Vector2D initialPos, Vector2D velocity, ObjectManager* pOM);
	void Update(double gt);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};