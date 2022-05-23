/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "computer.h"
#include "soldier.h"

void computer::Initialise(Vector2D pos, float size, float time)
{
	position = pos;
	scale = size;
	angle = 0.0f;
	active = true;

	//loading images of computer
	blink = AddAnimation();

	AddImage(blink, L"Images/Screen/screen0.png");
	AddImage(blink, L"Images/Screen/screen1.png");
	AddImage(blink, L"Images/Screen/screen2.png");
	AddImage(blink, L"Images/Screen/screen3.png");
	AddImage(blink, L"Images/Screen/screen4.png");
	AddImage(blink, L"Images/Screen/screen5.png");
	AddImage(blink, L"Images/Screen/screen6.png");
	AddImage(blink, L"Images/Screen/screen7.png");
	AddImage(blink, L"Images/Screen/screen8.png");
	AddImage(blink, L"Images/Screen/screen9.png");
	AddImage(blink, L"Images/Screen/screen10.png");
	AddImage(blink, L"Images/Screen/screen11.png");
	NextAnimation(blink, blink);
	SetAnimationSpeed(blink, 9.0f);
	SetCurrentAnimation(blink);
	
}

void computer::Update(double gt)
{
	SetCurrentAnimation(blink);
	Animate(gt);
}

void computer::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);
	}
}

void computer::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		Deactivate();
	}
}
void computer::HandleDetection(GameObject& other)
{
}

IShape2D& computer::GetShape()
{
	collisionShape.PlaceAt(position-Vector2D(30,15), position+Vector2D(30,15));
	return collisionShape;
}
IShape2D& computer::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position,1);
	return detectionRadius;
}