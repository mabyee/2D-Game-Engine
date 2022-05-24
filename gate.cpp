/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "gate.h"


void gate::Initialise(Vector2D pos, Soldier* pSol)
{
	active = true;
	position = pos;
	scale = 0.7f;
	angle = 0.0f;
	pSoldier = pSol;
	
	closed = AddAnimation();
	AddImage(closed, L"Images/Gate/gateClosed.png");

	open = AddAnimation();
	AddImage(open, L"Images/Gate/gateOpen.png");

	opening = AddAnimation();
	AddImage(opening, L"Images/Gate/gate0.png");
	AddImage(opening, L"Images/Gate/gate1.png");
	AddImage(opening, L"Images/Gate/gate2.png");
	AddImage(opening, L"Images/Gate/gate3.png");
	AddImage(opening, L"Images/Gate/gate4.png");
	AddImage(opening, L"Images/Gate/gate5.png");
	AddImage(opening, L"Images/Gate/gate6.png");
	AddImage(opening, L"Images/Gate/gate7.png");
	AddImage(opening, L"Images/Gate/gate8.png");
	AddImage(opening, L"Images/Gate/gate9.png");
	AddImage(opening, L"Images/Gate/gate10.png");
	AddImage(opening, L"Images/Gate/gate11.png");
	NextAnimation(opening, open);
	SetAnimationSpeed(opening, 9.0f);

	SetCurrentAnimation(closed);
}

void gate::Update(double gt)
{
	Animate(gt);
}

void gate::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);
	}
}

void gate::HandleCollision(GameObject& other)
{
	
}

void gate::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		int accessCount = pSoldier->GetAccessCount();
		if (accessCount == 4) //only open if all computers accessed
		{
			static bool initialized; //only execute once
			if (!initialized) {
				initialized = true;
				SetCurrentAnimation(opening);
			} 
			// TODO: GAME OVER
		}
		else
		{
			MyDrawEngine* pDE = MyDrawEngine::GetInstance();
			pDE->WriteText(position + Vector2D(-170, 50), L"ACCESS DENIED: You haven't accessed every computer", MyDrawEngine::WHITE);
		}
	}
}

IShape2D& gate::GetShape()
{
	collisionShape.PlaceAt(position - Vector2D(44, 44), position + Vector2D(44, 44));
	return collisionShape;
}
IShape2D& gate::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position - Vector2D(150, 150), position + Vector2D(150, 150));
	return detectionRadius;
}
