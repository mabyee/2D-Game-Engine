#include "enemy.h"
#include "bullet.h"
#include "spaceship.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel)
{
	position.set(initialPos);
	active = true;
	angle = 0;
	velocity = vel;
	scale = 3.0f;
	LoadImg(L"botboy.bmp");
}

void Enemy::Update(double gt)
{
	position = position + velocity * gt;
}

IShape2D& Enemy::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}

void Enemy::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		Deactivate();
	}
	if (typeid(other) == typeid(Spaceship))
	{
		Deactivate();
	}
}