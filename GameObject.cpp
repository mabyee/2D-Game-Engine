/*
Created by Henri Puennel, W19019002.
This file...
*/
// GameObject.cpp
#include "GameObject.h"

void GameObject::Render() {
    if (active) {
        MyDrawEngine* pDE = MyDrawEngine::GetInstance();
        pDE->DrawAt(position, image, scale, angle, 0.0f);
    }
}

void GameObject::LoadImg(const wchar_t* filename) {
    MyDrawEngine* pDE = MyDrawEngine::GetInstance();
    image = pDE->LoadPicture(filename);
}

bool GameObject::IsActive() const {
    return active;
}

void GameObject::Deactivate() {
    active = false;
}

GameObject::GameObject() : active(true), scale(1.0f), angle(0.0f) {
    screenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
    screenHeight = MyDrawEngine::GetInstance()->GetScreenHeight();
}

GameObject::~GameObject() {
    // Destructor implementation, if needed.
}

Vector2D GameObject::GetPosition() {
    return position;
}

// Implement the GetX and GetY methods to return the X and Y coordinates of the object.
double GameObject::GetX() const {
    return position.XValue; // Assuming you store the position as a Vector2D.
}

double GameObject::GetY() const {
    return position.YValue; // Assuming you store the position as a Vector2D.
}

// Implement these methods if needed for handling images/animations.
void GameObject::AddImage(Animation* anim, const wchar_t* filename) {
    // Implementation for adding images/animations.
}

void GameObject::SetCurrentImage(int image) {
    // Implementation for setting the current image.
}
