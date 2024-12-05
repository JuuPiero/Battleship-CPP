#pragma once
#include <vector>
#include <string>
#include <iostream>
class Command {
public:
    virtual ~Command() = default;
    virtual void Execute(const std::vector<std::string>& args) = 0;
};

class HelpCommand : public Command {
public:
    void Execute(const std::vector<std::string>& args) override;
};

class PingCommand : public Command {
public:
    inline void Execute(const std::vector<std::string>& args) override {
        std::cout << "pong" << std::endl;
    }
};

class ExitCommand : public Command {
public:
    inline void Execute(const std::vector<std::string>& args) override {
        std::cout << "ok" << std::endl;
        exit(0);
    }
};

class SetCommand : public Command {
public:
    const unsigned int MAX_ARGS = 4;
    void Execute(const std::vector<std::string>& args) override;
};

class GetCommand : public Command {
public:
    const unsigned int MAX_ARGS = 3;
    void Execute(const std::vector<std::string>& args) override;
};

class StartCommand : public Command {
    const unsigned int MAX_ARGS = 1;
    void Execute(const std::vector<std::string>& args) override;
};

class StopCommand : public Command {
    const unsigned int MAX_ARGS = 1;
    void Execute(const std::vector<std::string>& args) override;
};

class CreateCommand : public Command {
    const unsigned int MAX_ARGS = 2;
    void Execute(const std::vector<std::string>& args) override;
};

class ShootCommand : public Command {
    const unsigned int MAX_ARGS = 3;
    void Execute(const std::vector<std::string>& args) override;
};




class LoadCommand : public Command {
    const unsigned int MAX_ARGS = 2;
    void Execute(const std::vector<std::string>& args) override;
};



class DumpCommand : public Command {
    const unsigned int MAX_ARGS = 2;
    void Execute(const std::vector<std::string>& args) override;
};


class WinCommand : public Command {
    void Execute(const std::vector<std::string>& args) override;
};

class LoseCommand : public Command {
    void Execute(const std::vector<std::string>& args) override;
};

class FinishedCommand : public Command {
    void Execute(const std::vector<std::string>& args) override;
};