/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "boss.h"

void Boss::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos)
{
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
	move = AddAnimation();

	AddImage(move, L"cloud1.png");
	AddImage(move, L"cloud2.png");
	AddImage(move, L"cloud3.png");
	AddImage(move, L"cloud4.png");

	NextAnimation(move, move);
	SetAnimationSpeed(move, 6.0f);
	SetCurrentAnimation(move);
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

		SetCurrentAnimation(move);
		Animate(gt);
	}
}

void Boss::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.1f);

	}
}

IShape2D& Boss::GetShape()
{
	collisionShape.PlaceAt(position, scale*20); //collision scales with scale
	return collisionShape;
}
IShape2D& Boss::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 400); //collision scales with scale
	return detectionRadius;
}

void Boss::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		health = health + 0.1; //heals when damaging the player
		scale = scale + 0.02; //grows as he damages the player
	}
}
void Boss::HandleDetection(GameObject& other)
{

}