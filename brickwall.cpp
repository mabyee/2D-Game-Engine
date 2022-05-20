/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "brickwall.h"
#include "bullet.h"

void BrickWall::Initialise(Vector2D pos, float ang)
{
	position = pos;
	active = true;
	LoadImg(L"Wall.bmp");
	scale = 3.0f;
	angle = ang;
	health = 100;
}

void BrickWall::Update(double gt)
{
	if (health <= 0)
	{
		Deactivate();
	}
}

IShape2D& BrickWall::GetShape()
{
	collisionShape.PlaceAt(position - Vector2D(44,44), position + Vector2D(44, 44));
	return collisionShape;
}

void BrickWall::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health = health - 5;
	}
}
IShape2D& BrickWall::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position,0);
	return detectionRadius;
}

void BrickWall::HandleDetection(GameObject& other)
{
}