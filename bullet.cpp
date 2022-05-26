/*
Created by Henri Puennel, W19019002.
This file handels the creation and movement of bullets fired by other objects in the game.
*/
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "ObjectManager.h"
#include "brickwall.h"
#include "turret.h"
#include "outerwall.h"
#include "RoamingRobot.h"
#include "gate.h"

void Bullet::Initialise(Vector2D initialPos, float soldierAngle, float bulletSpeed, ObjectManager* pOM)
{
	position.set(initialPos);
	velocity.setBearing(soldierAngle, bulletSpeed);
	LoadImg(L"Images/Bullet/bullet.png");
	active = true;
	scale = 0.5f;
	timer = 5.0f;
	angle = soldierAngle;
	pObjectManager = pOM;
}

void Bullet::Update(double gt)
{
	position = position + velocity * gt;
	if (timer < 0.0f)						// delete bullet after timeout
	{
		active = false;
	}
	timer = timer - gt;
}

IShape2D& Bullet::GetShape()
{
	collisionShape.PlaceAt(position, 5);
	return collisionShape;
}
IShape2D& Bullet::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 1);
	return detectionRadius;
}

void Bullet::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Enemy))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 0.5f, 0.2f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
	if (typeid(other) == typeid(BrickWall))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 0.2f, 0.2f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
	if (typeid(other) == typeid(Turret))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 0.2f, 0.2f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
	if (typeid(other) == typeid(outerwall))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 0.2f, 0.2f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
	if (typeid(other) == typeid(RoamingRobot))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 0.2f, 0.2f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
	if (typeid(other) == typeid(gate))
	{
		Deactivate();
		Explosion* pExp = new Explosion();
		pExp->Initialise(position, 0.2f, 0.2f, Vector2D(0, 0));
		pObjectManager->AddObject(pExp);
	}
}
void Bullet::HandleDetection(GameObject& other)
{

}