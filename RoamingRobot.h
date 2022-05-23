#pragma once
#include "AnimatedGameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "soldier.h"

class RoamingRobot:public AnimatedGameObject
{
private:
	//animation variables
	const float ANIMATION_SPEED = 6.0f;
	int rightRun, rightIdle, rightDeath, rightShoot, leftRun, leftIdle, leftDeath, leftShoot;
	//movement variables
	float movementSpeed;
	int direction;
	enum class currentState { CHASE, RUN_AWAY, IDLE, ATTACK, DEAD, ROAMING };
	currentState state;
	int randDirX;
	int randDirY;
	//other
	Circle2D collisionShape;
	Circle2D detectionRadius;
	ObjectManager* pObjectManager;
	SoundFX* pSoundFX;
	float health;
	Soldier* pSoldier;
	float timer;
	bool isMoving;
	Score* pScore;
	int soldierAmmo;

public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos, Score* pCurrentScore);
	void Update(double gt);
	void Render()override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};

