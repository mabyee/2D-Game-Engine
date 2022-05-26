/*
Created by Henri Puennel, W19019002.
This file is an ammo box which can be picked up to restore some ammo to the player.
*/
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class ammoBox:public GameObject
{
private:
	Circle2D collisionShape;
	Circle2D detectionRadius;
	ObjectManager* pObjectManager;
public:
	void Initialise(Vector2D pos, ObjectManager* pOM);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};

