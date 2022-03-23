//
// Created by Luca Marzano on 11/03/2022.
//

#include "commands/Command.hpp"

PartCommand::PartCommand(Server *server) : Command(server) {}

PartCommand::~PartCommand() {}

// format: PART <channel>{,<channel>} [<reason>]
void PartCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PART"));
		return;
	}

	std::string name = arguments[0];

	Channel *channel = _server->getChannel(name);
	if (!channel) {
		client->sendMessage(ERR_NOSUCHCHANNEL);
		return;
	}

	if (!client->getChannel() || client->getChannel()->getName() != name) {
		client->sendMessage(ERR_NOTONCHANNEL);
		return;
	}

	client->leave();
}