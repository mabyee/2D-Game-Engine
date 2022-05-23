#include "RoamingRobot.h"
#include "bullet.h"
#include "soldier.h"
#include "stinger.h"
#include "outerwall.h"
#include "brickwall.h"

void RoamingRobot::Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos, Score* pCurrentScore)
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
	pScore = pCurrentScore;

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
	SetAnimationSpeed(rightRun, ANIMATION_SPEED);

	rightIdle = AddAnimation();
	AddImage(rightIdle, L"robot-idle0.png");
	AddImage(rightIdle, L"robot-idle1.png");
	AddImage(rightIdle, L"robot-idle2.png");
	AddImage(rightIdle, L"robot-idle3.png");
	NextAnimation(rightIdle, rightIdle);
	SetAnimationSpeed(rightIdle, ANIMATION_SPEED);

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
	SetAnimationSpeed(rightShoot, ANIMATION_SPEED);

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
	SetAnimationSpeed(rightDeath, ANIMATION_SPEED);

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
	SetAnimationSpeed(leftRun, ANIMATION_SPEED);

	leftIdle = AddAnimation();
	AddImage(leftIdle, L"flipped-robot-idle0.png");
	AddImage(leftIdle, L"flipped-robot-idle1.png");
	AddImage(leftIdle, L"flipped-robot-idle2.png");
	AddImage(leftIdle, L"flipped-robot-idle3.png");
	NextAnimation(leftIdle, leftIdle);
	SetAnimationSpeed(leftIdle, ANIMATION_SPEED);

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
	SetAnimationSpeed(leftShoot, ANIMATION_SPEED);

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
	SetAnimationSpeed(leftDeath, ANIMATION_SPEED);
	
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

	if (direction == 1 && active) //animations if facing right
	{
		switch (state)
		{
		case currentState::IDLE:
			health += 1.0f; //health regen when IDLE
			SetCurrentAnimation(rightIdle);
			break;
		case currentState::DEAD:
			timer += gt;
			SetCurrentAnimation(rightDeath);
			if (timer >= 1.0f)
			{
				timer = 0.0f;
				active = false;
			}
			break;
		case currentState::CHASE:
			SetCurrentAnimation(rightRun);
			break;
		case currentState::RUN_AWAY:
			SetCurrentAnimation(leftRun); //opposite run direction
			break;
		case currentState::ATTACK:
			timer += gt;
			SetCurrentAnimation(rightShoot);
			if (timer >= 1.0f)
			{
				pSoldier->DealDamage(20);
				timer = 0.0f; //reset timer
			}
			break;
		}
	}

	if (direction == 0 && active) //animations if facing left
	{
		switch (state)
		{
		case currentState::IDLE:
			health += 1.0f; //health regen when IDLE
			SetCurrentAnimation(leftIdle);
			break;
		case currentState::DEAD:
			timer += gt;
			SetCurrentAnimation(leftDeath);
			if (timer >= 1.0f)
			{
				timer = 0.0f;
				active = false;
				pScore->AddScore(150); //adding score
			}	
			break;
		case currentState::CHASE:
			SetCurrentAnimation(leftRun);
			break;
		case currentState::RUN_AWAY:
			SetCurrentAnimation(rightRun); //opposite run direction
			break;
		case currentState::ATTACK:
			SetCurrentAnimation(leftShoot);
			timer += gt;
			if (timer >= 1.0f)
			{
				pSoldier->DealDamage(20);
				timer = 0.0f; //reset timer
			}
			break;
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
		pScore->AddScore(75); //adding score
	}
	if (typeid(other) == typeid(outerwall))
	{
		//collision
	}
	if (typeid(other) == typeid(BrickWall))
	{
		//collision
	}
	if (typeid(other) == typeid(Soldier))
	{
		state = currentState::ATTACK;
		Vector2D soldierPos = other.GetPosition();
		float X = soldierPos.XValue;
		float Y = soldierPos.YValue;
		float dirX = X - position.XValue;
		float dirY = Y - position.YValue;
		float hyp = sqrt(dirX * dirX + dirY * dirY);
		dirX /= hyp;
		dirY /= hyp;
		position.XValue += dirX * movementSpeed / 2; //reduced movement speed while attacking
		position.YValue += dirY * movementSpeed / 2;
	}
}
void RoamingRobot::HandleDetection(GameObject& other)
{
	if (typeid(other) == typeid(Soldier) && active) //if player is in detection radius, CHASE
	{
		Vector2D soldierPos = other.GetPosition();
		float X = soldierPos.XValue;
		float Y = soldierPos.YValue;
		float dirX = X - position.XValue;
		float dirY = Y - position.YValue;
		float hyp = sqrt(dirX * dirX + dirY * dirY);
		
		if (health >= 50.0f) //chase
		{
			if (hyp < 75)
			{
				state = currentState::ATTACK;
				dirX /= hyp;
				dirY /= hyp;
				position.XValue += dirX * movementSpeed/2; //reduced movement speed while attacking
				position.YValue += dirY * movementSpeed/2;
			}
			else
			{
				state = currentState::CHASE;
				dirX /= hyp;
				dirY /= hyp;
				position.XValue += dirX * movementSpeed;
				position.YValue += dirY * movementSpeed;
			}
		}
		if (health < 50.0f) //run away
		{
			if (hyp < 75)
			{
				state = currentState::ATTACK;
				dirX /= hyp;
				dirY /= hyp;
				position.XValue += dirX * movementSpeed / 2; //reduced movement speed while attacking
				position.YValue += dirY * movementSpeed / 2;
			}
			else
			{
				state = currentState::RUN_AWAY;
				dirX /= hyp;
				dirY /= hyp;
				position.XValue -= dirX * movementSpeed;
				position.YValue -= dirY * movementSpeed;
			}
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