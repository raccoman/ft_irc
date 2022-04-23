#ifndef FT_IRC_UTILS_H
#define FT_IRC_UTILS_H

#include <iostream>
#include <string>
#include <time.h>

//ERROR REPLIES
#define ERR_NEEDMOREPARAMS(source, command)		"461 " + source + " " + command + " :Not enough parameters"
#define ERR_NOTREGISTERED(source)				"451 " + source + " :You have not registered"
#define ERR_ALREADYREGISTERED(source)			"462 " + source + " :You may not reregister"
#define ERR_PASSWDMISMATCH(source)				"464 " + source + " :Password incorrect"
#define ERR_NONICKNAMEGIVEN(source)				"431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source)				"433 " + source + " " + source  + " :Nickname is already in use"
#define ERR_TOOMANYCHANNELS(source, channel)	"405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)		"442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)		"403 " + source + " " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(source, channel)		"475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_NOSUCHNICK(source)					"401 " + source + " " + source  + " :No such nick/channel"

//#define ERR_CHANOPRIVSNEEDED(source)			"482 " + source + " :You're not channel operator"
//#define ERR_USERNOTINCHANNEL(source)			"441 " + source + " :They aren't on that channel"

// PRIVMSG ERRORS
#define ERR_NOSUCHNICK							"PRIVMSG 401 * : No such nick."

// NUMERIC REPLIES
#define RPL_WELCOME(client)						"001 " + client + " :Welcome " + client + " to the ft_irc network"
#define RPL_NAMREPLY(client, channel, users)	"353 " + client + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(client, channel)			"366 " + client + " " + channel + " :End of /NAMES list."


// COMMAND REPLIES
#define RPL_JOIN(source, channel)				":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)				":" + source + " PART :" + channel
#define RPL_PING(source, token)					":" + source + " PONG :" + token
#define RPL_PONG(source, token)					":" + source + " PING :" + token
#define RPL_PRIVMSG(source, target, message)	":" + source + " PRIVMSG " + target + " :" + message
#define RPL_QUIT(source, message)				":" + source + " QUIT :Quit: " + message
//#define RPL_QUITOTHERS(source, message)						source + "QUIT:" + message


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
