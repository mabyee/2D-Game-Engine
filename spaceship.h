#pragma once
#include "GameObject.h"
#include "mysoundengine.h"
#include "mydrawengine.h"
#include "ObjectManager.h"

class Spaceship:public GameObject
{
private:
	Vector2D velocity;
	SoundIndex shootSound;
	SoundIndex thrustLoop;
	ObjectManager* pObjectManager;

public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM);
	void Update();
};
