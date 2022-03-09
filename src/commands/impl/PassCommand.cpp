#include "commands/Command.hpp"

PassCommand::PassCommand(Server *server) : Command(server) {}

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

	if (_server->getPassword() != arguments[0]) {
		client->sendMessage(ERR_PASSWDMISMATCH);
		return;
	}

	client->sendMessage("The PASS was correct");
	client->setEntered(true);
	client->checkRegistered();
}