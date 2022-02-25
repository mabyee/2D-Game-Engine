#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"

class GameObject {
private:
	PictureIndex image;
protected:
	Vector2D position;
	float angle;
	bool active;
	void LoadImg(const wchar_t* filename);
public:
	void Render();
	virtual void Update() = 0;
};