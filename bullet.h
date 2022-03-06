#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Bullet:public GameObject
{
private:
	Vector2D velocity;
	SoundIndex impactSound;
	float timer;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
public:
	void Initialise(Vector2D initialPos, float angle, float bulletSpeed, ObjectManager* pOM);
	void Update(double gt);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};
