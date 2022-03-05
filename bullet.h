#pragma once
#include "GameObject.h"

class Bullet:public GameObject
{
private:
	Vector2D velocity;
	SoundIndex impactSound;
public:
	void Initialise(Vector2D initialPos, float angle, float bulletSpeed);
	void Update();
};
