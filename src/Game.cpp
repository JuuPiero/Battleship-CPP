#define DEBUG 1
#include "Game.h"
#include <string>
#include <fstream>
#include "Ship.h"
#include "Utils.h"
std::shared_ptr<Game> Game::s_Instance = nullptr;

std::shared_ptr<Game> Game::GetInstance() {
    if (!s_Instance) s_Instance = std::shared_ptr<Game>(new Game());
    return s_Instance;
}

Game::Game() {
    m_Processor = std::make_unique<CommandProcessor>();
    isPlaying = false;
    Initialize();
}
void Game::Initialize() {
    Reset();
    master = std::make_shared<Player>(Player::Role::MASTER);
    master->strategy = Player::Strategy::ORDERED; //default

    slave = std::make_shared<Player>(Player::Role::SLAVE);
    currentPlayer = master;

    m_Processor->RegisterCommand("help", std::make_shared<HelpCommand>());
    m_Processor->RegisterCommand("ping", std::make_shared<PingCommand>());
    m_Processor->RegisterCommand("exit", std::make_shared<ExitCommand>());
    m_Processor->RegisterCommand("get", std::make_shared<GetCommand>());
    m_Processor->RegisterCommand("set", std::make_shared<SetCommand>());
    m_Processor->RegisterCommand("start", std::make_shared<StartCommand>());
    m_Processor->RegisterCommand("create", std::make_shared<CreateCommand>());
    m_Processor->RegisterCommand("load", std::make_shared<LoadCommand>());
    m_Processor->RegisterCommand("shot", std::make_shared<ShootCommand>());
    m_Processor->RegisterCommand("stop", std::make_shared<StopCommand>());
    m_Processor->RegisterCommand("win", std::make_shared<WinCommand>());
    m_Processor->RegisterCommand("lose", std::make_shared<LoseCommand>());
    m_Processor->RegisterCommand("finished", std::make_shared<FinishedCommand>());
    m_Processor->RegisterCommand("dump", std::make_shared<DumpCommand>());

}
void Game::Run() {
    Render();
    std::string input;
    while (true) {
        std::cout << "Strategy: " << ( master->strategy == 1 ? "Ordered" : "Custom") << std::endl;
        std::cout << (currentPlayer->IsMaster() ? "Master" : "Slave") << "@Battleship#:~$ ";
        std::getline (std::cin, input);
        m_Processor->ExecuteCommand(input);
    }
}

void Game::Render() {
    system("cls");
    std::cout << "\t\tBATTLESHIP GAME" << std::endl;
    std::cout << "Run 'help' for more information on a command." << std::endl;
    // std::cout << "Or run 'load default.txt' for quick setup game with default." << std::endl << std::endl;
    if(!isPlaying) {
        currentPlayer->DisplayMap();
        std::cout << std::endl;
        DrawGrid();
    }
    else {
        slave->DisplayMap();
        std::cout << std::endl;
        if(!currentPlayer->IsMaster()) {
            DisplayGrid(m_Width, m_Height);
            std::cout << std::endl;
        }
#if DEBUG
        master->DisplayMap();
#endif

    }
}


// void Game::Load(const char* path) {
//     std::ifstream file(path);
//     if (!file) {
//         std::cerr << "Cannot open file:" << path << std::endl;
//         return;
//     }

//     file >> m_Width >> m_Height;
//     board = CreateMap(m_Height, m_Width);

// }