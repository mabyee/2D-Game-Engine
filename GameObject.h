#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"

class GameObject {
private:
	Vector2D position;
	float angle;
	PictureIndex image;
	bool active;
	
public:
	GameObject();						//constructor
	~GameObject();
	void LoadImg();						// std::string filename
	void Render();
	void Update();
};