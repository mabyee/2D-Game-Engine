#pragma once
#include "GameObject.h"
#include "mysoundengine.h"
#include "mydrawengine.h"
#include "ObjectManager.h"

class Spaceship:public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D friction;
	SoundIndex shootSound;
	SoundIndex thrustLoop;
	ObjectManager* pObjectManager;
	Circle2D collisionShape;
public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM);
	void Update(double gt);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};
