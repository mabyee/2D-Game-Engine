/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "outerwall.h"

void outerwall::Initialise(Vector2D pos, float ang, int width, int height)
{
	wallWidth = width;
	wallHeight = height;
	position = pos;
	active = true;
	scale = 3.0f;
	angle = ang;
	LoadImg(L"Images/OuterWall/outerWall.png");
}

void outerwall::HandleCollision(GameObject& other)
{

}
void outerwall::HandleDetection(GameObject& other)
{

}
void outerwall::Update(double gt)
{

}

void outerwall::Render()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	for (int i = 0;  i < wallWidth; i++)
	{
		for (int j = 0; j < wallHeight; j++)
		{
			if (active)
			{
				pDE->DrawAt(position+Vector2D(i*88,j*88), image, scale, angle);
			}
		}
	}
}

IShape2D& outerwall::GetShape()
{
	collisionShape.PlaceAt(position - Vector2D(44, 44), position + Vector2D((88 * wallWidth)-44, (88 * wallHeight)-44));
	return collisionShape;
}

IShape2D& outerwall::GetDetectionRadius()
{
	detectionRadius.PlaceAt(position, 0);
	return detectionRadius;
}

int outerwall::GetWallWidth()
{
	return wallWidth;
}

int outerwall::GetWallHeight()
{
	return wallHeight;
}