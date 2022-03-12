#include "commands/Command.hpp"

PassCommand::PassCommand(Server *server, bool auth) : Command(server, auth) {}

PassCommand::~PassCommand() {}

void PassCommand::execute(Client *client, std::vector<std::string> arguments)
{
	if (client->isRegistered()) {
		client->sendMessage(ERR_ALREADYREGISTERED);
		return;
	}

	if (arguments.empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PASS"));
		return;
	}

	if (_server->getPassword() != arguments[0].substr(1, arguments[0].length())) {
		client->sendMessage(ERR_PASSWDMISMATCH);
		return;
	}

	client->setState(::LOGIN);
}