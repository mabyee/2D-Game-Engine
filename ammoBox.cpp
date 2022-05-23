/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "ammoBox.h"
#include "soldier.h"

void ammoBox::Initialise(Vector2D pos, ObjectManager* pOM)
{
	position.set(pos);
	LoadImg(L"Images/Crate/crate.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
}
void ammoBox::Update(double gt)
{

}

IShape2D& ammoBox::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}
IShape2D& ammoBox::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 1);
	return detectionRadius;
}

void ammoBox::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		Deactivate();
	}
}
void ammoBox::HandleDetection(GameObject& other)
{

}
