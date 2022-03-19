#pragma once
#include "spaceship.h"
#include "myinputs.h"
#include "bullet.h"
#include "enemy.h"
#include "gamecode.h"
#include "explosion.h"
#include "brickwall.h"
#include "ammoBox.h"

//Initialise Spaceship
void Spaceship::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound)
{
	//MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	//pDrawEngine->theCamera.PlaceAt(position);
	health = 100;
	position.set(initialPos);
	velocity.set(0,0);
	LoadImg(L"ship.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
	pSoundFX = sound;
	ammo = 20;
	HealthBar.PlaceAt(0,0,20,10);
	colourRed = _XRGB(255, 0, 0);
	colourGreen = _XRGB(0, 255, 0);
}

//Update Spaceship
void Spaceship::Update(double gt)
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
		// create new ship and add blinking effect (respawn)
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
		pSoundFX->StartThrust();
		acceleration.setBearing(angle, 300.0f);
		velocity = velocity + acceleration * gt;
		Explosion* pExp = new Explosion();
		Vector2D jet;
		jet.setBearing(angle + 3.14f, 16.0f);
		jet = jet + position;
		pExp->Initialise(jet, 0.4f, 0.5f, Vector2D(0,0));
		pObjectManager->AddObject(pExp);
	}

	if ((!pInputs->KeyPressed(DIK_W)) && (!pInputs->KeyPressed(DIK_S)))
	{
		pSoundFX->StopThrust();
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		pSoundFX->StartThrust();
		
		acceleration.setBearing(angle, -300.0f);
		velocity = velocity + acceleration * gt;
	}
	velocity = velocity + friction * gt;
	friction = -3 * velocity;						// -2 for more friction, 0 to disable friction
	position = position + velocity*2 * gt;

	if (pInputs->NewKeyPressed(DIK_SPACE))
	{		
		if (pObjectManager && ammo>0)
		{
			Bullet* pBullet = new Bullet();
			Vector2D gun;
			gun.setBearing(angle + 3.14f, -36.0f);
			gun = gun + position;
			pBullet->Initialise(gun, angle, 700.0f, pObjectManager);
			pObjectManager->AddObject(pBullet);
			pSoundFX->PlayShot();
			ammo = ammo - 1;
		}
	}
	// placing camera center at location of spaceship
	//MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	//pDrawEngine->theCamera.PlaceAt(position);
	
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
	DamageBar.PlaceAt(position+Vector2D(-50,50), position+Vector2D(50,65));
	HealthBar.PlaceAt(position + Vector2D(-50, 50), position + Vector2D(-50 + health, 65)); 
	MyDrawEngine::GetInstance()->FillRect(DamageBar, colourRed, 0.0f); //healthbar green area
	MyDrawEngine::GetInstance()->FillRect(HealthBar, colourGreen, 0.0f); //healthbar red area


}
IShape2D& Spaceship::GetShape()
{
	collisionShape.PlaceAt(position, 32);
	return collisionShape;
 }

void Spaceship::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Enemy))
	{
		health = health - 50;
		pSoundFX->StartAlarm();
	}
	if (typeid(other) == typeid(Bullet))
	{
		health = health - 10;
	}
	if (typeid(other) == typeid(BrickWall))
	{
		//effect on wall hit
	}
	if (typeid(other) == typeid(ammoBox))
	{
		ammo = ammo + 20;
		health = 100;
	}
}