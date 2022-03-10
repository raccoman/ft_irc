#include "commands/Command.hpp"

JoinCommand::JoinCommand(Server *server) : Command(server) {}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute(Client *client, std::vector<std::string> arguments) {

	std::string channelName = arguments[0];
	ft_log(channelName);
	std::string channelPassword = arguments[1];
	ft_log(channelPassword);

	if (client->getChannel() !=  nullptr) {
		client->sendMessage(ERR_TOOMANYCHANNELS(client->getNickname()));
		ft_log("ERROR: Channel already exists.");
		return;
	}

	if (_server->getChannel(channelName) == nullptr) {
		_server->addChannel(channelName, channelPassword, client);
		client->setChannel(_server->getChannel(channelName));
		client->sendMessage("Created Channel " + channelName);
	}
	else {
		Channel* channel = _server->getChannel(channelName);
		channel->addClient(client);
		client->setChannel(channel);
		client->sendMessage("Joined Channel " + channelName);
	}
}