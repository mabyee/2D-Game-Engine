#include "computer.h"
#include "soldier.h"

void computer::Initialise(Vector2D pos, float size, float time)
{
	position = pos;
	animationSpeed = 8 / time;
	scale = size;
	angle = 0.0f;

	//loading images of computer
	MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
	computerImages[0] = pDrawEngine->LoadPicture(L"screen0.png");
	computerImages[1] = pDrawEngine->LoadPicture(L"screen1.png");
	computerImages[2] = pDrawEngine->LoadPicture(L"screen2.png");
	computerImages[3] = pDrawEngine->LoadPicture(L"screen3.png");
	computerImages[4] = pDrawEngine->LoadPicture(L"screen4.png");
	computerImages[5] = pDrawEngine->LoadPicture(L"screen5.png");
	computerImages[6] = pDrawEngine->LoadPicture(L"screen6.png");
	computerImages[7] = pDrawEngine->LoadPicture(L"screen7.png");
	computerImages[8] = pDrawEngine->LoadPicture(L"screen8.png");
	computerImages[9] = pDrawEngine->LoadPicture(L"screen9.png");
	computerImages[10] = pDrawEngine->LoadPicture(L"screen10.png");
	computerImages[11] = pDrawEngine->LoadPicture(L"screen11.png");


	currentImage = computerImages[0];
	active = true;
}

void computer::Update(double gt)
{
	currentImage += gt * animationSpeed;
	if (currentImage >= 30)
	{
		currentImage = 41;
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
	if (typeid(other) == typeid(Soldier))
	{
		Deactivate();
	}
}
void computer::HandleDetection(GameObject& other)
{
}

IShape2D& computer::GetShape()
{
	collisionShape.PlaceAt(position-Vector2D(30,15), position+Vector2D(30,15));
	return collisionShape;
}
IShape2D& computer::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position,1);
	return detectionRadius;
}