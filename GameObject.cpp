#include "GameObject.h"

void GameObject::Update()
{										
	angle = 0;												// base angle
	scale = 1.0f;											// base scale
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