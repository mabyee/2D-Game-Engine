/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "soldier.h"
#include "AnimatedGameObject.h"

class Boss:public AnimatedGameObject
{
private:
	int move;
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

