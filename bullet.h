#pragma once
#include "GameObject.h"

class Bullet:public GameObject
{
private:
	Vector2D velocity;
	SoundIndex impactSound;
	float timer;
public:
	void Initialise(Vector2D initialPos, float angle, float bulletSpeed);
	void Update(double gt);
};
