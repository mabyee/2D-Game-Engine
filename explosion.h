#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	Circle2D detectionRadius;
	float animationSpeed;
	float currentImage;
	PictureIndex images[8];
public:
	void Initialise(Vector2D pos, float size, float time, Vector2D vel);
	void Update(double gt);
	void Render() override;
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
};

