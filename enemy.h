/*
Created by Henri Puennel, W19019002.
This file is a simple enemy which rotates and bounces of objects. Upon contact it explodes and deals damage.
*/
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "score.h"
#include "AnimatedGameObject.h"

class Enemy : public AnimatedGameObject
{
private:
	int move;
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