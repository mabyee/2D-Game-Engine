#include "ObjectManager.h"

void ObjectManager::UpdateAll(double gt) 
{
	for (auto const& i : pObjectList)
	{
		if (i->IsActive())
		{
			i->Update(gt);
		}
	}
}

void ObjectManager::RenderAll()
{
	for (auto const& i : pObjectList) 
	{
		if (i->IsActive())
		{
			i->Render();
		}
	}
	MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(), MyDrawEngine::GREEN);			// Keeps count of objects being tracked

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

void ObjectManager::DeleteInactiveObjects()
{
	for (GameObject*& pNext : pObjectList)
	{
		if (!pNext->IsActive())
		{
			delete pNext;
			pNext = nullptr;
		}
	}
	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);				// Moving nullptr to end
	pObjectList.erase(it, pObjectList.end());											// Deleting end (all nullptr)
}