#include "HUD.h"

void HUD::Initialise()
{
	active = true;
	colour = _XRGB(255, 10, 10);
	SizeX = Vector2D(-400, -850);
	SizeY = Vector2D(400, -1000);
	HUDShape.PlaceAt(SizeX, SizeY);
}

void HUD::Update(double gt)
{
}

void HUD::Render()
{
	MyDrawEngine::GetInstance()->FillRect(HUDShape, colour, 0.0f);
}

IShape2D& HUD::GetShape()
{
	collisionShape.PlaceAt(position, 0);
	return collisionShape;
}

void HUD::HandleCollision(GameObject& other)
{

}