#include "ObjectManager.h"

void ObjectManager::UpdateAll() 
{
	for (auto const& i : pObjectList){
		i->Update();
	}
}

void ObjectManager::RenderAll()
{
	for (auto const& i : pObjectList) {
		i->Render();
	}
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	if (pNewObject)											// checking if nullptr
	{
		pObjectList.push_back(pNewObject);
	}
}