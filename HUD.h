/*
Created by Henri Puennel, W19019002.
This file is the HUD and displays soldier and score information.
*/
#pragma once
#include "GameObject.h"
#include "soldier.h"

class HUD
{
private:
	PictureIndex HUDimage;
	Vector2D pos;
	int screenHeight;
	int screenWidth;
	float scale;
	float transparency;
	Soldier* pSoldier;
	int stingerAmmo, ammo, health, cardCount, accessCount;
	const wchar_t* missionMessage;

public:
	void Initialise(Soldier* pSol);
	void Update(int score);
	//HUD();
	//~HUD();
};

