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

	AddImage(blink, L"screen0.png");
	AddImage(blink, L"screen1.png");
	AddImage(blink, L"screen2.png");
	AddImage(blink, L"screen3.png");
	AddImage(blink, L"screen4.png");
	AddImage(blink, L"screen5.png");
	AddImage(blink, L"screen6.png");
	AddImage(blink, L"screen7.png");
	AddImage(blink, L"screen8.png");
	AddImage(blink, L"screen9.png");
	AddImage(blink, L"screen10.png");
	AddImage(blink, L"screen11.png");
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