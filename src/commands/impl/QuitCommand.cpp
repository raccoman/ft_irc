//
// Created by Roberto Boldini on 3/11/22.
//
#include "commands/Command.hpp"

QuitCommand::QuitCommand(Server *server, bool authRequired) : Command(server, authRequired) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(Client *client, std::vector<std::string> arguments) {

	std::string message = arguments.empty() ? "Leaved." : arguments.at(0).substr(1);

	client->write(RPL_QUIT(client->getPrefix(), message));
	_server->onClientDisconnect(client->getFD());
}