#include "Command/Command.h"
#include "Game.h"
void SetCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() > MAX_ARGS) {
        std::cout << "Too many arguments" << std::endl;
        return;
    }
    if (args.size() < 3) { 
        std::cout << "Missing argument" << std::endl;
        return;
    }
    auto game = Game::GetInstance();
    if(!game->currentPlayer->IsMaster()) {
        std::cout << "You are not master player" << std::endl;
        return;
    }

    if(args[1] == "width") {
        int width = atoi(args[2].c_str());
        game->SetWidth(width);
    }
    else if(args[1] == "height") {
        int height = atoi(args[2].c_str());
        game->SetHeight(height);
    }
    else if (args[1] == "strategy") {
        if(args[2] == "ordered") {
            game->currentPlayer->strategy = Player::Strategy::ORDERED;
        }
        else if(args[2] == "custom") {
            game->currentPlayer->strategy = Player::Strategy::CUSTOM;
        }
    }
    else if(args[1] == "count") {
        if(args.size() < 4) {
            std::cout << "Missing argument" << std::endl;
            return;
        }
        int count = atoi(args[3].c_str()); // quantity of 
        int type = atoi(args[2].c_str());
        if(type < 0 || type > 4) {
            std::cout << "Not valid ship type [1, 2, 3, 4]" << std::endl;
        }
        //TODO Set count ship type
        switch (type) {
            case 1:
                game->countShipType_1 = count;
                break;
            case 2:
                game->countShipType_2 = count;
                break;
            case 3:
                game->countShipType_3 = count;
                break;
            case 4:
                game->countShipType_4 = count;
                break;
            default:
                break;
        }
    }
    else {
        std::cout << "Unknown argument: " << args[1] << std::endl;
    }
    game->Render();
    std::cout << "ok" << std::endl;

}
