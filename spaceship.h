#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"

class Spaceship
{
private:
	Vector2D velocity;
	Vector2D position;
	float direction;
	bool status;
	PictureIndex spaceshipPicture;
	SoundIndex shootSound;
	SoundIndex thrustLoop;

public:
	Spaceship(); //constructor
	~Spaceship(); //destructor

	void Initialise(Vector2D initialPos);
	void Render();
	void Update();
};
