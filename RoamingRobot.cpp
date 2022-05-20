#include "RoamingRobot.h"
void RoamingRobot::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos)
{
	health = 150;
	position.set(initialPos);
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
	pSoundFX = sound;
	pSoldier = solPos;

	//adding images for different animation states
	run = AddAnimation();
	AddImage(run, L"boss-run0.png");
	AddImage(run, L"boss-run1.png");
	AddImage(run, L"boss-run2.png");
	AddImage(run, L"boss-run3.png");
	AddImage(run, L"boss-run4.png");
	AddImage(run, L"boss-run5.png");
	AddImage(run, L"boss-run6.png");
	AddImage(run, L"boss-run7.png");
	AddImage(run, L"boss-run8.png");

	NextAnimation(run, run);
	SetAnimationSpeed(run, 6.0f);

	idle = AddAnimation();
	AddImage(idle, L"boss-idle0.png");
	AddImage(idle, L"boss-idle1.png");
	AddImage(idle, L"boss-idle2.png");
	AddImage(idle, L"boss-idle3.png");
	NextAnimation(idle, idle);
	SetAnimationSpeed(idle, 6.0f);

	shoot = AddAnimation();
	AddImage(shoot, L"boss-shoot0.png");
	AddImage(shoot, L"boss-shoot1.png");
	AddImage(shoot, L"boss-shoot2.png");
	AddImage(shoot, L"boss-shoot3.png");
	AddImage(shoot, L"boss-shoot4.png");
	AddImage(shoot, L"boss-shoot5.png");
	AddImage(shoot, L"boss-shoot6.png");
	AddImage(shoot, L"boss-shoot7.png");
	NextAnimation(shoot, shoot);
	SetAnimationSpeed(shoot, 6.0f);

	death = AddAnimation();
	AddImage(death, L"boss-death0.png");
	AddImage(death, L"boss-death1.png");
	AddImage(death, L"boss-death2.png");
	AddImage(death, L"boss-death3.png");
	AddImage(death, L"boss-death4.png");
	AddImage(death, L"boss-death5.png");
	AddImage(death, L"boss-death6.png");
	AddImage(death, L"boss-death7.png");
	AddImage(death, L"boss-death8.png");
	NextAnimation(death, death);
	SetAnimationSpeed(death, 6.0f);

	SetCurrentAnimation(idle);
}

void RoamingRobot::Update(double gt)
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

		SetCurrentAnimation(run);
		
	}

	if (active & health <= 0)
	{
		timer = -gt;
		SetCurrentAnimation(death);
		if (timer >= 1.0f)
		{
			timer = 0.0f;
			active = false;
		}
	}
	Animate(gt);
}

void RoamingRobot::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.1f);

	}
}

IShape2D& RoamingRobot::GetShape()
{
	collisionShape.PlaceAt(position, scale * 20); //collision scales with scale
	return collisionShape;
}
IShape2D& RoamingRobot::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 400); //collision scales with scale
	return detectionRadius;
}

void RoamingRobot::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Soldier))
	{
		health = health + 0.1; //heals when damaging the player
		scale = scale + 0.02; //grows as he damages the player
	}
}
void RoamingRobot::HandleDetection(GameObject& other)
{

}