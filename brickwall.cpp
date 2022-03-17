#include "brickwall.h"

void BrickWall::Initialise(Vector2D initialPos)
{
	position = initialPos;
	active = true;
	LoadImg(L"Wall.bmp");
	scale = 5.0f;
	angle = 1;
}

void BrickWall::Update(double gt)
{
}

IShape2D& BrickWall::GetShape()
{
	collisionShape.PlaceAt(position, 32);
	return collisionShape;
}

void BrickWall::HandleCollision(GameObject& other)
{

}