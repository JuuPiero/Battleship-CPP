#include "Player.h"
#include <iostream>
#include "Game.h"
#include "Utils.h"
#include <set>
#include <utility>
#include <queue>
#include <cstdlib>
#include <ctime>
Player::Player(Role role): role(role) {}
bool Player::Shoot(int x, int y) {
    auto game = Game::GetInstance();
    std::set<char> validValues = {'1', '2', '3', '4'};

    std::shared_ptr<Player> enemy = nullptr;
    if(game->currentPlayer->IsMaster()) enemy = game->slave;
    else enemy = game->master;

    if (x >= 0 && x < game->board.size() && y >= 0 && y < game->board[0].size() && enemy->IsMaster()) {
        if(validValues.count(enemy->map[y][x]) && game->board[y][x] != 'H') {
            game->board[y][x] = 'H'; // Bắn trúng
            // char type = enemy->map[x][y];
            enemy->map[y][x] = 'H';
            game->Render();
            return true;
        }
        else if (enemy->map[y][x] == '~') {
            game->board[y][x] = 'M';
            enemy->map[y][x] = 'M';
            game->Render();
            return false;
            // std::cout << "miss" << std::endl;
        }
        else {
            return false;
            // std::cout << "miss" << std::endl;
        }
    } else {
        std::cout << "Invalid coordinates!" << std::endl;
        return false;
    }
}


bool Player::MapEmpty() {
    auto game = Game::GetInstance();
    for (int row = 0; row < game->GetHeight(); row++) {
        for (int col = 0; col < game->GetWidth(); col++) {
            if(map[row][col] != '~') return false;
        }
    }
    return true;
}

void Player::DisplaytListShip() {
    for (auto &ship : ships) {
        std::cout << "Ship " << ship.type << std::endl;
        std::cout << "Ship direction: " << ship.direction << std::endl;
        std::cout << "Ship position: " << ship.x << ", " << ship.y << std::endl;
    }
}

void Player::DisplayMap() {
    auto game = Game::GetInstance();
    if(!game->GetWidth() || !game->GetHeight()) {
        return;
    }
    if(map.empty()) {
        return;
    }
    std::cout << "   ";  
    for (int col = 0; col < game->GetWidth(); col++) {
        std::cout << col << ' ';
    }
    std::cout << '\n';

    for (int row = 0; row < game->GetHeight(); row++) {
        std::cout << row << "  "; 
        for (int col = 0; col < game->GetWidth(); col++) {
            std::cout << map[row][col] << ' ';
        }
        std::cout << '\n';
    }
}


std::tuple<int, int, bool>  Player::ShootOrdered() {
    // if(!IsMaster());
    auto game = Game::GetInstance();
    auto& grid = game->slave->map;
    
    std::set<char> validValues = {'1', '2', '3', '4'};
    
    for (size_t y = 0; y < grid.size(); ++y) {        
        for (size_t x = 0; x < grid[y].size(); ++x) { 
            if (grid[y][x] == '~') { 
                grid[y][x] = 'M'; 
                return std::make_tuple(x, y, false);
            }
            else if(validValues.count(grid[y][x])) {
                grid[y][x] = 'H';
                return std::make_tuple(x, y, true);
            }
        }
    }
    return std::make_tuple(-1, -1, false);
}

bool Player::IsWinner() {
    std::set<char> validValues = {'1', '2', '3', '4'};
    auto game = Game::GetInstance();
    std::shared_ptr<Player> enemy = nullptr;
    if(game->currentPlayer->IsMaster()) enemy = game->slave;
    else enemy = game->master;

    for (size_t y = 0; y < game->GetHeight(); ++y) {
        for (size_t x = 0; x < game->GetWidth(); ++x) {
            if (validValues.count(enemy->map[y][x])) {
                return false;
            }
        }
    }
    return true; 
}

bool Player::IsLose() {
    std::set<char> validValues = {'1', '2', '3', '4'};
    auto game = Game::GetInstance();
    for (size_t y = 0; y < game->GetHeight(); ++y) {
        for (size_t x = 0; x < game->GetWidth(); ++x) {
            if (validValues.count(this->map[y][x])) {
                return false;
            }
        }
    }
    return true;
}


std::tuple<int, int, bool>  Player::ShootCustom() {
    auto& grid = Game::GetInstance()->slave->map;


    auto game = Game::GetInstance();
    std::set<char> validValues = {'1', '2', '3', '4'};
   
  
    const std::vector<std::pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    while (!targets.empty()) {
        auto [x, y] = targets.front();
        targets.pop();
        
        if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size() || grid[y][x] != 'H' || grid[y][x] != 'M') {
            continue; // Bỏ qua ô không hợp lệ hoặc đã bắn
        }

        if (validValues.count(grid[y][x])) {
            std::cout << "hit\n";
            grid[y][x] = 'H'; // Đánh dấu 
            // Thêm các ô lân cận vào danh sách mục tiêu
            for (const auto& [dx, dy] : directions) {
                targets.push({x + dx, y + dy});
            }
            // return true; // Dừng sau khi bắn trúng
            return std::make_tuple(x, y, true);
        } else {
            grid[y][x] = 'M'; // Đánh dấu đã bắn nhưng không trúng
            // return false; // Dừng sau khi bắn
            return std::make_tuple(x, y, false);
        }
    }

    if (targets.empty()) {
        auto [rx, ry] = GetRandomTarget(grid);
        if (rx != -1 && ry != -1) {
            if (validValues.count(grid[ry][rx])) {
                grid[ry][rx] = 'H'; 
                for (const auto& [dx, dy] : directions) {
                    int nx = rx + dx;
                    int ny = ry + dy;
                    if (nx >= 0 && nx < grid[0].size() && ny >= 0 && ny < grid.size() && grid[ny][nx] == '~') {
                        targets.push({nx, ny});
                    }
                }
                // return true; 
                return std::make_tuple(rx, ry, true);
            } else {
                grid[ry][rx] = 'M'; // Đánh dấu không trúng
                // return false; 
                return std::make_tuple(rx, ry, false);
            }
        }
        return std::make_tuple(-1, -1, false);
    }
    return std::make_tuple(-1, -1, false);
}