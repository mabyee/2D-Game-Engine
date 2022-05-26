/*
Created by Henri Puennel, W19019002.
This is the outer wall, stopping the player or NPCs from leaving the play area.
*/
#pragma once
#include "GameObject.h"

class outerwall :public GameObject
{
private:
	int wallWidth;
	int wallHeight;
	Rectangle2D collisionShape;
	Circle2D detectionRadius;
public:
	void Render() override;
	void Initialise(Vector2D pos, float ang, int width, int height);
	void Update(double gt);
	void HandleCollision(GameObject& other);
	void HandleDetection(GameObject& other);
	IShape2D& GetShape();
	IShape2D& GetDetectionRadius();
	int GetWallWidth();
	int GetWallHeight();
};