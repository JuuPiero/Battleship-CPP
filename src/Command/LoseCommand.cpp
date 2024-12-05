#include "Command/Command.h"
#include <iostream>
#include "Game.h"

void LoseCommand::Execute(const std::vector<std::string>& args) {
    auto game = Game::GetInstance();
    if(!game->isPlaying) {
        std::cout << "Game is not started" << std::endl;
        return;
    }
    if(game->currentPlayer->IsLose()) {
        std::cout << "yes" << std::endl;
    }
    else {
        std::cout << "no" << std::endl;
    }
}
