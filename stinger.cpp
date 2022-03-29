/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "stinger.h"
#include "enemy.h"
#include "boss.h"
#include "soldier.h"

void Stinger::Initialise(Vector2D initialPos, ObjectManager* pOM)
{
	animationSpeedStinger = 3.0f;
	position.set(initialPos);
	active = true;
	scale = 2.0f;

	//loading images of stinger
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	stingerImages[0] = pDrawEngine->LoadPicture(L"stinger0.png");
	stingerImages[1] = pDrawEngine->LoadPicture(L"stinger1.png");
	stingerImages[2] = pDrawEngine->LoadPicture(L"stinger2.png");

	currentImageStinger = stingerImages[0];
}

void Stinger::Update(double gt)
{
	if (currentImageStinger >= 42)
	{
		currentImageStinger = 44;
	}
	currentImageStinger += gt * animationSpeedStinger;
}

void Stinger::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, currentImageStinger, scale, angle, 0.0f);

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
}
void Stinger::HandleDetection(GameObject& other)
{

}