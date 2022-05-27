#include "commands/Command.hpp"

ModeCommand::ModeCommand(Server *server) : Command(server) {}

ModeCommand::~ModeCommand() {}

void ModeCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
		return;
	}

	std::string target = arguments.at(0);

	Channel *channel = _server->getChannel(target); //MODE on clients not implemented
	if (!channel) {
		client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), target));
		return;
	}

	if (channel->getAdmin() != client) {
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickname(), target));
		return;
	}

	int i = 0;
	int p = 2;
	char c;

	while ((c = arguments[1][i])) {

		char prevC = i > 0 ? arguments[1][i - 1] : '\0';
		bool active = prevC == '+';

		switch (c) {

			case 'n': {
				channel->setNoExt(active);
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+n" : "-n"), ""));
				break;
			}

			case 'l': {
				channel->setMaxClients(active ? std::stol(arguments[p]) : 0);
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+l" : "-l"), (active ? arguments[p] : "")));
				p += active ? 1 : 0;
				break;
			}

			case 'k': {
				channel->setPassword(active ? arguments[p] : "");
				channel->broadcast(RPL_MODE(client->getPrefix(), channel->getName(), (active ? "+k" : "-k"), (active ? arguments[p] : "")));
				p += active ? 1 : 0;
				break;
			}

			default:
				break;
		}

		i++;
	}
}