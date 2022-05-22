#pragma once
#include "AnimatedGameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"
#include "soldier.h"

class RoamingRobot:public AnimatedGameObject
{
private:
	int rightRun, rightIdle, rightDeath, rightShoot, leftRun, leftIdle, leftDeath, leftShoot;
	float movementSpeed;
	int direction;
	Circle2D collisionShape;
	Circle2D detectionRadius;
	ObjectManager* pObjectManager;
	SoundFX* pSoundFX;
	float health;
	Soldier* pSoldier;
	float timer;
	bool isMoving;
	enum class currentState { CHASE, RUN_AWAY, IDLE, ATTACK, DEAD };
	currentState state;

public:
	void Initialise(Vector2D initialPos, ObjectManager* pOM, SoundFX* sound, Soldier* solPos);
	void Update(double gt);
	void Render()override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	IShape2D& GetDetectionRadius();
	void HandleDetection(GameObject& other);
};

