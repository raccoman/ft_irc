#ifndef FT_IRC_IRCBOT_HPP
#define FT_IRC_IRCBOT_HPP

#include <iostream>
#include <string>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include <vector>
#include "utils.hpp"
#include "color.hpp"

class IrcBot {
public:
	IrcBot(const std::string &host, const std::string &port, const std::string &password);

	~IrcBot();

	void start();

private:
	int _sock;
	std::string _host;
	std::string _port;
	std::string _password;
	std::string _buffer;

	static void receiver(IrcBot *instance);

	int newSocket();

	void authenticate(const std::string &nick);

	void flush(const std::string &message);

	void sendPrivMsg(const std::string &source, const std::string &message);

	void sendFile(const std::string &source, const std::string &filename, const std::string &as);

	void onMessageReceived(const std::string &message);

	void onNumericReply(const std::string &source, const std::string &reply, std::vector<std::string> args);

	void onCommandReply(const std::string &source, const std::string &cmd, std::vector<std::string> args);
};

#endif
