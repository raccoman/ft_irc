#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

//ERROR REPLIES
#define ERR_UNKNOWNCOMMAND(source, command)				"421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)				"461 " + source + " " + command + " :Not enough parameters"
#define ERR_NOTREGISTERED(source)						"451 " + source + " :You have not registered"
#define ERR_ALREADYREGISTERED(source)					"462 " + source + " :You may not reregister"
#define ERR_PASSWDMISMATCH(source)						"464 " + source + " :Password incorrect"
#define ERR_NONICKNAMEGIVEN(source)						"431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source)						"433 " + source + " " + source  + " :Nickname is already in use"
#define ERR_TOOMANYCHANNELS(source, channel)			"405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)				"442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)				"403 " + source + " " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(source, channel)				"475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_NOSUCHNICK(source, nickname)				"401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel)	"441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_CHANOPRIVSNEEDED(source, channel)			"482 " + source + " " + channel + " :You're not channel operator"
#define ERR_CHANNELISFULL(source, channel)				"471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_CANNOTSENDTOCHAN(source, channel)			"404 " + source + " " + channel + " :Cannot send to channel"

// NUMERIC REPLIES
#define RPL_WELCOME(source)						"001 " + source + " :Welcome " + source + " to the ft_irc network"
#define RPL_NAMREPLY(source, channel, users)	"353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)			"366 " + source + " " + channel + " :End of /NAMES list."

// COMMAND REPLIES
#define RPL_JOIN(source, channel)					":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)					":" + source + " PART :" + channel
#define RPL_PING(source, token)						":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message)		":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message)			":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)					":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)	":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_MODE(source, channel, modes, args)		":" + source + " MODE " + channel + " " + modes + " " + args

static inline void ft_log(const std::string &message) {
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	std::string str(buffer);
	(void)message;
	std::cout << "[" << str << "] " << message << std::endl;
};

#endif //FT_IRC_UTILS_HPP
