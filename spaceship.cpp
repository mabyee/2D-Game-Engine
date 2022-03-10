#pragma once
#include "spaceship.h"
#include "myinputs.h"
#include "bullet.h"
#include "enemy.h"
#include "gamecode.h"
#include "explosion.h"

//Initialise Spaceship
void Spaceship::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound)
{
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	pDrawEngine->theCamera.PlaceAt(position);
	pDrawEngine->theCamera.SetZoom(0.8f);
	health = 100;
	position.set(initialPos);
	velocity.set(0,0);
	LoadImg(L"ship.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
	pSoundFX = sound;
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
		angle = angle - 0.05;
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		angle = angle + 0.05;
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
	friction = -0.5 * velocity;						// -2 for more friction, 0 to disable friction
	position = position + velocity * gt;

	if (pInputs->NewKeyPressed(DIK_SPACE))
	{		
		if (pObjectManager)
		{
			Bullet* pBullet = new Bullet();
			Vector2D gun;
			gun.setBearing(angle + 3.14f, -32.0f);
			gun = gun + position;
			pBullet->Initialise(gun, angle, 700.0f, pObjectManager);
			pObjectManager->AddObject(pBullet);
			pSoundFX->PlayShot();
		}
	}
	// placing camera center at location of spaceship
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	pDrawEngine->theCamera.PlaceAt(position);
	
	// checking if is in bounds (wraping around)
	//if (position.XValue >= 1500 || position.XValue <= -1500)
	//{
	//	position.XValue = position.XValue * -1;
	//}
	//if (position.YValue >= 1000 || position.YValue <= -1000)
	//{
	//	position.YValue = position.YValue * -1;
	//}
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
}