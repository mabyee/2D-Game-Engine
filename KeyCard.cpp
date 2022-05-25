/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "KeyCard.h"
#include "soldier.h"

void KeyCard::Initialise(Vector2D pos)
{
	position.set(pos);
	int selection = rand() % 4;
	switch (selection) //randomly load one of 4 keycard images
	{
	case 0:
		LoadImg(L"Images/KeyCard/keyCard0.png");
		break;
	case 1:
		LoadImg(L"Images/KeyCard/keyCard1.png");
		break;
	case 2:
		LoadImg(L"Images/KeyCard/keyCard2.png");
		break;
	case 3:
		LoadImg(L"Images/KeyCard/keyCard3.png");
		break;
	}
	angle = 0;
	active = true;
	scale = 1.0f;
}
void KeyCard::Update(double gt)
{

}

IShape2D& KeyCard::GetShape()
{
	collisionShape.PlaceAt(position, 8);
	return collisionShape;
}
IShape2D& KeyCard::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 1);
	return detectionRadius;
}

void KeyCard::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		Deactivate();
	}
}
void KeyCard::HandleDetection(GameObject& other)
{

}
