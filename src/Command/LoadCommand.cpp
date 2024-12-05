#include "Command/Command.h"
#include <iostream>
#include "Game.h"
#include <string>
#include <fstream>
#include "Utils.h"
void LoadCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() < 2) {
        std::cout << "Usage: load <filename>" << std::endl;
        return;
    }
    std::string path = args[1];
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Cannot open file:" << path << std::endl;
        return;
    }
    auto game = Game::GetInstance();
    uint64_t w, h;
    file >> w >> h;
    if(game->currentPlayer->IsMaster()) {
        game->Reset();
        game->SetWidth(w);
        game->SetHeight(h);
        game->board = CreateMap(game->GetHeight(), game->GetWidth());
        game->master->map = CreateMap(game->GetHeight(), game->GetWidth());
        game->slave->map = CreateMap(game->GetHeight(), game->GetWidth());

    }
    else {
        game->slave->map = CreateMap(game->GetHeight(), game->GetWidth());
    }
   
    std::vector<Ship> ships;
    int type, x, y;
    char direction;
    bool isValid = true;

    while (file >> type >> direction >> x >> y) {
        Ship ship = {type, direction, x, y};
        if (isValidPosition(game->board, ship, w, h)) {
            // placeShipChar(game->board, ship);
            placeShip(game->currentPlayer->map, ship);
            ships.push_back(ship);
            ///////////////////////
            if(game->currentPlayer->IsMaster()) {
                switch (type) {
                    case 1:
                        game->countShipType_1++;
                        break;
                    case 2:
                        game->countShipType_2++;
                        break;
                    case 3:
                        game->countShipType_3++;
                        break;
                    case 4:
                        game->countShipType_4++;
                        break;
                    default:
                        break;
                }
            }
        } else {
            std::cerr << "Ship type " << type << " at (" << x << "," << y << ") not valid!\n";
            isValid = false;
        }
    }
    game->currentPlayer->ships = ships;
    file.close();
    game->Render();
    std::cout << "ok" << std::endl;
    game->currentPlayer->DisplaytListShip();
}