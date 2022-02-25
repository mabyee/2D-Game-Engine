#include "GameObject.h"

void GameObject::Update()
{
	active = true;											//activating
	angle = 0;												//setting angle												
}

void GameObject::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, 1.0f, angle, 0.0f);
	}
}

void GameObject::LoadImg(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);					
}