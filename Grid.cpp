
#pragma once
#include "Grid.h"

Grid::Grid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize) {
    int numCols = width / cellSize;
    int numRows = height / cellSize;
    cells.resize(numCols, std::vector<std::unordered_set<GameObject*>>(numRows));
}

void Grid::addObject(GameObject* obj) {
    int cellX = calculateCellX(obj->GetX());
    int cellY = calculateCellY(obj->GetY());
    cells[cellX][cellY].insert(obj);
}

void Grid::removeObject(GameObject* obj) {
    int cellX = calculateCellX(obj->GetX());
    int cellY = calculateCellY(obj->GetY());
    cells[cellX][cellY].erase(obj);
}

void Grid::checkCellCollisions(GameObject* obj, std::unordered_set<GameObject*>& collisions) {
    int cellX = calculateCellX(obj->GetX());
    int cellY = calculateCellY(obj->GetY());

    for (GameObject* other : cells[cellX][cellY]) {
        if (other != obj && other->GetShape().Intersects(obj->GetShape())) {
            collisions.insert(other);
        }
    }
}

void Grid::checkAdjacentCellCollisions(GameObject* obj, std::unordered_set<GameObject*>& collisions) {
    int cellX = calculateCellX(obj->GetX());
    int cellY = calculateCellY(obj->GetY());

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int neighborX = cellX + dx;
            int neighborY = cellY + dy;

            if (neighborX >= 0 && neighborX < cells.size() && neighborY >= 0 && neighborY < cells[0].size()) {
                for (GameObject* other : cells[neighborX][neighborY]) {
                    if (other != obj && other->GetShape().Intersects(obj->GetShape())) {
                        collisions.insert(other);
                    }
                }
            }
        }
    }
}

int Grid::calculateCellX(double x) {
    return static_cast<int>(x / cellSize);
}

int Grid::calculateCellY(double y) {
    return static_cast<int>(y / cellSize);
}
