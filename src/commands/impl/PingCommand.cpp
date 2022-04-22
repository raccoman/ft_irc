#include "commands/Command.hpp"

PingCommand::PingCommand(Server *server) : Command(server) {}

PingCommand::~PingCommand() {}

void PingCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PING"));
		return;
	}

	client->sendMessage("PONG " + arguments.at(0));
}