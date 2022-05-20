/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"
#include "AnimatedGameObject.h"

class Explosion : public AnimatedGameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	Circle2D detectionRadius;
	int explode;
	float timer;
public:
	void Initialise(Vector2D pos, float size, float time, Vector2D vel);
	void Update(double gt);
	void Render() override;
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
};