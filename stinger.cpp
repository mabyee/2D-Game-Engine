/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "stinger.h"
#include "enemy.h"
#include "boss.h"
#include "soldier.h"
#include "RoamingRobot.h"

void Stinger::Initialise(Vector2D initialPos, ObjectManager* pOM)
{
	position.set(initialPos);
	active = true;
	scale = 2.0f;

	//loading images of stinger
	blink = AddAnimation();

	AddImage(blink,L"Images/Stinger/stinger0.png");
	AddImage(blink, L"Images/Stinger/stinger1.png");
	AddImage(blink, L"Images/Stinger/stinger2.png");
	NextAnimation(blink, blink);
	SetAnimationSpeed(blink, 3.0f);
	SetCurrentAnimation(blink);
}

void Stinger::Update(double gt)
{
	SetCurrentAnimation(blink);
	Animate(gt);
}

void Stinger::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);
	}
}

IShape2D& Stinger::GetShape()
{
	collisionShape.PlaceAt(position, 24);
	return collisionShape;
}
IShape2D& Stinger::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 1);
	return detectionRadius;
}

void Stinger::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Enemy))
	{
		Deactivate();
	}
	if (typeid(other) == typeid(Boss))
	{
		Deactivate();
	}
	if (typeid(other) == typeid(RoamingRobot))
	{
		Deactivate();
	}
}
void Stinger::HandleDetection(GameObject& other)
{

}