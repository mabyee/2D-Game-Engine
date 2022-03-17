#pragma once
#include "GameObject.h"

class BrickWall: public GameObject
{
private:
	Rectangle2D rectangle;
	int colour;
	Rectangle2D collisionShape;
	Vector2D rectangleStart;
	Vector2D rectangleEnd;
public:
	void Initialise(Vector2D initialPos, Vector2D endPos, int r, int g, int b);
	void Update(double gt);
	void Render() override;
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
};