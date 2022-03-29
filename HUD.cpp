/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "HUD.h"
#include "GameObject.h"

//HUD::HUD()
//{
//}
//
//HUD::~HUD()
//{
//}

void HUD::Initialise()
{
	HUDimage = MyDrawEngine::GetInstance()->LoadPicture(L"HUD.png");
}

void HUD::Update(int score, int health, int ammo, int stingerAmmo)
{
	pos = MyDrawEngine::GetInstance()->GetViewport().GetCentre();
	screenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	screenHeight = MyDrawEngine::GetInstance()->GetScreenHeight();
	MyDrawEngine::GetInstance()->DrawAt(Vector2D(pos.XValue + 450, pos.YValue - 550), HUDimage, 8.0f, 0.0f, 0.2f); //incorporate ammo count here, remove from soldier class
	MyDrawEngine::GetInstance()->WriteText(screenWidth/2-60, 100, L"Score:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth/2, 100, score, MyDrawEngine::YELLOW); //Displaying Score
	MyDrawEngine::GetInstance()->WriteText(screenWidth-670, screenHeight - 40, L"Ammo:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteText(screenWidth-800, screenHeight - 40, L"Stingers:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth-720, screenHeight - 40, stingerAmmo, MyDrawEngine::WHITE); //ammo count in HUD
	MyDrawEngine::GetInstance()->WriteInt(screenWidth-600, screenHeight - 40, ammo, MyDrawEngine::WHITE); //stinger ammo count in HUD
	MyDrawEngine::GetInstance()->WriteText(screenWidth - 800, screenHeight - 75, L"Health:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(screenWidth - 720, screenHeight - 75, health, MyDrawEngine::WHITE); //ammo count in HUD
}