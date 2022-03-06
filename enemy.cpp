#include "enemy.h"
#include "bullet.h"
#include "spaceship.h"
#include "explosion.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel, ObjectManager* pOM)
{
	position.set(initialPos);
	active = true;
	angle = 0;
	velocity = vel;
	scale = 3.0f;
	LoadImg(L"botboy.bmp");
	pObjectManager = pOM;
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
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 3.0f, 1.0f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
	if (typeid(other) == typeid(Spaceship))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 3.0f, 1.0f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
}