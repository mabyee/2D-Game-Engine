#include "brickwall.h"

void BrickWall::Initialise(Vector2D pos, float ang)
{
	position = pos;
	active = true;
	LoadImg(L"Wall.bmp");
	scale = 1.5f;
	angle = ang;
}

void BrickWall::Update(double gt)
{
}

IShape2D& BrickWall::GetShape()
{
	collisionShape.PlaceAt(position - Vector2D(22, 22), position + Vector2D(22, 22));
	return collisionShape;
}

void BrickWall::HandleCollision(GameObject& other)
{

}