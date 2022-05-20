/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"

class computer : public GameObject
{
private:
	Vector2D velocity;
	Rectangle2D collisionShape;
	Circle2D detectionRadius;
	float animationSpeed;
	float currentImage;
	PictureIndex computerImages[12];
public:
	void Initialise(Vector2D pos, float size, float time);
	void Update(double gt);
	void Render() override;
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
	void HandleDetection(GameObject& other);
	IShape2D& GetDetectionRadius();
};

