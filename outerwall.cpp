/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "outerwall.h"

void outerwall::Initialise(int side)
{
	active = true;
	LoadImg(L"Images/InnerWall/innerWall0.png");
	scale = 0.7f;
	wallSide = side;
}

void outerwall::Update(double gt)
{

}

IShape2D& outerwall::GetShape()
{
	switch (wallSide) //place collision depending on wall location
	{
	case 1://NORTH-EAST
		collisionShape.PlaceAt(Vector2D(-1600, 1000), Vector2D(0, 936));
		position = Vector2D(-1600, 936);
		break;
	case 2://NORTH-WEST
		collisionShape.PlaceAt(Vector2D(0, 1000), Vector2D(1600, 936));
		position = Vector2D(0, 936);
		break;
	case 3://EAST
		collisionShape.PlaceAt(Vector2D(1600, 1000), Vector2D(1568, -1000));
		position = Vector2D(1600,0);
		break;
	case 4://SOUTH
		collisionShape.PlaceAt(Vector2D(-1600, -1000), Vector2D(1600, -936));
		position = Vector2D(0, -1000);
		break;
	case 5://WEST
		collisionShape.PlaceAt(Vector2D(-1600, 1000), Vector2D(-1568, -1000));
		position = Vector2D(-1600, 0);
		break;
	}
	return collisionShape;
}

void outerwall::HandleCollision(GameObject& other)
{
}
IShape2D& outerwall::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 0);
	return detectionRadius;
}

void outerwall::HandleDetection(GameObject& other)
{
}