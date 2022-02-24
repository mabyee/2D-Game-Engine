#pragma once
#include "GameObject.h"

class Spaceship:public GameObject
{
private:
	Vector2D velocity;
	Vector2D position;
	float angle;
	bool status;
	PictureIndex spaceshipPicture;
	SoundIndex shootSound;
	SoundIndex thrustLoop;

public:
	Spaceship(); //constructor
	~Spaceship(); //destructor

	void Initialise(Vector2D initialPos);
	void Update();
};
