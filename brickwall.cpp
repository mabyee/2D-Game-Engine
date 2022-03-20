#include "brickwall.h"
#include "bullet.h"

void BrickWall::Initialise(Vector2D pos, float ang)
{
	position = pos;
	active = true;
	scale = 3.0f;
	angle = ang;
	LoadImg(L"Wall.bmp");
	health = 100;
}

void BrickWall::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health = health - 5;
	}
}

void BrickWall::Update(double gt)
{
	if (health <= 0)
	{
		Deactivate();
	}
}