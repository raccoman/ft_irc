#include "commands/Command.hpp"

PassCommand::PassCommand(Server *server) : Command(server)
{
}

PassCommand::~PassCommand()
{
}

void PassCommand::execute(Client *client, std::vector<std::string> arguments)
{

    if (client->isRegistered())
    {
        client->sendMessage(ERR_ALREADYREGISTERED);
        return;
    }

    if (arguments.size() <= 0)
    {
        client->sendMessage(ERR_NEEDMOREPARAMS("PASS"));
        return;
    }

    if (_server->getPassword().compare(arguments[0]) != 0)
    {
        client->sendMessage(ERR_PASSWDMISMATCH);
        return;
    }
}