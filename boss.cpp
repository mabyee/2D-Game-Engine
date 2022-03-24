#include "boss.h"
#include <math.h>


void Boss::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos)
{
	animationSpeed = 6.0f;
	health = 500;
	position.set(initialPos);
	speed = 3.0f;
	angle = 0.0f;
	active = true;
	scale = 4.0f;
	pObjectManager = pOM;
	pSoundFX = sound;
	pSoldier = solPos;
	//loading images of boss
	bossImages[0] = MyDrawEngine::GetInstance()->LoadPicture(L"puff1.bmp");
	bossImages[1] = MyDrawEngine::GetInstance()->LoadPicture(L"puff2.bmp");
	bossImages[2] = MyDrawEngine::GetInstance()->LoadPicture(L"puff3.bmp");
	bossImages[3] = MyDrawEngine::GetInstance()->LoadPicture(L"puff4.bmp");
	bossImages[4] = MyDrawEngine::GetInstance()->LoadPicture(L"puff5.bmp");
	bossImages[5] = MyDrawEngine::GetInstance()->LoadPicture(L"puff6.bmp");
	bossImages[6] = MyDrawEngine::GetInstance()->LoadPicture(L"puff7.bmp");
	bossImages[7] = MyDrawEngine::GetInstance()->LoadPicture(L"puff8.bmp");

	currentImage = bossImages[0];
}

void Boss::Update(double gt)
{
	if (active)
	{
		Vector2D soldierPos = pSoldier->GetPosition();
		float dirX = soldierPos.XValue - position.XValue;
		float dirY = soldierPos.YValue - position.YValue;
		float hyp = sqrt(dirX * dirX + dirY * dirY);
		dirX /= hyp;
		dirY /= hyp;
		position.XValue += dirX * speed;
		position.YValue += dirY * speed;

		if (currentImage >= 27)
		{
			currentImage = 20;
		}
		currentImage += gt * animationSpeed;
	}
}

void Boss::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, currentImage, scale, angle, 0.1f);

	}
}

IShape2D& Boss::GetShape()
{
	collisionShape.PlaceAt(position, scale*20); //collision scales with scale
	return collisionShape;
}

void Boss::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		health = health + 0.1; //heals when damaging the player
		scale = scale + 0.02; //grows as he damages the player
	}
}