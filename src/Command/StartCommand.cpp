#include "Command/Command.h"
#include <iostream>
#include "Game.h"
void StartCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() > MAX_ARGS) {
        std::cout << "Too many arguments" << std::endl;
        return;
    }

    auto game = Game::GetInstance();
    if(game->GetWidth() <= 0 || game->GetHeight() <= 0){
        std::cout << "Cannot start game" << std::endl;
        return;
    }
    game->isPlaying = true;
    game->currentPlayer = game->slave;
    game->Render();
    std::cout << "ok" << std::endl;

    // std::string newInput;
    // int x, y;
    // while(true) {
    //     std::cout << "is playing...:";
    //     std::getline(std::cin, newInput);
    //     if(newInput == "stop") {
    //         std::cout << "ok" << std::endl;
    //         break;
    //     }
    //     // std::cin >> x >> y;
    //     // if(x < 0 || y < 0 || x >= game->GetWidth() || y >= game->GetHeight()) {
    //     //     std::cout << "Invalid location" << std::endl;
    //     //     continue;
    //     // }
    // }
}