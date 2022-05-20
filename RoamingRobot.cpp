#include "RoamingRobot.h"
#include "bullet.h"
#include "soldier.h"

void RoamingRobot::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos)
{
	movementSpeed = 0.0f;
	health = 150;
	position.set(initialPos);
	active = true;
	scale = 0.5f;
	pObjectManager = pOM;
	pSoundFX = sound;
	pSoldier = solPos;
	direction = 1;

	//adding flipped images for different animation states
	rightRun = AddAnimation();
	AddImage(rightRun, L"robot-run0.png");
	AddImage(rightRun, L"robot-run1.png");
	AddImage(rightRun, L"robot-run2.png");
	AddImage(rightRun, L"robot-run3.png");
	AddImage(rightRun, L"robot-run4.png");
	AddImage(rightRun, L"robot-run5.png");
	AddImage(rightRun, L"robot-run6.png");
	AddImage(rightRun, L"robot-run7.png");

	NextAnimation(rightRun, rightRun);
	SetAnimationSpeed(rightRun, 6.0f);

	rightIdle = AddAnimation();
	AddImage(rightIdle, L"robot-idle0.png");
	AddImage(rightIdle, L"robot-idle1.png");
	AddImage(rightIdle, L"robot-idle2.png");
	AddImage(rightIdle, L"robot-idle3.png");
	NextAnimation(rightIdle, rightIdle);
	SetAnimationSpeed(rightIdle, 6.0f);

	rightShoot = AddAnimation();
	AddImage(rightShoot, L"robot-shoot0.png");
	AddImage(rightShoot, L"robot-shoot1.png");
	AddImage(rightShoot, L"robot-shoot2.png");
	AddImage(rightShoot, L"robot-shoot3.png");
	AddImage(rightShoot, L"robot-shoot4.png");
	AddImage(rightShoot, L"robot-shoot5.png");
	AddImage(rightShoot, L"robot-shoot6.png");
	AddImage(rightShoot, L"robot-shoot7.png");
	NextAnimation(rightShoot, rightShoot);
	SetAnimationSpeed(rightShoot, 6.0f);

	rightDeath = AddAnimation();
	AddImage(rightDeath, L"robot-death0.png");
	AddImage(rightDeath, L"robot-death1.png");
	AddImage(rightDeath, L"robot-death2.png");
	AddImage(rightDeath, L"robot-death3.png");
	AddImage(rightDeath, L"robot-death4.png");
	AddImage(rightDeath, L"robot-death5.png");
	AddImage(rightDeath, L"robot-death6.png");
	AddImage(rightDeath, L"robot-death7.png");
	AddImage(rightDeath, L"robot-death8.png");
	NextAnimation(rightDeath, rightDeath);
	SetAnimationSpeed(rightDeath, 6.0f);

	//adding normal images for different animation states
	leftRun = AddAnimation();
	AddImage(leftRun, L"flipped-robot-run0.png");
	AddImage(leftRun, L"flipped-robot-run1.png");
	AddImage(leftRun, L"flipped-robot-run2.png");
	AddImage(leftRun, L"flipped-robot-run3.png");
	AddImage(leftRun, L"flipped-robot-run4.png");
	AddImage(leftRun, L"flipped-robot-run5.png");
	AddImage(leftRun, L"flipped-robot-run6.png");
	AddImage(leftRun, L"flipped-robot-run7.png");

	NextAnimation(leftRun, leftRun);
	SetAnimationSpeed(leftRun, 6.0f);

	leftIdle = AddAnimation();
	AddImage(leftIdle, L"flipped-robot-idle0.png");
	AddImage(leftIdle, L"flipped-robot-idle1.png");
	AddImage(leftIdle, L"flipped-robot-idle2.png");
	AddImage(leftIdle, L"flipped-robot-idle3.png");
	NextAnimation(leftIdle, leftIdle);
	SetAnimationSpeed(leftIdle, 6.0f);

	leftShoot = AddAnimation();
	AddImage(leftShoot, L"flipped-robot-shoot0.png");
	AddImage(leftShoot, L"flipped-robot-shoot1.png");
	AddImage(leftShoot, L"flipped-robot-shoot2.png");
	AddImage(leftShoot, L"flipped-robot-shoot3.png");
	AddImage(leftShoot, L"flipped-robot-shoot4.png");
	AddImage(leftShoot, L"flipped-robot-shoot5.png");
	AddImage(leftShoot, L"flipped-robot-shoot6.png");
	AddImage(leftShoot, L"flipped-robot-shoot7.png");
	NextAnimation(leftShoot, leftShoot);
	SetAnimationSpeed(leftShoot, 6.0f);

	leftDeath = AddAnimation();
	AddImage(leftDeath, L"flipped-robot-death0.png");
	AddImage(leftDeath, L"flipped-robot-death1.png");
	AddImage(leftDeath, L"flipped-robot-death2.png");
	AddImage(leftDeath, L"flipped-robot-death3.png");
	AddImage(leftDeath, L"flipped-robot-death4.png");
	AddImage(leftDeath, L"flipped-robot-death5.png");
	AddImage(leftDeath, L"flipped-robot-death6.png");
	AddImage(leftDeath, L"flipped-robot-death7.png");
	AddImage(leftDeath, L"flipped-robot-death8.png");
	NextAnimation(leftDeath, leftDeath);
	SetAnimationSpeed(leftDeath, 6.0f);
	
	//setting base animation state
	SetCurrentAnimation(rightIdle);
}

void RoamingRobot::Update(double gt)
{
	if (direction == 1 && active) //animations if facing right
	{
		if (movementSpeed == 0.0f) //not moving
		{
			SetCurrentAnimation(rightIdle);
		}

		if (health <= 0) //death
		{
			timer = -gt;
			SetCurrentAnimation(rightDeath);
			if (timer >= 1.0f)
			{
				timer = 0.0f;
				active = false;
			}
		}

		if (movementSpeed) //moving
		{
			SetCurrentAnimation(rightRun);
		}
	}

	if (direction == 0 && active) //animations if facing left
	{
		if (movementSpeed == 0.0f) //not moving
		{
			SetCurrentAnimation(leftIdle);
		}

		if (health <= 0) //death
		{
			timer = -gt;
			SetCurrentAnimation(leftDeath);
			if (timer >= 1.0f)
			{
				timer = 0.0f;
				active = false;
			}
		}

		if (movementSpeed) //moving
		{
			SetCurrentAnimation(leftRun);
		}
	}
	Animate(gt);
}

void RoamingRobot::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);
	}
}

IShape2D& RoamingRobot::GetShape()
{
	collisionShape.PlaceAt(position, 20);
	return collisionShape;
}
IShape2D& RoamingRobot::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 400);
	return detectionRadius;
}

void RoamingRobot::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health -= 10;
	}
}
void RoamingRobot::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier) && active)
	{
		Vector2D soldierPos = other.GetPosition();
		float X = soldierPos.XValue;
		float Y = soldierPos.YValue;
		if (X > position.XValue)
		{
			direction = 1;
		}
		else
		{
			direction = 0;
		}

		//angle = -atan2(Y - position.YValue, X - position.XValue) + 1.57;
		//DOES NOT WORK, IMAGE ROTATES- Instead mirror left and right depending on
		//the direction it is moving/the player is.
	}
}