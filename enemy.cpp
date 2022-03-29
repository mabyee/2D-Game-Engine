/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "enemy.h"
#include "bullet.h"
#include "soldier.h"
#include "explosion.h"
#include "brickwall.h"
#include "stinger.h"
#include "outerwall.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore)
{
	animationSpeed = 5.0f;
	health = 50;
	position.set(initialPos);
	active = true;
	velocity = vel;
	scale = 1.5f;
	pObjectManager = pOM;
	pSoundFX = sound;
	pScore = pCurrentScore;

	//loading images of enemy
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	enemyImages[0] = pDrawEngine->LoadPicture(L"robot0.png");
	enemyImages[1] = pDrawEngine->LoadPicture(L"robot1.png");
	enemyImages[2] = pDrawEngine->LoadPicture(L"robot2.png");
	enemyImages[3] = pDrawEngine->LoadPicture(L"robot3.png");
	enemyImages[4] = pDrawEngine->LoadPicture(L"robot4.png");
	enemyImages[5] = pDrawEngine->LoadPicture(L"robot5.png");
	enemyImages[6] = pDrawEngine->LoadPicture(L"robot6.png");
	enemyImages[7] = pDrawEngine->LoadPicture(L"robot7.png");

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
		if (currentImage >= 12)
		{
			currentImage = 5;
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
IShape2D& Enemy::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 350);
	return detectionRadius;
}

void Enemy::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health -= 10;
		int score = 5;
		pScore->AddScore(score);
	}
	if (typeid(other) == typeid(Soldier))
	{
		health = 0;
		int score = 50;
		pScore->AddScore(score);
	}
	if (typeid(other) == typeid(Enemy))
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
		}
	}
	if (typeid(other) == typeid(BrickWall))
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
		}
	}
	if (typeid(other) == typeid(Stinger))
	{
		health = 0;
		int score = 150;
		pScore->AddScore(score);
	}

	if (typeid(other) == typeid(outerwall))
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
		}
	}
}
void Enemy::HandleDetection(GameObject& other)
{

}