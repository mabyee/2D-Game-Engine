#include "enemy.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel)
{
	position.set(initialPos);
	active = true;
	angle = 0;
	velocity = vel;
	scale = 3.0f;
	LoadImg(L"botboy.bmp");
}

void Enemy::Update()
{
	position = position + velocity;
}