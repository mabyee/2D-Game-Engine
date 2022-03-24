#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

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

void ObjectManager::CheckAllCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
		{
			if ((*it1) && (*it2) && (*it1)->IsActive() && (*it2)->IsActive() && ((*it1)->GetShape().Intersects((*it2)->GetShape())))
			{
				(*it1)->HandleCollision((**it2));
				(*it2)->HandleCollision((**it1));
			}
			if ((*it1) && (*it2) && (*it1)->IsActive() && (*it2)->IsActive() && ((*it1)->GetDetectionRadius().Intersects((*it2)->GetDetectionRadius())))
			{
				(*it1)->HandleDetection((**it2));
				(*it2)->HandleDetection((**it1));
			}
		}
	}
}