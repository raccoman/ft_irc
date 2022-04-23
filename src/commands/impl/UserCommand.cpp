#include "commands/Command.hpp"

UserCommand::UserCommand(Server *server, bool auth) : Command(server, auth) {}

UserCommand::~UserCommand() {}

void UserCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (client->isRegistered()) {
		client->reply(ERR_ALREADYREGISTERED(client->getNickname()));
		return;
	}

	if (arguments.size() < 4) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "USER"));
		return;
	}
	client->setUsername(arguments[0]);
	client->setRealName(arguments[3]);
	client->welcome();
}