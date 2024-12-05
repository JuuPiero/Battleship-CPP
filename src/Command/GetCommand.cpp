#include "Command/Command.h"
#include <iostream>
#include "Game.h"

void GetCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() > MAX_ARGS) {
        std::cout << "Too many arguments" << std::endl;
        return;
    }

    if (args.size() <= 1) { // Kiểm tra xem args[1] có tồn tại không
        std::cout << "Missing argument" << std::endl;
        std::cout << "\tUse 'get width' " << std::endl;
        std::cout << "\tUse 'get height' " << std::endl;
        std::cout << "\tUse 'get count [1, 2, 3, 4]' " << std::endl;
        return;
    }
    auto game = Game::GetInstance();

    if(args[1] == "width") {
        std::cout << game->GetWidth() << std::endl;
    }
    else if(args[1] == "height") {
        std::cout << game->GetHeight() << std::endl;
    }
    else if (args[1] == "count") {
        if(args.size() < 3) {
            std::cout << "Missing argument [1, 2, 3, 4]" << std::endl;
            return;
        }
        //TODO: log count of ship type
        int type = atoi(args[2].c_str());
        // std::cout<< 
        switch (type) {
            case 1:
                std::cout << game->countShipType_1 << std::endl;
                break;
            case 2:
                std::cout << game->countShipType_2 << std::endl;
                break;
            case 3:
                std::cout << game->countShipType_3 << std::endl;
                break;
            case 4:
                std::cout << game->countShipType_4 << std::endl;
                break;
            default:
                break;
        }

    }
    else {
        std::cout << "Unknown argument: " << args[1] << std::endl;
    }
}