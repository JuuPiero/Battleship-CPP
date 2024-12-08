#pragma once
#include "Ship.h"
#include <vector>
#include <memory>
#include <queue>
#include <tuple>

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
    bool Shoot(int x, int y);
    std::tuple<int, int, bool> ShootOrdered();
    std::tuple<int, int, bool> ShootCustom();

    void DisplaytListShip();
    void DisplayMap();
    inline bool IsMaster() const { return role == Role::MASTER; };

    bool MapEmpty();
    bool IsWinner();
    bool IsLose();
public:
    Role role;
    std::vector<Ship> ships;
    std::vector<std::vector<char>> map;
    std::queue<std::pair<int, int>> targets;
    bool isWinner = false;
    Strategy strategy;
};