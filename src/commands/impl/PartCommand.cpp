//
// Created by Luca Marzano on 11/03/2022.
//
#include "commands/Command.hpp"

PartCommand::PartCommand(Server *server) : Command(server) {}

PartCommand::~PartCommand() {}

void PartCommand::execute(Client *client, std::vector<std::string> arguments) {
	Channel	*channel = client->getChannel();

	if (channel->getName() == arguments[0]) {
		ft_log("");
		std::cout << "leaving channel #" << channel->getName() << std::endl;// DEBUG

		client->setChannel(nullptr);
		if (channel->checkEmptyClients()) {
			_server->removeChannel(channel);// seems like it's not removing the channel from vector.
		}
	}
	std::cout << "-------" << std::endl;// DEBUG
	_server->printChannels();// DEBUG
	std::cout << "-------" << std::endl;// DEBUG
}