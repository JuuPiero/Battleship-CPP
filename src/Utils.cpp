#include "Utils.h"
#include <cstring>

bool isValidPosition(const std::vector<std::vector<char>>& grid, const Ship& ship, int gridWidth, int gridHeight) {
    int dx = (ship.direction == 'h') ? 1 : 0;
    int dy = (ship.direction == 'v') ? 1 : 0;

    // Kiểm tra tàu có vượt khỏi lưới không
    if ((ship.x + dy * (ship.type - 1) >= gridHeight) || (ship.y + dx * (ship.type - 1) >= gridWidth)) {
        return false;
    }

    // Kiểm tra tàu có chồng lấn không
    for (int i = 0; i < ship.type; i++) {
        int nx = ship.x + i * dy;
        int ny = ship.y + i * dx;
        if (grid[nx][ny] != '~') {
            return false;
        }
    }
    return true;
}


void PlaceShip(std::vector<std::vector<char>>& grid, const Ship& ship) {
    int dx = (ship.direction == 'h') ? 1 : 0;
    int dy = (ship.direction == 'v') ? 1 : 0;
    
    for (int i = 0; i < ship.type; i++) {
        int nx = ship.x + i * dx; 
        int ny = ship.y + i * dy; 
        grid[ny][nx] =  ship.type + '0'; // Đánh dấu tàu trên lưới
    }
}

void DrawGrid(std::vector<std::vector<char>>& grid) {
    auto game = Game::GetInstance();
    if(game->GetWidth() == 0 || game->GetHeight() == 0) {
        return;
    }

    std::cout << "   ";  
    for (int col = 0; col < game->GetWidth(); col++) {
        std::cout << col << ' ';
    }
    std::cout << '\n';

    for (int row = 0; row < game->GetHeight(); row++) {
        std::cout << row << "  ";  // Tọa độ hàng
        for (int col = 0; col < game->GetWidth(); col++) {
            std::cout << grid[row][col] << ' ';
        }
        std::cout << '\n';
    }
}


void DisplayGrid(int width, int height) {
    if(width == 0 || height == 0) {
        return;
    }
    auto game = Game::GetInstance();
    if(game->board.empty()) {
        return;
    }

    std::cout << "   ";  
    for (int col = 0; col < width; col++) {
        std::cout << col << ' ';
    }
    std::cout << '\n';

    for (int row = 0; row < height; row++) {
        std::cout << row << "  ";  // Tọa độ hàng
        for (int col = 0; col < width; col++) {
            std::cout << game->board[row][col] << ' ';
        }
        std::cout << '\n';
    }
}


std::pair<int, int> GetRandomTarget(const std::vector<std::vector<char>>& grid) {
    std::vector<std::pair<int, int>> availableTargets;

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] != 'H' || grid[y][x] != 'M') { // Ô chưa bị bắn
                availableTargets.emplace_back(x, y);
            }
        }
    }

    if (availableTargets.empty()) {
        return {-1, -1};
    }

    int randomIndex = std::rand() % availableTargets.size();
    return availableTargets[randomIndex];
}
