/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "soldier.h"
#include "myinputs.h"
#include "bullet.h"
#include "enemy.h"
#include "gamecode.h"
#include "explosion.h"
#include "brickwall.h"
#include "ammoBox.h"
#include "computer.h"
#include "stinger.h"
#include "outerwall.h"
#include "boss.h"
#include "RoamingRobot.h"


//Initialise Soldier
void Soldier::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore)
{
	health = 100;
	position.set(initialPos);
	velocity.set(0,0);
	angle = 0.0f;
	active = true;
	scale = 1.0f;
	pScore = pCurrentScore;
	pObjectManager = pOM;
	pSoundFX = sound;
	ammo = 30;
	stingerAmmo = 4;
	HealthBar.PlaceAt(0,0,20,10);
	colourRed = _XRGB(255, 0, 0);
	colourGreen = _XRGB(0, 255, 0);

	//new animation engine
	walk = AddAnimation();
	AddImage(walk, L"Images/Soldier/walking0.png");
	AddImage(walk, L"Images/Soldier/walking1.png");
	AddImage(walk, L"Images/Soldier/walking2.png");
	AddImage(walk, L"Images/Soldier/walking3.png");
	AddImage(walk, L"Images/Soldier/walking4.png");
	AddImage(walk, L"Images/Soldier/walking5.png");
	AddImage(walk, L"Images/Soldier/walking6.png");
	AddImage(walk, L"Images/Soldier/walking7.png");
	NextAnimation(walk, walk);
	SetAnimationSpeed(walk, 9.0f);
	SetCurrentAnimation(walk);
	
	idle = AddAnimation();
	AddImage(idle, L"Images/Soldier/walking4.png");
}

//Update Soldier
void Soldier::Update(double gt)
{
	gameTime = gt; //keep a local gametime
	if (health <= 0)
	{
		Deactivate();
		// create new soldier and add blinking effect (respawn) TODO

	}

	// placing camera center at location of soldier and zooming in slightly
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	pDrawEngine->theCamera.PlaceAt(Vector2D(position.XValue, -position.YValue));
	pDrawEngine->theCamera.SetZoom(1.3f);

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (pInputs->KeyPressed(DIK_A))
	{
		angle = angle - 0.05 * gt * 50;
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		angle = angle + 0.05 * gt * 50;
	}
	if (pInputs->KeyPressed(DIK_W))
	{
		acceleration.setBearing(angle, 300.0f);
		velocity = velocity + acceleration * gt;
		//walking animation
		SetCurrentAnimation(walk);
	}

	if ((!pInputs->KeyPressed(DIK_W)) && (!pInputs->KeyPressed(DIK_S)))
	{
		//idle animation
		SetCurrentAnimation(idle);
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		acceleration.setBearing(angle, -300.0f);
		velocity = velocity + acceleration * gt;
		//walking animation
		SetCurrentAnimation(walk);

	}
	velocity = velocity + friction * gt;
	friction = -6 * velocity; // -10 for more friction, 0 to disable friction
	position = position + velocity*3 * gt;

	if (pInputs->NewKeyPressed(DIK_SPACE)) // shoot
	{		
		if (pObjectManager && ammo>0)
		{
			Bullet* pBullet = new Bullet();
			Vector2D gun;
			gun.setBearing(angle + 3.14f, -20.0f);
			gun = gun + position;
			pBullet->Initialise(gun, angle, 700.0f, pObjectManager);
			pObjectManager->AddObject(pBullet);
			pSoundFX->PlayShot();
			ammo = ammo - 1;
		}
	}

	if (pInputs->NewKeyPressed(DIK_E)) // place stinger
	{
		if (pObjectManager && stingerAmmo >= 1)
		{
			pSoundFX->PlayStingerDrop();
			Stinger* pStinger = new Stinger();
			pStinger->Initialise(position,pObjectManager);
			pObjectManager->AddObject(pStinger);
			// place object that does damage, costs 5 ammo, explodes on collision
			stingerAmmo = stingerAmmo - 1;
		}
	}

	DamageBar.PlaceAt(position + Vector2D(-50.0f, 50.0f), position + Vector2D(50.0f, 65.0f));
	HealthBar.PlaceAt(position + Vector2D(-50.0f, 50.0f), position + Vector2D(-50.0f + health, 65.0f));
	MyDrawEngine::GetInstance()->FillRect(DamageBar, colourRed, 0.0f); //healthbar green area
	MyDrawEngine::GetInstance()->FillRect(HealthBar, colourGreen, 0.0f); //healthbar red area

	Animate(gt);
}

