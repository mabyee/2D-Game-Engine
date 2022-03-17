#include "enemy.h"
#include "bullet.h"
#include "spaceship.h"
#include "explosion.h"
#include "brickwall.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel, ObjectManager* pOM, SoundFX* sound)
{
	health = 50;
	position.set(initialPos);
	active = true;
	angle = 0;
	velocity = vel;
	scale = 3.0f;
	LoadImg(L"botboy.bmp");
	pObjectManager = pOM;
	pSoundFX = sound;
}

void Enemy::Update(double gt)
{
	if (health <= 0)
	{
		pSoundFX->PlayExplosion();
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 3.0f, 1.0f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);

		// If one dies, another spawns at a random location
		Enemy* pRock = new Enemy();			
		Vector2D pos;
		Vector2D vel;
		pos.setBearing(rand() % 628 / 100.0f, rand() % 400 + 600);
		vel.setBearing(rand() % 628 / 100.0f, rand() % 100 + 100);
		pRock->Initialise(pos, vel, pObjectManager, pSoundFX);
		pObjectManager->AddObject(pRock);
	}
	else
	{
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);
		position = position + velocity * gt;
		// checking if is in bounds (wraping around)
		if (position.XValue > screenWidth || position.XValue < -screenWidth)
		{
			position.XValue = position.XValue * -1;
		}
		if (position.YValue > screenHeight || position.YValue < -screenHeight)
		{
			position.YValue = position.YValue * -1;
		}
	}
	
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
		health = health - 10;
	}
	if (typeid(other) == typeid(Spaceship))
	{
		health = 0;
	}
	if (typeid(other) == typeid(Enemy))
	{
		health = 0;
	}
	if (typeid(other) == typeid(BrickWall))
	{
		health = 0;
	}
}