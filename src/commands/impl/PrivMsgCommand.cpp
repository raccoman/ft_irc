//
// Created by Roberto Boldini on 3/12/22.
//

#include "commands/Command.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server): Command(server) {};

PrivMsgCommand::~PrivMsgCommand() {};

void PrivMsgCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments[0].empty() || arguments[1].empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PRIVMSG"));
		return;
	}
	std::string fullMessage;
	for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++) {
		fullMessage.append(*it + " ");
	}

	if (arguments[0][0] == '#') {
		Channel *channel;
		if ((channel = client->getChannel()) != nullptr) {
			channel->sendMessage(fullMessage, client->getNickname());
			return;
		}
		client->sendMessage(ERR_NOSUCHCHANNEL);
	}

	Client *dest;
	if ((dest = _server->getClient(arguments[0])) != nullptr) {
		dest->sendMessage(fullMessage);
		return;
	}
	client->sendMessage(ERR_NOSUCHNICK);
}
