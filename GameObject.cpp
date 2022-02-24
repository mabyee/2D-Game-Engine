#include "GameObject.h"

void GameObject::Update()
{
	active = true;											//activating
	angle = 0;												//setting angle												
}

void GameObject::Render()
{

}

void GameObject::LoadImg()									// std::string filename
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(L"ship.bmp");					//HARDCODED FOR NOW : TODO
}