#pragma once
#include "GameObject.h"
#include "soldier.h"

class HUD:public GameObject
{
private:
	unsigned int colour;
	Vector2D SizeX;
	Vector2D SizeY;
	Rectangle2D HUDShape;
	Circle2D collisionShape;
	Soldier* pSoldier;
public:
	void Initialise();
	void Update(double gt);
	void Render() override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

