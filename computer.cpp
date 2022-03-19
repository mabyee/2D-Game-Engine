#include "computer.h"
#include "spaceship.h"

void computer::Initialise(Vector2D pos, float size, float time)
{
	position = pos;
	animationSpeed = 8 / time;
	scale = size;
	angle = 0.0f;
	computerImages[0] = MyDrawEngine::GetInstance()->LoadPicture(L"screen0.png");
	computerImages[1] = MyDrawEngine::GetInstance()->LoadPicture(L"screen1.png");
	computerImages[2] = MyDrawEngine::GetInstance()->LoadPicture(L"screen2.png");
	computerImages[3] = MyDrawEngine::GetInstance()->LoadPicture(L"screen3.png");
	computerImages[4] = MyDrawEngine::GetInstance()->LoadPicture(L"screen4.png");
	computerImages[5] = MyDrawEngine::GetInstance()->LoadPicture(L"screen5.png");
	computerImages[6] = MyDrawEngine::GetInstance()->LoadPicture(L"screen6.png");
	computerImages[7] = MyDrawEngine::GetInstance()->LoadPicture(L"screen7.png");
	computerImages[8] = MyDrawEngine::GetInstance()->LoadPicture(L"screen8.png");
	computerImages[9] = MyDrawEngine::GetInstance()->LoadPicture(L"screen9.png");
	computerImages[10] = MyDrawEngine::GetInstance()->LoadPicture(L"screen10.png");
	computerImages[11] = MyDrawEngine::GetInstance()->LoadPicture(L"screen11.png");


	currentImage = computerImages[0];
	active = true;
}

void computer::Update(double gt)
{
	currentImage += gt * animationSpeed;
	if (currentImage >= 15)
	{
		currentImage = 5;
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
	if (typeid(other) == typeid(Spaceship))
	{
		Deactivate();
	}
}

IShape2D& computer::GetShape()
{
	collisionShape.PlaceAt(position-Vector2D(30,15), position+Vector2D(30,15));
	return collisionShape;
}