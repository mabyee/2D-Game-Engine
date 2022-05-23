/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "explosion.h"
#include "SoundFX.h"

void Explosion::Initialise(Vector2D pos, float size, float time, Vector2D vel = Vector2D(0,0))
{
	position = pos;
	scale = size;
	velocity = vel;
	angle = (rand() % 628 / 100.0f);
	active = true;

	//loading images of explosion
	explode = AddAnimation();

	AddImage(explode, L"Images/Explosion/explosion1.bmp");
	AddImage(explode, L"Images/Explosion/explosion2.bmp");
	AddImage(explode, L"Images/Explosion/explosion3.bmp");
	AddImage(explode, L"Images/Explosion/explosion4.bmp");
	AddImage(explode, L"Images/Explosion/explosion5.bmp");
	AddImage(explode, L"Images/Explosion/explosion6.bmp");
	AddImage(explode, L"Images/Explosion/explosion7.bmp");
	AddImage(explode, L"Images/Explosion/explosion8.bmp");

	NextAnimation(explode, explode);
	SetAnimationSpeed(explode, 10.0f);
	SetCurrentAnimation(explode);
}

void Explosion::Update(double gt)
{
	timer += gt;
	SetCurrentAnimation(explode);
	Animate(gt);
	if (timer >= 0.7f)
	{
		Deactivate();
		timer = 0.0f;
	}
}

void Explosion::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);
	}
}

void Explosion::HandleCollision(GameObject& other)
{

}
void Explosion::HandleDetection(GameObject& other)
{

}

IShape2D& Explosion::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}
IShape2D& Explosion::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 1);
	return detectionRadius;
}