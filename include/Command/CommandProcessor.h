#pragma once
#include <functional>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>

#include "Command/Command.h"
class CommandProcessor {
private:
    std::unordered_map<std::string, std::shared_ptr<Command>> commands;

private:
    std::vector<std::string> SplitInput(const std::string& input);

public:
    inline void RegisterCommand(const std::string& name, std::shared_ptr<Command> command) {
        commands[name] = command;
    }


    void ExecuteCommand(const std::string& input);
};