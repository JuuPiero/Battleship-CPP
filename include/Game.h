#pragma once
#include "Command/CommandProcessor.h"
#include <memory>
#include <vector>
#include "Player.h"
class Game {
private:
    Game();
  
public:
    static std::shared_ptr<Game> GetInstance();
    void Initialize();
    void Run();
    void Render();

    inline uint64_t GetWidth() const { return m_Width; }
    inline uint64_t GetHeight() const { return m_Height; }

    void SetWidth(uint64_t width);
    void SetHeight(uint64_t height);

    inline void Reset() {
        isPlaying = false;
        countShipType_1 = 0;
        countShipType_2 = 0;
        countShipType_3 = 0;
        countShipType_4 = 0;
        m_Width = 0;
        m_Height = 0;
    }
public:
    bool isPlaying = false;
    std::shared_ptr<Player> master;
    std::shared_ptr<Player> slave;
    std::shared_ptr<Player> currentPlayer;
   
    std::vector<std::vector<char>> board;
public:
    uint32_t countShipType_1;
    uint32_t countShipType_2;
    uint32_t countShipType_3;
    uint32_t countShipType_4;
private:
    uint64_t m_Width;
    uint64_t m_Height;
    
    std::unique_ptr<CommandProcessor> m_Processor;
    static std::shared_ptr<Game> s_Instance;
};  




