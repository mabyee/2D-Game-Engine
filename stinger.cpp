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
	stingerImages[0] = MyDrawEngine::GetInstance()->LoadPicture(L"stinger0.png");
	stingerImages[1] = MyDrawEngine::GetInstance()->LoadPicture(L"stinger1.png");
	stingerImages[2] = MyDrawEngine::GetInstance()->LoadPicture(L"stinger2.png");

	currentImageStinger = stingerImages[0];
}

void Stinger::Update(double gt)
{
	if (currentImageStinger >= 37)
	{
		currentImageStinger = 35;
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