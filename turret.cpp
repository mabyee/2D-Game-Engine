/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "turret.h"
#include "soldier.h"
#include "bullet.h"

void Turret::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore)
{
	LoadImg(L"turret.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
	pScore = pCurrentScore;
	pSoundFX = sound;
	position = initialPos;
	cooldown = 0;
	health = 100;
	functional = true;
}
void Turret::Update(double gt)
{
	if (health <= 0)
	{
		cooldown = 1;
		functional = false;
	}
	else
	{
		angle = angle + 0.02;
		cooldown -= gt;
	}
}
IShape2D& Turret::GetShape()
{
	collisionShape.PlaceAt(position, 32);
	return collisionShape;
}
IShape2D& Turret::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 500);
	return detectionRadius;
}
void Turret::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health -= 10;
	}
}
void Turret::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		if (functional && active)
		{
			Vector2D soldierPos = other.GetPosition();
			float X = soldierPos.XValue;
			float Y = soldierPos.YValue;
			angle = -atan2(Y - position.YValue, X - position.XValue) + 1.57; //rotate the turret to the players current position

			if (cooldown <= 0)
			{
				Bullet* pBullet = new Bullet();//change bullet to something else to avoid counting score
				Vector2D gun;
				gun.setBearing(angle + 3.14f, -40.0f);
				gun = gun + position;
				pBullet->Initialise(gun, angle, 700.0f, pObjectManager);
				pObjectManager->AddObject(pBullet);
				pSoundFX->PlayShot();
				cooldown = 1.5;
			}
		}
	}
}