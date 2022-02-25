#pragma once
#include "GameObject.h"
#include "mysoundengine.h"
#include "mydrawengine.h"

class Spaceship:public GameObject
{
private:
	Vector2D velocity;
	SoundIndex shootSound;
	SoundIndex thrustLoop;

public:
	void Initialise(Vector2D initialPos);
	void Update();
};
