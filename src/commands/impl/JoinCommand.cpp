#include "commands/Command.hpp"

JoinCommand::JoinCommand(Server *server) : Command(server) {}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute(Client *client, std::vector<std::string> arguments) {

	std::string channelName = arguments[0];
	std::string channelPassword = arguments[1];

	if (client->getChannel() !=  nullptr) {
		client->sendMessage(ERR_TOOMANYCHANNELS(client->getNickname()));
		return;
	}

	if (!_server->getChannel(channelName)) {
		_server->addChannel(channelName, channelPassword);
		client->setChannel(_server->getChannel(channelName));
		client->sendMessage("Joined Channel" + channelName);
	}

}