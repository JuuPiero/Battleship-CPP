#include "Command/Command.h"
#include <iostream>
#include "Game.h"
#include <fstream>
void DumpCommand::Execute(const std::vector<std::string>& args) {
    if(args.size() < 2) {
        std::cout << "Usage: dump <filename>" << std::endl;
        return;
    }
    auto game = Game::GetInstance();
    std::string path = args[1];
    std::ofstream outFile(path);

      if (outFile.is_open()) {
        // Ghi dữ liệu vào file
        outFile << game->GetWidth() << " " << game->GetHeight() << std::endl;
        for (auto &ship : game->currentPlayer->ships) {
            outFile << ship.type << " " << ship.direction << " " << ship.x << " " << ship.y << std::endl;
        }
        outFile.close();
        std::cout << "ok" << std::endl;
    } else {
        std::cerr << "failed" << std::endl;
    }
}