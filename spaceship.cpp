#pragma once
#include "spaceship.h"
#include "myinputs.h"
#include "bullet.h"

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
void Spaceship::Update()
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
		velocity.setBearing(angle, 4.0f);
		pSE->Play(thrustLoop, true);
		position = position + velocity;
	}
	if ((!pInputs->KeyPressed(DIK_W)) && (!pInputs->KeyPressed(DIK_S)))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Stop(thrustLoop);
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		velocity.setBearing(angle, -4.0f);
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustLoop, true);
		position = position + velocity;
	}
	if (pInputs->NewKeyPressed(DIK_SPACE))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(shootSound);
		
		Bullet* pBullet = new Bullet();
		pBullet->Initialise(position, angle, 10.0f);
		if (pObjectManager)
		{
			pObjectManager->AddObject(pBullet);
		}
	}
}
