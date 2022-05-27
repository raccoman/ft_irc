#include "commands/Command.hpp"

JoinCommand::JoinCommand(Server *server) : Command(server) {}

JoinCommand::~JoinCommand() {}

// format : JOIN <channel>{,<channel>} [<key>{,<key>}]
void JoinCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PASS"));
		return;
	}

	std::string name = arguments[0];
	std::string password = arguments.size() > 1 ? arguments[1] : "";

	Channel *channel = client->getChannel();
	if (channel) {
		client->reply(ERR_TOOMANYCHANNELS(client->getNickname(), name));
		return;
	}

	channel = _server->getChannel(name);
	if (!channel)
		channel = _server->createChannel(name, password, client);

	if (channel->getMaxClients() > 0 && channel->getNumClients() >= channel->getMaxClients()){
		client->reply(ERR_CHANNELISFULL(client->getNickname(), name));
		return;
	}

	if (channel->getPassword() != password) {
		client->reply(ERR_BADCHANNELKEY(client->getNickname(), name));
		return;
	}

	client->join(channel);
}