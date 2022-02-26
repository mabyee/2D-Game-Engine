#pragma once
#include "spaceship.h"
#include "myinputs.h"

//Initialise Spaceship
void Spaceship::Initialise(Vector2D initialPos)
{
	position.set(initialPos);
	velocity.set(0,0);
	LoadImg(L"botboy.bmp");
	angle = 0;
	active = true;
	scale = 3.0f;
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	thrustLoop = pSE->LoadWav(L"thrustloop2.wav");
	shootSound = pSE->LoadWav(L"shoot.wav");
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
	}
}
