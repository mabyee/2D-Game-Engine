#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "soldier.h"

class Boss:public GameObject
{
private:
	// boss moving animation
	float animationSpeed;
	float currentImage;
	PictureIndex bossImages[8];

	float speed;
	Circle2D collisionShape;
	Circle2D detectionRadius;
	ObjectManager* pObjectManager;
	SoundFX* pSoundFX;
	int health;
	Soldier* pSoldier;
public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos);
	void Update(double gt);
	void Render()override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};

