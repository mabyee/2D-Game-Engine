#pragma once
#include "GameObject.h"

class Wall :public GameObject
{
private:
	Circle2D detectionRadius;
public:
	void Initialise(Vector2D pos, float ang);
	Rectangle2D collisionShape;
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	void Update(double gt);
	void HandleDetection(GameObject& other);
};

