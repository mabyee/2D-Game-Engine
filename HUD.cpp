/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "HUD.h"
#include "GameObject.h"

void HUD::Initialise(Soldier* pSol)
{
	HUDimage = MyDrawEngine::GetInstance()->LoadPicture(L"Images/HUD/HUD.png");
	scale = 2.0f;
	transparency = 0.2f;
	pSoldier = pSol;
}
//void HUD::Update(int score, int health, int ammo, int stingerAmmo, Soldier* pSol)

void HUD::Update(int score)
{
	ammo = pSoldier->GetAmmo();
	stingerAmmo = pSoldier->GetStingerAmmo();
	health = pSoldier->GetHealth();
	cardCount = pSoldier->GetCardCount();
	pos = MyDrawEngine::GetInstance()->GetViewport().GetCentre();
	screenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	screenHeight = MyDrawEngine::GetInstance()->GetScreenHeight();
	MyDrawEngine::GetInstance()->DrawAt(Vector2D(pos.XValue, pos.YValue-screenHeight/3.3f), HUDimage, scale, 0.0f, transparency);
	MyDrawEngine::GetInstance()->WriteText(screenWidth/2-60, 100, L"Score:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth/2, 100, score, MyDrawEngine::YELLOW); //Displaying Score
	MyDrawEngine::GetInstance()->WriteText(screenWidth/2-125, screenHeight - 40, L"Ammo:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth/2-50, screenHeight - 40, ammo, MyDrawEngine::WHITE); // ammo count in HUD
	MyDrawEngine::GetInstance()->WriteText(screenWidth/2, screenHeight - 40, L"Stingers:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth/2+75, screenHeight - 40, stingerAmmo, MyDrawEngine::WHITE); //stingerAmmo count in HUD
	MyDrawEngine::GetInstance()->WriteText(screenWidth/2 -125, screenHeight - 75, L"Health:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth/2 -50, screenHeight - 75, health, MyDrawEngine::WHITE); //health count in HUD
	MyDrawEngine::GetInstance()->WriteText(screenWidth / 2, screenHeight - 75, L"Key Cards:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth / 2 +100, screenHeight - 75, cardCount, MyDrawEngine::WHITE); //card count in HUD
}