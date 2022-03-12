//
// Created by Roberto Boldini on 3/12/22.
//

#include "commands/Command.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server): Command(server) {};

PrivMsgCommand::~PrivMsgCommand() {};

void PrivMsgCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments[0].empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PRIVMSG"));
		return;
	}
	if (arguments[0][0] == '#') {
		Channel *channel;
		if ((channel = client->getChannel()) != nullptr) {
			channel->sendMessage(arguments[1], client->getNickname());
			return;
		}
		client->sendMessage(ERR_NOSUCHCHANNEL);
	}
	Client *dest;
	if ((dest = _server->getClient(arguments[0])) != nullptr) {
		dest->sendMessage("");
		return;
	}
	client->sendMessage(ERR_NOSUCHNICK);
}
