#include "commands/Command.hpp"

NoticeCommand::NoticeCommand(Server *server) : Command(server) {};

NoticeCommand::~NoticeCommand() {};

void NoticeCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.size() < 2 || arguments[0].empty() || arguments[1].empty()) {
		//client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "NOTICE"));
		return;
	}

	std::string target = arguments.at(0);
	std::string message;

	for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++) {
		message.append(*it + " ");
	}

	message = message.at(0) == ':' ? message.substr(1) : message;

	if (target.at(0) == '#') {

		Channel *channel = client->getChannel();
		if (!channel) {
			//client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), target));
			return;
		}

		if (channel->isNoExt()){
			std::vector<std::string>			nicknames(channel->getNicknames());
			std::vector<std::string>::iterator	i;
			
			for (i = nicknames.begin(); i != nicknames.end(); i++)
				if (*i == client->getNickname())
					break;
			if (i == nicknames.end())
			{
				client->reply(ERR_CANNOTSENDTOCHAN(client->getNickname(), target));
				return;
			}
		}

		channel->broadcast(RPL_NOTICE(client->getPrefix(), target, message), client);
		return;
	}

	Client *dest = _server->getClient(target);
	if (!dest) {
		//client->reply(ERR_NOSUCHNICK(client->getNickname(), target));
		return;
	}

	dest->write(RPL_NOTICE(client->getPrefix(), target, message));
}