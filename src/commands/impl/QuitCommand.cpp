//
// Created by Roberto Boldini on 3/11/22.
//
#include "commands/Command.hpp"

QuitCommand::QuitCommand(Server *server, bool auth) : Command(server, auth) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(Client *client, std::vector<std::string> arguments) {
	_server->onClientDisconnect(client->getPollFD()->fd);
}