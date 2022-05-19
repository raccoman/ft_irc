#include "commands/CommandHandler.hpp"

CommandHandler::CommandHandler(Server *server) : _server(server)
{
	_commands["PASS"] = new PassCommand(_server, false);
	_commands["NICK"] = new NickCommand(_server, false);
	_commands["USER"] = new UserCommand(_server, false);
	_commands["QUIT"] = new QuitCommand(_server, false);

	_commands["PING"] = new PingCommand(_server);
	_commands["PONG"] = new PongCommand(_server);
	_commands["JOIN"] = new JoinCommand(_server);
	_commands["MODE"] = new ModeCommand(_server);
	_commands["PART"] = new PartCommand(_server);
	_commands["KICK"] = new KickCommand(_server);

	_commands["PRIVMSG"] = new PrivMsgCommand(_server);
	_commands["NOTICE"] = new NoticeCommand(_server);
}

CommandHandler::~CommandHandler()
{
	for (std::map<std::string, Command *>::iterator it = _commands.begin(); it != _commands.end(); it++)
		delete it->second;
}

void CommandHandler::invoke(Client *client, const std::string &message)
{

	std::stringstream ssMessage(message);
	std::string syntax;

	while (std::getline(ssMessage, syntax))
	{

		syntax = syntax.substr(0, syntax[syntax.length() - 1] == '\r' ? syntax.length() - 1 : syntax.length());
		std::string name = syntax.substr(0, syntax.find(' '));

		try
		{
			Command *command = _commands.at(name);

			std::vector<std::string> arguments;

			std::string buf;
			std::stringstream ss(syntax.substr(name.length(), syntax.length()));

			while (ss >> buf)
			{
				arguments.push_back(buf);
			}

			if (!client->isRegistered() && command->authRequired())
			{
				client->reply(ERR_NOTREGISTERED(client->getNickname()));
				return;
			}

			command->execute(client, arguments);
		}
		catch (const std::out_of_range &e)
		{
			client->reply(ERR_UNKNOWNCOMMAND(client->getNickname(), name));
		}
	}
}