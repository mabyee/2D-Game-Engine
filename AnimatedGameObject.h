/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "GameObject.h"
#include "Animation.h"

class AnimatedGameObject : public GameObject
{
private:
	std::vector<Animation> animations;
	int m_currentAnimation = 0;
	float m_animationTimer = 0.0f;
public:
	void SetCurrentAnimation(int anim);
	void Animate(float frameTime);
	int AddAnimation();
	void AddImage(int animCount, const wchar_t* filename);
	void SetAnimationSpeed(int index, float speed);
	void NextAnimation(int currentIndex, int nextIndex);
};

