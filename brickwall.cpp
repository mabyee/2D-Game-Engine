#include "brickwall.h"

void BrickWall::Initialise(Vector2D initialPos, Vector2D endPos, int r, int g, int b)
{
	rectangleStart = initialPos;
	rectangleEnd = endPos;
	active = true;
	rectangle.PlaceAt(rectangleStart, rectangleEnd);
	colour = _XRGB(r, g, b);
	MyDrawEngine::GetInstance()->FillRect(rectangle, colour); // draws for 1 second
}

void BrickWall::Update(double gt)
{
	MyDrawEngine::GetInstance()->FillRect(rectangle, colour); // doesnt work
}

void BrickWall::Render()
{
	MyDrawEngine::GetInstance()->FillRect(rectangle, colour); // doesnt work
}

IShape2D& BrickWall::GetShape()
{
	collisionShape.PlaceAt(rectangleStart,rectangleEnd);
	return collisionShape;
}

void BrickWall::HandleCollision(GameObject& other)
{

}