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

void HUD::Update(int score)
{
	pos = MyDrawEngine::GetInstance()->GetViewport().GetCentre();
	MyDrawEngine::GetInstance()->DrawAt(Vector2D(pos.XValue + 450, pos.YValue - 500), HUDimage, 8.0f, 0.0f, 0.5f); //incorporate ammo count here, remove from soldier class
	MyDrawEngine::GetInstance()->WriteText(1020, 100, L"Score:", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(1100, 100, score, MyDrawEngine::YELLOW); //Displaying Score
}