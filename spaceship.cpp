#pragma once
#include "spaceship.h"
#include "myinputs.h"
#include "bullet.h"
#include "enemy.h"

//Initialise Spaceship
void Spaceship::Initialise(Vector2D initialPos, ObjectManager* pOM)
{
	position.set(initialPos);
	velocity.set(0,0);
	LoadImg(L"ship.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	thrustLoop = pSE->LoadWav(L"thrustloop2.wav");
	shootSound = pSE->LoadWav(L"shoot.wav");
	pObjectManager = pOM;
}

//Update Spaceship
void Spaceship::Update(double gt)
{
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
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustLoop, true);

		acceleration.setBearing(angle, 300.0f);
		velocity = velocity + acceleration * gt;
	}

	if ((!pInputs->KeyPressed(DIK_W)) && (!pInputs->KeyPressed(DIK_S)))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Stop(thrustLoop);
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustLoop, true);
		
		acceleration.setBearing(angle, -300.0f);
		velocity = velocity + acceleration * gt;
	}
	velocity = velocity + friction * gt;
	friction = -0.5 * velocity;						// -2 for more friction, 0 to disable friction
	position = position + velocity * gt;

	if (pInputs->NewKeyPressed(DIK_SPACE))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		
		Bullet* pBullet = new Bullet();
		pBullet->Initialise(position, angle, 700.0f);
		if (pObjectManager)
		{
			pObjectManager->AddObject(pBullet);
			pSE->Play(shootSound);
		}
	}
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
		Deactivate();
	}
}