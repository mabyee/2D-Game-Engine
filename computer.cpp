#include "computer.h"

void computer::Initialise(Vector2D pos, float size, float time, Vector2D vel = Vector2D(0, 0))
{
	position = pos;
	animationSpeed = 8 / time;
	scale = size;
	velocity = vel;
	angle = 0.0f;
	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"screen0.png");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"screen1.png");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"screen2.png");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"screen3.png");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"screen4.png");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"screen5.png");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"screen6.png");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"screen7.png");


	currentImage = images[0];
	active = true;
}

void computer::Update(double gt)
{
	currentImage += gt * animationSpeed;
	if (currentImage >= 8)
	{
		currentImage = 0;
	}
	position = position + velocity * gt;
}

void computer::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, currentImage, scale, angle, 0.0f);
	}
}

void computer::HandleCollision(GameObject& other)
{

}

IShape2D& computer::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}