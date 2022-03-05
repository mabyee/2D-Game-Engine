#include "bullet.h"

void Bullet::Initialise(Vector2D initialPos, float shipAngle, float bulletSpeed)
{
	position.set(initialPos);
	velocity.setBearing(shipAngle, bulletSpeed);
	LoadImg(L"ship.bmp");
	active = true;
	scale = 0.2f;
}

void Bullet::Update()
{
	position = position + velocity;
}