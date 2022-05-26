/*
Created by Henri Puennel, W19019002.
This file handels game objects which are animated.
*/
#include "AnimatedGameObject.h"

void AnimatedGameObject::AddImage(int animCount, const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	animations[animCount].m_images.push_back(pDE->LoadPicture(filename));
}

// reset timer, change animation
void AnimatedGameObject::SetCurrentAnimation(int anim)
{
	if (anim != m_currentAnimation)
	{
		m_currentAnimation = anim;
		m_animationTimer = 0;
	}
}

void AnimatedGameObject::Animate(float frameTime)
{
	Animation& anim = animations[m_currentAnimation];
	m_animationTimer += anim.m_animationSpeed * frameTime;
	if (m_animationTimer >= anim.m_images.size())
	{
		m_currentAnimation = anim.m_nextAnimation;
		m_animationTimer = 0;
	}
	image = animations[m_currentAnimation].m_images[int(m_animationTimer)];
}

int AnimatedGameObject::AddAnimation()
{
	Animation* temp = new Animation();
	animations.push_back(*temp);
	delete temp;
	temp = nullptr;
	return animations.size() - 1;
}

void AnimatedGameObject::NextAnimation(int currentIndex, int nextIndex)
{
	animations[currentIndex].m_nextAnimation = nextIndex;
}

void AnimatedGameObject::SetAnimationSpeed(int index, float speed)
{
	animations[index].m_animationSpeed = speed;
}