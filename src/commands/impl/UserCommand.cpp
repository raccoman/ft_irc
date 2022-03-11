#include "commands/Command.hpp"

UserCommand::UserCommand(Server *server, bool auth) : Command(server, auth) {}

UserCommand::~UserCommand() {}

void UserCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (client->isRegistered()) {
		client->sendMessage(ERR_ALREADYREGISTERED);
		return;
	}

	if (arguments.size() < 4) {
		client->sendMessage(ERR_NEEDMOREPARAMS("USER"));
		return;
	}
	client->setUsername(arguments[0]);
	client->setRealName(arguments[3]);
	client->setState(::PLAY);
}