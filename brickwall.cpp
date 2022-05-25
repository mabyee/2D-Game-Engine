/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "brickwall.h"
#include "bullet.h"

void BrickWall::Initialise(Vector2D pos, float ang)
{
	position = pos;
	active = true;
	LoadImg(L"Images/InnerWall/innerWall0.png");
	scale = 0.7f;
	angle = ang;
	health = 100;
}

void BrickWall::Update(double gt)
{
	if (health <= 0)
	{
		Deactivate();
	}
	if (health < 80 & health > 50) //wall damage stages
	{
		LoadImg(L"Images/InnerWall/innerWall1.png");
	}
	if (health < 49 & health > 20)
	{
		LoadImg(L"Images/InnerWall/innerWall2.png");
	}
	if (health < 19 & health >= 0)
	{
		LoadImg(L"Images/InnerWall/innerWall3.png");
	}
}

void BrickWall::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		health = health - 5;
	}
}

void BrickWall::HandleDetection(GameObject& other)
{
}