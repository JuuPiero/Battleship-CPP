#include "Command/Command.h"
#include <iostream>
#include "Game.h"

void StopCommand::Execute(const std::vector<std::string>& args) {
    auto game = Game::GetInstance();

    game->isPlaying = false;
    game->currentPlayer = game->master;
    game->Reset();
    game->Render();
    std::cout << "ok" << std::endl;
}
