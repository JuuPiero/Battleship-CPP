#include "Command/Command.h"
#include <iostream>
void HelpCommand::Execute(const std::vector<std::string>& args) {
    std::cout << "List of commands:\n";
    std::cout << "  - help: Display all commands.\n";
    std::cout << "  - exit: Exit the game.\n";
    std::cout << "  - start: Start the game.\n";
    std::cout << "  - stop: Stop the current game.\n";
    std::cout << "  - set width <N>(integer): Set the map's width.\n";
    std::cout << "  - get width: Return the map's width.\n";
    std::cout << "  - set height <N>(integer): Set the map's height.\n";
    std::cout << "  - get height: Return the map's height.\n";
    std::cout << "  - set count <type> <N>(integer): Set the number of ships for a specific type.\n";
    std::cout << "  - get count <type>: Get the number of ships for a specific type.\n";
    std::cout << "  - set strategy <ordered/custom>: Choose the playing strategy.\n";
    std::cout << "  - shot <X> <Y>: Fire at the coordinate (X, Y).\n";
    std::cout << "  - shot: Get the coordinate for the next shot.\n";
    std::cout << "  - finished: Check if the game is over.\n";
    std::cout << "  - win: Check if you are the winner.\n";
    std::cout << "  - lose: Check if you lost the game.\n";
    std::cout << "  - dump <PATH>: Save the map's size and ship layout to a file.\n";
    std::cout << "  - load <PATH>: Load the map's size and ship layout from a file.\n";
    std::cout << "  - ping: Check the connection.\n";
    std::cout << "  - create [master/slave]: Create a game in master or slave mode.\n";
}