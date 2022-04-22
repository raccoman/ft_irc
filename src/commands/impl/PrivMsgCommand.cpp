//
// Created by Roberto Boldini on 3/12/22.
//

#include "commands/Command.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server) : Command(server) {};

PrivMsgCommand::~PrivMsgCommand() {};

void PrivMsgCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() < 2 || arguments[0].empty() || arguments[1].empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PRIVMSG"));
		return;
	}

	std::string target = arguments.at(0);
	std::string message;

	for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++) {
		message.append(*it + " ");
	}

	message = message.substr(1);

	if (target.at(0) == '#') {

		Channel *channel = client->getChannel();
		if (!channel)
			client->sendMessage(ERR_NOSUCHCHANNEL);

		channel->broadcast(RPL_PRIVMSG(client->getNickname(), target, message), client);
		return;
	}

	Client *dest = _server->getClient(target);
	if (!dest)
		client->sendMessage(ERR_NOSUCHNICK);

	dest->sendMessage(RPL_PRIVMSG(client->getNickname(), target, message));
}
