#pragma once
#include "GameObject.h"
#include <list>
class ObjectManager {
private:
	std::list<GameObject*> pObjectList;
public:
	void AddObject(GameObject* pNewObject);
	void UpdateAll();
	void RenderAll();
};