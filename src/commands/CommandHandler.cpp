#include "commands/CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server) : _server(server) {
	_commands["PASS"] = new PassCommand(_server, false);
	_commands["NICK"] = new NickCommand(_server, false);
	_commands["USER"] = new UserCommand(_server, false);
	_commands["QUIT"] = new QuitCommand(_server, false);

	//_commands["JOIN"] = new JoinCommand(_server);
	//_commands["PART"] = new PartCommand(_server);
//	TODO: PART, QUIT, KICK commands to be implemented
}

CommandHandler::~CommandHandler() {
}

void CommandHandler::invoke(Client *client, const std::string &message) {

	std::string name = message.substr(0, message.find(' '));
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);

	try {
//		TODO: Some commands may not use arguments in that case the _command.at(name) fail. Need a fix

		Command *command = _commands.at(name);

		std::vector<std::string> arguments;

		std::string buf;
		std::stringstream ss(message.substr(name.length(), message.length()));

		while (ss >> buf) {
			arguments.push_back(buf);
		}

		if (!client->isRegistered() && command->authRequired()) {
			client->sendMessage("0 * : You need to be registered in order to do that.");
			return;
		}
		command->execute(client, arguments);
	}
	catch (const std::out_of_range &e) {
		char buffer[100];
		sprintf(buffer, "%s:%d has sent unknown command: %s", client->getHostname().c_str(), client->getPort(), name.c_str());
		ft_log(buffer);
	}
}