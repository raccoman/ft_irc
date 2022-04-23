#include "commands/Command.hpp"

PingCommand::PingCommand(Server *server) : Command(server) {}

PingCommand::~PingCommand() {}

void PingCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PING"));
		return;
	}

	client->reply(RPL_PING(client->getNickname(), arguments.at(0)));
}