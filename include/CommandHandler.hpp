#ifndef FT_IRC_COMMANDHANDLER_HPP
#define FT_IRC_COMMANDHANDLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Client.hpp"
#include "logger.hpp"
#include "Command.hpp"

#include "commands/NickCommand.hpp"

class CommandHandler
{

private:
	std::map<std::string, Command *> _commands;

public:
	CommandHandler();
	~CommandHandler();

	void invoke(Client *client, const std::string &message);
};

#endif // FT_IRC_COMMANDHANDLER_HPP
