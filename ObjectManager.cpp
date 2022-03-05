#include "ObjectManager.h"

void ObjectManager::UpdateAll(double gt) 
{
	for (auto const& i : pObjectList){
		i->Update(gt);
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

void ObjectManager::DeleteAll()
{
	for (GameObject* pNext : pObjectList)
	{
		delete pNext;
		pNext = nullptr;
	}
	pObjectList.clear();
}