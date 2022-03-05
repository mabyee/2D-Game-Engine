#include "GameObject.h"

void GameObject::Update(double gt)
{
	if (active)
	{
		angle = 0;												// base angle
		scale = 1.0f;											// base scale
	}
}

void GameObject::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, 0.0f);
	}
}

void GameObject::LoadImg(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);					
}

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::Deactivate()
{
	active = false;
}

// Constructor and Destructor
GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}
