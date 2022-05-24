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
	missionMessage = L"Access all computers. A keycard may be required.";
}
//void HUD::Update(int score, int health, int ammo, int stingerAmmo, Soldier* pSol)

void HUD::Update(int score)
{
	//Collecting variable values from soldier
	ammo = pSoldier->GetAmmo();
	stingerAmmo = pSoldier->GetStingerAmmo();
	health = pSoldier->GetHealth();
	cardCount = pSoldier->GetCardCount();
	accessCount = pSoldier->GetAccessCount();
	//Collecting screen size information to adjust HUD
	pos = MyDrawEngine::GetInstance()->GetViewport().GetCentre();
	screenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	screenHeight = MyDrawEngine::GetInstance()->GetScreenHeight();
	//Pointer to MyDrawEngine for better readability
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	//------------- DRAWING HUD ---------------
	//Score HUD
	pDE->WriteText(screenWidth/2-60, 100, L"Score:", MyDrawEngine::WHITE);
	pDE->WriteInt(screenWidth/2, 100, score, MyDrawEngine::YELLOW); //Displaying Score
	//Player Stats HUD
	pDE->DrawAt(Vector2D(pos.XValue, pos.YValue - screenHeight / 3.3f), HUDimage, scale, 0.0f, transparency);
	pDE->WriteText(screenWidth/2-125, screenHeight - 40, L"Ammo:", MyDrawEngine::WHITE);
	pDE->WriteInt(screenWidth/2-50, screenHeight - 40, ammo, MyDrawEngine::WHITE); // ammo count in HUD
	pDE->WriteText(screenWidth/2, screenHeight - 40, L"Stingers:", MyDrawEngine::WHITE);
	pDE->WriteInt(screenWidth/2+75, screenHeight - 40, stingerAmmo, MyDrawEngine::WHITE); //stingerAmmo count in HUD
	pDE->WriteText(screenWidth/2 -125, screenHeight - 75, L"Health:", MyDrawEngine::WHITE);
	pDE->WriteInt(screenWidth/2 -50, screenHeight - 75, health, MyDrawEngine::WHITE); //health count in HUD
	pDE->WriteText(screenWidth / 2, screenHeight - 75, L"Key Cards:", MyDrawEngine::WHITE);
	pDE->WriteInt(screenWidth / 2 +100, screenHeight - 75, cardCount, MyDrawEngine::WHITE); //card count in HUD
	//Objective HUD
	//Update mission upon completion
	if (accessCount == 4)
	{
		pDE->WriteText(screenWidth / 2 - 62, 200, L"Find the Exit", MyDrawEngine::WHITE);
		pDE->WriteText(screenWidth / 2 - 55, 225, L"/4 accessed.", MyDrawEngine::YELLOW);
		pDE->WriteInt(screenWidth / 2 - 70, 225, accessCount, MyDrawEngine::YELLOW);
	}
	else
	{
		pDE->WriteText(screenWidth / 2 - 225, 200, L"Access all computers. A keycard may be required.", MyDrawEngine::WHITE);
		pDE->WriteText(screenWidth / 2 - 55, 225, L"/4 accessed.", MyDrawEngine::YELLOW);
		pDE->WriteInt(screenWidth / 2 - 70, 225, accessCount, MyDrawEngine::YELLOW);
	}
}