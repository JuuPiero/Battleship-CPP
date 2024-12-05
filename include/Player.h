#pragma once
#include "Ship.h"
#include <vector>
#include <memory>
#include <queue>
class Player {
public:
    enum Role {
        MASTER,
        SLAVE
    };
    enum Strategy {
        NONE,
        ORDERED,
        CUSTOM
    };
    Player(Role role);
    ~Player() = default;
    void Shoot(int x, int y);
    // void Shot(int x, int y);
    void ShootOrdered(std::vector<std::vector<char>>& grid);
    void ShootCustom(std::vector<std::vector<char>>& grid);

    void DisplaytListShip();

    void DisplayMap();
    inline bool IsMaster() const { return role == Role::MASTER; };
    bool IsWinner();
    bool IsLose();
public:
    Role role;
    std::vector<Ship> ships;
    std::vector<std::vector<char>> map;
    std::queue<std::pair<int, int>> targets;
    bool isWinner = false;
    Strategy strategy = Strategy::NONE;
};
