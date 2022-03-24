#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Stinger :public GameObject
{
private:
	// stinger animation
	float animationSpeedStinger;
	float currentImageStinger;
	PictureIndex stingerImages[3];

	Circle2D collisionShape;
	Circle2D detectionRadius;
	ObjectManager* pObjectManager;
	int health;
public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM);
	void Update(double gt);
	void Render()override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};


