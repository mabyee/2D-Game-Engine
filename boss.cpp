#include "boss.h"

void Boss::Initialise(Vector2D initialPos, Vector2D velocity, ObjectManager* pOM, SoundFX* sound)
{

}

void Boss::Update(double gt)
{

}

void Boss::Render()
{

}

IShape2D& Boss::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}

void Boss::HandleCollision(GameObject& other)
{

}