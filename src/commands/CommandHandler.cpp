#include "CommandHandler.hpp"

CommandHandler::CommandHandler()
{
	_commands["NICK"] = new NickCommand();
	//     _commands["USER"] = NULL;
	//     _commands["HELP"] = NULL;
	//     _commands["PASS"] = NULL;
	//     _commands["QUIT"] = NULL;
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::invoke(Client *client, const std::string &message) // PASS ciaociao s a
{

	std::string name = message.substr(0, message.find(" "));
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);

	try
	{
		Command *command = _commands.at(name);

		std::vector<std::string> arguments;
		std::string arguments_text = message.substr(name.length(), message.length());

		size_t pos = 0;
		while ((pos = arguments_text.find(" ")) != std::string::npos)
		{
			arguments.push_back(arguments_text.substr(0, pos));
			arguments_text.erase(0, pos + 1);
		}

		command->execute(client, name, arguments);
	}
	catch (const std::out_of_range &e)
	{
		char message[1000];
		sprintf(message, "%s:%d has sent unknown command: %s.", client->getHostname().c_str(), client->getPort(), name.c_str());
		ft_log(message);
	}
}