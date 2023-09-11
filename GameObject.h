/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once

#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"
#include <typeinfo>
#include "Animation.h"

class GameObject {
protected:
    PictureIndex image;
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
    virtual IShape2D& GetDetectionRadius() = 0;
    virtual void HandleCollision(GameObject& other) = 0;
    virtual void HandleDetection(GameObject& other) = 0;
    bool IsActive() const;
    void Deactivate();
    Vector2D GetPosition();
    // Add these methods to get the X and Y coordinates.
    double GetX() const;
    double GetY() const;
    virtual void AddImage(Animation* anim, const wchar_t* filename);
    virtual void SetCurrentImage(int image);
};
