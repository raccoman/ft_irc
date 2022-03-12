#ifndef FT_IRC_UTILS_H
#define FT_IRC_UTILS_H

#include <iostream>
#include <string>
#include <time.h>

// ERROR REPLIES
#define ERR_NEEDMOREPARAMS(command) "461 * " command " :Not enough parameters"
#define ERR_ALREADYREGISTERED "462 * :You may not reregister"
#define ERR_PASSWDMISMATCH "464 * :Password incorrect"
#define ERR_NICKNAMEINUSE "433 * :Nickname is already in use"
#define ERR_NONICKNAMEGIVEN "431 * :Nickname not given"
#define ERR_TOOMANYCHANNELS(client) ("405 * " + (client) + ": You have joined too many channels")
#define ERR_FATAL(message) ("ERROR :" message)

// STANDARD REPLIES
#define RPL_WELCOME(nick) ("001 * :Welcome " + (nick) + " to the ft_irc network")

static inline void ft_log(const std::string &message)
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	std::string str(buffer);
	std::cout << "[" << str << "] " << message << std::endl;
};

#endif //FT_IRC_UTILS_H
