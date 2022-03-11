#include "commands/CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server) : _server(server) {
	_commands["PASS"] = new PassCommand(_server);
	_commands["NICK"] = new NickCommand(_server);
	_commands["USER"] = new UserCommand(_server);
	_commands["QUIT"] = new QuitCommand(_server);

	_commands["JOIN"] = new JoinCommand(_server);
//	TODO: PART, QUIT, KICK commands to be implemented
}

CommandHandler::~CommandHandler() {
}

void CommandHandler::invoke(Client *client, const std::string &message) {
	std::cout << message << std::endl;

	std::string name = message.substr(0, message.find(' '));
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);

	try {
//		TODO: Some commands may not use arguments in that case the _command.at(name) fail. Need a fix

		ft_log(name);				// DEBUG

		Command *command = _commands.at(name);

		ft_log("DEBUG: _commands.at(name) PASSED! ✅");		// DEBUG

		std::vector<std::string> arguments;

		std::string buf;
		std::stringstream ss(message.substr(name.length(), message.length()));

		while (ss >> buf) {
			arguments.push_back(buf);
		}
		if (tryCommand(name) || (client->isRegistered() && !tryCommand(name) )) {
			command->execute(client, arguments);
		}
		else { client->sendMessage("0 * : You need to be registered in order to do that."); }
	}
	catch (const std::out_of_range &e) {
		char buffer[100];
		sprintf(buffer, "%s:%d has sent unknown command: %s", client->getHostname().c_str(), client->getPort(), name.c_str());
		ft_log(buffer);
	}
}