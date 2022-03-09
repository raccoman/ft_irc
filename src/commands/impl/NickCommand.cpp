#include "commands/Command.hpp"

NickCommand::NickCommand(Server *server) : Command(server) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty() || arguments[0].empty()) {
		client->sendMessage(ERR_NONICKNAMEGIVEN);
		return;
	}

	std::string nickname = arguments[0];

	if (_server->getClient(nickname)) {
		client->sendMessage(ERR_NICKNAMEINUSE);
		return;
	}

	client->setNickname(nickname);
	client->checkRegistered();
}