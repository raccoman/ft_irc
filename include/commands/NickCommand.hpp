#ifndef FT_IRC_NICKCOMMAND_HPP
#define FT_IRC_NICKCOMMAND_HPP

#include "Command.hpp"

class NickCommand : public Command
{
public:
    NickCommand();
    ~NickCommand();

    void execute(Client *client, const std::string &name, std::vector<std::string> arguments);
};

#endif