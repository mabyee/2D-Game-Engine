#include "enemy.h"
#include "bullet.h"
#include "soldier.h"
#include "explosion.h"
#include "brickwall.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel, ObjectManager* pOM, SoundFX* sound)
{
	animationSpeed = 5.0f;
	health = 50;
	position.set(initialPos);
	active = true;
	angle =  position.XValue-3.14f;
	velocity = vel;
	scale = 1.5f;
	pObjectManager = pOM;
	pSoundFX = sound;

	//loading images of enemy
	enemyImages[0] = MyDrawEngine::GetInstance()->LoadPicture(L"robot0.png");
	enemyImages[1] = MyDrawEngine::GetInstance()->LoadPicture(L"robot1.png");
	enemyImages[2] = MyDrawEngine::GetInstance()->LoadPicture(L"robot2.png");
	enemyImages[3] = MyDrawEngine::GetInstance()->LoadPicture(L"robot3.png");
	enemyImages[4] = MyDrawEngine::GetInstance()->LoadPicture(L"robot4.png");
	enemyImages[5] = MyDrawEngine::GetInstance()->LoadPicture(L"robot5.png");
	enemyImages[6] = MyDrawEngine::GetInstance()->LoadPicture(L"robot6.png");
	enemyImages[7] = MyDrawEngine::GetInstance()->LoadPicture(L"robot7.png");

	currentImage = enemyImages[0];
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
	}
	else
	{
		position = position + velocity * gt;
		angle = angle + 2.0f * gt;
		if (currentImage >= 9)
		{
			currentImage = 2;
		}
		currentImage += gt * animationSpeed;

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

void Enemy::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, currentImage, scale, angle, 0.0f);

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
	if (typeid(other) == typeid(Soldier))
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