/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"

class HUD
{
private:
	PictureIndex HUDimage;
	Vector2D pos;
	int screenHeight;
	int screenWidth;
public:
	void Initialise();
	void Update(int score, int health, int ammo, int stingerAmmo);
	//HUD();
	//~HUD();
};

