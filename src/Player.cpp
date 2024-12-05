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
void Player::Shoot(int x, int y) {
    auto game = Game::GetInstance();
    std::set<char> validValues = {'1', '2', '3', '4'};

    std::shared_ptr<Player> enemy = nullptr;
    if(game->currentPlayer->IsMaster()) enemy = game->slave;
    else enemy = game->master;

    if (x >= 0 && x < game->board.size() && y >= 0 && y < game->board[0].size() && enemy->IsMaster()) {
        if(validValues.count(enemy->map[y][x]) && game->board[y][x] != 'H') {
            game->board[y][x] = 'H'; // Bắn trúng
            char type = enemy->map[x][y];
            enemy->map[y][x] = 'H';
            game->Render();
            std::cout << "hit" << std::endl;
        }
        else if (enemy->map[y][x] == '~') {
            game->board[y][x] = 'M';
            game->Render();
            std::cout << "miss" << std::endl;
        }
        else {
            std::cout << "miss" << std::endl;
        }
    } else {
        std::cout << "Invalid coordinates!" << std::endl;
    }
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
    if(game->GetWidth() == 0 && game->GetHeight() == 0) {
        return;
    }
    std::cout << "   ";  // Dành chỗ cho tọa độ hàng
    for (int col = 0; col < game->GetWidth(); col++) {
        std::cout << col << ' ';
    }
    std::cout << '\n';

    for (int row = 0; row < game->GetHeight(); row++) {
        std::cout << row << "  ";  // Tọa độ hàng
        for (int col = 0; col < game->GetWidth(); col++) {
            std::cout << map[row][col] << ' ';
        }
        std::cout << '\n';
    }
}


void Player::ShootOrdered(std::vector<std::vector<char>>& grid) {
    auto game = Game::GetInstance();
    std::set<char> validValues = {'1', '2', '3', '4'};
    
    for (size_t y = 0; y < grid.size(); ++y) {        // Duyệt từng hàng (trục dọc)
        for (size_t x = 0; x < grid[y].size(); ++x) { // Duyệt từng cột (trục ngang)
            if (grid[y][x] == '~') { 
                grid[y][x] = 'M'; 
                return;
            }
            else if(validValues.count(grid[y][x])) {
                grid[y][x] = 'H';
                return; 
            }
        }
    }
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
    return true; // Thắng
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
    return true; // Thua
}




// Hàm xử lý lượt bắn tự động thông minh
void Player::ShootCustom(std::vector<std::vector<char>>& grid) {
    // std::vector<std::vector<char>>& grid, std::queue<std::pair<int, int>>& targets
    auto game = Game::GetInstance();
    std::set<char> validValues = {'1', '2', '3', '4'};
   
    // if (!targets.empty()) {
    //     std::cout << "Have .\n";
    //     while (!targets.empty()) {
    //         auto [x, y] = targets.front();
    //         targets.pop(); // Lấy phần tử đầu tiên ra và xóa nó khỏi bản sao
    //         std::cout << "(" << x << ", " << y << ") ";
    //     }
    //     // return;
    //     exit(0);
    //     // fore
    // }
    const std::vector<std::pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    while (!targets.empty()) {
        auto [x, y] = targets.front();
        targets.pop();

        // std::cout <<
        // Kiểm tra tính hợp lệ của ô
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
            return; // Dừng sau khi bắn trúng
        } else {
            grid[y][x] = 'M'; // Đánh dấu đã bắn nhưng không trúng
            return; // Dừng sau khi bắn
        }
    }

    if (targets.empty()) {
        std::cout << "Queue is empty. Choosing random target.\n";
        auto [rx, ry] = GetRandomTarget(grid);
        if (rx != -1 && ry != -1) {
            // std::cout << "Computer fired at (" << rx << ", " << ry << ").\n";
            if (validValues.count(grid[ry][rx])) {
                std::cout << "hit\n";
                grid[ry][rx] = 'H'; 
                for (const auto& [dx, dy] : directions) {
                    int nx = rx + dx;
                    int ny = ry + dy;
                    if (nx >= 0 && nx < grid[0].size() && ny >= 0 && ny < grid.size() && grid[ny][nx] == '~') {
                        targets.push({nx, ny});
                    }
                }
            } else {
                grid[ry][rx] = 'M'; // Đánh dấu không trúng
            }
        }
        return;
    }


    // for (size_t y = 0; y < grid.size(); ++y) {
    //     for (size_t x = 0; x < grid[y].size(); ++x) {
    //         if (grid[y][x] == '~') { // '.' đại diện cho ô chưa bị bắn
    //             grid[y][x] = 'M';   // Đánh dấu đã bắn
    //             return;
    //         }
    //         else if(validValues.count(grid[y][x])) {
    //             grid[y][x] = 'H';
    //             std::cout << "hit";
    //             for (const auto& [dx, dy] : directions) {
    //                 targets.push({x + dx, y + dy});
    //             }
    //             return; // Ngừng bắn sau khi tìm thấy mục tiêu
    //         }

        // }
    // }

    // std::cout << "Computer has no valid targets left to fire.\n";
}