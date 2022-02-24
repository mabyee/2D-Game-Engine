#pragma once
#include "spaceship.h"
#include "myinputs.h"

Spaceship::Spaceship()
{
};//constructor
Spaceship::~Spaceship()
{
};//destructor

//Initialise Spaceship
void Spaceship::Initialise(Vector2D initialPos)
{
	position.set(initialPos);
	velocity.set(0,0);
	LoadImg();
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	shootSound = pSE->LoadWav(L"shoot.wav");
	thrustLoop = pSE->LoadWav(L"thrustloop2.wav");
}

//Update Spaceship
void Spaceship::Update()
{
	if (status == true) //check if active
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, spaceshipPicture, 1.0f, angle, 0.0f);
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
		velocity.setBearing(angle, 4.0f);
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(this->thrustLoop, true);
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
		pSE->Play(this->thrustLoop, true);
		position = position + velocity;
	}
	if (pInputs->NewKeyPressed(DIK_SPACE))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(this->shootSound);
	}
}
