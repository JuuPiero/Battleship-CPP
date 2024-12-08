
#pragma once
#define CHEAT 0
#include <vector>
#include "Ship.h"
#include <iostream>
#include "Game.h"

bool isValidPosition(const std::vector<std::vector<char>>& grid, const Ship& ship, int gridWidth, int gridHeight);

void PlaceShip(std::vector<std::vector<char>>& grid, const Ship& ship);

void DisplayGrid(int width, int height);

std::pair<int, int> GetRandomTarget(const std::vector<std::vector<char>>& grid);
inline std::vector<std::vector<char>> CreateMap(int rows, int cols, char defaultValue = '~') {
    return std::vector<std::vector<char>>(rows, std::vector<char>(cols, defaultValue));
}
void DrawGrid(std::vector<std::vector<char>>& grid);