#include "explosion.h"

void Explosion::Initialise(Vector2D pos, float size, float time, Vector2D vel = Vector2D(0,0))
{
	position = pos;
	animationSpeed = 8 / time;
	scale = size;
	velocity = vel;
	angle = (rand() % 628 / 100.0f);
	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");

	currentImage = 0;
	active = true;
}

void Explosion::Update(double gt)
{
	currentImage += gt * animationSpeed;
	if (currentImage >= 8)
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

IShape2D& Explosion::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}