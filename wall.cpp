/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "wall.h"

void Wall::Initialise(Vector2D pos, float ang)
{

}

IShape2D& Wall::GetShape()
{
	collisionShape.PlaceAt(position - Vector2D(44, 44), position + Vector2D(44, 44));
	return collisionShape;
}

void Wall::Update(double gt)
{

}
IShape2D& Wall::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 0);
	return detectionRadius;
}

void Wall::HandleDetection(GameObject& other)
{
}