#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	float animationSpeed;
	float currentImage;
	PictureIndex images[8];
public:
	void Initialise(Vector2D pos, float size, float time, Vector2D vel);
	void Update(float gt);
	void Render();
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
};

