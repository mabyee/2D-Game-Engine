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

//Initialise Soldier
void Soldier::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore)
{
	animationSpeed = 8.0f;
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

	//loading images of soldier
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	soldierImages[0] = pDrawEngine->LoadPicture(L"walking0.png");
	soldierImages[1] = pDrawEngine->LoadPicture(L"walking1.png");
	soldierImages[2] = pDrawEngine->LoadPicture(L"walking2.png");
	soldierImages[3] = pDrawEngine->LoadPicture(L"walking3.png");
	soldierImages[4] = pDrawEngine->LoadPicture(L"walking4.png");
	soldierImages[5] = pDrawEngine->LoadPicture(L"walking5.png");
	soldierImages[6] = pDrawEngine->LoadPicture(L"walking6.png");
	soldierImages[7] = pDrawEngine->LoadPicture(L"walking7.png");

	currentImage = soldierImages[0];
}

//Update Soldier
void Soldier::Update(double gt)
{
	if (health <= 0)
	{
		Deactivate();
		// create new soldier and add blinking effect (respawn) TODO
	}

	// placing camera center at location of soldier
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
		if (currentImage >= 20)
		{
			currentImage = 14;
		}
		currentImage += gt * animationSpeed;
	}

	if ((!pInputs->KeyPressed(DIK_W)) && (!pInputs->KeyPressed(DIK_S)))
	{
		currentImage = 16; //sets idle position image
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		acceleration.setBearing(angle, -300.0f);
		velocity = velocity + acceleration * gt;
		//walking animation reversed
		if (currentImage <= 14)
		{
			currentImage = 20;
		}
		currentImage -= gt * animationSpeed;
	}
	velocity = velocity + friction * gt;
	friction = -6 * velocity;						// -2 for more friction, 0 to disable friction
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

	// checking if is in bounds (wraping around) add back incase of teleporter wall
	//if (position.XValue >= 1600 || position.XValue <= -1600)
	//{
	//	position.XValue = position.XValue * -1;
	//

	DamageBar.PlaceAt(position + Vector2D(-50.0f, 50.0f), position + Vector2D(50.0f, 65.0f));
	HealthBar.PlaceAt(position + Vector2D(-50.0f, 50.0f), position + Vector2D(-50.0f + health, 65.0f));
	MyDrawEngine::GetInstance()->FillRect(DamageBar, colourRed, 0.0f); //healthbar green area
	MyDrawEngine::GetInstance()->FillRect(HealthBar, colourGreen, 0.0f); //healthbar red area


}

void Soldier::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, currentImage, scale, angle, 0.0f);

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
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 1.5 * (velocity * normal) * normal;
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
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 1.5 * (velocity * normal) * normal;
		}
	}
	if (typeid(other) == typeid(Boss))
	{
		health = health - 0.1;
		MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
		pDrawEngine->theCamera.SetZoom(3.0f);
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