#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
class Spaceship:public GameObject
{
private:
	int health;
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D friction;
	SoundIndex shootSound;
	SoundIndex thrustLoop;
	SoundFX* pSoundFX;
	ObjectManager* pObjectManager; // Pointer to objectmanager required when an object creates another object
	Circle2D collisionShape;
public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound);
	void Update(double gt);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};
