/*
Created by Henri Puennel, W19019002.
This is the keycard which is dropped by enemies and the roaming robot. It is a consumable, needed to access computers.
*/
#pragma once
#include "GameObject.h"

class KeyCard :public GameObject
{
private:
	Circle2D collisionShape;
	Circle2D detectionRadius;

public:
	void Initialise(Vector2D pos);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};

