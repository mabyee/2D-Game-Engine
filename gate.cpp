/*
Created by Henri Puennel, W19019002.
This file is the gate which the player enters to win the game. It is unlocked once 4 computers have been accessed.
*/
#include "gate.h"
#include "gamecode.h"

void gate::Initialise(Vector2D pos, Soldier* pSol)
{
	active = true;
	position = pos;
	scale = 0.7f;
	angle = 0.0f;
	pSoldier = pSol;
	hasWon = false;
	
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
	if (typeid(other) == typeid(Soldier) && hasWon == true)
	{
		Game::instance.ChangeState(Game::GameState::MENU); //win game if passing through door and timer ended
	}
}

void gate::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		int accessCount = pSoldier->GetAccessCount();
		if (accessCount >= 4) //only open if all computers accessed
		{
			static bool initialized; //only execute once
			if (!initialized) {
				initialized = true;
				SetCurrentAnimation(opening);
			}
			pDE->WriteText(other.GetPosition() + Vector2D(-80, 50), L"GAME OVER: YOU WON", MyDrawEngine::WHITE);
			timer += 0.1;
			if (timer >= 7) //set has won to true after some time has passed
			{
				hasWon = true;
			}
		}
		else
		{
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
