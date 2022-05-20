/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "GameObject.h"


void GameObject::Update(double gt)
{
	if (active)
	{

	}
}

void GameObject::AddImage(Animation* anim, const wchar_t* filename) {};
void GameObject::SetCurrentImage(int image) {};

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

Vector2D GameObject::GetPosition()
{
	return position;
}