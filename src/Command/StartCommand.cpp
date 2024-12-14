#include "Command/Command.h"
#include <iostream>
#include "Game.h"
#include "Utils.h"
void StartCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() > MAX_ARGS) {
        std::cout << "Too many arguments" << std::endl;
        return;
    }

    auto game = Game::GetInstance();
    if(game->GetWidth() <= 0 || game->GetHeight() <= 0){
        std::cout << "Cannot start game" << std::endl;
        std::cout << "Please set width and height, or load file" << std::endl;
        return;
    }


    if(game->master->MapEmpty()) {
        std::cout << "Master map is empty" << std::endl;
        std::cout << "Place master ships in the map" << std::endl;
        std::cout << "Ship type 1: " << game->countShipType_1 << std::endl;
        auto master = game->master;

        for (size_t i = 0; i < game->countShipType_1; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates (x, y) for ship type 1 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v - h) for ship type 1 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {1, direction, x, y};
            PlaceShip(master->map, {1, direction, x, y});
            master->ships.push_back(newShip);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < game->countShipType_2; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates for ship type 2 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v, h) for ship type 2 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {2, direction, x, y};
            PlaceShip(master->map, newShip);
            master->ships.push_back(newShip);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < game->countShipType_3; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates for ship type 3 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v, h) for ship type 3 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {3, direction, x, y};
            PlaceShip(master->map, newShip);
            master->ships.push_back(newShip);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < game->countShipType_4; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates for ship type 4 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v, h) for ship type 4 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {4, direction, x, y};
            PlaceShip(master->map, newShip);
            master->ships.push_back(newShip);
            std::cout << std::endl;
        }
        std::cin.ignore();
    }



    if(game->slave->MapEmpty()) {
        std::cout << "Slave map is empty" << std::endl;
        std::cout << "Place slave ships in the map" << std::endl;
        std::cout << "Ship type 1: " << game->countShipType_1 << std::endl;
        auto slave = game->slave;

        for (size_t i = 0; i < game->countShipType_1; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates (x, y) for ship type 1 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v - h) for ship type 1 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {1, direction, x, y};
            PlaceShip(slave->map, {1, direction, x, y});
            slave->ships.push_back(newShip);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < game->countShipType_2; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates for ship type 2 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v, h) for ship type 2 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {2, direction, x, y};
            PlaceShip(slave->map, newShip);
            slave->ships.push_back(newShip);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < game->countShipType_3; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates for ship type 3 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v, h) for ship type 3 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {3, direction, x, y};
            PlaceShip(slave->map, newShip);
            slave->ships.push_back(newShip);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < game->countShipType_4; i++) {
            int x, y;
            char direction;
            std::cout << "Enter coordinates for ship type 4 (" << i + 1 <<  "): ";
            std::cin >> x >> y;
            std::cout << "Enter direction (v, h) for ship type 4 (" << i + 1 <<  "): ";
            std::cin >> direction;
            Ship newShip = {4, direction, x, y};
            PlaceShip(slave->map, newShip);
            slave->ships.push_back(newShip);
            std::cout << std::endl;
        }
        std::cin.ignore();
    }

    // if(game->master->MapEmpty()) {
    //     game->Render();
    //     std::cout << "Master' map is empty." << std::endl;
    //     std::cout << "Load master's map before start" << std::endl;
    //     return;
    // }
    game->isPlaying = true;
    game->currentPlayer = game->slave;
    game->Render();
    std::cout << "ok" << std::endl;
   
}