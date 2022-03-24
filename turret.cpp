#include "turret.h"
#include "soldier.h"
#include "bullet.h"

void Turret::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Score* pCurrentScore)
{
	LoadImg(L"turret.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
	pScore = pCurrentScore;
	pSoundFX = sound;
	position = initialPos;
	cooldown = 0;
}
void Turret::Update(double gt)
{
	angle = angle + 0.02;
	cooldown -= gt;
}
IShape2D& Turret::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}
IShape2D& Turret::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 350);
	return detectionRadius;
}
void Turret::HandleCollision(GameObject& other)
{

}
void Turret::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		Vector2D soldierPos = other.GetPosition();
		float X = soldierPos.XValue;
		float Y = soldierPos.YValue;
		angle = -atan2(Y - position.YValue, X - position.XValue) + 1.57;

		if (cooldown <= 0)
		{
			Bullet* pBullet = new Bullet();
			Vector2D gun;
			gun.setBearing(angle + 3.14f, -20.0f);
			gun = gun + position;
			pBullet->Initialise(gun, angle, 700.0f, pObjectManager);
			pObjectManager->AddObject(pBullet);
			pSoundFX->PlayShot();
			cooldown = 1.5;
		}
	}
}