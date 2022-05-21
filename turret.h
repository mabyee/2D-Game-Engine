/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"
#include "SoundFX.h"
#include "score.h"
#include "AnimatedGameObject.h"
#include "ObjectManager.h"

class Turret:public AnimatedGameObject
{
private:
	PictureIndex image;
	Vector2D velocity;
	Circle2D detectionRadius;
	Circle2D collisionShape;
	float health;
	SoundFX* pSoundFX;
	Score* pScore;
	ObjectManager* pObjectManager;
	float cooldown;
	bool functional;
	int working, broken;
public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore);
	void Update(double gt);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
};

