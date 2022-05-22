#include "RoamingRobot.h"
#include "bullet.h"
#include "soldier.h"
#include "stinger.h"
#include "outerwall.h"
#include "brickwall.h"

void RoamingRobot::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos)
{
	movementSpeed = 5.0f;
	health = 150.0f;
	position.set(initialPos);
	active = true;
	scale = 0.5f;
	pObjectManager = pOM;
	pSoundFX = sound;
	pSoldier = solPos;
	direction = 1;
	isMoving = false;
	state = currentState::IDLE;

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
	if (health <= 0) //set DEAD state when health reaches 0
	{
		movementSpeed = 0.0f;
		state = currentState::DEAD;
	}

	if (health < 50 && health > 0) //set RUN_AWAY if low health
	{
		state = currentState::RUN_AWAY;
	}

	if (direction == 1 && active) //animations if facing right
	{
		if (state == currentState::IDLE) //not moving
		{
			health += 0.1f; //health regen when IDLE
			SetCurrentAnimation(rightIdle);
		}

		if (state == currentState::DEAD) //death
		{
			timer += gt;
			SetCurrentAnimation(rightDeath);
			if (timer >= 1.0f)
			{
				timer = 0.0f;
				active = false;
			}
		}

		if (state == currentState::CHASE) //moving
		{
			SetCurrentAnimation(rightRun);
		}

		if (state == currentState::RUN_AWAY)
		{

			SetCurrentAnimation(leftRun);//opposite run direction

		}
	}

	if (direction == 0 && active) //animations if facing left
	{
		if (state == currentState::IDLE) //not moving
		{
			health += 0.1f;
			SetCurrentAnimation(leftIdle);
		}

		if (state == currentState::DEAD) //death
		{
			timer += gt;
			SetCurrentAnimation(leftDeath);
			if (timer >= 1.5f)
			{
				timer = 0.0f;
				active = false;
			}
		}

		if (state == currentState::CHASE) //moving
		{
			SetCurrentAnimation(leftRun);
		}

		if (state == currentState::RUN_AWAY)
		{

			SetCurrentAnimation(rightRun);
		
		}
	}
	Animate(gt); //play animation
	state = currentState::IDLE; //reset to IDLE
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
	collisionShape.PlaceAt(position, 50);
	return collisionShape;
}
IShape2D& RoamingRobot::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 500);
	return detectionRadius;
}

void RoamingRobot::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health -= 10.0f;
	}
	if (typeid(other) == typeid(Stinger))
	{
		health -= 75.0f;
	}
	if (typeid(other) == typeid(outerwall))
	{
		//collision
	}
	if (typeid(other) == typeid(BrickWall))
	{
		//collision
	}
}
void RoamingRobot::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier) && active) //if player is in detection radius, CHASE
	{
		Vector2D soldierPos = other.GetPosition();
		float X = soldierPos.XValue;
		float Y = soldierPos.YValue;
		
		if (health >= 50.0f) //chase
		{
			state = currentState::CHASE;
			float dirX = X - position.XValue;
			float dirY = Y - position.YValue;
			float hyp = sqrt(dirX * dirX + dirY * dirY);
			dirX /= hyp;
			dirY /= hyp;
			position.XValue += dirX * movementSpeed;
			position.YValue += dirY * movementSpeed;
		}
		else //run away
		{
			state = currentState::RUN_AWAY;
			float dirX = X - position.XValue;
			float dirY = Y - position.YValue;
			float hyp = sqrt(dirX * dirX + dirY * dirY);
			dirX /= hyp;
			dirY /= hyp;
			position.XValue -= dirX * movementSpeed;
			position.YValue -= dirY * movementSpeed;
		}
		
		//turn the model depending on X position relative to player
		if (X > position.XValue)
		{
			direction = 1;

		}
		else
		{
			direction = 0;
		}
	}
}