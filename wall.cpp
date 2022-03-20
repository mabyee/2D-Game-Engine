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
