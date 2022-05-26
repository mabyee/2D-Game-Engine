/*
Created by Henri Puennel, W19019002.
This file is a simple enemy which rotates and bounces of objects. Upon contact it explodes and deals damage.
*/
#include "enemy.h"
#include "bullet.h"
#include "soldier.h"
#include "explosion.h"
#include "brickwall.h"
#include "stinger.h"
#include "outerwall.h"
#include "KeyCard.h"

void Enemy::Initialise(Vector2D initialPos, Vector2D vel, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore)
{
	health = 50;
	position.set(initialPos);
	active = true;
	velocity = vel;
	scale = 1.5f;
	pObjectManager = pOM;
	pSoundFX = sound;
	pScore = pCurrentScore;

	//loading images of enemy
	move = AddAnimation();

	AddImage(move, L"Images/MiniRobot/robot0.png");
	AddImage(move, L"Images/MiniRobot/robot1.png");
	AddImage(move, L"Images/MiniRobot/robot2.png");
	AddImage(move, L"Images/MiniRobot/robot3.png");
	AddImage(move, L"Images/MiniRobot/robot4.png");
	AddImage(move, L"Images/MiniRobot/robot5.png");
	AddImage(move, L"Images/MiniRobot/robot6.png");
	AddImage(move, L"Images/MiniRobot/robot7.png");

	NextAnimation(move, move);
	SetAnimationSpeed(move, 8.0f);
	SetCurrentAnimation(move);
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
		//drop keycard on death
		KeyCard* pKeyCard = new KeyCard();
		pKeyCard->Initialise(position);
		pObjectManager->AddObject(pKeyCard);
	}
	else
	{
		position = position + velocity * gt;
		angle = angle + 2.0f * gt;
		SetCurrentAnimation(move);
		Animate(gt);
	}
}

void Enemy::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);

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
	}
	if (typeid(other) == typeid(Soldier))
	{
		health = 0;
		pScore->AddScore(50);
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
		velocity.XValue = -velocity.XValue;
		velocity.YValue = -velocity.YValue;
	}
}
void Enemy::HandleDetection(GameObject& other)
{

}