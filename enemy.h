#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
class Enemy : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	SoundFX* pSoundFX;
	int health;
public:
	void Initialise(Vector2D initialPos, Vector2D velocity, ObjectManager* pOM, SoundFX* sound);
	void Update(double gt);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};