#include "commands/Command.hpp"

JoinCommand::JoinCommand(Server *server) : Command(server) {}

JoinCommand::~JoinCommand() {}

// format : JOIN <channel>{,<channel>} [<key>{,<key>}]
void JoinCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty()) {
		client->sendMessage(ERR_NEEDMOREPARAMS("PASS"));
		return;
	}

	std::string name = arguments[0];
	std::string password = arguments.size() > 1 ? arguments[1] : "";

	Channel *channel = client->getChannel();

	if (channel) {
		client->sendMessage(ERR_TOOMANYCHANNELS);
		return;
	}

	channel = _server->getChannel(name);
	if (!channel)
		channel = _server->createChannel(name, password, client);

	if (channel->getPassword() != password) {
		client->sendMessage(ERR_BADCHANNELKEY);
		return;
	}

	client->join(channel);
}