#include "ammoBox.h"
#include "spaceship.h"

void ammoBox::Initialise(Vector2D pos, ObjectManager* pOM)
{
	position.set(pos);
	LoadImg(L"crate1.bmp");
	angle = 0;
	active = true;
	scale = 1.0f;
	pObjectManager = pOM;
}
void ammoBox::Update(double gt)
{

}
void ammoBox::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Spaceship))
	{
		Deactivate(); //remove
	}
}
IShape2D& ammoBox::GetShape()
{
	collisionShape.PlaceAt(position, 16);
	return collisionShape;
}