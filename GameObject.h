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
	float scale;
	void LoadImg(const wchar_t* filename);
public:
	GameObject();
	virtual ~GameObject();
	void Render();
	virtual void Update(double gt) = 0;
	bool IsActive() const;
	void Deactivate();
};