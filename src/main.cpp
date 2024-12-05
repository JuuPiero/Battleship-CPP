#include "Game.h"

int main(int argc, char **argv) {
    auto game = Game::GetInstance();
    game->Run();
    return 0;
}