#pragma once
#include <vector>
#include <unordered_set>
#include "GameObject.h"

class Grid {
private:
    int width;
    int height;
    int cellSize;
    std::vector<std::vector<std::unordered_set<GameObject*>>> cells;

public:
    Grid(int width, int height, int cellSize);
    void addObject(GameObject* obj);
    void removeObject(GameObject* obj);
    void checkCellCollisions(GameObject* obj, std::unordered_set<GameObject*>& collisions);
    void checkAdjacentCellCollisions(GameObject* obj, std::unordered_set<GameObject*>& collisions);

private:
    int calculateCellX(double x);
    int calculateCellY(double y);
};