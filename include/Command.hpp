#ifndef FT_IRC_COMMAND_HPP
#define FT_IRC_COMMAND_HPP

#include <string>
#include "Client.hpp"
#include "logger.hpp"

class Command
{

public:
    Command(){};
    virtual ~Command(){};

    virtual void execute(Client *client, const std::string &name, std::vector<std::string> arguments) = 0;
};

#endif // FT_IRC_COMMAND_HPP