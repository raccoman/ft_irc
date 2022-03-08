#ifndef FT_IRC_COMMANDHANDLER_HPP
#define FT_IRC_COMMANDHANDLER_HPP

class CommandHandler;

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include "Command.hpp"

class CommandHandler
{

private:
	Server *_server;
	std::map<std::string, Command *> _commands;

public:
	CommandHandler(Server *server);

	~CommandHandler();

	void invoke(Client *client, const std::string &message);
};

#endif // FT_IRC_COMMANDHANDLER_HPP
