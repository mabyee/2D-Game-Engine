#pragma once
#include "GameObject.h"

class HUD
{
private:
	PictureIndex HUDimage;
	Vector2D pos;
public:
	void Initialise();
	void Update(int score);
	//HUD();
	//~HUD();
};

