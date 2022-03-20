#include "outerwall.h"

void outerwall::Initialise(Vector2D pos, float ang)
{
	position = pos;
	active = true;
	scale = 3.0f;
	angle = ang;
	LoadImg(L"outerWall.png");
}

void outerwall::HandleCollision(GameObject& other)
{

}

void outerwall::Update(double gt)
{

}