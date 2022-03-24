#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "score.h"

class Enemy : public GameObject
{
private:
	// enemy walking animation
	float animationSpeed;
	float currentImage;
	PictureIndex enemyImages[8];

	Vector2D velocity;
	Circle2D collisionShape;
	Circle2D detectionRadius;
	ObjectManager* pObjectManager;
	SoundFX* pSoundFX;
	int health;
	Score* pScore;
public:
	void Initialise(Vector2D initialPos, Vector2D velocity, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore);
	void Update(double gt);
	void Render()override;
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
	void HandleCollision(GameObject& other);
};