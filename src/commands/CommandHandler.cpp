#include "commands/CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server) : _server(server)
{
	_commands["PASS"] = new PassCommand(_server);
	_commands["NICK"] = new NickCommand(_server);
	_commands["USER"] = new UserCommand(_server);
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::invoke(Client *client, const std::string &message)
{
	std::cout << message << std::endl;

	std::string name = message.substr(0, message.find(" "));
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);

	try
	{
		Command *command = _commands.at(name);

		std::string buf;
		std::vector<std::string> arguments;
		std::stringstream ss(message.substr(name.length(), message.length()));

		while (ss >> buf)
			arguments.push_back(buf);

		command->execute(client, arguments);
	}
	catch (const std::out_of_range &e)
	{
		char buffer[100];
		sprintf(buffer, "%s:%d has sent unknown command: %s.", client->getHostname().c_str(), client->getPort(), name.c_str());
		ft_log(buffer);
	}
}