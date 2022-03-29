#ifndef FT_IRC_UTILS_H
#define FT_IRC_UTILS_H

#include <iostream>
#include <string>
#include <time.h>

// ERROR REPLIES
#define ERR_NEEDMOREPARAMS(command)				"461 * " command " :Not enough parameters"
#define ERR_ALREADYREGISTERED					"462 * :You may not reregister"
#define ERR_PASSWDMISMATCH						"464 * :Password incorrect"
#define ERR_NICKNAMEINUSE						"433 * :Nickname is already in use"
#define ERR_NONICKNAMEGIVEN						"431 * :Nickname not given"
#define ERR_TOOMANYCHANNELS						"405 * :You have joined too many channels"
#define ERR_NOTONCHANNEL						"442 * :You're not on that channel"
#define ERR_NOSUCHCHANNEL						"403 * :No such channel"
#define ERR_BADCHANNELKEY						"475 * :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED					"482 * :You're not channel operator"
#define ERR_USERNOTINCHANNEL					"441 * :They aren't on that channel"
#define ERR_FATAL(message)						"ERROR :" message

// PRIVMSG ERRORS
#define ERR_NOSUCHNICK							"PRIVMSG 401 * : No such nick."

// REPLIES
#define RPL_WELCOME(nick)						"001 * :Welcome " + nick + " to the ft_irc network"
#define RPL_JOIN(client, channel)				":" + client + " JOIN :" + channel
#define RPL_NAMREPLY(client, channel, admins)	"353 * " + client + " = " + channel + " :" + admins
#define RPL_ENDOFNAMES(client, channel)			"366 * " + client + " " + channel + " :End of /NAMES list."

static inline void ft_log(const std::string &message) {
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
