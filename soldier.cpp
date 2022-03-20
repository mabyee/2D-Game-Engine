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

//Initialise Soldier
void Soldier::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound)
{
	animationSpeed = 8.0f;
	health = 100;
	position.set(initialPos);
	velocity.set(0,0);
	LoadImg(L"ship.bmp");
	angle = 0.0f;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
	pSoundFX = sound;
	ammo = 30;
	stingerAmmo = 4;
	HealthBar.PlaceAt(0,0,20,10);
	colourRed = _XRGB(255, 0, 0);
	colourGreen = _XRGB(0, 255, 0);

	//loading images of soldier
	soldierImages[0] = MyDrawEngine::GetInstance()->LoadPicture(L"walking0.png");
	soldierImages[1] = MyDrawEngine::GetInstance()->LoadPicture(L"walking1.png");
	soldierImages[2] = MyDrawEngine::GetInstance()->LoadPicture(L"walking2.png");
	soldierImages[3] = MyDrawEngine::GetInstance()->LoadPicture(L"walking3.png");
	soldierImages[4] = MyDrawEngine::GetInstance()->LoadPicture(L"walking4.png");
	soldierImages[5] = MyDrawEngine::GetInstance()->LoadPicture(L"walking5.png");
	soldierImages[6] = MyDrawEngine::GetInstance()->LoadPicture(L"walking6.png");
	soldierImages[7] = MyDrawEngine::GetInstance()->LoadPicture(L"walking7.png");
	soldierImages[8] = MyDrawEngine::GetInstance()->LoadPicture(L"walking8.png");

	currentImage = soldierImages[0];
}

//Update Soldier
void Soldier::Update(double gt)
{
	if (health <= 0)
	{
		// loading sound
		pSoundFX->StopThrust();
		pSoundFX->PlayExplosion();
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 2.0f, 0.5f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
		// create new soldier and add blinking effect (respawn)
	}

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
		if (currentImage >= 18)
		{
			currentImage = 11;
		}
		currentImage += gt * animationSpeed;
	}

	if ((!pInputs->KeyPressed(DIK_W)) && (!pInputs->KeyPressed(DIK_S)))
	{
		currentImage = 15; //sets idle position image
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		acceleration.setBearing(angle, -300.0f);
		velocity = velocity + acceleration * gt;
		//walking animation reversed
		if (currentImage <= 12)
		{
			currentImage = 18;
		}
		currentImage -= gt * animationSpeed;
	}
	velocity = velocity + friction * gt;
	friction = -3 * velocity;						// -2 for more friction, 0 to disable friction
	position = position + velocity*2 * gt;

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
			Stinger* pStinger = new Stinger();
			pStinger->Initialise(position,pObjectManager);
			pObjectManager->AddObject(pStinger);
			// place object that does damage, costs 5 ammo, explodes on collision
			stingerAmmo = stingerAmmo - 1;
		}
	}

	
	// checking if is in bounds (wraping around)
	if (position.XValue >= 1600 || position.XValue <= -1600)
	{
		position.XValue = position.XValue * -1;
	}
	if (position.YValue >= 1000 || position.YValue <= -1000)
	{
		position.YValue = position.YValue * -1;
	}
	MyDrawEngine::GetInstance()->WriteInt(1900, 1400, ammo, MyDrawEngine::LIGHTRED); //ammo count in HUD
	MyDrawEngine::GetInstance()->WriteInt(1850, 1400, stingerAmmo, MyDrawEngine::LIGHTBLUE); //stinger ammo count in HUD

	DamageBar.PlaceAt(position+Vector2D(-50,50), position+Vector2D(50,65));
	HealthBar.PlaceAt(position + Vector2D(-50, 50), position + Vector2D(-50 + health, 65)); 
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
			velocity = velocity - 2* (velocity * normal) * normal;
		}
	}
	if (typeid(other) == typeid(ammoBox))
	{
		ammo = ammo + 20;
		stingerAmmo = stingerAmmo + 3;
	}
	if (typeid(other) == typeid(computer))
	{
		health = 100;
		pSoundFX->PlayChirp();
	}
}