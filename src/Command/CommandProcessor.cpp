#include "Command/CommandProcessor.h"
#include <istream>
#include <string>

void CommandProcessor::ExecuteCommand(const std::string& input) {
    auto tokens = SplitInput(input);
    if (tokens.empty()) {
        // std::cout << "No command entered." << std::endl;
        return;
    }

    const std::string& commandName = tokens[0];
    auto it = commands.find(commandName);
    
    if (it != commands.end()) {
        it->second->Execute(tokens); // Truyền các token còn lại vào hàm execute
    } else {
        std::cout << "Unknown command: " << commandName << std::endl;
    }
}

std::vector<std::string> CommandProcessor::SplitInput(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}