//
// Created by Luca Marzano on 3/29/22.
//

#include "commands/Command.hpp"

KickCommand::KickCommand(Server *server, bool authRequired) : Command(server) {}

KickCommand::~KickCommand() {}

// format: KICK <channel> <user> *( "," <user> ) [<comment>]
void KickCommand::execute(Client *client, std::vector<std::string> arguments)
{
	if (arguments.size() < 2) {
		client->sendMessage(ERR_NEEDMOREPARAMS("KICK"));
		return;
	}

	std::string channel_name = arguments[0];
	Channel		*channel = _server->getChannel(channel_name);
	Client		*kicked;
	bool 		inChannel = false;

	// if <channel doesn't exist ERROR
	if (!channel) {
		client->sendMessage(ERR_NOSUCHCHANNEL);
		return;
	}
	// if user is not chanop command INVALID
	for (std::vector<Client *>::iterator ops = channel->getChanops().begin(); ops != channel->getChanops().end(); ops++) {
		if (client == *ops || client == channel->getAdmin()) {
			inChannel = true
			break;
		}
	}
	if (!inChannel) {
		client->sendMessage(ERR_CHANOPRIVSNEEDED);
	}
	inChannel = false;

	// if chanop is not on <channel> ERROR
	if (channel != client->getChannel()) {
		client->sendMessage(ERR_NOTONCHANNEL);
		return;
	}
	// if <user> is not in <channel> ERROR
	for (std::vector<Client *>::iterator list = channel->getClients().begin(); list != channel->getClients().end(); list++) {
		// if <user> is in <channel> remove <user> from <channel>
		kicked = *list;
		if (arguments[1] == kicked->getNickname()) {
			inChannel = true;
			kicked->kick(client->getNickname(), channel);
		}
	}
	if (!inChannel) {
		client->sendMessage(ERR_USERNOTINCHANNEL);
		return;
	}
}

/*
** ERR_NEEDMOREPARAMS (461)
** ERR_NOSUCHCHANNEL (403)
** ERR_CHANOPRIVSNEEDED (482)
** ERR_USERNOTINCHANNEL (441)
** ERR_NOTONCHANNEL (442)
 */