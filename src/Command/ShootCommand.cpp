#include "Command/Command.h"
#include "Game.h"
#include <tuple>
void ShootCommand::Execute(const std::vector<std::string>& args) {
    auto game = Game::GetInstance();
    if(!game->isPlaying) {
        std::cout << "Game is not started" << std::endl;
        return;
    }
    if(args.size() == 1) {
        std::pair<int, int> coords;
        if(game->master->strategy == Player::Strategy::ORDERED) {
            auto [x, y, hit] =  game->master->ShootOrdered();
            game->Render();
            std::cout << x << " " << y << std::endl;
            std::cout << (hit ? "hit" : "miss") << std::endl;
        }
        else if(game->master->strategy == Player::Strategy::CUSTOM) {
            auto [x, y, hit] = game->master->ShootCustom();
            game->Render();
            std::cout << x << " " << y << std::endl;
            std::cout << (hit ? "hit" : "miss") << std::endl;
        }
        return;
    }

    if(args.size() < 3) {
        std::cout << "Too few arguments" << std::endl;
        return;
    }
 
    int x = atoi(args[1].c_str());
    int y = atoi(args[2].c_str());
    bool result = game->currentPlayer->Shoot(x, y);
    game->Render();
    std::cout << (result ? "hit" : "miss") << std::endl;
}