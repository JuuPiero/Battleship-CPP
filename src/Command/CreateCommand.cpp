#include "Command/Command.h"
#include <iostream>
#include "Game.h"
void CreateCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() < 2) {
        std::cout << "Missing argument" << std::endl;
    }
    if(args.size() > MAX_ARGS) {
        std::cout << "Too many arguments" << std::endl;
        return;
    }

    auto game = Game::GetInstance();
    if(game->isPlaying) {
        std::cout << "Cannot create while playing " << std::endl;
        return;
    }
    if(args[1] == "master") {
        game->currentPlayer = game->master;
    }
    else if(args[1] == "slave") {
        game->currentPlayer = game->slave;
    }
    else {
        std::cout << "Invalid argument" << std::endl;
    }
    game->Render();
    std::cout << "ok" << std::endl;

}