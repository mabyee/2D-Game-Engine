/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "computer.h"
#include "soldier.h"

void computer::Initialise(Vector2D pos, float size)
{
	position = pos;
	scale = size;
	angle = 0.0f;
	active = true;

	//loading images of computer
	on = AddAnimation();
	AddImage(on, L"Images/Screen/screen0.png");
	AddImage(on, L"Images/Screen/screen1.png");
	AddImage(on, L"Images/Screen/screen2.png");
	AddImage(on, L"Images/Screen/screen3.png");
	AddImage(on, L"Images/Screen/screen4.png");
	AddImage(on, L"Images/Screen/screen5.png");
	AddImage(on, L"Images/Screen/screen6.png");
	AddImage(on, L"Images/Screen/screen7.png");
	AddImage(on, L"Images/Screen/screen8.png");
	AddImage(on, L"Images/Screen/screen9.png");
	AddImage(on, L"Images/Screen/screen10.png");
	AddImage(on, L"Images/Screen/screen11.png");
	NextAnimation(on, on);
	SetAnimationSpeed(on, 9.0f);
	SetCurrentAnimation(on);

	off = AddAnimation();
	AddImage(off, L"Images/Screen/screenOff.png");
	NextAnimation(off, off);
	SetAnimationSpeed(off, 1.0f);
}

void computer::Update(double gt)
{
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
		MyDrawEngine* pDE =  MyDrawEngine::GetInstance();
		pDE->WriteText(position+Vector2D(-75,50), L"Press F to use Keycard", MyDrawEngine::WHITE);
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