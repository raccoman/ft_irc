#include "commands/NickCommand.hpp"
#include <iostream>

NickCommand::NickCommand()
{
}

NickCommand::~NickCommand()
{
}

void NickCommand::execute(Client *client, const std::string &name, std::vector<std::string> arguments)
{
    std::cout << "Called NICK command" << std::endl;
}