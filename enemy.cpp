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
		position = position + velocity * gt;

		if (position.YValue > 1000 && velocity.YValue > 0)
		{
			velocity.YValue = -velocity.YValue;
		}
		if (position.YValue < -1000 && velocity.YValue < 0)
		{
			velocity.YValue = -velocity.YValue;
		}
		if (position.XValue > 1600 && velocity.XValue > 0)
		{
			velocity.XValue = -velocity.XValue;
		}
		if (position.XValue < -1600 && velocity.XValue < 0)
		{
			velocity.XValue = -velocity.XValue;
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
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
		}
	}
}