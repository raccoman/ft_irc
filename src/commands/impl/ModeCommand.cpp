#include "commands/Command.hpp"

ModeCommand::ModeCommand(Server *server) : Command(server) {}

ModeCommand::~ModeCommand() {}

// format: KICK <channel> <user> *( "," <user> ) [<comment>]
void ModeCommand::execute(Client *client, std::vector<std::string> arguments)
{

    (void)client;

    if (arguments.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
        return;
    }

    // std::smatch match;
    // std::regex regex("([+-]i)*([+-]n)*([+-]t)*([+-]l)*([+-]k)*");
    // while (std::regex_search(arguments[1], match, regex))
    // {
    //     for (size_t i = 0; i < match.size(); ++i)
    //     {
    //         std::cout << match[i] << std::endl;
    //     }
    // }
}