#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"
#include <typeinfo>

class GameObject {
private:
	PictureIndex image;
protected:
	Vector2D position;
	float angle;
	bool active;
	float scale;
	void LoadImg(const wchar_t* filename);
	int screenWidth;
	int screenHeight;
public:
	GameObject();
	virtual ~GameObject();
	virtual void Render();
	virtual void Update(double gt) = 0;
	virtual IShape2D& GetShape() = 0;
	virtual void HandleCollision(GameObject& other) = 0;
	bool IsActive() const;
	void Deactivate();
	Vector2D GetPosition();
};