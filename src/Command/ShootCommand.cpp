#include "Command/Command.h"
#include "Game.h"

void ShootCommand::Execute(const std::vector<std::string>& args) {
    auto game = Game::GetInstance();
    // if(args.size() == 1) {
    //     std::cout << game->master-> << std::endl;
    //     return;
    // }

    if(args.size() < 3) {
        std::cout << "Too few arguments" << std::endl;
        return;
    }
    
    if(game->currentPlayer->IsMaster()) {
        std::cout << "You are not the slave player" << std::endl;
        return;
    }
    if(!game->isPlaying) {
        std::cout << "Game is not started" << std::endl;
        return;
    }

    int x = atoi(args[1].c_str());
    int y = atoi(args[2].c_str());

    game->currentPlayer->Shoot(x, y);

    if(game->master->strategy == Player::Strategy::ORDERED) {
        game->master->ShootOrdered(game->slave->map);
    }
    else if(game->master->strategy == Player::Strategy::CUSTOM) {
        // game->ChangePlayer();
        game->master->ShootCustom(game->slave->map);

    }
    game->Render();

}