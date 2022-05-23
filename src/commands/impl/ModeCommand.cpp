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
    // std::regex regex("([+-]i*)([+-]n*)([+-]t*)([+-]l*)([+-]k*)");
    // while (std::regex_search(arguments[1], match, regex))
    // {
    //     for (size_t i = 0; i < match.size(); ++i)
    //     {
    //         std::cout << match[i] << std::endl;
    //     }
    // }

    int i(-1);
    int n(2);
    char c;

    Channel *channel = client->getChannel();

    while ((c = arguments[1][++i]))
    {
        if (c == '+' || c == '-')
        {
            continue;
        }
        else if (c == 'i')
        {
            if (arguments[1][i - 1] == '-')
                // remove invite only
                std::cout << "meno i" << std::endl;
            else if (arguments[1][i - 1] == '+')
                // add invite only
                std::cout << "più i" << std::endl;
        }
        else if (c == 'n')
        {
            if (arguments[1][i - 1] == '-')
                // remove no external message
                ;
            else if (arguments[1][i - 1] == '+')
                // add no external message
                ;
        }
        else if (c == 't')
        {
            if (arguments[1][i - 1] == '-')
                // remove protected topic mode
                ;
            else if (arguments[1][i - 1] == '+')
                // add protected topic mode
                ;
        }
        else if (c == 'l')
        {
            if (arguments[1][i - 1] == '-')
                // remove client limit channel mode
                ;
            else if (arguments[1][i - 1] == '+')
            {
                // add client limit channel mod
                ;
                n++;
            }
        }
        else if (c == 'k')
        {
            if (arguments[1][i - 1] == '-')
			{
                channel->setPassword("");
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), "-k", ""));
			}
			else if (arguments[1][i - 1] == '+')
			{
                channel->setPassword(arguments[n]);
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), "+k", arguments[n]));
			}
		}
    }
}