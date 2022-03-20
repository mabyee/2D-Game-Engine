#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"

class Boss:public GameObject
{
private:
	// boss walking animation
	float animationSpeed;
	float currentImage;
	PictureIndex enemyImages[8];

	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	SoundFX* pSoundFX;
	int health;
public:
	void Initialise(Vector2D initialPos, Vector2D velocity, ObjectManager* pOM, SoundFX* sound);
	void Update(double gt);
	void Render()override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