void Soldier::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);

	}
}

IShape2D& Soldier::GetShape()
{
	collisionShape.PlaceAt(position, 26);
	return collisionShape;
 }
IShape2D& Soldier::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 1);
	return detectionRadius;
}

void Soldier::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Enemy))
	{
		health = health - 50;
	}
	if (typeid(other) == typeid(Bullet))
	{
		health = health - 10;
	}
	if (typeid(other) == typeid(BrickWall))
	{
		float otherPosX = other.GetPosition().XValue; //reduce number of calls
		float otherPosY = other.GetPosition().YValue;
		float playerSize = 26.0f;
		float wallSize = 110.0f; //wallSize value gained by tweaking and testing
		MyDrawEngine* draw = MyDrawEngine::GetInstance();
		draw->WriteText(other.GetPosition(), L"Wall Here", MyDrawEngine::WHITE);

		if (position.XValue > otherPosX && position.YValue + wallSize / 2.0f > otherPosY
			&& position.YValue - wallSize / 2.0f < otherPosY)
		{
			position.XValue = otherPosX + (playerSize + wallSize) / 2.0f;
		}
		if (position.XValue < otherPosX && position.YValue - wallSize / 2.0f < otherPosY
			&& position.YValue + wallSize / 2.0f > otherPosY)
		{
			position.XValue = otherPosX - (playerSize + wallSize) / 2.0f;
		}
		if (position.YValue > otherPosY && position.XValue + wallSize / 2 > otherPosX
			&& position.XValue - wallSize / 2.0f < otherPosX)
		{
			position.YValue = otherPosY + (playerSize + wallSize) / 2.0f;
		}
		if (position.YValue < otherPosY && position.XValue - wallSize / 2.0f < otherPosX
			&& position.XValue + wallSize / 2.0f > otherPosX)
		{
			position.YValue = otherPosY - (playerSize + wallSize) / 2.0f;
		}
	}
	
	if (typeid(other) == typeid(ammoBox))
	{
		pSoundFX->PlayHealthPickup();
		ammo = ammo + 20;
		stingerAmmo = stingerAmmo + 3;
	}
	if (typeid(other) == typeid(computer))
	{
		health = 100;
		pSoundFX->PlayChirp();
		int score = 10;
		pScore->AddScore(score);
	}
	if (typeid(other) == typeid(outerwall))
	{
		float otherPosX = other.GetPosition().XValue; //reduce number of calls
		float otherPosY = other.GetPosition().YValue;
		float playerSize = 26.0f;
		float wallSize = 102.0f;
		MyDrawEngine* draw = MyDrawEngine::GetInstance();
		draw->WriteText(other.GetPosition(), L"Wall Here", MyDrawEngine::WHITE);

		if (position.XValue > otherPosX && position.YValue + wallSize / 2.0f > otherPosY
			&& position.YValue - wallSize / 2.0f < otherPosY)
		{
			position.XValue = otherPosX + (playerSize + wallSize) / 2.0f;
		}
		if (position.XValue < otherPosX && position.YValue - wallSize / 2.0f < otherPosY
			&& position.YValue + wallSize / 2.0f > otherPosY)
		{
			position.XValue = otherPosX - (playerSize + wallSize) / 2.0f;
		}
		if (position.YValue > otherPosY && position.XValue + wallSize / 2 > otherPosX
			&& position.XValue - wallSize / 2.0f < otherPosX)
		{
			position.YValue = otherPosY + (playerSize + wallSize) / 2.0f;
		}
		if (position.YValue < otherPosY && position.XValue - wallSize / 2.0f < otherPosX
			&& position.XValue + wallSize / 2.0f > otherPosX)
		{
			position.YValue = otherPosY - (playerSize + wallSize) / 2.0f;
		}
	}
	if (typeid(other) == typeid(Boss))
	{
		health = health - 0.1;
		MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
		pDrawEngine->theCamera.SetZoom(3.0f);
	}
	if (typeid(other) == typeid(RoamingRobot))
	{
		
		timer += gameTime; //start count
		if (timer >= 1.0f)
		{
			//health = health - 20;
			timer = 0.0f; //reset timer
		}
		
	}
}

void Soldier::HandleDetection(GameObject& other)
{

}

int Soldier::GetAmmo()
{
	return ammo;
}

int Soldier::GetStingerAmmo()
{
	return stingerAmmo;
}

int Soldier::GetHealth()
{
	return health;
}

void Soldier::DealDamage(int damageAmount)
{
	health -= damageAmount;
}