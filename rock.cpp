#include "rock.h"

void Rock::Initialise(Vector2D initialPos)
{
	position.set(initialPos);
	velocity.set(0, 0);
	active = true;
	angle = 0;
	scale = 3.0f;
	LoadImg(L"botboy.bmp");
}

void Rock::Update()
{

}