//
// Created by Luca Marzano on 3/29/22.
//

#include "commands/Command.hpp"

KickCommand::KickCommand(Server *server) : Command(server) {}

KickCommand::~KickCommand() {}

// format: KICK <channel> <user> *( "," <user> ) [<comment>]
void KickCommand::execute(Client *client, std::vector<std::string> arguments) {
	(void)client;
	(void)arguments;
}

/*
** ERR_NEEDMOREPARAMS (461)
** ERR_NOSUCHCHANNEL (403)
** ERR_CHANOPRIVSNEEDED (482)
** ERR_USERNOTINCHANNEL (441)
** ERR_NOTONCHANNEL (442)
 */