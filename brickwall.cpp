#include "brickwall.h"

void BrickWall::Initialise(Vector2D initialPos, Vector2D endPos, int r, int g, int b)
{
	rectangleStart = initialPos;
	rectangleEnd = endPos;
	active = true;
	rectangle.PlaceAt(rectangleStart, rectangleEnd);
	colour = _XRGB(r, g, b);
}

void BrickWall::Update(double gt)
{
}

void BrickWall::Render()
{
	MyDrawEngine::GetInstance()->FillRect(rectangle, colour);
}

IShape2D& BrickWall::GetShape()
{
	collisionShape.PlaceAt(rectangleStart,rectangleEnd);
	return collisionShape;
}

void BrickWall::HandleCollision(GameObject& other)
{

}