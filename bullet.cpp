#include "bullet.h"

void Bullet::Initialise(Vector2D initialPos, float shipAngle, float bulletSpeed)
{
	position.set(initialPos);
	velocity.setBearing(shipAngle, bulletSpeed);
	LoadImg(L"ship.bmp");
	active = true;
	scale = 0.2f;
	timer = 2.0f;
}

void Bullet::Update(double gt)
{
	position = position + velocity * gt;
	if (timer < 0.0f)
	{
		active = false;
	}
	timer = timer - gt;
}