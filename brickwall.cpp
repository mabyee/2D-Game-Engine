#include "brickwall.h"
#include "Shapes.h"
#include "mydrawengine.h"
#include "vector2D.h"

void BrickWall::Update()
{

}

void BrickWall::Initialise()
{

}


void BrickWall::makeWall(int brickStart, int brickEnd, int R, int G, int B, int brickAmount)
{
	Rectangle2D brickWallArray[1000];			// Maximum size 1000
	Rectangle2D rectangle;
	rectangle.PlaceAt(brickStart, brickStart, brickEnd, brickEnd);
	int colour = _XRGB(R, G, B);
	MyDrawEngine::GetInstance()->FillRect(rectangle, colour);

	for (int i = 0; i < brickAmount; i++)
	{
		brickWallArray[i] = rectangle;
	}
}