#include "HUD.h"
HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Initialise()
{
	colour = _XRGB(255, 100, 10);
	SizeX = Vector2D(-400, -850);
	SizeY = Vector2D(400, -1000);
	HUDShape.PlaceAt(SizeX, SizeY);
}

void HUD::Update(double gt)
{
	MyDrawEngine::GetInstance()->FillRect(HUDShape, colour, 0.0f);
}