#include "bullet.h"
#include "enemy.h"

void Bullet::Initialise(Vector2D initialPos, float shipAngle, float bulletSpeed)
{
	position.set(initialPos);
	velocity.setBearing(shipAngle, bulletSpeed);
	LoadImg(L"bullet.bmp");
	active = true;
	scale = 2.0f;
	timer = 3.0f;
	angle = shipAngle;
}

void Bullet::Update(double gt)
{
	position = position + velocity * gt;
	if (timer < 0.0f)						// delete bullet after timeout
	{
		active = false;
	}
	timer = timer - gt;
}

IShape2D& Bullet::GetShape()
{
	collisionShape.PlaceAt(position, 5);
	return collisionShape;
}

void Bullet::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Enemy))
	{
		Deactivate();
	}
}