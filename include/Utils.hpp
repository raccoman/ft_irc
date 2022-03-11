#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

// ERROR REPLIES
#define ERR_NEEDMOREPARAMS(command) "461 * " command " :Not enough parameters"
#define ERR_ALREADYREGISTERED "462 * :You may not reregister"
#define ERR_PASSWDMISMATCH "464 * :Password incorrect"
#define ERR_NICKNAMEINUSE "433 * :Nickname is already in use"
#define ERR_NONICKNAMEGIVEN "431 * :Nickname not given"
#define ERR_TOOMANYCHANNELS(client) ("405 * " + (client) + ": You have joined too many channels")

// STANDARD REPLIES
#define RPL_WELCOME(nick) ("001 * :Welcome " + (nick) + " to the ft_irc network")

static bool tryCommand(const std::string& name) {
	if (name == "PASS" || name == "NICK" || name == "USER" || name == "QUIT")
		return true;
	return false;
}

#endif //FT_IRC_UTILS_HPP
