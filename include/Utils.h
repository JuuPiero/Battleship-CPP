
#pragma once
#include <vector>
#include "Ship.h"
#include <iostream>
#include "Game.h"
bool isValidPosition(const std::vector<std::vector<char>>& grid, const Ship& ship, int gridWidth, int gridHeight);

// void placeShip(std::vector<std::vector<int>>& grid, const Ship& ship);

void placeShip(std::vector<std::vector<char>>& grid, const Ship& ship);

void DisplayGrid(int width, int height);

std::pair<int, int> GetRandomTarget(const std::vector<std::vector<char>>& grid);
inline std::vector<std::vector<char>> CreateMap(int rows, int cols, char defaultValue = '~') {
    return std::vector<std::vector<char>>(rows, std::vector<char>(cols, defaultValue));
}