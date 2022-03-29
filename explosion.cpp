/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "explosion.h"
#include "SoundFX.h"

void Explosion::Initialise(Vector2D pos, float size, float time, Vector2D vel = Vector2D(0,0))
{
	position = pos;
	animationSpeed = 8 / time;
	scale = size;
	velocity = vel;
	angle = (rand() % 628 / 100.0f);

	//loading images of explosion
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	images[0] = pDrawEngine->LoadPicture(L"explosion1.bmp");
	images[1] = pDrawEngine->LoadPicture(L"explosion2.bmp");
	images[2] = pDrawEngine->LoadPicture(L"explosion3.bmp");
	images[3] = pDrawEngine->LoadPicture(L"explosion4.bmp");
	images[4] = pDrawEngine->LoadPicture(L"explosion5.bmp");
	images[5] = pDrawEngine->LoadPicture(L"explosion6.bmp");
	images[6] = pDrawEngine->LoadPicture(L"explosion7.bmp");
	images[7] = pDrawEngine->LoadPicture(L"explosion8.bmp");

	currentImage = images[0];
	active = true;
}

void Explosion::Update(double gt)
{
	currentImage += gt * animationSpeed;
	if (currentImage >= 51)
	{
		Deactivate();
	}
	position = position + velocity * gt;
}

void Explosion::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, currentImage, scale, angle, 0.0f);
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