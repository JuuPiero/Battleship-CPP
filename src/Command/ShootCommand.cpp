#include "Command/Command.h"
#include "Game.h"

void ShootCommand::Execute(const std::vector<std::string>& args) {

    if(args.size() < 3) {
        std::cout << "Too few arguments" << std::endl;
        return;
    }
    auto game = Game::GetInstance();
    
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

    bool result = game->currentPlayer->Shoot(x, y);
  
    if(game->master->strategy == Player::Strategy::ORDERED) {
        game->master->ShootOrdered(game->slave->map);
    }
    else if(game->master->strategy == Player::Strategy::CUSTOM) {
        game->master->ShootCustom(game->slave->map);

    }
    game->Render();
    std::cout << (result ? "hit" : "miss") << std::endl;
}